#include "stdafx.h"
#include <stdio.h>
#include "DES-header.h"

extern unsigned long long Block;

/*
 * Function that test the DES Encyprtion flow
*/

void Encryption_unitTest(){
	// Blocks with multipels of 8 bytes, i.e. full block padding
	char* argv[] = {" " ,"encrypt", "plaintext_NF.txt", "key.txt", "ciphertext_NF.dat"};
	main_flow(argv);
	if(Block == 0x7915FD57D724DB9F)
		printf("Test Normal Flow Passed! \n");
	else
		printf("Test Normal Flow Failed! \n");
	// Block size % 8 != 0, i.e. subset block padding 	
	argv[1] = "encrypt";
	argv[2] =  "plaintext_SPadding.txt";
	argv[3] =  "key.txt";
	argv[4] =  "ciphertext_SPadding.dat";
	main_flow(argv);
	if(Block == 0x7D295C474D209AA1)
		printf("Test Padding Passed! \n");
	else
		printf("Test Padding Failed! \n");
}

