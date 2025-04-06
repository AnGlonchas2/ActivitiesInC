#ifndef EASYIO_H
#define EASYIO_H

#include <stdio.h>

#define CLEAR "\e[1;1H\e[2J"

int randint(int min, int max){
    return rand() % ((max+1) -min) + min;
}

void clearBuffer(){
    fseek(stdin,0,SEEK_END);
}

void waitForEnter(){
    char str[2];
    printf("Presione enter para continuar...");
    fgets(str, 2, stdin);
    clearBuffer();
    str[strcspn(str, "\n")] = 0;
}

void sendError(const char* message, int *mode){
    puts(message);
    waitForEnter();
    *mode = 0;
}

void sendMessage(const char* message){
    puts(message);
    waitForEnter();
}

void getString(const char* message, char* str, const int buffsz){
    printf("%s",message);
    fgets(str, buffsz+1, stdin);
    str[strcspn(str, "\n")] = 0;
    clearBuffer();
}

void getInt(const char *message, int *num, int buffsz){
    char getint[buffsz+1];
    printf("%s", message);
    fgets(getint, sizeof(getint), stdin);
    *num = strtol(getint, NULL, 10);
    clearBuffer();
}

void getFloat(const char *message, float *num, int buffsz){
    char getfloat[buffsz+1];
    printf("%s", message);
    fgets(getfloat, sizeof(getfloat), stdin);
    *num = strtof(getfloat, NULL);
    clearBuffer();
}

#endif
