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
    if (op == 0) {
        controls->RegDst = 1;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 7;
        controls->MemWrite = 0;
        controls->ALUSrc = 0;
        controls->RegWrite = 1;
    } else if (op == 8) {
        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 0;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
    } else if (op == 35) {
        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 1;
        controls->MemtoReg = 1;
        controls->ALUOp = 0;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
    } else if (op == 43) {
        controls->RegDst = 2;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 2;
        controls->ALUOp = 0;
        controls->MemWrite = 1;
        controls->ALUSrc = 1;
        controls->RegWrite = 0;
    } else if (op == 15) {
        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 6;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
    } else if (op == 4) {
        controls->RegDst = 2;
        controls->Jump = 0;
        controls->Branch = 1;
        controls->MemRead = 0;
        controls->MemtoReg = 2;
        controls->ALUOp = 1;
        controls->MemWrite = 0;
        controls->ALUSrc = 0;
        controls->RegWrite = 0;
    } else if (op == 10) {
        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 2;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
    } else if (op == 11) {
        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 3;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
    } else if (op == 2) {
        controls->RegDst = 2;
        controls->Jump = 1;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 2;
        controls->ALUOp = 0;
        controls->MemWrite = 0;
        controls->ALUSrc = 2;
        controls->RegWrite = 0;
    } else {
        return 1;
    }

    return 0;
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
    unsigned input2;
    char ALUControl;

    if (ALUSrc == 1) {
        input2 = extended_value;
    } else {
        input2 = data2;
    }

    if (ALUOp == 7) {
        if (funct == 32) {
            ALUControl = 0;
        } else if (funct == 34) {
            ALUControl = 1;
        } else if (funct == 36) {
            ALUControl = 4;
        } else if (funct == 37) {
            ALUControl = 5;
        } else if (funct == 42) {
            ALUControl = 2;
        } else if (funct == 43) {
            ALUControl = 3;
        } else {
            return 1;
        }
    } else {
        ALUControl = ALUOp;
    }

    ALU(data1, input2, ALUControl, ALUresult, Zero);

    return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
    if (MemRead == 1 || MemWrite == 1) {
        if (ALUresult % 4 != 0) {
            return 1;
        }

        if (ALUresult > 0xFFFF) {
            return 1;
        }
    }

    if (MemRead == 1) {
        *memdata  = Mem[ALUresult >> 2];
    }

    if (MemWrite == 1) {
        Mem[ALUresult >> 2] = data2;
    }

    return 0;
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
    unsigned write_register;
    unsigned write_data;

    if (RegWrite == 0) {
        return;
    }

    if (RegDst == 1) {
        write_register = r3;
    } else {
        write_register = r2;
    }

    if (MemtoReg == 1) {
        write_data = memdata;
    } else {
        write_data = ALUresult;
    }

    Reg[write_register] = write_data;
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
    unsigned newPC;
    newPC = *PC + 4;

    if (Branch == 1 && Zero == 1) {
        newPC = newPC + (extended_value << 2);
    }

    if (Jump == 1) {
        newPC = (newPC & 0xF0000000) | (jsec << 2);
    }

    *PC = newPC;
}

