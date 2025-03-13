#include <stdio.h>
#include <stdlib.h>
#include "include/ATM.h"

int main(){
    int usernum = 0;
    int mode = 0;
    int run = 1;

    User** userarr = calloc(usernum,sizeof(User)*(usernum+1));

    while(run){
        switch (mode){
            case 0: mMenu(&mode); break;
            case 1: 
                newUser(userarr, &usernum, &mode);
                usernum++;
                break;
            case 2: retire(userarr, &usernum, &mode); break;
            case 3: deposit(userarr, &usernum, &mode); break;
            case 4: getInfo(userarr, &usernum, &mode); break;
            case 5: selectUser(userarr, &usernum, &mode); break;
            case 6: run = 0; break;
            default: mMenu(&mode);
        }
    }
    free(*userarr);
    free(userarr);
    return 0;
}