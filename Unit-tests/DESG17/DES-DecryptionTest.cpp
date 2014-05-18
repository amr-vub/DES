#include "stdafx.h"
#include <stdio.h>
#include "DES-header.h"

extern unsigned long long Block;

/*
 * Function that test the DES Decryprtion flow
*/

void Decryption_unitTest(){
	// Blocks with multipels of 8 bytes, i.e. full block padding
	char* argv[] = {" " ,"decrypt", "plaintext_NF_D.txt", "key.txt", "ciphertext_NF.dat"};
	main_flow(argv);

	if(Block == 0x0808080808080808)
		printf("Test Normal Flow Passed! \n");
	else
		printf("Test Normal Flow Failed! \n");

	// Block size % 8 != 0, i.e. subset block padding 	
	argv[1] = "decrypt";
	argv[2] =  "plaintext_SPadding_D.txt";
	argv[3] =  "key.txt";
	argv[4] =  "ciphertext_SPadding.dat";
	main_flow(argv);

	if(Block == 0x50616464696e6700)
		printf("Test Padding Passed! \n");
	else
		printf("Test Padding Failed! \n");
}

