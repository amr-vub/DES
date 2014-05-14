#include "stdafx.h"
#include <stdio.h>
#include "DES-header.h"

void Encryption_unitTest(){
	// Blocks with multipels of 8 bytes, i.e. full block padding
	char* argv[] = {" " ,"encrypt", "plaintext_NF.txt", "key.txt", "ciphertext_NF.dat"};
	main_flow(argv);
	// Block size % 8 != 0, i.e. subset block padding 	
	argv[1] = "encrypt";
	argv[2] =  "plaintext_SPadding.txt";
	argv[3] =  "key.txt";
	argv[4] =  "ciphertext_SPadding.dat";
	main_flow(argv);
}

