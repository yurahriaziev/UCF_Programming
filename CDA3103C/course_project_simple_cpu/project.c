/*        CDA3103C - Course Project
This program is written by: Yurii Hriaziev */

#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    if (ALUControl == 0) {
        *ALUresult = A + B;
    } else if (ALUControl == 1) {
        *ALUresult = A - B;
    } else if (ALUControl == 2) {
        if ((int)A < (int)B) {
            *ALUresult = 1;
        } else {
            *ALUresult = 0;
        }
    } else if (ALUControl == 3) {
        if (A < B) {
            *ALUresult = 1;
        } else {
            *ALUresult = 0;
        }
    } else if (ALUControl == 4) {
        *ALUresult = A & B;
    } else if (ALUControl == 5) {
        *ALUresult = A | B;
    } else if (ALUControl == 6) {
        *ALUresult = B << 16;
    } else if (ALUControl == 7) {
        *ALUresult = ~A;
    }

    if (*ALUresult == 0) {
        *Zero = 1;
    } else {
        *Zero = 0;
    }
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    if (PC % 4 != 0) {
        return 1;
    }

    if (PC > 0xFFFF) {
        return 1;
    }

    *instruction = Mem[PC >> 2];
    return 0;
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    *op = instruction >> 26;

    *r1 = instruction >> 21;
    *r1 = *r1 & 0x1F;

    *r2 = instruction >> 16;
    *r2 = *r2 & 0x1F;

    *r3 = instruction >> 11;
    *r3 = *r3 & 0x1F;

    *funct = instruction & 0x3F;
    *offset = instruction & 0xFFFF;
    *jsec = instruction & 0x03FFFFFF;
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    *data1 = Reg[r1];
    *data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    if (offset >= 0x8000) {
        *extended_value = offset | 0xFFFF0000;
    } else {
        *extended_value = offset;
    }
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

