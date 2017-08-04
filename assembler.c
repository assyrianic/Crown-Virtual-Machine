/* fwrite example : write buffer */
#include <stdio.h>
#include <stdint.h>

#define INSTR_SET	\
	X(halt) \
	X(pushl) X(pushs) X(pushb) X(pushsp) X(puship) X(pushbp) \
	X(popl) X(pops) X(popb) X(popsp) X(popip) X(popbp) \
	X(wrtl) X(wrts) X(wrtb) \
	X(storel) X(stores) X(storeb) \
	X(storela) X(storesa) X(storeba) \
	X(storespl) X(storesps) X(storespb) \
	X(loadl) X(loads) X(loadb) \
	X(loadla) X(loadsa) X(loadba) \
	X(loadspl) X(loadsps) X(loadspb) \
	X(copyl) X(copys) X(copyb) \
	X(addl) X(uaddl) X(addf) \
	X(subl) X(usubl) X(subf) \
	X(mull) X(umull) X(mulf) \
	X(divl) X(udivl) X(divf) \
	X(modl) X(umodl) \
	X(andl) X(orl) X(xorl) \
	X(notl) X(shll) X(shrl) \
	X(incl) X(incf) X(decl) X(decf) X(negl) X(negf) \
	X(ltl) X(ultl) X(ltf) \
	X(gtl) X(ugtl) X(gtf) \
	X(cmpl) X(ucmpl) X(compf) \
	X(leql) X(uleql) X(leqf) \
	X(geql) X(ugeql) X(geqf) \
	X(jmp) X(jzl) X(jnzl) \
	X(call) X(calls) X(calla) X(ret) X(reset) \
	X(callnat) \
	X(nop) \

#define X(x) x,
enum InstrSet { INSTR_SET };
#undef X
typedef uint8_t		bytecode[];

