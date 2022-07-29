#pragma once

#include "macro_meta.h"


#define RBTreeNode(KeyType, MappedType)			 nameMangling3(RBTreeNode, KeyType, MappedType)
#define RBTree(KeyType, MappedType)				 nameMangling3(RBTree, KeyType,  MappedType)
#define PRBTree(KeyType, MappedType)			 nameMangling3(PRBTree, KeyType, MappedType)
#define PairRBTree(KeyType, MappedType)			 nameMangling3(PairRBTree, KeyType,  MappedType)
#define CompareRBTree(KeyType, MappedType)       nameMangling3(CompareRBTree, KeyType,  MappedType)
#define UnaryFunctionRBtree(KeyType, MappedType) nameMangling3(UnaryFunctionRBtree, KeyType,  MappedType)

#define PriorDeclRBTree(KeyType, MappedType)																			   \
    typedef struct nameMangling3(tagPairRBTree, KeyType, MappedType) PairRBTree(KeyType, MappedType);                  \
                                                                                                                       \
    typedef int(*CompareRBTree(KeyType, MappedType))(KeyType left, KeyType right);									   \
    typedef void(*UnaryFunctionRBtree(KeyType, MappedType))(PairRBTree(KeyType, MappedType)* pPair);			       \
                                                                                                                       \
    typedef struct nameMangling3(tagNodeRBTree, KeyType, MappedType)  RBTreeNode(KeyType, MappedType);				   \
                                                                                                                       \
    typedef struct nameMangling3(tagRBTree, KeyType, MappedType)                                                       \
        RBTree(KeyType, MappedType), *PRBTree(KeyType, MappedType)
        