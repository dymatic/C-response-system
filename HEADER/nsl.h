/*
*This software is licensed under the Noran Restricted Public License (0.02)
*Author: Norton "dymatic" Jenkins <kzzear@hotmail.com>
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
using namespace std;
/**
*Finds the number of lines in a file.
*@param filename - The path to the file
*@return lines - The number of lines in the file
*/
int linec(string filename)
{
    ifstream file(filename.c_str());
    int lines=0;
    string buffer;

    for(; getline(file,buffer);)
    {
        lines++;
    }
    file.close();
    return lines;
}

/**
*Orders the file by file length.
*@param filepath - The path to the file
*/
void orderFile(string filepath)
{

    ifstream file(filepath.c_str());
    int nlines=linec(filepath);

    string lines[nlines];

    for(int index=0; index<nlines; index++) //Make container
        getline(file,lines[index]);

    for(int index=0; index<nlines-1; index++) //Iterate through positions
    {
        while(lines[index].length()<lines[index+1].length())
        {
            string buffer;
            buffer=lines[index];

            lines[index]=lines[index+1];
            lines[index+1]=buffer;

            if(index>0)
                index--;
        }
    }
    file.close();
    ofstream writer(filepath.c_str());
    for(int index=0; index<nlines; index++)
        writer<<lines[index]<<endl;
    writer.close();
}
/**
*A utility for generating passwords.
*They can contain uppercase, lowercase, and numbers.
*READ: YOU MUST CALL srand(TIME(NULL)) from cstdlib and time.h for this to work.
*@param labels - What kinds of characters to include. This is a string with numbers from 0 to 3.
* 0 = lowercase, 1=capital, 2=numbers, 3=symbols. They can be grouped like this: 032
*@param length - How long the password should be.
*@return psswd - The password
*/
string spew(string labels, int intensity)
{
    stringstream buffer;

    string alphaL  = "abcdefghijklmnopqrstuvwxyz";
    string alphaC  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string numeric = "0123456789";
    string symbols = "`~!@#$%^&*()_+-=,<.>/?; :'\"\\][{}";

    for(int index=0; index<intensity; index++)
    {
        if(labels.find("0")!=-1)//Lower-case level
            buffer << alphaL.at(rand()%alphaL.length());

        if(labels.find("1")!=-1)//Upper-case level
            buffer << alphaC.at(rand()%alphaC.length());

        if(labels.find("2")!=-1)//Numeric level
            buffer << numeric.at(rand()%numeric.length());

        if(labels.find("3")!=-1)//Symbol level
            buffer << symbols.at(rand()%symbols.length());
    }
    return buffer.str();
}
/**
*Finds the number of times a string occurs in a larger string.
*@param toFindIn - The string to look in
*@param lookingFor - The string you are looking for
*/
int numberOf(string toFindIn, string lookingFor)
{
    int counter=0;
    string buff;
    while(toFindIn.find(lookingFor)!=-1)
    {
        counter++;
        buff=toFindIn.substr((toFindIn.find(lookingFor)+1),toFindIn.length());//Bump beyond lookingFor
        toFindIn=buff;
    }
    return counter;
}

/**
*Replaces all of the text in a string with specified text.
*@param str - The string to change in
*@param from - The text to replace in str
*@param to - The string that from changes to in str
*/
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
*@param input - The string to sanitize.
*@return rMsg - The sanitized message
*/
string sanitizeInput(string input)
{
    string punc[14]= {".",","," ",":",";","(",")","*","^","_","-","[","]","?"};//To remove
    string whitespace="";


    string returnMessage;

    for(unsigned int index=0; index<14; index++)//Removes punctuation. Note undeclared constant
        replaceAll(input,punc[index],whitespace);

    for(unsigned int index=0; index<input.length(); index++)//Makes lowercase
        returnMessage+=(tolower(input.at(index)));

    return returnMessage;
}

/**
*Splitstr is a very important function.
*This finds text in between two magic characters and removes it from the string.
*
*Here it is used for comments in a learn file.
*@param toSplit   - The string to remove sensitive strings from.
*@param magicahar - The character used in the code file to denote a sensitive string. "$" is the standard.
*/
void splitstr(string &toSplit, string magichar)
{
    if(toSplit.find(magichar)!=-1)
    {
        /*Objects*/
        stringstream buffer;

        string copy;//A copy of toSplit

        /*Initializations*/
        copy=toSplit;

        /*Body*/
        if(toSplit.find(magichar)!=-1)//Put the text before first magichar in buffer
            buffer<<copy.substr(0,toSplit.find(magichar));

        if(copy.find(magichar)!=-1)//Make copy equal to the whole string minus the part up to the first magichar
            copy=copy.substr(toSplit.find(magichar)+1,toSplit.length());

        if(copy.find(magichar)!=-1)//Put the position of the magichar+1 in the buffer.
            buffer<<copy.substr(copy.find("~")+1,copy.length());

        toSplit=buffer.str();
    }//End if
}

/**
*Removes a comment in between ~~s.
*@param comment - The reference to the string containing a comment
*@param delim   - The deliminator (~ is default)
*/
void rmComment(string &comment, char *delim)
{
    if(comment.find(delim)!=-1&&numberOf(comment,delim)%2==0)   //Delims have to be even ex: ~remove me~
    {
        for(int index=0; index<numberOf(comment,delim)/2; index++)   // /2 because splitstr() removes both.
        {
            splitstr(comment,delim);
        }

    }
}
