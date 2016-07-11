#ifndef _CODEGEN_H
#define _CODEGEN_H


// you likely will need to include other
// header files from your compiler here
#include "parser.h"
#include <string.h>

#define PR_INT 1
#define PR_STR 4

// add all definitions exported by your code gen modules here
// extern void codegen();

typedef struct single_line {
    int type;
    int opcode;
    int rd;
    int rs;
    int rt;
    int immed;
    char* target;
    char target_num;
} single_line;

// AND, DIV, MULT, OR have conflicting names with the token enum
// in here they are no referred to as ADD_MIPS, DIV_MIPS, MULT_MIPS, OR_MIPS
typedef enum {  R0, // zero register
                AT, // reserved for pseudo instructions
                V0, V1, // return registers
                A0, A1, A2, A3, //arguement registers
                T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, // temporary registers
                S0, S1, S2, S3, S4, S5, S6, S7, S8,  // saved registers
                K0, K1, // kernal registers. do not use.
                GP, // global area pointer
                SP, // stack pointer
                RA, // Return Address register
                R_TYPE, I_TYPE, J_TYPE, TARGET, //instruction types
                ADD, ADDI, ADDIU, ADDU, // OP codes
                AND_MIPS, ANDI, BEQ,
                BNE,
                DIV_MIPS,
                DIVU,
                J,
                JAL,
                JR,
                LBU,
                LHU,
                LUI,
                LW,
                MFHI,
                MFLO,
                MFC0,
                MULT_MIPS,
                MULTU,
                NOR,
                XOR,
                OR_MIPS,
                ORI,
                SB,
                SH,
                SEQ,
                SLT, SLE,
                SLTI,
                SLTIU,
                SLTU,
                SLL,
                SRL,
                SRA,
                SUB,
                SUBU,
                SW,
                BLT,
                BGT,
                BLE,
                NEG,
                NOT_MIPS,
                BGE,
                LI,
                LA,
                MOVE,
                SGE,
                SGT,
                SYSCALL,

                // R0, // zero register
                // AT, // reserved for pseudo instructions
                // V0, V1, // return registers
                // A0, A1, A2, A3, //arguement registers
                // T0, T1, T2, T3, T4, T5, T6, T7,  // temporary registers
                // S0, S1, S2, S3, S4, S5, S6, S7,  // saved registers
                // T8, T9, // more temporary registers
                // K0, K1, // kernal registers. do not use.
                // GP, // global area pointer
                // SP, // stack pointer
                // S8, // saved register again
                // RA // Return Address register
                NEWLINE
             } mipsT;


// const char *mipsArray[] = {   "$r0", // zero register
//                               "$at", // reserved for pseudo instructions
//                               "$v0", "$v1", // return registers
//                               "$a0", "$a1", "$a2", "$a3", //arguement registers
//                               "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",  // temporary registers
//                               "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",  // saved registers
//                               "$t8", "$t9", // more temporary registers
//                               "$k0", "$k1", // kernal registers. do not use.
//                               "$gp", // global area pointer
//                               "$sp", // stack pointer
//                               "$s8", // saved register again
//                               "$ra" // Return Address register
//                               "R_TYPE", "I_TYPE", "J_TYPE", //instruction types
//                               "add",  // OP codes
//                               "addi",
//                               "addiu",
//                               "addu",
//                               "and",
//                               "andi",
//                               "beq",
//                               "bne",
//                               "div",
//                               "divu",
//                               "j",
//                               "jal",
//                               "jr",
//                               "lbu",
//                               "lhu",
//                               "lui",
//                               "lw",
//                               "mfhi",
//                               "mflo",
//                               "mfc0",
//                               "mult",
//                               "multu",
//                               "nor",
//                               "xor",
//                               "or",
//                               "ori",
//                               "sb",
//                               "sh",
//                               "slt",
//                               "slti",
//                               "sltiu",
//                               "sltu",
//                               "sll",
//                               "srl",
//                               "sra",
//                               "sub",
//                               "subu",
//                               "sw",
//                               "blt",
//                               "bgt",
//                               "ble",
//                               "neg",
//                               "not",
//                               "bge",
//                               "li",
//                               "la",
//                               "move",
//                               "sge",
//                               "sgt",
//                               // "$r0", // zero register
//                               // "$at", // reserved for pseudo instructions
//                               // "$v0", "$v1", // return registers
//                               // "$a0", "$a1", "$a2", "$a3", //arguement registers
//                               // "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",  // temporary registers
//                               // "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",  // saved registers
//                               // "$t8", "$t9", // more temporary registers
//                               // "$k0", "$k1", // kernal registers. do not use.
//                               // "$gp", // global area pointer
//                               // "$sp", // stack pointer
//                               // "$s8", // saved register again
//                               // "$ra" // Return Address register
//                               "pr_int", "pr_str", "_newline_"
//                           } ;

#endif


// #ifndef _MIPS
// #define _MIPS
// typedef enum {  R0, // zero register
//                 AT, // reserved for pseudo instructions
//                 V0, V1, // return registers
//                 A0, A1, A2, A3, //arguement registers
//                 T0, T1, T2, T3, T4, T5, T6, T7,  // temporary registers
//                 S0, S1, S2, S3, S4, S5, S6, S7,  // saved registers
//                 T8, T9, // more temporary registers
//                 K0, K1, // kernal registers. do not use.
//                 GP, // global area pointer
//                 SP, // stack pointer
//                 S8, // saved register again
//                 RA, // Return Address register
//                 R_TYPE, I_TYPE, J_TYPE, //instruction types
//                 ADD, ADDI, ADDIU, ADDU, // OP codes
//                 AND, ANDI, BEQ,
//                 BNE,
//                 DIV,
//                 DIVU,
//                 J,
//                 JAL,
//                 JR,
//                 LBU,
//                 LHU,
//                 LUI,
//                 LW,
//                 MFHI,
//                 MFLO,
//                 MFC0,
//                 MULT,
//                 MULTU,
//                 NOR,
//                 XOR,
//                 OR,
//                 ORI,
//                 SB,
//                 SH,
//                 SLT,
//                 SLTI,
//                 SLTIU,
//                 SLTU,
//                 SLL,
//                 SRL,
//                 SRA,
//                 SUB,
//                 SUBU,
//                 SW,
//                 // R0, // zero register
//                 // AT, // reserved for pseudo instructions
//                 // V0, V1, // return registers
//                 // A0, A1, A2, A3, //arguement registers
//                 // T0, T1, T2, T3, T4, T5, T6, T7,  // temporary registers
//                 // S0, S1, S2, S3, S4, S5, S6, S7,  // saved registers
//                 // T8, T9, // more temporary registers
//                 // K0, K1, // kernal registers. do not use.
//                 // GP, // global area pointer
//                 // SP, // stack pointer
//                 // S8, // saved register again
//                 // RA // Return Address register
//                 PR_INT, PR_STR, NEWLINE
//              } mipsT;
// #endif
