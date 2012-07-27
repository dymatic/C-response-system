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
int globalCounter;//Position in arrays
/*STRINGS*/
string fileName;//Path to learn file

string input [10000];
string output[10000];

/*RESOURCES*/

/*FUNCTION IMPLEMENTATIONS*/
//!Not my work
void replaceAll(std::string& str,  std::string& from,  std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
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
string sanitizeInput(string input) {
    string punc[14]= {".",","," ",":",";","(",")","*","^","_","-","[","]","?"};//To remove
    string whitespace;//


    string returnMessage;

    for(unsigned int index=0; index<14; index++)//Removes punctuation
        replaceAll(input,punc[index],whitespace);

    for(unsigned int index=0; index<input.length(); index++)//Makes lowercase
        returnMessage+=(tolower(input.at(index)));

    return returnMessage;
}
/**
  *Counts the number of lines in a file.
  *Depending on the size of the file, this is a lengthy process.
  *@param file - The file path to the target file.
  *@return counter - The number of lines in the file.
  */
int linec(string file) {
    /*Objects*/
    ifstream fileReader(file.c_str());
    string buff;

    int counter=0;

    for(counter=0; getline(fileReader,buff); counter++)
        ;
    return counter;
}
/**
*Finds the number of times a string occurs in a larger string.
*@param toFindIn - The string to look in
*@param lookingFor - The string you are looking for
*/
int numberOf(string toFindIn, string lookingFor) {
    /*Primitives*/
    int counter;

    /*Objects*/
    string buff;

    /*Initializations*/
    counter=0;

    while(toFindIn.find(lookingFor)!=-1) {
        counter++;

        buff=toFindIn.substr((toFindIn.find(lookingFor)+1),toFindIn.length());//Bumps past character
        toFindIn=buff;
    }
    return counter;
}

/**
*Splitstr is a very important function.
*This finds text in between two magic characters and removes it from the string.
*
*Here it is used for comments in a learn file.
*@param toSplit   - The string to remove sensitive strings from.
*@param magicahar - The character used in the code file to denote a sensitive string. "$" is the standard.
*/
void splitstr(string &toSplit, string magichar) {
    if(toSplit.find(magichar)!=-1) {
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
*Adds a string to the arrays.
*@param string - The string in in_out syntax.
*/
void addStr(string msg) {
    input[globalCounter]=msg.substr(0,msg.find("_"));
    output[globalCounter]=msg.substr(msg.find("_")+1,msg.length());

    globalCounter++;
}

/**
*Adds the two strings to the two IO arrays.
*@param in - The string to add to the input
*@param out - The string to add to the output arrays.
*/
void addStr(string in, string out) {
    input[globalCounter] = in;
    output[globalCounter] = out;

    globalCounter++;
}

/**
*Adds an array of inputs with the same output to the arrays.
*@param *in - The pointer of arrays to add
*@param out - The output
*@param argInput - The number of inputs to write
*/
void addStrArr(string in[], string out, int argInput) {
    for(int index=0; index<argInput; index++) {
        input[globalCounter]=in[index];
        output[globalCounter]=out;
        globalCounter++;
    }
}

/**
*Splits a string on a given character, returning an array equal to the split string.
*@param message - The string to split from
*@param delim - What to split on
*@param argc - The number of strings to have in the array
*@return *strings - The array containing the strings
*//*
string** splitOn(string message, char *delim) {
    string *rString[numberOf(message, string(delim))+1];

    for(int index=0; index<numberOf(message, string(delim)); index++) {
        *rString[index]=message.substr(0, message.find(delim));

        message = message.substr(message.find(delim)+1, message.length());//Coming soon to a repo near you!
    }
    *rString[numberOf(message, string(delim))] = message;

    return rString;
}*/
/**
*Removes a comment in between ~~s.
*@param comment - The reference to the string containing a comment
*@param delim   - The deliminator (~ is default)
*/
void rmComment(string &comment, char *delim) {
    if(comment.find(delim)!=-1&&numberOf(comment,delim)%2==0) { //Delims have to be even ex: ~remove me~
        for(int index=0; index<numberOf(comment,delim)/2; index++) { // /2 because splitstr() removes both.
            splitstr(comment,delim);
        }

    }
}
/**
  *Loads a learn file into RAM for use with response formulation.
  *Syntax for the learning file is input_output
  *@param file - The path to the leaning file
  *@param wingNum - The chance to guess what the user wants without knowing
  */
void setupStrings(string &file, int wingNum) {
    /*Objects*/
    ifstream reader(file.c_str());//Learn file

    string whole;//An entire line from the learn file. Overwritten frequently/

    /*Primitives*/
    globalCounter=0;//Number of *_outputs to write to ARRAYS (not in file)

    /*Intializations*/
    fileName=file;//Global learn file path

    for(int index=0; index<linec(file); index++) {
        /*This loop does:
         0 Gets line
         1 Strips comments
         2 Writes multiple inputs to one output
         3 Writes to the learn file
         4 Sets filename and wing global variables*/

        getline(reader,whole);

        rmComment(whole, "~");
        int tokens=numberOf(whole,"$");
        if(whole.find("$")!=-1) {
            /*$ seperates input that warrant the same output,
              like "hi" and "hey" both returning "Hello".*/

            string arr[numberOf(whole, "$")];//Array of Inputs

            for(int tindex=0; whole.find("$")!=-1; tindex++) {
                arr[tindex]=whole.substr(0, whole.find("$"));
                whole=whole.substr(whole.find("$")+1, whole.length());
            }

            addStrArr(arr, (whole.substr(whole.find("_")+1,whole.length())), tokens);
            addStr(whole);
        }//END mult IF

        else
            addStr(whole);
    }//END for
    Gmembers=globalCounter;

    wing=wingNum;
}

/**
  *Returns the RAM used by the strings to the memory.
  *The program will be unusable after this until setupStrings() is manually called.
  */
void clearMemory() {
    delete &input;
    delete &output;
    delete &fileName;
    delete &Gmembers;
}
/**
*Causes explicit learning. This should be triggerd with a is_a statement.
*For instance, that elephant IS fat. What is that elephant? fat.
*@param toParse - The string to learn from
*/
void exlLearn(string toParse) {
    fstream inFile;//The learn file, assigned using globals
    inFile.open(fileName.c_str(),fstream::in|fstream::out|fstream::app);

    inFile << endl;
    string token;//Subject
    stringstream toWrite;
    string toSOn;

    if(toParse.find(" is ")!=-1) {
        toSOn=" is ";
    } else if(toParse.find(" are ")!=-1) {
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
  *                  thought process here is that main can handle it (makes function portable).
  *                  Since version 4.0, this function can return "exlLearned" if it has been
  *                  explicitly taught.
  */
string formulateResponse(string toReplyTo) {
    /*Primitives*/
    bool good=false;//Whether or not the statement was found.
    /*Objects*/
    string buff;//Santized toReplyTo

    /*Initializations*/
    buff = sanitizeInput(toReplyTo);

    for(unsigned int index=0; index<Gmembers; index++) {
        if(buff.find(input[index])!=-1&&input[index].length()>1) { //Exact match (input file INSIDE buff)
            return output[index];
            good=true;
        }

        else if((input[index].length()==buff.length())&&(rand()%wing==5)) { //WING
            return output[index];//If the lengths are the same
            good=true;
        }
    }

    if(toReplyTo.find("is")!=-1||toReplyTo.find("are")!=-1) {
        return "exlLearned";
    }
//This will only execute if proper output is not found
    if(!good) {
        return "learn(toReplyTo)";//Interpreted in main
    }
}


/**
  *Causes the robot to learn from its mistakes.
  *@param toLearn - The message that tripped it up
  *@param learned - The message to implant in the file. If
  *you are using interactive mode, leave this blank
  *@return learned - Learned is returned to make output better.
  */
string learn(string toLearn, string learned) {

    /*Objects*/
    fstream inFile;//The learn file

    /*Intializations*/
    inFile.open(fileName.c_str(),fstream::in|fstream::out|fstream::app);

    /*Function Body*/
    if(learned.length()<=1) { //Interactive Mode
        cout << "What I should say: ";
        getline(cin,learned);
        cout << endl;
    }//END if

    inFile<<endl<<toLearn<<"_"<<learned;//Writes in prompt_result syntax
    inFile.close();

    addStr(toLearn,learned);//The program, by default, makes use of the learned phrase right away

    return learned;
}

