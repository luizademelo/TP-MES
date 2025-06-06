// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_DECODE_HUFF_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_DECODE_HUFF_H
#include <grpc/support/port_platform.h>

#include <cstddef>
#include <cstdint>
namespace grpc_core {
class HuffDecoderCommon {
 protected:
  static inline uint64_t GetOp2(size_t i) { return table2_0_ops_[i]; }
  static inline uint64_t GetEmit2(size_t, size_t emit) {
    return table2_0_emit_[emit];
  }
  static inline uint64_t GetOp3(size_t i) { return table3_0_ops_[i]; }
  static inline uint64_t GetEmit3(size_t, size_t emit) {
    return table3_0_emit_[emit];
  }
  static inline uint64_t GetOp4(size_t i) {
    return table4_ops_[i >> 6][i & 0x3f];
  }
  static inline uint64_t GetEmit4(size_t i, size_t emit) {
    return table4_emit_[i >> 6][emit];
  }
  static inline uint64_t GetOp5(size_t i) {
    return table5_ops_[i >> 7][i & 0x7f];
  }
  static inline uint64_t GetEmit5(size_t i, size_t emit) {
    return table5_emit_[i >> 7][emit];
  }
  static inline uint64_t GetOp6(size_t i) {
    return table6_ops_[i >> 5][i & 0x1f];
  }
  static inline uint64_t GetEmit6(size_t i, size_t emit) {
    return table6_emit_[i >> 5][emit];
  }
  static inline uint64_t GetOp7(size_t i) {
    return table7_ops_[i >> 6][i & 0x3f];
  }
  static inline uint64_t GetEmit7(size_t i, size_t emit) {
    return table7_emit_[i >> 6][emit];
  }
  static inline uint64_t GetOp8(size_t i) {
    return table8_inner_[i >> 6][table8_outer_[i >> 6][i & 0x3f]];
  }
  static inline uint64_t GetEmit8(size_t i, size_t emit) {
    return table8_emit_[i >> 6][emit];
  }
  static inline uint64_t GetOp9(size_t i) {
    return table9_ops_[i >> 5][i & 0x1f];
  }
  static inline uint64_t GetEmit9(size_t i, size_t emit) {
    return table9_emit_[i >> 5][emit];
  }
  static inline uint64_t GetOp10(size_t i) {
    return table10_inner_[i >> 6][table10_outer_[i >> 6][i & 0x3f]];
  }
  static inline uint64_t GetEmit10(size_t i, size_t emit) {
    return table10_emit_[i >> 6][emit];
  }
  static inline uint64_t GetOp11(size_t i) {
    return table11_inner_[i >> 6][table11_outer_[i >> 6][i & 0x3f]];
  }
  static inline uint64_t GetEmit11(size_t i, size_t emit) {
    return table11_emit_[i >> 6][emit];
  }
  static inline uint64_t GetOp1(size_t i) {
    return table1_inner_[i >> 6][table1_outer_[i >> 6][i & 0x3f]];
  }
  static inline uint64_t GetEmit1(size_t i, size_t emit) {
    return table1_emit_[i >> 6][emit];
  }
  static inline uint64_t GetOp13(size_t i) {
    return table13_0_inner_[(i < 3 ? (i) : (((i - 3) / 12) + 3))];
  }
  static inline uint64_t GetEmit13(size_t, size_t emit) {
    return (emit < 1 ? (((void)emit, 92)) : ((emit - 1) ? 208 : 195));
  }
  static inline uint64_t GetOp14(size_t i) { return table14_0_ops_[i]; }
  static inline uint64_t GetEmit14(size_t, size_t emit) {
    return table14_0_emit_[emit];
  }
  static inline uint64_t GetOp15(size_t i) { return table15_0_ops_[i]; }
  static inline uint64_t GetEmit15(size_t, size_t emit) {
    return table15_0_emit_[emit];
  }
  static inline uint64_t GetOp12(size_t i) {
    return table12_0_inner_[table12_0_outer_[i]];
  }
  static inline uint64_t GetEmit12(size_t, size_t emit) {
    return table12_0_emit_[emit];
  }
  static inline uint64_t GetOp16(size_t i) { return i ? 3 : 1; }
  static inline uint64_t GetEmit16(size_t, size_t emit) {
    return emit ? 135 : 1;
  }
  static inline uint64_t GetOp17(size_t i) { return i ? 3 : 1; }
  static inline uint64_t GetEmit17(size_t, size_t emit) { return emit + 137; }
  static inline uint64_t GetOp18(size_t i) { return i ? 3 : 1; }
  static inline uint64_t GetEmit18(size_t, size_t emit) { return emit + 139; }
  static inline uint64_t GetOp19(size_t i) { return i ? 3 : 1; }
  static inline uint64_t GetEmit19(size_t, size_t emit) {
    return emit ? 143 : 141;
  }
  static inline uint64_t GetOp20(size_t i) { return i ? 3 : 1; }
  static inline uint64_t GetEmit20(size_t, size_t emit) {
    return emit ? 149 : 147;
  }
  static inline uint64_t GetOp21(size_t i) { return i ? 3 : 1; }
  static inline uint64_t GetEmit21(size_t, size_t emit) { return emit + 150; }
  static inline uint64_t GetOp22(size_t i) { return i ? 3 : 1; }
  static inline uint64_t GetEmit22(size_t, size_t emit) {
    return emit ? 155 : 152;
  }
  static inline uint64_t GetOp23(size_t i) { return i ? 3 : 1; }
  static inline uint64_t GetEmit23(size_t, size_t emit) { return emit + 157; }
  static inline uint64_t GetOp24(size_t i) { return i ? 3 : 1; }
  static inline uint64_t GetEmit24(size_t, size_t emit) { return emit + 165; }
  static inline uint64_t GetOp25(size_t i) { return i ? 3 : 1; }
  static inline uint64_t GetEmit25(size_t, size_t emit) {
    return emit ? 174 : 168;
  }
  static inline uint64_t GetOp26(size_t i) { return i ? 3 : 1; }
  static inline uint64_t GetEmit26(size_t, size_t emit) {
    return emit ? 180 : 175;
  }
  static inline uint64_t GetOp27(size_t i) { return i ? 3 : 1; }
  static inline uint64_t GetEmit27(size_t, size_t emit) { return emit + 182; }
  static inline uint64_t GetOp28(size_t i) { return i ? 3 : 1; }
  static inline uint64_t GetEmit28(size_t, size_t emit) {
    return emit ? 191 : 188;
  }
  static inline uint64_t GetOp29(size_t i) { return i ? 3 : 1; }
  static inline uint64_t GetEmit29(size_t, size_t emit) {
    return emit ? 231 : 197;
  }
  static inline uint64_t GetOp30(size_t i) {
    return (i < 2 ? (i ? 6 : 2) : ((i - 2) ? 14 : 10));
  }
  static inline uint64_t GetEmit30(size_t, size_t emit) {
    return (emit < 2 ? (emit + 144) : ((emit - 2) ? 159 : 148));
  }
  static inline uint64_t GetOp31(size_t i) {
    return (i < 2 ? (i ? 6 : 2) : ((i - 2) ? 14 : 10));
  }
  static inline uint64_t GetEmit31(size_t, size_t emit) {
    return (emit < 2 ? (emit ? 206 : 171) : ((emit - 2) ? 225 : 215));
  }
  static inline uint64_t GetOp33(size_t i) { return table33_0_inner_[i]; }
  static inline uint64_t GetEmit33(size_t, size_t emit) {
    return table33_0_emit_[emit];
  }
  static inline uint64_t GetOp32(size_t i) { return table32_0_ops_[i]; }
  static inline uint64_t GetEmit32(size_t, size_t emit) {
    return table32_0_emit_[emit];
  }
  static inline uint64_t GetOp35(size_t i) { return i; }
  static inline uint64_t GetEmit35(size_t, size_t emit) {
    return ((void)emit, 239);
  }
  static inline uint64_t GetOp34(size_t i) {
    return ((i < 1 ? (((void)i, 0)) : ((i - 1))) < 1
                ? (((void)(i < 1 ? (((void)i, 0)) : ((i - 1))), 1))
                : (((i < 1 ? (((void)i, 0)) : ((i - 1))) - 1) ? 10 : 6));
  }
  static inline uint64_t GetEmit34(size_t, size_t emit) {
    return (emit < 1 ? (((void)emit, 239)) : ((emit - 1) ? 142 : 9));
  }
  static inline uint64_t GetOp37(size_t i) {
    return ((i < 2 ? (i) : (((void)(i - 2), 2))) < 1
                ? (((void)(i < 2 ? (i) : (((void)(i - 2), 2))), 0))
                : (((i < 2 ? (i) : (((void)(i - 2), 2))) - 1) ? 1 : 2));
  }
  static inline uint64_t GetEmit37(size_t, size_t emit) { return emit + 236; }
  static inline uint64_t GetOp36(size_t i) {
    return table36_0_inner_[(i < 3 ? ((i / 2) + 0) : ((i - 3) + 1))];
  }
  static inline uint64_t GetEmit36(size_t, size_t emit) {
    return table36_0_emit_[emit];
  }
  static inline uint64_t GetOp39(size_t i) { return table39_0_ops_[i]; }
  static inline uint64_t GetEmit39(size_t, size_t emit) {
    return table39_0_emit_[emit];
  }
  static inline uint64_t GetOp40(size_t i) { return table40_0_ops_[i]; }
  static inline uint64_t GetEmit40(size_t, size_t emit) {
    return table40_0_emit_[emit];
  }
  static inline uint64_t GetOp41(size_t i) { return table41_0_ops_[i]; }
  static inline uint64_t GetEmit41(size_t, size_t emit) {
    return table40_0_emit_[emit];
  }
  static inline uint64_t GetOp38(size_t i) {
    return table38_ops_[i >> 5][i & 0x1f];
  }
  static inline uint64_t GetEmit38(size_t i, size_t emit) {
    return table38_emit_[i >> 5][emit];
  }

