// DES17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "process.h"
#include <fstream>
#include <string.h>
#include "time.h"
#include <conio.h>
#include <istream>
#include <iostream> 
#include <hash_map>
#include <cmath>
#include <string.h>
//#include <UnitTest++.h>

using namespace std;


bool LoadKey(const char* keyFilePath, unsigned char** ppKey, unsigned long* pKeyLength)
{
	FILE* pKeyFile = fopen(keyFilePath, "r");
	if(pKeyFile==0)return 0;
	
	fseek(pKeyFile, 0, SEEK_END);
	int fileLength = ftell(pKeyFile);
	fseek(pKeyFile, 0, SEEK_SET);

	char* pKeyText = new char[fileLength+1];
	fgets(pKeyText, fileLength + 1, pKeyFile);
	fclose(pKeyFile);

	*ppKey = new unsigned char[fileLength]; //extra allocation
	*pKeyLength = 0;

	char separators[] = " .;\/-,\'\"";	
	char* pToken = strtok( pKeyText, separators);
	while( pToken != 0 )
	{
		sscanf(pToken, "%02x", &(*ppKey)[(*pKeyLength)++]);
		pToken = strtok(NULL, separators);
	}

	return true;
}
unsigned long long K1,K2,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,K14,K15,K16;
unsigned int C=0,D=0;

void rotate(unsigned int  *x, int L, int N) 
{
    unsigned int lsbs = (*x) & 0x08000000;
	//lsbs << N-1; x>>L;
	unsigned int tem = 0,tem2=0;
	tem = (lsbs >> (N-L));
	tem2 = (*x << L) ;
    *x = (tem | tem2)& 0x0fffffff;
}


