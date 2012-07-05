/*
  *AI 3 - Complete Rewuire
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

/**
*Makes the input conform to a certain set of standards.
*Whitespace is trimmed and it is made lowercase.
*/
string sanitizeInput(string input){
    string returnMessage;

    for(unsigned int index=0; index<input.length(); index++) {
        returnMessage+=tolower(input.at(index));
    }
    return returnMessage;
}
/**
  *Counts the number of lines in a file.
  *Depending on the size of the file, this is a lengthy process.
  *@param file - The file path to the target file.
  *@return counter - The number of lines in the file.
  */
int linec(string file){
    ifstream fileReader(file.c_str());
    string buff;

    int counter=0;

    for(counter=0;getline(fileReader,buff);counter++)
        ;
    return counter;
}

/**
  *Loads a learn file into RAM for use with response formulation.
  *Syntax for the learning file is input_output
  *@param file - The path to the leaning file
  *@param wingNum - The chance to guess what the user wants without knowing
  */
void setupStrings(string &file, int wingNum){
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
void clearMemory(){
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
string formulateResponse(string toReplyTo){
    string buff=toReplyTo;
    toReplyTo=sanitizeInput(buff);

   //First, searches the input strings for a match.
    for(int index=0; index<Gmembers; index++){
        if(input[index]==toReplyTo){
            return output[index];
        }
    }
    //Then, it searches for something that matches it. This is a wing feature.
    for(int index=0; index<Gmembers; index++){
        if(input[index].length()==toReplyTo.length()&&rand()%wing==wing-1)
            return output[index];
    }
    //When all else fails, it returns a message to main that will then call the learning function, rather than directly.
    return "learn(toReplyTo)";
}

/**
  *Causes the robot to learn from its mistakes.
  *@param toLearn - The message that tripped it up
  *@param learned - The message to implant in the file. If
  *you are using interactive mode, leave this blank
  *@return learned - Learned is returned to make output better.
  */
string learn(string toLearn, string learned){
    fstream inFile;
    inFile.open(fileName.c_str(),fstream::in|fstream::out|fstream::app);

    if(learned.length()<=1){//Interactive Mode
        cout << "What I should say: ";
        getline(cin,learned);
        cout << endl;
    }//END if

    inFile<<endl<<toLearn<<"_"<<learned;
    inFile.close();
    setupStrings(fileName,wing);
    return learned;
}

