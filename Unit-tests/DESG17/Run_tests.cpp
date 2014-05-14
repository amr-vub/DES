#include "stdafx.h"
#include <stdio.h>
#include "DES-header.h"
#include "DES-RountTest-header.h"
#include "DES-EncryptionTest-header.h"

void main(int argc, char* argv[]){
	// Round unit test
	unsigned long long R = Round_unit_test();
	printf("Right part is %x \n",R);	
	if (R == 0x8bddd057)
		printf("Round Test Passed");
	else
		printf("Round Test Failed");
	printf("stop");

	// Encryption flow testing
	Encryption_unitTest();

}