#pragma once

#include <stdbool.h>
#include <stdint.h>


typedef enum tagLoginStatus {
    noLoad,
    loginSuccess, 
    noLogin, 
    wrongPassword, 
    accountNotFound,
    insufficientPrivileges
} LoginStatus;

typedef enum tagAccountType {
    noAccount, 
    userAccount, 
    adminAccount,
    superAdminAccount
} AccountType;

typedef uint32_t AccountID;
struct tagAccount;
struct tagUser;
struct tagAdmin;
struct tagSuperAdmin;
typedef struct tagAccountInternal *PAccountInternal;
typedef struct tagAdminInternal AdminInternal, * PAdminInternal;

#include "products.h"
#include "PriorDeclVector.h"
#include "PriorDeclRBTree.h"
PriorDeclVector(Product);

PriorDeclRBTree(AccountID, PAccountInternal);

typedef PairRBTree(AccountID, PAccountInternal) *PAccountNode;
PriorDeclVector(PAccountNode);

typedef struct {
    LoginStatus	          (*login)          (int account,     int password);
    void                  (*logout)         (void);
    void                  (*cancel)         (void);
    LoginStatus           (*loginState)     (void);
    bool                  (*registerNewUser)(int account,     int password, const char* name, bool isMale, int64_t phoneNumber, bool isVIP);
    AccountType           (*accountType)    (void);
    bool                  (*changePassword) (int oldPassword, int newPassword);
    struct tagAccount*    (*toAccount)      (void); // only cast down, else return NULL
    struct tagUser*       (*toUser)         (void); // only cast down, else return NULL
    struct tagAdmin*      (*toAdmin)        (void); // only cast down, else return NULL
    struct tagSuperAdmin* (*toSuperAdmin)   (void); // only cast down, else return NULL
    Vector(PProduct)*     (*getProducts)    (bool isSort, bool reverse, SortWayProduct sortWay);
} VirtualTable_Account;

typedef struct {
    VirtualTable_Account;
    void    (*topUp)     (double money);
    int     (*buyProduct)(ProductID productID, uint32_t size);
    double  (*getMoney)  (void);
} VirtualTable_User;

typedef struct {
    VirtualTable_Account;
    Vector(PAccountNode)* (*getAccounts)  (void);
} VirtualTable_Admin;

typedef struct {
    VirtualTable_Account;
    Vector(PAccountNode)* (*getAccounts)  (void);
    bool                  (*addProduct)   (PProduct  pProduct);
    bool                  (*removeProduct)(ProductID productID);
    PProduct              (*findProduct)  (ProductID productID);
    bool                  (*addAdmin)     (const AdminInternal* pAccount);
    int                   (*removeAccount)(AccountID accountID);
} VirtualTable_SuperAdmin;

typedef struct tagAccount {
    const VirtualTable_Account*    const vptr;
} *Account;

typedef struct tagUser {
    const VirtualTable_User*       const vptr;
} *User;

typedef struct tagAdmin {
    const VirtualTable_Admin*      const vptr;
} *Admin;

typedef struct tagSuperAdmin {
    const VirtualTable_SuperAdmin* const vptr;
} *SuperAdmin;

// free accounts' memory
void     freeAccounts(void);

// load accounts from file
bool     loadAccounts(FILE* pFile);

// write a new file head
size_t   makeAccountsFile(const char* fileName);

// store accounts in pFile, return the size of the contents written to the file
size_t   storeAccounts(FILE* pFile);

// get the size of the contents when accounts written to the file(ps: O(N))
size_t   getAccountsStoreSize(void);

// get current account, return NULL if not loaded account from file
Account  getAccount(void);


// common methon
LoginStatus           loginAccount         (int account,     int password);
void                  logoutAccount        (void);
void                  cancelAccount        (void);
bool                  registerNewUser      (int account,     int password, const char* name, bool isMale, int64_t phoneNumber, bool isVIP);
LoginStatus           accountLoginState    (void);
AccountType           accountType          (void);
bool                  changeAccountPassword(int newPassword, int oldPassword);
struct tagAccount*    toAccount            (void);
struct tagUser*       toUser               (void);
struct tagAdmin*      toAdmin              (void);
struct tagSuperAdmin* toSuperAdmin         (void);

// user methon
void                  topUpUser            (double    money);
int                   buyProductUser       (ProductID productID, uint32_t size);
double                getMoneyUser         (void);
bool                  addAdmin             (int account, int password, const char* name, bool isMale, int64_t phoneNumber);
int                   removeAccount        (AccountID accountID);

// super admin methon
Vector(PAccountNode)* getAccountsSuperAdmin(void);
