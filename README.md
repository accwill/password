# 这是一个密码本项目

## 主要功能
1. 用户注册
    - 是否已经注册校验
2. 登录
3. 修改密码
4. 对密码本的增删改查

## 目录
```shell
│  main.c                         # 程序入口
│  main.h                         # main对应的头文件
│  README.md                      # 项目说明文件
│  untils.c                       # 工具代码
│  untils.h                       # 对应工具代码的头文件
│  user_control.c                 # 用户的操作逻辑（注册，删除，修改，登录）
│  user_control.h                 # 对应的头文件
│  website_control.c              # 密码本增删改查（文件操作）
│  website_control.h              # 对应密码本头文件
```


## 结构体说明

> 存储的内容都是保存在文件内的

```c
// 这个是站点信息文件，站点跟密码的关系是一对一
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
```

## 总结

> 花了2天完成的小DEMO，前期写用户那一块操作的时候思路比较混乱，所以抽象的不是很开，看着比较杂乱；写到密码本字段的增删改查之后，明显抽象的更加清晰；

**C语言初期的学习告一段落了，C写着有太多的问题，感觉整个程序都很脆弱，别人很容易就可K掉；相较于之前学习的`JS`来说`C`写起来麻烦且不稳定；写出来的C程序有一种哪里都是漏洞的感觉，这种感觉很不幸福。**

*没抽象为MVC，小白代码，感觉这样写快自闭了。。*

*当然C还是C。。。。。。自己呢依然是菜鸡。哈哈哈～～～～～～*