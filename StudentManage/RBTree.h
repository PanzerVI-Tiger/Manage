#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "macro_meta.h"

/***************************************************** head only  *****************************************************/

#define RBTreeNode(KeyType, MappedType)          nameMangling3(RBTreeNode, KeyType, MappedType)
#define RBTree(KeyType, MappedType)              nameMangling3(RBTree, KeyType,  MappedType)
#define PRBTree(KeyType, MappedType)             nameMangling3(PRBTree, KeyType, MappedType)
#define PairRBTree(KeyType, MappedType)          nameMangling3(PairRBTree, KeyType,  MappedType)
#define CompareRBTree(KeyType, MappedType)       nameMangling3(CompareRBTree, KeyType,  MappedType)
#define UnaryFunctionRBtree(KeyType, MappedType) nameMangling3(UnaryFunctionRBtree, KeyType,  MappedType)

#define linkPRBTreeName(mangling, KeyType, MappedType) \
    macroTransmit0(nameMangling2, mangling, PRBTree(KeyType, MappedType))

#define DeclRBTree(KeyType, MappedType)                                                                                \
    typedef struct nameMangling3(tagPairRBTree, KeyType, MappedType) {                                                 \
        const KeyType key;                                                                                             \
        MappedType    mapped;                                                                                          \
    } PairRBTree(KeyType, MappedType);                                                                                 \
                                                                                                                       \
    typedef int(*CompareRBTree(KeyType, MappedType))(KeyType left, KeyType right);                                     \
    typedef void(*UnaryFunctionRBtree(KeyType, MappedType))(PairRBTree(KeyType, MappedType)* pPair);                   \
                                                                                                                       \
    typedef struct nameMangling3(tagNodeRBTree, KeyType, MappedType) {                                                 \
        struct nameMangling3(tagNodeRBTree, KeyType, MappedType) *left;                                                \
        struct nameMangling3(tagNodeRBTree, KeyType, MappedType) *right;                                               \
        int                                                       color; /*true is red, false is black*/               \
        PairRBTree(KeyType, MappedType)                           pair;                                                \
    } RBTreeNode(KeyType, MappedType);                                                                                 \
                                                                                                                       \
    typedef struct nameMangling3(tagRBTree, KeyType, MappedType) {                                                     \
        CompareRBTree(KeyType, MappedType) compare;                                                                    \
        RBTreeNode(KeyType, MappedType)*      root;                                                                    \
        size_t                                nodeSize;                                                                \
    } RBTree(KeyType, MappedType), *PRBTree(KeyType, MappedType);                                                      \
                                                                                                                       \
