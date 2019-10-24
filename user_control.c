#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "untils.h"
#include "user_control.h"
#include "website_control.h"

// 注册用户
int registerUser() {
    USER user;
    PUSER u = &user;
    int isExist = 0;
    puts("请输入用户名：");
    while ((scanf_s("%s", u->userName, 50) != 1) || (isExist = checkUserIsExist(u->userName))) {
        if (isExist) {
            puts("用户已经注册，请重新输入~");
        } else {
            puts("无效的用户名，请重新输入~");
        }

        while (getchar() != '\n');
    }

    puts("请输入密码：");
    while (scanf_s("%s", u->password, 50) != 1) {
        puts("密码输入错误，请重新输入~");
        while (getchar() != '\n');
    }

    generaterUserID(u);

    // 写入user
    PUSER pu = NULL;;
    int elementCount = readUser(USERFILEINFO, sizeof(USER), &pu);
    if (elementCount && pu) {
        pu += elementCount;
        *pu = *u;
        pu -= elementCount;
        writeUser(USERFILEINFO, "wb", pu, elementCount + 1);
        free(pu);
    } else {
        writeUser(USERFILEINFO, "wb", u, elementCount + 1);
    }
    puts("恭喜，注册成功~");

    return 1;
}

// 登录
USER login() {
    char userName[50] = {0}, password[50];
    USER user;

    while (!checkUserInfoIsCorrect(userName, password, &user.id)) {
        if (strlen(userName) > 0) {
            puts("用户名或密码错误，请重新输入~");
        }
        puts("请输入用户名: ");
        while ((scanf_s("%s", userName, 50) != 1)) {
            puts("无效的用户名，请重新输入~");
            while (getchar() != '\n');
        }

        puts("请输入密码：");
        while (scanf_s("%s", password, 50) != 1) {
            puts("密码输入错误，请重新输入~");
            while (getchar() != '\n');
        }
    }
    puts("恭喜您, 登录成功~");
    strcpy_s(user.userName, sizeof(user.userName), userName);
    strcpy_s(user.password, sizeof(user.password), password);
    showUserControlMenu(user);
    return user;
}

// 生成并写入 USERID
void generaterUserID(PUSER u) {
        // 写入 USERID
    int* userIDS = NULL;
    int elementCountByUserID = readUserID(USERFILEBYID, sizeof(int), &userIDS);
    if (userIDS == NULL) { // 文件不存在, 直接write
        int temp[1] = { 1 };
        userIDS = temp;
        u->id = 1;
        writeUserID(USERFILEBYID, userIDS, 1);
    } else {
        // TODO: ID 只能自增到10 不支持删减。。
        int* temp = NULL;
        int currentID;
        int userIDSize = elementCountByUserID * sizeof(int);
        int tempSize = userIDSize + sizeof(int);
        currentID = userIDS[elementCountByUserID - 1] + 1;
        printf("id = %d \n", currentID);
        u->id = currentID; // 对用户进行赋值ID

        temp = (int*)malloc(tempSize);
        if (!temp) {
            puts("内存不足，程序退出~");
            exit(EXIT_FAILURE);
        }
        memset(temp, 0, tempSize);
        memcpy(temp, userIDS, userIDSize);
        free(userIDS);
        userIDS = NULL;

        userIDS = temp;
        userIDS[elementCountByUserID] = currentID;
        writeUserID(USERFILEBYID, userIDS, elementCountByUserID + 1);
        free(userIDS);
    }

}

// 写入文件, 注册用户时使用
int writeUser(char* fileName, char* mode, PUSER u, int puCount) {
    FILE* pf = NULL;

    int userSize = sizeof(USER);

    mode == NULL ? (mode = "w") : mode;

    if (fopen_s(&pf, fileName, mode) || pf == NULL) {
        printf("打开 %s 文件失败，重启电脑试一下~", fileName);
        exit(EXIT_FAILURE);
    }

    fwrite(u, userSize, puCount, pf);

    if (fclose(pf)) {
        return 0;
    }

    return 1;
}

// 从文件中读取所有文件信息
int readUser(char* fileName, int elementSize, PUSER* pu) {
    FILE* pf = NULL;
    int elementCount = 0;
    if (fopen_s(&pf, fileName, "rb") || pf == NULL) {
        return 0;
    }

    if (fseek(pf, SEEK_SET, SEEK_END)) {
        return elementCount;
    }
    long countSize = ftell(pf); // 总大小


    elementCount = countSize / elementSize;

    *pu = (PUSER)malloc(countSize + elementSize);
    memset(*pu, 0, countSize + elementSize);
    if (!pu) {
        return elementCount;
    }

    rewind(pf);

    fread(*pu, elementSize, elementCount, pf);

    fclose(pf);

    return elementCount;
}

