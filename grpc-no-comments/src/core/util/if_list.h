// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_IF_LIST_H
#define GRPC_SRC_CORE_UTIL_IF_LIST_H

#include <grpc/support/port_platform.h>

namespace grpc_core {

template <typename CheckArg, typename ActionArg, typename ActionFail,
          typename Check0, typename Action0>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Action0 action0) {
  if (check0(input)) return action0(action_arg);
  return action_fail(action_arg);
}

template <typename CheckArg, typename ActionArg, typename ActionFail,
          typename Check0, typename Check1, typename Action0, typename Action1>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Action0 action0, Action1 action1) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  return action_fail(action_arg);
}

template <typename CheckArg, typename ActionArg, typename ActionFail,
          typename Check0, typename Check1, typename Check2, typename Action0,
          typename Action1, typename Action2>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Action0 action0,
            Action1 action1, Action2 action2) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  return action_fail(action_arg);
}

template <typename CheckArg, typename ActionArg, typename ActionFail,
          typename Check0, typename Check1, typename Check2, typename Check3,
          typename Action0, typename Action1, typename Action2,
          typename Action3>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Action0 action0, Action1 action1, Action2 action2,
            Action3 action3) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  return action_fail(action_arg);
}

template <typename CheckArg, typename ActionArg, typename ActionFail,
          typename Check0, typename Check1, typename Check2, typename Check3,
          typename Check4, typename Action0, typename Action1, typename Action2,
          typename Action3, typename Action4>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Action0 action0, Action1 action1, Action2 action2,
            Action3 action3, Action4 action4) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  return action_fail(action_arg);
}

template <typename CheckArg, typename ActionArg, typename ActionFail,
          typename Check0, typename Check1, typename Check2, typename Check3,
          typename Check4, typename Check5, typename Action0, typename Action1,
          typename Action2, typename Action3, typename Action4,
          typename Action5>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Action0 action0, Action1 action1,
            Action2 action2, Action3 action3, Action4 action4,
            Action5 action5) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  return action_fail(action_arg);
}

template <typename CheckArg, typename ActionArg, typename ActionFail,
          typename Check0, typename Check1, typename Check2, typename Check3,
          typename Check4, typename Check5, typename Check6, typename Action0,
          typename Action1, typename Action2, typename Action3,
          typename Action4, typename Action5, typename Action6>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Action0 action0,
            Action1 action1, Action2 action2, Action3 action3, Action4 action4,
            Action5 action5, Action6 action6) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  return action_fail(action_arg);
}

template <typename CheckArg, typename ActionArg, typename ActionFail,
          typename Check0, typename Check1, typename Check2, typename Check3,
          typename Check4, typename Check5, typename Check6, typename Check7,
          typename Action0, typename Action1, typename Action2,
          typename Action3, typename Action4, typename Action5,
          typename Action6, typename Action7>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Action0 action0, Action1 action1, Action2 action2, Action3 action3,
            Action4 action4, Action5 action5, Action6 action6,
            Action7 action7) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  return action_fail(action_arg);
}

template <typename CheckArg, typename ActionArg, typename ActionFail,
          typename Check0, typename Check1, typename Check2, typename Check3,
          typename Check4, typename Check5, typename Check6, typename Check7,
          typename Check8, typename Action0, typename Action1, typename Action2,
          typename Action3, typename Action4, typename Action5,
          typename Action6, typename Action7, typename Action8>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Action0 action0, Action1 action1, Action2 action2,
            Action3 action3, Action4 action4, Action5 action5, Action6 action6,
            Action7 action7, Action8 action8) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  return action_fail(action_arg);
}

template <typename CheckArg, typename ActionArg, typename ActionFail,
          typename Check0, typename Check1, typename Check2, typename Check3,
          typename Check4, typename Check5, typename Check6, typename Check7,
          typename Check8, typename Check9, typename Action0, typename Action1,
          typename Action2, typename Action3, typename Action4,
          typename Action5, typename Action6, typename Action7,
          typename Action8, typename Action9>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Action0 action0, Action1 action1,
            Action2 action2, Action3 action3, Action4 action4, Action5 action5,
            Action6 action6, Action7 action7, Action8 action8,
            Action9 action9) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  return action_fail(action_arg);
}

template <typename CheckArg, typename ActionArg, typename ActionFail,
          typename Check0, typename Check1, typename Check2, typename Check3,
          typename Check4, typename Check5, typename Check6, typename Check7,
          typename Check8, typename Check9, typename Check10, typename Action0,
          typename Action1, typename Action2, typename Action3,
          typename Action4, typename Action5, typename Action6,
          typename Action7, typename Action8, typename Action9,
          typename Action10>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Action0 action0,
            Action1 action1, Action2 action2, Action3 action3, Action4 action4,
            Action5 action5, Action6 action6, Action7 action7, Action8 action8,
            Action9 action9, Action10 action10) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  return action_fail(action_arg);
}

template <typename CheckArg, typename ActionArg, typename ActionFail,
          typename Check0, typename Check1, typename Check2, typename Check3,
          typename Check4, typename Check5, typename Check6, typename Check7,
          typename Check8, typename Check9, typename Check10, typename Check11,
          typename Action0, typename Action1, typename Action2,
          typename Action3, typename Action4, typename Action5,
          typename Action6, typename Action7, typename Action8,
          typename Action9, typename Action10, typename Action11>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Action0 action0, Action1 action1, Action2 action2, Action3 action3,
            Action4 action4, Action5 action5, Action6 action6, Action7 action7,
            Action8 action8, Action9 action9, Action10 action10,
            Action11 action11) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  return action_fail(action_arg);
}

template <typename CheckArg, typename ActionArg, typename ActionFail,
          typename Check0, typename Check1, typename Check2, typename Check3,
          typename Check4, typename Check5, typename Check6, typename Check7,
          typename Check8, typename Check9, typename Check10, typename Check11,
          typename Check12, typename Action0, typename Action1,
          typename Action2, typename Action3, typename Action4,
          typename Action5, typename Action6, typename Action7,
          typename Action8, typename Action9, typename Action10,
          typename Action11, typename Action12>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Action0 action0, Action1 action1, Action2 action2,
            Action3 action3, Action4 action4, Action5 action5, Action6 action6,
            Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Action0, typename Action1, typename Action2,
    typename Action3, typename Action4, typename Action5, typename Action6,
    typename Action7, typename Action8, typename Action9, typename Action10,
    typename Action11, typename Action12, typename Action13>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Action0 action0, Action1 action1,
            Action2 action2, Action3 action3, Action4 action4, Action5 action5,
            Action6 action6, Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  return action_fail(action_arg);
}