/************** Node function  **************/                                                                         \
    /* createNodeRBTree */                                                                                             \
    inline RBTreeNode(KeyType, MappedType) nameMangling3(createNodeRBTree, KeyType, MappedType)                        \
        (KeyType key, const MappedType* pMapped, bool color)                                                           \
    {                                                                                                                  \
        RBTreeNode(KeyType, MappedType) result = {                                                                     \
            .left        = NULL,                                                                                       \
            .right       = NULL,                                                                                       \
            .color       = color,                                                                                      \
        };                                                                                                             \
        memcpy(&result.pair.key,    &key,    sizeof(KeyType));                                                         \
        memcpy(&result.pair.mapped, pMapped, sizeof(MappedType));                                                      \
                                                                                                                       \
        return result;                                                                                                 \
    }                                                                                                                  \
                                                                                                                       \
    /* destroyRBTreeNode */                                                                                            \
    inline void nameMangling3(destroyRBTreeNode, KeyType, MappedType)(RBTreeNode(KeyType, MappedType)* node)           \
    {                                                                                                                  \
        if (node == NULL) {                                                                                            \
            return;                                                                                                    \
        }                                                                                                              \
        nameMangling3(destroyRBTreeNode, KeyType, MappedType)(node->left);                                             \
        nameMangling3(destroyRBTreeNode, KeyType, MappedType)(node->right);                                            \
        free(node);                                                                                                    \
    }                                                                                                                  \
                                                                                                                       \
    /* heightRBTreeNode */                                                                                             \
    inline size_t nameMangling3(heightRBTreeNode, KeyType, MappedType)(RBTreeNode(KeyType, MappedType)* self)          \
    {                                                                                                                  \
        if (self == NULL) {                                                                                            \
            return -1;                                                                                                 \
        }                                                                                                              \
        size_t left  = nameMangling3(heightRBTreeNode, KeyType, MappedType)(self->left);                               \
        size_t right = nameMangling3(heightRBTreeNode, KeyType, MappedType)(self->right);                              \
        return (left > right ? left : right) + 1u;                                                                     \
    }                                                                                                                  \
                                                                                                                       \
    /* isRedRBTreeNode */                                                                                              \
    inline bool nameMangling3(isRedRBTreeNode, KeyType, MappedType)(const RBTreeNode(KeyType, MappedType)* self) {     \
        if (self == NULL) {                                                                                            \
            return false;                                                                                              \
        }                                                                                                              \
        return self->color != false;                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    /* isBlackRBTreeNode */                                                                                            \
    inline bool nameMangling3(isBlackRBTreeNode, KeyType, MappedType)(const RBTreeNode(KeyType, MappedType)* self) {   \
        if (self == NULL) {                                                                                            \
            return false;                                                                                              \
        }                                                                                                              \
        return self->color == false;                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    /* preOrderRBTreeNode */                                                                                           \
    inline void nameMangling3(preOrderRBTreeNode, KeyType, MappedType)                                                 \
        (RBTreeNode(KeyType, MappedType)* self, UnaryFunctionRBtree(KeyType, MappedType) func)                         \
    {                                                                                                                  \
        if (self == NULL) {                                                                                            \
            return;                                                                                                    \
        }                                                                                                              \
        func(&self->pair);                                                                                             \
        nameMangling3(preOrderRBTreeNode, KeyType, MappedType)(self->left, func);                                      \
        nameMangling3(preOrderRBTreeNode, KeyType, MappedType)(self->right, func);                                     \
    }                                                                                                                  \
                                                                                                                       \
    /* inOrderRBTreeNode */                                                                                            \
    inline void nameMangling3(inOrderRBTreeNode, KeyType, MappedType)                                                      \
        (RBTreeNode(KeyType, MappedType)* self, UnaryFunctionRBtree(KeyType, MappedType) func)                         \
    {                                                                                                                  \
        if (self == NULL) {                                                                                            \
            return;                                                                                                    \
        }                                                                                                              \
        nameMangling3(inOrderRBTreeNode, KeyType, MappedType)(self->left, func);                                       \
        func(&self->pair);                                                                                             \
        nameMangling3(inOrderRBTreeNode, KeyType, MappedType)(self->right, func);                                      \
    }                                                                                                                  \
                                                                                                                       \
    /* preOrderRBTreeNode */                                                                                           \
    inline void nameMangling3(postOrderRBTreeNode, KeyType, MappedType)                                                \
        (RBTreeNode(KeyType, MappedType)* self, UnaryFunctionRBtree(KeyType, MappedType) func)                         \
    {                                                                                                                  \
        if (self == NULL) {                                                                                            \
            return;                                                                                                    \
        }                                                                                                              \
        nameMangling3(postOrderRBTreeNode, KeyType, MappedType)(self->left, func);                                     \
        nameMangling3(postOrderRBTreeNode, KeyType, MappedType)(self->right, func);                                    \
        func(&self->pair);                                                                                             \
    }                                                                                                                  \
                                                                                                                       \
    /* flipColorsRBTreeNode */                                                                                         \
    inline void nameMangling3(flipColorsRBTreeNode, KeyType, MappedType)(RBTreeNode(KeyType, MappedType)* self)        \
    {                                                                                                                  \
        self->color        = !self->color;                                                                             \
        self->left->color  = !self->left->color;                                                                       \
        self->right->color = !self->right->color;                                                                      \
    }                                                                                                                  \
                                                                                                                       \
    /* rotateLeftRBTreeNode */                                                                                         \
    inline RBTreeNode(KeyType, MappedType)* nameMangling3(rotateLeftRBTreeNode, KeyType, MappedType)                   \
        (RBTreeNode(KeyType, MappedType)* self)                                                                        \
    {                                                                                                                  \
        RBTreeNode(KeyType, MappedType) *right = self->right;                                                          \
        self->right       = right->left;                                                                               \
        right->left       = self;                                                                                      \
        right->color      = self->color;                                                                               \
        self->color       = true; /* red */                                                                            \
                                                                                                                       \
        return right;                                                                                                  \
    }                                                                                                                  \
                                                                                                                       \
    /* rotateRightRBtreeNode */                                                                                        \
    inline RBTreeNode(KeyType, MappedType)* nameMangling3(rotateRightRBtreeNode, KeyType, MappedType)                  \
        (RBTreeNode(KeyType, MappedType)* self)                                                                        \
    {                                                                                                                  \
        RBTreeNode(KeyType, MappedType) *left = self->left;                                                            \
        self->left       = left->right;                                                                                \
        left->right      = self;                                                                                       \
        left->color      = self->color;                                                                                \
        self->color      = true; /* red */                                                                             \
                                                                                                                       \
        return left;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    /* moveRedLeftRBTreeNode */                                                                                        \
    inline RBTreeNode(KeyType, MappedType)* nameMangling3(moveRedLeftRBTreeNode, KeyType, MappedType)                  \
        (RBTreeNode(KeyType, MappedType)* self)                                                                        \
    {                                                                                                                  \
        nameMangling3(flipColorsRBTreeNode, KeyType, MappedType)(self);                                                \
        if (nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->right->left)) {                                  \
            self->right = nameMangling3(rotateRightRBtreeNode, KeyType, MappedType)(self->right);                      \
            self        = nameMangling3(rotateLeftRBTreeNode, KeyType, MappedType)(self);                              \
            nameMangling3(flipColorsRBTreeNode, KeyType, MappedType)(self);                                            \
        }                                                                                                              \
        return self;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    /* moveRedRightRBTreeNode */                                                                                       \
    inline RBTreeNode(KeyType, MappedType)* nameMangling3(moveRedRightRBTreeNode, KeyType, MappedType)                 \
        (RBTreeNode(KeyType, MappedType)* self)                                                                        \
    {                                                                                                                  \
        nameMangling3(flipColorsRBTreeNode, KeyType, MappedType)(self);                                                \
        if (nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->left->left)) {                                   \
            self = nameMangling3(rotateRightRBtreeNode, KeyType, MappedType)(self);                                    \
            nameMangling3(flipColorsRBTreeNode, KeyType, MappedType)(self);                                            \
        }                                                                                                              \
        return self;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    /* balanceRBTreeNode */                                                                                            \
    inline RBTreeNode(KeyType, MappedType)* nameMangling3(balanceRBTreeNode, KeyType, MappedType)                      \
        (RBTreeNode(KeyType, MappedType)* self)                                                                        \
    {                                                                                                                  \
        if (nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->right) &&                                        \
           !nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->left)) {                                         \
            self = nameMangling3(rotateLeftRBTreeNode, KeyType, MappedType)(self);                                     \
        }                                                                                                              \
        if (nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->left) &&                                         \
            nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->left->left)) {                                   \
            self = nameMangling3(rotateRightRBtreeNode, KeyType, MappedType)(self);                                    \
        }                                                                                                              \
        if (nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->left) &&                                         \
            nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->right)) {                                        \
            nameMangling3(flipColorsRBTreeNode, KeyType, MappedType)(self);                                            \
        }                                                                                                              \
        return self;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    /* minRBTreeNode */                                                                                                \
    inline RBTreeNode(KeyType, MappedType)* nameMangling3(minRBTreeNode, KeyType, MappedType)                          \
        (RBTreeNode(KeyType, MappedType)* self)                                                                        \
    {                                                                                                                  \
        if (self == NULL) {                                                                                            \
            return NULL;                                                                                               \
        }                                                                                                              \
        while (self->left != NULL) {                                                                                   \
            self = self->left;                                                                                         \
        }                                                                                                              \
        return self;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    /* maxRBTreeNode */                                                                                                \
    inline RBTreeNode(KeyType, MappedType)* nameMangling3(maxRBTreeNode, KeyType, MappedType)                          \
        (RBTreeNode(KeyType, MappedType)* self)                                                                        \
    {                                                                                                                  \
        if (self == NULL) {                                                                                            \
            return NULL;                                                                                               \
        }                                                                                                              \
        while (self->right != NULL) {                                                                                  \
            self = self->right;                                                                                        \
        }                                                                                                              \
        return self;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    /* insertRBTreeNode */                                                                                             \
    inline RBTreeNode(KeyType, MappedType)* nameMangling3(insertRBTreeNode, KeyType, MappedType)(                      \
        RBTreeNode(KeyType, MappedType)* self, RBTree(KeyType, MappedType)* tree,                                      \
        KeyType   key,  const MappedType* pMapped,                                                                     \
        bool        isReplace                                                                                          \
    )                                                                                                                  \
    {                                                                                                                  \
        if (self == NULL) {                                                                                            \
            ++tree->nodeSize;                                                                                          \
            RBTreeNode(KeyType, MappedType)* node = malloc(sizeof(RBTreeNode(KeyType, MappedType)));                   \
            *node = nameMangling3(createNodeRBTree, KeyType, MappedType)(key, pMapped, true);                          \
                                                                                                                       \
            return node;                                                                                               \
        }                                                                                                              \
                                                                                                                       \
        int compare = tree->compare(key, self->pair.key);                                                              \
        if (compare < 0) {                                                                                             \
            self->left  = nameMangling3(insertRBTreeNode, KeyType, MappedType)                                         \
                              (self->left,  tree, key, pMapped, isReplace);                                            \
        } else if (compare > 0) {                                                                                      \
            self->right = nameMangling3(insertRBTreeNode, KeyType, MappedType)                                         \
                              (self->right, tree, key, pMapped, isReplace);                                            \
        } else {                                                                                                       \
            if (isReplace) {                                                                                           \
                memcpy(&self->pair.mapped, pMapped, sizeof(MappedType));                                               \
            }                                                                                                          \
        }                                                                                                              \
                                                                                                                       \
        if (nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->right) &&                                        \
           !nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->left)) {                                         \
            self = nameMangling3(rotateLeftRBTreeNode, KeyType, MappedType)(self);                                     \
        }                                                                                                              \
                                                                                                                       \
        if (nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->left) &&                                         \
            nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->left->left)) {                                   \
            self = nameMangling3(rotateRightRBtreeNode, KeyType, MappedType)(self);                                    \
        }                                                                                                              \
                                                                                                                       \
        if (nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->left) &&                                         \
            nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->right)) {                                        \
            nameMangling3(flipColorsRBTreeNode, KeyType, MappedType)(self);                                            \
        }                                                                                                              \
                                                                                                                       \
        return self;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    /* eraseMinRBTreeNode */                                                                                           \
    inline RBTreeNode(KeyType, MappedType)* nameMangling3(eraseMinRBTreeNode, KeyType, MappedType)                     \
        (RBTreeNode(KeyType, MappedType)* self, RBTree(KeyType, MappedType)* tree)                                     \
    {                                                                                                                  \
        if (self->left == NULL) {                                                                                      \
            RBTreeNode(KeyType, MappedType)* node = self->right;                                                       \
            --tree->nodeSize;                                                                                          \
            free(self);                                                                                                \
            return node;                                                                                               \
        }                                                                                                              \
        self->left = nameMangling3(eraseMinRBTreeNode, KeyType, MappedType)(self->left, tree);                         \
                                                                                                                       \
        return nameMangling3(balanceRBTreeNode, KeyType, MappedType)(self);                                            \
    }                                                                                                                  \
                                                                                                                       \
    /* eraseMaxRBTreeNode */                                                                                           \
    inline RBTreeNode(KeyType, MappedType)* nameMangling3(eraseMaxRBTreeNode, KeyType, MappedType)                     \
        (RBTreeNode(KeyType, MappedType)* self, RBTree(KeyType, MappedType)* tree)                                     \
    {                                                                                                                  \
        if (self->right == NULL) {                                                                                     \
            RBTreeNode(KeyType, MappedType)* node = self->left;                                                        \
            --tree->nodeSize;                                                                                          \
            free(self);                                                                                                \
            return node;                                                                                               \
        }                                                                                                              \
        self->right = nameMangling3(eraseMaxRBTreeNode, KeyType, MappedType)(self->right, tree);                       \
                                                                                                                       \
        return nameMangling3(balanceRBTreeNode, KeyType, MappedType)(self);                                            \
    }                                                                                                                  \
                                                                                                                       \
    /* eraseRBTreeNode */                                                                                              \
    inline RBTreeNode(KeyType, MappedType)* nameMangling3(eraseRBTreeNode, KeyType, MappedType)                        \
        (RBTreeNode(KeyType, MappedType)* self, RBTree(KeyType, MappedType)* tree, KeyType key)                        \
    {                                                                                                                  \
        if (self == NULL) {                                                                                            \
            return NULL;                                                                                               \
        }                                                                                                              \
        int compare = tree->compare(key, self->pair.key);                                                              \
        if (compare < 0) {                                                                                             \
            if (!nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->left) &&                                    \
                !nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->left->left)) {                              \
                self = nameMangling3(moveRedLeftRBTreeNode, KeyType, MappedType)(self);                                \
            }                                                                                                          \
            self->left = nameMangling3(eraseRBTreeNode, KeyType, MappedType)(self->left, tree, key);                   \
        } else {                                                                                                       \
            if (nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->left)) {                                     \
                self = nameMangling3(rotateRightRBtreeNode, KeyType, MappedType)(self);                                \
            }                                                                                                          \
            if (tree->compare(key, self->pair.key) == 0 && self->right == NULL) {                                      \
                --tree->nodeSize;                                                                                      \
                free(self);                                                                                            \
                return NULL;                                                                                           \
            }                                                                                                          \
            if (!nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->right) &&                                   \
                !nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->right->left)) {                             \
                self = nameMangling3(moveRedRightRBTreeNode, KeyType, MappedType)(self);                               \
            }                                                                                                          \
            if (tree->compare(key, self->pair.key) == 0) {                                                             \
                RBTreeNode(KeyType, MappedType)* node =                                                                \
                    nameMangling3(minRBTreeNode, KeyType, MappedType)(self->right);                                    \
                memcpy(&self->pair.key,    &node->pair.key,    sizeof(KeyType));                                       \
                memcpy(&self->pair.mapped, &node->pair.mapped, sizeof(MappedType));                                    \
                self->right       = nameMangling3(eraseMinRBTreeNode, KeyType, MappedType)(self->right, tree);         \
            } else {                                                                                                   \
                self->right = nameMangling3(eraseRBTreeNode, KeyType, MappedType)(self->right, tree, key);             \
            }                                                                                                          \
        }                                                                                                              \
                                                                                                                       \
        return nameMangling3(balanceRBTreeNode, KeyType, MappedType)(self);                                            \
    }                                                                                                                  \
                                                                                                                       \
    /************** Tree Function  **************/                                                                     \
                                                                                                                       \
    /* createRBTree */                                                                                                 \
    inline RBTree(KeyType, MappedType) linkPRBTreeName(createRBTree, KeyType, MappedType)                              \
        (CompareRBTree(KeyType, MappedType) compare)                                                                   \
    {                                                                                                                  \
        RBTree(KeyType, MappedType) result = { compare, NULL, 0 };                                                     \
        return result;                                                                                                 \
    }                                                                                                                  \
                                                                                                                       \
    /* destroyRBTree */                                                                                                \
    inline void linkPRBTreeName(destroyRBTree, KeyType, MappedType)(RBTree(KeyType, MappedType)* self)                 \
    {                                                                                                                  \
        if (self->root) {                                                                                              \
            nameMangling3(destroyRBTreeNode, KeyType, MappedType)(self->root);                                         \
        }                                                                                                              \
        self->root     = NULL;                                                                                         \
        self->nodeSize = 0;                                                                                            \
    }                                                                                                                  \
                                                                                                                       \
    /* sizeRBTree */                                                                                                   \
    inline size_t linkPRBTreeName(sizeRBTree, KeyType, MappedType)(RBTree(KeyType, MappedType)* self)                  \
    {                                                                                                                  \
        return self->nodeSize;                                                                                         \
    }                                                                                                                  \
                                                                                                                       \
    /* isEmptyRBTree */                                                                                                \
    inline bool linkPRBTreeName(isEmptyRBTree, KeyType, MappedType)(RBTree(KeyType, MappedType)* self)                 \
    {                                                                                                                  \
        return self->root == NULL;                                                                                     \
    }                                                                                                                  \
                                                                                                                       \
    /* heightRBTree */                                                                                                 \
    inline size_t linkPRBTreeName(heightRBTree, KeyType, MappedType)(RBTree(KeyType, MappedType)* self)                \
    {                                                                                                                  \
        return nameMangling3(heightRBTreeNode, KeyType, MappedType)(self->root);                                       \
    }                                                                                                                  \
                                                                                                                       \
    /* preOrderRBTree */                                                                                               \
    inline void linkPRBTreeName(preOrderRBTree, KeyType, MappedType)                                                   \
        (RBTree(KeyType, MappedType)* self, UnaryFunctionRBtree(KeyType, MappedType) func)                             \
    {                                                                                                                  \
        if (self->root == NULL) {                                                                                      \
            return;                                                                                                    \
        }                                                                                                              \
        nameMangling3(preOrderRBTreeNode, KeyType, MappedType)(self->root, func);                                      \
    }                                                                                                                  \
                                                                                                                       \
    /* inOrderRBTree */                                                                                                \
    inline void linkPRBTreeName(inOrderRBTree, KeyType, MappedType)                                                    \
        (RBTree(KeyType, MappedType)* self, UnaryFunctionRBtree(KeyType, MappedType) func)                             \
    {                                                                                                                  \
        if (self->root == NULL) {                                                                                      \
            return;                                                                                                    \
        }                                                                                                              \
        nameMangling3(inOrderRBTreeNode, KeyType, MappedType)(self->root, func);                                       \
    }                                                                                                                  \
    /* postOrderRBTree */                                                                                              \
    inline void linkPRBTreeName(postOrderRBTree, KeyType, MappedType)                                                  \
        (RBTree(KeyType, MappedType)* self, UnaryFunctionRBtree(KeyType, MappedType) func)                             \
    {                                                                                                                  \
        if (self->root == NULL) {                                                                                      \
            return;                                                                                                    \
        }                                                                                                              \
        nameMangling3(postOrderRBTreeNode, KeyType, MappedType)(self->root, func);                                     \
    }                                                                                                                  \
                                                                                                                       \
    /* findRBTree */                                                                                                   \
    inline PairRBTree(KeyType, MappedType)* linkPRBTreeName(findRBTree, KeyType, MappedType)                           \
        (RBTree(KeyType, MappedType)* self, KeyType key)                                                               \
    {                                                                                                                  \
        RBTreeNode(KeyType, MappedType) *node = self->root;                                                            \
        while (node != NULL) {                                                                                         \
            int compare = self->compare(key, node->pair.key);                                                          \
            if (compare == 0) {                                                                                        \
                return &node->pair;                                                                                    \
            } else if (compare < 0) {                                                                                  \
                node = node->left;                                                                                     \
            } else {                                                                                                   \
                node = node->right;                                                                                    \
            }                                                                                                          \
        }                                                                                                              \
                                                                                                                       \
        return NULL;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    /* minRBTree */                                                                                                    \
    inline PairRBTree(KeyType, MappedType)* linkPRBTreeName(minRBTree, KeyType, MappedType)                            \
        (RBTree(KeyType, MappedType)* self)                                                                            \
    {                                                                                                                  \
        RBTreeNode(KeyType, MappedType)* result = nameMangling3(minRBTreeNode, KeyType, MappedType)(self->root);       \
        if (result == NULL) {                                                                                          \
            return NULL;                                                                                               \
        } else {                                                                                                       \
            return &result->pair;                                                                                      \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    /* maxRBTree */                                                                                                    \
    inline PairRBTree(KeyType, MappedType)* linkPRBTreeName(maxRBTree, KeyType, MappedType)                            \
        (RBTree(KeyType, MappedType)* self)                                                                            \
    {                                                                                                                  \
        RBTreeNode(KeyType, MappedType)* result = nameMangling3(maxRBTreeNode, KeyType, MappedType)(self->root);       \
        if (result == NULL) {                                                                                          \
            return NULL;                                                                                               \
        } else {                                                                                                       \
            return &result->pair;                                                                                      \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    /* eraseMinRBTree */                                                                                               \
    inline void linkPRBTreeName(eraseMinRBTree, KeyType, MappedType)(RBTree(KeyType, MappedType)* self)                \
    {                                                                                                                  \
        if (self->root == NULL) {                                                                                      \
            return;                                                                                                    \
        }                                                                                                              \
        self->root = nameMangling3(eraseMinRBTreeNode, KeyType, MappedType)(self->root, self);                         \
    }                                                                                                                  \
                                                                                                                       \
    /* eraseMaxRBTree */                                                                                               \
    inline void linkPRBTreeName(eraseMaxRBTree, KeyType, MappedType)(RBTree(KeyType, MappedType)* self)                \
    {                                                                                                                  \
        if (self->root == NULL) {                                                                                      \
            return;                                                                                                    \
        }                                                                                                              \
        self->root = nameMangling3(eraseMaxRBTreeNode, KeyType, MappedType)(self->root, self);                         \
    }                                                                                                                  \
                                                                                                                       \
    /* containsRBTree */                                                                                               \
    inline bool linkPRBTreeName(containsRBTree, KeyType, MappedType)(RBTree(KeyType, MappedType)* self, KeyType key)   \
    {                                                                                                                  \
        return linkPRBTreeName(findRBTree, KeyType, MappedType)(self, key) != NULL;                                    \
    }                                                                                                                  \
                                                                                                                       \
    /* lowerBoundRBTree */                                                                                             \
    inline RBTreeNode(KeyType, MappedType)* linkPRBTreeName(lowerBoundRBTree, KeyType, MappedType)                     \
        (RBTree(KeyType, MappedType)* self, KeyType key)                                                               \
    {                                                                                                                  \
        RBTreeNode(KeyType, MappedType)* node = self->root;                                                            \
        while (node != NULL) {                                                                                         \
            int compare = self->compare(key, node->pair.key);                                                          \
            if (compare >= 0) {                                                                                        \
                return &node;                                                                                          \
            } else  {                                                                                                  \
                node = node->left;                                                                                     \
            }                                                                                                          \
        }                                                                                                              \
                                                                                                                       \
        return NULL;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    /* upperBoundRBTree */                                                                                             \
    inline RBTreeNode(KeyType, MappedType)* linkPRBTreeName(upperBoundRBTree, KeyType, MappedType)                     \
        (RBTree(KeyType, MappedType)* self, KeyType key)                                                               \
    {                                                                                                                  \
        RBTreeNode(KeyType, MappedType)* node = self->root;                                                            \
        while (node != NULL) {                                                                                         \
            int compare = self->compare(key, node->pair.key);                                                          \
            if (compare > 0) {                                                                                         \
                return &node;                                                                                          \
            } else  {                                                                                                  \
                node = node->right;                                                                                    \
            }                                                                                                          \
        }                                                                                                              \
                                                                                                                       \
        return NULL;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    /* insertRBTree */                                                                                                 \
    inline void linkPRBTreeName(insertRBTree, KeyType, MappedType)                                                     \
        (RBTree(KeyType, MappedType)* self, KeyType key, const MappedType* pMapped, bool isReplace)                    \
    {                                                                                                                  \
        self->root = nameMangling3(insertRBTreeNode, KeyType, MappedType)(self->root, self, key, pMapped, isReplace);  \
    }                                                                                                                  \
                                                                                                                       \
    /* insertArrayRBTree */                                                                                            \
    inline void linkPRBTreeName(insertArrayRBTree, KeyType, MappedType)                                                \
        (RBTree(KeyType, MappedType)* self, const PairRBTree(KeyType, MappedType)* array, size_t size, bool isReplace) \
    {                                                                                                                  \
        while (size--) {                                                                                               \
            linkPRBTreeName(insertRBTree, KeyType, MappedType)(self, array->key, &array->mapped, isReplace);           \
            ++array;                                                                                                   \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    /* eraseRBTree */                                                                                                  \
    inline bool linkPRBTreeName(eraseRBTree, KeyType, MappedType)(RBTree(KeyType, MappedType)* self, KeyType key)      \
    {                                                                                                                  \
        if (self->root == NULL) {                                                                                      \
            return false;                                                                                              \
        }                                                                                                              \
                                                                                                                       \
        if (!linkPRBTreeName(containsRBTree, KeyType, MappedType)(self, key)) {                                        \
            return false;                                                                                              \
        }                                                                                                              \
                                                                                                                       \
        if (!nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->root->left) &&                                  \
            !nameMangling3(isRedRBTreeNode, KeyType, MappedType)(self->root->right)) {                                 \
            self->root->color = true; /* red */                                                                        \
        }                                                                                                              \
                                                                                                                       \
        size_t oldSize = linkPRBTreeName(sizeRBTree, KeyType, MappedType)(self);                                       \
        self->root = nameMangling3(eraseRBTreeNode, KeyType, MappedType)(self->root, self, key);                       \
        if (!linkPRBTreeName(isEmptyRBTree, KeyType, MappedType)(self)) {                                              \
            self->root->color = false; /* black */                                                                     \
        }                                                                                                              \
                                                                                                                       \
        return linkPRBTreeName(sizeRBTree, KeyType, MappedType)(self) != oldSize;                                      \
    }

#ifndef TypesPackRBTree
#    define TypesPackRBTree() 0 // empty
#endif

#define makeRBTreeDecl(count, ...) macroForeachBinary(count, DeclRBTree, __VA_ARGS__)

macroTransmit(makeRBTreeDecl, TypesPackRBTree());

#define TypesPackPRBTree() packMakeManglingTypePack2(PRBTree, TypesPackRBTree)

#define createRBTree(KeyType, MappedType)                 linkPRBTreeName(createRBTree,      KeyType, MappedType)
#define destroyRBTree(pTree)                              packReloadCall1(destroyRBTree,     pTree,   TypesPackPRBTree)(pTree)
#define sizeRBTree(pTree)                                 packReloadCall1(sizeRBTree,        pTree,   TypesPackPRBTree)(pTree)
#define isEmptyRBTree(pTree)                              packReloadCall1(isEmptyRBTree,     pTree,   TypesPackPRBTree)(pTree)
#define heightRBTree(pTree)                               packReloadCall1(heightRBTree,      pTree,   TypesPackPRBTree)(pTree)
#define preOrderRBTree(pTree, unaryFunc)                  packReloadCall1(preOrderRBTree,    pTree,   TypesPackPRBTree)(pTree, unaryFunc)
#define inOrderRBTree(pTree, unaryFunc)                   packReloadCall1(inOrderRBTree,     pTree,   TypesPackPRBTree)(pTree, unaryFunc)
#define postOrderRBTree(pTree, unaryFunc)                 packReloadCall1(postOrderRBTree,   pTree,   TypesPackPRBTree)(pTree, unaryFunc)
#define findRBTree(pTree, key)                            packReloadCall1(findRBTree,        pTree,   TypesPackPRBTree)(pTree, key)
#define minRBTree(pTree)                                  packReloadCall1(minRBTree,         pTree,   TypesPackPRBTree)(pTree)
#define maxRBTree(pTree)                                  packReloadCall1(maxRBTree,         pTree,   TypesPackPRBTree)(pTree)
#define eraseMinRBTree(pTree)                             packReloadCall1(eraseMinRBTree,    pTree,   TypesPackPRBTree)(pTree)
#define eraseMaxRBTree(pTree)                             packReloadCall1(eraseMaxRBTree,    pTree,   TypesPackPRBTree)(pTree)
#define containsRBTree(pTree, key)                        packReloadCall1(containsRBTree,    pTree,   TypesPackPRBTree)(pTree, key)
#define lowerBoundRBTree(pTree, key)                      packReloadCall1(lowerBoundRBTree,  pTree,   TypesPackPRBTree)(pTree, key)
#define upperBoundRBTree(pTree, key)                      packReloadCall1(upperBoundRBTree,  pTree,   TypesPackPRBTree)(pTree, key)
#define insertRBTree(pTree, key, value, isReplace)        packReloadCall1(insertRBTree,      pTree,   TypesPackPRBTree)(pTree, key,   value, isReplace)
#define insertArrayRBTree(pTree, array, count, isReplace) packReloadCall1(insertArrayRBTree, pTree,   TypesPackPRBTree)(pTree, array, count, isReplace)
#define eraseRBTree(pTree, key)                           packReloadCall1(eraseRBTree,       pTree,   TypesPackPRBTree)(pTree, key)
