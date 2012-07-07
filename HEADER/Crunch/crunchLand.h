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
const int members=9;
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
    string innercmmd;
    stringstream outercmmd;
    outercmmd<<"#";//In case the user does not understand that # is needed

    cout << "Enter a crunch command. lsc lists commands. desc describes commands. crnchID identifies commands. fisc does it all."<<endl;
    cout << "> ";

    getline(cin,innercmmd);

    if(innercmmd.find("#")==-1) {
        outercmmd<<innercmmd;
        getFun(outercmmd.str())();
    } else getFun(innercmmd)();
    return 0;
}
/////////////////////////////////////////////////////////////////////BEGIN COREUTILS
/*Arrays*/
int (*arrPts[members])() = {&hello,&spew,&quit,&intro,&desc,&crnchID,&lsc,&fisc,&isc};
string funcNames[members]= {"hello", "spew", "quit","intro", "desc","crnchID","lsc","fisc","isc"};
string docs[members]= {"Outputs \"hello\" to the screen","Generates a password based on a phrase user direction.",
                       "Calls exit(0);.","Guides the user","Gets the documentation for a command", "Gets the Crunch ID for a command",
                       "Lists the crunch commands","Gets the information for all crunch commands","Gets the information of a single crunch command."
                      };

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
    for(int index=0; index<members; index++) {
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
    string command;

    cout << "Command: ";
    cin  >> command;
    cout << endl;

    for(int index=0; index<members; index++) {
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
    cout << "MADE IT TO DESK"<<endl;
    string helper;
    cout << "Type an <id> or name. Like this: <34> or crunchName"<<endl;
    cout << "> ";
    getline(cin, helper);
    cout << endl;

    if(helper.find("<")!=-1&&helper.find(">")!=-1)
        cout << docs[atoi(helper.substr((helper.find("<")+1),helper.find(">")-1).c_str())];//Gets number in between <>'s
    else { //BEGIN name things
        for(int index=0; index<members; index++)
            if(funcNames[index]==helper) {
                cout << docs[index];
                break;
            }
    }//END name search
    return 0;
}
/**
*Core utility that returns all of the information of all crunch commands.
*/
int fisc(){

for(int index=0; index<members;index++)
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
int isc(){
    string helper;
    int idT;
    cout << "Type an <id> or name. Like this: <34> or crunchName"<<endl;
    cout << "> ";
    getline(cin, helper);
    cout << endl;

    if(helper.find("<")!=-1&&helper.find(">")!=-1){
        idT = atoi(helper.substr((helper.find("<")+1),helper.find(">")-1).c_str());//Gets number in between <>'s
   cout << "Name: "<<funcNames[idT]<<endl;
   cout << "ID: "  <<idT<<endl;
   cout << "Desc: "<<docs[idT]<<endl<<endl;
    }
    else { //BEGIN name things

        for(int index=0; index<members; index++)

            if(funcNames[index]==helper) {
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
    for(int index=0; index<members; index++) {
        if(name.substr(1,name.length())==funcNames[index]) { //Gets rid of the crunch symbol
            return arrPts[index];
        }
    }
}