template <typename CheckArg, typename ActionArg, typename ActionFail,
          typename Check0, typename Check1, typename Check2, typename Check3,
          typename Check4, typename Check5, typename Check6, typename Check7,
          typename Check8, typename Check9, typename Check10, typename Check11,
          typename Check12, typename Check13, typename Check14,
          typename Action0, typename Action1, typename Action2,
          typename Action3, typename Action4, typename Action5,
          typename Action6, typename Action7, typename Action8,
          typename Action9, typename Action10, typename Action11,
          typename Action12, typename Action13, typename Action14>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Action0 action0,
            Action1 action1, Action2 action2, Action3 action3, Action4 action4,
            Action5 action5, Action6 action6, Action7 action7, Action8 action8,
            Action9 action9, Action10 action10, Action11 action11,
            Action12 action12, Action13 action13, Action14 action14) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Action0,
    typename Action1, typename Action2, typename Action3, typename Action4,
    typename Action5, typename Action6, typename Action7, typename Action8,
    typename Action9, typename Action10, typename Action11, typename Action12,
    typename Action13, typename Action14, typename Action15>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Action0 action0, Action1 action1, Action2 action2, Action3 action3,
            Action4 action4, Action5 action5, Action6 action6, Action7 action7,
            Action8 action8, Action9 action9, Action10 action10,
            Action11 action11, Action12 action12, Action13 action13,
            Action14 action14, Action15 action15) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Action0, typename Action1, typename Action2, typename Action3,
    typename Action4, typename Action5, typename Action6, typename Action7,
    typename Action8, typename Action9, typename Action10, typename Action11,
    typename Action12, typename Action13, typename Action14, typename Action15,
    typename Action16>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Action0 action0, Action1 action1, Action2 action2,
            Action3 action3, Action4 action4, Action5 action5, Action6 action6,
            Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13, Action14 action14, Action15 action15,
            Action16 action16) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Action0, typename Action1, typename Action2,
    typename Action3, typename Action4, typename Action5, typename Action6,
    typename Action7, typename Action8, typename Action9, typename Action10,
    typename Action11, typename Action12, typename Action13, typename Action14,
    typename Action15, typename Action16, typename Action17>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Action0 action0, Action1 action1,
            Action2 action2, Action3 action3, Action4 action4, Action5 action5,
            Action6 action6, Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13, Action14 action14, Action15 action15,
            Action16 action16, Action17 action17) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Action0, typename Action1,
    typename Action2, typename Action3, typename Action4, typename Action5,
    typename Action6, typename Action7, typename Action8, typename Action9,
    typename Action10, typename Action11, typename Action12, typename Action13,
    typename Action14, typename Action15, typename Action16, typename Action17,
    typename Action18>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Action0 action0,
            Action1 action1, Action2 action2, Action3 action3, Action4 action4,
            Action5 action5, Action6 action6, Action7 action7, Action8 action8,
            Action9 action9, Action10 action10, Action11 action11,
            Action12 action12, Action13 action13, Action14 action14,
            Action15 action15, Action16 action16, Action17 action17,
            Action18 action18) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Action0,
    typename Action1, typename Action2, typename Action3, typename Action4,
    typename Action5, typename Action6, typename Action7, typename Action8,
    typename Action9, typename Action10, typename Action11, typename Action12,
    typename Action13, typename Action14, typename Action15, typename Action16,
    typename Action17, typename Action18, typename Action19>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Action0 action0, Action1 action1, Action2 action2, Action3 action3,
            Action4 action4, Action5 action5, Action6 action6, Action7 action7,
            Action8 action8, Action9 action9, Action10 action10,
            Action11 action11, Action12 action12, Action13 action13,
            Action14 action14, Action15 action15, Action16 action16,
            Action17 action17, Action18 action18, Action19 action19) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Action0, typename Action1, typename Action2, typename Action3,
    typename Action4, typename Action5, typename Action6, typename Action7,
    typename Action8, typename Action9, typename Action10, typename Action11,
    typename Action12, typename Action13, typename Action14, typename Action15,
    typename Action16, typename Action17, typename Action18, typename Action19,
    typename Action20>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Action0 action0, Action1 action1, Action2 action2,
            Action3 action3, Action4 action4, Action5 action5, Action6 action6,
            Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13, Action14 action14, Action15 action15,
            Action16 action16, Action17 action17, Action18 action18,
            Action19 action19, Action20 action20) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Action0, typename Action1, typename Action2,
    typename Action3, typename Action4, typename Action5, typename Action6,
    typename Action7, typename Action8, typename Action9, typename Action10,
    typename Action11, typename Action12, typename Action13, typename Action14,
    typename Action15, typename Action16, typename Action17, typename Action18,
    typename Action19, typename Action20, typename Action21>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Action0 action0, Action1 action1,
            Action2 action2, Action3 action3, Action4 action4, Action5 action5,
            Action6 action6, Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13, Action14 action14, Action15 action15,
            Action16 action16, Action17 action17, Action18 action18,
            Action19 action19, Action20 action20, Action21 action21) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Action0, typename Action1,
    typename Action2, typename Action3, typename Action4, typename Action5,
    typename Action6, typename Action7, typename Action8, typename Action9,
    typename Action10, typename Action11, typename Action12, typename Action13,
    typename Action14, typename Action15, typename Action16, typename Action17,
    typename Action18, typename Action19, typename Action20, typename Action21,
    typename Action22>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Action0 action0,
            Action1 action1, Action2 action2, Action3 action3, Action4 action4,
            Action5 action5, Action6 action6, Action7 action7, Action8 action8,
            Action9 action9, Action10 action10, Action11 action11,
            Action12 action12, Action13 action13, Action14 action14,
            Action15 action15, Action16 action16, Action17 action17,
            Action18 action18, Action19 action19, Action20 action20,
            Action21 action21, Action22 action22) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Action0,
    typename Action1, typename Action2, typename Action3, typename Action4,
    typename Action5, typename Action6, typename Action7, typename Action8,
    typename Action9, typename Action10, typename Action11, typename Action12,
    typename Action13, typename Action14, typename Action15, typename Action16,
    typename Action17, typename Action18, typename Action19, typename Action20,
    typename Action21, typename Action22, typename Action23>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Action0 action0, Action1 action1, Action2 action2, Action3 action3,
            Action4 action4, Action5 action5, Action6 action6, Action7 action7,
            Action8 action8, Action9 action9, Action10 action10,
            Action11 action11, Action12 action12, Action13 action13,
            Action14 action14, Action15 action15, Action16 action16,
            Action17 action17, Action18 action18, Action19 action19,
            Action20 action20, Action21 action21, Action22 action22,
            Action23 action23) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Action0, typename Action1, typename Action2, typename Action3,
    typename Action4, typename Action5, typename Action6, typename Action7,
    typename Action8, typename Action9, typename Action10, typename Action11,
    typename Action12, typename Action13, typename Action14, typename Action15,
    typename Action16, typename Action17, typename Action18, typename Action19,
    typename Action20, typename Action21, typename Action22, typename Action23,
    typename Action24>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Action0 action0, Action1 action1, Action2 action2,
            Action3 action3, Action4 action4, Action5 action5, Action6 action6,
            Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13, Action14 action14, Action15 action15,
            Action16 action16, Action17 action17, Action18 action18,
            Action19 action19, Action20 action20, Action21 action21,
            Action22 action22, Action23 action23, Action24 action24) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Action0, typename Action1, typename Action2,
    typename Action3, typename Action4, typename Action5, typename Action6,
    typename Action7, typename Action8, typename Action9, typename Action10,
    typename Action11, typename Action12, typename Action13, typename Action14,
    typename Action15, typename Action16, typename Action17, typename Action18,
    typename Action19, typename Action20, typename Action21, typename Action22,
    typename Action23, typename Action24, typename Action25>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Action0 action0, Action1 action1,
            Action2 action2, Action3 action3, Action4 action4, Action5 action5,
            Action6 action6, Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13, Action14 action14, Action15 action15,
            Action16 action16, Action17 action17, Action18 action18,
            Action19 action19, Action20 action20, Action21 action21,
            Action22 action22, Action23 action23, Action24 action24,
            Action25 action25) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Action0, typename Action1,
    typename Action2, typename Action3, typename Action4, typename Action5,
    typename Action6, typename Action7, typename Action8, typename Action9,
    typename Action10, typename Action11, typename Action12, typename Action13,
    typename Action14, typename Action15, typename Action16, typename Action17,
    typename Action18, typename Action19, typename Action20, typename Action21,
    typename Action22, typename Action23, typename Action24, typename Action25,
    typename Action26>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Action0 action0,
            Action1 action1, Action2 action2, Action3 action3, Action4 action4,
            Action5 action5, Action6 action6, Action7 action7, Action8 action8,
            Action9 action9, Action10 action10, Action11 action11,
            Action12 action12, Action13 action13, Action14 action14,
            Action15 action15, Action16 action16, Action17 action17,
            Action18 action18, Action19 action19, Action20 action20,
            Action21 action21, Action22 action22, Action23 action23,
            Action24 action24, Action25 action25, Action26 action26) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Action0,
    typename Action1, typename Action2, typename Action3, typename Action4,
    typename Action5, typename Action6, typename Action7, typename Action8,
    typename Action9, typename Action10, typename Action11, typename Action12,
    typename Action13, typename Action14, typename Action15, typename Action16,
    typename Action17, typename Action18, typename Action19, typename Action20,
    typename Action21, typename Action22, typename Action23, typename Action24,
    typename Action25, typename Action26, typename Action27>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Action0 action0, Action1 action1, Action2 action2, Action3 action3,
            Action4 action4, Action5 action5, Action6 action6, Action7 action7,
            Action8 action8, Action9 action9, Action10 action10,
            Action11 action11, Action12 action12, Action13 action13,
            Action14 action14, Action15 action15, Action16 action16,
            Action17 action17, Action18 action18, Action19 action19,
            Action20 action20, Action21 action21, Action22 action22,
            Action23 action23, Action24 action24, Action25 action25,
            Action26 action26, Action27 action27) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Action0, typename Action1, typename Action2, typename Action3,
    typename Action4, typename Action5, typename Action6, typename Action7,
    typename Action8, typename Action9, typename Action10, typename Action11,
    typename Action12, typename Action13, typename Action14, typename Action15,
    typename Action16, typename Action17, typename Action18, typename Action19,
    typename Action20, typename Action21, typename Action22, typename Action23,
    typename Action24, typename Action25, typename Action26, typename Action27,
    typename Action28>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Action0 action0, Action1 action1, Action2 action2,
            Action3 action3, Action4 action4, Action5 action5, Action6 action6,
            Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13, Action14 action14, Action15 action15,
            Action16 action16, Action17 action17, Action18 action18,
            Action19 action19, Action20 action20, Action21 action21,
            Action22 action22, Action23 action23, Action24 action24,
            Action25 action25, Action26 action26, Action27 action27,
            Action28 action28) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Action0, typename Action1, typename Action2,
    typename Action3, typename Action4, typename Action5, typename Action6,
    typename Action7, typename Action8, typename Action9, typename Action10,
    typename Action11, typename Action12, typename Action13, typename Action14,
    typename Action15, typename Action16, typename Action17, typename Action18,
    typename Action19, typename Action20, typename Action21, typename Action22,
    typename Action23, typename Action24, typename Action25, typename Action26,
    typename Action27, typename Action28, typename Action29>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Check29 check29, Action0 action0, Action1 action1,
            Action2 action2, Action3 action3, Action4 action4, Action5 action5,
            Action6 action6, Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13, Action14 action14, Action15 action15,
            Action16 action16, Action17 action17, Action18 action18,
            Action19 action19, Action20 action20, Action21 action21,
            Action22 action22, Action23 action23, Action24 action24,
            Action25 action25, Action26 action26, Action27 action27,
            Action28 action28, Action29 action29) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Action0, typename Action1,
    typename Action2, typename Action3, typename Action4, typename Action5,
    typename Action6, typename Action7, typename Action8, typename Action9,
    typename Action10, typename Action11, typename Action12, typename Action13,
    typename Action14, typename Action15, typename Action16, typename Action17,
    typename Action18, typename Action19, typename Action20, typename Action21,
    typename Action22, typename Action23, typename Action24, typename Action25,
    typename Action26, typename Action27, typename Action28, typename Action29,
    typename Action30>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Check29 check29, Check30 check30, Action0 action0,
            Action1 action1, Action2 action2, Action3 action3, Action4 action4,
            Action5 action5, Action6 action6, Action7 action7, Action8 action8,
            Action9 action9, Action10 action10, Action11 action11,
            Action12 action12, Action13 action13, Action14 action14,
            Action15 action15, Action16 action16, Action17 action17,
            Action18 action18, Action19 action19, Action20 action20,
            Action21 action21, Action22 action22, Action23 action23,
            Action24 action24, Action25 action25, Action26 action26,
            Action27 action27, Action28 action28, Action29 action29,
            Action30 action30) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Action0,
    typename Action1, typename Action2, typename Action3, typename Action4,
    typename Action5, typename Action6, typename Action7, typename Action8,
    typename Action9, typename Action10, typename Action11, typename Action12,
    typename Action13, typename Action14, typename Action15, typename Action16,
    typename Action17, typename Action18, typename Action19, typename Action20,
    typename Action21, typename Action22, typename Action23, typename Action24,
    typename Action25, typename Action26, typename Action27, typename Action28,
    typename Action29, typename Action30, typename Action31>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Check29 check29, Check30 check30, Check31 check31,
            Action0 action0, Action1 action1, Action2 action2, Action3 action3,
            Action4 action4, Action5 action5, Action6 action6, Action7 action7,
            Action8 action8, Action9 action9, Action10 action10,
            Action11 action11, Action12 action12, Action13 action13,
            Action14 action14, Action15 action15, Action16 action16,
            Action17 action17, Action18 action18, Action19 action19,
            Action20 action20, Action21 action21, Action22 action22,
            Action23 action23, Action24 action24, Action25 action25,
            Action26 action26, Action27 action27, Action28 action28,
            Action29 action29, Action30 action30, Action31 action31) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Action0, typename Action1, typename Action2, typename Action3,
    typename Action4, typename Action5, typename Action6, typename Action7,
    typename Action8, typename Action9, typename Action10, typename Action11,
    typename Action12, typename Action13, typename Action14, typename Action15,
    typename Action16, typename Action17, typename Action18, typename Action19,
    typename Action20, typename Action21, typename Action22, typename Action23,
    typename Action24, typename Action25, typename Action26, typename Action27,
    typename Action28, typename Action29, typename Action30, typename Action31,
    typename Action32>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Check29 check29, Check30 check30, Check31 check31,
            Check32 check32, Action0 action0, Action1 action1, Action2 action2,
            Action3 action3, Action4 action4, Action5 action5, Action6 action6,
            Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13, Action14 action14, Action15 action15,
            Action16 action16, Action17 action17, Action18 action18,
            Action19 action19, Action20 action20, Action21 action21,
            Action22 action22, Action23 action23, Action24 action24,
            Action25 action25, Action26 action26, Action27 action27,
            Action28 action28, Action29 action29, Action30 action30,
            Action31 action31, Action32 action32) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Action0, typename Action1, typename Action2,
    typename Action3, typename Action4, typename Action5, typename Action6,
    typename Action7, typename Action8, typename Action9, typename Action10,
    typename Action11, typename Action12, typename Action13, typename Action14,
    typename Action15, typename Action16, typename Action17, typename Action18,
    typename Action19, typename Action20, typename Action21, typename Action22,
    typename Action23, typename Action24, typename Action25, typename Action26,
    typename Action27, typename Action28, typename Action29, typename Action30,
    typename Action31, typename Action32, typename Action33>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Check29 check29, Check30 check30, Check31 check31,
            Check32 check32, Check33 check33, Action0 action0, Action1 action1,
            Action2 action2, Action3 action3, Action4 action4, Action5 action5,
            Action6 action6, Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13, Action14 action14, Action15 action15,
            Action16 action16, Action17 action17, Action18 action18,
            Action19 action19, Action20 action20, Action21 action21,
            Action22 action22, Action23 action23, Action24 action24,
            Action25 action25, Action26 action26, Action27 action27,
            Action28 action28, Action29 action29, Action30 action30,
            Action31 action31, Action32 action32, Action33 action33) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Action0, typename Action1,
    typename Action2, typename Action3, typename Action4, typename Action5,
    typename Action6, typename Action7, typename Action8, typename Action9,
    typename Action10, typename Action11, typename Action12, typename Action13,
    typename Action14, typename Action15, typename Action16, typename Action17,
    typename Action18, typename Action19, typename Action20, typename Action21,
    typename Action22, typename Action23, typename Action24, typename Action25,
    typename Action26, typename Action27, typename Action28, typename Action29,
    typename Action30, typename Action31, typename Action32, typename Action33,
    typename Action34>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Check29 check29, Check30 check30, Check31 check31,
            Check32 check32, Check33 check33, Check34 check34, Action0 action0,
            Action1 action1, Action2 action2, Action3 action3, Action4 action4,
            Action5 action5, Action6 action6, Action7 action7, Action8 action8,
            Action9 action9, Action10 action10, Action11 action11,
            Action12 action12, Action13 action13, Action14 action14,
            Action15 action15, Action16 action16, Action17 action17,
            Action18 action18, Action19 action19, Action20 action20,
            Action21 action21, Action22 action22, Action23 action23,
            Action24 action24, Action25 action25, Action26 action26,
            Action27 action27, Action28 action28, Action29 action29,
            Action30 action30, Action31 action31, Action32 action32,
            Action33 action33, Action34 action34) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Action0,
    typename Action1, typename Action2, typename Action3, typename Action4,
    typename Action5, typename Action6, typename Action7, typename Action8,
    typename Action9, typename Action10, typename Action11, typename Action12,
    typename Action13, typename Action14, typename Action15, typename Action16,
    typename Action17, typename Action18, typename Action19, typename Action20,
    typename Action21, typename Action22, typename Action23, typename Action24,
    typename Action25, typename Action26, typename Action27, typename Action28,
    typename Action29, typename Action30, typename Action31, typename Action32,
    typename Action33, typename Action34, typename Action35>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Check29 check29, Check30 check30, Check31 check31,
            Check32 check32, Check33 check33, Check34 check34, Check35 check35,
            Action0 action0, Action1 action1, Action2 action2, Action3 action3,
            Action4 action4, Action5 action5, Action6 action6, Action7 action7,
            Action8 action8, Action9 action9, Action10 action10,
            Action11 action11, Action12 action12, Action13 action13,
            Action14 action14, Action15 action15, Action16 action16,
            Action17 action17, Action18 action18, Action19 action19,
            Action20 action20, Action21 action21, Action22 action22,
            Action23 action23, Action24 action24, Action25 action25,
            Action26 action26, Action27 action27, Action28 action28,
            Action29 action29, Action30 action30, Action31 action31,
            Action32 action32, Action33 action33, Action34 action34,
            Action35 action35) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Action0, typename Action1, typename Action2, typename Action3,
    typename Action4, typename Action5, typename Action6, typename Action7,
    typename Action8, typename Action9, typename Action10, typename Action11,
    typename Action12, typename Action13, typename Action14, typename Action15,
    typename Action16, typename Action17, typename Action18, typename Action19,
    typename Action20, typename Action21, typename Action22, typename Action23,
    typename Action24, typename Action25, typename Action26, typename Action27,
    typename Action28, typename Action29, typename Action30, typename Action31,
    typename Action32, typename Action33, typename Action34, typename Action35,
    typename Action36>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Check29 check29, Check30 check30, Check31 check31,
            Check32 check32, Check33 check33, Check34 check34, Check35 check35,
            Check36 check36, Action0 action0, Action1 action1, Action2 action2,
            Action3 action3, Action4 action4, Action5 action5, Action6 action6,
            Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13, Action14 action14, Action15 action15,
            Action16 action16, Action17 action17, Action18 action18,
            Action19 action19, Action20 action20, Action21 action21,
            Action22 action22, Action23 action23, Action24 action24,
            Action25 action25, Action26 action26, Action27 action27,
            Action28 action28, Action29 action29, Action30 action30,
            Action31 action31, Action32 action32, Action33 action33,
            Action34 action34, Action35 action35, Action36 action36) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Action0, typename Action1, typename Action2,
    typename Action3, typename Action4, typename Action5, typename Action6,
    typename Action7, typename Action8, typename Action9, typename Action10,
    typename Action11, typename Action12, typename Action13, typename Action14,
    typename Action15, typename Action16, typename Action17, typename Action18,
    typename Action19, typename Action20, typename Action21, typename Action22,
    typename Action23, typename Action24, typename Action25, typename Action26,
    typename Action27, typename Action28, typename Action29, typename Action30,
    typename Action31, typename Action32, typename Action33, typename Action34,
    typename Action35, typename Action36, typename Action37>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Check29 check29, Check30 check30, Check31 check31,
            Check32 check32, Check33 check33, Check34 check34, Check35 check35,
            Check36 check36, Check37 check37, Action0 action0, Action1 action1,
            Action2 action2, Action3 action3, Action4 action4, Action5 action5,
            Action6 action6, Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13, Action14 action14, Action15 action15,
            Action16 action16, Action17 action17, Action18 action18,
            Action19 action19, Action20 action20, Action21 action21,
            Action22 action22, Action23 action23, Action24 action24,
            Action25 action25, Action26 action26, Action27 action27,
            Action28 action28, Action29 action29, Action30 action30,
            Action31 action31, Action32 action32, Action33 action33,
            Action34 action34, Action35 action35, Action36 action36,
            Action37 action37) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Action0, typename Action1,
    typename Action2, typename Action3, typename Action4, typename Action5,
    typename Action6, typename Action7, typename Action8, typename Action9,
    typename Action10, typename Action11, typename Action12, typename Action13,
    typename Action14, typename Action15, typename Action16, typename Action17,
    typename Action18, typename Action19, typename Action20, typename Action21,
    typename Action22, typename Action23, typename Action24, typename Action25,
    typename Action26, typename Action27, typename Action28, typename Action29,
    typename Action30, typename Action31, typename Action32, typename Action33,
    typename Action34, typename Action35, typename Action36, typename Action37,
    typename Action38>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Check29 check29, Check30 check30, Check31 check31,
            Check32 check32, Check33 check33, Check34 check34, Check35 check35,
            Check36 check36, Check37 check37, Check38 check38, Action0 action0,
            Action1 action1, Action2 action2, Action3 action3, Action4 action4,
            Action5 action5, Action6 action6, Action7 action7, Action8 action8,
            Action9 action9, Action10 action10, Action11 action11,
            Action12 action12, Action13 action13, Action14 action14,
            Action15 action15, Action16 action16, Action17 action17,
            Action18 action18, Action19 action19, Action20 action20,
            Action21 action21, Action22 action22, Action23 action23,
            Action24 action24, Action25 action25, Action26 action26,
            Action27 action27, Action28 action28, Action29 action29,
            Action30 action30, Action31 action31, Action32 action32,
            Action33 action33, Action34 action34, Action35 action35,
            Action36 action36, Action37 action37, Action38 action38) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Action0,
    typename Action1, typename Action2, typename Action3, typename Action4,
    typename Action5, typename Action6, typename Action7, typename Action8,
    typename Action9, typename Action10, typename Action11, typename Action12,
    typename Action13, typename Action14, typename Action15, typename Action16,
    typename Action17, typename Action18, typename Action19, typename Action20,
    typename Action21, typename Action22, typename Action23, typename Action24,
    typename Action25, typename Action26, typename Action27, typename Action28,
    typename Action29, typename Action30, typename Action31, typename Action32,
    typename Action33, typename Action34, typename Action35, typename Action36,
    typename Action37, typename Action38, typename Action39>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Check29 check29, Check30 check30, Check31 check31,
            Check32 check32, Check33 check33, Check34 check34, Check35 check35,
            Check36 check36, Check37 check37, Check38 check38, Check39 check39,
            Action0 action0, Action1 action1, Action2 action2, Action3 action3,
            Action4 action4, Action5 action5, Action6 action6, Action7 action7,
            Action8 action8, Action9 action9, Action10 action10,
            Action11 action11, Action12 action12, Action13 action13,
            Action14 action14, Action15 action15, Action16 action16,
            Action17 action17, Action18 action18, Action19 action19,
            Action20 action20, Action21 action21, Action22 action22,
            Action23 action23, Action24 action24, Action25 action25,
            Action26 action26, Action27 action27, Action28 action28,
            Action29 action29, Action30 action30, Action31 action31,
            Action32 action32, Action33 action33, Action34 action34,
            Action35 action35, Action36 action36, Action37 action37,
            Action38 action38, Action39 action39) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Action0, typename Action1, typename Action2, typename Action3,
    typename Action4, typename Action5, typename Action6, typename Action7,
    typename Action8, typename Action9, typename Action10, typename Action11,
    typename Action12, typename Action13, typename Action14, typename Action15,
    typename Action16, typename Action17, typename Action18, typename Action19,
    typename Action20, typename Action21, typename Action22, typename Action23,
    typename Action24, typename Action25, typename Action26, typename Action27,
    typename Action28, typename Action29, typename Action30, typename Action31,
    typename Action32, typename Action33, typename Action34, typename Action35,
    typename Action36, typename Action37, typename Action38, typename Action39,
    typename Action40>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Action0 action0, Action1 action1,
    Action2 action2, Action3 action3, Action4 action4, Action5 action5,
    Action6 action6, Action7 action7, Action8 action8, Action9 action9,
    Action10 action10, Action11 action11, Action12 action12, Action13 action13,
    Action14 action14, Action15 action15, Action16 action16, Action17 action17,
    Action18 action18, Action19 action19, Action20 action20, Action21 action21,
    Action22 action22, Action23 action23, Action24 action24, Action25 action25,
    Action26 action26, Action27 action27, Action28 action28, Action29 action29,
    Action30 action30, Action31 action31, Action32 action32, Action33 action33,
    Action34 action34, Action35 action35, Action36 action36, Action37 action37,
    Action38 action38, Action39 action39, Action40 action40) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Action0, typename Action1, typename Action2,
    typename Action3, typename Action4, typename Action5, typename Action6,
    typename Action7, typename Action8, typename Action9, typename Action10,
    typename Action11, typename Action12, typename Action13, typename Action14,
    typename Action15, typename Action16, typename Action17, typename Action18,
    typename Action19, typename Action20, typename Action21, typename Action22,
    typename Action23, typename Action24, typename Action25, typename Action26,
    typename Action27, typename Action28, typename Action29, typename Action30,
    typename Action31, typename Action32, typename Action33, typename Action34,
    typename Action35, typename Action36, typename Action37, typename Action38,
    typename Action39, typename Action40, typename Action41>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Check29 check29, Check30 check30, Check31 check31,
            Check32 check32, Check33 check33, Check34 check34, Check35 check35,
            Check36 check36, Check37 check37, Check38 check38, Check39 check39,
            Check40 check40, Check41 check41, Action0 action0, Action1 action1,
            Action2 action2, Action3 action3, Action4 action4, Action5 action5,
            Action6 action6, Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13, Action14 action14, Action15 action15,
            Action16 action16, Action17 action17, Action18 action18,
            Action19 action19, Action20 action20, Action21 action21,
            Action22 action22, Action23 action23, Action24 action24,
            Action25 action25, Action26 action26, Action27 action27,
            Action28 action28, Action29 action29, Action30 action30,
            Action31 action31, Action32 action32, Action33 action33,
            Action34 action34, Action35 action35, Action36 action36,
            Action37 action37, Action38 action38, Action39 action39,
            Action40 action40, Action41 action41) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Action0, typename Action1,
    typename Action2, typename Action3, typename Action4, typename Action5,
    typename Action6, typename Action7, typename Action8, typename Action9,
    typename Action10, typename Action11, typename Action12, typename Action13,
    typename Action14, typename Action15, typename Action16, typename Action17,
    typename Action18, typename Action19, typename Action20, typename Action21,
    typename Action22, typename Action23, typename Action24, typename Action25,
    typename Action26, typename Action27, typename Action28, typename Action29,
    typename Action30, typename Action31, typename Action32, typename Action33,
    typename Action34, typename Action35, typename Action36, typename Action37,
    typename Action38, typename Action39, typename Action40, typename Action41,
    typename Action42>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Action0 action0, Action1 action1, Action2 action2, Action3 action3,
    Action4 action4, Action5 action5, Action6 action6, Action7 action7,
    Action8 action8, Action9 action9, Action10 action10, Action11 action11,
    Action12 action12, Action13 action13, Action14 action14, Action15 action15,
    Action16 action16, Action17 action17, Action18 action18, Action19 action19,
    Action20 action20, Action21 action21, Action22 action22, Action23 action23,
    Action24 action24, Action25 action25, Action26 action26, Action27 action27,
    Action28 action28, Action29 action29, Action30 action30, Action31 action31,
    Action32 action32, Action33 action33, Action34 action34, Action35 action35,
    Action36 action36, Action37 action37, Action38 action38, Action39 action39,
    Action40 action40, Action41 action41, Action42 action42) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Action0,
    typename Action1, typename Action2, typename Action3, typename Action4,
    typename Action5, typename Action6, typename Action7, typename Action8,
    typename Action9, typename Action10, typename Action11, typename Action12,
    typename Action13, typename Action14, typename Action15, typename Action16,
    typename Action17, typename Action18, typename Action19, typename Action20,
    typename Action21, typename Action22, typename Action23, typename Action24,
    typename Action25, typename Action26, typename Action27, typename Action28,
    typename Action29, typename Action30, typename Action31, typename Action32,
    typename Action33, typename Action34, typename Action35, typename Action36,
    typename Action37, typename Action38, typename Action39, typename Action40,
    typename Action41, typename Action42, typename Action43>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Check29 check29, Check30 check30, Check31 check31,
            Check32 check32, Check33 check33, Check34 check34, Check35 check35,
            Check36 check36, Check37 check37, Check38 check38, Check39 check39,
            Check40 check40, Check41 check41, Check42 check42, Check43 check43,
            Action0 action0, Action1 action1, Action2 action2, Action3 action3,
            Action4 action4, Action5 action5, Action6 action6, Action7 action7,
            Action8 action8, Action9 action9, Action10 action10,
            Action11 action11, Action12 action12, Action13 action13,
            Action14 action14, Action15 action15, Action16 action16,
            Action17 action17, Action18 action18, Action19 action19,
            Action20 action20, Action21 action21, Action22 action22,
            Action23 action23, Action24 action24, Action25 action25,
            Action26 action26, Action27 action27, Action28 action28,
            Action29 action29, Action30 action30, Action31 action31,
            Action32 action32, Action33 action33, Action34 action34,
            Action35 action35, Action36 action36, Action37 action37,
            Action38 action38, Action39 action39, Action40 action40,
            Action41 action41, Action42 action42, Action43 action43) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Action0, typename Action1, typename Action2, typename Action3,
    typename Action4, typename Action5, typename Action6, typename Action7,
    typename Action8, typename Action9, typename Action10, typename Action11,
    typename Action12, typename Action13, typename Action14, typename Action15,
    typename Action16, typename Action17, typename Action18, typename Action19,
    typename Action20, typename Action21, typename Action22, typename Action23,
    typename Action24, typename Action25, typename Action26, typename Action27,
    typename Action28, typename Action29, typename Action30, typename Action31,
    typename Action32, typename Action33, typename Action34, typename Action35,
    typename Action36, typename Action37, typename Action38, typename Action39,
    typename Action40, typename Action41, typename Action42, typename Action43,
    typename Action44>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Action0 action0, Action1 action1,
    Action2 action2, Action3 action3, Action4 action4, Action5 action5,
    Action6 action6, Action7 action7, Action8 action8, Action9 action9,
    Action10 action10, Action11 action11, Action12 action12, Action13 action13,
    Action14 action14, Action15 action15, Action16 action16, Action17 action17,
    Action18 action18, Action19 action19, Action20 action20, Action21 action21,
    Action22 action22, Action23 action23, Action24 action24, Action25 action25,
    Action26 action26, Action27 action27, Action28 action28, Action29 action29,
    Action30 action30, Action31 action31, Action32 action32, Action33 action33,
    Action34 action34, Action35 action35, Action36 action36, Action37 action37,
    Action38 action38, Action39 action39, Action40 action40, Action41 action41,
    Action42 action42, Action43 action43, Action44 action44) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Action0, typename Action1, typename Action2,
    typename Action3, typename Action4, typename Action5, typename Action6,
    typename Action7, typename Action8, typename Action9, typename Action10,
    typename Action11, typename Action12, typename Action13, typename Action14,
    typename Action15, typename Action16, typename Action17, typename Action18,
    typename Action19, typename Action20, typename Action21, typename Action22,
    typename Action23, typename Action24, typename Action25, typename Action26,
    typename Action27, typename Action28, typename Action29, typename Action30,
    typename Action31, typename Action32, typename Action33, typename Action34,
    typename Action35, typename Action36, typename Action37, typename Action38,
    typename Action39, typename Action40, typename Action41, typename Action42,
    typename Action43, typename Action44, typename Action45>
