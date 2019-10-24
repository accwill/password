#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "user_control.h"
#include "website_control.h"
#include "untils.h"

void mainWebsite(USER user) {
    system("cls");
    PWEBSITE pw;
    int pwSize;
    pw = reandAndShowWebsite(user, &pwSize);
    showWebsiteMenu(user, pw, &pwSize);
}

int saveWebsiteFromInput(USER user) {
    WEBSITE web = inputWebsite(user); // �û�����վ����Ϣ
    int websiteID = generaterWebsiteID(&web); // ����Ψһ��ʶ
    saveWebsiteIDToFile(websiteID); // ����Ψһ��ʶ���ļ�
    saveWebsiteToFile(user, web); // ����վ����Ϣ���ļ�
    return 0;
}

int readWebsite(USER user, PWEBSITE* pw) {
    FILE* pf = NULL;
    char fileName[50];
    strcpy_s(fileName, 50, WEBSITEINFO);
    strcat_s(fileName, 50, "_");
    strcat_s(fileName, 50, user.userName);
    if (fopen_s(&pf, fileName, "rb") != 0 || pf == NULL) {
        return 0;
    }

    fseek(pf, SEEK_SET, SEEK_END);

    long countSize = ftell(pf);
    int elementSize = sizeof(WEBSITE);
    int elementCount = countSize / elementSize;
    rewind(pf);

    *pw = (PWEBSITE)malloc(countSize + sizeof(WEBSITE));
    if (*pw == NULL) return 0;
    memset(*pw, 0, countSize + sizeof(WEBSITE));

    fread_s(*pw, countSize, elementSize, elementCount, pf);
    fclose(pf);
    decEncryptPassword(*pw, elementCount);
    return elementCount;
}

WEBSITE inputWebsite(USER user) {
    WEBSITE website;
    puts("������վ���ַ��");
    getStr(website.websiteAddress, 50);
    puts("������վ�����ƣ�");
    getStr(website.websiteName, 50);
    puts("���������룺");
    getStr(website.websitePassword, 50);
    generaterWebsiteID(&website);
    website.userID = user.id;
    return website;
}

void saveWebsiteToFile(USER user, WEBSITE website) {
    FILE* pf = NULL;
    PWEBSITE pw;
    char fileName[50];

    strcpy_s(fileName, 50, WEBSITEINFO);
    strcat_s(fileName, 50, "_");
    strcat_s(fileName, 50, user.userName);

    int elementCount = readWebsite(user, &pw);
    if (fopen_s(&pf, fileName, "wb") != 0 || pf == NULL) {
        printf("wb�� %s ʧ��", fileName);
        exitProgram();
    }
    if (elementCount && pw != NULL) {
        pw[elementCount] = website;
    } else {
        pw = &website;
    }

    PWEBSITE pTemp;
    encryptPassword(pw, &pTemp, elementCount + 1);

    fwrite(pTemp, sizeof(WEBSITE), elementCount + 1, pf);
    fclose(pf);
    free(pTemp);
}

int generaterWebsiteID(PWEBSITE pw) {
    int websiteID = 0;
    FILE* pf = NULL;
    if (fopen_s(&pf, WEBIDFILE, "rb") != 0 || pf == NULL) {
        websiteID = 1;
        pw->id = websiteID;
        return websiteID;
    }

    fseek(pf, SEEK_SET, SEEK_END);

    long size = ftell(pf);
    rewind(pf);
    
    if (fread_s(&websiteID, sizeof(int), sizeof(int), 1, pf) == 0) {
        websiteID = 1;
        return websiteID;
    }

    pw->id = ++websiteID; // ��ֵ

    fclose(pf);
    return websiteID;
}

void saveWebsiteIDToFile(int websiteID) {
    FILE* pf = NULL;
    if (fopen_s(&pf, WEBIDFILE, "wb") != 0 || pf == NULL) {
        printf("wb�� %s ʧ�ܣ� ��������ĵ���~", WEBIDFILE);
        exit(EXIT_FAILURE);
    }

    if (fwrite(&websiteID, sizeof(int), 1, pf) == 0) {
        fclose(pf);
        printf("wbд�� %s ʧ�ܣ� ��������ĵ���~", WEBIDFILE);
        exit(EXIT_FAILURE);
    }

    fclose(pf);
}

PWEBSITE reandAndShowWebsite(USER user, int* size) {
    PWEBSITE pw;
    int elementCount = readWebsite(user, &pw);
    *size = elementCount;
    showWebsite(pw, *size);
    return pw;
}

void editWebsite(USER user, PWEBSITE pw, int size) {
    int resultIndex = inputWebsiteForID(pw, size);
    puts("�������µ�����~");
    while (scanf_s("%s", pw[resultIndex].websitePassword, 50) != 1) {
        puts("������������������~");
        while (getchar() != '\n');
    }
    saveWebsiteToFileFromModify(user, pw, size);
    puts("��ϲ�����޸ĳɹ�~");
}

void deleteWebsite(USER user, PWEBSITE pw, int* size) {
    if (size == NULL) return;
    int id = inputWebsiteForID(pw, *size);
    int resultIndex = searchWebsiteById(pw, *size, id);
    // ��װɾ����
    for (int i = 0; i < *size; i++) {
        int j = i + 1;
        if (i >= resultIndex && j < *size) {
            pw[i] = pw[j];
        }
    }

    *size = *size - 1;
    saveWebsiteToFileFromModify(user, pw, *size);
}

