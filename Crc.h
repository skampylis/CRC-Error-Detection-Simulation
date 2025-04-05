#ifndef CRC_H
#define CRC_H
#include <vector>
#include <iostream>

using namespace std;

class Crc
{
    public:
        vector<bool> signal;
        Crc();
        ~Crc();
        Crc(int);
        Crc(vector<bool>);
        Crc(string);
        Crc(const Crc&);
        void shift(int);
        Crc division(Crc);
        Crc noise(int);
        bool zero();
};

bool operator!=(const Crc,const Crc);

#endif // CRC_H
