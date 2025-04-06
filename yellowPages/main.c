#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "easyio.h"
#include "yellowpages.h"

int main(){
    srand((unsigned int)time(NULL));

    int usernum = 0;
    int mode = 0;
    int run = 1;
    printLogo();

    Contact** userarr = calloc(usernum,sizeof(Contact)*(usernum+1));
    newRandomContact(userarr, &usernum, &mode, 15);

    while(run){
        switch(mode){
        case 0: mMenu(&mode); break;
        case 1: newContact(userarr, &usernum, &mode); break;
        case 2: searchContact(userarr, &usernum, &mode); break;
        case 3: listContacts(userarr, &usernum, &mode); break;
        case 4: run = 0; break;
        default: mode = 0;
        }
    }

    free(*userarr);
    free(userarr);
    return 0;
}