void searchWebsite(USER user, PWEBSITE pw, int size) {
    char websiteAddress[50] = { 0 };
    puts("������վ���ַ~");
    while (scanf_s("%s", websiteAddress, 50) != 1) {
        puts("������������������~~~");
        while (getchar() != '\n');
    }
    putchar('\n');
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(pw[i].websiteAddress, websiteAddress) == 0) {
            count++;
        }
    }
    printf("һ���ѵ�%d�����~\n", count);
    if (count == 0) {
        return;
    }
    PWEBSITE pw1 = (PWEBSITE)malloc(sizeof(WEBSITE) * count);
    if (pw1 == NULL) {
        return;
    }
    memset(pw1, 0, sizeof(WEBSITE) * count);

    int j = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(pw[i].websiteAddress, websiteAddress) == 0) {
            pw1[j++] = pw[i];
        }
    }

    showWebsite(pw1, count);
}

int searchWebsiteById(PWEBSITE pw, int size, int id) {
    for (int i = 0; i < size; i++) {
        if (pw[i].id == id) {
            return i;
        }
    }
    return -1;
}

void saveWebsiteToFileFromModify(USER user, PWEBSITE pw, int size) {
    FILE* pf = NULL;
    char fileName[50];
    strcpy_s(fileName, 50, WEBSITEINFO);
    strcat_s(fileName, 50, "_");
    strcat_s(fileName, 50, user.userName);

    if (fopen_s(&pf, fileName, "wb") != 0 || pf == NULL) {
        printf("wb�� %s ʧ��\n", fileName);
        puts("�ļ��޸�ʧ��~");
        exitProgram();
    }

    PWEBSITE pTemp;
    encryptPassword(pw, &pTemp, size);

    fwrite(pTemp, sizeof(WEBSITE), size, pf);
    fclose(pf);
    free(pTemp);
}

int inputWebsiteForID(PWEBSITE pw, int size) {
    int id = 0xffff;
    int resultIndex = 0xffff;
    puts("������ID�����磺1");

    while ((resultIndex = searchWebsiteById(pw, size, id)) == -1 || id == 0xffff) {
        if (resultIndex == -1 && id != 0xffff) {
            puts("��Ǹ ID δ�ҵ�������������");
        }
        while (scanf_s("%d", &id) != 1) {
            puts("����������������������~");
            while (getchar() != '\n');
        }
    }

    return resultIndex;
}

void showWebsite(PWEBSITE pw, int size) {
    printf("  ID  USERID      WEBSITEADDRESS               WEBSITENAME            WEBSITEPASSWORD\n");
    printf("---------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%3d%5d%24s%22s%32s",
            pw[i].id, pw[i].userID, pw[i].websiteAddress, pw[i].websiteName, pw[i].websitePassword);
        putchar('\n');
    }
}

void showWebsiteMenu(USER user, PWEBSITE pw, int *size) {
    putchar('\n');
    puts("****************************��ѡ�����,ֱ�ӻس��˳�����****************************");
    putchar('\n');
    printf("%c���½�           %c���༭           "
        "%c��ɾ��           %c������           %c���鿴����",
        NEWWEBSITE, EDITWEBSITE, DELWEBSITE, SEARCHWEBSITE, VIEWALLWEBSITE);
    putchar('\n');
    puts("***********************************************************************************");
    char action;
    while (getchar() != '\n');
    scanf_s("%c", &action, 1);
    action = toupper(action);
    switch (action) {
        case NEWWEBSITE:
            saveWebsiteFromInput(user);
            mainWebsite(user);
            break;
        case EDITWEBSITE:
            editWebsite(user, pw, *size);
            mainWebsite(user);
            break;
        case DELWEBSITE:
            deleteWebsite(user, pw, size);
            mainWebsite(user);
            break;
        case VIEWALLWEBSITE:
            mainWebsite(user);
        case SEARCHWEBSITE:
            searchWebsite(user, pw, *size);
            showWebsiteMenu(user, pw, size);
            break;
        default:
            exitProgram();
    }
}

void encryptPassword(PWEBSITE pw, PWEBSITE* ppw, int size) {
    int countSize = sizeof(WEBSITE) * size;
    *ppw = (PWEBSITE)malloc(countSize);
    memcpy_s(*ppw, countSize, pw, countSize);


    if (*ppw == NULL) {
        puts("�ڱ����ļ�ʱ�������ڴ�ʧ��~������������һ��~");
        return;
    };

    PWEBSITE pw1 = *ppw;

    for (int j = 0; j < size; j++) {
        for (unsigned int i = 0; i < strlen(pw1[j].websitePassword); i++) {
            pw1[j].websitePassword[i] ^= 'A';
        }
    }
}

void decEncryptPassword(PWEBSITE pw, int size) {
    for (int j = 0; j < size; j++) {
        for (unsigned int i = 0; i < strlen(pw[j].websitePassword); i++) {
            pw[j].websitePassword[i] ^= 'A';
        }
    }
}
