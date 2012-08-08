/*
  *AI 4 - Complete Bump
  *This is free sofware with absolutely no warranty, expressed or implied.
  *The program is licensed under the GNU General Public License revision 2.
  *If you did not receive a copy of the GNU general public license, contact the
  *software distributor. The exact text of the GNU General Public License is always available
  * here: <http://www.gnu.org/licenses/old-licenses/lgpl-2.0.html>
  */
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>

#include "nsl.h"
using namespace std;

/*STATS*/
int wing;//Chance to guess
int globalCounter;//Position in arrays
/*STRINGS*/
string fileName;//Path to learn file

string input [10000];
string output[10000];

/*RESOURCES*/

/*FUNCTION IMPLEMENTATIONS*/
/**
*At setupStrings() there can be a wildcard string where one response is chosen over another.
*%is the delimiter for the wildcard.
*This function assumes old_new1%new2%... syntax
*/
bool hasWildCard(string message)
{
    if(message.find("%")!=-1)
        return true;

    return false;
}

vector<string> splitOn(string, string);
/**
*Gets one output from the wildcard bunch.
*@param message - The string to split from
*@return output - The output taken from the wildcards
*/
string getWildCard(string message)
{
    if(message.find("_")!=-1)
        message=message.substr(message.find("_")+1, message.length());

    vector<string> wildcards = splitOn(message, "%");

//Nate Debug
    return wildcards[rand()%wildcards.size()];
}
/**
*Adds a string to the arrays.
*@param string - The string in in_out syntax.
*/
void addStr(string msg)
{
    input[globalCounter]=msg.substr(0,msg.find("_"));

    if(!hasWildCard(msg))
        output[globalCounter]=msg.substr(msg.find("_")+1,msg.length());
    else output[globalCounter]=getWildCard(msg);

    globalCounter++;
}

/**
*Adds the two strings to the two IO arrays.
*Can handle wildcard strings in output.
*@param in - The string to add to the input
*@param out - The string to add to the output arrays.
*/
void addStr(string in, string out)
{
    input[globalCounter] = in;

    if(!hasWildCard(out))
        output[globalCounter]=out.substr(out.find("_")+1,out.length());
    else output[globalCounter]=getWildCard(out);

    globalCounter++;
}

/**
*Adds an array of inputs with the same output to the arrays.
*@param *in - The pointer of arrays to add
*@param out - The output
*@param argInput - The number of inputs to write
*/
void addStrArr(string in[], string out, int argInput)
{
    for(int index=0; index<argInput; index++)
    {
        input[globalCounter]=in[index];

        if(!hasWildCard(out))
            output[globalCounter]=out;
        else output[globalCounter]=getWildCard(out);
        globalCounter++;
    }
}
/**
*Adds a vector of strings into memory.
*@param inputs - The vector of inputs
*@param out - The output to put on the output arrays.
*/
void addStrVec(vector<string> inputs, string out)
{
    for(int index=0; index<inputs.size(); index++)
    {
        input[globalCounter]=inputs[index];

        if(!hasWildCard(out))
            output[globalCounter]=out;
        else output[globalCounter]=getWildCard(out);
        globalCounter++;
    }
}
/**
*Splits a string on a given character, returning an array equal to the split string.
*@param message - The string to split from
*@param delim - What to split on
*@return vStr - The vector of strings split from the message
*/
vector<string> splitOn(string message, string delim)
{

    vector<string> rString(0);

    for(int index=0; message.find(delim)!=-1; index++)
    {
        rString.push_back(message.substr(0, message.find(delim)));
        message = message.substr(message.find(delim)+1, message.length());
    }

    if(message.find("_")!=-1)//splitOn should not be used with whole IO identifier strings
        message = message.substr(0, message.find("_")-1);

    rString.push_back(message);
    return rString;
}

/**
  *Loads a learn file into RAM for use with response formulation.
  *Syntax for the learning file is input_output
  *@param file - The path to the leaning file
  *@param wingNum - The chance to guess what the user wants without knowing
  */
