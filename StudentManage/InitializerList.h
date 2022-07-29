#pragma once

#include <stddef.h>

#include "macro_meta.h"



#define InitializerList(ValueType) nameMangling2(InitializerList, ValueType)

#define DeclInitializerList(ValueType) \
    typedef struct {				   \
        const ValueType* first;		   \
        const size_t	 size;         \
    } InitializerList(ValueType);

#ifndef TypesPackInitializerList
#	define TypesPackInitializerList() 0
#endif

#define makeInitializerListDecl(count, ...) macroForeachUnary(count, DeclInitializerList, __VA_ARGS__)

macroTransmit(makeInitializerListDecl, TypesPackInitializerList());

#define createInitializerList(ValueType, ...)					 \
    (InitializerList(ValueType)){								 \
        (ValueType[]){ __VA_ARGS__ },							 \
        sizeof((ValueType[]){ __VA_ARGS__ }) / sizeof(ValueType) \
    }

#define initializerListCall(func, ValueType, ...)       \
    func(createInitializerList(ValueType, __VA_ARGS__))
