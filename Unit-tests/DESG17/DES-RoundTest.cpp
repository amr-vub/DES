#include "stdafx.h"
#include <stdio.h>
#include "DES-header.h"

unsigned long long Key = 0x5B5A57676A56676E, Key1;
unsigned long long R = 0x004df6fb;
unsigned long long L = 0xffb2194d;

extern int pc1[56], pc2[48];

/*
 * Unit test for the Round Function:
 * Checking
*/
unsigned long long Round_unit_test(){

	unsigned int C, D;	
	unsigned long long tem, tem2;

	// getting the key ready
	Key = perm( Key, pc1,  56, 64);
	C = (Key & 0x00FFFFFFF0000000)>>28;
	D = (Key & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	Key = tem |D;
	tem2 = Key;
	Key1 = perm(Key, pc2, 48, 56);

	Round(Key1, &L, &R);

	return R;
}
