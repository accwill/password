#include <stdio.h>
#include <stdlib.h>
#include "untils.h"

// �Ӽ��̻�ȡ�ַ���
void getStr(char* string, int size) {
    while (scanf_s("%s", string, size) != 1) {
        puts("�����������������룺");
        while (getchar() != '\n');
    }
}

// ����ļ��Ƿ����
int checkFileExist(char* fileName) {
    return 0;
}

// �˳�����
void exitProgram() {
    exit(EXIT_FAILURE);
}