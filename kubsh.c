
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>

#include<readline/readline.h>
#include<readline/history.h>
#define HISTORY_FILE ".kubsh_history"
sig_atomic_t signal_received = 0;

void debug( char* line){
printf("%s/n", line);}

void sig_handler(int signum){
signal_received = signum;
printf("Configuration reloaded");}

void print_env_var(const char *var_name){
if(var_name == NULL || strlen(var_name)== 0){
printf("Usage: \\e $VARNAME\n");
return;}

if(var_name[0] == '$'){var_name++;}

const char *value = getenv(var_name);
if(value==NULL){
printf("Variable '%s' not found.\n", var_name);
return;
}
char *copy=strdup(value);
if(!copy){
perror("strdup");
return;}

printf("%s = \n", var_name);

char*token= strtok(copy, ":");
if(token && strchr(value, ':')){
while(token!=NULL){
printf("-%s\n", token);
token=strtok(NULL, ":");

}}else { printf("%s\n",copy);
}free(copy);
}

int main() {


signal(SIGTSTP, sig_handler);
read_history(HISTORY_FILE);

printf("Kubsh started.\n");
    char *input;
while(true){
input = readline("$ ");
if(signal_received){
signal_received=0;
return 0;}
if(input== NULL){
break;}

add_history(input);
if(strcmp(input, "exit" ) == 0){
printf("exit from programm\n");
free(input);
break;}
else if(strcmp(input, "\\q")== 0){
printf("exit from programm\n");
free(input);
break;}
else if(strncmp(input, "\\e $PATH")== 0){
const char* var_name = input + 4;
while(*var_name == ' ') var_name++;
print_env_var(var_name);}
else if(strncmp(input, "debug", 5) == 0){
debug(input);}
else{printf("%s: command not found\n", input);}
free(input);
}
write_history(HISTORY_FILE);
return 0;
}






































