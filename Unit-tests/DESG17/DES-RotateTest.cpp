#include "stdafx.h"
#include <stdio.h>
#include "DES-header.h"

//extern int ip[64],invip[64],pc1[56],pc2[48],ep[48],p[32];
//unsigned long long data=0x8F78C612BA98A216;

/*
 * Unit test for the rotate function:
 *
*/

void RotateTest(){

	//test values takes the initial value of 000100000001 (binary)
	unsigned int testValue =0x00000101;
	rotate(&testValue, 1, 28);
	if (testValue==0x00000202)
		printf("\nRotate test passed succesfully!\n");
	else 
		printf("\nRotate test passed succesfully!\n");

}
