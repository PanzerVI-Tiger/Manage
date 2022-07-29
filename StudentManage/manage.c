#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "account_internal.h"
#include "manage.h"

#define TypesPackRBTree() 2, ProductID,ProductMapped, AccountID,PAccountInternal
#include "RBTree.h"
#define TypesPackVector() 3, PProduct, PAccountNode, Product
#include "Vector.h"


#define buffSize 32

static bool checkIsEffectNumber(const char* str, size_t min, size_t max);

static Account account  = NULL;
static bool    isChange = false;

void mainPanel()
{
    FILE* pf = fopen("manage.bin", "r+");
    if (pf == NULL) {
        makeAccountsFile("manage.bin");
        pf = fopen("manage.bin", "r+");
    }
    
    loadAccounts(pf);
    fclose(pf);
    
    while (true) {
        fputs("====================================\n"
              "|       欢迎来到电商管理系统       |\n"
              "====================================\n"
              "|                                  |\n"
              "|           1   : 登录             |\n"
              "|           2   : 注册             |\n"
              "|           其他: 退出             |\n"
              "|                                  |\n"
              "====================================\n"
              "input>>> ", stdout);
        
        char buff[buffSize] = { 0, };
        gets_s(buff, buffSize);
        
        system("cls");
        
        if (!checkIsEffectNumber(buff, 1, 1)) {
            goto clear;
        }
        
        switch (atoi(buff)) {
        case 1:
            loginPanel();
            continue;

        case 2:
            registerPanel();
            continue;

        default:
            goto clear;
        }
    }

    // write file if data has change
    clear:
    if (isChange) {
        pf = fopen("manage.bin", "w");
        storeAccounts(pf);
        fclose(pf);
    }
    freeAccounts();
}

static bool checkIsEffectNumber(const char* str, size_t min, size_t max)
{
    size_t len = strlen(str);
    if (len > max || len < min) {
        return false;
    }
    
    while (*str != '\0') {
        if (*str < '0' || *str > '9') {
            return false;
        }
        ++str;
    }
    return true;
}

