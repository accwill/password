#pragma once

// 用户ID保存文件名称
#define USERFILEBYID "user_id"

// 用户信息保存文件名称
#define USERFILEINFO "user_info"

// 站点ID保存的文件
#define WEBIDFILE "web_id_file"

// 站点信息保存文件名称
#define WEBSITEINFO "website_info"



// 站点信息
typedef struct _WEBSITE {
    // 唯一标识
    int id;

    // 关联用户的ID
    int userID;
    
    // 站点地址
    char websiteAddress[50];

    // 站点用户名称
    char websiteName[50];

    // 站点密码
    char websitePassword[50];
} WEBSITE, *PWEBSITE;

// 用户信息
typedef struct _USER {
    // 唯一标识
    int id;

    // 用户名
    char userName[50];

    // 密码
    char password[50];
} USER, *PUSER;
//4 11 13 15