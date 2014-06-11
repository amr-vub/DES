#include "stdafx.h"
#include <stdio.h>
#include "DES-header.h"
#include "DES-Tests-header.h"

void main(int argc, char* argv[]){
	// Round unit test
	unsigned long long R = Round_unit_test();
	printf("Right part is %x \n",R);	
	if (R == 0x8bddd057)
		printf("Round Test Passed");
	else
		printf("Round Test Failed");
	
	//Key generation testing
	int value=Key_Gen_test();
	if (value == 1)
		printf("KeyGen Test Passed\n");
	else
		printf("KeyGen Test Failed\n");

	// Encryption flow testing
	Encryption_unitTest();
	// Decryption flow testing
	Decryption_unitTest();

	// Sbox test
	SboxTest();
}