#pragma once
#include "main.h"

// 新建一个站点
#define NEWWEBSITE 'N'
// 编辑一个站点
#define EDITWEBSITE 'E'
// 删除一个站点
#define DELWEBSITE 'D'
// 搜索一个站点
#define SEARCHWEBSITE 'S'
// 查看所有站点信息
#define VIEWALLWEBSITE 'V'

// 打印所有站点和展示菜单
void mainWebsite(USER user);

// 读取站点
int readWebsite(USER user, PWEBSITE* pw);

// 从键盘录入站点信息
WEBSITE inputWebsite(USER user);

// 显示站点
PWEBSITE reandAndShowWebsite(USER user, int* size);

// 生成站点ID
int generaterWebsiteID(PWEBSITE pw);

// 存储节点ID
void saveWebsiteIDToFile(int websiteID);

// 保存
void saveWebsiteToFile(USER user, WEBSITE website);

// 保存用户录入的站点信息
int saveWebsiteFromInput(USER user);

// 编辑一个站点
void editWebsite(USER user, PWEBSITE pw, int size);

// 删除一个站点
void deleteWebsite(USER user, PWEBSITE pw, int* size);

// 搜索一个站点
void searchWebsite(USER user, PWEBSITE pw, int size);

// 根据ID 搜索一条站点，并返回该站点的ID
int searchWebsiteById(PWEBSITE pw, int size, int id);

// 显示站点控制菜单
void showWebsiteMenu(USER user, PWEBSITE pw, int* size);

// 编辑之后保存文件
void saveWebsiteToFileFromModify(USER user, PWEBSITE pw, int size);

// 接收用户输入的ID
int inputWebsiteForID(PWEBSITE pw, int size);

// 打印站点信息
void showWebsite(PWEBSITE pw, int size);

// 加密
void encryptPassword(PWEBSITE pw, PWEBSITE* ppw, int size);

// 解密
void decEncryptPassword(PWEBSITE pw, int size);
