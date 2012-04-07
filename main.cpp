#include <iostream>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "Item.h"
#include "Warriors.h"
#include "VoidGames.h"
#include "Engine.h"
using namespace std;

int main()
{
    srand(time(NULL));
    cout << "You will now talk to a dumb AI that does what it's told!"<<endl;
    cout << "What do you want to tell it? Oh, and enter # for a program command. # - rand is fun."<<endl<<endl;
    string input;
    string output;
    short result=0;
    for(int index; ; index++)
    {
        cout << "User: ";
        getline(cin,input);
        cout <<endl;

        if(input=="#")
            result=crunch();

        if(result==-1)
        {
            cout << "Shutting down the program."<<endl;
            break;
        }


        output=formulateResponse(cleanup(input));
        cout <<"AI: "<< output<<endl;
    }//Body Loop
    return 0;
}
