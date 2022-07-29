#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "macro_meta.h"

/****************************************************** head only  ******************************************************/

#define Vector(ElementType)                    nameMangling2(Vector,              ElementType)
#define PVector(ElementType)                   nameMangling2(PVector,             ElementType)
#define CompareVector(ElementType)             nameMangling2(CompareVector,       ElementType)
#define UnaryFunctionVector(ElementType)       nameMangling2(UnaryFunctionVector, ElementType)

#define linkPVectorName(mangling, ElementType) nameMangling3(mangling, PVector, ElementType)

#define DeclVector(ElementType)                                                                                          \
    typedef int  (*CompareVector(ElementType))      (const ElementType* left, const ElementType* right);                 \
    typedef void (*UnaryFunctionVector(ElementType))(ElementType*  element);                                             \
    typedef struct nameMangling2(Vector, ElementType) {                                                                  \
        ElementType* data;                                                                                               \
        size_t       size;                                                                                               \
        size_t       capacity;                                                                                           \
    } Vector(ElementType), *PVector(ElementType);                                                                        \
                                                                                                                         \
    /* createVector */                                                                                                   \
    inline Vector(ElementType) linkPVectorName(createVector, ElementType)(size_t count, const ElementType* pValue)       \
    {                                                                                                                    \
        Vector(ElementType) result;                                                                                      \
        result.capacity = sizeof(ElementType) <= 1 ? 16                                                                  \
                        : sizeof(ElementType) <= 2 ? 8                                                                   \
                        : sizeof(ElementType) <= 4 ? 4                                                                   \
                        : sizeof(ElementType) <= 8 ? 2                                                                   \
                        : 1;                                                                                             \
        while (result.capacity < count) {                                                                                \
            result.capacity <<= 1;                                                                                       \
        }                                                                                                                \
        result.data = malloc(result.capacity * sizeof(ElementType));                                                     \
        if (pValue != NULL) {                                                                                            \
            for (size_t i = 0; i < count; ++i) {                                                                         \
                memcpy(result.data + i, pValue, sizeof(ElementType));                                                    \
            }                                                                                                            \
        } else {                                                                                                         \
            memset(result.data, 0, result.capacity * sizeof(ElementType));                                               \
        }                                                                                                                \
        result.size = count;                                                                                             \
                                                                                                                         \
        return result;                                                                                                   \
    }                                                                                                                    \
                                                                                                                         \
    /* destroyVector */                                                                                                  \
    inline void linkPVectorName(destroyVector, ElementType)(Vector(ElementType)* self)                                   \
    {                                                                                                                    \
        free(self->data);                                                                                                \
        self->data     = NULL;                                                                                           \
        self->size     = 0;                                                                                              \
        self->capacity = 0;                                                                                              \
    }                                                                                                                    \
                                                                                                                         \
    /* capacityVector */                                                                                                 \
    inline size_t linkPVectorName(capacityVector, ElementType)(Vector(ElementType)* self)                                \
    {                                                                                                                    \
        return self->capacity;                                                                                           \
    }                                                                                                                    \
                                                                                                                         \
    /* sizeVector */                                                                                                     \
    inline size_t linkPVectorName(sizeVector, ElementType)(Vector(ElementType)* self)                                    \
    {                                                                                                                    \
        return self->size;                                                                                               \
    }                                                                                                                    \
                                                                                                                         \
    /* atVector */                                                                                                       \
    inline ElementType* linkPVectorName(atVector, ElementType)(Vector(ElementType)* self, size_t index)                  \
    {                                                                                                                    \
        return self->data + index;                                                                                       \
    }                                                                                                                    \
                                                                                                                         \
    /* frontVector */                                                                                                    \
    inline ElementType* linkPVectorName(frontVector, ElementType)(Vector(ElementType)* self)                             \
    {                                                                                                                    \
        return self->data;                                                                                               \
    }                                                                                                                    \
                                                                                                                         \
    /* backVector */                                                                                                     \
    inline ElementType* linkPVectorName(backVector, ElementType)(Vector(ElementType)* self)                              \
    {                                                                                                                    \
        return self->data + self->size - 1;                                                                              \
    }                                                                                                                    \
                                                                                                                         \
    /* dataVector */                                                                                                     \
    inline ElementType* linkPVectorName(dataVector, ElementType)(Vector(ElementType)* self)                              \
    {                                                                                                                    \
        return self->data;                                                                                               \
    }                                                                                                                    \
                                                                                                                         \
    /* foreachVector */                                                                                                  \
    inline void linkPVectorName(foreachVector, ElementType)                                                              \
        (Vector(ElementType)* self, UnaryFunctionVector(ElementType) func, bool isReverse)                               \
    {                                                                                                                    \
        if (isReverse) {                                                                                                 \
            for (size_t i = self->size; i > 0; --i) {                                                                    \
                func(linkPVectorName(atVector, ElementType)(self, i - 1));                                               \
            }                                                                                                            \
        } else {                                                                                                         \
            for (size_t i = 0; i < self->size; ++i) {                                                                    \
                func(linkPVectorName(atVector, ElementType)(self, i));                                                   \
            }                                                                                                            \
        }                                                                                                                \
    }                                                                                                                    \
                                                                                                                         \
    /* reserveVector */                                                                                                  \
    inline void linkPVectorName(reserveVector, ElementType)(Vector(ElementType)* self, size_t size)                      \
    {                                                                                                                    \
        if (size > self->capacity) {                                                                                     \
            self->data     = realloc(self->data, size * sizeof(ElementType));                                            \
            self->capacity = size;                                                                                       \
        }                                                                                                                \
    }                                                                                                                    \
                                                                                                                         \
    /* resizeVector */                                                                                                   \
    inline void linkPVectorName(resizeVector, ElementType)(Vector(ElementType)* self, size_t size)                       \
    {                                                                                                                    \
        if (size > self->capacity) {                                                                                     \
            linkPVectorName(reserveVector, ElementType)(self, size);                                                     \
        }                                                                                                                \
        if (size > self->size) {                                                                                         \
            memset(self->data + self->size, 0, (size - self->size) * sizeof(ElementType));                               \
        }                                                                                                                \
        self->size = size;                                                                                               \
    }                                                                                                                    \
                                                                                                                         \
    /* pushBackVector */                                                                                                 \
    inline void linkPVectorName(pushBackVector, ElementType)(Vector(ElementType)* self, const ElementType* pValue)       \
    {                                                                                                                    \
        if (self->size == self->capacity) {                                                                              \
            if (self->capacity != 0) {                                                                                   \
                self->capacity <<= 1;                                                                                    \
                self->data = realloc(self->data, self->capacity * sizeof(ElementType));                                  \
            } else {                                                                                                     \
                self->capacity = sizeof(ElementType) <= 1 ? 16                                                           \
                               : sizeof(ElementType) <= 2 ? 8                                                            \
                               : sizeof(ElementType) <= 4 ? 4                                                            \
                               : sizeof(ElementType) <= 8 ? 2                                                            \
                               : 1;                                                                                      \
                self->data = malloc(self->capacity * sizeof(ElementType));                                               \
            }                                                                                                            \
        }                                                                                                                \
                                                                                                                         \
        memcpy(self->data + self->size++, pValue, sizeof(ElementType));                                                  \
    }                                                                                                                    \
                                                                                                                         \
    /* popBackVector */                                                                                                  \
    inline void linkPVectorName(popBackVector, ElementType)(Vector(ElementType)* self)                                   \
    {                                                                                                                    \
        self->size--;                                                                                                    \
    }                                                                                                                    \
                                                                                                                         \
    /* insertVector */                                                                                                   \
    inline void linkPVectorName(insertVector, ElementType)                                                               \
        (Vector(ElementType)* self, size_t index, const ElementType* pValue)                                             \
    {                                                                                                                    \
        if (self->capacity == 0) {                                                                                       \
            linkPVectorName(pushBackVector, ElementType)(self, pValue);                                                  \
            return;                                                                                                      \
        }                                                                                                                \
        if (self->size == self->capacity) {                                                                              \
            self->capacity <<= 1;                                                                                        \
            self->data       = realloc(self->data, self->capacity * sizeof(ElementType));                                \
        }                                                                                                                \
                                                                                                                         \
        for (size_t i = self->size; i > index; --i) {                                                                    \
            memcpy(self->data + i, self->data + i - 1, sizeof(ElementType));                                             \
        }                                                                                                                \
                                                                                                                         \
        memcpy(self->data + index, pValue, sizeof(ElementType));                                                         \
        self->size++;                                                                                                    \
    }                                                                                                                    \
                                                                                                                         \
    /* insertArrayVector */                                                                                              \
    inline void linkPVectorName(insertArrayVector, ElementType)                                                          \
        (Vector(ElementType)* self, size_t index, const ElementType* array, size_t size)                                 \
    {                                                                                                                    \
        if (self->capacity == 0) {                                                                                       \
            self->capacity = sizeof(ElementType) <= 1 ? 16                                                               \
                           : sizeof(ElementType) <= 2 ? 8                                                                \
                           : sizeof(ElementType) <= 4 ? 4                                                                \
                           : sizeof(ElementType) <= 8 ? 2                                                                \
                           : 1;                                                                                          \
            while (self->capacity < size) {                                                                              \
                self->capacity <<= 1;                                                                                    \
            }                                                                                                            \
            self->data     = malloc(self->capacity * sizeof(ElementType));                                               \
        } else if (self->size + size > self->capacity) {                                                                 \
            while (self->capacity < self->size + size) {                                                                 \
                self->capacity <<= 1;                                                                                    \
            }                                                                                                            \
            self->data     = realloc(self->data, self->capacity * sizeof(ElementType));                                  \
        }                                                                                                                \
                                                                                                                         \
        for (size_t i = self->size + size - 1; i > index; --i) {                                                         \
            memcpy(self->data + i, self->data + i - size, sizeof(ElementType));                                          \
        }                                                                                                                \
                                                                                                                         \
        memcpy(self->data + index, array, size * sizeof(ElementType));                                                   \
        self->size += size;                                                                                              \
    }                                                                                                                    \
                                                                                                                         \
    /* eraseVector */                                                                                                    \
    inline void linkPVectorName(eraseVector, ElementType)(Vector(ElementType)* self, size_t index)                       \
    {                                                                                                                    \
        for (size_t i = index; i < self->size - 1; ++i) {                                                                \
            memcpy(self->data + i, self->data + i + 1, sizeof(ElementType));                                             \
        }                                                                                                                \
                                                                                                                         \
        self->size--;                                                                                                    \
    }                                                                                                                    \
                                                                                                                         \
    inline void linkPVectorName(sortVector, ElementType)(Vector(ElementType)* self, CompareVector(ElementType) compare)  \
    {                                                                                                                    \
        qsort(self->data, self->size, sizeof(ElementType), compare);                                                     \
    }