void setupStrings(string file, int wingNum)
{
    /*Objects*/
    ifstream reader(file.c_str());//Learn file
    string whole;//An entire line from the learn file. Overwritten frequently

    /*Initializations*/
    globalCounter=0;//Number of *_outputs to write to ARRAYS (not in file)
    fileName=file;//Global learn file path

    for(int index=0; index<linec(file); index++)
    {

        getline(reader,whole);//Get line

        rmComment(whole, "~");//Strip comments

        if(whole.find("$")!=-1)//Add multiple inputs to one output
            addStrVec(splitOn(whole, "$"), whole.substr(whole.find("_")+1, whole.length()));//May have wildcard

        else
            addStr(whole);//May have wildcard
    }//END for
    wing=wingNum;
}

/**
*Causes explicit learning. This should be triggerd with a is_a statement.
*For instance, that elephant IS fat. What is that elephant? fat.
*@param toParse - The string to learn from
*/
void exlLearn(string toParse)
{
    fstream inFile;//The learn file, assigned using globals
    inFile.open(fileName.c_str(),fstream::in|fstream::out|fstream::app);

    inFile << endl;
    string token;//Subject
    stringstream toWrite;
    string toSOn;

    if(toParse.find(" is ")!=-1)
    {
        toSOn=" is ";
    }
    else if(toParse.find(" are ")!=-1)
    {
        toSOn=" are ";
    }

    token=toParse.substr(0, toParse.find(toSOn));

    toWrite << "what"<<toSOn<<token;

    inFile << toWrite.str()<<"$"<<token<<"_"<<toParse;
}

/**
  *Uses the loaded strings to formulate a response.
  *If the strings do not have it, the program will "wing" it.
  *In the worst possible case, it will return special text to main
  *that forces a learn to take place.
  *@param toReplyTo - The message to reply to.
  *@return response - The response, "learn(toReplyTo)" if a learning is required. The
  *                  thought process here is that main or a wrapper can handle it (makes function portable).
  *                  Since version 4.0, this function can return "exlLearned" if it has been
  *                  explicitly taught.
  */
string formulateResponse(string toReplyTo)
{
    /*Primitives*/
    bool good=false;//Whether or not the statement was found.
    /*Objects*/
    string buff;//Santized toReplyTo

    /*Initializations*/
    buff = sanitizeInput(toReplyTo);

    for(unsigned int index=0; index<globalCounter; index++)
    {
        if(buff.find(input[index])!=-1&&input[index].length()>1)   //Exact match (input file INSIDE buff)
        {
            return output[index];
            good=true;
        }

        else if((input[index].length()==buff.length())&&(rand()%wing==5))   //WING
        {
            return output[index];//If the lengths are the same
            good=true;
        }
    }

    if(toReplyTo.find("is")!=-1||toReplyTo.find("are")!=-1)//EXLlearn
    {
        return "exlLearned";
    }
//This will only execute if proper output is not found
    if(!good)
    {
        return "learn(toReplyTo)";//Interpreted in main
    }
}


/**
  *Causes the bot to learn from its mistakes.
  *@param toLearn - The message that tripped it up
  *@param learned - The message to implant in the file. If
  *you are using interactive mode, leave this blank
  *@return learned - Learned is returned to make output better.
  */
string learn(string toLearn, string learned)
{

    /*Objects*/
    fstream inFile;//The learn file

    /*Intializations*/
    inFile.open(fileName.c_str(),fstream::in|fstream::out|fstream::app);


    if(learned.length()<=1)   //Interactive Mode
    {
        cout << "What I should say: ";
        getline(cin,learned);
        cout << endl;
    }//END if

    inFile<<endl<<toLearn<<"_"<<learned;//Writes in prompt_result syntax
    inFile.close();

    addStr(toLearn,learned);//The program, by default, makes use of the learned phrase right away

    return learned;
}

