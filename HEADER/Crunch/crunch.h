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
string cc;

/**
  *Determines whether or not a command is a crunch command.
  *@param ccmd - The command to parse
  *@return true if it is a command, false otherwise.
  */
bool isCrnchCmd(string ccmd)
{
    if(ccmd.length()>1)
    {

        if(ccmd.find("#")!=-1&&ccmd.find(" ")==-1&&crunchListed(ccmd))
            return true;
    }//END body if
    return false;
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
        getFun(cc)();
    }
    else
        getFun("#intro")();
}
