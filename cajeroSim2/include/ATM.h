#ifndef ATM_H
#define ATH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CLEAR "\e[1;1H\e[2J"

typedef struct {
    float money;
    char name[20];
    int nip;
    int id;
}User;

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

void waitForEnter(){
    char str[2];
    printf("Presione enter para continuar...");
    fgets(str, sizeof(str), stdin);
    fflush(stdin);
}

void getString(const char* message, char* str){
    printf("%s", message);
    fgets(str, sizeof(str), stdin);
    fflush(stdin);
    str[strcspn(str, "\n")] = 0;
}

int countNumbers(const char *str){
    int count = 0;
    for(int i = 0; i < sizeof(str); i++){
        if(str[i] >= 48 || str[i] <= 57){
            count++;
        }
    }
    return count;
}

void getInt(const char *message, int *num, int buffsz){
    char getint[buffsz+1];
    printf("%s", message);
    fgets(getint, sizeof(getint), stdin);
    fflush(stdin);
    *num = strtol(getint, NULL, 10);
}

void retire(User **userarr, int *usernum, int *mode){
    int nip;
    int id;
    int quant;

    getInt("Ingresa tu id: ",&id, 10);
    if(id > *usernum){
        printf("Id invalido, por favor intentelo de nuevo\n");
        waitForEnter();
        *mode = 0;
    }
    getInt("Ingresa tu nip: ",&nip, 10);
    getInt("Ingresa la cantidad a retirar: ", &quant, 10);
    if(quant <= 0){
        printf("Acciones no disponibles\n");
        waitForEnter();
        *mode = 0;
    }
    printf("Por favor espere un momento\n");
    sleep(1);
    waitForEnter();

    if(nip == (*userarr)[id].nip && quant <= (*userarr)[id].money){
        quant -= (*userarr)[id].money;
    }else{
        printf("Error: Fondos insuficientes\n");
        waitForEnter();
    }
    *mode = 0;
}


void deposit(User **userarr, int *usernum, int *mode){
    int nip;
    int id;
    int quant;

    getInt("Ingresa tu id: ",&id, 10);
    if(id > *usernum || id < 0){
        printf("Id invalido, por favor intentelo de nuevo\n");
        waitForEnter();
        *mode = 0;
    }
    getInt("Ingresa tu nip: ",&nip, 4);

    if(nip == -1){
        puts("Error: nip no valido");
        *mode = 0;
    }

    getInt("Ingresa la cantidad a almacenar: ", &quant, 10);
    if(quant <= 0){
        printf("Acciones no disponibles");
        waitForEnter();
        *mode = 0;
    }
    printf("Por favor introduzca $%.2f a la maquina\n", (float)quant);
    sleep(2);
    waitForEnter();

    if(nip == (*userarr)[id].nip){
        (*userarr)[id].money += quant;
    }else{
        printf("Error: Datos incorrectos\n");
        waitForEnter();
    }
    *mode = 0;
}


void selectUser(User **userarr, int *usernum, int *mode){
    int id, nip;
    printf(CLEAR"\n\tPerfiles\n");

    for(int i = 0; i < (*usernum); i++){
        printf("Usuario: %d\tNombre:\t%s\n", i, (*userarr)[i].name);
    }

    getInt("Ingresa el id de usuario: ",&id, 4);

    getInt("Ingresa el nip de usuario: ",&nip, 4);

    if(nip == (*userarr)[id].nip){
        printf(CLEAR);
        printf("\n\n");
        printf("\tNombre:\t%s\n",(*userarr)[id].name);
        printf("\tDinero:\t%.2f\n",(*userarr)[id].money);
        printf("\tId:\t%d\n",(*userarr)[id].id);
        printf("\tNip:\t%d\n",(*userarr)[id].nip);
        waitForEnter();

    }else{
        printf("Error: Datos incorrectos\n");
        waitForEnter();
        *mode = 0;
    }
    *mode = 0;
}

void newUser(User **userarr, int *usernum, int *mode){
    *userarr = realloc(*userarr, sizeof(User)*((*usernum) + 1));
    // Construir el struct
    (*userarr)[(*usernum)].money = 0;
    (*userarr)[(*usernum)].id = (*usernum);
    
    getString("Ingresa tu nombre: ", (*userarr)[(*usernum)].name);
    getInt("Ingresa tu nip: ",&(*userarr)[(*usernum)].nip, 4);

    printf("Tu id es %d\nPerfil guardado exitosamente\n", *usernum);
    waitForEnter();
    
    *mode = 0;
}

void getInfo(User **userarr, int *usernum, int *mode){
    int nip;
    int id;

    getInt("Ingresa tu id: ", &id, 10);
    getInt("Ingresa tu nip: ", &nip, 4);

    if(id > (*usernum)){
        printf("Error: Datos incorrectos\n");
        waitForEnter();
        *mode = 0;
    }


    if(nip == (*userarr)[id].nip){
        printf(CLEAR);
        printf("\n\n");
        printf("\tNombre:\t%s\n",(*userarr)[id].name);
        printf("\tDinero:\t%.2f\n",(*userarr)[id].money);
        printf("\tId:\t%d\n",(*userarr)[id].id);
        printf("\tNip:\t%d\n",(*userarr)[id].nip);
        waitForEnter();

    }else{
        printf("Error: Datos incorrectos\n");
        waitForEnter();
        *mode = 0;
    }

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