/*
  *AI 3 - Complete Rewire
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
using namespace std;

/*STATS*/
int Gmembers;
int wing;//Chance to guess

/*STRINGS*/
string fileName;//Path to learn file

string input [10000];
string output[10000];

/*RESOURCES*/
fstream fileWriter("learn.txt");

/*FUNCTION HEADERS*//*

 //System
void setupStrings(string file);
void clearMemory();
void crunch();

 //Output
string formulateResponse(string input);
string learn(std::string,std::string);

 //Utility
int linec(string file);

/*FUNCTION IMPLEMENTATIONS*/
//!Not my work
void replaceAll(std::string& str,  std::string& from,  std::string& to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}
/**
*Makes the input conform to a certain set of standards.
*Whitespace is trimmed and it is made lowercase.
*/
string sanitizeInput(string input)
{
    char letters[input.length()];
    string returnMessage;

    for(unsigned int index=0; index<input.length(); index++)
        letters[index]=input.at(index);


    for(unsigned int index=0; index<input.length(); index++)
        letters[index]=tolower(letters[index]);

    for(unsigned int index=0; index<input.length(); index++)
        returnMessage+=letters[index];
    return returnMessage;
}
/**
  *Counts the number of lines in a file.
  *Depending on the size of the file, this is a lengthy process.
  *@param file - The file path to the target file.
  *@return counter - The number of lines in the file.
  */
int linec(string file)
{
    ifstream fileReader(file.c_str());
    string buff;

    int counter=0;

    for(counter=0; getline(fileReader,buff); counter++)
        ;
    return counter;
}

/**
  *Loads a learn file into RAM for use with response formulation.
  *Syntax for the learning file is input_output
  *@param file - The path to the leaning file
  *@param wingNum - The chance to guess what the user wants without knowing
  */
void setupStrings(string &file, int wingNum)
{
    ifstream reader(file.c_str());

    string whole;
    string part1;

    fileName=file;

    for(int index=0; index<linec(file); index++)
    {
        getline(reader,whole);

        input[index] = whole.substr(0,whole.find("_"));
        output[index]=whole.substr(whole.find("_")+1,whole.length());

    }//END for
    Gmembers=linec(file);

    wing=wingNum;
}

/**
  *Returns the RAM used by the strings to the memory.
  *The program will be unusable after this until setupStrings() is manually called.
  */
void clearMemory()
{
    delete &input;
    delete &output;
    delete &fileName;
    delete &members;
}

/**
  *Uses the loaded strings to formulate a response.
  *If the strings do not have it, the program will "wing" it.
  *In the worst possible case, it will return special text to main
  *that forces a learn to take place.
  *@param toReplyTo - The message to reply to.
  *@return response - The response, "learn(toReplyTo)" if a learning is required.
  */
string formulateResponse(string toReplyTo)
{
    bool good=false;//Whether or not the statement was found.
    string buff = sanitizeInput(toReplyTo);

    for(unsigned int index=0; index<Gmembers; index++)
    {
        if(input[index].find(buff)!=-1)
        {
            return output[index];//If an exact match is found.
            good=true;
        }

        else if((input[index].length()==buff.length())&&(rand()%Gmembers==5)) //Wing
        {
            return output[index];//If the lengths are the same
            good=true;
        }
    }
//This will only execute if proper output is not found
    if(!good)
    {
        return "learn(toReplyTo)";
    }
}


/**
  *Causes the robot to learn from its mistakes.
  *@param toLearn - The message that tripped it up
  *@param learned - The message to implant in the file. If
  *you are using interactive mode, leave this blank
  *@return learned - Learned is returned to make output better.
  */
string learn(string toLearn, string learned)
{
    fstream inFile;
    inFile.open(fileName.c_str(),fstream::in|fstream::out|fstream::app);

    if(learned.length()<=1) //Interactive Mode
    {
        cout << "What I should say: ";
        getline(cin,learned);
        cout << endl;
    }//END if

    inFile<<endl<<toLearn<<"_"<<learned;
    inFile.close();
    setupStrings(fileName,wing);
    return learned;
}

