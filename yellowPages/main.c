#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "easyio.h"

#define CLEAR "\e[1;1H\e[2J"

int randint(int max){
    return rand() % max;
}

char names[10][30] = {
    "Thanos ",
    "Jose ",
    "Emiliano ",
    "Pedro ",
    "Carlos ",
    "Maria ",
    "Sara ",
    "Karla ",
    "Alma Marcela ",
    "Shrek "
};

char lastnames[10][30] = {
    "Campos ",
    "Gomez ",
    "Mendoza ",
    "Preciado ",
    "Crotolamo ",
    "Cero Cero Siete ",
    "Gozo ",
    "Serrano ",
    "Delgado ",
    "Barba "
};

typedef struct {
    char name[100];
    char number[11];
} Contact;

void printLogo(){
    printf(CLEAR);
    puts(" +-----+  +-----+  +-----+  +-+  + +   + +  +-----+   +-----+");
    puts(" | +-+ |  | +-+ |  | +---+  | |  | +-+ | |  | +-+ |   | +---+");
    puts(" | | | |  | | | |  | |      | |  |   +-+ |  | | | |   | +---+");
    puts(" | +-+ |  | +-+ |  | | +-+  | |  |       |  | +-+ |   +---+ |");
    puts(" | +---+  | +-+ |  | | | |  | |  | +-+   |  | +-+ |       | |");
    puts(" | |      | | | |  | +-+ |  | |  | | +-+ |  | | | |   +---+ |");
    puts(" +-+      +-+ +-+  +-----+  +-+  + +   + +  +-+ +-+   +-----+");
}

void printContactClear(Contact *contact){
    printf(CLEAR);
    printf("\n");
    printf("\tNombre:\t%s\n",contact->name);
    printf("\tNumero:\t%s\n",contact->number);
}

void printContact(Contact *contact){
    printf("\n");
    printf("\tNombre:\t%s\n",contact->name);
    printf("\tNumero:\t%s\n",contact->number);
}

void appendChar(char *str, char ch){
    char newElement[2] = {ch, '\0'};
    strcat(str, newElement);
}

void makeName(char *str){
    char res[100] = {0, '\0'};
    strcat(res, names[randint(9)]);
    strcat(res, lastnames[randint(9)]);
    strcpy(str, res);
}

void makeNumber(char *str){
    char res[100] = {0, '\0'};
    strcat(res, "33");
    for(int i = 0; i < 8; i++){
        appendChar(res, (char)randint(9)+48);
    }
    strcpy(str, res);
}

void newRandomContact(Contact **userarr, int *usernum, int *mode, int num){
    (*userarr) = realloc((*userarr), sizeof(Contact)*num);

    for(int i = 0; i < num; i++){
        makeName((*userarr)[i].name);
        makeNumber((*userarr)[i].number);
        printContact(&(*userarr)[i]);
    }
    (*usernum) = num;
    *mode = 0;
}

void searchContact(Contact **userarr, int *usernum, int*mode){
    char search[50];
    getString("Ingrese su termino de busqueda: ", search, 49);
    printf(CLEAR"\tUsuarios encontrados\n");

    for(int i = 0; i < (*usernum); i++){
        if(strstr((*userarr)[i].name,search)){
            printContact(&(*userarr)[i]);
        }
    }
    waitForEnter();
    *mode = 0;
}

void newContact(Contact **userarr, int *usernum, int*mode){
    char name[50];
    getString("Ingrese su nombre: ", name, 49);

    char number[11];
    getString("Ingrese su numero: ", number, 10);

    if(strlen(number) != 10){
        sendError("El numero debe ser de 10 digitos", mode);
        return;
    }

    (*userarr) = realloc((*userarr), sizeof(Contact)*(*usernum +1));
    strcpy((*userarr)[(*usernum)].name, name);
    strcpy((*userarr)[(*usernum)].number, number);

    (*usernum)++;

    sendMessage("Usted ha sido registrado exitosamente!");
    *mode = 0;
}

int main(){
    printf("%ld", __STDC_VERSION__);
    srand((unsigned int)time(NULL));

    int usernum = 0;
    int mode = 0;
    int run = 1;
    printLogo();

    Contact** userarr = calloc(usernum,sizeof(Contact)*(usernum+1));
    newRandomContact(userarr, &usernum, &mode, 15);

    searchContact(userarr, &usernum, &mode);

    free(*userarr);
    free(userarr);
    return 0;
}