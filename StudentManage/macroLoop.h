#pragma once

#include "macroBase.h"
#include "macroList.h"
#include "macroBranch.h"

#define macroRepet0(duplicate, getSeparator)
#define macroRepet1(duplicate, getSeparator) duplicate
#define macroRepet2(duplicate, getSeparator) duplicate getSeparator() macroRepet1(duplicate, getSeparator)
#define macroRepet3(duplicate, getSeparator) duplicate getSeparator() macroRepet2(duplicate, getSeparator)
#define macroRepet4(duplicate, getSeparator) duplicate getSeparator() macroRepet3(duplicate, getSeparator)
#define macroRepet5(duplicate, getSeparator) duplicate getSeparator() macroRepet4(duplicate, getSeparator)
#define macroRepet6(duplicate, getSeparator) duplicate getSeparator() macroRepet5(duplicate, getSeparator)
#define macroRepet7(duplicate, getSeparator) duplicate getSeparator() macroRepet6(duplicate, getSeparator)
#define macroRepet8(duplicate, getSeparator) duplicate getSeparator() macroRepet7(duplicate, getSeparator)
#define macroRepet9(duplicate, getSeparator) duplicate getSeparator() macroRepet8(duplicate, getSeparator)
#define macroRepet10(duplicate, getSeparator) duplicate getSeparator() macroRepet9(duplicate, getSeparator)
#define macroRepet11(duplicate, getSeparator) duplicate getSeparator() macroRepet10(duplicate, getSeparator)
#define macroRepet12(duplicate, getSeparator) duplicate getSeparator() macroRepet11(duplicate, getSeparator)
#define macroRepet13(duplicate, getSeparator) duplicate getSeparator() macroRepet12(duplicate, getSeparator)
#define macroRepet14(duplicate, getSeparator) duplicate getSeparator() macroRepet13(duplicate, getSeparator)
#define macroRepet15(duplicate, getSeparator) duplicate getSeparator() macroRepet14(duplicate, getSeparator)
#define macroRepet16(duplicate, getSeparator) duplicate getSeparator() macroRepet15(duplicate, getSeparator)
#define macroRepet17(duplicate, getSeparator) duplicate getSeparator() macroRepet16(duplicate, getSeparator)
#define macroRepet18(duplicate, getSeparator) duplicate getSeparator() macroRepet17(duplicate, getSeparator)
#define macroRepet19(duplicate, getSeparator) duplicate getSeparator() macroRepet18(duplicate, getSeparator)
#define macroRepet20(duplicate, getSeparator) duplicate getSeparator() macroRepet19(duplicate, getSeparator)
#define macroRepet21(duplicate, getSeparator) duplicate getSeparator() macroRepet20(duplicate, getSeparator)
#define macroRepet22(duplicate, getSeparator) duplicate getSeparator() macroRepet21(duplicate, getSeparator)
#define macroRepet23(duplicate, getSeparator) duplicate getSeparator() macroRepet22(duplicate, getSeparator)
#define macroRepet24(duplicate, getSeparator) duplicate getSeparator() macroRepet23(duplicate, getSeparator)
#define macroRepet25(duplicate, getSeparator) duplicate getSeparator() macroRepet24(duplicate, getSeparator)
#define macroRepet26(duplicate, getSeparator) duplicate getSeparator() macroRepet25(duplicate, getSeparator)
#define macroRepet27(duplicate, getSeparator) duplicate getSeparator() macroRepet26(duplicate, getSeparator)
#define macroRepet28(duplicate, getSeparator) duplicate getSeparator() macroRepet27(duplicate, getSeparator)
#define macroRepet29(duplicate, getSeparator) duplicate getSeparator() macroRepet28(duplicate, getSeparator)
#define macroRepet30(duplicate, getSeparator) duplicate getSeparator() macroRepet29(duplicate, getSeparator)
#define macroRepet31(duplicate, getSeparator) duplicate getSeparator() macroRepet30(duplicate, getSeparator)
#define macroRepet32(duplicate, getSeparator) duplicate getSeparator() macroRepet31(duplicate, getSeparator)

#define macroUnfoldCall0(getSeparator, varargCallable, fixedCount, ...)
#define macroUnfoldCall1(getSeparator, varargCallable, fixedCount, argsCount, ...) \
    macroTransmit0(varargCallable, argsCount,                                      \
    reserveList(fixedCount, __VA_ARGS__)                                           \
    macroIf(fixedCount)(macroIf(argsCount)(getSeparator()))                        \
    reserveList(argsCount, cutOffList(fixedCount, __VA_ARGS__)))

