#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "products.h"
#include "account_internal.h"
#define TypesPackRBTree() 2, AccountID,PAccountInternal, ProductID,ProductMapped
#include "RBTree.h"
#define TypesPackVector() 2, Product, PAccountNode
#include "Vector.h"


static const VirtualTable_Account vptrAccount = {
    .accountType     = &accountType,
    .cancel          = &cancelAccount,
    .changePassword  = &changeAccountPassword,
    .login           = &loginAccount,
    .loginState      = &accountLoginState,
    .logout          = &logoutAccount,
    .toAccount       = &toAccount,
    .toAdmin         = &toAdmin,
    .toSuperAdmin    = &toSuperAdmin,
    .toUser          = &toUser,
    .registerNewUser = &registerNewUser,
    .getProducts     = &getProductsVector
};

static const VirtualTable_User vptrUser = {
    .accountType     = &accountType,
    .cancel          = &cancelAccount,
    .changePassword  = &changeAccountPassword,
    .login           = &loginAccount,
    .loginState      = &accountLoginState,
    .logout          = &logoutAccount,
    .toAccount       = &toAccount,
    .toAdmin         = &toAdmin,
    .toSuperAdmin    = &toSuperAdmin,
    .toUser          = &toUser,
    .registerNewUser = &registerNewUser,
    .getProducts     = &getProductsVector,
    .buyProduct      = &buyProductUser,
    .topUp           = &topUpUser,
    .getMoney        = &getMoneyUser
};

static const VirtualTable_Admin vptrAdmin = {
    .accountType     = &accountType,
    .cancel          = &cancelAccount,
    .changePassword  = &changeAccountPassword,
    .login           = &loginAccount,
    .loginState      = &accountLoginState,
    .logout          = &logoutAccount,
    .toAccount       = &toAccount,
    .toAdmin         = &toAdmin,
    .toSuperAdmin    = &toSuperAdmin,
    .toUser          = &toUser,
    .registerNewUser = &registerNewUser,
    .getProducts     = &getProductsVector,
    .getAccounts     = &getAccountsSuperAdmin
};

static const VirtualTable_SuperAdmin vptrSuperAdmin = {
    .accountType     = &accountType,
    .cancel          = &cancelAccount,
    .changePassword  = &changeAccountPassword,
    .login           = &loginAccount,
    .loginState      = &accountLoginState,
    .logout          = &logoutAccount,
    .toAccount       = &toAccount,
    .toAdmin         = &toAdmin,
    .toSuperAdmin    = &toSuperAdmin,
    .toUser          = &toUser,
    .registerNewUser = &registerNewUser,
    .getProducts     = &getProductsVector,
    .addProduct      = &addProduct,
    .removeProduct   = &removeProduct,
    .findProduct     = &findProduct,
    .getAccounts     = &getAccountsSuperAdmin,
    .addAdmin        = &addAdmin,
    .removeAccount   = &removeAccount
};

static RBTree(AccountID, PAccountInternal) accounts;

static AccountInternal  emptyOperatorObject = {
    .type = noAccount, .vptr = &vptrAccount
};
static AccountNode      emptyOperatorNode   = {
    .key = 0, .mapped = &emptyOperatorObject
};
static AccountNode*     soleObject          = &emptyOperatorNode;
static LoginStatus      status              = noLoad;

static int compareIdRBtree(AccountID left, AccountID right) {
    if (left < right) {
        return -1;
    } else if (left > right) {
        return 1;
    } else {
        return 0;
    }
}

static void initial()
{
    if (status == noLoad) {
        accounts = createRBTree(AccountID, PAccountInternal)(&compareIdRBtree);
        status   = noLogin;
    }
}

static void freeNode(AccountNode* node)
{
    if (node->mapped->type == userAccount) {
        destroyVector(((UserInternal*)(node->mapped))->products);
        free(((UserInternal*)node->mapped)->products);
    } 
    free(node->mapped);
}

void freeAccounts(void)
{
    if (status == noLoad) {
        return;
    }
    status = noLoad;
    inOrderRBTree(&accounts, &freeNode);
    destroyRBTree(&accounts);
    freeProducts();
}