auto IfList(CheckArg input, ActionArg action_arg, ActionFail action_fail,
            Check0 check0, Check1 check1, Check2 check2, Check3 check3,
            Check4 check4, Check5 check5, Check6 check6, Check7 check7,
            Check8 check8, Check9 check9, Check10 check10, Check11 check11,
            Check12 check12, Check13 check13, Check14 check14, Check15 check15,
            Check16 check16, Check17 check17, Check18 check18, Check19 check19,
            Check20 check20, Check21 check21, Check22 check22, Check23 check23,
            Check24 check24, Check25 check25, Check26 check26, Check27 check27,
            Check28 check28, Check29 check29, Check30 check30, Check31 check31,
            Check32 check32, Check33 check33, Check34 check34, Check35 check35,
            Check36 check36, Check37 check37, Check38 check38, Check39 check39,
            Check40 check40, Check41 check41, Check42 check42, Check43 check43,
            Check44 check44, Check45 check45, Action0 action0, Action1 action1,
            Action2 action2, Action3 action3, Action4 action4, Action5 action5,
            Action6 action6, Action7 action7, Action8 action8, Action9 action9,
            Action10 action10, Action11 action11, Action12 action12,
            Action13 action13, Action14 action14, Action15 action15,
            Action16 action16, Action17 action17, Action18 action18,
            Action19 action19, Action20 action20, Action21 action21,
            Action22 action22, Action23 action23, Action24 action24,
            Action25 action25, Action26 action26, Action27 action27,
            Action28 action28, Action29 action29, Action30 action30,
            Action31 action31, Action32 action32, Action33 action33,
            Action34 action34, Action35 action35, Action36 action36,
            Action37 action37, Action38 action38, Action39 action39,
            Action40 action40, Action41 action41, Action42 action42,
            Action43 action43, Action44 action44, Action45 action45) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Action0, typename Action1,
    typename Action2, typename Action3, typename Action4, typename Action5,
    typename Action6, typename Action7, typename Action8, typename Action9,
    typename Action10, typename Action11, typename Action12, typename Action13,
    typename Action14, typename Action15, typename Action16, typename Action17,
    typename Action18, typename Action19, typename Action20, typename Action21,
    typename Action22, typename Action23, typename Action24, typename Action25,
    typename Action26, typename Action27, typename Action28, typename Action29,
    typename Action30, typename Action31, typename Action32, typename Action33,
    typename Action34, typename Action35, typename Action36, typename Action37,
    typename Action38, typename Action39, typename Action40, typename Action41,
    typename Action42, typename Action43, typename Action44, typename Action45,
    typename Action46>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Action0 action0, Action1 action1, Action2 action2, Action3 action3,
    Action4 action4, Action5 action5, Action6 action6, Action7 action7,
    Action8 action8, Action9 action9, Action10 action10, Action11 action11,
    Action12 action12, Action13 action13, Action14 action14, Action15 action15,
    Action16 action16, Action17 action17, Action18 action18, Action19 action19,
    Action20 action20, Action21 action21, Action22 action22, Action23 action23,
    Action24 action24, Action25 action25, Action26 action26, Action27 action27,
    Action28 action28, Action29 action29, Action30 action30, Action31 action31,
    Action32 action32, Action33 action33, Action34 action34, Action35 action35,
    Action36 action36, Action37 action37, Action38 action38, Action39 action39,
    Action40 action40, Action41 action41, Action42 action42, Action43 action43,
    Action44 action44, Action45 action45, Action46 action46) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Action0,
    typename Action1, typename Action2, typename Action3, typename Action4,
    typename Action5, typename Action6, typename Action7, typename Action8,
    typename Action9, typename Action10, typename Action11, typename Action12,
    typename Action13, typename Action14, typename Action15, typename Action16,
    typename Action17, typename Action18, typename Action19, typename Action20,
    typename Action21, typename Action22, typename Action23, typename Action24,
    typename Action25, typename Action26, typename Action27, typename Action28,
    typename Action29, typename Action30, typename Action31, typename Action32,
    typename Action33, typename Action34, typename Action35, typename Action36,
    typename Action37, typename Action38, typename Action39, typename Action40,
    typename Action41, typename Action42, typename Action43, typename Action44,
    typename Action45, typename Action46, typename Action47>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Action0 action0, Action1 action1, Action2 action2,
    Action3 action3, Action4 action4, Action5 action5, Action6 action6,
    Action7 action7, Action8 action8, Action9 action9, Action10 action10,
    Action11 action11, Action12 action12, Action13 action13, Action14 action14,
    Action15 action15, Action16 action16, Action17 action17, Action18 action18,
    Action19 action19, Action20 action20, Action21 action21, Action22 action22,
    Action23 action23, Action24 action24, Action25 action25, Action26 action26,
    Action27 action27, Action28 action28, Action29 action29, Action30 action30,
    Action31 action31, Action32 action32, Action33 action33, Action34 action34,
    Action35 action35, Action36 action36, Action37 action37, Action38 action38,
    Action39 action39, Action40 action40, Action41 action41, Action42 action42,
    Action43 action43, Action44 action44, Action45 action45, Action46 action46,
    Action47 action47) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Action0, typename Action1, typename Action2, typename Action3,
    typename Action4, typename Action5, typename Action6, typename Action7,
    typename Action8, typename Action9, typename Action10, typename Action11,
    typename Action12, typename Action13, typename Action14, typename Action15,
    typename Action16, typename Action17, typename Action18, typename Action19,
    typename Action20, typename Action21, typename Action22, typename Action23,
    typename Action24, typename Action25, typename Action26, typename Action27,
    typename Action28, typename Action29, typename Action30, typename Action31,
    typename Action32, typename Action33, typename Action34, typename Action35,
    typename Action36, typename Action37, typename Action38, typename Action39,
    typename Action40, typename Action41, typename Action42, typename Action43,
    typename Action44, typename Action45, typename Action46, typename Action47,
    typename Action48>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Action0 action0, Action1 action1,
    Action2 action2, Action3 action3, Action4 action4, Action5 action5,
    Action6 action6, Action7 action7, Action8 action8, Action9 action9,
    Action10 action10, Action11 action11, Action12 action12, Action13 action13,
    Action14 action14, Action15 action15, Action16 action16, Action17 action17,
    Action18 action18, Action19 action19, Action20 action20, Action21 action21,
    Action22 action22, Action23 action23, Action24 action24, Action25 action25,
    Action26 action26, Action27 action27, Action28 action28, Action29 action29,
    Action30 action30, Action31 action31, Action32 action32, Action33 action33,
    Action34 action34, Action35 action35, Action36 action36, Action37 action37,
    Action38 action38, Action39 action39, Action40 action40, Action41 action41,
    Action42 action42, Action43 action43, Action44 action44, Action45 action45,
    Action46 action46, Action47 action47, Action48 action48) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Check49, typename Action0, typename Action1, typename Action2,
    typename Action3, typename Action4, typename Action5, typename Action6,
    typename Action7, typename Action8, typename Action9, typename Action10,
    typename Action11, typename Action12, typename Action13, typename Action14,
    typename Action15, typename Action16, typename Action17, typename Action18,
    typename Action19, typename Action20, typename Action21, typename Action22,
    typename Action23, typename Action24, typename Action25, typename Action26,
    typename Action27, typename Action28, typename Action29, typename Action30,
    typename Action31, typename Action32, typename Action33, typename Action34,
    typename Action35, typename Action36, typename Action37, typename Action38,
    typename Action39, typename Action40, typename Action41, typename Action42,
    typename Action43, typename Action44, typename Action45, typename Action46,
    typename Action47, typename Action48, typename Action49>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Check49 check49, Action0 action0,
    Action1 action1, Action2 action2, Action3 action3, Action4 action4,
    Action5 action5, Action6 action6, Action7 action7, Action8 action8,
    Action9 action9, Action10 action10, Action11 action11, Action12 action12,
    Action13 action13, Action14 action14, Action15 action15, Action16 action16,
    Action17 action17, Action18 action18, Action19 action19, Action20 action20,
    Action21 action21, Action22 action22, Action23 action23, Action24 action24,
    Action25 action25, Action26 action26, Action27 action27, Action28 action28,
    Action29 action29, Action30 action30, Action31 action31, Action32 action32,
    Action33 action33, Action34 action34, Action35 action35, Action36 action36,
    Action37 action37, Action38 action38, Action39 action39, Action40 action40,
    Action41 action41, Action42 action42, Action43 action43, Action44 action44,
    Action45 action45, Action46 action46, Action47 action47, Action48 action48,
    Action49 action49) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  if (check49(input)) return action49(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Check49, typename Check50, typename Action0, typename Action1,
    typename Action2, typename Action3, typename Action4, typename Action5,
    typename Action6, typename Action7, typename Action8, typename Action9,
    typename Action10, typename Action11, typename Action12, typename Action13,
    typename Action14, typename Action15, typename Action16, typename Action17,
    typename Action18, typename Action19, typename Action20, typename Action21,
    typename Action22, typename Action23, typename Action24, typename Action25,
    typename Action26, typename Action27, typename Action28, typename Action29,
    typename Action30, typename Action31, typename Action32, typename Action33,
    typename Action34, typename Action35, typename Action36, typename Action37,
    typename Action38, typename Action39, typename Action40, typename Action41,
    typename Action42, typename Action43, typename Action44, typename Action45,
    typename Action46, typename Action47, typename Action48, typename Action49,
    typename Action50>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Check49 check49, Check50 check50,
    Action0 action0, Action1 action1, Action2 action2, Action3 action3,
    Action4 action4, Action5 action5, Action6 action6, Action7 action7,
    Action8 action8, Action9 action9, Action10 action10, Action11 action11,
    Action12 action12, Action13 action13, Action14 action14, Action15 action15,
    Action16 action16, Action17 action17, Action18 action18, Action19 action19,
    Action20 action20, Action21 action21, Action22 action22, Action23 action23,
    Action24 action24, Action25 action25, Action26 action26, Action27 action27,
    Action28 action28, Action29 action29, Action30 action30, Action31 action31,
    Action32 action32, Action33 action33, Action34 action34, Action35 action35,
    Action36 action36, Action37 action37, Action38 action38, Action39 action39,
    Action40 action40, Action41 action41, Action42 action42, Action43 action43,
    Action44 action44, Action45 action45, Action46 action46, Action47 action47,
    Action48 action48, Action49 action49, Action50 action50) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  if (check49(input)) return action49(action_arg);
  if (check50(input)) return action50(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Check49, typename Check50, typename Check51, typename Action0,
    typename Action1, typename Action2, typename Action3, typename Action4,
    typename Action5, typename Action6, typename Action7, typename Action8,
    typename Action9, typename Action10, typename Action11, typename Action12,
    typename Action13, typename Action14, typename Action15, typename Action16,
    typename Action17, typename Action18, typename Action19, typename Action20,
    typename Action21, typename Action22, typename Action23, typename Action24,
    typename Action25, typename Action26, typename Action27, typename Action28,
    typename Action29, typename Action30, typename Action31, typename Action32,
    typename Action33, typename Action34, typename Action35, typename Action36,
    typename Action37, typename Action38, typename Action39, typename Action40,
    typename Action41, typename Action42, typename Action43, typename Action44,
    typename Action45, typename Action46, typename Action47, typename Action48,
    typename Action49, typename Action50, typename Action51>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Check49 check49, Check50 check50,
    Check51 check51, Action0 action0, Action1 action1, Action2 action2,
    Action3 action3, Action4 action4, Action5 action5, Action6 action6,
    Action7 action7, Action8 action8, Action9 action9, Action10 action10,
    Action11 action11, Action12 action12, Action13 action13, Action14 action14,
    Action15 action15, Action16 action16, Action17 action17, Action18 action18,
    Action19 action19, Action20 action20, Action21 action21, Action22 action22,
    Action23 action23, Action24 action24, Action25 action25, Action26 action26,
    Action27 action27, Action28 action28, Action29 action29, Action30 action30,
    Action31 action31, Action32 action32, Action33 action33, Action34 action34,
    Action35 action35, Action36 action36, Action37 action37, Action38 action38,
    Action39 action39, Action40 action40, Action41 action41, Action42 action42,
    Action43 action43, Action44 action44, Action45 action45, Action46 action46,
    Action47 action47, Action48 action48, Action49 action49, Action50 action50,
    Action51 action51) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  if (check49(input)) return action49(action_arg);
  if (check50(input)) return action50(action_arg);
  if (check51(input)) return action51(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Check49, typename Check50, typename Check51, typename Check52,
    typename Action0, typename Action1, typename Action2, typename Action3,
    typename Action4, typename Action5, typename Action6, typename Action7,
    typename Action8, typename Action9, typename Action10, typename Action11,
    typename Action12, typename Action13, typename Action14, typename Action15,
    typename Action16, typename Action17, typename Action18, typename Action19,
    typename Action20, typename Action21, typename Action22, typename Action23,
    typename Action24, typename Action25, typename Action26, typename Action27,
    typename Action28, typename Action29, typename Action30, typename Action31,
    typename Action32, typename Action33, typename Action34, typename Action35,
    typename Action36, typename Action37, typename Action38, typename Action39,
    typename Action40, typename Action41, typename Action42, typename Action43,
    typename Action44, typename Action45, typename Action46, typename Action47,
    typename Action48, typename Action49, typename Action50, typename Action51,
    typename Action52>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Check49 check49, Check50 check50,
    Check51 check51, Check52 check52, Action0 action0, Action1 action1,
    Action2 action2, Action3 action3, Action4 action4, Action5 action5,
    Action6 action6, Action7 action7, Action8 action8, Action9 action9,
    Action10 action10, Action11 action11, Action12 action12, Action13 action13,
    Action14 action14, Action15 action15, Action16 action16, Action17 action17,
    Action18 action18, Action19 action19, Action20 action20, Action21 action21,
    Action22 action22, Action23 action23, Action24 action24, Action25 action25,
    Action26 action26, Action27 action27, Action28 action28, Action29 action29,
    Action30 action30, Action31 action31, Action32 action32, Action33 action33,
    Action34 action34, Action35 action35, Action36 action36, Action37 action37,
    Action38 action38, Action39 action39, Action40 action40, Action41 action41,
    Action42 action42, Action43 action43, Action44 action44, Action45 action45,
    Action46 action46, Action47 action47, Action48 action48, Action49 action49,
    Action50 action50, Action51 action51, Action52 action52) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  if (check49(input)) return action49(action_arg);
  if (check50(input)) return action50(action_arg);
  if (check51(input)) return action51(action_arg);
  if (check52(input)) return action52(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Check49, typename Check50, typename Check51, typename Check52,
    typename Check53, typename Action0, typename Action1, typename Action2,
    typename Action3, typename Action4, typename Action5, typename Action6,
    typename Action7, typename Action8, typename Action9, typename Action10,
    typename Action11, typename Action12, typename Action13, typename Action14,
    typename Action15, typename Action16, typename Action17, typename Action18,
    typename Action19, typename Action20, typename Action21, typename Action22,
    typename Action23, typename Action24, typename Action25, typename Action26,
    typename Action27, typename Action28, typename Action29, typename Action30,
    typename Action31, typename Action32, typename Action33, typename Action34,
    typename Action35, typename Action36, typename Action37, typename Action38,
    typename Action39, typename Action40, typename Action41, typename Action42,
    typename Action43, typename Action44, typename Action45, typename Action46,
    typename Action47, typename Action48, typename Action49, typename Action50,
    typename Action51, typename Action52, typename Action53>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Check49 check49, Check50 check50,
    Check51 check51, Check52 check52, Check53 check53, Action0 action0,
    Action1 action1, Action2 action2, Action3 action3, Action4 action4,
    Action5 action5, Action6 action6, Action7 action7, Action8 action8,
    Action9 action9, Action10 action10, Action11 action11, Action12 action12,
    Action13 action13, Action14 action14, Action15 action15, Action16 action16,
    Action17 action17, Action18 action18, Action19 action19, Action20 action20,
    Action21 action21, Action22 action22, Action23 action23, Action24 action24,
    Action25 action25, Action26 action26, Action27 action27, Action28 action28,
    Action29 action29, Action30 action30, Action31 action31, Action32 action32,
    Action33 action33, Action34 action34, Action35 action35, Action36 action36,
    Action37 action37, Action38 action38, Action39 action39, Action40 action40,
    Action41 action41, Action42 action42, Action43 action43, Action44 action44,
    Action45 action45, Action46 action46, Action47 action47, Action48 action48,
    Action49 action49, Action50 action50, Action51 action51, Action52 action52,
    Action53 action53) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  if (check49(input)) return action49(action_arg);
  if (check50(input)) return action50(action_arg);
  if (check51(input)) return action51(action_arg);
  if (check52(input)) return action52(action_arg);
  if (check53(input)) return action53(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Check49, typename Check50, typename Check51, typename Check52,
    typename Check53, typename Check54, typename Action0, typename Action1,
    typename Action2, typename Action3, typename Action4, typename Action5,
    typename Action6, typename Action7, typename Action8, typename Action9,
    typename Action10, typename Action11, typename Action12, typename Action13,
    typename Action14, typename Action15, typename Action16, typename Action17,
    typename Action18, typename Action19, typename Action20, typename Action21,
    typename Action22, typename Action23, typename Action24, typename Action25,
    typename Action26, typename Action27, typename Action28, typename Action29,
    typename Action30, typename Action31, typename Action32, typename Action33,
    typename Action34, typename Action35, typename Action36, typename Action37,
    typename Action38, typename Action39, typename Action40, typename Action41,
    typename Action42, typename Action43, typename Action44, typename Action45,
    typename Action46, typename Action47, typename Action48, typename Action49,
    typename Action50, typename Action51, typename Action52, typename Action53,
    typename Action54>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Check49 check49, Check50 check50,
    Check51 check51, Check52 check52, Check53 check53, Check54 check54,
    Action0 action0, Action1 action1, Action2 action2, Action3 action3,
    Action4 action4, Action5 action5, Action6 action6, Action7 action7,
    Action8 action8, Action9 action9, Action10 action10, Action11 action11,
    Action12 action12, Action13 action13, Action14 action14, Action15 action15,
    Action16 action16, Action17 action17, Action18 action18, Action19 action19,
    Action20 action20, Action21 action21, Action22 action22, Action23 action23,
    Action24 action24, Action25 action25, Action26 action26, Action27 action27,
    Action28 action28, Action29 action29, Action30 action30, Action31 action31,
    Action32 action32, Action33 action33, Action34 action34, Action35 action35,
    Action36 action36, Action37 action37, Action38 action38, Action39 action39,
    Action40 action40, Action41 action41, Action42 action42, Action43 action43,
    Action44 action44, Action45 action45, Action46 action46, Action47 action47,
    Action48 action48, Action49 action49, Action50 action50, Action51 action51,
    Action52 action52, Action53 action53, Action54 action54) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  if (check49(input)) return action49(action_arg);
  if (check50(input)) return action50(action_arg);
  if (check51(input)) return action51(action_arg);
  if (check52(input)) return action52(action_arg);
  if (check53(input)) return action53(action_arg);
  if (check54(input)) return action54(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Check49, typename Check50, typename Check51, typename Check52,
    typename Check53, typename Check54, typename Check55, typename Action0,
    typename Action1, typename Action2, typename Action3, typename Action4,
    typename Action5, typename Action6, typename Action7, typename Action8,
    typename Action9, typename Action10, typename Action11, typename Action12,
    typename Action13, typename Action14, typename Action15, typename Action16,
    typename Action17, typename Action18, typename Action19, typename Action20,
    typename Action21, typename Action22, typename Action23, typename Action24,
    typename Action25, typename Action26, typename Action27, typename Action28,
    typename Action29, typename Action30, typename Action31, typename Action32,
    typename Action33, typename Action34, typename Action35, typename Action36,
    typename Action37, typename Action38, typename Action39, typename Action40,
    typename Action41, typename Action42, typename Action43, typename Action44,
    typename Action45, typename Action46, typename Action47, typename Action48,
    typename Action49, typename Action50, typename Action51, typename Action52,
    typename Action53, typename Action54, typename Action55>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Check49 check49, Check50 check50,
    Check51 check51, Check52 check52, Check53 check53, Check54 check54,
    Check55 check55, Action0 action0, Action1 action1, Action2 action2,
    Action3 action3, Action4 action4, Action5 action5, Action6 action6,
    Action7 action7, Action8 action8, Action9 action9, Action10 action10,
    Action11 action11, Action12 action12, Action13 action13, Action14 action14,
    Action15 action15, Action16 action16, Action17 action17, Action18 action18,
    Action19 action19, Action20 action20, Action21 action21, Action22 action22,
    Action23 action23, Action24 action24, Action25 action25, Action26 action26,
    Action27 action27, Action28 action28, Action29 action29, Action30 action30,
    Action31 action31, Action32 action32, Action33 action33, Action34 action34,
    Action35 action35, Action36 action36, Action37 action37, Action38 action38,
    Action39 action39, Action40 action40, Action41 action41, Action42 action42,
    Action43 action43, Action44 action44, Action45 action45, Action46 action46,
    Action47 action47, Action48 action48, Action49 action49, Action50 action50,
    Action51 action51, Action52 action52, Action53 action53, Action54 action54,
    Action55 action55) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  if (check49(input)) return action49(action_arg);
  if (check50(input)) return action50(action_arg);
  if (check51(input)) return action51(action_arg);
  if (check52(input)) return action52(action_arg);
  if (check53(input)) return action53(action_arg);
  if (check54(input)) return action54(action_arg);
  if (check55(input)) return action55(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Check49, typename Check50, typename Check51, typename Check52,
    typename Check53, typename Check54, typename Check55, typename Check56,
    typename Action0, typename Action1, typename Action2, typename Action3,
    typename Action4, typename Action5, typename Action6, typename Action7,
    typename Action8, typename Action9, typename Action10, typename Action11,
    typename Action12, typename Action13, typename Action14, typename Action15,
    typename Action16, typename Action17, typename Action18, typename Action19,
    typename Action20, typename Action21, typename Action22, typename Action23,
    typename Action24, typename Action25, typename Action26, typename Action27,
    typename Action28, typename Action29, typename Action30, typename Action31,
    typename Action32, typename Action33, typename Action34, typename Action35,
    typename Action36, typename Action37, typename Action38, typename Action39,
    typename Action40, typename Action41, typename Action42, typename Action43,
    typename Action44, typename Action45, typename Action46, typename Action47,
    typename Action48, typename Action49, typename Action50, typename Action51,
    typename Action52, typename Action53, typename Action54, typename Action55,
    typename Action56>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Check49 check49, Check50 check50,
    Check51 check51, Check52 check52, Check53 check53, Check54 check54,
    Check55 check55, Check56 check56, Action0 action0, Action1 action1,
    Action2 action2, Action3 action3, Action4 action4, Action5 action5,
    Action6 action6, Action7 action7, Action8 action8, Action9 action9,
    Action10 action10, Action11 action11, Action12 action12, Action13 action13,
    Action14 action14, Action15 action15, Action16 action16, Action17 action17,
    Action18 action18, Action19 action19, Action20 action20, Action21 action21,
    Action22 action22, Action23 action23, Action24 action24, Action25 action25,
    Action26 action26, Action27 action27, Action28 action28, Action29 action29,
    Action30 action30, Action31 action31, Action32 action32, Action33 action33,
    Action34 action34, Action35 action35, Action36 action36, Action37 action37,
    Action38 action38, Action39 action39, Action40 action40, Action41 action41,
    Action42 action42, Action43 action43, Action44 action44, Action45 action45,
    Action46 action46, Action47 action47, Action48 action48, Action49 action49,
    Action50 action50, Action51 action51, Action52 action52, Action53 action53,
    Action54 action54, Action55 action55, Action56 action56) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  if (check49(input)) return action49(action_arg);
  if (check50(input)) return action50(action_arg);
  if (check51(input)) return action51(action_arg);
  if (check52(input)) return action52(action_arg);
  if (check53(input)) return action53(action_arg);
  if (check54(input)) return action54(action_arg);
  if (check55(input)) return action55(action_arg);
  if (check56(input)) return action56(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Check49, typename Check50, typename Check51, typename Check52,
    typename Check53, typename Check54, typename Check55, typename Check56,
    typename Check57, typename Action0, typename Action1, typename Action2,
    typename Action3, typename Action4, typename Action5, typename Action6,
    typename Action7, typename Action8, typename Action9, typename Action10,
    typename Action11, typename Action12, typename Action13, typename Action14,
    typename Action15, typename Action16, typename Action17, typename Action18,
    typename Action19, typename Action20, typename Action21, typename Action22,
    typename Action23, typename Action24, typename Action25, typename Action26,
    typename Action27, typename Action28, typename Action29, typename Action30,
    typename Action31, typename Action32, typename Action33, typename Action34,
    typename Action35, typename Action36, typename Action37, typename Action38,
    typename Action39, typename Action40, typename Action41, typename Action42,
    typename Action43, typename Action44, typename Action45, typename Action46,
    typename Action47, typename Action48, typename Action49, typename Action50,
    typename Action51, typename Action52, typename Action53, typename Action54,
    typename Action55, typename Action56, typename Action57>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Check49 check49, Check50 check50,
    Check51 check51, Check52 check52, Check53 check53, Check54 check54,
    Check55 check55, Check56 check56, Check57 check57, Action0 action0,
    Action1 action1, Action2 action2, Action3 action3, Action4 action4,
    Action5 action5, Action6 action6, Action7 action7, Action8 action8,
    Action9 action9, Action10 action10, Action11 action11, Action12 action12,
    Action13 action13, Action14 action14, Action15 action15, Action16 action16,
    Action17 action17, Action18 action18, Action19 action19, Action20 action20,
    Action21 action21, Action22 action22, Action23 action23, Action24 action24,
    Action25 action25, Action26 action26, Action27 action27, Action28 action28,
    Action29 action29, Action30 action30, Action31 action31, Action32 action32,
    Action33 action33, Action34 action34, Action35 action35, Action36 action36,
    Action37 action37, Action38 action38, Action39 action39, Action40 action40,
    Action41 action41, Action42 action42, Action43 action43, Action44 action44,
    Action45 action45, Action46 action46, Action47 action47, Action48 action48,
    Action49 action49, Action50 action50, Action51 action51, Action52 action52,
    Action53 action53, Action54 action54, Action55 action55, Action56 action56,
    Action57 action57) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  if (check49(input)) return action49(action_arg);
  if (check50(input)) return action50(action_arg);
  if (check51(input)) return action51(action_arg);
  if (check52(input)) return action52(action_arg);
  if (check53(input)) return action53(action_arg);
  if (check54(input)) return action54(action_arg);
  if (check55(input)) return action55(action_arg);
  if (check56(input)) return action56(action_arg);
  if (check57(input)) return action57(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Check49, typename Check50, typename Check51, typename Check52,
    typename Check53, typename Check54, typename Check55, typename Check56,
    typename Check57, typename Check58, typename Action0, typename Action1,
    typename Action2, typename Action3, typename Action4, typename Action5,
    typename Action6, typename Action7, typename Action8, typename Action9,
    typename Action10, typename Action11, typename Action12, typename Action13,
    typename Action14, typename Action15, typename Action16, typename Action17,
    typename Action18, typename Action19, typename Action20, typename Action21,
    typename Action22, typename Action23, typename Action24, typename Action25,
    typename Action26, typename Action27, typename Action28, typename Action29,
    typename Action30, typename Action31, typename Action32, typename Action33,
    typename Action34, typename Action35, typename Action36, typename Action37,
    typename Action38, typename Action39, typename Action40, typename Action41,
    typename Action42, typename Action43, typename Action44, typename Action45,
    typename Action46, typename Action47, typename Action48, typename Action49,
    typename Action50, typename Action51, typename Action52, typename Action53,
    typename Action54, typename Action55, typename Action56, typename Action57,
    typename Action58>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Check49 check49, Check50 check50,
    Check51 check51, Check52 check52, Check53 check53, Check54 check54,
    Check55 check55, Check56 check56, Check57 check57, Check58 check58,
    Action0 action0, Action1 action1, Action2 action2, Action3 action3,
    Action4 action4, Action5 action5, Action6 action6, Action7 action7,
    Action8 action8, Action9 action9, Action10 action10, Action11 action11,
    Action12 action12, Action13 action13, Action14 action14, Action15 action15,
    Action16 action16, Action17 action17, Action18 action18, Action19 action19,
    Action20 action20, Action21 action21, Action22 action22, Action23 action23,
    Action24 action24, Action25 action25, Action26 action26, Action27 action27,
    Action28 action28, Action29 action29, Action30 action30, Action31 action31,
    Action32 action32, Action33 action33, Action34 action34, Action35 action35,
    Action36 action36, Action37 action37, Action38 action38, Action39 action39,
    Action40 action40, Action41 action41, Action42 action42, Action43 action43,
    Action44 action44, Action45 action45, Action46 action46, Action47 action47,
    Action48 action48, Action49 action49, Action50 action50, Action51 action51,
    Action52 action52, Action53 action53, Action54 action54, Action55 action55,
    Action56 action56, Action57 action57, Action58 action58) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  if (check49(input)) return action49(action_arg);
  if (check50(input)) return action50(action_arg);
  if (check51(input)) return action51(action_arg);
  if (check52(input)) return action52(action_arg);
  if (check53(input)) return action53(action_arg);
  if (check54(input)) return action54(action_arg);
  if (check55(input)) return action55(action_arg);
  if (check56(input)) return action56(action_arg);
  if (check57(input)) return action57(action_arg);
  if (check58(input)) return action58(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Check49, typename Check50, typename Check51, typename Check52,
    typename Check53, typename Check54, typename Check55, typename Check56,
    typename Check57, typename Check58, typename Check59, typename Action0,
    typename Action1, typename Action2, typename Action3, typename Action4,
    typename Action5, typename Action6, typename Action7, typename Action8,
    typename Action9, typename Action10, typename Action11, typename Action12,
    typename Action13, typename Action14, typename Action15, typename Action16,
    typename Action17, typename Action18, typename Action19, typename Action20,
    typename Action21, typename Action22, typename Action23, typename Action24,
    typename Action25, typename Action26, typename Action27, typename Action28,
    typename Action29, typename Action30, typename Action31, typename Action32,
    typename Action33, typename Action34, typename Action35, typename Action36,
    typename Action37, typename Action38, typename Action39, typename Action40,
    typename Action41, typename Action42, typename Action43, typename Action44,
    typename Action45, typename Action46, typename Action47, typename Action48,
    typename Action49, typename Action50, typename Action51, typename Action52,
    typename Action53, typename Action54, typename Action55, typename Action56,
    typename Action57, typename Action58, typename Action59>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Check49 check49, Check50 check50,
    Check51 check51, Check52 check52, Check53 check53, Check54 check54,
    Check55 check55, Check56 check56, Check57 check57, Check58 check58,
    Check59 check59, Action0 action0, Action1 action1, Action2 action2,
    Action3 action3, Action4 action4, Action5 action5, Action6 action6,
    Action7 action7, Action8 action8, Action9 action9, Action10 action10,
    Action11 action11, Action12 action12, Action13 action13, Action14 action14,
    Action15 action15, Action16 action16, Action17 action17, Action18 action18,
    Action19 action19, Action20 action20, Action21 action21, Action22 action22,
    Action23 action23, Action24 action24, Action25 action25, Action26 action26,
    Action27 action27, Action28 action28, Action29 action29, Action30 action30,
    Action31 action31, Action32 action32, Action33 action33, Action34 action34,
    Action35 action35, Action36 action36, Action37 action37, Action38 action38,
    Action39 action39, Action40 action40, Action41 action41, Action42 action42,
    Action43 action43, Action44 action44, Action45 action45, Action46 action46,
    Action47 action47, Action48 action48, Action49 action49, Action50 action50,
    Action51 action51, Action52 action52, Action53 action53, Action54 action54,
    Action55 action55, Action56 action56, Action57 action57, Action58 action58,
    Action59 action59) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  if (check49(input)) return action49(action_arg);
  if (check50(input)) return action50(action_arg);
  if (check51(input)) return action51(action_arg);
  if (check52(input)) return action52(action_arg);
  if (check53(input)) return action53(action_arg);
  if (check54(input)) return action54(action_arg);
  if (check55(input)) return action55(action_arg);
  if (check56(input)) return action56(action_arg);
  if (check57(input)) return action57(action_arg);
  if (check58(input)) return action58(action_arg);
  if (check59(input)) return action59(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Check49, typename Check50, typename Check51, typename Check52,
    typename Check53, typename Check54, typename Check55, typename Check56,
    typename Check57, typename Check58, typename Check59, typename Check60,
    typename Action0, typename Action1, typename Action2, typename Action3,
    typename Action4, typename Action5, typename Action6, typename Action7,
    typename Action8, typename Action9, typename Action10, typename Action11,
    typename Action12, typename Action13, typename Action14, typename Action15,
    typename Action16, typename Action17, typename Action18, typename Action19,
    typename Action20, typename Action21, typename Action22, typename Action23,
    typename Action24, typename Action25, typename Action26, typename Action27,
    typename Action28, typename Action29, typename Action30, typename Action31,
    typename Action32, typename Action33, typename Action34, typename Action35,
    typename Action36, typename Action37, typename Action38, typename Action39,
    typename Action40, typename Action41, typename Action42, typename Action43,
    typename Action44, typename Action45, typename Action46, typename Action47,
    typename Action48, typename Action49, typename Action50, typename Action51,
    typename Action52, typename Action53, typename Action54, typename Action55,
    typename Action56, typename Action57, typename Action58, typename Action59,
    typename Action60>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Check49 check49, Check50 check50,
    Check51 check51, Check52 check52, Check53 check53, Check54 check54,
    Check55 check55, Check56 check56, Check57 check57, Check58 check58,
    Check59 check59, Check60 check60, Action0 action0, Action1 action1,
    Action2 action2, Action3 action3, Action4 action4, Action5 action5,
    Action6 action6, Action7 action7, Action8 action8, Action9 action9,
    Action10 action10, Action11 action11, Action12 action12, Action13 action13,
    Action14 action14, Action15 action15, Action16 action16, Action17 action17,
    Action18 action18, Action19 action19, Action20 action20, Action21 action21,
    Action22 action22, Action23 action23, Action24 action24, Action25 action25,
    Action26 action26, Action27 action27, Action28 action28, Action29 action29,
    Action30 action30, Action31 action31, Action32 action32, Action33 action33,
    Action34 action34, Action35 action35, Action36 action36, Action37 action37,
    Action38 action38, Action39 action39, Action40 action40, Action41 action41,
    Action42 action42, Action43 action43, Action44 action44, Action45 action45,
    Action46 action46, Action47 action47, Action48 action48, Action49 action49,
    Action50 action50, Action51 action51, Action52 action52, Action53 action53,
    Action54 action54, Action55 action55, Action56 action56, Action57 action57,
    Action58 action58, Action59 action59, Action60 action60) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  if (check49(input)) return action49(action_arg);
  if (check50(input)) return action50(action_arg);
  if (check51(input)) return action51(action_arg);
  if (check52(input)) return action52(action_arg);
  if (check53(input)) return action53(action_arg);
  if (check54(input)) return action54(action_arg);
  if (check55(input)) return action55(action_arg);
  if (check56(input)) return action56(action_arg);
  if (check57(input)) return action57(action_arg);
  if (check58(input)) return action58(action_arg);
  if (check59(input)) return action59(action_arg);
  if (check60(input)) return action60(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Check49, typename Check50, typename Check51, typename Check52,
    typename Check53, typename Check54, typename Check55, typename Check56,
    typename Check57, typename Check58, typename Check59, typename Check60,
    typename Check61, typename Action0, typename Action1, typename Action2,
    typename Action3, typename Action4, typename Action5, typename Action6,
    typename Action7, typename Action8, typename Action9, typename Action10,
    typename Action11, typename Action12, typename Action13, typename Action14,
    typename Action15, typename Action16, typename Action17, typename Action18,
    typename Action19, typename Action20, typename Action21, typename Action22,
    typename Action23, typename Action24, typename Action25, typename Action26,
    typename Action27, typename Action28, typename Action29, typename Action30,
    typename Action31, typename Action32, typename Action33, typename Action34,
    typename Action35, typename Action36, typename Action37, typename Action38,
    typename Action39, typename Action40, typename Action41, typename Action42,
    typename Action43, typename Action44, typename Action45, typename Action46,
    typename Action47, typename Action48, typename Action49, typename Action50,
    typename Action51, typename Action52, typename Action53, typename Action54,
    typename Action55, typename Action56, typename Action57, typename Action58,
    typename Action59, typename Action60, typename Action61>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Check49 check49, Check50 check50,
    Check51 check51, Check52 check52, Check53 check53, Check54 check54,
    Check55 check55, Check56 check56, Check57 check57, Check58 check58,
    Check59 check59, Check60 check60, Check61 check61, Action0 action0,
    Action1 action1, Action2 action2, Action3 action3, Action4 action4,
    Action5 action5, Action6 action6, Action7 action7, Action8 action8,
    Action9 action9, Action10 action10, Action11 action11, Action12 action12,
    Action13 action13, Action14 action14, Action15 action15, Action16 action16,
    Action17 action17, Action18 action18, Action19 action19, Action20 action20,
    Action21 action21, Action22 action22, Action23 action23, Action24 action24,
    Action25 action25, Action26 action26, Action27 action27, Action28 action28,
    Action29 action29, Action30 action30, Action31 action31, Action32 action32,
    Action33 action33, Action34 action34, Action35 action35, Action36 action36,
    Action37 action37, Action38 action38, Action39 action39, Action40 action40,
    Action41 action41, Action42 action42, Action43 action43, Action44 action44,
    Action45 action45, Action46 action46, Action47 action47, Action48 action48,
    Action49 action49, Action50 action50, Action51 action51, Action52 action52,
    Action53 action53, Action54 action54, Action55 action55, Action56 action56,
    Action57 action57, Action58 action58, Action59 action59, Action60 action60,
    Action61 action61) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  if (check49(input)) return action49(action_arg);
  if (check50(input)) return action50(action_arg);
  if (check51(input)) return action51(action_arg);
  if (check52(input)) return action52(action_arg);
  if (check53(input)) return action53(action_arg);
  if (check54(input)) return action54(action_arg);
  if (check55(input)) return action55(action_arg);
  if (check56(input)) return action56(action_arg);
  if (check57(input)) return action57(action_arg);
  if (check58(input)) return action58(action_arg);
  if (check59(input)) return action59(action_arg);
  if (check60(input)) return action60(action_arg);
  if (check61(input)) return action61(action_arg);
  return action_fail(action_arg);
}