void loginPanel(void)
{
    fputs("====================================\n"
          "|             登录界面             |\n" 
          "====================================\n"
          "请输入账号:\n"
          "input>>> " , stdout);
    char buff[buffSize] = { 0, };
    gets_s(buff, buffSize);

    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("无效的账号, 请重新输入(账号为纯数字, 且长度小于\n"
              "10位, 大于5位):\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int id = atoi(buff);
    
    fputs("请输入密码:\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("无效的密码, 请重新输入(密码为纯数字, 且长度小于\n"
              "10位, 大于5位):\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int password = atoi(buff);
    
    account            = getAccount();
    LoginStatus status = account->vptr->login(id, password);
    
    switch (status) {
    case accountNotFound:
        fputs("账号不存在! 按下回车继续:\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
        
        break;
        
    case wrongPassword:
        fputs("密码错误! 按下回车继续:\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);

        break;
        
    case loginSuccess:
        system("cls");
        switch (account->vptr->accountType()) {
        case superAdminAccount:
            superAdminPanel();
            break;
            
        case adminAccount:
            adminPanel();
            break;

        case userAccount:
            userPanel();
            break;
        }
    }
    system("cls");
}

void changePasswordPanel(void)
{
    fputs("====================================\n"
          "|           修改密码界面           |\n" 
          "====================================\n"
          "请输入原密码:\n"
          "input>>> ", stdout);
    char buff[buffSize] = { 0, };
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("无效的密码, 请重新输入(密码为纯数字, 且长度小于\n"
              "10位, 大于5位):\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int password = atoi(buff);
    
    fputs("请输入新密码:\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("无效的密码, 请重新输入(密码为纯数字, 且长度小于\n"
              "10位, 大于5位):\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int newPassword = atoi(buff);
    
    if (account->vptr->changePassword(password, newPassword)) {
        isChange = true;
        fputs("密码修改成功! 按下回车继续:\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    } else {
        fputs("密码修改失败! 按下回车继续:\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    system("cls");
}

void registerPanel(void)
{
    fputs("====================================\n"
          "|             注册界面             |\n" 
          "====================================\n"
          "请输入账号(账号为纯数字, 且长度小于\n"
          "10位, 大于5位):\n"
          "input>>> ", stdout);
    char buff[buffSize] = { 0, };
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("无效的账号, 请重新输入:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int id = atoi(buff);
    
    fputs("请输入密码(密码为纯数字, 且长度小于10位, 大于5位):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("无效的密码, 请重新输入:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int password = atoi(buff);
    
    fputs("请输入用户名(用户名必须小于10个字符, 两个汉字算一个字):\n"
          "input>>> ", stdout);
    char* name[buffSize] = { 0, };
    gets_s(name, buffSize);
    while (strlen(name) > 10) {
        fputs("用户名长度超过10个字符, 请重新输入:\n"
              "input>>> ", stdout);
        gets_s(name, buffSize);
    }

    fputs("请输入性别(1为男, 其他女):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    bool isMale = atoi(buff) == 1;

    fputs("请输入电话号码(少于12位):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 0, 11)) {
        fputs("无效的电话号码, 请重新输入:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    long long phone = atoll(buff);
    
    
    fputs("是否花费100元成为VIP(1是, 其他否):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    bool isVip = atoi(buff) == 1;

    account = getAccount();
    if (account->vptr->registerNewUser(id, password, name, isMale, phone, isVip)) {
        isChange = true;
        system("cls");
        loginPanel();
    } else {
        fputs("注册失败! 按下回车继续:\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    system("cls");
}

void userPanel(void)
{
    while (true) {
        UserInternal* user = account->vptr->toUser();
        printf("====================================\n"
               "|             用户界面             |\n"
               "------------------------------------\n"
               "|       欢迎回来, %-10s!      |\n"
               "====================================\n"
               "|          1:    在线购物          |\n"
               "|          2:    钱包管理          |\n"
               "|          3:    修改密码          |\n"
               "|          其他: 返回              |\n"
               "====================================\n"
               "input>>> ", user->name);
    
        char buff[buffSize] = { 0, };
        gets_s(buff, buffSize);
        if (!checkIsEffectNumber(buff, 1, 1)) {
            system("cls");
            return;
        }
        switch (atoi(buff)) {
        case 1:
            system("cls");
            shoppingPanel();
            break;

        case 2:
            system("cls");
            walletPanel();
            break;

        case 3:
            system("cls");
            changePasswordPanel();
            break;
        
        default:
            system("cls");
            return;
        }
    }
    system("cls");
}

void shoppingPanel(void)
{
    while (true) {
        fputs("====================================\n"
              "|             在线购物             |\n"
              "====================================\n"
              "|          1:    查看商品          |\n"
              "|          2:    购买商品          |\n"
              "|          3:    查看物流          |\n"
              "|          其他: 返回              |\n"
              "====================================\n"
              "input>>> ", stdout);
        char buff[buffSize] = { 0, };
        gets_s(buff, buffSize);
        if (!checkIsEffectNumber(buff, 1, 1)) {
            system("cls");
            return;
        }
    
        switch (atoi(buff)) {
        case 1:
            printProducts();
            break;
        
        case 2:
            buyProduct();
            break;

        case 3:
            printLogistics();
            break;

        default:
            system("cls");
            return;
        }
    }
    system("cls");
}

void printLogistics(void)
{
    UserInternal* user = account->vptr->toUser();
    fputs("---- --------------- ------ --------------- ------- ------- ----- ----- ----\n"
          "索引    商品名称    商品编号   发货地址      价格    进价   折扣  数量  类型\n"
          "---- --------------- ------ --------------- ------- ------- ----- ----- ----\n"
          , stdout);
    Vector(Product)* products = user->products;
    for (size_t i = 0, j = sizeVector(products); i < j; ++i) {
        PProduct product = atVector(products, i);
        char price[8];
        sprintf(price, "%-04.2f", product->mapped.price);
        char cost[8];
        sprintf(cost,  "%-04.2f", product->mapped.cost);
        char discount[6];
        sprintf(discount, "%-0.3f", product->mapped.discount);
        printf("%-4zd %-15s %-06d %-15s %-7s %-7s %-5s %-05d %-04d\n",
            i,                              product->mapped.name, product->key, 
            product->mapped.shipAddress,    price,                cost, 
            discount,                       product->mapped.size, product->mapped.type
        );
    }
    fputs("---- --------------- ------ --------------- ------- ------- ----- ----- ----\n"
          "按下回车继续:\n"
          ">>> ", stdout);
    char buff[buffSize];
    gets_s(buff, buffSize);
}

void buyProduct(void)
{
    fputs("请输入商品编号:\n"
          "input>>> ", stdout);
    char buff[buffSize] = { 0, };
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 6)) {
        fputs("无效的商品编号, 请重新输入:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    
    int32_t       productId = atoi(buff);

    fputs("请输入购买数量:\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 5)) {
        fputs("无效的购买数量, 请重新输入:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    uint32_t      size      = atoi(buff);
    UserInternal* user      = account->vptr->toUser();
    int           status    = user->vptr->buyProduct(productId, size);
    if (status == 0) {
        fputs("商品不存在!\n"
              "按下回车继续>>> ", stdout);
        gets_s(buff, buffSize); 
        return;
    }
    
    if (status == -2) {
        fputs("库存不足!\n"
              "按下回车继续>>> ", stdout);
        gets_s(buff, buffSize); 
        return;
    }
    
    while (status == -1) {
        fputs("余额不足, 是否充值?(1: 是, 其他: 否)\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
        if (!checkIsEffectNumber(buff, 1, 1)) {
            return;
        }
        if (atoi(buff) == 1) {
            walletPanel();
        }
        status = user->vptr->buyProduct(productId, size);
    }   
    isChange = true;
    fputs("购买成功!\n"
          "按下回车继续>>> ", stdout);
    gets_s(buff, buffSize);
}

void walletPanel(void)
{
    UserInternal* user = account->vptr->toUser();
    while (true) {
        fputs("====================================\n"
              "|             钱包管理             |\n"
              "====================================\n"
              "|          1:    查看余额          |\n"
              "|          2:    充值              |\n"
              "|          其他: 返回              |\n"
              "====================================\n"
              "input>>> ", stdout);
        char buff[buffSize] = { 0, };
        gets_s(buff, buffSize);
        
        system("cls");
        switch (atoi(buff)) {
        case 1: {
            double money = user->vptr->getMoney();
            sprintf(buff, "%.2f", money);
            printf("====================================\n"
                   "|             余额查看             |\n"
                   "====================================\n"
                   "|          余额: %-10s        |\n"
                   "====================================\n"
                   "按下回车继续>>> ", buff);
            }
              gets_s(buff, buffSize);
            
            break;
        
        case 2:
            fputs("请输入充值金额:\n"
                  "input>>> ", stdout);
            gets_s(buff, buffSize);
            double money = atof(buff);
            user->vptr->topUp(money);
            isChange = true;
            fputs("充值成功! 按下回车继续:\n"
                  ">>> ", stdout);
            gets_s(buff, buffSize);
            
            break;

        default:
            system("cls");
            return;
        }
        system("cls");
    }
}

void adminPanel(void)
{
    while (true) {
        fputs("====================================\n"
              "|             管理员面板             |\n"
              "====================================\n"
              "|          1:    管理商品          |\n"
              "|          2:    管理用户          |\n"
              "|          3:    修改密码          |\n"
              "|          其他: 查看用户          |\n"
              "====================================\n"
              "input>>> ", stdout);
        char buff[buffSize];
        gets_s(buff, buffSize);
        if (!checkIsEffectNumber(buff, 1, 1)) {
            system("cls");
            return;
        }
        switch (atoi(buff)) {
        case 1:
            productManagePanel();
            break;

        case 2:
            accountManagePanel();
            break;

        case 3:
            changePasswordPanel();
            break;

        default:
            system("cls");
            return;
        }
    }
}

void superAdminPanel(void)
{
    while (true) {
        fputs("====================================\n"
              "|          超级管理员界面          |\n"
              "------------------------------------\n"
              "|       欢迎回来, 超级管理员!      |\n"
              "====================================\n"
              "|          1:    管理账号          |\n"
              "|          2:    管理商品          |\n"
              "|          3:    修改密码          |\n"
              "|          其他: 返回              |\n"
              "====================================\n"
              "input>>> ", stdout);
    
        char buff[buffSize];
        gets_s(buff, buffSize);
        if (!checkIsEffectNumber(buff, 1, 1)) {
            system("cls");
            return;
        }
    
        system("cls");

        switch (atoi(buff)) {
        case 1:
            accountManagePanel();
            break;

        case 2:
            productManagePanel();
            break;

        case 3:
            changePasswordPanel();
            break;
    
        default:
            system("cls");
            return;
        }
    }
    system("cls");
}

void accountManagePanel(void)
{
    AccountType type = account->vptr->accountType();
    while (true) {
        puts("====================================\n"
              "|             账号管理             |\n"
              "====================================\n"
              "|       1:    查看账号信息         |\n"
              "|       2:    删除账号             |");
            
        if (type == superAdminAccount) {
            puts(
              "|       3:    添加管理员账号       |");
        }
        fputs("|       其他: 返回上一级           |\n"
              "====================================\n"
              "input>>> ", stdout);
        char buff[buffSize];
        gets_s(buff, buffSize);
        if (!checkIsEffectNumber(buff, 1, 1)) {
            system("cls");
            return;
        }
        switch (atoi(buff)) {
        case 1:
            printAccounts();
            break;

        case 3:
            if (type != superAdminAccount) {
                system("cls");
                return;
            }
            addAdminPanel();
            break;

        case 2:
            removeAccountPanel();
            break;

        default:
            system("cls");
            return;
        }
    }
    system("cls");
}

void addAdminPanel(void)
{
    fputs("====================================\n"
          "|          管理员创建界面          |\n" 
          "====================================\n"
          "请输入账号(账号为纯数字, 且长度小于\n"
          "10位, 大于5位):\n"
          "input>>> ", stdout);
    char buff[buffSize] = { 0, };
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("无效的账号, 请重新输入:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int id = atoi(buff);
    
    fputs("请输入密码(密码为纯数字, 且长度小于10位, 大于5位):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("无效的密码, 请重新输入:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int password = atoi(buff);
    
    fputs("请输入用户名(用户名必须小于10个字符, 两个汉字算一个字):\n"
          "input>>> ", stdout);
    char* name[buffSize] = { 0, };
    gets_s(name, buffSize);
    while (strlen(name) > 10) {
        fputs("用户名长度超过10个字符, 请重新输入:\n"
              "input>>> ", stdout);
        gets_s(name, buffSize);
    }

    fputs("请输入性别(1为男, 其他女):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    bool isMale = atoi(buff) == 1;

    fputs("请输入电话号码(少于12位):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 0, 11)) {
        fputs("无效的电话号码, 请重新输入:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    long long phone = atoll(buff);

    account = getAccount();
    SuperAdmin pSuperAdmin = account->vptr->toSuperAdmin();
    if (pSuperAdmin->vptr->addAdmin(id, password, name, isMale, phone)) {
        isChange = true;
        puts("添加成功!");
    } else {
        puts("注册失败!:");
        gets_s(buff, buffSize);
    }
    fputs("按下回车继续>>> ", stdout);
    gets_s(buff, buffSize);
}

void removeAccountPanel(void)
{
    fputs("====================================\n"
          "|          账号删除界面          |\n" 
          "====================================\n"
          "请输入账号(账号为纯数字, 且长度小于\n"
          "10位, 大于5位):\n"
          "input>>> ", stdout);
    char buff[buffSize] = { 0, };
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("无效的账号, 请重新输入:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int id = atoi(buff);
    
    account = getAccount();
    SuperAdmin pSuperAdmin = account->vptr->toSuperAdmin();
    if (pSuperAdmin->vptr->removeAccount(id)) {
        isChange = true;
        puts("删除成功!\n");
    } else {
        puts("删除失败!:\n");
        gets_s(buff, buffSize);
    }
}

void printAccounts(void)
{
    fputs("=============================================\n"
          "|                 账号列表                  |\n"
          "=============================================\n"
          "---------- --------- ------ -- ----------- --\n"
          "   姓名      账号     类型 性别 电话号码  VIP\n"
          "---------- --------- ------ -- ----------- --\n"
          , stdout);
    Vector(PAccountNode)* accounts = account->vptr->toAdmin()->vptr->getAccounts();
    for (int i = 0, j = sizeVector(accounts); i < j; ++i) {
        PAccountNode accountNode = *atVector(accounts, i);
        switch (accountNode->mapped->type) {
        case userAccount: {
                UserInternal* user = (UserInternal*)accountNode->mapped;
                printf("%-10s %-9d 用户   %-2s %-11lld %-2s\n",
                    user->name, accountNode->key, user->isMale ? "男" : "女", 
                    user->phoneNumber, user->isVIP ? "是" : "否");
            }
            break;
            
        case adminAccount: {
                AdminInternal* admin = (AdminInternal*)accountNode->mapped;
                printf("%-10s %-9d 管理员 %-2s %-11lld NA\n",
                    admin->name, accountNode->key, admin->isMale ? "男" : "女", 
                    admin->phoneNumber);
            }
        }
        
    }
    destroyVector(accounts);
    char buff[buffSize];
    fputs("---------- --------- ------ -- ----------- --\n"
          "按回车继续>>> ", stdout);
    gets_s(buff, buffSize);
}

void productManagePanel(void)
{
    while (true) {
        fputs("====================================\n"
              "|           商品管理界面           |\n"
              "====================================\n"
              "|          1:    添加商品          |\n"
              "|          2:    删除商品          |\n"
              "|          3:    修改商品          |\n"
              "|          4:    查询商品          |\n"
              "|          5:    列出商品          |\n"
              "|          其他: 返回              |\n"
              "====================================\n"
              "input>>> ", stdout);
        char buff[buffSize];
        gets_s(buff, buffSize);
        if (!checkIsEffectNumber(buff, 1, 1)) {
            system("cls");
            return;
        }
        switch (atoi(buff)) {
        case 1:
            addProductPanel();
            break;
        case 2:
            removeProductPanel();
            break;
        case 3:
            changeProductPanel();
            break;
        case 4:
            findProductPanel();
            break;
        case 5:
            printProducts();
            break;
        
        default:
            system("cls");
            return;
        }
    }
    system("cls");
}

void printProducts(void)
{
    fputs("=======================================================================\n"
          "|                              商品列表                               |\n"
          "=======================================================================\n", stdout);
    bool isSort            = false; 
    bool reverse           = false;
    SortWayProduct sortWay = sortByID;
    char buff[buffSize];
    fputs("请输入排序方式(1:名称, 2:编号, 3:价格, 4:折扣, 5:库存, 其他: 不排序):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    sortWay = atoi(buff);
    if (checkIsEffectNumber(buff, 1, 1) && sortWay <= 5 && sortWay >= 1) {
        isSort = true;
        fputs("是否逆向排序(1: 是, 其他: 否):\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
        reverse = atoi(buff) == 1 && checkIsEffectNumber(buff, 1, 1);
    }
    
    fputs("--------------- ------ --------------- ------- ------- ----- ----- ----\n"
          "   商品名称    商品编号   发货地址      价格    进价   折扣  库存  类型\n"
          "--------------- ------ --------------- ------- ------- ----- ----- ----\n"
          , stdout);
    Vector(PProduct)* products = account->vptr->getProducts(isSort, reverse, sortWay);
    for (size_t i = 0, j = sizeVector(products); i < j; ++i) {
        PProduct product = *atVector(products, i);
        char price[8];
        sprintf(price, "%-04.2f", product->mapped.price);
        char cost[8];
        sprintf(cost, "%-04.2f", product->mapped.cost);
        char discount[6];
        sprintf(discount, "%-0.3f", product->mapped.discount);
        printf("%-15s %-06d %-15s %-7s %-7s %-5s %-05d %-04d\n",
            product->mapped.name,  product->key,         product->mapped.shipAddress,
            price,                 cost,                 discount,
            product->mapped.size,  product->mapped.type
        );
    }
    destroyVector(products);
    fputs("--------------- ------ --------------- ------- ------- ----- ----- ----\n"
          "按下回车继续>>> ", stdout);
    gets_s(buff, buffSize);
}

void addProductPanel(void)
{
    fputs("====================================\n"
          "|           添加商品界面           |\n"
          "====================================\n"
          "请输入商品名称(不超过15个字符)\n"
          "input>>> ", stdout);
    char buff[buffSize];
    Product product;
    
    gets_s(buff, buffSize);
    while (strlen(buff) > 15) {
        fputs("商品名称过长, 请重新输入\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    strcpy(product.mapped.name, buff);
    
    fputs("请输入商品编号(数字, 不超过6个字符)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 6)) {
        fputs("商品编号过长或者输入了非数字字符, 请重新输入\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    *((ProductID*)(&product.key)) = atoi(buff);

    fputs("请输入商品发货地址(不超过15个字符)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (strlen(buff) > 15) {
        fputs("商品发货地址过长, 请重新输入\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }   
    strcpy(product.mapped.shipAddress, buff);

    fputs("请输入商品价格(不超过6位有效数字)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    product.mapped.price = atof(buff);

    fputs("请输入商品进价(不超过6位有效数字)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    product.mapped.cost = atof(buff);

    fputs("请输入商品折扣(小于1, 不超过3位有效数字)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    product.mapped.discount = atof(buff);
    while (product.mapped.discount > 1) {
        fputs("折扣大于一, 请重新输入\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
        product.mapped.discount = atof(buff);
    }
    
    fputs("请输入商品库存(不超过5位数字)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 5)) {
        fputs("输入数字过大或者输入了非数字字符, 请重新输入\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    product.mapped.size = atoi(buff);

    fputs("请输入商品类型(不超过4位数字)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 4)) {
        fputs("输入数字过大或者输入了非数字字符, 请重新输入\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    product.mapped.type = atoi(buff);

    SuperAdmin superAdmin = account->vptr->toSuperAdmin();
    if (superAdmin->vptr->addProduct(&product)) {
        isChange = true;
        fputs("添加商品成功\n"
              "按下回车继续>>> ", stdout);
        gets_s(buff, buffSize);
    } else {
        fputs("添加商品失败\n"
              "按下回车继续>>> ", stdout);
        gets_s(buff, buffSize);
    }
}

void removeProductPanel(void)
{
    fputs("====================================\n"
          "|           删除商品界面           |\n"
          "====================================\n"
          "请输入商品编号(数字, 不超过6个字符)\n"
          "input>>> ", stdout);
    char buff[buffSize];
    ProductID productID;
    
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 6)) {
        fputs("商品编号过长或者输入了非数字字符, 请重新输入\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    productID = atoi(buff);
    
    SuperAdmin superAdmin = account->vptr->toSuperAdmin();
    if (superAdmin->vptr->removeProduct(productID)) {
        isChange = true;
        fputs("删除商品成功\n"
              "按下回车继续>>> ", stdout);
        gets_s(buff, buffSize);
    } else {
        fputs("删除商品失败\n"
              "按下回车继续>>> ", stdout);
        gets_s(buff, buffSize);
    }
}

void changeProductPanel(void)
{
    fputs("====================================\n"
          "|           修改商品界面           |\n"
          "====================================\n"
          "请输入商品编号(数字, 不超过6个字符)\n"
          "input>>> ", stdout);
    char buff[buffSize];
    ProductID productID;
    
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 6)) {
        fputs("商品编号过长或者输入了非数字字符, 请重新输入\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    productID = atoi(buff);
    
    PProduct product = account->vptr->toSuperAdmin()->vptr->findProduct(productID);
    if (product == NULL) {
        fputs("没有找到该商品\n"
              "按下回车继续>>> ", stdout);
        gets_s(buff, buffSize);
        return;
    }
    
    isChange = true;
    fputs("请输入商品名称(不超过15个字符)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (strlen(buff) > 15) {
        fputs("商品名称过长, 请重新输入\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    strcpy(product->mapped.name, buff);

    fputs("请输入商品发货地址(不超过15个字符)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (strlen(buff) > 15) {
        fputs("商品发货地址过长, 请重新输入\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }   
    strcpy(product->mapped.shipAddress, buff);

    fputs("请输入商品价格(不超过6位有效数字)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    product->mapped.price = atof(buff);

    fputs("请输入商品进价(不超过6位有效数字)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    product->mapped.cost = atof(buff);

    fputs("请输入商品折扣(小于1, 不超过3位有效数字)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    product->mapped.discount = atof(buff);
    while (product->mapped.discount > 1) {
        fputs("折扣大于一, 请重新输入\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
        product->mapped.discount = atof(buff);
    }
    
    fputs("请输入商品库存(不超过5位数字)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 5)) {
        fputs("输入数字过大或者输入了非数字字符, 请重新输入\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    product->mapped.size = atoi(buff);

    fputs("请输入商品类型(不超过4位数字)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 4)) {
        fputs("输入数字过大或者输入了非数字字符, 请重新输入\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    product->mapped.type = atoi(buff);
    
    fputs("按下回车继续:\n"
          ">>> ", stdout);
    gets_s(buff, buffSize);
}

void findProductPanel(void)
{
    fputs("====================================\n"
          "|           查找商品界面           |\n"
          "====================================\n"
          "请输入商品编号(数字, 不超过6个字符)\n"
          "input>>> ", stdout);
    char buff[buffSize];
    ProductID productID;
    
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 6)) {
        fputs("商品编号过长或者输入了非数字字符, 请重新输入\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    productID = atoi(buff);
    
    PProduct product = account->vptr->toSuperAdmin()->vptr->findProduct(productID);
    if (product == NULL) {
        fputs("没有找到该商品\n"
              "按下回车继续>>> ", stdout);
        gets_s(buff, buffSize);
        return;
    }
    fputs("--------------- ------ --------------- ------- ------- ----- ----- ----\n"
          "   商品名称    商品编号   发货地址      价格    进价   折扣  库存  类型\n"
          "--------------- ------ --------------- ------- ------- ----- ----- ----\n"
          , stdout);
    char price[8];
    sprintf(price, "%-04.2f", product->mapped.price);
    char cost[8];
    sprintf(cost, "%-04.2f", product->mapped.cost);
    char discount[6];
    sprintf(discount, "%-0.3f", product->mapped.discount);
    printf("%-15s %-06d %-15s %-7s %-7s %-5s %-05d %-04d\n",
        product->mapped.name, product->key,         product->mapped.shipAddress,
        price,                cost,                 discount,
        product->mapped.size, product->mapped.type
    );
    
    fputs("--------------- ------ --------------- ------- ------- ----- ----- ----\n"
          "按下回车继续>>> ", stdout);
    gets_s(buff, buffSize);
}
