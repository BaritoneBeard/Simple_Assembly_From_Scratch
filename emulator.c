#include <stdio.h>


unsigned char memory[256];
unsigned char  A=0,B=0,C=0,D=0;
//int PC=0;
unsigned char PC=0;
int halted=0;

void doAnInstruction()
{
	//fetch: get instruction from memory
	unsigned char instruction = memory[PC];
	//PC=(PC+1) & 0xff;
	PC = PC+1;		//goto next instruction

	//decode
	unsigned char opcode4 = instruction >> 4;
	unsigned char opcode2 = instruction >> 6;
	unsigned char rs = instruction & 0b00000011;
	unsigned char rd = (instruction >> 2) & 0b00000011;
	unsigned char immh = (instruction >> 4) & 0b00000011;
	unsigned char imml = instruction & 0b00000011;
	unsigned char imm = (immh<<2) + imml; //Also (immh<<2) | imml works too

	unsigned char registerrd;
	if(rd == 0) registerrd = A;
	if(rd == 1) registerrd = B;
	if(rd == 2) registerrd = C;
	if(rd == 3) registerrd = D;
	unsigned char registerrs;
	if(rs==0) registerrs = A;
	if(rs==1) registerrs = B;
	if(rs==2) registerrs = C;
	if(rs==3) registerrs = D;


	if(instruction==0b00000001)	//HALT
	{
		halted = 1;
		printf("halt\n");
	}
	else if(opcode2==0b11)	//SLI (MOV)
	{
		printf("sli\n");
		registerrd = registerrd<<4;
		registerrd = registerrd + imm;

		if(rd==0) A=registerrd;
		if(rd==1) B=registerrd;
		if(rd==2) C=registerrd;
		if(rd==3) D=registerrd;

	}
	else if(opcode4==0b0011)	//STORE
	{
		printf("store %x and %x\n",registerrs, registerrd);
		//registerrs = registerrd;
		memory[registerrs] = registerrd;

		if(rd==0) A=registerrd;
		if(rd==1) B=registerrd;
		if(rd==2) C=registerrd;
		if(rd==3) D=registerrd;
	}
	else if(opcode4==0b0010)	//LOAD
	{
		printf("load\n %x and %x\n",registerrd, registerrs);	
		registerrd =memory[registerrs];

		if(rd==0) A=registerrd;
		if(rd==1) B=registerrd;
		if(rd==2) C=registerrd;
		if(rd==3) D=registerrd;
	}
	else if(opcode4==0b0111)	//ADD
	{
		printf("add %x + %x = ",registerrd,registerrs);
		registerrd = registerrd + registerrs;
		printf("%x\n",registerrd);
		if(rd==0) A=registerrd;
		if(rd==1) B=registerrd;
		if(rd==2) C=registerrd;
		if(rd==3) D=registerrd;
	}
	else if(opcode4==0b0001)	//SUB
	{
		printf("sub %x -  %x =",registerrd,registerrs);
		//registerrd = registerrd<<4;
		registerrd = registerrd - registerrs;
		printf("%x\n",registerrd);
		if(rd==0) A=registerrd;
		if(rd==1) B=registerrd;
		if(rd==2) C=registerrd;
		if(rd==3) D=registerrd;
	}
	else if(opcode4==0b0100 && imml == 01)	//SKIPNZ (non-zero)
	{
		printf("skipnz\n");
		if(registerrd != 0) PC = PC+1;
		if(rd==0) A=registerrd;
		if(rd==1) B=registerrd;
		if(rd==2) C=registerrd;
		if(rd==3) D=registerrd;
	}
	else if(opcode4==0b0100 && imml == 00)	//SKIP
	{
		printf("skip\n");
		if(registerrd == 0) PC = PC+1;
		if(rd==0) A=registerrd;
		if(rd==1) B=registerrd;
		if(rd==2) C=registerrd;
		if(rd==3) D=registerrd;
	}
	else if(opcode4==0b0101)	//JALR (jmp)
	{
		printf("jalr\n");
		registerrs = PC+1;
		PC = registerrd;
		if(rd==0) A=registerrd;
		if(rd==1) B=registerrd;
		if(rd==2) C=registerrd;
		if(rd==3) D=registerrd;
	}
	else
	{
		printf("ERROR: UNKOWN INSTRUCTION!\n");
	}
	printf("PC=%x,A=%x,B=%x,C=%x,D=%x\n",PC,A,B,C,D);	//DEBUG
}

int main()
{
	int i;
	//test program

/*	memory[0]=0xff;	//sli D,f
	memory[1]=0xfe;	//sli D,e
	memory[2]=0x2b;	//load C,(D)
	memory[3]=0xcc;	//sli D,0
	memory[4]=0xcd;	//sli D,1
	memory[5]=0x1b;	//sub C,D
	memory[6]=0xff;	//sli D,f
	memory[7]=0xfe;	//sli D,e
	memory[8]=0x3b;	//store C,(D)
	memory[9]=0x01;	//halt
*/	

	//Fibbonacci program
	unsigned char program[0x19] = {0xff,0xfc,0x23,0xff,0xfd,0x27,0xff,0xfe,0x2b,0x1f,0x1a,0x78,0x79,0x10,0x71,0x15,0x76,0xcc,0xee,0xc8,0xf9,0x18,0x48,0x5f,0x01};


	for(i = 0; i<0x19;i++) //for(0; < length of "program"; ++)
	{
		memory[i] = program[i];
		//printf("%x\n",memory[i]);
	}


	//input value
	memory[0xfd] = 1;	//input is 1 for B
	while(halted==0)
	{
		//printf("%x   ",memory[PC]);
		doAnInstruction();
	}

	//printf("memory of fe is no %x\n",memory[0xfe]);
	//printf("memory of ff is no %x\n",memory[0xff]);
	printf("value of A is %x\n",A);
	return 0;
}
