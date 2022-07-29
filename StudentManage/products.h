#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint32_t ProductID;
typedef struct {
    char    name[16];        // less than 16 characater
    char    shipAddress[16]; // less than 16 characater
    double  price;           // price of the product
    double  cost;            // cost of the product
//  double  profit = price - cost;
    double  discount;        // less than 1, only valid when user is VIP, then price = price * (1 - discount)
    int32_t size;            // count of this product
    int32_t type;            // product type
} ProductMapped;


#include "PriorDeclRBTree.h"
PriorDeclRBTree(ProductID, ProductMapped);
typedef PairRBTree(ProductID, ProductMapped) Product, * PProduct;
#include "PriorDeclVector.h"
PriorDeclVector(PProduct);

typedef enum {
    sortByID       = 2,
    sortByName     = 1,
    sortByPrice    = 3,
    sortByCost     = 6,
    sortByDiscount = 4,
    sortBySize     = 5,
    sortByType     = 7
} SortWayProduct;

// free products's memory
void              freeProducts    (void);

// load products form pFile
bool              loadProducts    (FILE* pFile);

// store products in pFile, return the size of the contents written to the file
size_t            storeProducts   (FILE* pFile);

// get the size of the contents when products written to the file
size_t            getProductsStoreSize     (void);

// return a pointer to vector which contained pointer to Product, must destroy it after use
Vector(PProduct)* getProductsVector(bool isSort, bool reverse, SortWayProduct sortWay);

// find product by id
PProduct          findProduct      (ProductID id);

// remove product by id
bool              removeProduct    (ProductID id);

// if nProduct is new, return true, else return false
bool              addProduct       (PProduct pProduct);
