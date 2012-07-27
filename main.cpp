#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <cstring>
#include "HEADER/Crunch/crunch.h"
#include "HEADER/aiCore.h"
using namespace std;

const int gnus=2;//How many command line options there are
void (*gnuFun[gnus])()= {&versionGet, &helpGet}; //Options relating to non-execution information
string gnuPrompts[gnus][3]= {{"--version","-v", "yes"},{"-h", "--help", "yes"}}; //The names with the primary (-a) on [ind] and --arg on [ind][0]. At ind[3] "yes" means exit, "no" means stay

/**
*Handles the command line arguments of main.
*@param argc - Number of args
*@param argv - The arguments
*@return handled - If an argument was found
*/
bool handleArgs(int argc, char**argv) {
    for(int index=1; index<argc; index++) {
/*
*LOOP OUTLINE
*Iterate through arguments
*Iterate through commands, comparing them to argument
*Execute command if it is found, go to next argument otherwise
*Exit if that is specified
*Return false if nothing was done
*/
        for(int gnuCommands=0; gnuCommands<gnus; gnuCommands++) {

            if(string(argv[index])==gnuPrompts[gnuCommands][0]||string(argv[index])==gnuPrompts[gnuCommands][1]) {//If the --command or -c is found
                gnuFun[gnuCommands]();//Executes the command that matches the name

                if(gnuPrompts[gnuCommands][2]=="yes") {
                    exit(0);
                } else return true;
            }//END found if
        }//END command search
    }//END arg list
    return false;
}//END function
/**
  *Main runs in two different ways: argument and interactive modes.
  *In argument mode, it is run like this: program [path to learn file] [wing modifier]
  *In interactive mode there are no arguments, but it will prompt for input.
  */
int main(int argc, char**argv) {
    srand(time(NULL));//Seed random for voids.h and WING

    /*Objects*/
    string path;//File Path
    string target;//Output

    /*Primitives*/
    int wing;//Chance to wing it.

    /*Constants*/
    const bool wantLearn=true;//Whether or not the bot should strive to learn(DEFAULT: TRUE)
    const bool allowCrunch=true;//Whether or not to allow executing plugins. (DEFAULT: TRUE)
    const bool allowExpllearn=true;//Whether or not to allow explicit non-confrontational learning (DEFAULT: TRUE)

    string prompt     = "~$ ";

    const char* noCrunchMsg="Permission Denied.";
    const char* understood ="Understood";//After exlLearned

    if(argc<2||handleArgs(argc, argv)) { //START interactive
        cout << "Path to learn file: ";
        getline(cin,path);
        cout << endl;

        cout << "WING modifier (higher is more accurate): ";
        cin  >> wing;
        cout << endl;
    }//END interactive

    else { //Not interactive
        path=argv[1];
        wing=atoi(argv[2]);

    }//END interactive mode

    cout << "Enjoy the bot. Type #quit to quit, #intro for crunch" <<endl;
    setupStrings(path,wing);
    string command;//Anything, crunch or voice.

    for(; command!="#quit";) { //Endless loop until #quit is called
        cout << prompt<<" ";
        getline(cin,command);
        if(command.length()<1)
            command="hi";

        if(command.find("Set")!=-1) { //Can set the prompte
            string p1=command.substr((command.find("<")+1),(command.find(">")-2));
            prompt=p1.substr(0,p1.length()-1);
            continue;
        }
        if(isCrnchCmd(command)) {
            cout << endl;

            if(allowCrunch) {
                loadCrunchCommand(command);
                executeCrunch();
            }//END allowed

            else {
                cout << noCrunchMsg << endl;
            }//END not allowed

        }//END crunch if

        else { //NOT crunch query
            setupStrings(path,wing);

            target=formulateResponse(command);

            if(target=="learn(toReplyTo)"&&wantLearn) { //Arrays not loaded right, WING not gotten, or new input
                string learnSentence;//Response to self

                cout << "I do not know how to reply to "<<command<<", please tell me.\n";
                cout << "> ";

                getline(cin,learnSentence);
                learn(sanitizeInput(command),learnSentence);//Will try twice if blank is given

                cout << "Got it. So, " << learnSentence<<endl<<endl;
            }//END learn

            else if(target=="exlLearned"&&allowExpllearn) {
                exlLearn(command);
                target="Understood.";
            }

            else if(target!="learn(toReplyTo)") { //Input found, or WING gotten
                cout << target<<endl;
                target=understood;
            }//END talk
            cout << endl;

            usleep(1000);
        }//END true talk
    }//END main loop
}//END main
