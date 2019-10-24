#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "untils.h"
#include "user_control.h"
#include "website_control.h"

// ע���û�
int registerUser() {
    USER user;
    PUSER u = &user;
    int isExist = 0;
    puts("�������û�����");
    while ((scanf_s("%s", u->userName, 50) != 1) || (isExist = checkUserIsExist(u->userName))) {
        if (isExist) {
            puts("�û��Ѿ�ע�ᣬ����������~");
        } else {
            puts("��Ч���û���������������~");
        }

        while (getchar() != '\n');
    }

    puts("���������룺");
    while (scanf_s("%s", u->password, 50) != 1) {
        puts("���������������������~");
        while (getchar() != '\n');
    }

    generaterUserID(u);

    // д��user
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
    puts("��ϲ��ע��ɹ�~");

    return 1;
}

// ��¼
USER login() {
    char userName[50] = {0}, password[50];
    USER user;

    while (!checkUserInfoIsCorrect(userName, password, &user.id)) {
        if (strlen(userName) > 0) {
            puts("�û����������������������~");
        }
        puts("�������û���: ");
        while ((scanf_s("%s", userName, 50) != 1)) {
            puts("��Ч���û���������������~");
            while (getchar() != '\n');
        }

        puts("���������룺");
        while (scanf_s("%s", password, 50) != 1) {
            puts("���������������������~");
            while (getchar() != '\n');
        }
    }
    puts("��ϲ��, ��¼�ɹ�~");
    strcpy_s(user.userName, sizeof(user.userName), userName);
    strcpy_s(user.password, sizeof(user.password), password);
    showUserControlMenu(user);
    return user;
}

// ���ɲ�д�� USERID
void generaterUserID(PUSER u) {
        // д�� USERID
    int* userIDS = NULL;
    int elementCountByUserID = readUserID(USERFILEBYID, sizeof(int), &userIDS);
    if (userIDS == NULL) { // �ļ�������, ֱ��write
        int temp[1] = { 1 };
        userIDS = temp;
        u->id = 1;
        writeUserID(USERFILEBYID, userIDS, 1);
    } else {
        // TODO: ID ֻ��������10 ��֧��ɾ������
        int* temp = NULL;
        int currentID;
        int userIDSize = elementCountByUserID * sizeof(int);
        int tempSize = userIDSize + sizeof(int);
        currentID = userIDS[elementCountByUserID - 1] + 1;
        printf("id = %d \n", currentID);
        u->id = currentID; // ���û����и�ֵID

        temp = (int*)malloc(tempSize);
        if (!temp) {
            puts("�ڴ治�㣬�����˳�~");
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

// д���ļ�, ע���û�ʱʹ��
int writeUser(char* fileName, char* mode, PUSER u, int puCount) {
    FILE* pf = NULL;

    int userSize = sizeof(USER);

    mode == NULL ? (mode = "w") : mode;

    if (fopen_s(&pf, fileName, mode) || pf == NULL) {
        printf("�� %s �ļ�ʧ�ܣ�����������һ��~", fileName);
        exit(EXIT_FAILURE);
    }

    fwrite(u, userSize, puCount, pf);

    if (fclose(pf)) {
        return 0;
    }

    return 1;
}

// ���ļ��ж�ȡ�����ļ���Ϣ
int readUser(char* fileName, int elementSize, PUSER* pu) {
    FILE* pf = NULL;
    int elementCount = 0;
    if (fopen_s(&pf, fileName, "rb") || pf == NULL) {
        return 0;
    }

    if (fseek(pf, SEEK_SET, SEEK_END)) {
        return elementCount;
    }
    long countSize = ftell(pf); // �ܴ�С


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

// ���ļ��ж�ȡ���е�userID
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

// д���ļ�, ע���û�ʱʹ��
int writeUserID(char* fileName, int* pIDS, int elementCount) {
    FILE* pf = NULL;
    int bIsOpen = fopen_s(&pf, fileName, "wb");
    
    if (bIsOpen || pf == NULL) {
        printf("�� %s �ļ�ʧ�ܣ�����������һ��~", fileName);
        exit(EXIT_FAILURE);
    }

    fwrite(pIDS, sizeof(int), elementCount, pf);

    fclose(pf);

    return 1;
}

// չʾ�����û���Ϣ
void showUser() {
    PUSER pu = NULL;
    int cout = readUser(USERFILEINFO, sizeof(USER), &pu);
    puts("show ");
    for (int i = 0; i < cout; i++) {
        printf("%s, %s, %d \n", pu[i].userName, pu[i].password, pu[i].id);
    }
    puts("show Done");
    
}

// ����û��Ƿ��Ѿ����ڣ����ڵĻ��ͽ�ֹע��
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

// У���û���Ϣ�Ƿ���ȷ�� �û���������
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

// �޸�����
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

    puts("������ɵ�����: ");
    getStr(oldPassword, 50);
    int j = 5;
    while (strcmp(pu[i].password, oldPassword) != 0) {
        j--;
        printf("�����������������, �㻹��%d�λ���\n", j);
        if (j == 0) {
            puts("��������������˳�.");
            exit(EXIT_FAILURE);
        }

        getStr(oldPassword, 50);
        while (getchar() != '\n');
    }

    puts("�������µ�����: ");
    getStr(newPassword, 50);
    strcpy_s(pu[i].password, sizeof(pu[i].password), newPassword);

    if (writeUser(USERFILEINFO, "wb", pu, userCount)) {
        puts("�޸ĳɹ�~");
    } else {
        puts("�޸�ʧ��~");
    }
    showUserControlMenu(pu[i]);
    return 0;
}

// ��¼�����һ������
void showUserControlMenu(USER user) {
    putchar('\n');
    puts("****************************��ѡ�����,ֱ�ӻس��˳�����****************************");
    putchar('\n');
    printf("%c: �˳�����           %c: �鿴վ��������Ϣ"
           "           %c: �޸�����\n", EXIT, WEBSITEVIEW, MODIFYPASSWORD);
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
