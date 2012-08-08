/*
*In version 4.6, crunch Commands got their first makeover since the rewrite of the original
*crunchCommands in nAI 3. Now a structure named crunchCommand holds the crunch commands. This
*makes a mistake pretty much impossible when leaving data out. Before the program used a function pointer and string array.
  */
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "voids.h"
using namespace std;
/*Indexing*/
const int members=15;//The number of plugins

/*Core utility headers*/
int lsc();
bool crunchListed(string cc);
int crnchID();
int desc();
int fisc();
int isc();

//!Holds function and documentation level data
struct crunchCommand
{
    int (*arrPtr)();//The function to execute
    string funcName;//The name of the function
    string documentation;//The documented that goes along with the function

    crunchCommand(int (*arrP)(), string fName, string docs)
    {
        arrPtr=arrP;
        funcName=fName;
        documentation=docs;
    }

//!Runs the crunch command
    void execute()
    {
        arrPtr();
    }
};

crunchCommand getFun(string);
/**
*Welcomes the user to crunchLand, directing them on what to do.
*/
int intro()
{
    /*Variables*/
    string innercmmd;
    stringstream outercmmd;

    /*Assignments*/
    //In case the user does not understand that # is needed


    cout << "Enter a crunch command. lsc lists commands. desc describes commands. crnchID identifies commands. fisc does it all."<<endl;
    cout << "> ";

    getline(cin,innercmmd);

    if(innercmmd.find("#")!=-1)
    {
        getFun(innercmmd).execute();
    }
    else
    {
        outercmmd<<"#";//Adds # for getFUn
        outercmmd<<innercmmd;//Now has #plugin syntax
        getFun(outercmmd.str()).execute();//Executes crunch
    }
    return 0;
}

///Begin Core Utilities

/*
*********
*OUTLINE*
*********
* variables
*Various crunch commands
*lsc - Lists all commands
*crunchListed - Whether or not crunch name is found
*crunchID - Get the <ID> of a crunch command
*desc - Describe a crunch command (doc dump)
*fisc - List everything about every command
*isc - List everything about one command
*getFun - Return a function pointer equal to the requested command
*/

crunchCommand helloC ( &hello,          "hello",   "Outputs \"hello\" to the screen");
crunchCommand spewC  ( &spew,           "spew",    "Generates a password based on a phrase the user writes.");
crunchCommand quitC  ( &quit,           "quit",    "Calls exit(0), closing the entire program");
crunchCommand introC ( &intro,          "intro",   "Guides the user and teaches them about desc.");
crunchCommand descC  ( &desc,           "desc",    "Gets the documentation for a crunch command");
crunchCommand crncIdC( &crnchID,        "crunchID","Gets the Crunch ID for a command");
crunchCommand lscC   ( &lsc,            "lsc",     "Lists the crunch commands");
crunchCommand fiscC  ( &fisc,           "fisc",    "Gets the information for all crunch commands");
crunchCommand iscC   ( &isc,            "isc",     "Gets all the information for one crunch command");
crunchCommand pGameC ( &populationGame, "popGame", "Simulates a city during a time of disaster");
crunchCommand skipC  ( &skip,           "skip",    "Simulates a skipping rock on idle water");
crunchCommand launchC( &launch,         "launch",  "Simulates a fired object");
crunchCommand bballC ( &throwBall,      "bball",   "Play a ball game of precision");
crunchCommand bookyC ( &booky,          "booky",   "Distribute your reading workload");
crunchCommand termC  ( &terminal,       "terminal","Execute external commands, even nAI");

crunchCommand allCommands[members]= {helloC, spewC, quitC, introC, descC, crncIdC, lscC, fiscC, iscC, pGameC, skipC, launchC, bballC, bookyC, termC};

/**
*Core utility for listing crunch commands.
*/
int lsc()
{
    for(int index=0; index<members; index++)
        cout << "#"<<allCommands[index].funcName<<endl;
    return 0;
}

/**
*Core utility for seeing if a crunch command exists
*/
bool crunchListed(string cc)
{
    for(int index=0; index<members; index++)
    {
        if(cc.find(allCommands[index].funcName)!=-1)//Finds the string instead of matching
            return true;            //Logic is that the #  will mess the process up
    }
    return false;
}
/**
*Core utility for finding the id of a crunch command.
*/
int crnchID()
{
    /*Objects*/
    string command;//Original Command

    cout << "Command: ";
    cin  >> command;
    cout << endl;

    if(command.find("#")!=-1)
    {
        command=command.substr(1,command.length());//If it has a #, get rid of it.
    }

    for(int index=0; index<members; index++)
    {
        if(command==allCommands[index].funcName)
            cout << "Crunch ID: "<<index<<endl;
    }
    cout << endl;
    return 0;
}

/**
*Core utility for returning function docs.
*/
int desc()
{
    /*Objects*/
    string helper;

    cout << "Type an <id> or name. Like this: <34> or crunchName"<<endl;
    cout << "> ";
    getline(cin, helper);
    cout << endl;

    if(helper.find("<")!=-1&&helper.find(">")!=-1)//MUST be a set
        cout << allCommands[atoi(getBetween(helper, "<", ">").c_str())].documentation;//Gets the docs at <index>
    else   //BEGIN name search
    {
        if(helper.find("#")!=-1)
            helper=helper.substr(0, helper.length());

        for(int index=0; index<members; index++)
            if(allCommands[index].funcName==helper)
            {
                cout << allCommands[index].documentation;
                break;
            }
    }//END name search
    cout << endl;
    return 0;
}
/**
*Core utility that returns all of the information of all crunch commands.
*/
int fisc()
{
//Output EVERYTHING
    for(int index=0; index<members; index++)
    {
        cout << "Name: "<<allCommands[index].funcName<<endl;
        cout << "ID: "  <<index<<endl;
        cout << "Desc: "<<allCommands[index].funcName<<endl<<endl;
    }
    return 0;
}
/**
*Core utility that returns all of the information for a single crunch command.
*/
int isc()
{
    /*Objects*/
    string helper;//Line of input

    /*Primitives*/
    int idT;//Becomes <index>

    cout << "Type an <id> or name. Like this: <34> or crunchName"<<endl;
    cout << "> ";
    getline(cin, helper);
    cout << endl;

    if(helper.find("<")!=-1&&helper.find(">")!=-1)
    {
        idT = atoi(getBetween(helper, "<", ">").c_str());//Gets number in between <>'s
        cout << "Name: "<<allCommands[idT].funcName<<endl;
        cout << "ID: "  <<idT<<endl;
        cout << "Desc: "<<allCommands[idT].documentation<<endl<<endl;
    }
    else     //BEGIN name search
    {

        if(helper.find("#")!=-1)
            helper=helper.substr(1, helper.length());

        for(int index=0; index<members; index++)
        {
            if(allCommands[index].funcName==helper)
            {
                cout << "Name: "<<allCommands[index].funcName<<endl;
                cout << "ID: "  <<index<<endl;
                cout << "Desc: "<<allCommands[index].documentation<<endl<<endl;
                break;
            }
        }
    }//END name search
    return 0;
}
/**
  *Returns the function matching the specified name.
  *@param name - The name of the function.
  *@return fun - The crunch command to get
  */
crunchCommand getFun(string name)
{
    for(int index=0; index<members; index++)
    {
        if(name.substr(1,name.length())==allCommands[index].funcName)   //Gets rid of the crunch symbol
        {
            return allCommands[index];
        }//END name match if
    }//END full array search
}//END getFun()
