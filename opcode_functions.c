#include "sim.h"
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

void lsf(int dst, int src_0, int src_1){
    Registers[dst] = Registers[src_0] << Registers[src_1];
}

//TODO check!
void rsf(int dst, int src_0, int src_1){
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

void lhi (int dst, int src_0, int src_1){
    Registers[dst] = Registers[dst] & 0x0000ffff;
	int imm_top = Registers[1] << 0x10;
	Registers[dst] = Registers[dst] | imm_top;
}

/*Load Word = take sum of registers rs,rt contents, and use it as index in dmem array's data, put it in rd's content*/
void ld (int dst, int src_0, int src_1) {
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
        PC = Registers[1] && MEM_MAX_SIZE -1;
	}
}

/*Brench if Less Than - if content of rs is smaller than the content of rt, jump the PC to rd's content (last 10 bits)*/
void jle(int dst, int src_0, int src_1) {
	if (Registers[src_0] <= Registers[src_1]) {
		Registers[SAVES_PC] = PC;
        //TODO understand this
        PC = Registers[1] && MEM_MAX_SIZE -1;
	}
}

/*Brench if Equal - if content of rs, rt registers is the same, jump the PC to rd's content (last 10 bits)*/
void jeq(int dst, int src_0, int src_1) {
	if (Registers[src_0] == Registers[src_1]) {
		Registers[SAVES_PC] = PC;
        //TODO understand this
        PC = Registers[1] && MEM_MAX_SIZE -1;
	}
}

/*Brench if Not Equal - if content of rs, rt registers is different, jump the PC to rd's content (last 10 bits)*/
void jne(int dst, int src_0, int src_1) {
	if (!(Registers[src_0] == Registers[src_1])) {
		Registers[SAVES_PC] = PC;
        //TODO understand this
        PC = Registers[1] && MEM_MAX_SIZE -1;
	}
}


/*Jump And Link - set the $ra register to the next PC (already there), and jump the PC to rd's content (last 10 bits)*/
void jin(int dst, int src_0, int src_1) {
	Registers[SAVES_PC] = PC;
    //TODO understand this
    PC = Registers[1] && MEM_MAX_SIZE -1;
}

void hlt(int dst, int src_0, int src_1){
    Is_Running = 0;
}



void execute_instruction(instruction_t* instruction)
{
    if ((instruction->src_0 == 1) ||  (instruction->src_0 == 1)){
        Registers[1] = instruction->imm;
    }
    if (instruction->opcode == 0){
        add(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 1){
        sub(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 2){
        lsf(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 3){
        rsf(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 4){
        and(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 5){
        or(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 6){
        xor(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 7){
        lhi(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 8){
        ld(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 9){
        st(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 16){
        jlt(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 17){
        jle(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 18){
        jeq(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 19){
        jne(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 20){
        jin(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    if (instruction->opcode == 24){
        hlt(instruction->dst, instruction->src_0, instruction->src_1);
        PC += 1;
    }
    
}