#define macroUnfoldCall2(getSeparator, varargCallable, fixedCount, argsCount, ...)                             \
    macroTransmit1(varargCallable, argsCount,                                                                  \
    reserveList(fixedCount, __VA_ARGS__) macroIf(fixedCount)(getSeparator())                                   \
    reserveList(argsCount, cutOffList(fixedCount, __VA_ARGS__)))                                               \
    getSeparator() macroTransmit1(macroUnfoldCall1, getSeparator, varargCallable, fixedCount,                  \
        reserveList(1, cutOffList(fixedCount, cutOffList(argsCount, __VA_ARGS__)))                             \
        macroIf(fixedCount)(                                                                                   \
            macroTransmit1(macroIf, reserveList(1, cutOffList(fixedCount, cutOffList(argsCount, __VA_ARGS__)))) \
                (separatorComma()))  \
        reserveList(fixedCount, __VA_ARGS__) macroIf(fixedCount)(macroIf(argsCount)(separatorComma())) \
        cutOffList(1, cutOffList(fixedCount, cutOffList(argsCount, __VA_ARGS__))))

#define macroUnfoldCall3(getSeparator, varargCallable, fixedCount, argsCount, ...)                             \
    macroTransmit2(varargCallable, argsCount,                                                                  \
    reserveList(fixedCount, __VA_ARGS__) macroIf(fixedCount)(getSeparator())                                   \
    reserveList(argsCount, cutOffList(fixedCount, __VA_ARGS__)))                                               \
    getSeparator() macroTransmit2(macroUnfoldCall2, getSeparator, varargCallable, fixedCount,                  \
        reserveList(1, cutOffList(fixedCount, cutOffList(argsCount, __VA_ARGS__)))                             \
        macroIf(fixedCount)(                                                                                   \
            macroTransmit2(macroIf, reserveList(1, cutOffList(fixedCount, cutOffList(argsCount, __VA_ARGS__)))) \
                (separatorComma()))  \
        reserveList(fixedCount, __VA_ARGS__) macroIf(fixedCount)(macroIf(argsCount)(separatorComma())) \
        cutOffList(1, cutOffList(fixedCount, cutOffList(argsCount, __VA_ARGS__))))

#define macroUnfoldCall4(getSeparator, varargCallable, fixedCount, argsCount, ...)                             \
    macroTransmit3(varargCallable, argsCount,                                                                  \
    reserveList(fixedCount, __VA_ARGS__) macroIf(fixedCount)(getSeparator())                                   \
    reserveList(argsCount, cutOffList(fixedCount, __VA_ARGS__)))                                               \
    getSeparator() macroTransmit3(macroUnfoldCall3, getSeparator, varargCallable, fixedCount,                  \
        reserveList(1, cutOffList(fixedCount, cutOffList(argsCount, __VA_ARGS__)))                             \
        macroIf(fixedCount)(                                                                                   \
            macroTransmit3(macroIf, reserveList(1, cutOffList(fixedCount, cutOffList(argsCount, __VA_ARGS__)))) \
                (separatorComma()))  \
        reserveList(fixedCount, __VA_ARGS__) macroIf(fixedCount)(macroIf(argsCount)(separatorComma())) \
        cutOffList(1, cutOffList(fixedCount, cutOffList(argsCount, __VA_ARGS__))))

#define macroUnfoldUnaryCall0(getSeparator, unaryCallable, ...)
#define macroUnfoldUnaryCall1(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg)
#define macroUnfoldUnaryCall2(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall1(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall3(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall2(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall4(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall3(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall5(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall4(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall6(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall5(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall7(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall6(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall8(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall7(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall9(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall8(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall10(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall9(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall11(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall10(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall12(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall11(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall13(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall12(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall14(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall13(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall15(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall14(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall16(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall15(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall17(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall16(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall18(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall17(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall19(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall18(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall20(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall19(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall21(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall20(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall22(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall21(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall23(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall22(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall24(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall23(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall25(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall24(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall26(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall25(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall27(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall26(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall28(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall27(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall29(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall28(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall30(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall29(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall31(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall30(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldUnaryCall32(getSeparator, unaryCallable, arg, ...) \
    unaryCallable(arg) getSeparator() macroUnfoldUnaryCall31(getSeparator, unaryCallable, __VA_ARGS__)

