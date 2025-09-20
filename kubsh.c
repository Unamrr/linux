#include <stdio.h>
#include <string.h>

int main() {
char input[100];
while(1)
{
printf("$");

if(fgets(input, 100, stdin)== NULL){
printf("\nExit Cntr+D\n");
break;
}
input[strlen(input) - 1] = '\0';

if(strcmp(input, "exit" ) == 0){
printf("exit from programm\n");
break;}
if(strcmp(input, "\\q" ) == 0){
printf("exit from programm\\q\n");
break;}
if(strcmp(input, "echo" ) == 0){
printf("123\n");
break;}


printf("%s: command not found\n",input);
}
return 0;
}
