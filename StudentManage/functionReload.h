#pragma once

#include "macroBase.h"
#include "macroLoop.h"
#include "macroList.h"

#define functionMangling1(funcName, Type) funcName ## _ ## Type
#define functionMangling2(funcName, Type1, Type2) funcName ## _ ## Type1 ## _ ## Type2

#define makeGenericArgsPTuplePair1(Type)		   Type: ((TupleType1(Type)*)(NULL))
#define makeGenericArgsPTuplePair2(Type1, Type2)   TupleType1(Type1)*: ((TupleType2(Type1, Type2)*)(NULL))

#define makeTypeFunctionPair1(funcName, Type)		  Type:	  functionMangling1(funcName, Type)
#define makeTypeFunctionPair2(funcName, Type1, Type2) TupleType2(Type1, Type2)*: functionMangling2(funcName, Type1, Type2)

#define makePTuple1(value, count, ...) \
    _Generic((value), macroUnfoldUnaryCall(count, separatorComma, makeGenericArgsPTuplePair1, __VA_ARGS__))

#define makePTuple2GenericList(value, Type1, count, ...) \
    
#define makePTuple2(value1, value2, count, ...) \
    _Generic((value1), macroUnfoldCall(count, separatorComma, , 1, value2, __VA_ARGS__))

#define reloadCall1(funcName, reloadArg, count, ...) \
    _Generic((reloadArg), macroUnfoldFixed1BinaryCall(count, separatorComma, makeTypeFunctionPair1, funcName, __VA_ARGS__))

#define reloadCall2()

#define packMakeCallTuple2(getTypesList) macroTransmit(makeCallTuple2, getTypesList())

#define packReloadCall1(funcName, reloadArg, typesPack) \
    macroTransmit(reloadCall1, funcName, reloadArg, typesPack())

