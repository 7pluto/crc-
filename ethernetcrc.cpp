#include "ethernetCrc.h"

EthernetCrc::EthernetCrc()
{
}

void EthernetCrc::gen_CRC32_TAB(uint_32 * table)
{
    uint_32 gx = 0x04c11db7;
    unsigned long i32, j32;
    unsigned long nData32;
    unsigned long nAccum32;
    for (i32 = 0; i32 < 256; i32++)
    {
        nData32 = (unsigned long)(i32 << 24);
        nAccum32 = 0;
        for (j32 = 0; j32 < 8; j32++)
        {
            if ((nData32 ^ nAccum32) & 0x80000000)
                nAccum32 = (nAccum32 << 1) ^ gx;
            else
                nAccum32 <<= 1;
            nData32 <<= 1;
        }
        table[i32] = nAccum32;
    }
}



uint_32 EthernetCrc::getCrc32CheckSum(uchar_8 *ptr, uint_32 len, uint_32 gx)
{
    uchar_8 i;
    uint_32 crc = 0xffffffff;
    while (len--)
    {
        for (i = 1; i != 0; i <<= 1)
        {
            if ((crc & 0x80000000) != 0)
            {
                crc <<= 1;
                crc ^= gx;
            }
            else
                crc <<= 1;
            if ((*ptr & i) != 0)
                crc ^= gx;
        }
        ptr++;
    }
    return (Reflect(crc, 32) ^ 0xffffffff);
}

ull_64 EthernetCrc::Reflect(ull_64 ref, uchar_8 ch)
{
    int i;
    ull_64 value = 0;
    for (i = 1; i < (ch + 1); i++)
    {
        if (ref & 1)
            value |= 1 << (ch - i);
        ref >>= 1;
    }
    return value;
}

void EthernetCrc::format_conversion(QString qs, uchar_8 * tx_data, int & _dataLen)
{
    char * str;
    //cin.getline(str, 999);
    QByteArray ba=qs.toLatin1();
    str = ba.data();
    int counter = 0;
    int len = strlen(str);

    for (int i = 0; i < len;i += 2) {
        tx_data[counter++] = catChar2Hex(str[i], str[i + 1]);
    }
    /*for (int i = 0; i < counter;i++) {
        printf("合并成一个字符为：0x%02x \n", int(tx_data[i]));
    }*/
    _dataLen = counter;
}

uchar_8 EthernetCrc::catChar2Hex(char hByte, char lByte)
{
    uchar_8 ucTmp = 0x00, hight, low;

    if ((hByte >= 'A') && (hByte <= 'F'))
    {
        hight = hByte - 'A' + 10;
    }
    else if (hByte >= 'a' && hByte <= 'f')
    {
        hight = hByte - 'a' + 10;
    }
    else if (hByte >= '0' && hByte <= '9')
    {
        hight = hByte - '0';
    }
    else
    {
        ucTmp = 0xff;
    }

    if ((lByte >= 'A') && (lByte <= 'F'))
    {
        low = lByte - 'A' + 10;
    }
    else if (lByte >= 'a' && lByte <= 'f')
    {
        low = lByte - 'a' + 10;
    } else if (lByte >= '0' && lByte <= '9')
    {
        low = lByte - '0';
    }
    else
    {
        ucTmp = 0xff;
    }
    ucTmp = (hight << 4) | (low << 0);//高位左移4位，低位不移动，组成一个8位十六进制字符
    return ucTmp;
}
