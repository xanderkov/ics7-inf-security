#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "AES.h"
#include "Sbox.h"
#include "keyExpansion.h"
#include "shiftRows.h"
#include "mixColumns.h"
#include "keyEnpy.h"
#include <string>
#include <iostream>

static uchar IV[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};


std::string getExtension(std::string& filename) {
    return filename.substr(filename.find_last_of("."));
}

void unitDecrypt(uchar list[16], uchar *preC)
{
    //the suffix of list
    int suffix=0;
    //loop num
    uchar loopNum = 9;
    //matrix from encrypt 128 bits
    uchar array[4][4];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            array[j][i] = list[suffix++];
        }
    }
    //first encrypt by key
    keyEnpy(array, 40);

    //9 cycles encrypt
    for(int i=0; i<loopNum; i++)
    {
        //shift rows
        invshiftRows(array);
        //Sbox substitude
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<4;k++)
            {
                array[k][j] = SboxSubt(array[k][j], invSbox);
            }

        }
        //encrypt by key
        keyEnpy(array, 40 - (i+1)*4);
        invmixColumns(array);
    }//for loopNum

    //last shift rows
    invshiftRows(array);

    //Sbox substitude
    for(int j=0;j<4;j++)
    {
        for(int k=0;k<4;k++)
        {
            array[k][j] = SboxSubt(array[k][j], invSbox);
        }

    }

    //last encrypt by key
    keyEnpy(array, 0);

    suffix = 0;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            list[suffix++] = array[j][i];
            list[suffix - 1] ^= preC[suffix - 1];
        }
    }

}


void unitEncrypt(uchar list[16], uchar *preC)
{
    //the suffix of list
    int suffix=0;
    //loop num
    uchar loopNum = 9;
    //matrix from encrypt 128 bits
    uchar array[4][4];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            array[j][i] = list[suffix++];
            array[j][i] ^= preC[suffix - 1];
        }
    }
    //first encrypt by key
    keyEnpy(array, 0);
    //9 cycles encrypt
    for(int i=0; i<loopNum; i++)
    {
        //Sbox substitude
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<4;k++)
            {
                array[k][j] = SboxSubt(array[k][j], Sbox);
            }

        }
        //shift rows
        shiftRows(array);
        mixColumns(array);
        //encrypt by key
        keyEnpy(array, (i+1)*4);
    }//for loopNum

    //the last time substitude
    for(int j=0;j<4;j++)
    {
        for(int k=0;k<4;k++)
        {
            array[k][j] = SboxSubt(array[k][j], Sbox);
        }

    }
    //the last time shift rows
    shiftRows(array);
    //the last time key encrypt
    keyEnpy(array, 40);

    suffix = 0;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            list[suffix++] = array[j][i];
        }
    }
}


void encrypt(FILE *inputData, FILE *outputData)
{
    //input list of 16 bytes
    uchar list[16];
    int suffix=0;
    uchar temp=0x00;
    uchar *preC = IV;
    fwrite(preC,16,1,outputData);
    while(fread(list,16,1,inputData)==1)
    {
        unitEncrypt(list, preC);
        fwrite(list,16,1,outputData);
    }

    //encrypt least data, whose length < 128
    while((temp = fgetc(inputData)!=EOF))
    {
        list[suffix++] = temp;
    }

    if(suffix > 0)
    {
        for(int i=suffix; i<16; i++)
        {
            list[i] = 0x00;
        }
        unitEncrypt(list, preC);
        fwrite(list,16,1,outputData);
    }

    fclose(inputData);
    fclose(outputData);
}

void decrypt(FILE *inputData, FILE *outputData)
{
    //input list of 16 bytes
    uchar list[16];
    int suffix=0;
    uchar IV[16] = {0x00};
    uchar *preC = IV;
    uchar thisC[16] = {0x00};
    fread(preC,16,1,inputData);
    while(fread(list,16,1,inputData)==1)
    {
        unitDecrypt(list, preC);
        fwrite(list,16,1,outputData);
    }

    fclose(inputData);
    fclose(outputData);
}


int main()
{
    genSbox(Sbox);
    geninvSbox(invSbox);

    keyExpansion();

    std::string filename;
    std::cout << "Filename: ";
//    std::cin >> filename;
    std::string pwd = "/Users/akovel/Documents/bmstu/ics7-inf-security/lab-03/src/";
    filename = pwd + "input/medic.jpg";
    std::string ext = getExtension(filename);

    FILE *inputData = fopen(filename.c_str(), "rb");

    std::string encFilename(pwd + "output/encryptedData");
    FILE *cryptedData = fopen((encFilename + ext).data(), "wb+");

    encrypt(inputData, cryptedData);

    std::cout << "Output in " << (encFilename + ext).data() << std::endl;
    printf("\n*************************************************\n\n");

    std::string decr(pwd + "output/decryptedData");
    cryptedData = fopen((encFilename + ext).data(), "rb+");
    FILE *decryptData = fopen((decr + ext).data(), "wb+");

    decrypt(cryptedData, decryptData);

    std::cout << "Output in " << (decr + ext).data() << std::endl;
    printf("\n*************************************************\n");
    return 0;
}