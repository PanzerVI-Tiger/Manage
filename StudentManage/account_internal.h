#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "account.h"
#include "products.h"
#include "PriorDeclVector.h"

PriorDeclVector(Product);

typedef struct {
    int32_t		type;
    int32_t		password;
} SuperAdminPrivate, AccountBase;

typedef struct {
    SuperAdminPrivate;
    char	    name[11];
    bool	    isMale;
    int64_t     phoneNumber;
} AdminPrivate;

typedef struct {
    AdminPrivate;
    double			 money;
    bool			 isVIP;
    Vector(Product)* products;
} UserPrivate;

typedef struct tagAccountInternal {
    const VirtualTable_Account*	   vptr;
    SuperAdminPrivate;
} AccountInternal, *PAccountInternal;

typedef struct {
    const VirtualTable_SuperAdmin* vptr;
    SuperAdminPrivate;
} SuperAdminInternal, *PSuperAdminInternal;

typedef struct tagAdminInternal {
    const VirtualTable_Admin*	   vptr;
    AdminPrivate;
} AdminInternal, *PAdminInternal;

typedef struct {
    const VirtualTable_User*	   vptr;
    UserPrivate;
} UserInternal, *PUserInternal;

typedef struct {
    uint32_t bytesSize;
    uint32_t accountSize;
} AccountsFileHead;

typedef struct {
    AccountID    id;
    AccountBase  headData;
// 	unsigned char data[];  it's size is determined by account type
} AccountsFileNode;


#include "PriorDeclRBTree.h"
PriorDeclRBTree(AccountID, PAccountInternal);	
typedef PairRBTree(AccountID, PAccountInternal) AccountNode;
