#ifndef ATM_H
#define ATH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CLEAR "\e[1;1H\e[2J"

typedef struct {
    float money;
    char name[30];
    char nip[5];
    int id;
} User;

// General Functions

void printTitle(){
    printf(CLEAR"Cajero BBVA v1.0.0 rev3\n");
    printf(" .----------------.  .----------------.  .----------------.  .----------------. \n");
    printf("| .--------------. || .--------------. || .--------------. || .--------------. |\n");
    printf("| |   ______     | || |   ______     | || | ____   ____  | || |      __      | |\n");
    printf("| |  |_   _ \\    | || |  |_   _ \\    | || ||_  _| |_  _| | || |     /  \\     | |\n");
    printf("| |    | |_) |   | || |    | |_) |   | || |  \\ \\   / /   | || |    / /\\ \\    | |\n");
    printf("| |    |  __'.   | || |    |  __'.   | || |   \\ \\ / /    | || |   / ____ \\   | |\n");
    printf("| |   _| |__) |  | || |   _| |__) |  | || |    \\ ' /     | || | _/ /    \\ \\_ | |\n");
    printf("| |  |_______/   | || |  |_______/   | || |     \\_/      | || ||____|  |____|| |\n");
    printf("| |              | || |              | || |              | || |              | |\n");
    printf("| '--------------' || '--------------' || '--------------' || '--------------' |\n");
    printf(" '----------------'  '----------------'  '----------------'  '----------------' \n");
    printf("Bienvenido\n");
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

void printUser(User user){
    printf(CLEAR);
    printf("\n");
    printf("\tNombre:\t%s\n",user.name);
    printf("\tDinero:\t%.2f\n",user.money);
    printf("\tId:\t%d\n",user.id);
    printf("\tNip:\t%s\n",user.nip);
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

// ATM pages

void retire(User **userarr, int *usernum, int *mode){
    char nip[5];
    int id;
    float quant;

    getInt("Ingrese su id: ",&id, 10);
    if(id < 0 || id > (*usernum) || (*usernum) == 0){
        sendError("Id invalido, por favor intentelo de nuevo", mode);
        return;
    }

    getString("Ingrese su nip: ", nip, 4);
    if(strcmp(nip, (*userarr)[id].nip) != 0){
        sendError("Nip incorrecto", mode);
        return;
    }

    getFloat("Ingrese la cantidad a retirar: ", &quant, 10);
    if(quant <= 0.0f){
        sendError("Acciones no disponibles", mode);
        return;
    }

    if(strcmp(nip, (*userarr)[id].nip) == 0 && quant <= (*userarr)[id].money){
        (*userarr)[id].money -= quant;
    }else{
        sendError("Error: Fondos insuficientes", mode);
        return;
    }

    puts("Por favor espere un momento...");
    sleep(1);
    puts("Por favor recoja su dinero");
    waitForEnter();
    *mode = 0;
}

void deposit(User **userarr, int *usernum, int *mode){
    char nip[5];
    int id;
    float quant;

    getInt("Ingrese su id: ",&id, 10);
    if(id < 0 || id > (*usernum) || (*usernum) == 0){
        sendError("Id invalido, por favor intentelo de nuevo", mode);
        return;
    }

    getString("Ingrese su nip: ", nip, 4);
    if(strcmp(nip, (*userarr)[id].nip) != 0){
        sendError("Error: nip no valido", mode);
        return;
    }

    getFloat("Ingrese la cantidad a almacenar: ", &quant, 10);
    if(quant <= 0.0f){
        sendError("Por favor, ingrese una cantidad valida", mode);
        return;
    }

    printf("Por favor introduzca $%.2f a la maquina\n", quant);
    sleep(2);

    if(strcmp(nip, (*userarr)[id].nip) == 0){
        (*userarr)[id].money += quant;
    }else{
        sendError("Error: Datos incorrectos", mode);
        return;
    }
    waitForEnter();
    *mode = 0;
}

void selectUser(User **userarr, int *usernum, int *mode){
    int id;
    char nip[5];

    printf("\tusernum: %d\n", (*usernum));
    printf(CLEAR"\n\tPerfiles\n");
    if((*usernum) == 0){
        sendError("No hay usuarios disponibles", mode);
        return;
    }

    for(int i = 0; i < (*usernum); i++){
        printf("Usuario: %d\tNombre:\t%s\n", i, (*userarr)[i].name);
    }

    getInt("Ingrese el id de usuario: ",&id, 4);
    getString("Ingrese el nip de usuario: ", nip, 4);

    if(strcmp(nip, (*userarr)[id].nip) == 0){
        printUser((*userarr)[id]);
        waitForEnter();
    }else{
        sendError("Error: Datos incorrectos", mode);
        return;
    }
    *mode = 0;
}

void getInfo(User **userarr, int *usernum, int *mode){
    char nip[5];
    int id;

    getInt("Ingrese su id: ", &id, 10);
    if(id < 0 || id > (*usernum) || (*usernum) == 0){
        sendError("Error: Datos incorrectos", mode);
        return;
    }

    getString("Ingrese su nip: ", nip, 4);
    if(strcmp(nip, (*userarr)[id].nip) == 0){
        printUser((*userarr)[id]);
        waitForEnter();
    }else{
        sendError("Error: Datos incorrectos", mode);
        return;
    }

    *mode = 0;
}

void newUser(User **userarr, int *usernum, int *mode){
    User tempUser = {0};
    getString("Ingrese su nombre: ", tempUser.name, sizeof(tempUser.name));
    getString("Ingrese su nip: ", tempUser.nip, 4);

    tempUser.id = (*usernum);
    tempUser.money = 0.0f;

    if(strlen(tempUser.nip) != 4){
        sendError("El nip proporcionado necesita ser de 4 caracteres", mode);
        return;
    }

    *userarr = realloc((*userarr), sizeof(User)*((*usernum)+1));

    // Copying the structure into the final user
    strcpy((*userarr)[(*usernum)].name, tempUser.name);
    strcpy((*userarr)[(*usernum)].nip, tempUser.nip);
    (*userarr)[(*usernum)].id = tempUser.id;
    (*userarr)[(*usernum)].money = tempUser.money;

    printUser((*userarr)[(*usernum)]);
    (*usernum)++;

    printf("Su id es %d\nPerfil guardado exitosamente\n", (*usernum)-1);
    waitForEnter();
    *mode = 0;
}

void mMenu(int *mode){
    int opt;
    printTitle();
    printf("\nEscriba el numero correspondiente a la opcion\n\n1.Registrarse\n2.Retirar dinero\n3.Depositar\n4.Informacion de la cuenta\n5.Seleccionar cuenta\n6.Salir\n");
    getInt("\nQue desea hacer? : ", &opt, 2);
    *mode = opt;
}

#endif