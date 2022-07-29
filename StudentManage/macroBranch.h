#pragma once

#include "macroBase.h"


#define macroElse_0(statement) statement
#define macroElse_1(statement) 

#define macroIfElse_0(statement) macroElse_0
#define macroIfElse_1(statement) statement macroElse_1
#define macroIfElse_2(statement) statement macroElse_1
#define macroIfElse_3(statement) statement macroElse_1
#define macroIfElse_4(statement) statement macroElse_1
#define macroIfElse_5(statement) statement macroElse_1
#define macroIfElse_6(statement) statement macroElse_1
#define macroIfElse_7(statement) statement macroElse_1
#define macroIfElse_8(statement) statement macroElse_1
#define macroIfElse_9(statement) statement macroElse_1
#define macroIfElse_10(statement) statement macroElse_1
#define macroIfElse_11(statement) statement macroElse_1
#define macroIfElse_12(statement) statement macroElse_1
#define macroIfElse_13(statement) statement macroElse_1
#define macroIfElse_14(statement) statement macroElse_1
#define macroIfElse_15(statement) statement macroElse_1
#define macroIfElse_16(statement) statement macroElse_1
#define macroIfElse_17(statement) statement macroElse_1
#define macroIfElse_18(statement) statement macroElse_1
#define macroIfElse_19(statement) statement macroElse_1
#define macroIfElse_20(statement) statement macroElse_1
#define macroIfElse_21(statement) statement macroElse_1
#define macroIfElse_22(statement) statement macroElse_1
#define macroIfElse_23(statement) statement macroElse_1
#define macroIfElse_24(statement) statement macroElse_1
#define macroIfElse_25(statement) statement macroElse_1
#define macroIfElse_26(statement) statement macroElse_1
#define macroIfElse_27(statement) statement macroElse_1
#define macroIfElse_28(statement) statement macroElse_1
#define macroIfElse_29(statement) statement macroElse_1
#define macroIfElse_30(statement) statement macroElse_1
#define macroIfElse_31(statement) statement macroElse_1
#define macroIfElse_32(statement) statement macroElse_1

#define macroIf_0(statement)
#define macroIf_1(statement) statement
#define macroIf_2(statement) statement
#define macroIf_3(statement) statement
#define macroIf_4(statement) statement
#define macroIf_5(statement) statement
#define macroIf_6(statement) statement
#define macroIf_7(statement) statement
#define macroIf_8(statement) statement
#define macroIf_9(statement) statement
#define macroIf_10(statement) statement
#define macroIf_11(statement) statement
#define macroIf_12(statement) statement
#define macroIf_13(statement) statement
#define macroIf_14(statement) statement
#define macroIf_15(statement) statement
#define macroIf_16(statement) statement
#define macroIf_17(statement) statement
#define macroIf_18(statement) statement
#define macroIf_19(statement) statement
#define macroIf_20(statement) statement
#define macroIf_21(statement) statement
#define macroIf_22(statement) statement
#define macroIf_23(statement) statement
#define macroIf_24(statement) statement
#define macroIf_25(statement) statement
#define macroIf_26(statement) statement
#define macroIf_27(statement) statement
#define macroIf_28(statement) statement
#define macroIf_29(statement) statement
#define macroIf_30(statement) statement
#define macroIf_31(statement) statement
#define macroIf_32(statement) statement

#define macroIf(cond)	  macroIf_ ## cond
#define macroIfElse(cond) macroIfElse_ ## cond

typedef struct { bool value; } TrueType;
typedef struct { bool value; } FalseType;
static TrueType  trueType  = { true };
static FalseType falseType = { false };

#define isFalseType(a) _Generic((a), FalseType: 1, default: 0)

#define isTrueType(a)  _Generic((a), TrueType: 1, default: 0)

#define genericMacroIfElse(cond, thenDo, elseDo) \
    _Generic((cond), FalseType: elseDo, default: thenDo)

#define genericMacroIf(cond, thenDo) \
    _Generic((cond), TrueType: thenDo, default:(void)(0))
