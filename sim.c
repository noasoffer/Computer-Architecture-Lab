#define _CRT_SECURE_NO_WARNINGS

#include "sim.h"
#include "opcode_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>


long int inst;

/*
* functionality: copy the content of the input file to Memory array.
* this allows us to read the given file only one time, and spare the run time.
*/
void memincopy(FILE* memin ) {
	int line = 0;
	int temp = 0;
	while (temp != -1) {
		temp = fscanf(memin, "%08x", &(Memory[line]));
		line++;
	}
}

/*
* functionality: traslate the instraction (saved in Memory) and saperat value of the opcode,  dst register, src 0 reister, src 1 register and imm.
*/
void translate_line(instruction_t* instruction) {
	inst = Memory[PC];
    instruction->opcode = (inst & 0x3E000000) >> 0x19;
	instruction->dst = (inst & 0x01c00000) >> 0x16;
	instruction->src_0 = (inst & 0x00380000) >> 0x13;
	instruction->src_1 =  (inst & 0x00070000) >> 0x10;
	instruction->imm =  ((inst & 0x0000ffff) << 16) >> 16;
}

//TODO 
void write_to_trace();

/*
* functionality: Writes the contents of the memory array to sram file in the desired format.
*/
void write_to_sram( FILE* sram) {
	for (int i = 0; i < MEM_MAX_SIZE; i++) {
		fprintf(sram, "%08X\n", Memory[i]);
	}
}


int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Worng number of args\n");
		exit(1);
	}
	FILE* memin = fopen(argv[1], "r"); /*Opening all the input files*/
	FILE* sram = fopen("sram_out.txt", "w");
	FILE* trace = fopen("trace.txt", "w");
	if ( !trace || !sram || !memin){
		fprintf(stderr, "Unable to open file \n");
	    exit(1);
    }
    memincopy(memin);


    while(Is_Running)
    {
        instruction_t instruction;
        translate_line (& instruction);
        write_to_trace();
        execute_instruction(& instruction);
    }
    write_to_sram(sram);
    exit(0);
}