int main ()
{
	FILE *pFile = NULL;
	bytecode endian_test1 = {
		0xDE, 0xC0, 7,0,0,0,
		nop,
		//pushl, 255, 1, 0, 0x0,
		//pushs, 0xDD, 0xDD,
		//pushb, 0xAA,
		//pushb, 0xFF,
		wrtl,	0,0,0,0,	0xA,0xB,0xC,0xD,
		pushl,	0xA,0xB,0xC,0xD,
		halt
	};
	bytecode float_test = {
		0xDE, 0xC0, 6,0,0,0,
		//jmp, 17,0,0,0,
		// -16776961
		//pushl, 255,0,0,255,
		//pushl, 1,0,0,0,
		// -855637761
		// 10.f in 4 bytes form
		pushl,	65,32,0,0,
		// 2.f in 4 bytes form
		pushl,	64,0,0,0,
		addf,	// 12.f
		//leqf,
		halt
	};
	
	// Fibonnaci sequence to test performance!
	/*	int fib(int n)
		{
			int a=0, b=1;
			while (n-- > 1) {
				int t = a;
				a = b;
				b += t;
			}
			return b;
		}
	*/
	bytecode fibonacci = {
		0xDE, 0xC0, 6,0,0,0,
		nop, // calc fibonnaci number
		wrtl,	0,0,0,0,	0,0,0,7,	// write n to address 0, remember that memory is little endian!
		call,	0,0,0,22,
		halt,
		// a = 0;
		wrtl,	0,0,0,4,	0,0,0,0,		// 16
		// b = 1;
		wrtl,	0,0,0,8,	0,0,0,1,		// 25
		// while( n-- > 1 ) {
		loadl,	0,0,0,0,		// load param n		// 34
		pushl,	0,0,0,1,		// push 1
		gtl,
		loadl,	0,0,0,0,		// load param n
		decl,				// decrement address 0
		storel,	0,0,0,0,	// store decrement result to memory address
		jzl,	0,0,0,109,		// jmp to storing b and returning.
		popl,
		// int t = a;
		loadl,	0,0,0,4,		// load a's value.
		storel,	0,0,0,12,	// store a's value into another address as 't'
		// a = b;
		loadl,	0,0,0,8,		// load b.
		storel,	0,0,0,4,	// store b's value into a's address.
		// b += t;
		loadl,	0,0,0,12,	// load t.
		loadl,	0,0,0,8,		// load b.
		uaddl,				// add b and t
		storel,	0,0,0,8,	// store addition value to b's address.
		jmp,	0,0,0,40,		// jmp back to start of loop.	// 98
		// }
		ret		// b has been fully 'mathemized' and is stored into memory for reuse.
	};
	
	bytecode hello_world = {
		0xDE, 0xC0, 6,0,0,0,
		nop,
		wrtb,	0,0,0,0,	100,	// d
		wrtb,	0,0,0,1,	108,	// l
		wrtb,	0,0,0,2,	114,	// r
		wrtb,	0,0,0,3,	111,	// o
		wrtb,	0,0,0,4,	87,		// W
		wrtb,	0,0,0,5,	32,		// space
		wrtb,	0,0,0,6,	111,	// o
		wrtb,	0,0,0,7,	108,	// l
		wrtb,	0,0,0,8,	108,	// l
		wrtb,	0,0,0,9,	101,	// e
		wrtb,	0,0,0,10,	72,		// H
		halt,
	};
	
	bytecode global_pointers = {
		0xDE, 0xC0, 7,0,0,0,
		nop,
		// The way you wuold store to a pointer would be something like...
		// pushl <value to store>
		// loadl <ptr address>
		// storela
		
		// push 170 to tos.
		pushl,	0,0,0,0xAA,
		// store 170 to address 255 as variable 'i'
		// int i = 170;
		storel,	0,0,0,0xff,
		
		// the way you would load from a pointer would be something like:
		// loadl <ptr address>
		// loadla
		
		// load address of 'i'
		// int *p = &i;
		// *p = 26;		// i == 26;
		pushl,	0,0,0,0x1a,
		pushl, 0,0,0,0xff,
		storela, // pops 4 byte address, then pops 4 byte data into memory address.
		halt
	};
	
	// example of locally (stack-allocated) made pointers and manipulating them.
	bytecode local_pointers = {
		0xDE, 0xC0, 7,0,0,0,
		nop,
		// int i = 170;
		// i's address is 4 (tos address, not beginning data address)
		pushl,	0,0,0,0xaa,
		
		// int *p = &i;
		pushl,	0,0,0,0xff,	// going to overwrite &i with 255.
		pushl,	0,0,0,4, storespl,	// stack index of i aka &i
		halt
	};
	
	// void func(int a, int b) { return a+b; }
	// func declarations are done by cdecl standard.
	bytecode test_func_call = {
		0xDE, 0xC0, 6,0,0,0,	// 0
		pushl,	0,0,1,244,	// 6	push b
		pushl,	0,0,0,2,	//		push a
		call,	0,0,0,24,	// 16		func(int a, int b) ==> b=500 and a=2
		popl,popl,	// clean up args a and b from stack
		halt,			// 11
		pushl,	0,0,0,8, loadspl,	// load a to TOS
		pushl,	0,0,0,4, loadspl,	// load b to TOS
		addl,	// return a+b;
		ret,	// 22
	};
	
	bytecode all_opcodes_test = {
		0xDE, 0xC0, 6,0,0,0,	// 0
		// push + pop tests
		pushl,	0xa,0xb,0xc,0xd, popl,
		pushs,	0xff,0xaa, pops,
		pushb,	0xfa, popb,
		pushsp,	popsp,
		//puship,	popip,	// it works, trust me lol
		pushbp, popbp,
		
		// write to memory tests
		wrtl,	0,0,0,0,	0xa,0xb,0xc,0xd,	// direct write to address 0x0
		wrts,	0,0,0,4,	0xff,0xaa,			// direct write to address 0x4
		wrtb,	0,0,0,6,	0xfa,				// direct write to address 0x6
		
		// store + load tests
		halt,
	};
	
	pFile = fopen("./endian_test1.tagha", "wb");
	if( pFile ) {
		fwrite(endian_test1, sizeof(uint8_t), sizeof(endian_test1), pFile);
		fclose(pFile);
	}
	pFile = fopen("./float_test.tagha", "wb");
	if( pFile ) {
		fwrite(float_test, sizeof(uint8_t), sizeof(float_test), pFile);
		fclose(pFile);
	}
	pFile = fopen("./fibonacci.tagha", "wb");
	if( pFile ) {
		fwrite(fibonacci, sizeof(uint8_t), sizeof(fibonacci), pFile);
		fclose(pFile);
	}
	pFile = fopen("./global_pointers.tagha", "wb");
	if( pFile ) {
		fwrite(global_pointers, sizeof(uint8_t), sizeof(global_pointers), pFile);
		fclose(pFile);
	}
	pFile = fopen("./local_pointers.tagha", "wb");
	if( pFile ) {
		fwrite(local_pointers, sizeof(uint8_t), sizeof(local_pointers), pFile);
		fclose(pFile);
	}
	pFile = fopen("./test_func_call.tagha", "wb");
	if( pFile ) {
		fwrite(test_func_call, sizeof(uint8_t), sizeof(test_func_call), pFile);
		fclose(pFile);
	}
	pFile = fopen("./all_opcodes_test.tagha", "wb");
	if( pFile ) {
		fwrite(all_opcodes_test, sizeof(uint8_t), sizeof(all_opcodes_test), pFile);
		fclose(pFile);
	}
	return 0;
}