// 从文件中读取所有的userID
int readUserID(char* fileName, int elementSize, int** pIDS) {
    FILE* pf;
    if (fopen_s(&pf, fileName, "rb") || pf == NULL) {
        return 0;
    }

    if (fseek(pf, SEEK_SET, SEEK_END)) {
        return 0;
    }
    long countSize = ftell(pf);
    int elementCount = countSize / elementSize;

    *pIDS = (int*)malloc(countSize + sizeof(int));
    if (*pIDS == NULL) return 0;
    memset(*pIDS, 0, countSize + 1);
    rewind(pf);

    if (fread_s(*pIDS, countSize, elementSize, elementCount, pf) == 0) {
        fclose(pf);
        return 0;
    }

    fclose(pf);

    return elementCount;
}

// 写入文件, 注册用户时使用
int writeUserID(char* fileName, int* pIDS, int elementCount) {
    FILE* pf = NULL;
    int bIsOpen = fopen_s(&pf, fileName, "wb");
    
    if (bIsOpen || pf == NULL) {
        printf("打开 %s 文件失败，重启电脑试一下~", fileName);
        exit(EXIT_FAILURE);
    }

    fwrite(pIDS, sizeof(int), elementCount, pf);

    fclose(pf);

    return 1;
}

// 展示所有用户信息
void showUser() {
    PUSER pu = NULL;
    int cout = readUser(USERFILEINFO, sizeof(USER), &pu);
    puts("show ");
    for (int i = 0; i < cout; i++) {
        printf("%s, %s, %d \n", pu[i].userName, pu[i].password, pu[i].id);
    }
    puts("show Done");
    
}

// 检查用户是否已经存在，存在的话就禁止注册
int checkUserIsExist(char* userName) {
    PUSER pu;
    int userCount = readUser(USERFILEINFO, sizeof(USER), &pu);
    int i = 0;
    while (i < userCount) {
        if (strcmp(pu[i].userName, userName) == 0) {
            return 1;
        }
        i++;
    }

    return 0;
}

// 校验用户信息是否正确， 用户名和密码
int checkUserInfoIsCorrect(char* userName, char* password, int* pID) {
    PUSER pu = NULL;
    int userCount = readUser(USERFILEINFO, sizeof(USER), &pu);
    int i = 0;
    if (pu == NULL) {
        return 0;
    }

    while (i < userCount) {
        if (!strcmp(pu[i].userName, userName) && !strcmp(pu[i].password, password)) {
            *pID = pu[i].id;
            return 1;
        }
        i++;
    }
    return 0;
}

// 修改密码
int modifyPassword(int userID) {
    PUSER pu;
    int userCount = readUser(USERFILEINFO, sizeof(USER), &pu);
    int i = 0;
    char oldPassword[50];
    char newPassword[50];
    while (i < userCount) {
        if (pu[i].id == userID) {
            break;
        }
        i++;
    }

    puts("请输入旧的密码: ");
    getStr(oldPassword, 50);
    int j = 5;
    while (strcmp(pu[i].password, oldPassword) != 0) {
        j--;
        printf("密码错误，请重新输入, 你还有%d次机会\n", j);
        if (j == 0) {
            puts("恶意操作，程序退出.");
            exit(EXIT_FAILURE);
        }

        getStr(oldPassword, 50);
        while (getchar() != '\n');
    }

    puts("请输入新的密码: ");
    getStr(newPassword, 50);
    strcpy_s(pu[i].password, sizeof(pu[i].password), newPassword);

    if (writeUser(USERFILEINFO, "wb", pu, userCount)) {
        puts("修改成功~");
    } else {
        puts("修改失败~");
    }
    showUserControlMenu(pu[i]);
    return 0;
}

// 登录后的下一步操作
void showUserControlMenu(USER user) {
    putchar('\n');
    puts("****************************请选择操作,直接回车退出程序****************************");
    putchar('\n');
    printf("%c: 退出程序           %c: 查看站点密码信息"
           "           %c: 修改密码\n", EXIT, WEBSITEVIEW, MODIFYPASSWORD);
    putchar('\n');
    puts("***********************************************************************************");
    char action;
    while (getchar() != '\n');
    scanf_s("%c", &action, 1);
    action = toupper(action);
    switch (action) {
        case EXIT:
            exitProgram();
        case MODIFYPASSWORD:
            modifyPassword(user.id);
            break;
        case WEBSITEVIEW:
            mainWebsite(user);
            break;
        default:
            exitProgram();
            break;
    }
}
