#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define HISTORY_FILE ".kubsh_history"
#define MAX_PATH_LENGTH 1024
#define MAX_ARGS 64

sig_atomic_t signal_received = 0;

// Пункт 9: Обработчик сигнала SIGHUP
void sig_handler(int signum) {
    signal_received = signum;
    printf("\nConfiguration reloaded\n");
}

// Пункт 7: Вывод переменной окружения
void print_env_var(const char *var_name) {
    if (var_name == NULL || strlen(var_name) == 0) {
        printf("Usage: \\e $VARNAME\n");
        return;
    }

    // Пропускаем символ $ если он есть
    if (var_name[0] == '$') {
        var_name++;
    }

    const char *value = getenv(var_name);
    if (value == NULL) {
        printf("Variable '%s' not found.\n", var_name);
        return;
    }

    printf("%s = ", var_name);

    // Пункт 7: Если есть разделитель :, выводим списком
    if (strchr(value, ':') != NULL) {
        printf("\n");
        char *copy = strdup(value);
        if (!copy) {
            perror("strdup");
            return;
        }

        char *token = strtok(copy, ":");
        while (token != NULL) {
            printf("  - %s\n", token);
            token = strtok(NULL, ":");
        }
        free(copy);
    } else {
        printf("%s\n", value);
    }
}

// Функция от преподавателя: проверка исполняемости файла
int is_executable(const char *path) {
    return access(path, X_OK) == 0;
}

// Функция от преподавателя: поиск команды в PATH
char *find_in_path(const char *command) {
    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        return NULL;
    }

    // Создаем копию для strtok
    char *path_copy = strdup(path_env);
    if (path_copy == NULL) {
        perror("strdup");
        return NULL;
    }

    char *full_path = malloc(MAX_PATH_LENGTH);
    if (full_path == NULL) {
        perror("malloc");
        free(path_copy);
        return NULL;
    }

    // Разбиваем PATH на директории
    char *dir = strtok(path_copy, ":");
    while (dir != NULL) {
        // Формируем полный путь: директория + / + команда
        snprintf(full_path, MAX_PATH_LENGTH, "%s/%s", dir, command);
        
        // Проверяем, исполняемый ли файл
        if (is_executable(full_path)) {
            free(path_copy);
            return full_path;
        }
        
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    free(full_path);
    return NULL;
}

// Функция от преподавателя: запуск процесса
void fork_exec(char *full_path, int argc, char **argv) {
    int pid = fork();
    if (pid == 0) {
        // child process
        execv(full_path, argv);
        perror("execv");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // parent process
        int status;
        waitpid(pid, &status, 0);
    } else {
        perror("fork");
    }
}

// Пункт 5: Команда echo
void handle_echo(char *args) {
    if (args == NULL || strlen(args) == 0) {
        printf("\n");
        return;
    }
    
    // Пропускаем пробелы после "echo"
    char *text = args + 4;
    while (*text == ' ') text++;
    
    // Убираем кавычки если они есть
    if ((text[0] == '"' && text[strlen(text)-1] == '"') ||
        (text[0] == '\'' && text[strlen(text)-1] == '\'')) {
        text[strlen(text)-1] = '\0';
        text++;
    }
    
    printf("%s\n", text);
}

// Парсинг командной строки на аргументы
int parse_arguments(char *input, char **argv) {
    int argc = 0;
    char *token = strtok(input, " \t\n");
    
    while (token != NULL && argc < MAX_ARGS - 1) {
        argv[argc++] = token;
        token = strtok(NULL, " \t\n");
    }
    argv[argc] = NULL;
    
    return argc;
}

// Пункт 8: Выполнение команды
void execute_command(char *input) {
    char *argv[MAX_ARGS];
    char input_copy[MAX_PATH_LENGTH];
    
    // Создаем копию для разбивки на токены
    strncpy(input_copy, input, MAX_PATH_LENGTH - 1);
    input_copy[MAX_PATH_LENGTH - 1] = '\0';
    
    int argc = parse_arguments(input_copy, argv);
    if (argc == 0) {
        return;
    }
    
    // Пункт 6: Проверка введённой команды через поиск в PATH
    char *full_path = find_in_path(argv[0]);
    if (full_path != NULL) {
        fork_exec(full_path, argc, argv);
        free(full_path);
    } else {
        printf("%s: command not found\n", argv[0]);
    }
}

int main() {
    // Пункт 9: Обработка SIGHUP
    signal(SIGHUP, sig_handler);
    
    // Пункт 4: Работа с историей команд
    using_history();
    read_history(HISTORY_FILE);

    printf("Kubsh started. Type 'exit' or '\\q' to quit.\n");
    
    char *input;
    while (true) {
        input = readline("$ ");
        
        if (signal_received) {
            signal_received = 0;
            // Продолжаем работу после SIGHUP
        }
        
        // Пункт 2: Выход по Ctrl+D
        if (input == NULL) {
            printf("\n");
            break; // Ctrl+D
        }
        
        // Пропускаем пустые строки
        if (strlen(input) == 0) {
            free(input);
            continue;
        }
        
        // Пункт 4: Добавление в историю и сохранение
        add_history(input);
        write_history(HISTORY_FILE);
        
        // Пункт 3: Команда выхода \q
        if (strcmp(input, "exit") == 0 || strcmp(input, "\\q") == 0) {
            printf("Exiting kubsh.\n");
            free(input);
            break;
        }
        // Пункт 5: Команда echo
        else if (strncmp(input, "echo", 4) == 0) {
            handle_echo(input);
        }
        // Пункт 7: Вывод переменной окружения
        else if (strncmp(input, "\\e", 2) == 0) {
            char *var_name = input + 2;
            while (*var_name == ' ') var_name++;
            print_env_var(var_name);
        }
        // Пункт 8: Выполнение бинарника через поиск в PATH
        // Пункт 6: Проверка введённой команды
        else {
            execute_command(input);
        }
        
        free(input);
    }
    
    // Пункт 4: Сохранение истории при выходе
    write_history(HISTORY_FILE);
    return 0;
}
