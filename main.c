#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "user_control.h"


int main()
{
    USER user;

    char action;
    puts("****************************请选择操作,直接回车退出程序****************************");
    putchar('\n');
    printf("%c：登录           %c：退出           %c: 注册\n", LOGIN, EXIT, REGISTER);
    putchar('\n');
    puts("***********************************************************************************");
    scanf_s("%c", &action, 1);
    action = toupper(action);

    switch (action) {
        case LOGIN:
            user = login();
            break;
        case EXIT: 
            exit(EXIT_SUCCESS);
            break;
        case REGISTER:
            registerUser();
            break;
        default:
            exit(EXIT_SUCCESS);
            break;
    }

    return 0;

}
