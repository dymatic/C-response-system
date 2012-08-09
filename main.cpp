/*
*Main is the heart of the program, handling crunch commands and output.
*See the README for what each of the files in HEADER/* do.
*/
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <cstring>
#include "HEADER/Crunch/crunch.h"
#include "HEADER/aiCore.h"
#include "HEADER/mainHelper.h"
#include "HEADER/mainResponse.h"
using namespace std;

/**
  *Main runs in two different ways: argument and interactive modes.
  *In argument mode, it is run like this: program [path to learn file] [wing modifier]
  *In interactive mode there are no arguments, but it will prompt for input.
  */
int main(int argc, char**argv)
{
    srand(time(NULL));//Seed random for voids.h and WING
    /*Objects*/
    string path;//File Path
    string target;//Output
    /*Primitives*/
    int wing;//Chance to wing it.

    /*Options*/
    bool WANT_LEARN=true;//Whether or not the bot should strive to learn(DEFAULT: TRUE)
    bool ALLOW_CRUNCH=true;//Whether or not to allow executing plugins. (DEFAULT: TRUE)
    bool ALLOW_EXPLICIT=true;//Whether or not to allow explicit non-confrontational learning (DEFAULT: TRUE)
    bool ASSUME_CRUCIAL=true;//Reverses crucial string behavior.

    string prompt     = "Bot $  ";

    const char* noCrunchMsg="Permission Denied.";//Used when crunch is not allowed
    const char* understood ="Understood";//After exlLearned
    const char* greetings  ="Enjoy the bot. Here are some useful commands: \n\
                    Set<anything > where anthing becomes the prompt (really use <>'s)\n\
                    #quit - To end the program\n\
                    #intro - Learn about crunch commands\n\
                    #terminal - Run external commands\n\n";

    bool handled=handleArgs(argc, argv);//Whether or not arguments were found

    if(argc<2||handled)   //START interactive
    {
        cout << "Path to learn file: ";
        getline(cin,path);
        cout << endl;

        cout << "WING modifier (higher is more accurate): ";
        cin  >> wing;
        cout << endl;
    }//END interactive

    else   //Not interactive
    {
        path=argv[1];
        wing=atoi(argv[2]);

    }//END interactive mode

    if(pConfig.path!=defPath)//Configuration file set by -c option at command line
    {
        pConfig.loadConfig(WANT_LEARN, ALLOW_CRUNCH, ALLOW_EXPLICIT, ASSUME_CRUCIAL);
        setAC(ASSUME_CRUCIAL);
        cout << "Finished loading"<<endl;
    }

    cout << greetings<<endl;
    setupStrings(path,wing);
    string command;//Anything, crunch or voice.

    for(; command!="#quit";)   //Endless loop until #quit is called
    {
        cout << prompt<<" ";
        getline(cin,command);

        if(command.length()<1)
            command="hi";

        if(command.find("Set")!=-1&&command.find("<")!=-1&&command.find(">")!=-1)   //Can set the prompte
        {
            string p1=getBetween(command, "<", ">");
            prompt=p1.substr(0, p1.length()-1);
            continue;
        }

        if(isCrnchCmd(command))
        handleCrunch(command, ALLOW_CRUNCH, noCrunchMsg);

        else   //NOT crunch query
        {
        handleResponse(path, wing, WANT_LEARN, ALLOW_EXPLICIT, command, understood);
        }//END true talk
    }//END main loop
}//END main
