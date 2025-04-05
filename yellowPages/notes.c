#include <stdio.h>
#include <string.h>

/*

--Preguntas--

1. Dada la cadena "Programación", ¿qué imprime este código?

char texto[] = "Programación";
printf("%c", texto[strlen(texto) - 1]);

stdout: ├│
u ó, dependiendo de la tabla ascii


Pregunta 2:
 - ¿Por qué en C las cadenas de caracteres deben terminar con el carácter '\0'? 
 Ejemplifica. (5 pts)

 Para poder señalizar donde terminan las strings, esta manera de terminar strings
 facilita ver donde termina o empieza la memoria si tienes varias strings contiguas

*/

void invertString(char *str){
    char result[100];
    for(int i = strlen(str), j = 0; j < strlen(str); i--, j++){
        result[i] = str[j];
    }
    result[strlen(str)+1] = '\0';
    result[0] = 255;
    strcpy(str, result);
}

void makeUpper(char *str){
    for(int i = 0; i < strlen(str); i++){
        if(str[i] >= 'a' && str[i] <= 'z'){
            str[i] += 'A' - 'a';
        }
    }
}

int isVocal(char ch){
    if(ch == 'a'
        || ch == 'e'
        || ch == 'i'
        || ch == 'o'
        || ch == 'u'
        || ch == 'A'
        || ch == 'E'
        || ch == 'I'
        || ch == 'O'
        || ch == 'U'
    )
    { 
        return 1;
    }else{
        return 0;
    }
}

int countVocals(char *str){
    int counter = 0;
    for(int i = 0; i < strlen(str); i++){
        if(isVocal(str[i])) counter++;
    }
    return counter;
}

void quitVocals(char *str){
    char result[100];
    for(int i = 0, counter = 0; i < strlen(str); i++){
        if(!isVocal(str[i])){
            //printf("Letter: %c\t str[i]: %d\n", str[i], i);
            result[counter] = str[i];
            counter++;
        }
    }
    result[strlen(str)-4] = '\0';
    strcpy(str, result);
}

int main(){
    char string1[] = "reconocer1";
    makeUpper(string1);
    printf("%s\n", string1);
    invertString(string1);
    printf("%s\n", string1);
    quitVocals(string1);
    printf("%s\n", string1);
    return 0;
}