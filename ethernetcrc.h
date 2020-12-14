#pragma once
#include<iostream>
#include <QMainWindow>
using namespace std;

#define uchar_8  unsigned char
#define uint_32  unsigned int
#define ull_64   unsigned long long

class EthernetCrc{
public:
    EthernetCrc();
    ull_64 Reflect(ull_64 ref, uchar_8 ch);
    void format_conversion(QString qs, uchar_8 * tx_data, int & _dataLen);
    uint_32 getCrc32CheckSum(uchar_8 * ptr, uint_32 len, uint_32 gx);
    void gen_CRC32_TAB(uint_32 * table);
    uchar_8 catChar2Hex(char hByte, char lByte);
};

