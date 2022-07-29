#pragma once

#include "macroLoop.h"
#include "macroList.h"
#include "macroBranch.h"

#define TupleType1(Type)  Tuple_ ## Type
#define PTupleType1(Type)  PTuple_ ## Type
#define DeclTuple1(Type) \
    typedef struct {     \
        Type value;      \
    } TupleType1(Type), *PTupleType1(Type)

#define TupleType2(Type1, Type2)  Tuple_ ## Type1 ## _ ## Type2
#define PTupleType2(Type1, Type2)  PTuple_ ## Type1 ## _ ## Type2
#define DeclTuple2(Type1, Type2) \
    DeclTuple1(Type2);           \
    typedef struct {             \
        Type1             value; \
        TupleType1(Type2) next;  \
    } TupleType2(Type1, Type2), *PTupleType2(Type1, Type2)

#define TupleType3(Type1, Type2, Type3)  Tuple_ ## Type1 ## _ ## Type2 ## _ ## Type3
#define PTupleType3(Type1, Type2, Type3)  PTuple_ ## Type1 ## _ ## Type2 ## _ ## Type3
#define DeclTuple3(Type1, Type2, Type3) \
    DeclTuple2(Type2, Type3);           \
    typedef struct {                    \
        Type1                    value; \
        TupleType2(Type2, Type3) next;  \
    } TupleType3(Type1, Type2, Type3), *PTupleType3(Type1, Type2, Type3)

#define macroLinkToken2(left, right) left ## right
#define macroLinkToken3(a, b, c) a ## b ## c
#define macroLinkToken4(a, b, c, d) a ## b ## c ## d
#define macroLinkToken5(a, b, c, d, e) a ## b ## c ## d ## e
#define macroLinkToken6(a, b, c, d, e, f) a ## b ## c ## d ## e ## f
#define macroLinkToken7(a, b, c, d, e, f, g) a ## b ## c ## d ## e ## f ## g
#define macroLinkToken8(a, b, c, d, e, f, g, h) a ## b ## c ## d ## e ## f ## g ## h

#define makeGenericPair(Type, exp) Type: exp

#define separatorComma() ,
#define separatorSemicolon() ;
#define separatorSpace()

#define macroTransmit(callable, ...) callable(__VA_ARGS__)
#define macroTransmit0(callable, ...) callable(__VA_ARGS__)
#define macroTransmit1(callable, ...) callable(__VA_ARGS__)
#define macroTransmit2(callable, ...) callable(__VA_ARGS__)
#define macroTransmit3(callable, ...) callable(__VA_ARGS__)
#define macroTransmit4(callable, ...) callable(__VA_ARGS__)
#define macroTransmit5(callable, ...) callable(__VA_ARGS__)
#define macroTransmit6(callable, ...) callable(__VA_ARGS__)
#define macroTransmit7(callable, ...) callable(__VA_ARGS__)
#define macroTransmit8(callable, ...) callable(__VA_ARGS__)
#define macroTransmit9(callable, ...) callable(__VA_ARGS__)
#define macroTransmit10(callable, ...) callable(__VA_ARGS__)
#define macroTransmit11(callable, ...) callable(__VA_ARGS__)
#define macroTransmit12(callable, ...) callable(__VA_ARGS__)
#define macroTransmit13(callable, ...) callable(__VA_ARGS__)
#define macroTransmit14(callable, ...) callable(__VA_ARGS__)
#define macroTransmit15(callable, ...) callable(__VA_ARGS__)
#define macroTransmit16(callable, ...) callable(__VA_ARGS__)
#define macroTransmit17(callable, ...) callable(__VA_ARGS__)
#define macroTransmit18(callable, ...) callable(__VA_ARGS__)
#define macroTransmit19(callable, ...) callable(__VA_ARGS__)
#define macroTransmit20(callable, ...) callable(__VA_ARGS__)
#define macroTransmit21(callable, ...) callable(__VA_ARGS__)
#define macroTransmit22(callable, ...) callable(__VA_ARGS__)
#define macroTransmit23(callable, ...) callable(__VA_ARGS__)
#define macroTransmit24(callable, ...) callable(__VA_ARGS__)
#define macroTransmit25(callable, ...) callable(__VA_ARGS__)
#define macroTransmit26(callable, ...) callable(__VA_ARGS__)
#define macroTransmit27(callable, ...) callable(__VA_ARGS__)
#define macroTransmit28(callable, ...) callable(__VA_ARGS__)
#define macroTransmit29(callable, ...) callable(__VA_ARGS__)
#define macroTransmit30(callable, ...) callable(__VA_ARGS__)
#define macroTransmit31(callable, ...) callable(__VA_ARGS__)
#define macroTransmit32(callable, ...) callable(__VA_ARGS__)

#define forwardTransmit1(a) a
#define forwardTransmit(...) __VA_ARGS__

#define nameMangling2(mangling, a)       mangling ## _ ## a
#define nameMangling3(mangling, a, b)    mangling ## _ ## a ## _ ## b
#define nameMangling4(mangling, a, b, c) mangling ## _ ## a ## _ ## b ## _ ## c
#define nameMangling5(mangling, a, b, c, d) mangling ## _ ## a ## _ ## b ## _ ## c ## _ ## d
#define nameMangling6(mangling, a, b, c, d, e) mangling ## _ ## a ## _ ## b ## _ ## c ## _ ## d ## _ ## e
#define nameMangling7(mangling, a, b, c, d, e, f) mangling ## _ ## a ## _ ## b ## _ ## c ## _ ## d ## _ ## e ## _ ## f


#define macroGetList2(arg1, arg2, ...) arg2

#define macroProbe(x) x, 1
#define macroCheck(...)     macroGetList2(__VA_ARGS__, 0)
#define macroIsListEmpty(x) macroCheck(macroLinkToken(macroTransmit(macroLinkToken, macroIsListEmpty_, x), 0))
#define macroIsListEmpty_ macroProbe()


#define makepTuplePack2(count, ...) \
    count macroTransmit(macroIf, count)(separatorComma()) macroTransmit(macroUnfoldBinaryCall, count, separatorComma, PTupleType2, __VA_ARGS__)

#define packMakePTuplePack2(TypePack) macroTransmit0(makepTuplePack2, TypePack())

#define DeclTuples2(count, ...) \
    macroForeachBinary(count, DeclTuple2, __VA_ARGS__)

#define PackDeclTuples2(TypePack) macroTransmit0(DeclTuples2, TypePack())


#define makeManglingTypePack1(unaryManglingFunc, count, ...) \
    count macroTransmit(macroIf, count)(separatorComma()) \
    macroTransmit0(macroUnfoldUnaryCall, count, separatorComma, unaryManglingFunc, __VA_ARGS__)

#define makeManglingTypePack2(binaryManglingFunc, count, ...) \
    count macroTransmit(macroIf, count)(separatorComma()) \
    macroTransmit0(macroUnfoldBinaryCall, count, separatorComma, binaryManglingFunc, __VA_ARGS__)

#define packMakeManglingTypePack1(unaryManglingFunc, TypePack) \
    macroTransmit1(makeManglingTypePack1, unaryManglingFunc, TypePack())

#define packMakeManglingTypePack2(binaryManglingFunc, TypePack) \
    macroTransmit1(makeManglingTypePack2, binaryManglingFunc, TypePack())
