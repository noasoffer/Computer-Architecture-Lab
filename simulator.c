#define _CRT_SECURE_NO_WARNINGS

#include "simulator.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>


long int inst;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

#define SAVES_PC 7

//Functionality: function adds the arguments in register rs and rt, saves it to rd
void add(int dst, int src_0, int src_1) {
	Registers[dst] =
		Registers[src_0] + Registers[src_1];
}

//Functionality: function subtracts the arguments in register rt from rs, saves it to dst
void sub(int dst, int src_0, int src_1) {
	Registers[dst] =
		Registers[src_0] - Registers[src_1];
}

void lsf(int dst, int src_0, int src_1) {
	Registers[dst] = Registers[src_0] << Registers[src_1];
}

//TODO check!
void rsf(int dst, int src_0, int src_1) {
	int size = sizeof(int) * 8; // usually sizeof(int) is 4 bytes (32 bits)
	Registers[dst] = (Registers[src_0] >> Registers[src_1]) & ~(((0x1 << size) >> Registers[src_1]) << 1);
}


//Functionality: rs bitwise-and with rt, store in dst
void and(int dst, int src_0, int src_1) {
	Registers[dst] =
		Registers[src_0] & Registers[src_1];
}


//Functionality: rs bitwise-or with rt, store in dst
void or (int dst, int src_0, int src_1) {
	Registers[dst] =
		Registers[src_0] | Registers[src_1];
}

//Functionality: rs bitwise-xor with rt, store in dst
void xor (int dst, int src_0, int src_1) {
	Registers[dst] =
		Registers[src_0] ^ Registers[src_1];
}

void lhi(int dst, int src_0, int src_1) {
	Registers[dst] = Registers[dst] & 0x0000ffff;
	int imm_top = Registers[1] << 0x10;
	Registers[dst] = Registers[dst] | imm_top;
}

/*Load Word = take sum of registers rs,rt contents, and use it as index in dmem array's data, put it in rd's content*/
void ld(int dst, int src_0, int src_1) {
	Registers[dst] = Memory[Registers[src_1]];
}

/*Store Word = take sum of registers rs,rt contents, and use it as index in dmem array's data, put rd's content in this index*/
void st(int dst, int src_0, int src_1) {
	Memory[Registers[src_1]] = Registers[src_0];
}

/*Brench if Less Than - if content of rs is smaller than the content of rt, jump the PC to rd's content (last 10 bits)*/
void jlt(int dst, int src_0, int src_1) {
	if (Registers[src_0] < Registers[src_1]) {
		Registers[SAVES_PC] = PC;
		//TODO understand this
		//PC = Registers[1] && MEM_MAX_SIZE - 1;
		PC = Registers[1] - 1;
	}
}

/*Brench if Less Than - if content of rs is smaller than the content of rt, jump the PC to rd's content (last 10 bits)*/
void jle(int dst, int src_0, int src_1) {
	if (Registers[src_0] <= Registers[src_1]) {
		Registers[SAVES_PC] = PC;
		//TODO understand this
		//PC = Registers[1] && MEM_MAX_SIZE - 1;
		PC = Registers[1] - 1;
	}
}

/*Brench if Equal - if content of rs, rt registers is the same, jump the PC to rd's content (last 10 bits)*/
void jeq(int dst, int src_0, int src_1) {
	if (Registers[src_0] == Registers[src_1]) {
		Registers[SAVES_PC] = PC;
		//TODO understand this
		//PC = Registers[1] && MEM_MAX_SIZE - 1;
		PC = Registers[1] -1;
	}
}

/*Brench if Not Equal - if content of rs, rt registers is different, jump the PC to rd's content (last 10 bits)*/
void jne(int dst, int src_0, int src_1) {
	if (!(Registers[src_0] == Registers[src_1])) {
		Registers[SAVES_PC] = PC;
		//TODO understand this
		//PC = Registers[1] && MEM_MAX_SIZE - 1;
		PC = Registers[1] - 1;
	}
}


/*Jump And Link - set the $ra register to the next PC (already there), and jump the PC to rd's content (last 10 bits)*/
void jin(int dst, int src_0, int src_1) {
	Registers[SAVES_PC] = PC;
	//TODO understand this
	//PC = Registers[1] && MEM_MAX_SIZE - 1;
	PC = Registers[1] - 1;
}

void hlt(int dst, int src_0, int src_1) {
	Is_Running = 0;
}



