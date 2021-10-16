#ifndef SIM_H
#define SIM_H

#define NUM_OF_REGISTER 8 
#define MEM_MAX_SIZE 65536

static int Registers[16] = { 0 }; // holds the register state at any given moment.
static int Memory[MEM_MAX_SIZE] = { 0 }; // holds the memory state at any given moment.
static int Is_Running = 1;
static int PC = 0;

typedef struct 
{
    int opcode;
    int dst;
    int src_0;
    int src_1;
    long int imm;
} instruction_t;


#endif
