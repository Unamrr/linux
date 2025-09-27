#include <stdio.h>
#include <string.h>

void debug(const char* input){
const char* text = input + 5;
while(*text == ''){
text++;}
printf("%s\n", input + 5);}

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
if(strncmp(input, "debug", 5)= 0) {
debug(input);}
else{
printf("%s: command not found\n",input);
}
}
return 0;
}


