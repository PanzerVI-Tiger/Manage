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
              "|       ��ӭ�������̹���ϵͳ       |\n"
              "====================================\n"
              "|                                  |\n"
              "|           1   : ��¼             |\n"
              "|           2   : ע��             |\n"
              "|           ����: �˳�             |\n"
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
          "|             ��¼����             |\n" 
          "====================================\n"
          "�������˺�:\n"
          "input>>> " , stdout);
    char buff[buffSize] = { 0, };
    gets_s(buff, buffSize);

    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("��Ч���˺�, ����������(�˺�Ϊ������, �ҳ���С��\n"
              "10λ, ����5λ):\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int id = atoi(buff);
    
    fputs("����������:\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("��Ч������, ����������(����Ϊ������, �ҳ���С��\n"
              "10λ, ����5λ):\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int password = atoi(buff);
    
    account            = getAccount();
    LoginStatus status = account->vptr->login(id, password);
    
    switch (status) {
    case accountNotFound:
        fputs("�˺Ų�����! ���»س�����:\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
        
        break;
        
    case wrongPassword:
        fputs("�������! ���»س�����:\n"
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
          "|           �޸��������           |\n" 
          "====================================\n"
          "������ԭ����:\n"
          "input>>> ", stdout);
    char buff[buffSize] = { 0, };
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("��Ч������, ����������(����Ϊ������, �ҳ���С��\n"
              "10λ, ����5λ):\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int password = atoi(buff);
    
    fputs("������������:\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("��Ч������, ����������(����Ϊ������, �ҳ���С��\n"
              "10λ, ����5λ):\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int newPassword = atoi(buff);
    
    if (account->vptr->changePassword(password, newPassword)) {
        isChange = true;
        fputs("�����޸ĳɹ�! ���»س�����:\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    } else {
        fputs("�����޸�ʧ��! ���»س�����:\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    system("cls");
}

void registerPanel(void)
{
    fputs("====================================\n"
          "|             ע�����             |\n" 
          "====================================\n"
          "�������˺�(�˺�Ϊ������, �ҳ���С��\n"
          "10λ, ����5λ):\n"
          "input>>> ", stdout);
    char buff[buffSize] = { 0, };
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("��Ч���˺�, ����������:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int id = atoi(buff);
    
    fputs("����������(����Ϊ������, �ҳ���С��10λ, ����5λ):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("��Ч������, ����������:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int password = atoi(buff);
    
    fputs("�������û���(�û�������С��10���ַ�, ����������һ����):\n"
          "input>>> ", stdout);
    char* name[buffSize] = { 0, };
    gets_s(name, buffSize);
    while (strlen(name) > 10) {
        fputs("�û������ȳ���10���ַ�, ����������:\n"
              "input>>> ", stdout);
        gets_s(name, buffSize);
    }

    fputs("�������Ա�(1Ϊ��, ����Ů):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    bool isMale = atoi(buff) == 1;

    fputs("������绰����(����12λ):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 0, 11)) {
        fputs("��Ч�ĵ绰����, ����������:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    long long phone = atoll(buff);
    
    
    fputs("�Ƿ񻨷�100Ԫ��ΪVIP(1��, ������):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    bool isVip = atoi(buff) == 1;

    account = getAccount();
    if (account->vptr->registerNewUser(id, password, name, isMale, phone, isVip)) {
        isChange = true;
        system("cls");
        loginPanel();
    } else {
        fputs("ע��ʧ��! ���»س�����:\n"
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
               "|             �û�����             |\n"
               "------------------------------------\n"
               "|       ��ӭ����, %-10s!      |\n"
               "====================================\n"
               "|          1:    ���߹���          |\n"
               "|          2:    Ǯ������          |\n"
               "|          3:    �޸�����          |\n"
               "|          ����: ����              |\n"
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
              "|             ���߹���             |\n"
              "====================================\n"
              "|          1:    �鿴��Ʒ          |\n"
              "|          2:    ������Ʒ          |\n"
              "|          3:    �鿴����          |\n"
              "|          ����: ����              |\n"
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
          "����    ��Ʒ����    ��Ʒ���   ������ַ      �۸�    ����   �ۿ�  ����  ����\n"
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
          "���»س�����:\n"
          ">>> ", stdout);
    char buff[buffSize];
    gets_s(buff, buffSize);
}

void buyProduct(void)
{
    fputs("��������Ʒ���:\n"
          "input>>> ", stdout);
    char buff[buffSize] = { 0, };
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 6)) {
        fputs("��Ч����Ʒ���, ����������:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    
    int32_t       productId = atoi(buff);

    fputs("�����빺������:\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 5)) {
        fputs("��Ч�Ĺ�������, ����������:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    uint32_t      size      = atoi(buff);
    UserInternal* user      = account->vptr->toUser();
    int           status    = user->vptr->buyProduct(productId, size);
    if (status == 0) {
        fputs("��Ʒ������!\n"
              "���»س�����>>> ", stdout);
        gets_s(buff, buffSize); 
        return;
    }
    
    if (status == -2) {
        fputs("��治��!\n"
              "���»س�����>>> ", stdout);
        gets_s(buff, buffSize); 
        return;
    }
    
    while (status == -1) {
        fputs("����, �Ƿ��ֵ?(1: ��, ����: ��)\n"
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
    fputs("����ɹ�!\n"
          "���»س�����>>> ", stdout);
    gets_s(buff, buffSize);
}

void walletPanel(void)
{
    UserInternal* user = account->vptr->toUser();
    while (true) {
        fputs("====================================\n"
              "|             Ǯ������             |\n"
              "====================================\n"
              "|          1:    �鿴���          |\n"
              "|          2:    ��ֵ              |\n"
              "|          ����: ����              |\n"
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
                   "|             ���鿴             |\n"
                   "====================================\n"
                   "|          ���: %-10s        |\n"
                   "====================================\n"
                   "���»س�����>>> ", buff);
            }
              gets_s(buff, buffSize);
            
            break;
        
        case 2:
            fputs("�������ֵ���:\n"
                  "input>>> ", stdout);
            gets_s(buff, buffSize);
            double money = atof(buff);
            user->vptr->topUp(money);
            isChange = true;
            fputs("��ֵ�ɹ�! ���»س�����:\n"
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
              "|             ����Ա���             |\n"
              "====================================\n"
              "|          1:    ������Ʒ          |\n"
              "|          2:    �����û�          |\n"
              "|          3:    �޸�����          |\n"
              "|          ����: �鿴�û�          |\n"
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
              "|          ��������Ա����          |\n"
              "------------------------------------\n"
              "|       ��ӭ����, ��������Ա!      |\n"
              "====================================\n"
              "|          1:    �����˺�          |\n"
              "|          2:    ������Ʒ          |\n"
              "|          3:    �޸�����          |\n"
              "|          ����: ����              |\n"
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
              "|             �˺Ź���             |\n"
              "====================================\n"
              "|       1:    �鿴�˺���Ϣ         |\n"
              "|       2:    ɾ���˺�             |");
            
        if (type == superAdminAccount) {
            puts(
              "|       3:    ��ӹ���Ա�˺�       |");
        }
        fputs("|       ����: ������һ��           |\n"
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
          "|          ����Ա��������          |\n" 
          "====================================\n"
          "�������˺�(�˺�Ϊ������, �ҳ���С��\n"
          "10λ, ����5λ):\n"
          "input>>> ", stdout);
    char buff[buffSize] = { 0, };
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("��Ч���˺�, ����������:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int id = atoi(buff);
    
    fputs("����������(����Ϊ������, �ҳ���С��10λ, ����5λ):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("��Ч������, ����������:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int password = atoi(buff);
    
    fputs("�������û���(�û�������С��10���ַ�, ����������һ����):\n"
          "input>>> ", stdout);
    char* name[buffSize] = { 0, };
    gets_s(name, buffSize);
    while (strlen(name) > 10) {
        fputs("�û������ȳ���10���ַ�, ����������:\n"
              "input>>> ", stdout);
        gets_s(name, buffSize);
    }

    fputs("�������Ա�(1Ϊ��, ����Ů):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    bool isMale = atoi(buff) == 1;

    fputs("������绰����(����12λ):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 0, 11)) {
        fputs("��Ч�ĵ绰����, ����������:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    long long phone = atoll(buff);

    account = getAccount();
    SuperAdmin pSuperAdmin = account->vptr->toSuperAdmin();
    if (pSuperAdmin->vptr->addAdmin(id, password, name, isMale, phone)) {
        isChange = true;
        puts("��ӳɹ�!");
    } else {
        puts("ע��ʧ��!:");
        gets_s(buff, buffSize);
    }
    fputs("���»س�����>>> ", stdout);
    gets_s(buff, buffSize);
}

void removeAccountPanel(void)
{
    fputs("====================================\n"
          "|          �˺�ɾ������          |\n" 
          "====================================\n"
          "�������˺�(�˺�Ϊ������, �ҳ���С��\n"
          "10λ, ����5λ):\n"
          "input>>> ", stdout);
    char buff[buffSize] = { 0, };
    gets_s(buff, buffSize);
    
    while (!checkIsEffectNumber(buff, 6, 9)) {
        fputs("��Ч���˺�, ����������:\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
    }
    int id = atoi(buff);
    
    account = getAccount();
    SuperAdmin pSuperAdmin = account->vptr->toSuperAdmin();
    if (pSuperAdmin->vptr->removeAccount(id)) {
        isChange = true;
        puts("ɾ���ɹ�!\n");
    } else {
        puts("ɾ��ʧ��!:\n");
        gets_s(buff, buffSize);
    }
}

void printAccounts(void)
{
    fputs("=============================================\n"
          "|                 �˺��б�                  |\n"
          "=============================================\n"
          "---------- --------- ------ -- ----------- --\n"
          "   ����      �˺�     ���� �Ա� �绰����  VIP\n"
          "---------- --------- ------ -- ----------- --\n"
          , stdout);
    Vector(PAccountNode)* accounts = account->vptr->toAdmin()->vptr->getAccounts();
    for (int i = 0, j = sizeVector(accounts); i < j; ++i) {
        PAccountNode accountNode = *atVector(accounts, i);
        switch (accountNode->mapped->type) {
        case userAccount: {
                UserInternal* user = (UserInternal*)accountNode->mapped;
                printf("%-10s %-9d �û�   %-2s %-11lld %-2s\n",
                    user->name, accountNode->key, user->isMale ? "��" : "Ů", 
                    user->phoneNumber, user->isVIP ? "��" : "��");
            }
            break;
            
        case adminAccount: {
                AdminInternal* admin = (AdminInternal*)accountNode->mapped;
                printf("%-10s %-9d ����Ա %-2s %-11lld NA\n",
                    admin->name, accountNode->key, admin->isMale ? "��" : "Ů", 
                    admin->phoneNumber);
            }
        }
        
    }
    destroyVector(accounts);
    char buff[buffSize];
    fputs("---------- --------- ------ -- ----------- --\n"
          "���س�����>>> ", stdout);
    gets_s(buff, buffSize);
}

void productManagePanel(void)
{
    while (true) {
        fputs("====================================\n"
              "|           ��Ʒ�������           |\n"
              "====================================\n"
              "|          1:    �����Ʒ          |\n"
              "|          2:    ɾ����Ʒ          |\n"
              "|          3:    �޸���Ʒ          |\n"
              "|          4:    ��ѯ��Ʒ          |\n"
              "|          5:    �г���Ʒ          |\n"
              "|          ����: ����              |\n"
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
          "|                              ��Ʒ�б�                               |\n"
          "=======================================================================\n", stdout);
    bool isSort            = false; 
    bool reverse           = false;
    SortWayProduct sortWay = sortByID;
    char buff[buffSize];
    fputs("����������ʽ(1:����, 2:���, 3:�۸�, 4:�ۿ�, 5:���, ����: ������):\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    sortWay = atoi(buff);
    if (checkIsEffectNumber(buff, 1, 1) && sortWay <= 5 && sortWay >= 1) {
        isSort = true;
        fputs("�Ƿ���������(1: ��, ����: ��):\n"
              "input>>> ", stdout);
        gets_s(buff, buffSize);
        reverse = atoi(buff) == 1 && checkIsEffectNumber(buff, 1, 1);
    }
    
    fputs("--------------- ------ --------------- ------- ------- ----- ----- ----\n"
          "   ��Ʒ����    ��Ʒ���   ������ַ      �۸�    ����   �ۿ�  ���  ����\n"
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
          "���»س�����>>> ", stdout);
    gets_s(buff, buffSize);
}

void addProductPanel(void)
{
    fputs("====================================\n"
          "|           �����Ʒ����           |\n"
          "====================================\n"
          "��������Ʒ����(������15���ַ�)\n"
          "input>>> ", stdout);
    char buff[buffSize];
    Product product;
    
    gets_s(buff, buffSize);
    while (strlen(buff) > 15) {
        fputs("��Ʒ���ƹ���, ����������\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    strcpy(product.mapped.name, buff);
    
    fputs("��������Ʒ���(����, ������6���ַ�)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 6)) {
        fputs("��Ʒ��Ź������������˷������ַ�, ����������\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    *((ProductID*)(&product.key)) = atoi(buff);

    fputs("��������Ʒ������ַ(������15���ַ�)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (strlen(buff) > 15) {
        fputs("��Ʒ������ַ����, ����������\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }   
    strcpy(product.mapped.shipAddress, buff);

    fputs("��������Ʒ�۸�(������6λ��Ч����)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    product.mapped.price = atof(buff);

    fputs("��������Ʒ����(������6λ��Ч����)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    product.mapped.cost = atof(buff);

    fputs("��������Ʒ�ۿ�(С��1, ������3λ��Ч����)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    product.mapped.discount = atof(buff);
    while (product.mapped.discount > 1) {
        fputs("�ۿ۴���һ, ����������\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
        product.mapped.discount = atof(buff);
    }
    
    fputs("��������Ʒ���(������5λ����)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 5)) {
        fputs("�������ֹ�����������˷������ַ�, ����������\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    product.mapped.size = atoi(buff);

    fputs("��������Ʒ����(������4λ����)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 4)) {
        fputs("�������ֹ�����������˷������ַ�, ����������\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    product.mapped.type = atoi(buff);

    SuperAdmin superAdmin = account->vptr->toSuperAdmin();
    if (superAdmin->vptr->addProduct(&product)) {
        isChange = true;
        fputs("�����Ʒ�ɹ�\n"
              "���»س�����>>> ", stdout);
        gets_s(buff, buffSize);
    } else {
        fputs("�����Ʒʧ��\n"
              "���»س�����>>> ", stdout);
        gets_s(buff, buffSize);
    }
}

void removeProductPanel(void)
{
    fputs("====================================\n"
          "|           ɾ����Ʒ����           |\n"
          "====================================\n"
          "��������Ʒ���(����, ������6���ַ�)\n"
          "input>>> ", stdout);
    char buff[buffSize];
    ProductID productID;
    
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 6)) {
        fputs("��Ʒ��Ź������������˷������ַ�, ����������\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    productID = atoi(buff);
    
    SuperAdmin superAdmin = account->vptr->toSuperAdmin();
    if (superAdmin->vptr->removeProduct(productID)) {
        isChange = true;
        fputs("ɾ����Ʒ�ɹ�\n"
              "���»س�����>>> ", stdout);
        gets_s(buff, buffSize);
    } else {
        fputs("ɾ����Ʒʧ��\n"
              "���»س�����>>> ", stdout);
        gets_s(buff, buffSize);
    }
}

void changeProductPanel(void)
{
    fputs("====================================\n"
          "|           �޸���Ʒ����           |\n"
          "====================================\n"
          "��������Ʒ���(����, ������6���ַ�)\n"
          "input>>> ", stdout);
    char buff[buffSize];
    ProductID productID;
    
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 6)) {
        fputs("��Ʒ��Ź������������˷������ַ�, ����������\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    productID = atoi(buff);
    
    PProduct product = account->vptr->toSuperAdmin()->vptr->findProduct(productID);
    if (product == NULL) {
        fputs("û���ҵ�����Ʒ\n"
              "���»س�����>>> ", stdout);
        gets_s(buff, buffSize);
        return;
    }
    
    isChange = true;
    fputs("��������Ʒ����(������15���ַ�)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (strlen(buff) > 15) {
        fputs("��Ʒ���ƹ���, ����������\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    strcpy(product->mapped.name, buff);

    fputs("��������Ʒ������ַ(������15���ַ�)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (strlen(buff) > 15) {
        fputs("��Ʒ������ַ����, ����������\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }   
    strcpy(product->mapped.shipAddress, buff);

    fputs("��������Ʒ�۸�(������6λ��Ч����)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    product->mapped.price = atof(buff);

    fputs("��������Ʒ����(������6λ��Ч����)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    product->mapped.cost = atof(buff);

    fputs("��������Ʒ�ۿ�(С��1, ������3λ��Ч����)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    product->mapped.discount = atof(buff);
    while (product->mapped.discount > 1) {
        fputs("�ۿ۴���һ, ����������\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
        product->mapped.discount = atof(buff);
    }
    
    fputs("��������Ʒ���(������5λ����)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 5)) {
        fputs("�������ֹ�����������˷������ַ�, ����������\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    product->mapped.size = atoi(buff);

    fputs("��������Ʒ����(������4λ����)\n"
          "input>>> ", stdout);
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 4)) {
        fputs("�������ֹ�����������˷������ַ�, ����������\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    product->mapped.type = atoi(buff);
    
    fputs("���»س�����:\n"
          ">>> ", stdout);
    gets_s(buff, buffSize);
}

void findProductPanel(void)
{
    fputs("====================================\n"
          "|           ������Ʒ����           |\n"
          "====================================\n"
          "��������Ʒ���(����, ������6���ַ�)\n"
          "input>>> ", stdout);
    char buff[buffSize];
    ProductID productID;
    
    gets_s(buff, buffSize);
    while (!checkIsEffectNumber(buff, 1, 6)) {
        fputs("��Ʒ��Ź������������˷������ַ�, ����������\n"
              ">>> ", stdout);
        gets_s(buff, buffSize);
    }
    productID = atoi(buff);
    
    PProduct product = account->vptr->toSuperAdmin()->vptr->findProduct(productID);
    if (product == NULL) {
        fputs("û���ҵ�����Ʒ\n"
              "���»س�����>>> ", stdout);
        gets_s(buff, buffSize);
        return;
    }
    fputs("--------------- ------ --------------- ------- ------- ----- ----- ----\n"
          "   ��Ʒ����    ��Ʒ���   ������ַ      �۸�    ����   �ۿ�  ���  ����\n"
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
          "���»س�����>>> ", stdout);
    gets_s(buff, buffSize);
}
