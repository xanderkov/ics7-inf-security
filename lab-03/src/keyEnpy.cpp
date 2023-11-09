#include "keyExpansion.h"


//m mean crypted data matrix, num is the number of key being used
void keyEnpy(uchar m[4][4], int num)
{
	int j=0;
	for(int i=0;i<4;i++)
	{
		j = num + i;
		m[0][i] ^= (expKey[j] >> 24) & 0x000000ff;
		m[1][i] ^= (expKey[j]>>16) & 0x000000ff;
		m[2][i] ^= (expKey[j]>>8) & 0x000000ff;
		m[3][i] ^= expKey[j] & 0x000000ff;
	}
}