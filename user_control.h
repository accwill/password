#pragma once
#include "main.h"


// ��¼��ʶ��
#define LOGIN 'L'

// �˳���ʶ��
#define EXIT 'Q'

// ע���ʶ��
#define REGISTER 'R'

// �޸������ʶ��
#define MODIFYPASSWORD 'M'

// �鿴վ�㼶����
#define WEBSITEVIEW 'W'


// ע���û�
int registerUser();

// ��¼
USER login();

// ���ɲ�д��USERID
void generaterUserID(PUSER u);

// ���ļ�д���û���Ϣ
int writeUser(char* fileName, char* mode, PUSER u, int puCount);

// ���ļ�д����ID
int writeUserID(char* fileName, int* pIDS, int elementCount);

// ���ļ���ȡ�����û�
int readUser(char* fileName, int elementSize, PUSER* pu);

// ���ļ���ȡ�����û�ID
int readUserID(char* fileName, int elementSize, int** pIDS);

// չʾ�û�
void showUser();

// ����û��Ƿ����
int checkUserIsExist(char* userName);

// У���û���Ϣ�Ƿ���ȷ�� �û���������
int checkUserInfoIsCorrect(char* userName, char* password, int* pID);

// չʾ�˵�
void showUserControlMenu(USER user);