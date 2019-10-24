#pragma once

// �û�ID�����ļ�����
#define USERFILEBYID "user_id"

// �û���Ϣ�����ļ�����
#define USERFILEINFO "user_info"

// վ��ID������ļ�
#define WEBIDFILE "web_id_file"

// վ����Ϣ�����ļ�����
#define WEBSITEINFO "website_info"



// վ����Ϣ
typedef struct _WEBSITE {
    // Ψһ��ʶ
    int id;

    // �����û���ID
    int userID;
    
    // վ���ַ
    char websiteAddress[50];

    // վ���û�����
    char websiteName[50];

    // վ������
    char websitePassword[50];
} WEBSITE, *PWEBSITE;

// �û���Ϣ
typedef struct _USER {
    // Ψһ��ʶ
    int id;

    // �û���
    char userName[50];

    // ����
    char password[50];
} USER, *PUSER;
//4 11 13 15