bool loadAccounts(FILE* pFile)
{
    if (pFile == NULL) {
        return;
    }
    
    if (status == noLoad) {
        initial();
    } else {
        destroyRBTree(&accounts);
    }
    
    AccountsFileHead head;
    fread(&head, sizeof(head), 1, pFile);
    for (size_t i = 0; i < head.accountSize; i++) {
        // [nodeHead, data[determined by type]]
        AccountsFileNode node;
        fread(&node, sizeof(node), 1, pFile); // read node head
        
        // read other
        switch (node.headData.type) {
        case userAccount: {
                UserInternal* pUserAccount = malloc(sizeof(UserInternal));
                pUserAccount->vptr         = &vptrUser;
                pUserAccount->password     = node.headData.password;
                pUserAccount->type         = node.headData.type;

                fread((char*)(pUserAccount) + sizeof(pUserAccount->vptr) + sizeof(node.headData), 
                      sizeof(UserInternal)  - sizeof(pUserAccount->vptr) - 
                      sizeof(node.headData) - sizeof(pUserAccount->products), 
                      1, pFile
                );
                
                // read a vector: [size, data[size]]
                int32_t productSize;
                fread(&productSize, sizeof(productSize), 1, pFile);                             // read size
                pUserAccount->products  = malloc(sizeof(Vector(Product)));                      // new a Vector
                *pUserAccount->products = createVector(Product)(productSize, 0);
                fread(dataVector(pUserAccount->products), sizeof(Product), productSize, pFile); // read data
                
                insertRBTree(&accounts, node.id, (AccountInternal**)&pUserAccount, false);
            }
            break;
            
        case adminAccount:{
                AdminInternal* pAdminAccount = malloc(sizeof(AdminInternal));
                pAdminAccount->vptr     = &vptrAdmin;
                pAdminAccount->password = node.headData.password;
                pAdminAccount->type     = node.headData.type;
                fread((char*)(pAdminAccount) + sizeof(pAdminAccount->vptr) + sizeof(node.headData), 
                      sizeof(AdminInternal)  - sizeof(pAdminAccount->vptr) - sizeof(node.headData), 1, pFile);
                insertRBTree(&accounts, node.id, (AccountInternal**)&pAdminAccount, false);
            }
            break;
            
        case superAdminAccount: {
                SuperAdminInternal* pSuperAdminAccount = malloc(sizeof(SuperAdminInternal));
                pSuperAdminAccount->vptr     = &vptrSuperAdmin;
                pSuperAdminAccount->password = node.headData.password;
                pSuperAdminAccount->type     = node.headData.type;
                
                insertRBTree(&accounts, node.id, (AccountInternal**)&pSuperAdminAccount, false);
            }
        }
    }
    loadProducts(pFile);
}

size_t   makeAccountsFile(const char* fileName)
{
    if (fileName == NULL) {
        return 0;
    }
    
    FILE* pFile = fopen(fileName, "w");
    
    AccountsFileHead head = {
        .bytesSize   = sizeof(AccountsFileNode) + sizeof(AccountsFileHead),
        .accountSize = 1
    };
    
    AccountsFileNode node = {
        .headData.password = 1919810,
        .headData.type     = superAdminAccount,
        .id                = 114514
    };
    fwrite(&head, sizeof(head), 1, pFile);
    fwrite(&node, sizeof(node), 1, pFile);

    Product product = {
        .key                = 191981,
        .mapped.cost        = 1000.,
        .mapped.price       = 1145.14,
        .mapped.name        = "ÏÉ±´¤Î°®",
        .mapped.discount    = 0.875,
        .mapped.shipAddress = "ÏÂ±±Ôó",
        .mapped.size        = 1919,
        .mapped.type        = 0
    };
    addProduct(&product);
    storeProducts(pFile);
    freeProducts();
    
    fclose(pFile);
    
    return head.bytesSize + getProductsStoreSize();
}

Account getAccount()
{
    return (Account)soleObject->mapped;
}

static size_t captureSize;

