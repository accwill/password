#include <stdio.h>
#include <stdlib.h>
#include "untils.h"

// 从键盘获取字符串
void getStr(char* string, int size) {
    while (scanf_s("%s", string, size) != 1) {
        puts("输入有误，请重新输入：");
        while (getchar() != '\n');
    }
}

// 检查文件是否存在
int checkFileExist(char* fileName) {
    return 0;
}

// 退出程序
void exitProgram() {
    exit(EXIT_FAILURE);
}