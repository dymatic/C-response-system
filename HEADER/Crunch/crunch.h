#include <iostream>
#include <cstdlib>
#include "crunchLand.h"
using namespace std;
/*
  *Provides a programmable set of functions that
  *work as plugins for the main program. They are run with
  *#plugin syntax from the main prompt.
  */

/*Variables*/
string cc;//The crunch command.

/**
  *Determines whether or not a command is a crunch command.
  *@param ccmd - The command to parse
  *@return true if it is a command, false otherwise.
  */
bool isCrnchCmd(string ccmd)
{
    if(ccmd.length()>1)
    {

        if(ccmd.find("#")!=-1&&ccmd.find(" ")==-1&&crunchListed(ccmd))//Cannot have space, must be listed
            return true;
    }//END body if
    return false;//The text was NOT a crunch command
}

/**
  *Loads the crunch command into the buffer.
  *@param ccmd - The crunch command
  */
void loadCrunchCommand(string ccmd)
{
    cc=ccmd;
}

/**
  *Runs the crunch command from the master crunch library. The library
  *has an array of names that will be searched to find the appropriate function.
  */
void executeCrunch()
{
    if(cc.length()>0)
    {
        getFun(cc).execute();//Executes the crunch command with the name of cc.
    }
    else
        getFun("#intro").execute();//Help function
}