static void countAccountsByteSize(AccountNode* account)
{
    switch (account->mapped->type) {
    case userAccount:
        captureSize += sizeof(AccountID)             + sizeof(UserInternal) - 
                       sizeof(account->mapped->vptr) + sizeof(int32_t)      + 
                       sizeVector(((UserInternal*)(account->mapped))->products) * sizeof(Product);
        break;
    case adminAccount:
        captureSize += sizeof(AccountID) + sizeof(AdminInternal)      - sizeof(account->mapped->vptr);
        break;
    case superAdminAccount:
        captureSize += sizeof(AccountID) + sizeof(SuperAdminInternal) - sizeof(account->mapped->vptr);
        break;
    }
}

size_t getAccountsStoreSize(void)
{
    if (status == noLoad) {
        return 0;
    }
    captureSize   = 0;
    inOrderRBTree(&accounts, &countAccountsByteSize);
    size_t result = captureSize;
    captureSize   = 0;
    
    return result + sizeof(AccountsFileHead);
}

static FILE* captureFile = NULL;

static void storeNode(AccountNode* account)
{
    fwrite(&account->key, sizeof(account->key), 1, captureFile);
    switch (account->mapped->type) {
    case userAccount:
        // store user except products, [other, size, product[size]]
        fwrite((char*)(account->mapped)  + sizeof(account->mapped->vptr),
               sizeof(UserInternal)      - sizeof(account->mapped->vptr) -
               sizeof(Vector(Product)*), 1, captureFile);
        // store products
        int32_t size = sizeVector(((UserInternal*)(account->mapped))->products);
        fwrite(&size, sizeof(size), 1, captureFile);
        fwrite(dataVector(((UserInternal*)(account->mapped))->products), 
               sizeof(Product), size, captureFile);
        break;
        
    case adminAccount:
        fwrite((char*)(account->mapped)  + sizeof(account->mapped->vptr),
               sizeof(AdminInternal)     - sizeof(account->mapped->vptr), 1, captureFile);
        break;
        
    case superAdminAccount:
        fwrite((char*)(account->mapped)  + sizeof(account->mapped->vptr),
               sizeof(SuperAdminInternal)   - sizeof(account->mapped->vptr), 1, captureFile);
        break;
    }
}

size_t storeAccounts(FILE* pFile)
{
    if (pFile == NULL || status == noLoad) {
        return 0;
    }
    
    AccountsFileHead head = {
        .bytesSize   = getAccountsStoreSize(),
        .accountSize = sizeRBTree(&accounts)
    };
    fwrite(&head, sizeof(head), 1, pFile);

    captureFile = pFile;
    inOrderRBTree(&accounts, &storeNode);
    captureFile = NULL;
    
    storeProducts(pFile);
    
    return head.bytesSize;
}

LoginStatus loginAccount(int account, int password)
{
    if (status == noLoad) {
        return noLoad;
    }
    
    AccountNode* result = findRBTree(&accounts, account);
    if (result == NULL) {
        return accountNotFound;
    }
    
    if (result->mapped->password != password) {
        return wrongPassword;
    }

    soleObject = result;
    status     = loginSuccess;

    return loginSuccess;
}

void logoutAccount(void)
{
    if (status == noLoad) {
        return;
    }
    soleObject = &emptyOperatorNode;
    status     = noLogin;
}

void cancelAccount(void)
{
    if (status == noLoad || status == noLogin || soleObject->mapped->type == superAdminAccount) {
        return;
    }
    
    AccountNode* result = findRBTree(&accounts, soleObject->key);
    if (result == NULL) {
        return;
    }
    
    freeNode(result);
    eraseRBTree(&accounts, soleObject->key);
    
    status = noLogin;
}

bool registerNewUser(int account, int password, const char* name, bool isMale, int64_t phoneNumber, bool isVIP)
{
    if (status == noLoad) {
        return false;
    }
    
    if (containsRBTree(&accounts, account)) {
        return false;
    }
    
    UserInternal* pUserAccount = malloc(sizeof(UserInternal));
    pUserAccount->vptr         = &vptrUser;
    pUserAccount->password     = password;
    strcpy(pUserAccount->name, name);
    pUserAccount->isMale       = isMale;
    pUserAccount->phoneNumber  = phoneNumber;
    pUserAccount->isVIP        = isVIP;
    pUserAccount->type         = userAccount;
    pUserAccount->money        = 0;
    pUserAccount->products     = malloc(sizeof(Vector(Product)));
    *pUserAccount->products    = createVector(Product)(0, 0);
    
    insertRBTree(&accounts, account, (AccountInternal**)&pUserAccount, false);
    
    return true;
}