template <
    typename CheckArg, typename ActionArg, typename ActionFail, typename Check0,
    typename Check1, typename Check2, typename Check3, typename Check4,
    typename Check5, typename Check6, typename Check7, typename Check8,
    typename Check9, typename Check10, typename Check11, typename Check12,
    typename Check13, typename Check14, typename Check15, typename Check16,
    typename Check17, typename Check18, typename Check19, typename Check20,
    typename Check21, typename Check22, typename Check23, typename Check24,
    typename Check25, typename Check26, typename Check27, typename Check28,
    typename Check29, typename Check30, typename Check31, typename Check32,
    typename Check33, typename Check34, typename Check35, typename Check36,
    typename Check37, typename Check38, typename Check39, typename Check40,
    typename Check41, typename Check42, typename Check43, typename Check44,
    typename Check45, typename Check46, typename Check47, typename Check48,
    typename Check49, typename Check50, typename Check51, typename Check52,
    typename Check53, typename Check54, typename Check55, typename Check56,
    typename Check57, typename Check58, typename Check59, typename Check60,
    typename Check61, typename Check62, typename Action0, typename Action1,
    typename Action2, typename Action3, typename Action4, typename Action5,
    typename Action6, typename Action7, typename Action8, typename Action9,
    typename Action10, typename Action11, typename Action12, typename Action13,
    typename Action14, typename Action15, typename Action16, typename Action17,
    typename Action18, typename Action19, typename Action20, typename Action21,
    typename Action22, typename Action23, typename Action24, typename Action25,
    typename Action26, typename Action27, typename Action28, typename Action29,
    typename Action30, typename Action31, typename Action32, typename Action33,
    typename Action34, typename Action35, typename Action36, typename Action37,
    typename Action38, typename Action39, typename Action40, typename Action41,
    typename Action42, typename Action43, typename Action44, typename Action45,
    typename Action46, typename Action47, typename Action48, typename Action49,
    typename Action50, typename Action51, typename Action52, typename Action53,
    typename Action54, typename Action55, typename Action56, typename Action57,
    typename Action58, typename Action59, typename Action60, typename Action61,
    typename Action62>