void execute_instruction(instruction_t* instruction)
{
	
	if (instruction->opcode == 0) {
		add(instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "ADD";
	}
	if (instruction->opcode == 1) {
		sub(instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "SUB";
	}
	if (instruction->opcode == 2) {
		lsf(instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "LSF";
	}
	if (instruction->opcode == 3) {
		rsf(instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "RSF";
	}
	if (instruction->opcode == 4) {
		and (instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "AND";
	}
	if (instruction->opcode == 5) {
		or (instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "OR";
	}
	if (instruction->opcode == 6) {
		xor (instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "XOR";
	}
	if (instruction->opcode == 7) {
		lhi(instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "LHI";
	}
	if (instruction->opcode == 8) {
		ld(instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "LD";
	}
	if (instruction->opcode == 9) {
		st(instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "ST";
	}
	if (instruction->opcode == 16) {
		jlt(instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "JLT";
	}
	if (instruction->opcode == 17) {
		jle(instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "JLE";
	}
	if (instruction->opcode == 18) {
		jeq(instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "JEQ";
	}
	if (instruction->opcode == 19) {
		jne(instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "JNE";
	}
	if (instruction->opcode == 20) {
		jin(instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "JIN";
	}
	if (instruction->opcode == 24) {
		hlt(instruction->dst, instruction->src_0, instruction->src_1);
		instruction->code = "HLT";
	}
	

}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

/*
* functionality: copy the content of the input file to Memory array.
* this allows us to read the given file only one time, and spare the run time.
*/
void memincopy(FILE* memin) {
	int line = 0;
	int temp = 0;
	while (temp != -1) {
		temp = fscanf(memin, "%08x", &(Memory[line]));
		line++;
	}
}

void set_code(instruction_t* instruction) {
	int code = instruction->opcode;
	if (code == 0) {
		instruction->code = "ADD";
	}
	if (code == 1) {
		instruction->code = "SUB";
	}
	if (code == 2) {
		instruction->code = "LSF";
	}
	if (code == 3) {
		instruction->code = "RSF";
	}
	if (code == 4) {
		instruction->code = "AND";
	}
	if (code == 5) {
		instruction->code = "OR";
	}
	if (code == 6) {
		instruction->code = "XOR";
	}
	if (code == 7) {
		instruction->code = "LHI";
	}
	if (code == 8) {
		instruction->code = "LD";
	}
	if (code == 9) {
		instruction->code = "ST";
	}
	if (code == 16) {
		instruction->code = "JLT";
	}
	if (code == 17) {
		instruction->code = "JLE";
	}
	if (code == 18) {
		instruction->code = "JEQ";
	}
	if (code == 19) {
		instruction->code = "JNE";
	}
	if (code == 20) {
		instruction->code = "JIN";
	}
	if (code == 24) {
		instruction->code = "HLT";
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
	instruction->src_1 = (inst & 0x00070000) >> 0x10;
	instruction->imm = ((inst & 0x0000ffff) << 16) >> 16;
	instruction->inst = Memory[PC];//TODO check this
	/**if ((instruction->src_0 == 1) || (instruction->src_1 == 1)) {
		Registers[1] = instruction->imm;
	}*/
	Registers[1] = instruction->imm;

}


/*
* functionality: Writes the contents of the memory array to sram file in the desired format.
*/
void write_to_sram(FILE* sram, FILE* trace) {
	for (int i = 0; i < MEM_MAX_SIZE; i++) {
		fprintf(sram, "%08x\n", Memory[i]);
	}
}

void write_to_trace(FILE* trace, instruction_t* instruction) {
	fprintf(trace, "--- instruction %i (%04x) @ PC %i (%04x) -----------------------------------------------------------\n", Instrctions_Counter, Instrctions_Counter, PC, PC);
	fprintf(trace, "pc = %04i, inst = %08x, opcode = %i (%s), dst = %i, src0 = %i, src1 = %i, immediate = %08x\n", PC, instruction->inst, instruction->opcode, instruction->code, instruction->dst, instruction->src_0, instruction->src_1, instruction->imm);
	fprintf(trace, "r[0] = 00000000 r[1] = %08x r[2] = %08x r[3] = %08x \n", Registers[1], Registers[2], Registers[3]);
	fprintf(trace, "r[4] = %08x r[5] = %08x r[6] = %08x r[7] = %08x \n\n", Registers[4], Registers[5], Registers[6], Registers[7]);
	if (instruction->opcode >= 0 && instruction->opcode <= 7) {
		fprintf(trace, ">>>> EXEC: R[%i] = %i %s %i <<<<\n\n", instruction->dst, Registers[instruction->src_0], instruction->code, Registers[instruction->src_1]);
	}
	if (instruction->opcode == 8) {
		fprintf(trace, ">>>> EXEC: R[%i] = MEM[%i] = %08i <<<<\n\n", instruction->dst, Registers[instruction->src_1], instruction->imm);
	}
	if (instruction->opcode == 9) {
		fprintf(trace, ">>>> EXEC: MEM[%i] = R[%i] = %08x <<<<\n\n", Registers[instruction->src_1], instruction->src_0, Registers[instruction->src_0]);
	}
	if (instruction->opcode >= 16 && instruction->opcode <= 20) {
		fprintf(trace, ">>>> EXEC: %s %d, %d, %d <<<<\n\n", instruction->code, Registers[instruction->src_0], Registers[instruction->src_1], PC + 1);
	}
	if (instruction->opcode == 24) {
		fprintf(trace, ">>>> EXEC: HALT at PC %04x<<<<\n", PC);
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
	if (!trace || !sram || !memin) {
		fprintf(stderr, "Unable to open file \n");
		exit(1);
	}
	memincopy(memin);


	while (Is_Running)
	{
		instruction_t instruction;
		translate_line(&instruction);
		set_code(&instruction);
		write_to_trace(trace, &instruction);
		execute_instruction(&instruction);
		PC += 1;
		Instrctions_Counter += 1;
	}
	write_to_sram(sram);
	exit(0);
}
