#include <stdio.h>

#include "PolyOptn.h"
#include "Sbox.h"

const unsigned int P=0x11B; //this is the base polyminal of GF(2^8)
uchar Sbox[16][16];
uchar invSbox[16][16];

//generate original matrix
void originMatrix(uchar m[16][16])
{
	for(uchar i=0;i<=0xf;i++)
		for(uchar j=0;j<=0xf;j++)
			m[i][j] = (i << 4) + j;
}

//print matrix
void printMatrix(uchar m[16][16])
{
	printf("%-5c", ' ');
	for(uchar t=0;t<=0xf;t++)
		printf("0x%-5x",t);
	printf("\n");
	for(uchar i=0;i<=0xf;i++)
	{
		printf("0x%-3x",i);
		for(uchar j=0;j<=0xf;j++)
			printf("0x%-5x",m[i][j]);
		printf("\n");
	}
}


//figure the reverse unit of a
uchar figureRev(uchar a)
{
	uint16 x_1=1,x0=0;//x_1 means x-1
	uint16 y_1=0,y0=1;
	uint16 q,r_1,r;
	uint16 r0 = P;
	r_1 = (uint16)a;
	uint16 x,y;
	if(a == 0x00)
		return 0;
	q = divide(r_1, r0, r);
	while(r != 0x01)
	{
		x = addDel(x_1, (uchar)multiply(x0, q));
		y = addDel(y_1, (uchar)multiply(y0, q));
		r_1 = r0;
		r0 = r;
		x_1 = x0;
		x0 = x;
		y_1 = y0;
		y0 = y;
		q = divide(r_1, r0, r);
	}
	x = addDel(x_1, (uchar)multiply(x0, q));
	return (uchar)x;
}

//gennerate reverse unit matrix, as S box
void genSbox(uchar m[16][16])
{
	originMatrix(m);
	for(int i=0;i<=0xf;i++)
		for(int j=0;j<=0xf;j++)
		{
			m[i][j] = figureRev(m[i][j]);
			m[i][j] = maptranf(m[i][j]);
		}
}

//map transformation
uchar maptranf(uchar a)
{
	const uchar matNum=0x63;
	uchar tmp[8]={0x00};

	for(uchar i=0;i<8;i++)
    {
        tmp[i]= (((a>>i)&0x1)^((a>>((i+4)%8))&0x1)^((a>>((i+5)%8))&0x1)^((a>>((i+6)%8))&0x1)^((a>>((i+7)%8))&0x1)^((matNum>>i)&0x1)) << i;
    }
    tmp[0] = tmp[0]+tmp[1]+tmp[2]+tmp[3]+tmp[4]+tmp[5]+tmp[6]+tmp[7];
    return tmp[0];
}

//reverse map transfer
uchar invmaptranf(uchar a)
{
	const uchar matNum=0x05;
	uchar tmp[8]={0x00};

	for(uchar i=0;i<8;i++)
    {
        tmp[i]= (((a>>((i+2)%8))&0x1)^((a>>((i+5)%8))&0x1)^((a>>((i+7)%8))&0x1)^((matNum>>i)&0x1)) << i;
    }
    tmp[0] = tmp[0]+tmp[1]+tmp[2]+tmp[3]+tmp[4]+tmp[5]+tmp[6]+tmp[7];
    return tmp[0];
}

//generate inverse Sbox
void geninvSbox(uchar m[16][16])
{
	originMatrix(m);
	for(int i=0;i<=0xf;i++)
		for(int j=0;j<=0xf;j++)
		{
			m[i][j]=invmaptranf(m[i][j]);
			m[i][j] = figureRev(m[i][j]);
		}
}         

//substitude function
//ch is substitude char, box is substitude box(Sbox/invSbox)
uchar SboxSubt(uchar ch, uchar box[16][16])
{
	uchar row=0x00, col=0x00;
	row = (ch & 0xf0) >> 4;
	col = ch & 0x0f;
	return box[row][col];
}


