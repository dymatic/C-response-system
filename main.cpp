#include <iostream>
#include <cstdlib>
#include <time.h>
#include "HEADER/Crunch/crunch.h"
#include "HEADER/aiCore.h"
using namespace std;

/**
  *Main runs in two different ways: argument and interactive modes.
  *In argument mode, it is run like this: program [path to learn file] [wing modifier]
  *In interactive mode there are no arguments, but it will prompt for input.
  */
int main(int argc, char**argv){
    srand(time(NULL));
    string path;
    string target;

    int wing;
    if(argc<2)//START interactive
    {
        cout << "Path to learn file: ";
        getline(cin,path);
        cout << endl;

        cout << "WING modifier (higher is more accurate): ";
        cin  >> wing;
        cout << endl;
    }//END interactive
    else
    {
        path=argv[1];
        wing=atoi(argv[2]);

    }//END arg
    cout << "Enjoy the bot. Type #quit to quit." <<endl;
    setupStrings(path,wing);
    string command;
    for(;command!="#quit";)
    {
        cout << ":~$ ";
        getline(cin,command);
        if(command.length()<1)
            command="hi";

        if(isCrnchCmd(command))
        {
            cout << endl;
            loadCrunchCommand(command);
            executeCrunch();
        }//END crunch if
        else {
        setupStrings(path,wing);

        target=formulateResponse(command);

        if(target=="learn(toReplyTo)")
        {
            string learnSentence;
            cout << "I do not know how to reply to "<<command<<", please tell me.\n";
            cout << "> ";
            getline(cin,learnSentence);
            learn(command,learnSentence);
            cout << "Got it. So, " << learnSentence<<endl<<endl;
        }//END learn
        else
        cout << target<<endl;
        target="";
        }//END talk
        cout << endl;
    }//END main loop
}//END main