auto IfList(
    CheckArg input, ActionArg action_arg, ActionFail action_fail, Check0 check0,
    Check1 check1, Check2 check2, Check3 check3, Check4 check4, Check5 check5,
    Check6 check6, Check7 check7, Check8 check8, Check9 check9, Check10 check10,
    Check11 check11, Check12 check12, Check13 check13, Check14 check14,
    Check15 check15, Check16 check16, Check17 check17, Check18 check18,
    Check19 check19, Check20 check20, Check21 check21, Check22 check22,
    Check23 check23, Check24 check24, Check25 check25, Check26 check26,
    Check27 check27, Check28 check28, Check29 check29, Check30 check30,
    Check31 check31, Check32 check32, Check33 check33, Check34 check34,
    Check35 check35, Check36 check36, Check37 check37, Check38 check38,
    Check39 check39, Check40 check40, Check41 check41, Check42 check42,
    Check43 check43, Check44 check44, Check45 check45, Check46 check46,
    Check47 check47, Check48 check48, Check49 check49, Check50 check50,
    Check51 check51, Check52 check52, Check53 check53, Check54 check54,
    Check55 check55, Check56 check56, Check57 check57, Check58 check58,
    Check59 check59, Check60 check60, Check61 check61, Check62 check62,
    Action0 action0, Action1 action1, Action2 action2, Action3 action3,
    Action4 action4, Action5 action5, Action6 action6, Action7 action7,
    Action8 action8, Action9 action9, Action10 action10, Action11 action11,
    Action12 action12, Action13 action13, Action14 action14, Action15 action15,
    Action16 action16, Action17 action17, Action18 action18, Action19 action19,
    Action20 action20, Action21 action21, Action22 action22, Action23 action23,
    Action24 action24, Action25 action25, Action26 action26, Action27 action27,
    Action28 action28, Action29 action29, Action30 action30, Action31 action31,
    Action32 action32, Action33 action33, Action34 action34, Action35 action35,
    Action36 action36, Action37 action37, Action38 action38, Action39 action39,
    Action40 action40, Action41 action41, Action42 action42, Action43 action43,
    Action44 action44, Action45 action45, Action46 action46, Action47 action47,
    Action48 action48, Action49 action49, Action50 action50, Action51 action51,
    Action52 action52, Action53 action53, Action54 action54, Action55 action55,
    Action56 action56, Action57 action57, Action58 action58, Action59 action59,
    Action60 action60, Action61 action61, Action62 action62) {
  if (check0(input)) return action0(action_arg);
  if (check1(input)) return action1(action_arg);
  if (check2(input)) return action2(action_arg);
  if (check3(input)) return action3(action_arg);
  if (check4(input)) return action4(action_arg);
  if (check5(input)) return action5(action_arg);
  if (check6(input)) return action6(action_arg);
  if (check7(input)) return action7(action_arg);
  if (check8(input)) return action8(action_arg);
  if (check9(input)) return action9(action_arg);
  if (check10(input)) return action10(action_arg);
  if (check11(input)) return action11(action_arg);
  if (check12(input)) return action12(action_arg);
  if (check13(input)) return action13(action_arg);
  if (check14(input)) return action14(action_arg);
  if (check15(input)) return action15(action_arg);
  if (check16(input)) return action16(action_arg);
  if (check17(input)) return action17(action_arg);
  if (check18(input)) return action18(action_arg);
  if (check19(input)) return action19(action_arg);
  if (check20(input)) return action20(action_arg);
  if (check21(input)) return action21(action_arg);
  if (check22(input)) return action22(action_arg);
  if (check23(input)) return action23(action_arg);
  if (check24(input)) return action24(action_arg);
  if (check25(input)) return action25(action_arg);
  if (check26(input)) return action26(action_arg);
  if (check27(input)) return action27(action_arg);
  if (check28(input)) return action28(action_arg);
  if (check29(input)) return action29(action_arg);
  if (check30(input)) return action30(action_arg);
  if (check31(input)) return action31(action_arg);
  if (check32(input)) return action32(action_arg);
  if (check33(input)) return action33(action_arg);
  if (check34(input)) return action34(action_arg);
  if (check35(input)) return action35(action_arg);
  if (check36(input)) return action36(action_arg);
  if (check37(input)) return action37(action_arg);
  if (check38(input)) return action38(action_arg);
  if (check39(input)) return action39(action_arg);
  if (check40(input)) return action40(action_arg);
  if (check41(input)) return action41(action_arg);
  if (check42(input)) return action42(action_arg);
  if (check43(input)) return action43(action_arg);
  if (check44(input)) return action44(action_arg);
  if (check45(input)) return action45(action_arg);
  if (check46(input)) return action46(action_arg);
  if (check47(input)) return action47(action_arg);
  if (check48(input)) return action48(action_arg);
  if (check49(input)) return action49(action_arg);
  if (check50(input)) return action50(action_arg);
  if (check51(input)) return action51(action_arg);
  if (check52(input)) return action52(action_arg);
  if (check53(input)) return action53(action_arg);
  if (check54(input)) return action54(action_arg);
  if (check55(input)) return action55(action_arg);
  if (check56(input)) return action56(action_arg);
  if (check57(input)) return action57(action_arg);
  if (check58(input)) return action58(action_arg);
  if (check59(input)) return action59(action_arg);
  if (check60(input)) return action60(action_arg);
  if (check61(input)) return action61(action_arg);
  if (check62(input)) return action62(action_arg);
  return action_fail(action_arg);
}

}

#endif
