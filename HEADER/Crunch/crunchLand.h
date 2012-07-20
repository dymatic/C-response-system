/*
  *Since the first version of AI and prior to the update there has been a feature
  *called "Crunch Commands". These are basically plugins taht can be called from the
  *command prompt of the main applications. These small plugins are all no-argument
  *and have some rules. They can ask for output, but they must ALL output two newlines
  *at the end of the function. The function added to this library MUST be added to the
  *array of function names. Also, the array holding the function pointers must be in the
  *EXACT same order that the array pointing to the names of the function are located in.
  *ALL return an int 0 to 1. 1 tells the program to stop immediately, not just the crunch
  *applet.

    TODO when adding a plugin: 1) Change the func point arr, 2) Change the funcNames arr, 3)
    change the docs arrays, 4) Change the members constant.
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
int (*getFun(string name))();

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
        getFun(innercmmd)();
    }
    else
    {
        outercmmd<<"#";//Adds # for getFUn
        outercmmd<<innercmmd;//Now has #plugin syntax
        getFun(outercmmd.str())();//Executes crunch
    }
    return 0;
}

///Begin Core Utilities

/*
*********
*OUTLINE*
*********
* variables
*arrPts - Array of function pointers
*funcNames - Array of function names
*docs - Array of short descriptions
*lsc - Lists all commands
*crunchListed - Whether or not crunch name is found
*crunchID - Get the <ID> of a crunch command
*desc - Describe a crunch command (doc dump)
*fisc - List everything about every command
*isc - List everything about one command
*getFun - Return a function pointer equal to the requested command
*/

/*Arrays*/
int (*arrPts[members])() = {&hello,&spew,&quit,&intro,&desc,&crnchID,&lsc,&fisc,&isc,&populationGame,&skip,&launch,&throwBall,
                            &booky, &terminal
                           };

string funcNames[members]= {"hello", "spew", "quit","intro", "desc","crnchID","lsc","fisc","isc","popGame","skip","launch","bball","booky","terminal"
                           };

string docs[members]= {"Outputs \"hello\" to the screen","Generates a password based on a phrase user direction.",
                       "Calls exit(0);.","Guides the user","Gets the documentation for a command", "Gets the Crunch ID for a command",
                       "Lists the crunch commands","Gets the information for all crunch commands","Gets the information of a single crunch command.",
                       "Simulates a city durting a time of disaster.","Simulates a skipping rock","Simultes a fired object","Play a ball game of precision.",
                       "Distribute your workload","Runs the system shell, allowing you to execute external commands."
                      };//Stores documentation for each plugin. If an author does not document their work, it will throw the whole system off.
// If you do not plan on documenting, please leave a space and remember to change members.

/**
*Core utility for listing crunch commands.
*/
int lsc()
{
    for(int index=0; index<members; index++)
        cout << "#"<<funcNames[index]<<endl;
    return 0;
}

/**
*Core utility for seeing if a crunch command exists
*/
bool crunchListed(string cc)
{
    for(int index=0; index<members; index++)
    {
        if(cc.find(funcNames[index])!=-1)//Finds the string instead of matching
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
        if(command==funcNames[index])
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
        cout << docs[atoi(helper.substr((helper.find("<")+1),helper.find(">")-1).c_str())];//Gets the docs at <index>
    else   //BEGIN name search
    {
        for(int index=0; index<members; index++)
            if(funcNames[index]==helper)
            {
                cout << docs[index];
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
        cout << "Name: "<<funcNames[index]<<endl;
        cout << "ID: "  <<index<<endl;
        cout << "Desc: "<<docs[index]<<endl<<endl;
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
        idT = atoi(helper.substr((helper.find("<")+1),helper.find(">")-1).c_str());//Gets number in between <>'s
        cout << "Name: "<<funcNames[idT]<<endl;
        cout << "ID: "  <<idT<<endl;
        cout << "Desc: "<<docs[idT]<<endl<<endl;
    }
    else   //BEGIN name search
    {

        for(int index=0; index<members; index++)

            if(funcNames[index]==helper)
            {
                cout << "Name: "<<funcNames[index]<<endl;
                cout << "ID: "  <<index<<endl;
                cout << "Desc: "<<docs[index]<<endl<<endl;
                break;
            }
    }//END name search
}
/**
  *Returns the function matching the specified name.
  *@param name - The name of the function.
  *@return *fun - The pointer to the function
  */
int (*getFun(string name))()
{
    for(int index=0; index<members; index++)
    {
        if(name.substr(1,name.length())==funcNames[index])   //Gets rid of the crunch symbol
        {
            return arrPts[index];
        }//END name match if
    }//END full array search
}//END getFun()
