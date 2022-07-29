#pragma once

#include "macro_meta.h"


#define Vector(ElementType)                    nameMangling2(Vector,              ElementType)
#define PVector(ElementType)                   nameMangling2(PVector,             ElementType)
#define CompareVector(ElementType)             nameMangling2(CompareVector,       ElementType)
#define UnaryFunctionVector(ElementType)       nameMangling2(UnaryFunctionVector, ElementType)

#define PriorDeclVector(ElementType)                                                                                     \
    typedef int  (*CompareVector(ElementType))      (const ElementType* left, const ElementType* right);                 \
    typedef void (*UnaryFunctionVector(ElementType))(int*  element);                                                     \
    typedef struct nameMangling2(Vector, ElementType) Vector(ElementType), *PVector(ElementType);