int ip[64]={58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
int invip[64]={40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};
int pc1[56]={57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
int pc2[48]={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
int ep[48]={32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
int p[32]={ 16  , 7 , 20 ,21,
            29 , 12,  28, 17,
            1 , 15 , 23 , 26,
            5 , 18 , 31 , 10,
            2,   8  ,24 , 14,
            32 , 27,   3,  9,
            19 , 13 , 30 , 6,
            22 , 11 ,  4,  25};


int chk=0;

unsigned long long Block;

unsigned long long perm(unsigned long long data, int per[], int outputSize, int shiftSize)
{
	unsigned long long result = 0, mask = 1;
	unsigned long long temp;
	unsigned long long d[64];
	short j = 0;
	for(int i=outputSize-1;i>=0;i--)
	{		
		//if(i==59) 
		//	cout<<"";
		temp = (data&(mask<<(shiftSize-per[i])))>>(shiftSize-per[i]);
		d[i]= temp;		
		temp<<=(outputSize-1-i);
		result|=temp;
		j++;
	}

	//cout<<pow(2.0,63)+1;
	return result;
}


void KeyGenerator( unsigned char* ppkey, unsigned long pKeyLength)
{
	unsigned long long tem=0, tem2, Key=0;
	short sh=56;
	for(int i =0; i<pKeyLength;i++)
	{
		tem = ppkey[i];						
		tem<<=sh;
		Key|=tem;							
		sh-=8;		
	}
	//Key = 0x133457799bbcdff1;/*0x1d17073525061f29;*///--------Just for test
	//PC2 for the original Key
	Key = perm( Key, pc1,  56, 64);
	//getting Key 1
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
	K1 = perm(Key, pc2, 48, 56);
	//
	//getting Key 2
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K2 = perm(tem2, pc2, 48, 56);
	//tem2 = K2;
	//
	//getting Key 3
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K3 = perm(tem2, pc2, 48, 56);
	//tem2 = K3;
	//
	//getting Key 4
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K4 = perm(tem2, pc2,  48, 56);
	//tem2 = K4;
	//
	//getting Key 5
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K5 = perm(tem2, pc2,  48, 56);
	//tem2 = K5;
	//
	//getting Key 6
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K6 = perm(tem2, pc2,  48, 56);
	//tem2 = K6;
	//
	//getting Key 7
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K7 = perm(tem2, pc2,  48, 56);
	//tem2 = K7;
	//
	//getting Key 8
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K8 = perm(tem2, pc2,  48, 56);
	//tem2 = K8;
	//
	//getting Key 9
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K9 = perm(tem2, pc2,  48, 56);
	//tem2 = K9;
	//
	//getting Key 10
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K10 = perm(tem2, pc2,  48, 56);
	//tem2 = K10;
	//
	//getting Key 11
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K11 = perm(tem2, pc2,  48, 56);
	//tem2 = K11;
	//
	//getting Key 12
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K12 = perm(tem2, pc2,  48, 56);
	//tem2 = K12;
	//
	//getting Key 13
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K13= perm(tem2, pc2,  48, 56);
	//tem2 = K13;
	//
	//getting Key 14
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K14 = perm(tem2, pc2,  48, 56);
	//tem2 = K14;
	//
	//getting Key 14
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K15 = perm(tem2, pc2,  48, 56);
	//tem2 = K15;
	//
	//getting Key 16
	C = (tem2 & 0x00FFFFFFF0000000)>>28;
	D = (tem2 & 0x000000000FFFFFFF);
	//rotate one time
	rotate(&C, 1, 28);
	rotate(&D, 1, 28);
	tem=0;
	tem = (C&0x000000000fffffff);
	tem<<=28;
	tem2 = tem |D;
	K16 = perm(tem2, pc2,  48, 56);
	//
}


	int S1[4][16] = 
	{{14 , 4 , 13 , 1  , 2 ,15,  11 , 8  , 3, 10  , 6, 12 ,  5,  9,   0,  7},
	{0 ,15  , 7 , 4 , 14,  2 ,13 , 1,  10,  6 , 12, 11 ,  9 , 5,   3,  8},
	{4,  1 , 14,  8,  13 , 6  , 2, 11 , 15, 12 ,  9 , 7, 3, 10 ,  5 , 0},
	{15,12,  8, 2 , 4, 9,  1, 7 , 5, 11,  3,14 ,10 ,0,  6,13}
	};

	int S2[4][16] =
	{{ 15 ,1 ,  8, 14,   6 ,11 ,  3 , 4 ,  9,  7 ,  2, 13 , 12,  0,   5, 10},
	{ 3, 13 ,  4 , 7 , 15 , 2 ,  8, 14 , 12 , 0  , 1, 10 ,  6 , 9 , 11 , 5 },
	{ 0 , 14 ,  7 ,11 , 10 , 4 , 13 , 1  , 5 , 8 ,12 , 6 ,  9 , 3 ,  2 , 15 },
	{ 13 , 8 , 10 , 1 ,  3 , 15 ,  4 , 2 , 11 , 6 ,  7, 12 ,  0 , 5 , 14 , 9 }
	};

	int S3[4][16] =
	{{ 10 , 0 ,  9, 14 ,  6 , 3 , 15 , 5 ,  1, 13 , 12 , 7 , 11 , 4  , 2 , 8},
	{ 13 , 7 ,  0 , 9 ,  3 , 4 ,  6 ,10 ,  2 , 8 ,  5 ,14 , 12, 11 , 15 , 1  },
	{ 13 , 6  , 4 , 9 ,  8 ,15 ,  3 , 0 , 11 , 1  , 2, 12 ,  5 ,10 , 14 , 7 },
	{  1 ,10 , 13 , 0  , 6 , 9 ,  8 , 7  , 4 ,15 , 14 , 3 , 11 , 5 ,  2, 12 }	
	};
	int S4[4][16] =
	{{ 7 ,13 , 14 , 3  , 0 , 6 ,  9 ,10  , 1 , 2 ,  8 , 5 , 11 ,12 ,  4 ,15},
	{ 13 , 8 , 11,  5 ,  6 ,15  , 0 , 3 ,  4 , 7  , 2 ,12  , 1 ,10 , 14 , 9 },
	{ 10 , 6  , 9 , 0 , 12 ,11 ,  7 ,13 , 15 , 1 ,  3 ,14 ,  5,  2 ,  8 , 4  },
	{ 3, 15  , 0 , 6 , 10 , 1 , 13 , 8 ,  9 , 4  , 5, 11 , 12 , 7  , 2, 14 }	
	};
	int S5[4][16] =
	{{ 2, 12  , 4,  1 ,  7, 10 , 11,  6 ,  8 , 5 ,  3 ,15 , 13 , 0 , 14 , 9},
	{ 14 ,11 ,  2 ,12  , 4 , 7 , 13 , 1  , 5 , 0 , 15 ,10 ,  3 , 9  , 8 , 6 },
	{ 4 , 2 ,  1 ,11 , 10, 13 ,  7 , 8  ,15 , 9 , 12 , 5  , 6 , 3  , 0 ,14 },
	{ 11,  8 , 12 , 7 ,  1 ,14 ,  2 ,13 ,  6 ,15 ,  0 , 9 , 10 , 4 ,  5 , 3 }	
	};
	int S6[4][16] =
	{{ 12,  1 , 10 ,15  , 9 , 2  , 6 , 8  , 0 ,13 ,  3 , 4 , 14 , 7 ,  5 ,11 },
	{ 10 ,15  , 4 , 2  , 7 ,12 ,  9 , 5  , 6 , 1 , 13, 14  , 0 ,11  , 3 , 8 },
	{ 9, 14,  15,  5 ,  2 , 8  ,12 , 3 ,  7 , 0 ,  4, 10 ,  1, 13,  11 , 6 },
	{ 4 , 3  , 2 ,12  , 9  ,5  ,15 ,10 , 11, 14  , 1 , 7  , 6 , 0 ,  8, 13 }	
	};
	int S7[4][16] =
	{{ 4, 11 ,  2, 14 , 15 , 0 ,  8, 13,   3, 12  , 9 , 7 ,  5 ,10  , 6  ,1},
	{ 13, 0 , 11 , 7  , 4  ,9  , 1 ,10 , 14 , 3 ,  5, 12 ,  2 ,15 ,  8 , 6 },
	{ 1 , 4 , 11 ,13 , 12,  3  , 7 ,14  ,10 ,15 ,  6 , 8 ,  0  ,5  , 9 , 2 },
	{ 6 ,11  ,13  ,8 ,  1 , 4 , 10 , 7  , 9 , 5  , 0 ,15 , 14 , 2  , 3 ,12 }	
	};
	int S8[4][16] =
	{{ 13 , 2 ,  8 , 4  , 6 ,15 , 11 , 1  ,10 , 9  , 3 ,14 ,  5 , 0  ,12 , 7  },
	{ 1 ,15  ,13 , 8 , 10 , 3  , 7 , 4 , 12 , 5  , 6, 11  , 0 ,14  , 9 , 2 },
	{ 7 ,11  , 4 , 1  , 9 ,12 , 14 , 2  , 0 , 6 , 10, 13 , 15 , 3 ,  5 , 8 },
	{ 2 , 1 , 14 , 7 ,  4, 10  , 8, 13 , 15, 12 ,  9 , 0 ,  3 , 5  , 6, 11 }	
	};

void SBox( int Si[4][16], unsigned long long data, unsigned int *newData, unsigned long long mask, short shift, unsigned long long maskfirstBit, short shiftS)
{
	int indexCol = 0;
	int firstBit = 0;
	int lastBit = 0;
	short indexRow = 0;
	unsigned int temp = 0;

	indexCol = (data & mask) >> shift ;
	firstBit = (data & maskfirstBit)>>(shift+3);
	lastBit =  (data & (maskfirstBit>>5))>>(shift-1);
	indexRow = firstBit | lastBit;

	temp = Si[indexRow][indexCol]<< shiftS;

	(*newData) = (*newData) | temp;

}

void Round(unsigned long long Key, unsigned long long *L, unsigned long long *R)
{
	unsigned int tem = 0;
	tem = *L;
	*L = *R;
	//Exp perm
	*R = perm( *R, ep, 48, 32);

	//Xoring with the 48-bit key
	(*R) = (*R)^Key;

	//S-Box
	 unsigned int newBlock = 0;
	unsigned long long mask = 0x0000780000000000;
	short shift = 43, shiftS = 28;
	unsigned long long maskFirstBit = 0x0000800000000000;
	//S1
	SBox(S1, (*R), &newBlock,mask, shift, maskFirstBit, shiftS);
	mask>>=6; maskFirstBit>>=6; shiftS-=4; shift-=6;
	//S2
	SBox(S2, (*R), &newBlock,mask, shift, maskFirstBit, shiftS);
	mask>>=6; maskFirstBit>>=6; shiftS-=4; shift-=6;
	//S3
	SBox(S3, (*R), &newBlock,mask, shift, maskFirstBit, shiftS);
	mask>>=6; maskFirstBit>>=6; shiftS-=4; shift-=6;
	//S4
	SBox(S4, (*R), &newBlock,mask, shift, maskFirstBit, shiftS);
	mask>>=6; maskFirstBit>>=6; shiftS-=4; shift-=6;
	//S5
	SBox(S5, (*R), &newBlock,mask, shift, maskFirstBit, shiftS);
	mask>>=6; maskFirstBit>>=6; shiftS-=4; shift-=6;
	//S6
	SBox(S6, (*R), &newBlock,mask, shift, maskFirstBit, shiftS);
	mask>>=6; maskFirstBit>>=6; shiftS-=4; shift-=6;
	//S7
	SBox(S7, (*R), &newBlock,mask, shift, maskFirstBit, shiftS);
	mask>>=6; maskFirstBit>>=6; shiftS-=4; shift-=6;
	//S8
	SBox(S8, (*R), &newBlock,mask, shift, maskFirstBit, shiftS);

	(*R) = newBlock;
	//Permutation
	(*R) = perm(*R, p,  32, 32);

	//Xoring with the old L
	(*R) = (*R)^tem;
}

//void main(int argc, char* argv[])
//{
//	long starttime = clock();
//
//	if((argc-1)!=4){printf("\ninvalid program arguments.\n");exit(0);}
//	unsigned char* pkey = 0;
//	unsigned long keylength = 0;
//	if(!loadkey((const char*)argv[3], &pkey, &keylength)){printf("\nerror loading plain text file.\n");exit(0);}
//	keygenerator(pkey, keylength);
//
//	file* pplaintextfile = 0;
//	file* pciphertextfile = 0;
//
//	if(stricmp(argv[1], "encrypt")==0)
//	{
//		pplaintextfile = fopen((const char*)argv[2], "r");
//		if(pplaintextfile==0){
//			printf("\nerror loading plaintext file.\n");
//			exit(0);
//		}
//
//		pciphertextfile = fopen((const char*)argv[4], "wb");
//		if(pciphertextfile==0){printf("\nerror creating ciphertext file.\n");exit(0);}
//		//
//		//getting the file size
//		fseek(pplaintextfile, 0, seek_end);
//		int filelength = ftell(pplaintextfile);
//		fseek(pplaintextfile, 0, seek_set);
//
//		
//		char* plaintxtblock = new char[filelength]; // the block of data(64 bits)
//		//cout<<
//		
//		char toto[8];	
//		unsigned long long key = 29699430183026, blockright,mas,tem;
//		int iterating = 0;
//		unsigned long long l,r;	
//		int flagdummy = 0;
//		short sh=56, re=8;
//		//reading the data from the file!
//		while(iterating < filelength){
//			if(flagdummy == 0)
//			{
//				block = 0;
//				blockright=0;
//				fread(&blockright,8,1,pplaintextfile);
//							
//				mas = 0x00000000000000ff;
//				sh=56; re=8;
//				if(filelength-8<iterating)
//					cout<<"";
//				for(int i =0; i<8;i++){//----------------------------
//					tem = (blockright&mas);						
//					if(i<4)
//					{
//						tem<<=sh;
//						block|=tem;							
//						sh-=16;
//					}
//					else
//					{
//						tem>>=re;
//						block|=tem;	
//						re+=16;
//					}
//					mas<<=8;
//				}
//				if(filelength%8==0 && iterating+8==filelength)
//				{				
//					iterating-=8;
//					flagdummy = 1;				
//				}
//	
//			}
//			else 
//				block = 0x0808080808080808;
//			//
//			//block = 0x00006520656d6169;//---------------------test block
//			//k1 = 0x0000cb3d8b0e17f5;//-------------test key
//			//check for the end block size	
//			if(filelength%8!=0 && iterating+8>filelength)
//			{
//				unsigned long long data2add = 8-((filelength) % 8);
//				unsigned long long temp = data2add;//data2add<<(8*(8-data2add));
//				for(int i=0;i<data2add;i++)
//				{
//					block = block|temp;
//					temp = data2add<<8*(i+1);//(8*((8-data2add)+(i+1)));
//				}
//			}
//
//			if(block == 0x7365637572697479)
//				cout<<"";
//		
//			//ip
//			block = perm(block, ip, 64, 64);
//
//			l = (block & 0xffffffff00000000)>>32;
//			r = (block & 0x00000000ffffffff);
//			//printf("%x", l);
//			//r1
//			round(k1,&l,&r);
//			//r1
//			round(k2,&l,&r);
//			//r1
//			round(k3,&l,&r);
//			//r1
//			round(k4,&l,&r);
//			//r1
//			round(k5,&l,&r);
//			//r1
//			round(k6,&l,&r);
//			//r1
//			round(k7,&l,&r);
//			//r1
//			round(k8,&l,&r);
//			//r1
//			round(k9,&l,&r);
//			//r1
//			round(k10,&l,&r);
//			//r1
//			round(k11,&l,&r);
//			//r1
//			round(k12,&l,&r);
//			//r1
//			round(k13,&l,&r);
//			//r1
//			round(k14,&l,&r);
//			//r1
//			round(k15,&l,&r);
//			//r1
//			round(k16,&l,&r);
//
//			//32-bit swap
//			unsigned long long temp=0 ;
//			temp= l;
//			l=r;
//			r=temp;
//			block = 0;
//			block = l;
//			block <<=32;
//			block|=r;
//
//			//inv ip
//			block=perm( block, invip,  64, 64);	
//
//			char mybuffer[8];
//				
//
//			char *c_ptr = (char*)&block;			
//			//sprintf(mybuffer,"%c%c%c%c%c%c%c%c", c_ptr[7], c_ptr[6], c_ptr[5], c_ptr[4], c_ptr[3], c_ptr[2], c_ptr[1], c_ptr[0]);
//			//cout<<mybuffer;
//			fprintf( pciphertextfile, "%c%c%c%c%c%c%c%c",c_ptr[7], c_ptr[6], c_ptr[5], c_ptr[4], c_ptr[3], c_ptr[2], c_ptr[1], c_ptr[0]);
//			//fwrite((const void*)&block, 8,1,pciphertextfile);
//
//			iterating+=8;
//	
//		}
//
//		long finishtime = clock();
//
//		printf("\nencryption completed successfully in %d ms\n", finishtime- starttime);
//		cout<<"";
//	}
//	else if(stricmp(argv[1], "decrypt")==0)
//	{
//		pplaintextfile = fopen((const char*)argv[2], "w");
//		if(pplaintextfile==0){printf("\nerror loading plaintext file.\n");exit(0);}
//
//		pciphertextfile = fopen((const char*)argv[4], "rb");
//		if(pciphertextfile==0){printf("\nerror creating ciphertext file.\n");exit(0);}
//		//
//		//getting the file size
//		fseek(pciphertextfile, 0, seek_end);
//		int filelength = ftell(pciphertextfile);
//		fseek(pciphertextfile, 0, seek_set);
//		//
//		unsigned long long tem=0,key = 0, blockright=0, mas;
//		int iterating = 0;
//		unsigned long long l = 0,r = 0;
//		short sh=56, re=8; 
//		unsigned char mybuffer[8];
//		//filelength-=3;
//		//reading the data from the file!
//		while(iterating < filelength)
//		{	
//
//
//			//reading the 64-bit block						
//			blockright=0;
//			block=0;
//			fread(&mybuffer,8,1,pciphertextfile);	
//
//			block |= mybuffer[7];
//			tem = mybuffer[6];
//			block |= tem<<8;
//			tem = mybuffer[5];
//			block |= tem<<16;
//			tem = mybuffer[4];
//			block |= tem<<24;
//			tem = mybuffer[3];
//			block |= tem<<32;
//			tem = mybuffer[2];
//			block |= tem<<40;
//			tem = mybuffer[1];
//			block |= tem<<48;
//			tem = mybuffer[0];
//			block |= tem<<56;	
//
//			//block = 0x0123456789abcdef;//---------------------test block
//			//k16 = 0x0000cb3d8b0e17f5;//-------------test key
//			// ip
//			if(iterating ==296)
//				cout<<"";
//			block = perm(block, ip,  64, 64);
//
//			//
//			l = (block & 0xffffffff00000000)>>32;
//			r = (block & 0x00000000ffffffff);
//		
//			//r16
//			round(k16,&l,&r);
//			//r15
//			round(k15,&l,&r);
//			//r14
//			round(k14,&l,&r);
//			//r13
//			round(k13,&l,&r);
//			//r12
//			round(k12,&l,&r);
//			//r11
//			round(k11,&l,&r);
//			//r10
//			round(k10,&l,&r);
//			//r9
//			round(k9,&l,&r);
//			//r8
//			round(k8,&l,&r);
//			//r7
//			round(k7,&l,&r);
//			//r6
//			round(k6,&l,&r);
//			//r5
//			round(k5,&l,&r);
//			//r4
//			round(k4,&l,&r);
//			//r3
//			round(k3,&l,&r);
//			//r2
//			round(k2,&l,&r);
//			//r1
//			round(k1,&l,&r);
//			//
//			//32-bit swap
//			unsigned long long temp = 0;
//			temp = l;
//			l=r;
//			r=temp;
//			block = 0;
//			block = l;
//			block <<=32;
//			block|=r;
//
//			// ip
//			block=perm( block, invip,  64, 64);
//
//			//check for the end block size		
//			if(filelength-8==iterating)
//			{
//				char ch = block&0x0000000000000000ff;
//				short data2remove =0;
//				data2remove = ch;
//				mas = 0xffffffffffffff00;
//				if(ch!=0x08)
//				{
//					for(int i = 0; i<data2remove;i++){
//						block &= mas;
//						mas<<=8;
//					}
//				}
//				else if(ch==0x08)
//					break;
//			}
//			
//			//long long mylonglong = 0x74657374696e6773;
//			char c_ptr[8];
//			/*unsigned long long tr4y=(block&0xff00000000000000)>>56;*/
//			c_ptr[7]=(block&0xff00000000000000)>>56;
//			c_ptr[6]=(block&0x00ff000000000000)>>48;
//			c_ptr[5]=(block&0x0000ff0000000000)>>40;
//			c_ptr[4]=(block&0x000000ff00000000)>>32;
//			c_ptr[3]=(block&0x00000000ff000000)>>24;
//			c_ptr[2]=(block&0x0000000000ff0000)>>16;
//			c_ptr[1]=(block&0x000000000000ff00)>>8;
//			c_ptr[0]=(block&0x00000000000000ff);
//
//			fprintf( pplaintextfile,"%c%c%c%c%c%c%c%c", c_ptr[7], c_ptr[6], c_ptr[5], c_ptr[4], c_ptr[3], c_ptr[2], c_ptr[1], c_ptr[0]);
//			//writing in the plain text file
//			
//
//			iterating+=8;
//
//		}
//
//			long finishtime = clock();
//
//			printf("\ndecryption completed successfully in %d ms\n", finishtime- starttime);
//			cout<<"";
//	}
//	
//	delete[] pkey;
//
//	fclose(pplaintextfile);
//	fclose(pciphertextfile);
//	//getch();
//}

