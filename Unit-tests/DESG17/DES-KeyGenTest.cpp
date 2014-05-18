#include "stdafx.h"
#include <stdio.h>
#include "DES-header.h"
#include "process.h"

unsigned char* pKey;
unsigned long keyLength = 64;


extern unsigned long long K1,K2,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,K14,K15,K16;

/*
 * Unit test for the KeyGenerator Function:
 * Checking
*/
int Key_Gen_test(){
	if(!LoadKey("TestKey.txt", &pKey, &keyLength)){printf("\nError Loading Plain Text File.\n");exit(0);}
	KeyGenerator(pKey, keyLength);
	if (K1 != 0x0000e096e6bfa9cf ){
		return 0;
	}
	if (K2 != 0x0000a096727727ef ){
		return 0;
	}
	if (K3 != 0x0000e45a72feb9cb ){
		return 0;
	}
	if (K4 != 0x0000a6f35066f77f ){
		return 0;
	}
	if (K5 != 0x00000e57537fbdea ){
		return 0;
	}
	if (K6 != 0x00006f5159ecdd7b ){
		return 0;
	}
	if (K7 != 0x00000fc1c94ffe7e ){
		return 0;
	}
	if (K8 != 0x00001b499bfdddf8 ){
		return 0;
	}
	if (K9 != 0x00001f4a89dffe3c ){
		return 0;
	}
	if (K10 != 0x00001b398cf95ff8 ){
		return 0;
	}
	if (K11 != 0x0000182ccd99fa3f ){
		return 0;
	}
	if (K12 != 0x0000516c2cf77eb4 ){
		return 0;
	}
	if (K13 != 0x0000c0ada4b92bff ){
		return 0;
	}
	if (K14 != 0x0000d0ae27b7fa97 ){
		return 0;
	}
	if (K15 != 0x0000e1b6227727f7 ){
		return 0;
	}
	if (K16 != 0x0000e0b22ef6f397 ){
		return 0;
	}

		return 1;	


}