 private:
  static const uint8_t table2_0_emit_[10];
  static const uint8_t table2_0_ops_[32];
  static const uint8_t table3_0_emit_[36];
  static const uint8_t table3_0_ops_[64];
  static const uint8_t table4_0_emit_[22];
  static const uint8_t table4_0_ops_[64];
  static const uint8_t table4_1_emit_[46];
  static const uint8_t table4_1_ops_[64];
  static const uint8_t* const table4_emit_[2];
  static const uint8_t* const table4_ops_[2];
  static const uint8_t table5_0_ops_[128];
  static const uint8_t table5_1_emit_[52];
  static const uint8_t table5_1_ops_[128];
  static const uint8_t* const table5_emit_[2];
  static const uint8_t* const table5_ops_[2];
  static const uint8_t table6_0_emit_[2];
  static const uint8_t table6_0_ops_[32];
  static const uint8_t table6_1_emit_[2];
  static const uint8_t table6_2_emit_[2];
  static const uint8_t table6_3_emit_[2];
  static const uint8_t table6_4_emit_[2];
  static const uint8_t table6_5_emit_[4];
  static const uint8_t table6_5_ops_[32];
  static const uint8_t table6_6_emit_[4];
  static const uint8_t table6_7_emit_[4];
  static const uint8_t table6_8_emit_[4];
  static const uint8_t table6_9_emit_[4];
  static const uint8_t table6_10_emit_[4];
  static const uint8_t table6_11_emit_[6];
  static const uint8_t table6_11_ops_[32];
  static const uint8_t table6_12_emit_[8];
  static const uint8_t table6_12_ops_[32];
  static const uint8_t table6_13_emit_[8];
  static const uint8_t table6_14_emit_[8];
  static const uint8_t table6_15_emit_[10];
  static const uint8_t table6_15_ops_[32];
  static const uint8_t* const table6_emit_[16];
  static const uint8_t* const table6_ops_[16];
  static const uint8_t table7_0_emit_[36];
  static const uint8_t table7_0_ops_[64];
  static const uint8_t table7_1_emit_[36];
  static const uint8_t table7_1_ops_[64];
  static const uint8_t table7_2_emit_[36];
  static const uint8_t table7_2_ops_[64];
  static const uint8_t table7_3_emit_[36];
  static const uint8_t table7_3_ops_[64];
  static const uint8_t table7_4_emit_[38];
  static const uint8_t table7_4_ops_[64];
  static const uint8_t table7_5_ops_[64];
  static const uint8_t table7_11_ops_[64];
  static const uint8_t table7_12_ops_[64];
  static const uint8_t table7_15_emit_[15];
  static const uint8_t table7_15_ops_[64];
  static const uint8_t* const table7_emit_[16];
  static const uint8_t* const table7_ops_[16];
  static const uint8_t table8_0_emit_[71];
  static const uint16_t table8_0_inner_[38];
  static const uint8_t table8_0_outer_[64];
  static const uint8_t table8_1_emit_[71];
  static const uint16_t table8_1_inner_[38];
  static const uint8_t table8_2_emit_[71];
  static const uint16_t table8_2_inner_[38];
  static const uint8_t table8_3_emit_[71];
  static const uint16_t table8_3_inner_[38];
  static const uint8_t table8_4_emit_[71];
  static const uint16_t table8_4_inner_[38];
  static const uint8_t table8_5_emit_[71];
  static const uint16_t table8_5_inner_[38];
  static const uint8_t table8_6_emit_[71];
  static const uint16_t table8_6_inner_[38];
  static const uint8_t table8_7_emit_[71];
  static const uint16_t table8_7_inner_[38];
  static const uint8_t table8_8_emit_[71];
  static const uint16_t table8_8_inner_[38];
  static const uint8_t table8_9_emit_[71];
  static const uint16_t table8_9_inner_[38];
  static const uint8_t table8_10_emit_[40];
  static const uint16_t table8_10_inner_[23];
  static const uint8_t table8_10_outer_[64];
  static const uint8_t table8_11_emit_[40];
  static const uint8_t table8_12_emit_[40];
  static const uint8_t table8_13_emit_[40];
  static const uint8_t table8_14_emit_[40];
  static const uint8_t table8_15_emit_[40];
  static const uint8_t table8_16_emit_[40];
  static const uint8_t table8_17_emit_[40];
  static const uint8_t table8_18_emit_[40];
  static const uint8_t table8_19_emit_[40];
  static const uint8_t table8_20_emit_[40];
  static const uint8_t table8_21_emit_[40];
  static const uint8_t table8_22_emit_[40];
  static const uint8_t table8_23_emit_[4];
  static const uint16_t table8_23_inner_[5];
  static const uint8_t table8_23_outer_[64];
  static const uint8_t table8_24_emit_[4];
  static const uint8_t table8_25_emit_[4];
  static const uint8_t table8_26_emit_[4];
  static const uint8_t table8_27_emit_[4];
  static const uint8_t table8_28_emit_[4];
  static const uint8_t table8_29_emit_[4];
  static const uint8_t table8_30_emit_[4];
  static const uint8_t table8_31_emit_[14];
  static const uint16_t table8_31_inner_[16];
  static const uint8_t table8_31_outer_[64];
  static const uint8_t* const table8_emit_[32];
  static const uint16_t* const table8_inner_[32];
  static const uint8_t* const table8_outer_[32];
  static const uint8_t table9_0_emit_[15];
  static const uint8_t table9_0_ops_[32];
  static const uint8_t table9_1_emit_[28];
  static const uint8_t table9_1_ops_[32];
  static const uint8_t table9_2_emit_[36];
  static const uint8_t table9_2_ops_[32];
  static const uint8_t table9_3_emit_[56];
  static const uint8_t table9_3_ops_[32];
  static const uint8_t table9_4_emit_[15];
  static const uint8_t table9_4_ops_[32];
  static const uint8_t table9_5_emit_[28];
  static const uint8_t table9_6_emit_[36];
  static const uint8_t table9_7_emit_[56];
  static const uint8_t table9_8_emit_[15];
  static const uint8_t table9_8_ops_[32];
  static const uint8_t table9_9_emit_[28];
  static const uint8_t table9_10_emit_[36];
  static const uint8_t table9_11_emit_[56];
  static const uint8_t table9_12_emit_[15];
  static const uint8_t table9_12_ops_[32];
  static const uint8_t table9_13_emit_[28];
  static const uint8_t table9_14_emit_[36];
  static const uint8_t table9_15_emit_[56];
  static const uint8_t table9_16_emit_[15];
  static const uint8_t table9_16_ops_[32];
  static const uint8_t table9_17_emit_[28];
  static const uint8_t table9_18_emit_[36];
  static const uint8_t table9_19_emit_[56];
  static const uint8_t table9_20_emit_[15];
  static const uint8_t table9_20_ops_[32];
  static const uint8_t table9_21_emit_[28];
  static const uint8_t table9_22_emit_[36];
  static const uint8_t table9_23_emit_[56];
  static const uint8_t table9_24_emit_[15];
  static const uint8_t table9_24_ops_[32];
  static const uint8_t table9_25_emit_[28];
  static const uint8_t table9_26_emit_[36];
  static const uint8_t table9_27_emit_[56];
  static const uint8_t table9_28_emit_[16];
  static const uint8_t table9_28_ops_[32];
  static const uint8_t table9_29_emit_[28];
  static const uint8_t table9_30_emit_[36];
  static const uint8_t table9_31_emit_[56];
  static const uint8_t table9_32_emit_[16];
  static const uint8_t table9_33_emit_[27];
  static const uint8_t table9_33_ops_[32];
  static const uint8_t table9_34_emit_[36];
  static const uint8_t table9_35_emit_[56];
  static const uint8_t table9_36_emit_[16];
  static const uint8_t table9_37_emit_[27];
  static const uint8_t table9_37_ops_[32];
  static const uint8_t table9_38_emit_[36];
  static const uint8_t table9_39_emit_[56];
  static const uint8_t table9_40_emit_[43];
  static const uint8_t table9_40_ops_[32];
  static const uint8_t table9_41_emit_[28];
  static const uint8_t table9_41_ops_[32];
  static const uint8_t table9_42_emit_[43];
  static const uint8_t table9_42_ops_[32];
  static const uint8_t table9_43_emit_[28];
  static const uint8_t table9_44_emit_[43];
  static const uint8_t table9_44_ops_[32];
  static const uint8_t table9_45_emit_[28];
  static const uint8_t table9_46_emit_[43];
  static const uint8_t table9_46_ops_[32];
  static const uint8_t table9_47_emit_[28];
  static const uint8_t table9_48_emit_[43];
  static const uint8_t table9_48_ops_[32];
  static const uint8_t table9_49_emit_[28];
  static const uint8_t table9_50_emit_[43];
  static const uint8_t table9_50_ops_[32];
  static const uint8_t table9_51_emit_[28];
  static const uint8_t table9_52_emit_[43];
  static const uint8_t table9_52_ops_[32];
  static const uint8_t table9_53_emit_[28];
  static const uint8_t table9_54_emit_[43];
  static const uint8_t table9_54_ops_[32];
  static const uint8_t table9_55_emit_[28];
  static const uint8_t table9_56_emit_[43];
  static const uint8_t table9_56_ops_[32];
  static const uint8_t table9_57_emit_[28];
  static const uint8_t table9_58_emit_[43];
  static const uint8_t table9_58_ops_[32];
  static const uint8_t table9_59_emit_[28];
  static const uint8_t table9_60_emit_[43];
  static const uint8_t table9_60_ops_[32];
  static const uint8_t table9_61_emit_[28];
  static const uint8_t table9_62_emit_[44];
  static const uint8_t table9_62_ops_[32];
  static const uint8_t table9_63_emit_[28];
  static const uint8_t table9_64_emit_[44];
  static const uint8_t table9_65_emit_[27];
  static const uint8_t table9_65_ops_[32];
  static const uint8_t table9_66_emit_[44];
  static const uint8_t table9_67_emit_[27];
  static const uint8_t table9_67_ops_[32];
  static const uint8_t table9_68_emit_[44];
  static const uint8_t table9_69_emit_[27];
  static const uint8_t table9_69_ops_[32];
  static const uint8_t table9_70_emit_[44];
  static const uint8_t table9_71_emit_[27];
  static const uint8_t table9_71_ops_[32];
  static const uint8_t table9_72_emit_[44];
  static const uint8_t table9_73_emit_[27];
  static const uint8_t table9_73_ops_[32];
  static const uint8_t table9_74_emit_[44];
  static const uint8_t table9_75_emit_[27];
  static const uint8_t table9_75_ops_[32];
  static const uint8_t table9_76_emit_[44];
  static const uint8_t table9_77_emit_[27];
  static const uint8_t table9_77_ops_[32];
  static const uint8_t table9_78_emit_[44];
  static const uint8_t table9_79_emit_[27];
  static const uint8_t table9_79_ops_[32];
  static const uint8_t table9_80_emit_[44];
  static const uint8_t table9_81_emit_[27];
  static const uint8_t table9_81_ops_[32];
  static const uint8_t table9_82_emit_[44];
  static const uint8_t table9_83_emit_[27];
  static const uint8_t table9_83_ops_[32];
  static const uint8_t table9_84_emit_[44];
  static const uint8_t table9_85_emit_[27];
  static const uint8_t table9_85_ops_[32];
  static const uint8_t table9_86_emit_[44];
  static const uint8_t table9_87_emit_[27];
  static const uint8_t table9_87_ops_[32];
  static const uint8_t table9_88_emit_[44];
  static const uint8_t table9_89_emit_[27];
  static const uint8_t table9_89_ops_[32];
  static const uint8_t table9_90_emit_[44];
  static const uint8_t table9_91_emit_[28];
  static const uint8_t table9_92_emit_[20];
  static const uint8_t table9_92_ops_[32];
  static const uint8_t table9_93_emit_[20];
  static const uint8_t table9_94_emit_[20];
  static const uint8_t table9_95_emit_[20];
  static const uint8_t table9_96_emit_[20];
  static const uint8_t table9_97_emit_[20];
  static const uint8_t table9_98_emit_[20];
  static const uint8_t table9_99_emit_[20];
  static const uint8_t table9_100_emit_[20];
  static const uint8_t table9_101_emit_[20];
  static const uint8_t table9_102_emit_[20];
  static const uint8_t table9_103_emit_[20];
  static const uint8_t table9_104_emit_[20];
  static const uint8_t table9_105_emit_[20];
  static const uint8_t table9_106_emit_[20];
  static const uint8_t table9_107_emit_[20];
  static const uint8_t table9_108_emit_[20];
  static const uint8_t table9_109_emit_[20];
  static const uint8_t table9_110_emit_[20];
  static const uint8_t table9_111_emit_[20];
  static const uint8_t table9_112_emit_[20];
  static const uint8_t table9_113_emit_[20];
  static const uint8_t table9_114_emit_[20];
  static const uint8_t table9_115_emit_[20];
  static const uint8_t table9_116_emit_[20];
  static const uint8_t table9_117_emit_[20];
  static const uint8_t table9_118_emit_[20];
  static const uint8_t table9_119_emit_[20];
  static const uint8_t table9_120_emit_[20];
  static const uint8_t table9_121_emit_[20];
  static const uint8_t table9_122_emit_[20];
  static const uint8_t table9_123_emit_[20];
  static const uint8_t table9_124_emit_[2];
  static const uint8_t table9_124_ops_[32];
  static const uint8_t table9_125_emit_[2];
  static const uint8_t table9_126_emit_[2];
  static const uint8_t table9_127_emit_[10];
  static const uint8_t table9_127_ops_[32];
  static const uint8_t* const table9_emit_[128];
  static const uint8_t* const table9_ops_[128];
  static const uint16_t table10_0_inner_[9];
  static const uint8_t table10_0_outer_[64];
  static const uint16_t table10_1_inner_[15];
  static const uint8_t table10_1_outer_[64];
  static const uint16_t table10_2_inner_[19];
  static const uint8_t table10_2_outer_[64];
  static const uint8_t table10_3_emit_[68];
  static const uint16_t table10_3_inner_[36];
  static const uint8_t table10_3_outer_[64];
  static const uint16_t table10_4_inner_[9];
  static const uint8_t table10_7_emit_[68];
  static const uint16_t table10_8_inner_[9];
  static const uint8_t table10_11_emit_[68];
  static const uint16_t table10_12_inner_[9];
  static const uint8_t table10_15_emit_[68];
  static const uint16_t table10_16_inner_[9];
  static const uint8_t table10_19_emit_[68];
  static const uint16_t table10_20_inner_[9];
  static const uint8_t table10_23_emit_[68];
  static const uint16_t table10_24_inner_[9];
  static const uint8_t table10_27_emit_[68];
  static const uint16_t table10_28_inner_[9];
  static const uint8_t table10_31_emit_[68];
  static const uint16_t table10_33_inner_[15];
  static const uint8_t table10_35_emit_[68];
  static const uint16_t table10_37_inner_[15];
  static const uint8_t table10_39_emit_[68];
  static const uint16_t table10_40_inner_[23];
  static const uint8_t table10_40_outer_[64];
  static const uint8_t table10_41_emit_[92];
  static const uint16_t table10_41_inner_[48];
  static const uint8_t table10_41_outer_[64];
  static const uint16_t table10_42_inner_[23];
  static const uint8_t table10_43_emit_[92];
  static const uint16_t table10_44_inner_[23];
  static const uint8_t table10_45_emit_[92];
  static const uint16_t table10_46_inner_[23];
  static const uint8_t table10_47_emit_[92];
  static const uint16_t table10_48_inner_[23];
  static const uint8_t table10_49_emit_[92];
  static const uint16_t table10_50_inner_[23];
  static const uint8_t table10_51_emit_[92];
  static const uint16_t table10_52_inner_[23];
  static const uint8_t table10_53_emit_[92];
  static const uint16_t table10_54_inner_[23];
  static const uint8_t table10_55_emit_[92];
  static const uint16_t table10_56_inner_[23];
  static const uint8_t table10_57_emit_[92];
  static const uint16_t table10_58_inner_[23];
  static const uint8_t table10_59_emit_[92];
  static const uint16_t table10_60_inner_[23];
  static const uint8_t table10_61_emit_[92];
  static const uint16_t table10_62_inner_[23];
  static const uint8_t table10_63_emit_[92];
  static const uint8_t table10_65_emit_[91];
  static const uint16_t table10_65_inner_[48];
  static const uint8_t table10_67_emit_[91];
  static const uint16_t table10_67_inner_[48];
  static const uint8_t table10_69_emit_[91];
  static const uint16_t table10_69_inner_[48];
  static const uint8_t table10_71_emit_[91];
  static const uint16_t table10_71_inner_[48];
  static const uint8_t table10_73_emit_[91];
  static const uint16_t table10_73_inner_[48];
  static const uint8_t table10_75_emit_[91];
  static const uint16_t table10_75_inner_[48];
  static const uint8_t table10_77_emit_[91];
  static const uint16_t table10_77_inner_[48];
  static const uint8_t table10_79_emit_[91];
  static const uint16_t table10_79_inner_[48];
  static const uint8_t table10_81_emit_[91];
  static const uint16_t table10_81_inner_[48];
  static const uint8_t table10_83_emit_[91];
  static const uint16_t table10_83_inner_[48];
  static const uint8_t table10_85_emit_[91];
  static const uint16_t table10_85_inner_[48];
  static const uint8_t table10_87_emit_[91];
  static const uint16_t table10_87_inner_[48];
  static const uint8_t table10_89_emit_[91];
  static const uint16_t table10_89_inner_[48];
  static const uint8_t table10_91_emit_[91];
  static const uint16_t table10_91_inner_[48];
  static const uint8_t table10_92_emit_[72];
  static const uint16_t table10_92_inner_[38];
  static const uint8_t table10_93_emit_[72];
  static const uint8_t table10_94_emit_[72];
  static const uint8_t table10_95_emit_[72];
  static const uint8_t table10_96_emit_[72];
  static const uint8_t table10_97_emit_[72];
  static const uint8_t table10_98_emit_[72];
  static const uint8_t table10_99_emit_[72];
  static const uint8_t table10_100_emit_[72];
  static const uint8_t table10_101_emit_[72];
  static const uint8_t table10_102_emit_[72];
  static const uint8_t table10_103_emit_[72];
  static const uint8_t table10_104_emit_[72];
  static const uint8_t table10_105_emit_[72];
  static const uint8_t table10_106_emit_[72];
  static const uint8_t table10_107_emit_[72];
  static const uint8_t table10_108_emit_[72];
  static const uint8_t table10_109_emit_[72];
  static const uint8_t table10_110_emit_[72];
  static const uint8_t table10_111_emit_[72];
  static const uint8_t table10_112_emit_[72];
  static const uint8_t table10_113_emit_[72];
  static const uint8_t table10_114_emit_[72];
  static const uint8_t table10_115_emit_[72];
  static const uint8_t table10_116_emit_[72];
  static const uint8_t table10_117_emit_[72];
  static const uint8_t table10_118_emit_[72];
  static const uint8_t table10_119_emit_[72];
  static const uint8_t table10_120_emit_[72];
  static const uint8_t table10_121_emit_[72];
  static const uint8_t table10_122_emit_[72];
  static const uint8_t table10_123_emit_[72];
  static const uint8_t table10_124_emit_[40];
  static const uint8_t table10_125_emit_[40];
  static const uint8_t table10_126_emit_[40];
  static const uint8_t table10_127_emit_[16];
  static const uint16_t table10_127_inner_[18];
  static const uint8_t table10_127_outer_[64];
  static const uint8_t* const table10_emit_[128];
  static const uint16_t* const table10_inner_[128];
  static const uint8_t* const table10_outer_[128];
  static const uint8_t table11_0_emit_[7];
  static const uint16_t table11_0_inner_[5];
  static const uint8_t table11_1_emit_[8];
  static const uint16_t table11_1_inner_[5];
  static const uint8_t table11_2_emit_[12];
  static const uint16_t table11_2_inner_[7];
  static const uint8_t table11_2_outer_[64];
  static const uint8_t table11_3_emit_[16];
  static const uint8_t table11_4_emit_[16];
  static const uint8_t table11_5_emit_[20];
  static const uint16_t table11_5_inner_[11];
  static const uint8_t table11_5_outer_[64];
  static const uint8_t table11_6_emit_[32];
  static const uint16_t table11_6_inner_[17];
  static const uint8_t table11_6_outer_[64];
  static const uint8_t table11_7_emit_[36];
  static const uint16_t table11_7_inner_[20];
  static const uint8_t table11_7_outer_[64];
  static const uint8_t table11_8_emit_[7];
  static const uint16_t table11_8_inner_[5];
  static const uint8_t table11_9_emit_[8];
  static const uint8_t table11_10_emit_[12];
  static const uint8_t table11_11_emit_[16];
  static const uint8_t table11_12_emit_[16];
  static const uint8_t table11_13_emit_[20];
  static const uint8_t table11_14_emit_[32];
  static const uint8_t table11_15_emit_[36];
  static const uint8_t table11_16_emit_[7];
  static const uint16_t table11_16_inner_[5];
  static const uint8_t table11_17_emit_[8];
  static const uint8_t table11_18_emit_[12];
  static const uint8_t table11_19_emit_[16];
  static const uint8_t table11_20_emit_[16];
  static const uint8_t table11_21_emit_[20];
  static const uint8_t table11_22_emit_[32];
  static const uint8_t table11_23_emit_[36];
  static const uint8_t table11_24_emit_[8];
  static const uint8_t table11_25_emit_[8];
  static const uint8_t table11_26_emit_[12];
  static const uint8_t table11_27_emit_[16];
  static const uint8_t table11_28_emit_[16];
  static const uint8_t table11_29_emit_[20];
  static const uint8_t table11_30_emit_[32];
  static const uint8_t table11_31_emit_[36];
  static const uint8_t table11_32_emit_[8];
  static const uint8_t table11_33_emit_[7];
  static const uint8_t table11_34_emit_[12];
  static const uint8_t table11_35_emit_[16];
  static const uint8_t table11_36_emit_[16];
  static const uint8_t table11_37_emit_[20];
  static const uint8_t table11_38_emit_[32];
  static const uint8_t table11_39_emit_[36];
  static const uint8_t table11_40_emit_[8];
  static const uint8_t table11_41_emit_[7];
  static const uint8_t table11_42_emit_[12];
  static const uint8_t table11_43_emit_[16];
  static const uint8_t table11_44_emit_[16];
  static const uint8_t table11_45_emit_[20];
  static const uint8_t table11_46_emit_[32];
  static const uint8_t table11_47_emit_[36];
  static const uint8_t table11_48_emit_[8];
  static const uint8_t table11_49_emit_[7];
  static const uint8_t table11_50_emit_[12];
  static const uint8_t table11_51_emit_[16];
  static const uint8_t table11_52_emit_[16];
  static const uint8_t table11_53_emit_[20];
  static const uint8_t table11_54_emit_[32];
  static const uint8_t table11_55_emit_[36];
  static const uint8_t table11_56_emit_[8];
  static const uint8_t table11_57_emit_[8];
  static const uint8_t table11_58_emit_[12];
  static const uint8_t table11_59_emit_[16];
  static const uint8_t table11_60_emit_[16];
  static const uint8_t table11_61_emit_[20];
  static const uint8_t table11_62_emit_[32];
  static const uint8_t table11_63_emit_[36];
  static const uint8_t table11_64_emit_[8];
  static const uint8_t table11_65_emit_[8];
  static const uint8_t table11_66_emit_[11];
  static const uint16_t table11_66_inner_[7];
  static const uint8_t table11_67_emit_[16];
  static const uint8_t table11_68_emit_[16];
  static const uint8_t table11_69_emit_[20];
  static const uint8_t table11_70_emit_[32];
  static const uint8_t table11_71_emit_[36];
  static const uint8_t table11_72_emit_[8];
  static const uint8_t table11_73_emit_[8];
  static const uint8_t table11_74_emit_[11];
  static const uint16_t table11_74_inner_[7];
  static const uint8_t table11_75_emit_[16];
  static const uint8_t table11_76_emit_[16];
  static const uint8_t table11_77_emit_[20];
  static const uint8_t table11_78_emit_[32];
  static const uint8_t table11_79_emit_[36];
  static const uint8_t table11_80_emit_[16];
  static const uint8_t table11_81_emit_[27];
  static const uint16_t table11_81_inner_[15];
  static const uint8_t table11_82_emit_[36];
  static const uint8_t table11_83_emit_[68];
  static const uint8_t table11_84_emit_[16];
  static const uint8_t table11_85_emit_[27];
  static const uint16_t table11_85_inner_[15];
  static const uint8_t table11_86_emit_[36];
  static const uint8_t table11_87_emit_[68];
  static const uint8_t table11_88_emit_[16];
  static const uint8_t table11_89_emit_[27];
  static const uint16_t table11_89_inner_[15];
  static const uint8_t table11_90_emit_[36];
  static const uint8_t table11_91_emit_[68];
  static const uint8_t table11_92_emit_[16];
  static const uint8_t table11_93_emit_[27];
  static const uint16_t table11_93_inner_[15];
  static const uint8_t table11_94_emit_[36];
  static const uint8_t table11_95_emit_[68];
  static const uint8_t table11_96_emit_[16];
  static const uint8_t table11_97_emit_[27];
  static const uint16_t table11_97_inner_[15];
  static const uint8_t table11_98_emit_[36];
  static const uint8_t table11_99_emit_[68];
  static const uint8_t table11_100_emit_[16];
  static const uint8_t table11_101_emit_[27];
  static const uint16_t table11_101_inner_[15];
  static const uint8_t table11_102_emit_[36];
  static const uint8_t table11_103_emit_[68];
  static const uint8_t table11_104_emit_[16];
  static const uint8_t table11_105_emit_[27];
  static const uint16_t table11_105_inner_[15];
  static const uint8_t table11_106_emit_[36];
  static const uint8_t table11_107_emit_[68];
  static const uint8_t table11_108_emit_[16];
  static const uint8_t table11_109_emit_[27];
  static const uint16_t table11_109_inner_[15];
  static const uint8_t table11_110_emit_[36];
  static const uint8_t table11_111_emit_[68];
  static const uint8_t table11_112_emit_[16];
  static const uint8_t table11_113_emit_[27];
  static const uint16_t table11_113_inner_[15];
  static const uint8_t table11_114_emit_[36];
  static const uint8_t table11_115_emit_[68];
  static const uint8_t table11_116_emit_[16];
  static const uint8_t table11_117_emit_[27];
  static const uint16_t table11_117_inner_[15];
  static const uint8_t table11_118_emit_[36];
  static const uint8_t table11_119_emit_[68];
  static const uint8_t table11_120_emit_[16];
  static const uint8_t table11_121_emit_[27];
  static const uint16_t table11_121_inner_[15];
  static const uint8_t table11_122_emit_[36];
  static const uint8_t table11_123_emit_[68];
  static const uint8_t table11_124_emit_[16];
  static const uint8_t table11_125_emit_[28];
  static const uint8_t table11_126_emit_[36];
  static const uint8_t table11_127_emit_[68];
  static const uint8_t table11_128_emit_[16];
  static const uint8_t table11_129_emit_[28];
  static const uint8_t table11_130_emit_[35];
  static const uint16_t table11_130_inner_[19];
  static const uint8_t table11_131_emit_[68];
  static const uint8_t table11_132_emit_[16];
  static const uint8_t table11_133_emit_[28];
  static const uint8_t table11_134_emit_[35];
  static const uint16_t table11_134_inner_[19];
  static const uint8_t table11_135_emit_[68];
  static const uint8_t table11_136_emit_[16];
  static const uint8_t table11_137_emit_[28];
  static const uint8_t table11_138_emit_[35];
  static const uint16_t table11_138_inner_[19];
  static const uint8_t table11_139_emit_[68];
  static const uint8_t table11_140_emit_[16];
  static const uint8_t table11_141_emit_[28];
  static const uint8_t table11_142_emit_[35];
  static const uint16_t table11_142_inner_[19];
  static const uint8_t table11_143_emit_[68];
  static const uint8_t table11_144_emit_[16];
  static const uint8_t table11_145_emit_[28];
  static const uint8_t table11_146_emit_[35];
  static const uint16_t table11_146_inner_[19];
  static const uint8_t table11_147_emit_[68];
  static const uint8_t table11_148_emit_[16];
  static const uint8_t table11_149_emit_[28];
  static const uint8_t table11_150_emit_[35];
  static const uint16_t table11_150_inner_[19];
  static const uint8_t table11_151_emit_[68];
  static const uint8_t table11_152_emit_[16];
  static const uint8_t table11_153_emit_[28];
  static const uint8_t table11_154_emit_[35];
  static const uint16_t table11_154_inner_[19];
  static const uint8_t table11_155_emit_[68];
  static const uint8_t table11_156_emit_[16];
  static const uint8_t table11_157_emit_[28];
  static const uint8_t table11_158_emit_[35];
  static const uint16_t table11_158_inner_[19];
  static const uint8_t table11_159_emit_[68];
  static const uint8_t table11_160_emit_[16];
  static const uint8_t table11_161_emit_[28];
  static const uint8_t table11_162_emit_[35];
  static const uint16_t table11_162_inner_[19];
  static const uint8_t table11_163_emit_[68];
  static const uint8_t table11_164_emit_[16];
  static const uint8_t table11_165_emit_[28];
  static const uint8_t table11_166_emit_[35];
  static const uint16_t table11_166_inner_[19];
  static const uint8_t table11_167_emit_[68];
  static const uint8_t table11_168_emit_[16];
  static const uint8_t table11_169_emit_[28];
  static const uint8_t table11_170_emit_[35];
  static const uint16_t table11_170_inner_[19];
  static const uint8_t table11_171_emit_[68];
  static const uint8_t table11_172_emit_[16];
  static const uint8_t table11_173_emit_[28];
  static const uint8_t table11_174_emit_[35];
  static const uint16_t table11_174_inner_[19];
  static const uint8_t table11_175_emit_[68];
  static const uint8_t table11_176_emit_[16];
  static const uint8_t table11_177_emit_[28];
  static const uint8_t table11_178_emit_[35];
  static const uint16_t table11_178_inner_[19];
  static const uint8_t table11_179_emit_[68];
  static const uint8_t table11_180_emit_[16];
  static const uint8_t table11_181_emit_[28];
  static const uint8_t table11_182_emit_[35];
  static const uint16_t table11_182_inner_[19];
  static const uint8_t table11_183_emit_[68];
  static const uint8_t table11_184_emit_[44];
  static const uint8_t table11_185_emit_[91];
  static const uint16_t table11_185_inner_[48];
  static const uint8_t table11_186_emit_[44];
  static const uint8_t table11_187_emit_[91];
  static const uint16_t table11_187_inner_[48];
  static const uint8_t table11_188_emit_[44];
  static const uint8_t table11_189_emit_[91];
  static const uint16_t table11_189_inner_[48];
  static const uint8_t table11_190_emit_[44];
  static const uint8_t table11_191_emit_[91];
  static const uint16_t table11_191_inner_[48];
  static const uint8_t table11_192_emit_[44];
  static const uint8_t table11_193_emit_[91];
  static const uint16_t table11_193_inner_[48];
  static const uint8_t table11_194_emit_[44];
  static const uint8_t table11_195_emit_[91];
  static const uint16_t table11_195_inner_[48];
  static const uint8_t table11_196_emit_[44];
  static const uint8_t table11_197_emit_[91];
  static const uint16_t table11_197_inner_[48];
  static const uint8_t table11_198_emit_[44];
  static const uint8_t table11_199_emit_[91];
  static const uint16_t table11_199_inner_[48];
  static const uint8_t table11_200_emit_[44];
  static const uint8_t table11_201_emit_[91];
  static const uint16_t table11_201_inner_[48];
  static const uint8_t table11_202_emit_[44];
  static const uint8_t table11_203_emit_[91];
  static const uint16_t table11_203_inner_[48];
  static const uint8_t table11_204_emit_[44];
  static const uint8_t table11_205_emit_[91];
  static const uint16_t table11_205_inner_[48];
  static const uint8_t table11_206_emit_[44];
  static const uint8_t table11_207_emit_[91];
  static const uint16_t table11_207_inner_[48];
  static const uint8_t table11_208_emit_[44];
  static const uint8_t table11_209_emit_[91];
  static const uint16_t table11_209_inner_[48];
  static const uint8_t table11_210_emit_[44];
  static const uint8_t table11_211_emit_[91];
  static const uint16_t table11_211_inner_[48];
  static const uint8_t table11_212_emit_[44];
  static const uint8_t table11_213_emit_[91];
  static const uint16_t table11_213_inner_[48];
  static const uint8_t table11_214_emit_[44];
  static const uint8_t table11_215_emit_[91];
  static const uint16_t table11_215_inner_[48];
  static const uint8_t table11_216_emit_[44];
  static const uint8_t table11_217_emit_[91];
  static const uint16_t table11_217_inner_[48];
  static const uint8_t table11_218_emit_[44];
  static const uint8_t table11_219_emit_[91];
  static const uint16_t table11_219_inner_[48];
  static const uint8_t table11_220_emit_[44];
  static const uint8_t table11_221_emit_[91];
  static const uint16_t table11_221_inner_[48];
  static const uint8_t table11_222_emit_[44];
  static const uint8_t table11_223_emit_[91];
  static const uint16_t table11_223_inner_[48];
  static const uint8_t table11_224_emit_[44];
  static const uint8_t table11_225_emit_[91];
  static const uint16_t table11_225_inner_[48];
  static const uint8_t table11_226_emit_[44];
  static const uint8_t table11_227_emit_[91];
  static const uint16_t table11_227_inner_[48];
  static const uint8_t table11_228_emit_[44];
  static const uint8_t table11_229_emit_[91];
  static const uint16_t table11_229_inner_[48];
  static const uint8_t table11_230_emit_[44];
  static const uint8_t table11_231_emit_[91];
  static const uint16_t table11_231_inner_[48];
  static const uint8_t table11_232_emit_[44];
  static const uint8_t table11_233_emit_[91];
  static const uint16_t table11_233_inner_[48];
  static const uint8_t table11_234_emit_[44];
  static const uint8_t table11_235_emit_[91];
  static const uint16_t table11_235_inner_[48];
  static const uint8_t table11_236_emit_[44];
  static const uint8_t table11_237_emit_[91];
  static const uint16_t table11_237_inner_[48];
  static const uint8_t table11_238_emit_[44];
  static const uint8_t table11_239_emit_[91];
  static const uint16_t table11_239_inner_[48];
  static const uint8_t table11_240_emit_[44];
  static const uint8_t table11_241_emit_[91];
  static const uint16_t table11_241_inner_[48];
  static const uint8_t table11_242_emit_[44];
  static const uint8_t table11_243_emit_[91];
  static const uint16_t table11_243_inner_[48];
  static const uint8_t table11_244_emit_[44];
  static const uint8_t table11_245_emit_[91];
  static const uint16_t table11_245_inner_[48];
  static const uint8_t table11_246_emit_[44];
  static const uint8_t table11_247_emit_[92];
  static const uint8_t table11_248_emit_[72];
  static const uint8_t table11_249_emit_[72];
  static const uint8_t table11_250_emit_[72];
  static const uint8_t table11_251_emit_[72];
  static const uint8_t table11_252_emit_[72];
  static const uint8_t table11_253_emit_[72];
  static const uint8_t table11_254_emit_[4];
  static const uint8_t table11_255_emit_[14];
  static const uint8_t table11_255_outer_[64];
  static const uint8_t* const table11_emit_[256];
  static const uint16_t* const table11_inner_[256];
  static const uint8_t* const table11_outer_[256];
  static const uint8_t table1_0_emit_[55];
  static const uint16_t table1_0_inner_[22];
  static const uint8_t table1_0_outer_[64];
  static const uint8_t table1_1_emit_[58];
  static const uint16_t table1_1_inner_[22];
  static const uint8_t table1_2_emit_[58];
  static const uint8_t table1_3_emit_[58];
  static const uint8_t table1_4_emit_[58];
  static const uint8_t table1_5_emit_[8];
  static const uint16_t table1_5_inner_[4];
  static const uint8_t table1_5_outer_[64];
  static const uint8_t table1_6_emit_[8];
  static const uint8_t table1_7_emit_[8];
  static const uint8_t table1_8_emit_[8];
  static const uint8_t table1_9_emit_[8];
  static const uint8_t table1_10_emit_[8];
  static const uint8_t table1_11_emit_[12];
  static const uint16_t table1_11_inner_[6];
  static const uint8_t table1_11_outer_[64];
  static const uint8_t table1_12_emit_[16];
  static const uint16_t table1_12_inner_[8];
  static const uint8_t table1_12_outer_[64];
  static const uint8_t table1_13_emit_[16];
  static const uint8_t table1_14_emit_[16];
  static const uint8_t table1_15_emit_[30];
  static const uint16_t table1_15_inner_[16];
  static const uint8_t table1_15_outer_[64];
  static const uint8_t table1_16_emit_[57];
  static const uint16_t table1_16_inner_[22];
  static const uint8_t table1_17_emit_[58];
  static const uint16_t table1_17_inner_[22];
  static const uint8_t table1_18_emit_[58];
  static const uint8_t table1_19_emit_[58];
  static const uint8_t table1_20_emit_[58];
  static const uint8_t table1_21_emit_[8];
  static const uint8_t table1_22_emit_[8];
  static const uint8_t table1_23_emit_[8];
  static const uint8_t table1_24_emit_[8];
  static const uint8_t table1_25_emit_[8];
  static const uint8_t table1_26_emit_[8];
  static const uint8_t table1_27_emit_[12];
  static const uint8_t table1_28_emit_[16];
  static const uint8_t table1_29_emit_[16];
  static const uint8_t table1_30_emit_[16];
  static const uint8_t table1_31_emit_[30];
  static const uint8_t table1_32_emit_[58];
  static const uint16_t table1_32_inner_[22];
  static const uint8_t table1_33_emit_[55];
  static const uint16_t table1_33_inner_[22];
  static const uint8_t table1_34_emit_[58];
  static const uint8_t table1_35_emit_[58];
  static const uint8_t table1_36_emit_[58];
  static const uint8_t table1_37_emit_[8];
  static const uint8_t table1_38_emit_[8];
  static const uint8_t table1_39_emit_[8];
  static const uint8_t table1_40_emit_[8];
  static const uint8_t table1_41_emit_[8];
  static const uint8_t table1_42_emit_[8];
  static const uint8_t table1_43_emit_[12];
  static const uint8_t table1_44_emit_[16];
  static const uint8_t table1_45_emit_[16];
  static const uint8_t table1_46_emit_[16];
  static const uint8_t table1_47_emit_[30];
  static const uint8_t table1_48_emit_[58];
  static const uint16_t table1_48_inner_[22];
  static const uint8_t table1_49_emit_[57];
  static const uint16_t table1_49_inner_[22];
  static const uint8_t table1_50_emit_[58];
  static const uint8_t table1_51_emit_[58];
  static const uint8_t table1_52_emit_[58];
  static const uint8_t table1_53_emit_[8];
  static const uint8_t table1_54_emit_[8];
  static const uint8_t table1_55_emit_[8];
  static const uint8_t table1_56_emit_[8];
  static const uint8_t table1_57_emit_[8];
  static const uint8_t table1_58_emit_[8];
  static const uint8_t table1_59_emit_[12];
  static const uint8_t table1_60_emit_[16];
  static const uint8_t table1_61_emit_[16];
  static const uint8_t table1_62_emit_[16];
  static const uint8_t table1_63_emit_[30];
  static const uint8_t table1_64_emit_[58];
  static const uint16_t table1_64_inner_[22];
  static const uint8_t table1_65_emit_[58];
  static const uint8_t table1_66_emit_[55];
  static const uint16_t table1_66_inner_[22];
  static const uint8_t table1_67_emit_[58];
  static const uint8_t table1_68_emit_[58];
  static const uint8_t table1_69_emit_[8];
  static const uint8_t table1_70_emit_[8];
  static const uint8_t table1_71_emit_[8];
  static const uint8_t table1_72_emit_[8];
  static const uint8_t table1_73_emit_[8];
  static const uint8_t table1_74_emit_[8];
  static const uint8_t table1_75_emit_[12];
  static const uint8_t table1_76_emit_[16];
  static const uint8_t table1_77_emit_[16];
  static const uint8_t table1_78_emit_[16];
  static const uint8_t table1_79_emit_[30];
  static const uint8_t table1_80_emit_[58];
  static const uint16_t table1_80_inner_[22];
  static const uint8_t table1_81_emit_[58];
  static const uint8_t table1_82_emit_[57];
  static const uint16_t table1_82_inner_[22];
  static const uint8_t table1_83_emit_[58];
  static const uint8_t table1_84_emit_[58];
  static const uint8_t table1_85_emit_[8];
  static const uint8_t table1_86_emit_[8];
  static const uint8_t table1_87_emit_[8];
  static const uint8_t table1_88_emit_[8];
  static const uint8_t table1_89_emit_[8];
  static const uint8_t table1_90_emit_[8];
  static const uint8_t table1_91_emit_[12];
  static const uint8_t table1_92_emit_[16];
  static const uint8_t table1_93_emit_[16];
  static const uint8_t table1_94_emit_[16];
  static const uint8_t table1_95_emit_[30];
  static const uint8_t table1_96_emit_[58];
  static const uint16_t table1_96_inner_[22];
  static const uint8_t table1_97_emit_[58];
  static const uint8_t table1_98_emit_[58];
  static const uint8_t table1_99_emit_[55];
  static const uint16_t table1_99_inner_[22];
  static const uint8_t table1_100_emit_[58];
  static const uint8_t table1_101_emit_[8];
  static const uint8_t table1_102_emit_[8];
  static const uint8_t table1_103_emit_[8];
  static const uint8_t table1_104_emit_[8];
  static const uint8_t table1_105_emit_[8];
  static const uint8_t table1_106_emit_[8];
  static const uint8_t table1_107_emit_[12];
  static const uint8_t table1_108_emit_[16];
  static const uint8_t table1_109_emit_[16];
  static const uint8_t table1_110_emit_[16];
  static const uint8_t table1_111_emit_[30];
  static const uint8_t table1_112_emit_[58];
  static const uint16_t table1_112_inner_[22];
  static const uint8_t table1_113_emit_[58];
  static const uint8_t table1_114_emit_[58];
  static const uint8_t table1_115_emit_[57];
  static const uint16_t table1_115_inner_[22];
  static const uint8_t table1_116_emit_[58];
  static const uint8_t table1_117_emit_[8];
  static const uint8_t table1_118_emit_[8];
  static const uint8_t table1_119_emit_[8];
  static const uint8_t table1_120_emit_[8];
  static const uint8_t table1_121_emit_[8];
  static const uint8_t table1_122_emit_[8];
  static const uint8_t table1_123_emit_[12];
  static const uint8_t table1_124_emit_[16];
  static const uint8_t table1_125_emit_[16];
  static const uint8_t table1_126_emit_[16];
  static const uint8_t table1_127_emit_[30];
  static const uint8_t table1_128_emit_[58];
  static const uint16_t table1_128_inner_[22];
  static const uint8_t table1_129_emit_[58];
  static const uint8_t table1_130_emit_[58];
  static const uint8_t table1_131_emit_[58];
  static const uint8_t table1_132_emit_[55];
  static const uint16_t table1_132_inner_[22];
  static const uint8_t table1_133_emit_[8];
  static const uint8_t table1_134_emit_[8];
  static const uint8_t table1_135_emit_[8];
  static const uint8_t table1_136_emit_[8];
  static const uint8_t table1_137_emit_[8];
  static const uint8_t table1_138_emit_[8];
  static const uint8_t table1_139_emit_[12];
  static const uint8_t table1_140_emit_[16];
  static const uint8_t table1_141_emit_[16];
  static const uint8_t table1_142_emit_[16];
  static const uint8_t table1_143_emit_[30];
  static const uint8_t table1_144_emit_[59];
  static const uint16_t table1_144_inner_[22];
  static const uint8_t table1_145_emit_[59];
  static const uint8_t table1_146_emit_[59];
  static const uint8_t table1_147_emit_[59];
  static const uint8_t table1_148_emit_[59];
  static const uint8_t table1_149_emit_[8];
  static const uint8_t table1_150_emit_[8];
  static const uint8_t table1_151_emit_[8];
  static const uint8_t table1_152_emit_[8];
  static const uint8_t table1_153_emit_[8];
  static const uint8_t table1_154_emit_[8];
  static const uint8_t table1_155_emit_[12];
  static const uint8_t table1_156_emit_[16];
  static const uint8_t table1_157_emit_[16];
  static const uint8_t table1_158_emit_[16];
  static const uint8_t table1_159_emit_[30];
  static const uint8_t table1_160_emit_[8];
  static const uint8_t table1_161_emit_[8];
  static const uint8_t table1_162_emit_[11];
  static const uint16_t table1_162_inner_[6];
  static const uint8_t table1_163_emit_[16];
  static const uint8_t table1_164_emit_[16];
  static const uint8_t table1_165_emit_[20];
  static const uint16_t table1_165_inner_[10];
  static const uint8_t table1_165_outer_[64];
  static const uint8_t table1_166_emit_[32];
  static const uint16_t table1_166_inner_[16];
  static const uint8_t table1_166_outer_[64];
  static const uint8_t table1_167_emit_[36];
  static const uint16_t table1_167_inner_[19];
  static const uint8_t table1_167_outer_[64];
  static const uint8_t table1_168_emit_[8];
  static const uint8_t table1_169_emit_[8];
  static const uint8_t table1_170_emit_[11];
  static const uint16_t table1_170_inner_[6];
  static const uint8_t table1_171_emit_[16];
  static const uint8_t table1_172_emit_[16];
  static const uint8_t table1_173_emit_[20];
  static const uint8_t table1_174_emit_[32];
  static const uint8_t table1_175_emit_[36];
  static const uint8_t table1_176_emit_[8];
  static const uint8_t table1_177_emit_[8];
  static const uint8_t table1_178_emit_[11];
  static const uint16_t table1_178_inner_[6];
  static const uint8_t table1_179_emit_[16];
  static const uint8_t table1_180_emit_[16];
  static const uint8_t table1_181_emit_[20];
  static const uint8_t table1_182_emit_[32];
  static const uint8_t table1_183_emit_[36];
  static const uint8_t table1_184_emit_[8];
  static const uint8_t table1_185_emit_[8];
  static const uint8_t table1_186_emit_[12];
  static const uint8_t table1_187_emit_[16];
  static const uint8_t table1_188_emit_[16];
  static const uint8_t table1_189_emit_[20];
  static const uint8_t table1_190_emit_[32];
  static const uint8_t table1_191_emit_[36];
  static const uint8_t table1_192_emit_[8];
  static const uint8_t table1_193_emit_[8];
  static const uint8_t table1_194_emit_[12];
  static const uint8_t table1_195_emit_[15];
  static const uint16_t table1_195_inner_[8];
  static const uint8_t table1_196_emit_[16];
  static const uint8_t table1_197_emit_[20];
  static const uint8_t table1_198_emit_[32];
  static const uint8_t table1_199_emit_[36];
  static const uint8_t table1_200_emit_[8];
  static const uint8_t table1_201_emit_[8];
  static const uint8_t table1_202_emit_[12];
  static const uint8_t table1_203_emit_[15];
  static const uint16_t table1_203_inner_[8];
  static const uint8_t table1_204_emit_[16];
  static const uint8_t table1_205_emit_[20];
  static const uint8_t table1_206_emit_[32];
  static const uint8_t table1_207_emit_[36];
  static const uint8_t table1_208_emit_[8];
  static const uint8_t table1_209_emit_[8];
  static const uint8_t table1_210_emit_[12];
  static const uint8_t table1_211_emit_[15];
  static const uint16_t table1_211_inner_[8];
  static const uint8_t table1_212_emit_[16];
  static const uint8_t table1_213_emit_[20];
  static const uint8_t table1_214_emit_[32];
  static const uint8_t table1_215_emit_[36];
  static const uint8_t table1_216_emit_[8];
  static const uint8_t table1_217_emit_[8];
  static const uint8_t table1_218_emit_[12];
  static const uint8_t table1_219_emit_[15];
  static const uint16_t table1_219_inner_[8];
  static const uint8_t table1_220_emit_[16];
  static const uint8_t table1_221_emit_[20];
  static const uint8_t table1_222_emit_[32];
  static const uint8_t table1_223_emit_[36];
  static const uint8_t table1_224_emit_[8];
  static const uint8_t table1_225_emit_[8];
  static const uint8_t table1_226_emit_[12];
  static const uint8_t table1_227_emit_[15];
  static const uint16_t table1_227_inner_[8];
  static const uint8_t table1_228_emit_[16];
  static const uint8_t table1_229_emit_[20];
  static const uint8_t table1_230_emit_[32];
  static const uint8_t table1_231_emit_[36];
  static const uint8_t table1_232_emit_[8];
  static const uint8_t table1_233_emit_[8];
  static const uint8_t table1_234_emit_[12];
  static const uint8_t table1_235_emit_[15];
  static const uint16_t table1_235_inner_[8];
  static const uint8_t table1_236_emit_[16];
  static const uint8_t table1_237_emit_[20];
  static const uint8_t table1_238_emit_[32];
  static const uint8_t table1_239_emit_[36];
  static const uint8_t table1_240_emit_[8];
  static const uint8_t table1_241_emit_[8];
  static const uint8_t table1_242_emit_[12];
  static const uint8_t table1_243_emit_[15];
  static const uint16_t table1_243_inner_[8];
  static const uint8_t table1_244_emit_[16];
  static const uint8_t table1_245_emit_[20];
  static const uint8_t table1_246_emit_[32];
  static const uint8_t table1_247_emit_[36];
  static const uint8_t table1_248_emit_[8];
  static const uint8_t table1_249_emit_[8];
  static const uint8_t table1_250_emit_[12];
  static const uint8_t table1_251_emit_[16];
  static const uint8_t table1_252_emit_[16];
  static const uint8_t table1_253_emit_[20];
  static const uint8_t table1_254_emit_[32];
  static const uint8_t table1_255_emit_[36];
  static const uint8_t table1_256_emit_[8];
  static const uint8_t table1_257_emit_[8];
  static const uint8_t table1_258_emit_[12];
  static const uint8_t table1_259_emit_[16];
  static const uint8_t table1_260_emit_[15];
  static const uint8_t table1_261_emit_[20];
  static const uint8_t table1_262_emit_[32];
  static const uint8_t table1_263_emit_[36];
  static const uint8_t table1_264_emit_[8];
  static const uint8_t table1_265_emit_[8];
  static const uint8_t table1_266_emit_[12];
  static const uint8_t table1_267_emit_[16];
  static const uint8_t table1_268_emit_[15];
  static const uint8_t table1_269_emit_[20];
  static const uint8_t table1_270_emit_[32];
  static const uint8_t table1_271_emit_[36];
  static const uint8_t table1_272_emit_[8];
  static const uint8_t table1_273_emit_[8];
  static const uint8_t table1_274_emit_[12];
  static const uint8_t table1_275_emit_[16];
  static const uint8_t table1_276_emit_[15];
  static const uint8_t table1_277_emit_[20];
  static const uint8_t table1_278_emit_[32];
  static const uint8_t table1_279_emit_[36];
  static const uint8_t table1_280_emit_[8];
  static const uint8_t table1_281_emit_[8];
  static const uint8_t table1_282_emit_[12];
  static const uint8_t table1_283_emit_[16];
  static const uint8_t table1_284_emit_[15];
  static const uint8_t table1_285_emit_[20];
  static const uint8_t table1_286_emit_[32];
  static const uint8_t table1_287_emit_[36];
  static const uint8_t table1_288_emit_[8];
  static const uint8_t table1_289_emit_[8];
  static const uint8_t table1_290_emit_[12];
  static const uint8_t table1_291_emit_[16];
  static const uint8_t table1_292_emit_[15];
  static const uint8_t table1_293_emit_[20];
  static const uint8_t table1_294_emit_[32];
  static const uint8_t table1_295_emit_[36];
  static const uint8_t table1_296_emit_[8];
  static const uint8_t table1_297_emit_[8];
  static const uint8_t table1_298_emit_[12];
  static const uint8_t table1_299_emit_[16];
  static const uint8_t table1_300_emit_[15];
  static const uint8_t table1_301_emit_[20];
  static const uint8_t table1_302_emit_[32];
  static const uint8_t table1_303_emit_[36];
  static const uint8_t table1_304_emit_[8];
  static const uint8_t table1_305_emit_[8];
  static const uint8_t table1_306_emit_[12];
  static const uint8_t table1_307_emit_[16];
  static const uint8_t table1_308_emit_[15];
  static const uint8_t table1_309_emit_[20];
  static const uint8_t table1_310_emit_[32];
  static const uint8_t table1_311_emit_[36];
  static const uint8_t table1_312_emit_[8];
  static const uint8_t table1_313_emit_[8];
  static const uint8_t table1_314_emit_[12];
  static const uint8_t table1_315_emit_[16];
  static const uint8_t table1_316_emit_[16];
  static const uint8_t table1_317_emit_[20];
  static const uint8_t table1_318_emit_[32];
  static const uint8_t table1_319_emit_[36];
  static const uint8_t table1_320_emit_[8];
  static const uint8_t table1_321_emit_[8];
  static const uint8_t table1_322_emit_[12];
  static const uint8_t table1_323_emit_[16];
  static const uint8_t table1_324_emit_[16];
  static const uint8_t table1_325_emit_[19];
  static const uint16_t table1_325_inner_[10];
  static const uint8_t table1_326_emit_[32];
  static const uint8_t table1_327_emit_[36];
  static const uint8_t table1_328_emit_[8];
  static const uint8_t table1_329_emit_[8];
  static const uint8_t table1_330_emit_[12];
  static const uint8_t table1_331_emit_[16];
  static const uint8_t table1_332_emit_[16];
  static const uint8_t table1_333_emit_[19];
  static const uint16_t table1_333_inner_[10];
  static const uint8_t table1_334_emit_[32];
  static const uint8_t table1_335_emit_[36];
  static const uint8_t table1_336_emit_[8];
  static const uint8_t table1_337_emit_[8];
  static const uint8_t table1_338_emit_[12];
  static const uint8_t table1_339_emit_[16];
  static const uint8_t table1_340_emit_[16];
  static const uint8_t table1_341_emit_[19];
  static const uint16_t table1_341_inner_[10];
  static const uint8_t table1_342_emit_[32];
  static const uint8_t table1_343_emit_[36];
  static const uint8_t table1_344_emit_[8];
  static const uint8_t table1_345_emit_[8];
  static const uint8_t table1_346_emit_[12];
  static const uint8_t table1_347_emit_[16];
  static const uint8_t table1_348_emit_[16];
  static const uint8_t table1_349_emit_[19];
  static const uint16_t table1_349_inner_[10];
  static const uint8_t table1_350_emit_[32];
  static const uint8_t table1_351_emit_[36];
  static const uint8_t table1_352_emit_[8];
  static const uint8_t table1_353_emit_[8];
  static const uint8_t table1_354_emit_[12];
  static const uint8_t table1_355_emit_[16];
  static const uint8_t table1_356_emit_[16];
  static const uint8_t table1_357_emit_[19];
  static const uint16_t table1_357_inner_[10];
  static const uint8_t table1_358_emit_[32];
  static const uint8_t table1_359_emit_[36];
  static const uint8_t table1_360_emit_[8];
  static const uint8_t table1_361_emit_[8];
  static const uint8_t table1_362_emit_[12];
  static const uint8_t table1_363_emit_[16];
  static const uint8_t table1_364_emit_[16];
  static const uint8_t table1_365_emit_[19];
  static const uint16_t table1_365_inner_[10];
  static const uint8_t table1_366_emit_[32];
  static const uint8_t table1_367_emit_[36];
  static const uint8_t table1_368_emit_[16];
  static const uint8_t table1_369_emit_[28];
  static const uint16_t table1_369_inner_[14];
  static const uint8_t table1_369_outer_[64];
  static const uint8_t table1_370_emit_[35];
  static const uint16_t table1_370_inner_[18];
  static const uint8_t table1_370_outer_[64];
  static const uint8_t table1_371_emit_[68];
  static const uint16_t table1_371_inner_[35];
  static const uint8_t table1_371_outer_[64];
  static const uint8_t table1_372_emit_[16];
  static const uint8_t table1_373_emit_[28];
  static const uint8_t table1_374_emit_[35];
  static const uint16_t table1_374_inner_[18];
  static const uint8_t table1_375_emit_[68];
  static const uint8_t table1_376_emit_[16];
  static const uint8_t table1_377_emit_[28];
  static const uint8_t table1_378_emit_[35];
  static const uint16_t table1_378_inner_[18];
  static const uint8_t table1_379_emit_[68];
  static const uint8_t table1_380_emit_[16];
  static const uint8_t table1_381_emit_[28];
  static const uint8_t table1_382_emit_[36];
  static const uint16_t table1_382_inner_[18];
  static const uint8_t table1_383_emit_[68];
  static const uint8_t table1_384_emit_[16];
  static const uint8_t table1_385_emit_[28];
  static const uint8_t table1_386_emit_[36];
  static const uint8_t table1_387_emit_[67];
  static const uint16_t table1_387_inner_[35];
  static const uint8_t table1_388_emit_[16];
  static const uint8_t table1_389_emit_[28];
  static const uint8_t table1_390_emit_[36];
  static const uint8_t table1_391_emit_[67];
  static const uint16_t table1_391_inner_[35];
  static const uint8_t table1_392_emit_[16];
  static const uint8_t table1_393_emit_[28];
  static const uint8_t table1_394_emit_[36];
  static const uint8_t table1_395_emit_[67];
  static const uint16_t table1_395_inner_[35];
  static const uint8_t table1_396_emit_[16];
  static const uint8_t table1_397_emit_[28];
  static const uint8_t table1_398_emit_[36];
  static const uint8_t table1_399_emit_[67];
  static const uint16_t table1_399_inner_[35];
  static const uint8_t table1_400_emit_[16];
  static const uint8_t table1_401_emit_[28];
  static const uint8_t table1_402_emit_[36];
  static const uint8_t table1_403_emit_[67];
  static const uint16_t table1_403_inner_[35];
  static const uint8_t table1_404_emit_[16];
  static const uint8_t table1_405_emit_[28];
  static const uint8_t table1_406_emit_[36];
  static const uint8_t table1_407_emit_[67];
  static const uint16_t table1_407_inner_[35];
  static const uint8_t table1_408_emit_[16];
  static const uint8_t table1_409_emit_[28];
  static const uint8_t table1_410_emit_[36];
  static const uint8_t table1_411_emit_[67];
  static const uint16_t table1_411_inner_[35];
  static const uint8_t table1_412_emit_[16];
  static const uint8_t table1_413_emit_[28];
  static const uint8_t table1_414_emit_[36];
  static const uint8_t table1_415_emit_[67];
  static const uint16_t table1_415_inner_[35];
  static const uint8_t table1_416_emit_[16];
  static const uint8_t table1_417_emit_[28];
  static const uint8_t table1_418_emit_[36];
  static const uint8_t table1_419_emit_[67];
  static const uint16_t table1_419_inner_[35];
  static const uint8_t table1_420_emit_[16];
  static const uint8_t table1_421_emit_[28];
  static const uint8_t table1_422_emit_[36];
  static const uint8_t table1_423_emit_[67];
  static const uint16_t table1_423_inner_[35];
  static const uint8_t table1_424_emit_[16];
  static const uint8_t table1_425_emit_[28];
  static const uint8_t table1_426_emit_[36];
  static const uint8_t table1_427_emit_[67];
  static const uint16_t table1_427_inner_[35];
  static const uint8_t table1_428_emit_[16];
  static const uint8_t table1_429_emit_[28];
  static const uint8_t table1_430_emit_[36];
  static const uint8_t table1_431_emit_[67];
  static const uint16_t table1_431_inner_[35];
  static const uint8_t table1_432_emit_[16];
  static const uint8_t table1_433_emit_[28];
  static const uint8_t table1_434_emit_[36];
  static const uint8_t table1_435_emit_[67];
  static const uint16_t table1_435_inner_[35];
  static const uint8_t table1_436_emit_[16];
  static const uint8_t table1_437_emit_[28];
  static const uint8_t table1_438_emit_[36];
  static const uint8_t table1_439_emit_[67];
  static const uint16_t table1_439_inner_[35];
  static const uint8_t table1_440_emit_[16];
  static const uint8_t table1_441_emit_[28];
  static const uint8_t table1_442_emit_[36];
  static const uint8_t table1_443_emit_[67];
  static const uint16_t table1_443_inner_[35];
  static const uint8_t table1_444_emit_[16];
  static const uint8_t table1_445_emit_[28];
  static const uint8_t table1_446_emit_[36];
  static const uint8_t table1_447_emit_[67];
  static const uint16_t table1_447_inner_[35];
  static const uint8_t table1_448_emit_[16];
  static const uint8_t table1_449_emit_[28];
  static const uint8_t table1_450_emit_[36];
  static const uint8_t table1_451_emit_[67];
  static const uint16_t table1_451_inner_[35];
  static const uint8_t table1_452_emit_[16];
  static const uint8_t table1_453_emit_[28];
  static const uint8_t table1_454_emit_[36];
  static const uint8_t table1_455_emit_[67];
  static const uint16_t table1_455_inner_[35];
  static const uint8_t table1_456_emit_[16];
  static const uint8_t table1_457_emit_[28];
  static const uint8_t table1_458_emit_[36];
  static const uint8_t table1_459_emit_[67];
  static const uint16_t table1_459_inner_[35];
  static const uint8_t table1_460_emit_[16];
  static const uint8_t table1_461_emit_[28];
  static const uint8_t table1_462_emit_[36];
  static const uint8_t table1_463_emit_[67];
  static const uint16_t table1_463_inner_[35];
  static const uint8_t table1_464_emit_[16];
  static const uint8_t table1_465_emit_[28];
  static const uint8_t table1_466_emit_[36];
  static const uint8_t table1_467_emit_[67];
  static const uint16_t table1_467_inner_[35];
  static const uint8_t table1_468_emit_[16];
  static const uint8_t table1_469_emit_[28];
  static const uint8_t table1_470_emit_[36];
  static const uint8_t table1_471_emit_[67];
  static const uint16_t table1_471_inner_[35];
  static const uint8_t table1_472_emit_[16];
  static const uint8_t table1_473_emit_[28];
  static const uint8_t table1_474_emit_[36];
  static const uint8_t table1_475_emit_[67];
  static const uint16_t table1_475_inner_[35];
  static const uint8_t table1_476_emit_[16];
  static const uint8_t table1_477_emit_[28];
  static const uint8_t table1_478_emit_[36];
  static const uint8_t table1_479_emit_[67];
  static const uint16_t table1_479_inner_[35];
  static const uint8_t table1_480_emit_[16];
  static const uint8_t table1_481_emit_[28];
  static const uint8_t table1_482_emit_[36];
  static const uint8_t table1_483_emit_[67];
  static const uint16_t table1_483_inner_[35];
  static const uint8_t table1_484_emit_[16];
  static const uint8_t table1_485_emit_[28];
  static const uint8_t table1_486_emit_[36];
  static const uint8_t table1_487_emit_[67];
  static const uint16_t table1_487_inner_[35];
  static const uint8_t table1_488_emit_[16];
  static const uint8_t table1_489_emit_[28];
  static const uint8_t table1_490_emit_[36];
  static const uint8_t table1_491_emit_[67];
  static const uint16_t table1_491_inner_[35];
  static const uint8_t table1_492_emit_[16];
  static const uint8_t table1_493_emit_[28];
  static const uint8_t table1_494_emit_[36];
  static const uint8_t table1_495_emit_[67];
  static const uint16_t table1_495_inner_[35];
  static const uint8_t table1_496_emit_[44];
  static const uint16_t table1_496_inner_[22];
  static const uint8_t table1_496_outer_[64];
  static const uint8_t table1_497_emit_[92];
  static const uint16_t table1_497_inner_[47];
  static const uint8_t table1_497_outer_[64];
  static const uint8_t table1_498_emit_[44];
  static const uint8_t table1_499_emit_[92];
  static const uint8_t table1_500_emit_[44];
  static const uint8_t table1_501_emit_[92];
  static const uint8_t table1_502_emit_[44];
  static const uint8_t table1_503_emit_[92];
  static const uint8_t table1_504_emit_[44];
  static const uint8_t table1_505_emit_[92];
  static const uint8_t table1_506_emit_[44];
  static const uint8_t table1_507_emit_[92];
  static const uint8_t table1_508_emit_[40];
  static const uint16_t table1_508_inner_[22];
  static const uint8_t table1_509_emit_[40];
  static const uint8_t table1_510_emit_[22];
  static const uint16_t table1_510_inner_[13];
  static const uint8_t table1_510_outer_[64];
  static const uint8_t table1_511_emit_[14];
  static const uint16_t table1_511_inner_[15];
  static const uint8_t table1_511_outer_[64];
  static const uint8_t* const table1_emit_[512];
  static const uint16_t* const table1_inner_[512];
  static const uint8_t* const table1_outer_[512];
  static const uint8_t table13_0_inner_[5];
  static const uint8_t table14_0_emit_[11];
  static const uint8_t table14_0_ops_[32];
  static const uint8_t table15_0_emit_[24];
  static const uint8_t table15_0_ops_[64];
  static const uint8_t table12_0_emit_[50];
  static const uint16_t table12_0_inner_[70];
  static const uint8_t table12_0_outer_[128];
  static const uint8_t table33_0_emit_[15];
  static const uint8_t table33_0_inner_[16];
  static const uint8_t table32_0_emit_[17];
  static const uint8_t table32_0_ops_[32];
  static const uint8_t table36_0_emit_[6];
  static const uint8_t table36_0_inner_[6];
  static const uint8_t table39_0_emit_[17];
  static const uint8_t table39_0_ops_[32];
  static const uint8_t table40_0_emit_[46];
  static const uint8_t table40_0_ops_[64];
  static const uint8_t table41_0_ops_[128];
  static const uint8_t table38_0_emit_[4];
  static const uint16_t table38_0_ops_[32];
  static const uint8_t table38_1_emit_[4];
  static const uint8_t table38_2_emit_[4];
  static const uint8_t table38_3_emit_[4];
  static const uint8_t table38_4_emit_[7];
  static const uint16_t table38_4_ops_[32];
  static const uint8_t table38_5_emit_[8];
  static const uint16_t table38_5_ops_[32];
  static const uint8_t table38_6_emit_[8];
  static const uint8_t table38_7_emit_[10];
  static const uint16_t table38_7_ops_[32];
  static const uint8_t* const table38_emit_[8];
  static const uint16_t* const table38_ops_[8];
};
template <typename F>
class HuffDecoder : public HuffDecoderCommon {
 public:
  HuffDecoder(F sink, const uint8_t* begin, const uint8_t* end)
      : sink_(sink), begin_(begin), end_(end) {}
  bool Run() {
    while (!done_) {
      if (!RefillTo15()) {
        Done0();
        break;
      }
      const auto index = (buffer_ >> (buffer_len_ - 15)) & 0x7fff;
      const auto op = GetOp1(index);
      const int consumed = op & 15;
      buffer_len_ -= consumed;
      const auto emit_ofs = op >> 6;
      switch ((op >> 4) & 3) {
        case 0: {
          sink_(GetEmit1(index, emit_ofs + 0));
          sink_(GetEmit1(index, emit_ofs + 1));
          sink_(GetEmit1(index, emit_ofs + 2));
          break;
        }
        case 1: {
          sink_(GetEmit1(index, emit_ofs + 0));
          sink_(GetEmit1(index, emit_ofs + 1));
          break;
        }
        case 2: {
          sink_(GetEmit1(index, emit_ofs + 0));
          break;
        }
        case 3: {
          DecodeStep0();
          break;
        }
      }
    }
    return ok_;
  }

