

bool LoadKey(const char* keyFilePath, unsigned char** ppKey, unsigned long* pKeyLength);

void rotate(unsigned int  *x, int L, int N);

unsigned long long perm(unsigned long long data, int per[], int outputSize, int shiftSize);

void KeyGenerator( unsigned char* ppkey, unsigned long pKeyLength);

void SBox( int Si[4][16], unsigned long long data, unsigned int *newData, unsigned long long mask, short shift, unsigned long long maskfirstBit, short shiftS);

void Round(unsigned long long Key, unsigned long long *L, unsigned long long *R);
