//
// Created by Александр Ковель on 12.10.2023.
//

#include "Des.h"

void Des::expansion_function(int pos, int text)
{
    for (int i = 0; i < 48; i++)
    {
        if (E[i] == pos + 1) {
            EXPtext[i] = text;
        }
    }
}

int Des::initialPermutation(int pos, int text)
{
    int i;
    for (i = 0; i < 64; i++)
    {
        if (IP[i] == pos + 1) {
            break;
        }
    }
    IPtext[i] = text;
}


int Des::F1(int i)
{
    int r, c, b[6];

    for (int j = 0; j < 6; j++) {
        b[j] = X[i][j];
    }

    r = b[0] * 2 + b[5];
    c = 8 * b[1] + 4 * b[2] + 2 * b[3] + b[4];

    if (i == 0) {
        return S1[r][c];
    }
    else if (i == 1) {
        return S2[r][c];
    }
    else if (i == 2) {
        return S3[r][c];
    }
    else if (i == 3) {
        return S4[r][c];
    }
    else if (i == 4) {
        return S5[r][c];
    }
    else if (i == 5) {
        return S6[r][c];
    }
    else if (i == 6) {
        return S7[r][c];
    }
    else if (i == 7) {
        return S8[r][c];
    }
}

int Des::XOR(int a, int b) {
    return (a ^ b);
}

int Des::ToBits(int value) {
    int k, j, m;
    static int i;

    if (i % 32 == 0) {
        i = 0;
    }

    for (j = 3; j >= 0; j--)
    {
        m = 1 << j;
        k = value & m;
        if (k == 0) {
            X2[3 - j + i] = '0' - 48;
        }
        else {
            X2[3 - j + i] = '1' - 48;
        }
    }

    i = i + 4;
}

int Des::SBox(int *XORtext) {
    int k = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6; j++) {
            X[i][j] = XORtext[k++];
        }
    }

    int value;
    for (int i = 0; i < 8; i++)
    {
        value = F1(i);
        ToBits(value);
    }
}

int Des::PBox(int pos, int text) {
    int i;
    for (i = 0; i < 32; i++)
    {
        if (P[i] == pos + 1) {
            break;
        }
    }
    R[i] = text;
}

void Des::cipher(int Round, int mode) {
    for (int i = 0; i < 32; i++) {
        expansion_function(i, RIGHT[Round - 1][i]);
    }

    for (int i = 0; i < 48; i++)
    {
        if (mode == 0) {
            XORtext[i] = XOR(EXPtext[i], key48bit[Round][i]);
        }
        else {
            XORtext[i] = XOR(EXPtext[i], key48bit[17 - Round][i]);
        }
    }

    SBox(XORtext);

    for (int i = 0; i < 32; i++) {
        PBox(i, X2[i]);
    }

    for (int i = 0; i < 32; i++) {
        RIGHT[Round][i] = XOR(LEFT[Round - 1][i], R[i]);
    }
}

void Des::finalPermutation(int pos, int text) {
    int i;
    for (i = 0; i < 64; i++)
    {
        if (FP[i] == pos + 1) {
            break;
        }
    }
    ENCRYPTED[i] = text;
}



void Des::key64to48(unsigned int *key) {
    int k, backup[17][2];
    int CD[17][56];
    int C[17][28], D[17][28];

    for (int i = 0; i < 64; i++) {
        key64to56(i, key[i]);
    }

    for (int i = 0; i < 56; i++)
    {
        if (i < 28) {
            C[0][i] = key56bit[i];
        }
        else {
            D[0][i - 28] = key56bit[i];
        }
    }

    for (int x = 1; x < 17; x++)
    {
        int shift = SHIFTS[x - 1];

        for (int i = 0; i < shift; i++) {
            backup[x - 1][i] = C[x - 1][i];
        }

        for (int i = 0; i < (28 - shift); i++) {
            C[x][i] = C[x - 1][i + shift];
        }

        k = 0;
        for (int i = 28 - shift; i < 28; i++) {
            C[x][i] = backup[x - 1][k++];
        }

        for (int i = 0; i < shift; i++) {
            backup[x - 1][i] = D[x - 1][i];
        }

        for (int i = 0; i < (28 - shift); i++) {
            D[x][i] = D[x - 1][i + shift];
        }

        k = 0;
        for (int i = 28 - shift; i < 28; i++) {
            D[x][i] = backup[x - 1][k++];
        }
    }

    for (int j = 0; j < 17; j++)
    {
        for (int i = 0; i < 28; i++) {
            CD[j][i] = C[j][i];
        }

        for (int i = 28; i < 56; i++) {
            CD[j][i] = D[j][i - 28];
        }
    }

    for (int j = 1; j < 17; j++)
    {
        for (int i = 0; i < 56; i++) {
            key56to48(j, i, CD[j][i]);
        }
    }

}

int Des::key64to56(int pos, int text) {
    int i;
    for (i = 0; i < 56; i++)
    {
        if (PC1[i] == pos + 1) {
            break;
        }
    }
    key56bit[i] = text;
}

void Des::key56to48(int round, int pos, int text) {
    int i;
    for (i = 0; i < 56; i++)
    {
        if (PC2[i] == pos + 1) {
            break;
        }
    }
    key48bit[round][i] = text;
}

void Des::generate_key(std::string key) {
    unsigned int c_key[key.length()];
    char ch;
    for (int i = 0; i < key.length(); i++)
    {
        ch = key[i];
        c_key[i++] = ch - 48;
    }

    key64to48(c_key);
}

std::string Des::encrypt(std::string plain) {

    for (int i = 0; i < 64; i++) {
        initialPermutation(i, plain[i]);
    }

    for (int i = 0; i < 32; i++) {
        LEFT[0][i] = IPtext[i];
    }

    for (int i = 32; i < 64; i++) {
        RIGHT[0][i - 32] = IPtext[i];
    }

    for (int k = 1; k < 17; k++)
    {
        cipher(k, 0);

        for (int i = 0; i < 32; i++)
            LEFT[k][i] = RIGHT[k - 1][i];
    }

    for (int i = 0; i < 64; i++)
    {
        if (i < 32) {
            CIPHER[i] = RIGHT[16][i];
        }
        else {
            CIPHER[i] = LEFT[16][i - 32];
        }
        finalPermutation(i, CIPHER[i]);
    }
    std::string ret;
    for (int i = 0; i < 64; i++) {
        ret.push_back(ENCRYPTED[i]);
    }
    return ret;
}