 private:
  bool RefillTo15() {
    switch (buffer_len_) {
      case 0: {
        return Read2to8Bytes();
      }
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6: {
        return Read2to7Bytes();
      }
      case 7:
      case 8: {
        return Read1to7Bytes();
      }
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14: {
        return Read1to6Bytes();
      }
    }
    return true;
  }
  bool Read2to8Bytes() {
    switch (end_ - begin_) {
      case 0:
      case 1: {
        return false;
      }
      case 2: {
        Fill2();
        return true;
      }
      case 3: {
        Fill3();
        return true;
      }
      case 4: {
        Fill4();
        return true;
      }
      case 5: {
        Fill5();
        return true;
      }
      case 6: {
        Fill6();
        return true;
      }
      case 7: {
        Fill7();
        return true;
      }
      default: {
        Fill8();
        return true;
      }
    }
  }
  void Fill2() {
    buffer_ = (buffer_ << 16) | (static_cast<uint64_t>(begin_[0]) << 8) |
              (static_cast<uint64_t>(begin_[1]) << 0);
    begin_ += 2;
    buffer_len_ += 16;
  }
  void Fill3() {
    buffer_ = (buffer_ << 24) | (static_cast<uint64_t>(begin_[0]) << 16) |
              (static_cast<uint64_t>(begin_[1]) << 8) |
              (static_cast<uint64_t>(begin_[2]) << 0);
    begin_ += 3;
    buffer_len_ += 24;
  }
  void Fill4() {
    buffer_ = (buffer_ << 32) | (static_cast<uint64_t>(begin_[0]) << 24) |
              (static_cast<uint64_t>(begin_[1]) << 16) |
              (static_cast<uint64_t>(begin_[2]) << 8) |
              (static_cast<uint64_t>(begin_[3]) << 0);
    begin_ += 4;
    buffer_len_ += 32;
  }
  void Fill5() {
    buffer_ = (buffer_ << 40) | (static_cast<uint64_t>(begin_[0]) << 32) |
              (static_cast<uint64_t>(begin_[1]) << 24) |
              (static_cast<uint64_t>(begin_[2]) << 16) |
              (static_cast<uint64_t>(begin_[3]) << 8) |
              (static_cast<uint64_t>(begin_[4]) << 0);
    begin_ += 5;
    buffer_len_ += 40;
  }
  void Fill6() {
    buffer_ = (buffer_ << 48) | (static_cast<uint64_t>(begin_[0]) << 40) |
              (static_cast<uint64_t>(begin_[1]) << 32) |
              (static_cast<uint64_t>(begin_[2]) << 24) |
              (static_cast<uint64_t>(begin_[3]) << 16) |
              (static_cast<uint64_t>(begin_[4]) << 8) |
              (static_cast<uint64_t>(begin_[5]) << 0);
    begin_ += 6;
    buffer_len_ += 48;
  }
  void Fill7() {
    buffer_ = (buffer_ << 56) | (static_cast<uint64_t>(begin_[0]) << 48) |
              (static_cast<uint64_t>(begin_[1]) << 40) |
              (static_cast<uint64_t>(begin_[2]) << 32) |
              (static_cast<uint64_t>(begin_[3]) << 24) |
              (static_cast<uint64_t>(begin_[4]) << 16) |
              (static_cast<uint64_t>(begin_[5]) << 8) |
              (static_cast<uint64_t>(begin_[6]) << 0);
    begin_ += 7;
    buffer_len_ += 56;
  }
  void Fill8() {
    buffer_ = 0 | (static_cast<uint64_t>(begin_[0]) << 56) |
              (static_cast<uint64_t>(begin_[1]) << 48) |
              (static_cast<uint64_t>(begin_[2]) << 40) |
              (static_cast<uint64_t>(begin_[3]) << 32) |
              (static_cast<uint64_t>(begin_[4]) << 24) |
              (static_cast<uint64_t>(begin_[5]) << 16) |
              (static_cast<uint64_t>(begin_[6]) << 8) |
              (static_cast<uint64_t>(begin_[7]) << 0);
    begin_ += 8;
    buffer_len_ += 64;
  }
  bool Read2to7Bytes() {
    switch (end_ - begin_) {
      case 0:
      case 1: {
        return false;
      }
      case 2: {
        Fill2();
        return true;
      }
      case 3: {
        Fill3();
        return true;
      }
      case 4: {
        Fill4();
        return true;
      }
      case 5: {
        Fill5();
        return true;
      }
      case 6: {
        Fill6();
        return true;
      }
      default: {
        Fill7();
        return true;
      }
    }
  }
  bool Read1to7Bytes() {
    switch (end_ - begin_) {
      case 0: {
        return false;
      }
      case 1: {
        Fill1();
        return true;
      }
      case 2: {
        Fill2();
        return true;
      }
      case 3: {
        Fill3();
        return true;
      }
      case 4: {
        Fill4();
        return true;
      }
      case 5: {
        Fill5();
        return true;
      }
      case 6: {
        Fill6();
        return true;
      }
      default: {
        Fill7();
        return true;
      }
    }
  }
  void Fill1() {
    buffer_ = (buffer_ << 8) | (static_cast<uint64_t>(begin_[0]) << 0);
    begin_ += 1;
    buffer_len_ += 8;
  }
  bool Read1to6Bytes() {
    switch (end_ - begin_) {
      case 0: {
        return false;
      }
      case 1: {
        Fill1();
        return true;
      }
      case 2: {
        Fill2();
        return true;
      }
      case 3: {
        Fill3();
        return true;
      }
      case 4: {
        Fill4();
        return true;
      }
      case 5: {
        Fill5();
        return true;
      }
      default: {
        Fill6();
        return true;
      }
    }
  }
  void Done0() {
    done_ = true;
    switch (end_ - begin_) {
      case 1: {
        Fill1();
        break;
      }
    }
    switch (buffer_len_) {
      case 1:
      case 2:
      case 3:
      case 4: {
        ok_ = (buffer_ & ((1 << buffer_len_) - 1)) == (1 << buffer_len_) - 1;
        return;
      }
      case 5: {
        const auto index = buffer_ & 31;
        const auto op = GetOp2(index);
        switch (op & 3) {
          case 0: {
            sink_(GetEmit2(index, (op >> 2) + 0));
            break;
          }
          case 1: {
            ok_ = false;
            break;
          }
        }
        return;
      }
      case 6: {
        const auto index = buffer_ & 63;
        const auto op = GetOp3(index);
        switch (op & 3) {
          case 0: {
            ok_ = false;
            break;
          }
          case 1: {
            sink_(GetEmit3(index, (op >> 2) + 0));
            break;
          }
        }
        return;
      }
      case 7: {
        const auto index = buffer_ & 127;
        const auto op = GetOp4(index);
        switch (op & 3) {
          case 0: {
            ok_ = false;
            break;
          }
          case 1: {
            sink_(GetEmit4(index, (op >> 2) + 0));
            break;
          }
        }
        return;
      }
      case 8: {
        const auto index = buffer_ & 255;
        const auto op = GetOp5(index);
        switch (op & 3) {
          case 0: {
            ok_ = false;
            break;
          }
          case 1: {
            sink_(GetEmit5(index, (op >> 2) + 0));
            break;
          }
        }
        return;
      }
      case 9: {
        const auto index = buffer_ & 511;
        const auto op = GetOp6(index);
        switch (op & 3) {
          case 0: {
            ok_ = false;
            break;
          }
          case 1: {
            sink_(GetEmit6(index, (op >> 2) + 0));
            break;
          }
        }
        return;
      }
      case 10: {
        const auto index = buffer_ & 1023;
        const auto op = GetOp7(index);
        switch (op & 3) {
          case 0: {
            sink_(GetEmit7(index, (op >> 2) + 0));
            sink_(GetEmit7(index, (op >> 2) + 1));
            break;
          }
          case 1: {
            ok_ = false;
            break;
          }
          case 2: {
            sink_(GetEmit7(index, (op >> 2) + 0));
            break;
          }
        }
        return;
      }
      case 11: {
        const auto index = buffer_ & 2047;
        const auto op = GetOp8(index);
        switch (op & 3) {
          case 0: {
            ok_ = false;
            break;
          }
          case 1: {
            sink_(GetEmit8(index, (op >> 2) + 0));
            sink_(GetEmit8(index, (op >> 2) + 1));
            break;
          }
          case 2: {
            sink_(GetEmit8(index, (op >> 2) + 0));
            break;
          }
        }
        return;
      }
      case 12: {
        const auto index = buffer_ & 4095;
        const auto op = GetOp9(index);
        switch (op & 3) {
          case 0: {
            ok_ = false;
            break;
          }
          case 1: {
            sink_(GetEmit9(index, (op >> 2) + 0));
            sink_(GetEmit9(index, (op >> 2) + 1));
            break;
          }
          case 2: {
            sink_(GetEmit9(index, (op >> 2) + 0));
            break;
          }
        }
        return;
      }
      case 13: {
        const auto index = buffer_ & 8191;
        const auto op = GetOp10(index);
        switch (op & 3) {
          case 0: {
            ok_ = false;
            break;
          }
          case 1: {
            sink_(GetEmit10(index, (op >> 2) + 0));
            sink_(GetEmit10(index, (op >> 2) + 1));
            break;
          }
          case 2: {
            sink_(GetEmit10(index, (op >> 2) + 0));
            break;
          }
        }
        return;
      }
      case 14: {
        const auto index = buffer_ & 16383;
        const auto op = GetOp11(index);
        switch (op & 3) {
          case 0: {
            ok_ = false;
            break;
          }
          case 1: {
            sink_(GetEmit11(index, (op >> 2) + 0));
            sink_(GetEmit11(index, (op >> 2) + 1));
            break;
          }
          case 2: {
            sink_(GetEmit11(index, (op >> 2) + 0));
            break;
          }
        }
        return;
      }
      case 0: {
        return;
      }
    }
  }
  void DecodeStep0() {
    if (!RefillTo7()) {
      Done1();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 7)) & 0x7f;
    const auto op = GetOp12(index);
    const int consumed = op & 7;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 8;
    switch ((op >> 3) & 31) {
      case 0: {
        sink_(GetEmit12(index, emit_ofs + 0));
        break;
      }
      case 1: {
        DecodeStep1();
        break;
      }
      case 2: {
        DecodeStep2();
        break;
      }
      case 3: {
        DecodeStep3();
        break;
      }
      case 4: {
        DecodeStep4();
        break;
      }
      case 5: {
        DecodeStep5();
        break;
      }
      case 6: {
        DecodeStep6();
        break;
      }
      case 7: {
        DecodeStep7();
        break;
      }
      case 8: {
        DecodeStep8();
        break;
      }
      case 9: {
        DecodeStep9();
        break;
      }
      case 10: {
        DecodeStep10();
        break;
      }
      case 11: {
        DecodeStep11();
        break;
      }
      case 12: {
        DecodeStep12();
        break;
      }
      case 13: {
        DecodeStep13();
        break;
      }
      case 14: {
        DecodeStep14();
        break;
      }
      case 15: {
        DecodeStep18();
        break;
      }
      case 16: {
        DecodeStep15();
        break;
      }
      case 17: {
        DecodeStep16();
        break;
      }
      case 18: {
        DecodeStep19();
        break;
      }
      case 19: {
        DecodeStep17();
        break;
      }
      case 20: {
        DecodeStep20();
        break;
      }
    }
  }
  bool RefillTo7() {
    switch (buffer_len_) {
      case 0: {
        return Read1to8Bytes();
      }
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6: {
        return Read1to7Bytes();
      }
    }
    return true;
  }
  bool Read1to8Bytes() {
    switch (end_ - begin_) {
      case 0: {
        return false;
      }
      case 1: {
        Fill1();
        return true;
      }
      case 2: {
        Fill2();
        return true;
      }
      case 3: {
        Fill3();
        return true;
      }
      case 4: {
        Fill4();
        return true;
      }
      case 5: {
        Fill5();
        return true;
      }
      case 6: {
        Fill6();
        return true;
      }
      case 7: {
        Fill7();
        return true;
      }
      default: {
        Fill8();
        return true;
      }
    }
  }
  void Done1() {
    done_ = true;
    switch (buffer_len_) {
      case 1:
      case 2:
      case 3: {
        ok_ = (buffer_ & ((1 << buffer_len_) - 1)) == (1 << buffer_len_) - 1;
        return;
      }
      case 4: {
        const auto index = buffer_ & 15;
        const auto op = GetOp13(index);
        switch (op & 3) {
          case 0: {
            sink_(GetEmit13(index, (op >> 2) + 0));
            break;
          }
          case 1: {
            ok_ = false;
            break;
          }
        }
        return;
      }
      case 5: {
        const auto index = buffer_ & 31;
        const auto op = GetOp14(index);
        switch (op & 3) {
          case 0: {
            ok_ = false;
            break;
          }
          case 1: {
            sink_(GetEmit14(index, (op >> 2) + 0));
            break;
          }
        }
        return;
      }
      case 6: {
        const auto index = buffer_ & 63;
        const auto op = GetOp15(index);
        switch (op & 3) {
          case 0: {
            ok_ = false;
            break;
          }
          case 1: {
            sink_(GetEmit15(index, (op >> 2) + 0));
            break;
          }
        }
        return;
      }
      case 0: {
        return;
      }
    }
  }
  void DecodeStep1() {
    if (!RefillTo1()) {
      Done2();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 1)) & 0x1;
    const auto op = GetOp16(index);
    const int consumed = op & 1;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 1;
    sink_(GetEmit16(index, emit_ofs + 0));
  }
  bool RefillTo1() {
    switch (buffer_len_) {
      case 0: {
        return Read1to8Bytes();
      }
    }
    return true;
  }
  void Done2() {
    done_ = true;
    ok_ = false;
  }
  void DecodeStep2() {
    if (!RefillTo1()) {
      Done3();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 1)) & 0x1;
    const auto op = GetOp17(index);
    const int consumed = op & 1;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 1;
    sink_(GetEmit17(index, emit_ofs + 0));
  }
  void Done3() {
    done_ = true;
    ok_ = false;
  }
  void DecodeStep3() {
    if (!RefillTo1()) {
      Done4();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 1)) & 0x1;
    const auto op = GetOp18(index);
    const int consumed = op & 1;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 1;
    sink_(GetEmit18(index, emit_ofs + 0));
  }
  void Done4() {
    done_ = true;
    ok_ = false;
  }
  void DecodeStep4() {
    if (!RefillTo1()) {
      Done5();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 1)) & 0x1;
    const auto op = GetOp19(index);
    const int consumed = op & 1;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 1;
    sink_(GetEmit19(index, emit_ofs + 0));
  }
  void Done5() {
    done_ = true;
    ok_ = false;
  }
  void DecodeStep5() {
    if (!RefillTo1()) {
      Done6();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 1)) & 0x1;
    const auto op = GetOp20(index);
    const int consumed = op & 1;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 1;
    sink_(GetEmit20(index, emit_ofs + 0));
  }
  void Done6() {
    done_ = true;
    ok_ = false;
  }
  void DecodeStep6() {
    if (!RefillTo1()) {
      Done7();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 1)) & 0x1;
    const auto op = GetOp21(index);
    const int consumed = op & 1;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 1;
    sink_(GetEmit21(index, emit_ofs + 0));
  }
  void Done7() {
    done_ = true;
    ok_ = false;
  }
  void DecodeStep7() {
    if (!RefillTo1()) {
      Done8();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 1)) & 0x1;
    const auto op = GetOp22(index);
    const int consumed = op & 1;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 1;
    sink_(GetEmit22(index, emit_ofs + 0));
  }
  void Done8() {
    done_ = true;
    ok_ = false;
  }
  void DecodeStep8() {
    if (!RefillTo1()) {
      Done9();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 1)) & 0x1;
    const auto op = GetOp23(index);
    const int consumed = op & 1;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 1;
    sink_(GetEmit23(index, emit_ofs + 0));
  }
  void Done9() {
    done_ = true;
    ok_ = false;
  }
  void DecodeStep9() {
    if (!RefillTo1()) {
      Done10();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 1)) & 0x1;
    const auto op = GetOp24(index);
    const int consumed = op & 1;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 1;
    sink_(GetEmit24(index, emit_ofs + 0));
  }
  void Done10() {
    done_ = true;
    ok_ = false;
  }
  void DecodeStep10() {
    if (!RefillTo1()) {
      Done11();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 1)) & 0x1;
    const auto op = GetOp25(index);
    const int consumed = op & 1;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 1;
    sink_(GetEmit25(index, emit_ofs + 0));
  }
  void Done11() {
    done_ = true;
    ok_ = false;
  }
  void DecodeStep11() {
    if (!RefillTo1()) {
      Done12();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 1)) & 0x1;
    const auto op = GetOp26(index);
    const int consumed = op & 1;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 1;
    sink_(GetEmit26(index, emit_ofs + 0));
  }
  void Done12() {
    done_ = true;
    ok_ = false;
  }
  void DecodeStep12() {
    if (!RefillTo1()) {
      Done13();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 1)) & 0x1;
    const auto op = GetOp27(index);
    const int consumed = op & 1;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 1;
    sink_(GetEmit27(index, emit_ofs + 0));
  }
  void Done13() {
    done_ = true;
    ok_ = false;
  }
  void DecodeStep13() {
    if (!RefillTo1()) {
      Done14();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 1)) & 0x1;
    const auto op = GetOp28(index);
    const int consumed = op & 1;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 1;
    sink_(GetEmit28(index, emit_ofs + 0));
  }
  void Done14() {
    done_ = true;
    ok_ = false;
  }
  void DecodeStep14() {
    if (!RefillTo1()) {
      Done15();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 1)) & 0x1;
    const auto op = GetOp29(index);
    const int consumed = op & 1;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 1;
    sink_(GetEmit29(index, emit_ofs + 0));
  }
  void Done15() {
    done_ = true;
    ok_ = false;
  }
  void DecodeStep15() {
    if (!RefillTo2()) {
      Done16();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 2)) & 0x3;
    const auto op = GetOp30(index);
    const int consumed = op & 3;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 2;
    sink_(GetEmit30(index, emit_ofs + 0));
  }
  bool RefillTo2() {
    switch (buffer_len_) {
      case 0: {
        return Read1to8Bytes();
      }
      case 1: {
        return Read1to7Bytes();
      }
    }
    return true;
  }
  void Done16() {
    done_ = true;
    switch (buffer_len_) {
      case 1:
      case 0: {
        ok_ = false;
        return;
      }
    }
  }
  void DecodeStep16() {
    if (!RefillTo2()) {
      Done17();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 2)) & 0x3;
    const auto op = GetOp31(index);
    const int consumed = op & 3;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 2;
    sink_(GetEmit31(index, emit_ofs + 0));
  }
  void Done17() {
    done_ = true;
    switch (buffer_len_) {
      case 1:
      case 0: {
        ok_ = false;
        return;
      }
    }
  }
  void DecodeStep17() {
    if (!RefillTo5()) {
      Done18();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 5)) & 0x1f;
    const auto op = GetOp32(index);
    const int consumed = op & 7;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 3;
    sink_(GetEmit32(index, emit_ofs + 0));
  }
  bool RefillTo5() {
    switch (buffer_len_) {
      case 0: {
        return Read1to8Bytes();
      }
      case 1:
      case 2:
      case 3:
      case 4: {
        return Read1to7Bytes();
      }
    }
    return true;
  }
  void Done18() {
    done_ = true;
    switch (buffer_len_) {
      case 1:
      case 2:
      case 3:
      case 0: {
        ok_ = false;
        return;
      }
      case 4: {
        const auto index = buffer_ & 15;
        const auto op = GetOp33(index);
        switch (op & 1) {
          case 0: {
            sink_(GetEmit33(index, (op >> 1) + 0));
            break;
          }
          case 1: {
            ok_ = false;
            break;
          }
        }
        return;
      }
    }
  }
  void DecodeStep18() {
    if (!RefillTo2()) {
      Done19();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 2)) & 0x3;
    const auto op = GetOp34(index);
    const int consumed = op & 3;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 2;
    sink_(GetEmit34(index, emit_ofs + 0));
  }
  void Done19() {
    done_ = true;
    switch (buffer_len_) {
      case 1: {
        const auto index = buffer_ & 1;
        const auto op = GetOp35(index);
        switch (op & 1) {
          case 0: {
            sink_(GetEmit35(index, (op >> 1) + 0));
            break;
          }
          case 1: {
            ok_ = false;
            break;
          }
        }
        return;
      }
      case 0: {
        ok_ = false;
        return;
      }
    }
  }
  void DecodeStep19() {
    if (!RefillTo3()) {
      Done20();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 3)) & 0x7;
    const auto op = GetOp36(index);
    const int consumed = op & 3;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 2;
    sink_(GetEmit36(index, emit_ofs + 0));
  }
  bool RefillTo3() {
    switch (buffer_len_) {
      case 0: {
        return Read1to8Bytes();
      }
      case 1:
      case 2: {
        return Read1to7Bytes();
      }
    }
    return true;
  }
  void Done20() {
    done_ = true;
    switch (buffer_len_) {
      case 1:
      case 0: {
        ok_ = false;
        return;
      }
      case 2: {
        const auto index = buffer_ & 3;
        const auto op = GetOp37(index);
        switch (op & 1) {
          case 0: {
            sink_(GetEmit37(index, (op >> 1) + 0));
            break;
          }
          case 1: {
            ok_ = false;
            break;
          }
        }
        return;
      }
    }
  }
  void DecodeStep20() {
    if (!RefillTo8()) {
      Done21();
      return;
    }
    const auto index = (buffer_ >> (buffer_len_ - 8)) & 0xff;
    const auto op = GetOp38(index);
    const int consumed = op & 15;
    buffer_len_ -= consumed;
    const auto emit_ofs = op >> 5;
    switch ((op >> 4) & 1) {
      case 0: {
        sink_(GetEmit38(index, emit_ofs + 0));
        break;
      }
      case 1: {
        begin_ = end_;
        buffer_len_ = 0;
        break;
      }
    }
  }
  bool RefillTo8() {
    switch (buffer_len_) {
      case 0: {
        return Read1to8Bytes();
      }
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7: {
        return Read1to7Bytes();
      }
    }
    return true;
  }
  void Done21() {
    done_ = true;
    switch (end_ - begin_) {}
    switch (buffer_len_) {
      case 1:
      case 2:
      case 3:
      case 4: {
        ok_ = (buffer_ & ((1 << buffer_len_) - 1)) == (1 << buffer_len_) - 1;
        return;
      }
      case 5: {
        const auto index = buffer_ & 31;
        const auto op = GetOp39(index);
        switch (op & 3) {
          case 0: {
            sink_(GetEmit39(index, (op >> 2) + 0));
            break;
          }
          case 1: {
            ok_ = false;
            break;
          }
        }
        return;
      }
      case 6: {
        const auto index = buffer_ & 63;
        const auto op = GetOp40(index);
        switch (op & 3) {
          case 0: {
            ok_ = false;
            break;
          }
          case 1: {
            sink_(GetEmit40(index, (op >> 2) + 0));
            break;
          }
        }
        return;
      }
      case 7: {
        const auto index = buffer_ & 127;
        const auto op = GetOp41(index);
        switch (op & 3) {
          case 0: {
            ok_ = false;
            break;
          }
          case 1: {
            sink_(GetEmit41(index, (op >> 2) + 0));
            break;
          }
        }
        return;
      }
      case 0: {
        return;
      }
    }
  }
  F sink_;
  const uint8_t* begin_;
  const uint8_t* const end_;
  uint64_t buffer_ = 0;
  int buffer_len_ = 0;
  bool ok_ = true;
  bool done_ = false;
};
}
#endif