LoginStatus accountLoginState(void)
{
    return status;
}

AccountType accountType(void)
{
    return soleObject->mapped->type;
}

bool changeAccountPassword(int oldPassword, int newPassword)
{
    AccountNode* result = findRBTree(&accounts, soleObject->key);
    if (result == NULL) {
        return false;
    }
    
    if (result->mapped->password != oldPassword) {
        return false;
    }
    
    result->mapped->password = newPassword;
    
    return true;
}

struct tagAccount* toAccount(void)
{
    return soleObject->mapped;
}

struct tagUser* toUser(void)
{
    if (soleObject->mapped->type != userAccount) {
        return NULL;
    }
    
    return soleObject->mapped;
}

struct tagAdmin* toAdmin(void)
{
    if (soleObject->mapped->type < adminAccount) {
        return NULL;
    }
    
    return soleObject->mapped;
}

struct tagSuperAdmin* toSuperAdmin(void)
{
    if (soleObject->mapped->type != superAdminAccount) {
        return NULL;
    }
    
    return soleObject->mapped;
}

void topUpUser(double money)
{
    if (status == noLoad || status == noLogin || soleObject->mapped->type != userAccount) {
        return;
    }
    
    ((UserInternal*)(soleObject->mapped))->money += money;
}

int buyProductUser(ProductID productID, uint32_t size)
{
    if (status == noLoad || status == noLogin || soleObject->mapped->type != userAccount) {
        return 0;
    }
    
    PProduct product    = findProduct(productID);
    if (product == NULL) {
        return 0;
    }
    
    UserInternal* pUser = (UserInternal*)soleObject->mapped;
    
    double price = product->mapped.price * size;
    if (pUser->isVIP) {
        price *= product->mapped.discount;
    }
    
    if (pUser->money < price) {
        return -1;
    }
    
    if (product->mapped.size < size) {
        return -2;
    }
    product->mapped.size -= size;
    
    pUser->money -= price;
    
    Vector(Product)* pProducts = pUser->products;
    
    pushBackVector(pProducts, product);
    backVector(pProducts)->mapped.size = 1;
    
    return 1;
}

double  getMoneyUser(void)
{
    if (status == noLoad || status == noLogin || soleObject->mapped->type != userAccount) {
        return 0;
    }
    
    return ((UserInternal*)(soleObject->mapped))->money;
}

bool addAdmin(int account, int password, const char* name, bool isMale, int64_t phoneNumber)
{
    if (status == noLoad || status == noLogin || soleObject->mapped->type != superAdminAccount) {
        return false;
    }
    
    if (containsRBTree(&accounts, account)) {
        return false;
    }
    
    AdminInternal* pAdmin = malloc(sizeof(AdminInternal));
    pAdmin->vptr          = &vptrAdmin;
    pAdmin->password      = password;
    strcpy(pAdmin->name, name);
    pAdmin->isMale        = isMale;
    pAdmin->phoneNumber   = phoneNumber;
    pAdmin->type          = adminAccount;

    insertRBTree(&accounts, account, (AccountInternal**)&pAdmin, false);
    
    return true;
}

int removeAccount(AccountID accountID)
{
    if (status == noLoad || status == noLogin) {
        return 0;
    }
    
    AccountNode* result = findRBTree(&accounts, accountID);
    if (result == NULL) {
        return 0;
    }

    if (soleObject->mapped->type < adminAccount) {
        return -1;
    }
    
    freeNode(result);
    eraseRBTree(&accounts, accountID);
    
    return 1;
}

static Vector(PAccountNode) accountsVector;

void pushBackAccount(AccountNode* pAccount)
{
    if (soleObject->mapped->type <= pAccount->mapped->type) {
        return;
    }
    pushBackVector(&accountsVector, &pAccount);
}

Vector(PAccountNode)* getAccountsSuperAdmin(void)
{
    if (status == noLoad || status == noLogin || soleObject->mapped->type < adminAccount) {
        return NULL;
    }
    
    accountsVector = createVector(PAccountNode)(0, 0);
    inOrderRBTree(&accounts, &pushBackAccount);
    
    return &accountsVector;
}

