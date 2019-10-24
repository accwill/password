#pragma once
#include "main.h"

// �½�һ��վ��
#define NEWWEBSITE 'N'
// �༭һ��վ��
#define EDITWEBSITE 'E'
// ɾ��һ��վ��
#define DELWEBSITE 'D'
// ����һ��վ��
#define SEARCHWEBSITE 'S'
// �鿴����վ����Ϣ
#define VIEWALLWEBSITE 'V'

// ��ӡ����վ���չʾ�˵�
void mainWebsite(USER user);

// ��ȡվ��
int readWebsite(USER user, PWEBSITE* pw);

// �Ӽ���¼��վ����Ϣ
WEBSITE inputWebsite(USER user);

// ��ʾվ��
PWEBSITE reandAndShowWebsite(USER user, int* size);

// ����վ��ID
int generaterWebsiteID(PWEBSITE pw);

// �洢�ڵ�ID
void saveWebsiteIDToFile(int websiteID);

// ����
void saveWebsiteToFile(USER user, WEBSITE website);

// �����û�¼���վ����Ϣ
int saveWebsiteFromInput(USER user);

// �༭һ��վ��
void editWebsite(USER user, PWEBSITE pw, int size);

// ɾ��һ��վ��
void deleteWebsite(USER user, PWEBSITE pw, int* size);

// ����һ��վ��
void searchWebsite(USER user, PWEBSITE pw, int size);

// ����ID ����һ��վ�㣬�����ظ�վ���ID
int searchWebsiteById(PWEBSITE pw, int size, int id);

// ��ʾվ����Ʋ˵�
void showWebsiteMenu(USER user, PWEBSITE pw, int* size);

// �༭֮�󱣴��ļ�
void saveWebsiteToFileFromModify(USER user, PWEBSITE pw, int size);

// �����û������ID
int inputWebsiteForID(PWEBSITE pw, int size);

// ��ӡվ����Ϣ
void showWebsite(PWEBSITE pw, int size);

// ����
void encryptPassword(PWEBSITE pw, PWEBSITE* ppw, int size);

// ����
void decEncryptPassword(PWEBSITE pw, int size);
