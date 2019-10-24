#pragma once
#include "main.h"


// 登录标识符
#define LOGIN 'L'

// 退出标识符
#define EXIT 'Q'

// 注册标识符
#define REGISTER 'R'

// 修改密码标识符
#define MODIFYPASSWORD 'M'

// 查看站点级密码
#define WEBSITEVIEW 'W'


// 注册用户
int registerUser();

// 登录
USER login();

// 生成并写入USERID
void generaterUserID(PUSER u);

// 向文件写入用户信息
int writeUser(char* fileName, char* mode, PUSER u, int puCount);

// 向文件写入用ID
int writeUserID(char* fileName, int* pIDS, int elementCount);

// 向文件读取所有用户
int readUser(char* fileName, int elementSize, PUSER* pu);

// 向文件读取所有用户ID
int readUserID(char* fileName, int elementSize, int** pIDS);

// 展示用户
void showUser();

// 检查用户是否存在
int checkUserIsExist(char* userName);

// 校验用户信息是否正确， 用户名和密码
int checkUserInfoIsCorrect(char* userName, char* password, int* pID);

// 展示菜单
void showUserControlMenu(USER user);