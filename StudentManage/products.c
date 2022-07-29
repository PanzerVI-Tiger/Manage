#include "products.h"

#define TypesPackRBTree() 1, ProductID,ProductMapped
#include "RBTree.h"

#define TypesPackVector() 1, PProduct
#include "Vector.h"

typedef struct {
    uint32_t bytesSize;
    uint32_t productsSize;
} ProductsFileHead;

static bool                             isInitial = false;
static RBTree(ProductID, ProductMapped) products;

static int compareIdRBtree(ProductID left, ProductID right) {
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
    if (!isInitial)
    {
        isInitial = true;
        products  = createRBTree(ProductID, ProductMapped)(&compareIdRBtree);
    }
}

void freeProducts(void)
{
    if (!isInitial) {
        return;
    }
    isInitial = false;
    destroyRBTree(&products);
}

bool loadProducts(FILE* pFile)
{
    if (pFile == NULL) {
        return false;
    }
    if (!isInitial) {
        initial();
    } else {
        destroyRBTree(&products);
    }
    
    ProductsFileHead fHead;
    fread(&fHead, sizeof(fHead), 1, pFile);
    
    for (uint32_t i = 0; i < fHead.productsSize; ++i) {
        Product buff;
        fread(&buff, sizeof(buff), 1, pFile);
        insertRBTree(&products, buff.key, &buff.mapped, false);
    }
    
    return true;
}

static FILE* capturePFile = NULL;

static void storeNode(Product* pair)
{
    fwrite(pair, 1, sizeof(*pair), capturePFile);
}

size_t storeProducts(FILE* pFile)
{
    if (!isInitial || pFile == NULL) {
        return 0;
    } else {
        ProductsFileHead fhead = {
            .bytesSize    = sizeof(fhead) + sizeof(Product) * sizeRBTree(&products),
            .productsSize = sizeRBTree(&products)
        };
        fwrite(&fhead, 1, sizeof(fhead), pFile);
        
        capturePFile = pFile;
        inOrderRBTree(&products, &storeNode);
        capturePFile = NULL;
    }
    
    return getProductsStoreSize();
}

size_t getProductsStoreSize(void)
{
    if (!isInitial) {
        return sizeof(ProductsFileHead);
    }
    return sizeof(ProductsFileHead) + sizeof(Product) * sizeRBTree(&products);
}

static int compareId(PProduct* left, PProduct* right)
{
    if ((*left)->key > (*right)->key) {
        return 1;
    } else if ((*left)->key < (*right)->key) {
        return -1;
    } else {
        return 0;
    }
}

static int compareIdReverse(PProduct* left, PProduct* right)
{
    if ((*left)->key > (*right)->key) {
        return -1;
    } else if ((*left)->key < (*right)->key) {
        return 1;
    } else {
        return 0;
    }
}

static int compareName(const PProduct* left, const PProduct* right)
{
    return strcmp((*left)->mapped.name, (*right)->mapped.name);
}

static int compareNameReverse(const PProduct* left, const PProduct* right)
{
    return strcmp((*right)->mapped.name, (*left)->mapped.name);
}

static int comparePrice(const PProduct* left, const PProduct* right)
{
    return (int)((*left)->mapped.price - (*right)->mapped.price);
}

static int comparePriceReverse(const PProduct* left, const PProduct* right)
{
    return (int)((*right)->mapped.price - (*left)->mapped.price);
}

static int compareCost(const PProduct* left, const PProduct* right)
{
    return (int)((*left)->mapped.cost - (*right)->mapped.cost);
}

static int compareCostReverse(const PProduct* left, const PProduct* right)
{
    return (int)((*right)->mapped.cost - (*left)->mapped.cost);
}

static int compareDiscount(const PProduct* left, const PProduct* right)
{
    return (int)((*left)->mapped.discount - (*right)->mapped.discount);
}

static int compareDiscountReverse(const PProduct* left, const PProduct* right)
{
    return  (int)((*right)->mapped.discount - (*left)->mapped.discount);
}

static int compareSize(const PProduct* left, const PProduct* right)
{
    if ((*left)->mapped.size > (*right)->mapped.size) {
        return 1;
    } else if ((*left)->mapped.size < (*right)->mapped.size) {
        return -1;
    } else {
        return 0;
    }
}

static int compareSizeReverse(const PProduct* left, const PProduct* right)
{
    if ((*left)->mapped.size > (*right)->mapped.size) {
        return -1;
    } else if ((*left)->mapped.size < (*right)->mapped.size) {
        return 1;
    } else {
        return 0;
    }
}

static int compareType(const PProduct* left, const PProduct* right)
{
    if ((*left)->mapped.type > (*right)->mapped.type) {
        return 1;
    } else if ((*left)->mapped.type < (*right)->mapped.type) {
        return -1;
    } else {
        return 0;
    }
}

static int compareTypeReverse(const PProduct* left, const PProduct* right)
{
    if ((*left)->mapped.type > (*right)->mapped.type) {
        return -1;
    } else if ((*left)->mapped.type < (*right)->mapped.type) {
        return 1;
    } else {
        return 0;
    }
}

static Vector(PProduct)* captureVector = NULL;

static void pushNodeInVector(Product* pProduct)
{
    pushBackVector(captureVector, &pProduct);
}

Vector(PProduct)* getProductsVector(bool isSort, bool reverse, SortWayProduct sortWay)
{
    static Vector(PProduct) result;
    result = createVector(PProduct)(0, NULL);
    
    if (!isInitial) {
        return &result; // empty
    }
    
    captureVector           = &result;
    inOrderRBTree(&products, &pushNodeInVector);
    captureVector           = NULL;

    if (!isSort) {
        return &result;
    }

    CompareRBTree(ProductID, ProductMapped) compare = NULL;
    if (!reverse) {
        switch (sortWay) {
        case sortByID:
            return &result;
        case sortByName:
            compare = &compareName;
            break;
        case sortByPrice:
            compare = &comparePrice;
            break;
        case sortByCost:
            compare = &compareCost;
            break;
        case sortByDiscount:
            compare = &compareDiscount;
            break;
        case sortBySize:
            compare = &compareSize;
            break;
        case sortByType:
            compare = &compareType;
            break;
        }
    } else {
        switch (sortWay) {
        case sortByID:
            // reverse
            for (size_t i = 0, j = sizeVector(&result); i < j; i++) {
                PProduct temp                 = *atVector(&result, i);
                *atVector(&result, i)         = *atVector(&result, j - i - 1);
                *atVector(&result, j - i - 1) = temp;
            }
            return &result;
        case sortByName:
            compare = &compareNameReverse;
            break;
        case sortByPrice:
            compare = &comparePriceReverse;
            break;
        case sortByCost:
            compare = &compareCostReverse;
            break;
        case sortByDiscount:
            compare = &compareDiscountReverse;
            break;
        case sortBySize:
            compare = &compareSizeReverse;
            break;
        case sortByType:
            compare = &compareTypeReverse;
            break;
        }
    }
    sortVector(&result, compare);
    return &result;
}

PProduct findProduct(ProductID id)
{
    if (!isInitial) {
        return NULL;
    }
    return findRBTree(&products, id);
}

bool removeProduct(ProductID id)
{
    if (!isInitial) {
        return false;
    }
    
    return eraseRBTree(&products, id);
}

bool addProduct(PProduct pProduct)
{
    initial();
    PProduct product = findProduct(pProduct->key);
    if (product == NULL) {
        insertRBTree(&products, pProduct->key, &pProduct->mapped, false);
    } else {
        product->mapped.size += pProduct->mapped.size;
    }
    return true;
}