#define macroUnfoldBinaryCall0(getSeparator, binaryCallable, ...)
#define macroUnfoldBinaryCall1(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2)
#define macroUnfoldBinaryCall2(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall1(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall3(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall2(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall4(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall3(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall5(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall4(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall6(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall5(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall7(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall6(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall8(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall7(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall9(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall8(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall10(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall9(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall11(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall10(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall12(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall11(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall13(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall12(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall14(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall13(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall15(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall14(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall16(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall15(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall17(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall16(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall18(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall17(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall19(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall18(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall20(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall19(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall21(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall20(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall22(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall21(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall23(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall22(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall24(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall23(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall25(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall24(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall26(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall25(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall27(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall26(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall28(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall27(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall29(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall28(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall30(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall29(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall31(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall30(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall32(getSeparator, binaryCallable, arg1, arg2, ...) \
    binaryCallable(arg1, arg2) getSeparator() macroUnfoldBinaryCall31(getSeparator, binaryCallable, __VA_ARGS__)

#define macroUnfoldFixed1BinaryCall0(getSeparator, binaryCallable, ...)
#define macroUnfoldFixed1BinaryCall1(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg)
#define macroUnfoldFixed1BinaryCall2(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall1(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall3(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall2(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall4(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall3(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall5(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall4(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall6(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall5(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall7(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall6(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall8(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall7(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall9(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall8(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall10(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall9(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall11(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall10(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall12(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall11(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall13(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall12(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall14(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall13(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall15(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall14(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall16(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall15(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall17(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall16(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall18(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall17(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall19(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall18(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall20(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall19(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall21(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall20(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall22(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall21(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall23(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall22(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall24(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall23(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall25(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall24(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall26(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall25(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall27(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall26(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall28(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall27(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall29(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall28(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall30(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall29(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall31(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall30(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1BinaryCall32(getSeparator, binaryCallable, fixedArg, arg, ...) \
    binaryCallable(fixedArg, arg) getSeparator() macroUnfoldFixed1BinaryCall31(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)

#define macroUnfoldTernaryCall0(getSeparator, ternaryCallable, ...)
#define macroUnfoldTernaryCall1(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3)
#define macroUnfoldTernaryCall2(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall1(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall3(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall2(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall4(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall3(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall5(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall4(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall6(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall5(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall7(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall6(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall8(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall7(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall9(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall8(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall10(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall9(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall11(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall10(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall12(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall11(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall13(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall12(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall14(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall13(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall15(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall14(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall16(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall15(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall17(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall16(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall18(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall17(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall19(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall18(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall20(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall19(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall21(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall20(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall22(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall21(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall23(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall22(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall24(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall23(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall25(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall24(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall26(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall25(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall27(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall26(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall28(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall27(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall29(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall28(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall30(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall29(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall31(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall30(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall32(getSeparator, ternaryCallable, arg1, arg2, arg3, ...) \
    ternaryCallable(arg1, arg2, arg3) getSeparator() macroUnfoldTernaryCall31(getSeparator, ternaryCallable, __VA_ARGS__)

#define macroUnfoldFixed1TernaryCall0(getSeparator, ternaryCallable, ...)
#define macroUnfoldFixed1TernaryCall1(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2)
#define macroUnfoldFixed1TernaryCall2(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall1(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall3(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall2(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall4(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall3(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall5(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall4(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall6(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall5(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall7(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall6(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall8(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall7(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall9(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall8(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall10(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall9(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall11(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall10(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall12(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall11(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall13(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall12(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall14(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall13(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall15(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall14(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall16(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall15(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall17(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall16(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall18(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall17(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall19(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall18(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall20(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall19(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall21(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall20(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall22(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall21(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall23(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall22(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall24(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall23(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall25(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall24(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall26(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall25(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall27(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall26(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall28(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall27(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall29(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall28(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall30(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall29(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall31(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall30(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall32(getSeparator, ternaryCallable, fixedArg, arg1, arg2, ...) \
    ternaryCallable(fixedArg, arg1, arg2) getSeparator() macroUnfoldFixed1TernaryCall31(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)

