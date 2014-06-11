#include "stdafx.h"
#include <stdio.h>
#include "DES-header.h"

extern int S1[4][16], S2[4][16], S3[4][16],
	S4[4][16], S5[4][16], S6[4][16], 
	S7[4][16], S8[4][16];

void SboxTest(){
	// preparing input data
	unsigned long long ip = 0x0000485031823567;
	// output data holder
	unsigned int op;
	// helper varaibles //
	// mask is used to get the middle 4 bits of each 6 bits value
	unsigned long long mask = 0x0000780000000000;
	// shift is used to shift the 4 bit value to the most right
	// shiftS is used to 
	short shift = 43, shiftS = 28;
	// maskFirstBit is used to get the first and then the last bits of the 6 bit value
	unsigned long long maskFirstBit = 0x0000800000000000;

	/*	
	 * Now, we call pass the input data through the 8-Sboxs, 
	 * as in the flow of DES 
	 */
	// S1 is applied to the first 6-bit value of the input data
	SBox(S1, ip, &op, mask, shift, maskFirstBit, shiftS);
	//updating the helper varaible in order to act on the next 6-bit value
	mask>>=6; maskFirstBit>>=6; shiftS-=4; shift-=6;

	// S2 is applied to the second 6-bit value of the input data
	SBox(S1, ip, &op, mask, shift, maskFirstBit, shiftS);
	//updating the helper varaible in order to act on the next 6-bit value
	mask>>=6; maskFirstBit>>=6; shiftS-=4; shift-=6;

	// S3 is applied to the third 6-bit value of the input data
	SBox(S1, ip, &op, mask, shift, maskFirstBit, shiftS);
	//updating the helper varaible in order to act on the next 6-bit value
	mask>>=6; maskFirstBit>>=6; shiftS-=4; shift-=6;

	// S4 is applied to the fourth 6-bit value of the input data
	SBox(S1, ip, &op, mask, shift, maskFirstBit, shiftS);
	//updating the helper varaible in order to act on the next 6-bit value
	mask>>=6; maskFirstBit>>=6; shiftS-=4; shift-=6;

	// S5 is applied to the fifth 6-bit value of the input data
	SBox(S1, ip, &op, mask, shift, maskFirstBit, shiftS);
	//updating the helper varaible in order to act on the next 6-bit value
	mask>>=6; maskFirstBit>>=6; shiftS-=4; shift-=6;

	// S6 is applied to the sixth 6-bit value of the input data
	SBox(S1, ip, &op, mask, shift, maskFirstBit, shiftS);
	//updating the helper varaible in order to act on the next 6-bit value
	mask>>=6; maskFirstBit>>=6; shiftS-=4; shift-=6;

	// S7 is applied to the seventh 6-bit value of the input data
	SBox(S1, ip, &op, mask, shift, maskFirstBit, shiftS);
	//updating the helper varaible in order to act on the next 6-bit value
	mask>>=6; maskFirstBit>>=6; shiftS-=4; shift-=6;

	// S8 is applied to the last 6-bit value of the input data
	SBox(S1, ip, &op, mask, shift, maskFirstBit, shiftS);

	// Checking if the output value is as expected
	if(op == 0xefedccce )
		printf("\nTest SBox Passed! \n");
	else
		printf("Test SBox Failed! \n");
}