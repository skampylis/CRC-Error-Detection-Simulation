#include <iostream>
#include <string>
#include "Crc.h"

using namespace std;

int main()
{
    int k,BER,i,noflag=0,yesflag=0;
    unsigned int j;
    string s;
    cout<<"Give k(Tip:Give 20 for the exercise):";
    cin>>k;
    cout<<"Give P(Tip:Give 110101 for the exercise):";
    cin>>s;
    Crc P(s);
    cout<<"Give (BER) Bit Error Rate(Tip:Give 1000 for 10^-3):";
    cin>>BER;
    cout<<"Wait some seconds for the wrong messages to get detected by the CRC..."<<endl;
    i=0;
    while (i<1000000)
    {
        Crc signal(k),T,Noised,C;
        T=signal;
        T.shift(P.signal.size()-1);
        C=T.division(P);
        j=0;
        while (j<C.signal.size())
        {
            T.signal.pop_back();
            j++;
        }
        j=0;
        while (j<C.signal.size())
        {
            T.signal.push_back(C.signal.at(j));
            j++;
        }
        Noised=T.noise(BER);
        C=Noised.division(P);
        if (C.zero())
        {
            if (Noised!=T)
            {
                yesflag++;
            }
        }
        else
        {
            noflag++;
        }
        i++;
    }
    cout<<endl<<"The number of wrong messages get detected by the CRC:"<<noflag<<endl;
    cout<<"The number of wrong messages that reached the receiver and were not get detected by the CRC:"<<yesflag<<endl;
}
