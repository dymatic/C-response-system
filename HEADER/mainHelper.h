/*
*Verison 4.7 - mantic
*mainHelper.h
*
*Mainhelper helps main, thus the name. Utilities for parsing command
*line options are the application startup go here. Anything relating
*to the configuration file also go here as that relates to the startup
*of the application.
*/
#include <fstream>
#include <iostream>
using namespace std;
const int gnus=3;//How many command line options there are
const string defPath = "No configuration file loaded";//The default path that conf uses

//*Configuration file utilities*/
const int options=4;//The number of options in the configuration file
string optTrigs[options]= {"allow learn",
                           "allow crunch",
                           "allow explicit",
                           "assume crucial"
                          };//What
bool settings[options];
string conf=defPath;//The path to the configuration file

//BEGIN CONFIGURATION FILE UTILITIES
struct config
{
    bool want_learn;//Can the bot learn?
    bool allow_crunch;//Can a user execute crunch commands?
    bool allow_exl;//Can the bot quietly learn?

    string path;//Path to the configuration file

    config()
    {
        path=conf;
    }

//!Does the line contain "false"?
    bool isFalse(string line)
    {
        return (line.find("false")!=-1)?true:false;
    }

    /**
    *Sets the structure's internal options based on a file.
    *To specify the file set config.path
    */
    void setOptions()
    {
        ifstream reader(path.c_str());//Configuration file stream
        string line;//Used for individual line from reader's stream

        for(int index=0; getline(reader, line); index++)//Iterate through lines
        {

            for(int sindex=0; sindex<options; sindex++)//Iterate through arguments and match it with line
                if(line.find(optTrigs[sindex])!=-1)
                {
                    if(isFalse(line))
                        settings[sindex]=false;
                    else settings[sindex]=true;
                }
        }
        reader.close();
    }
    void loadConfig(bool&wl, bool&ac, bool&exl, bool &asc)
    {
        wl= settings [0];
        ac= settings [1];
        exl=settings [2];
        asc=settings [3];
        cout<< "Loading configuration settings"<<endl<<endl;
    }
};
config pConfig;
void setConfFile(string arg)
{
    pConfig.path=arg;
    pConfig.setOptions();

}
struct cLineOption
{
    string longname;//The long -- name of the command.
    string shortname;//The short letter symbol of a command.
    bool quitAfter;//Whether or not to quit after execution
    bool parseForward;//Whether or not to take an argument from the next token.

    void (*gcmd)(string);//The command to execute
//!Creates a command line option with a longname, a shortname, quit after, parse forward, and f(str)
    cLineOption(string ln, string sn, bool qA, bool pF, void (*gnuFun)(string))
    {
        longname=ln;
        shortname=sn;
        quitAfter=qA;
        parseForward=pF;
        gcmd=gnuFun;
    }

    /**
    *If the shortname or the longname are found
    *@param arg - The string to search in
    *@return true if found, false otherwise
    */
    bool ifMatches(string arg)
    {
        if(arg.find(shortname)!=-1||arg.find(longname)!=-1)
            return true;
        return false;
    }

    void exec(string arg)
    {
        gcmd(arg);
    }
};

//                       long       short quit  take
cLineOption clVersion("--version",  "-v", true, false, &versionGet);
cLineOption clHelp(   "--help",     "-h", true, false, &helpGet);
cLineOption clSetCF(  "--set-conf", "-c", false, true, &setConfFile);

cLineOption allCLOptions[gnus] = {clVersion, clHelp, clSetCF};

/**
*Handles the command line arguments of main.
*@param argc - Number of args
*@param argv - The arguments
*@return handled - If an argument was found
*/
bool handleArgs(int argc, char**argv)
{
    bool found; //If the command is found, regardless of array options

    for(int index=1; index<argc; index++)//Iterate through args
    {
        /*
        *LOOP OUTLINE
        *Iterate through arguments
        *Iterate through commands, comparing them to argument
        *Execute command if it is found, go to next argument otherwise
        *Exit if that is specified
        *Return false if nothing was done
        */
        for(int gnuCommands=0; gnuCommands<gnus; gnuCommands++)//Iterate through commands on one arg
        {
            found=false;


            if(allCLOptions[gnuCommands].ifMatches(string(argv[index])))
            {
                found=true;
            }
            else continue;

            if(found&&!allCLOptions[gnuCommands].parseForward)
                allCLOptions[gnuCommands].exec(string(argv[index]));//Executes the command that matches the name

            if(found&&allCLOptions[gnuCommands].parseForward)
            {
                allCLOptions[gnuCommands].exec(string(argv[index+1]));//Parsed forward to next option
            }

            if(found&&allCLOptions[gnuCommands].quitAfter)
            {
                exit(0);
            }
            else return true;//The command was found, executed, but did not want to quit

        }//END command search
    }//END arg list
    return false;
}//END function