#define macroUnfoldQuaternaryCall0(getSeparator, quaternaryCallable, ...)
#define macroUnfoldQuaternaryCall1(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4)
#define macroUnfoldQuaternaryCall2(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall1(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall3(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall2(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall4(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall3(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall5(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall4(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall6(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall5(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall7(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall6(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall8(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall7(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall9(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall8(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall10(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall9(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall11(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall10(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall12(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall11(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall13(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall12(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall14(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall13(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall15(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall14(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall16(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall15(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall17(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall16(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall18(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall17(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall19(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall18(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall20(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall19(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall21(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall20(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall22(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall21(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall23(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall22(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall24(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall23(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall25(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall24(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall26(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall25(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall27(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall26(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall28(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall27(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall29(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall28(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall30(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall29(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall31(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall30(getSeparator, quaternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternaryCall32(getSeparator, quaternaryCallable, arg1, arg2, arg3, arg4, ...) \
    quaternaryCallable(arg1, arg2, arg3, arg4) getSeparator() macroUnfoldQuaternaryCall31(getSeparator, quaternaryCallable, __VA_ARGS__)

// 0 - 32
#define macroUnfoldFixed2QuaternaryCall0(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, ...)
#define macroUnfoldFixed2QuaternaryCall1(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2)
#define macroUnfoldFixed2QuaternaryCall2(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall1(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall3(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall2(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall4(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall3(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall5(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall4(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall6(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall5(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall7(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall6(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall8(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall7(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall9(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall8(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall10(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall9(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall11(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall10(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall12(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall11(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall13(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall12(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall14(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall13(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall15(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall14(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall16(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall15(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall17(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall16(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall18(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall17(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall19(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall18(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall20(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall19(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall21(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall20(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall22(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall21(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall23(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall22(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall24(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall23(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall25(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall24(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall26(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall25(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall27(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall26(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall28(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall27(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall29(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall28(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall30(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall29(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall31(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall30(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall32(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, arg1, arg2, ...) \
    quaternaryCallable(fixedArg1, fixedArg2, arg1, arg2) getSeparator() macroUnfoldFixed2QuaternaryCall31(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)

#define macroRepet(count, duplicate, getSeparator) macroRepet ## count(duplicate, getSeparator)

#define macroUnfoldCall(count, getSeparator, varargCallable, fixedCount, argsCount, ...) \
    macroUnfoldCall ## count (getSeparator, varargCallable, fixedCount, argsCount, __VA_ARGS__)
#define macroUnfoldUnaryCall(count, getSeparator, unaryCallable, ...) \
    macroUnfoldUnaryCall ## count(getSeparator, unaryCallable, __VA_ARGS__)
#define macroUnfoldBinaryCall(count, getSeparator, binaryCallable, ...) \
    macroUnfoldBinaryCall ## count(getSeparator, binaryCallable, __VA_ARGS__)
#define macroUnfoldTernaryCall(count, getSeparator, ternaryCallable, ...) \
    macroUnfoldTernaryCall ## count(getSeparator, ternaryCallable, __VA_ARGS__)
#define macroUnfoldQuaternary(count, getSeparator, quaternaryCallable, ...) \
    macroUnfoldQuaternaryCall ## count(getSeparator, quaternaryCallable,, __VA_ARGS__)

#define macroUnfoldFixed1BinaryCall(count, getSeparator, binaryCallable, fixedArg, ...) \
    macroUnfoldFixed1BinaryCall ## count(getSeparator, binaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed1TernaryCall(count, getSeparator, ternaryCallable, fixedArg, ...) \
    macroUnfoldFixed1TernaryCall ## count(getSeparator, ternaryCallable, fixedArg, __VA_ARGS__)
#define macroUnfoldFixed2QuaternaryCall(count, getSeparator, quaternaryCallable, fixedArg1, fixedArg2, ...) \
    macroUnfoldFixed2QuaternaryCall ## count(getSeparator, quaternaryCallable, fixedArg1, fixedArg2, __VA_ARGS__)

#define macroFor(count, statement) macroRepet(count, statement, separatorSemicolon)
#define macroForeachUnary(count, unaryCallable, ...) \
    macroUnfoldUnaryCall(count, separatorSemicolon, unaryCallable, __VA_ARGS__)
#define macroForeachBinary(count, binaryCallable, ...) \
    macroUnfoldBinaryCall(count, separatorSemicolon, binaryCallable, __VA_ARGS__)
#define macroForeachTernary(count, ternaryCallable, ...) \
    macroUnfoldTernaryCall(count, separatorSemicolon, ternaryCallable, __VA_ARGS__)
