/*
*Verison 4.5 - mantic
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
string conf="No configuration file found";//The path to the configuration file
bool hasConf=false;//Whether or not the program has a configuration file

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
        hasConf=true;
    }

    bool isFalse(string line)
    {
        return (line.find("false")!=-1)?true:false;
    }
    void setOptions(string pathC)
    {
        short lines;
        ifstream reader(path.c_str());
        string line;
        lines=linec(path);

        for(int index=0; index<(int)lines; index++)
        {
            getline(reader, line);
            cout << line << endl;
            if(line.find("allow crunch")!=-1)
            {
                if(isFalse(line))
                    allow_crunch=false;
                else allow_crunch=true;

            }

            if(line.find("allow learn")!=-1)
            {
                if(isFalse(line))
                    want_learn=false;
                else want_learn=true;
            }

            if(line.find("allow explicit")!=-1)
            {
                if(isFalse(line))
                    allow_exl=false;
                else allow_exl=true;
            }
        }
        reader.close();
    }
    void loadConfig(bool&wl, bool&ac, bool&exl)
    {
        wl=want_learn;
        ac=allow_crunch;
        exl=allow_exl;

        cout << "LEARN: "<<wl<<endl;
        cout << "CRUNCH: "<<ac<<endl;
        cout << "EXPLIC: "<<exl<<endl;
    }
};
config pConfig;
void setConfFile(string arg)
{
    conf=arg;
    hasConf=true;

    pConfig.path=conf;
    pConfig.setOptions(conf);

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

//!Get the short name from options array
string getSn(int index)
{
    return allCLOptions[index].shortname;
}

//!Get the long name from options array
string getLn(int index)
{
    return allCLOptions[index].longname;
}
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
                allCLOptions[gnuCommands].exec(string(argv[index+1]));
            }

            if(found&&allCLOptions[gnuCommands].quitAfter)
            {
                exit(0);
            }
            else return true;
        }//END command search
    }//END arg list
    return false;
}//END function

//!Retrieve the configuration file's value
string getConfFile()
{
    return conf;
}
