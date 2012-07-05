/*
*Sometimes crunch plugin entries can get big.
*That is where voids.h comes in. This is a collection for the collection,
*a wasteland of data and functions for use in crunchLand.h, which is then used
*in crunch. If you are making a direct copy of a function from here to call in
*crunchLand, you must create functions and docs and what-not that will call in
*crunchland.
*
*PLEASE do not add any functions for use in crunch anywhere but right here. Even
*if this one file is to surpass ten-thousand or so lines it is designed to handle
*it. Nobody but the author of a function will have to look in this file.
*/
#include <iostream>
#include <cstdlib>

using namespace std;
/**
*The cookie-cutter crunch plugin.
*/
int hello()
{
    cout << "Hello!"<<endl<<endl;
    return 0;
}

int quit()
{
    exit(0);
    return 1;
}

int spew()
{
    stringstream buffer;

    string alphaL  = "abcdefghijklmnopqrstuvwxyz";
    string alphaC  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string numeric = "0123456789";
    string symbols = "`~!@#$%^&*()_+-=,<.>/?; :'\"\\][{}";

    string labels;
    int intensity;
    cout << "Welcome to the advanced spew interface. Type which pools to spew from."<<endl;
    cout << "0=lowercase, 1=uppercase, 2=Numbers, 3=Symbols. They can be combined like \"024\""<<endl;

    cout << "> ";
    cin  >> labels;
    cout << endl;

    cout << "How many characters?"<<endl;
    cout << "> ";
    cin  >> intensity;
    cout << endl;

    for(int index=0; index<intensity; index++) {
        if(labels.find("0")!=-1)
            buffer << alphaL.at(rand()%alphaL.length());

        if(labels.find("1")!=-1)
            buffer << alphaC.at(rand()%alphaC.length());

        if(labels.find("2")!=-1)
            buffer << numeric.at(rand()%numeric.length());

        if(labels.find("3")!=-1)
            buffer << symbols.at(rand()%symbols.length());
    }
    cout << "SPEW output: "<<buffer.str()<<endl<<endl;
    return 0;
}
