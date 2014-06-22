#include "stdafx.h"
#include <stdio.h>
#include "DES-header.h"
#include "DES-Tests-header.h"

void main(int argc, char* argv[]){
	// Round unit test
	unsigned long long R = Round_unit_test();
	printf("Right part is %x \n",R);	
	if (R == 0x8bddd057)
		printf("\nRound Test Passed\n");
	else
		printf("\nRound Test Failed\n");
	
	//Key generation testing
	int value=Key_Gen_test();
	if (value == 1)
		printf("\nKeyGen Test Passed\n");
	else
		printf("\nKeyGen Test Failed\n");

	// Encryption flow testing
	Encryption_unitTest();
	// Decryption flow testing
	Decryption_unitTest();

	// Sbox test
	SboxTest();

	//Permutations testing
	int permValue=PermTest();
	if (permValue == 1)
		printf("\nAll permutations Passed!\n");
	else
		printf("\nPermutations Test Failed!\n");

	//Rotating testing
	RotateTest();

	// Load key test
	loadKeyTest();
}