#include "stdafx.h"
#include <stdio.h>
#include "DES-header.h"

extern int ip[64],invip[64],pc1[56],pc2[48],ep[48],p[32];
unsigned long long data=0x8F78C612BA98A216;

/*
 * Unit test for the permutations:
 *
*/

int PermTest(){

	unsigned long long ipTest,invipTest,pc1Test,pc2Test,epTest,pTest;

	ipTest=perm(data, ip,  56, 64);
	invipTest=perm(data, invip,  56, 64);
	pc1Test=perm(data, pc1,  56, 64);
	pc2Test=perm(data, pc2,  56, 64);
	epTest=perm(data, ep,  56, 64);
	pTest=perm(data, p,  56, 64);

	//testing the Initial Permutation 
	if(ipTest != 0x0006ba8501755233)
		return 0;

	//testing the Inverse Initial Permutation 
	if(invipTest != 0x0040cf46f0b39814)
		return 0;

	//testing the Permutation Choice 1 
	if(pc1Test != 0x00750652bdd8533a)
		return 0;

	//testing the Permutation Choice 2 
	if(pc2Test != 0x006d5a52b4ee0445)
		return 0;

	//testing the Encryption Path
	if(epTest != 0x0045ebf160c0a547)
		return 0;

	//testing the final Permutation
	if(pTest != 0x0047af405c337923)
		return 0;

	return 1;

}