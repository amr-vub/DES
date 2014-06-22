#include "stdafx.h"
#include <stdio.h>
#include "DES-header.h"

void loadKeyTest(){
	// prepearing input varaibles
	char* fileName = "key.txt";

	// prepearing output varaibles
	unsigned char* pKey;
	// the number of bytes
	unsigned long keyLength = 0;

	bool res=false;

	res = LoadKey(fileName, &pKey, &keyLength);

	if(res == true)
		if(keyLength == 8)
			printf("\nLoadKeyTest has passed! \n");
		else
			printf("\nLoadKeyTest has failed! \n");
	else
		printf("\nLoadKeyTest has failed! \n");
	
}