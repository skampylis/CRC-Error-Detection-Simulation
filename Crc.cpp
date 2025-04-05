#include "Crc.h"
#include <ctime>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

Crc::Crc()
{

}

Crc::~Crc()
{
    signal.clear();
}

Crc::Crc(int digits)
{
    static int t=time(nullptr);
    int i,num;
    srand(t*t);
    t=t*t+t;
    i=0;
    while (i<digits)
    {
        num=rand()%2;
        signal.push_back(num);
        i++;
    }
}

Crc::Crc(vector<bool> a)
{
    signal=a;
}

Crc::Crc(const Crc &a)
{
    signal=a.signal;
}

Crc::Crc(string a)
{
    int i=0;
    while(a[i])
    {
        if(a[i]!=48)
        {
            signal.push_back(1);
        }
        else
        {
            signal.push_back(0);
        }
        i++;
    }
}

void Crc::shift(int num)
{
    int i=0;
    while (i<num)
    {
        signal.push_back(0);
        i++;
    }
}

Crc Crc::division(Crc P)
{
    int i,j,signalSize=signal.size(),Psize=P.signal.size();
    vector<bool> temp;
    i=0;
    while (i<signalSize)
    {
        temp.push_back(signal.at(i));
        i++;
    }
    i=0;
    while(i<=signalSize-Psize)
    {
        if(temp.at(i)==1)
        {
            j=0;
            while(j<Psize)
            {
                temp.at(i+j)=temp.at(i+j)^P.signal.at(j);
                j++;
            }
        }
        i++;
    }
    vector<bool> rest;
    i=signalSize-Psize+1;
    while (i<signalSize)
    {
        rest.push_back(temp.at(i));
        i++;
    }
    return Crc(rest);
}

Crc Crc::noise(int BER)
{
    vector<bool> noised;
    static int t=time(nullptr);
    unsigned int i=0;
    srand(t*t);
    t=t*t+t;
    while (i<signal.size())
    {
        if (rand()%(BER+1)%BER==BER-1)
        {
            noised.push_back(!signal.at(i));
        }
        else
        {
            noised.push_back(signal.at(i));
        }
        i++;
    }
    return Crc(noised);
}

bool Crc::zero()
{
    unsigned int i=0;
    while (i<signal.size())
    {
        if (signal.at(i)!=0)
        {
            return false;
        }
        i++;
    }
    return true;
}

bool operator !=(const Crc a,const Crc b)
{
    unsigned int i=0;
    while (i<a.signal.size())
    {
        if(a.signal.at(i)!=b.signal.at(i))
        {
            return true;
        }
        i++;
    }
    return false;
}