#ifndef TypesPackVector
#   define TypesPackVector() 0
#endif 

#define makeVectorDecl(count, ...) macroForeachUnary(count, DeclVector, __VA_ARGS__)
#define TypePackPVector()          packMakeManglingTypePack1(PVector, TypesPackVector)

macroTransmit(makeVectorDecl, TypesPackVector());

#define createVector(ElementType)                      linkPVectorName(createVector,      ElementType)
#define destroyVector(pVector)                         packReloadCall1(destroyVector,     pVector, TypePackPVector)(pVector)
#define capacityVector(pVector)                        packReloadCall1(capacityVector,    pVector, TypePackPVector)(pVector)
#define sizeVector(pVector)                            packReloadCall1(sizeVector,        pVector, TypePackPVector)(pVector)
#define atVector(pVector, index)                       packReloadCall1(atVector,          pVector, TypePackPVector)(pVector, index)
#define frontVector(pVector)                           packReloadCall1(frontVector,       pVector, TypePackPVector)(pVector)
#define backVector(pVector)                            packReloadCall1(backVector,        pVector, TypePackPVector)(pVector)
#define dataVector(pVector)                            packReloadCall1(dataVector,        pVector, TypePackPVector)(pVector)
#define foreachVector(pVector, unaryFunc, isReverse)   packReloadCall1(foreachVector,     pVector, TypePackPVector)(pVector, unaryFunc, isReverse)
#define reserveVector(pVector, size)                   packReloadCall1(reserveVector,     pVector, TypePackPVector)(pVector, size)
#define resizeVector(pVector, size)                    packReloadCall1(resizeVector,      pVector, TypePackPVector)(pVector, size)
#define pushBackVector(pVector, pValue)                packReloadCall1(pushBackVector,    pVector, TypePackPVector)(pVector, pValue)
#define popBackVector(pVector)                         packReloadCall1(popBackVector,     pVector, TypePackPVector)(pVector)
#define insertVector(pVector, index, pValue)           packReloadCall1(insertVector,      pVector, TypePackPVector)(pVector, index, pValue)
#define insertArrayVector(pVector, index, array, size) packReloadCall1(insertArrayVector, pVector, TypePackPVector)(pVector, index, array, size)
#define eraseVector(pVector, index)                    packReloadCall1(eraseVector,       pVector, TypePackPVector)(pVector, index)
#define sortVector(pVector, compare)                   packReloadCall1(sortVector,        pVector, TypePackPVector)(pVector, compare)
