
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
//Whole file copied directly from Langdiff. Major versions are reflected
//Here when released.
using namespace std;

string *fromStrings=new string[10000];//C++ members
string *toStrings=new string[10000]; // Custom language members
void splitstr(string &c,string s);
int linec(string);
int members=0;                     //  The number of members

/**
*Orders the langdefines by line length.
*This prevents the replacing of smaller words in
*larger ones.
*@param filepath - The path to the file
*/
void orderFile(string filepath)
{
    ifstream file(filepath.c_str());
    int nlines=linec(filepath);

    string lines[nlines];//Contains all of the lines

    for(int index=0; index<nlines; index++) //Make container
        getline(file,lines[index]);

    for(int index=0; index<nlines-1; index++) //Iterate through positions
    {
        while(lines[index].length()<lines[index+1].length())
        {
            string buffer;//Loop executes while a string below it needs replacing.
            buffer=lines[index];

            lines[index]=lines[index+1];
            lines[index+1]=buffer;
            cout << "Let's see something."<<endl;
            index--;
        }
    }
    file.close();
    ofstream writer(filepath.c_str());
    for(int index=0; index<nlines; index++)
        writer<<lines[index]<<endl;//Write the ordered awway
    writer.close();
}
/**
 * Loads a language into the arrays.
 * The syntax of the file should be old_new
 * @param filename - The path to the file
 * @param lines - How many lines long the file is. This can be
 input manually or with linec(string filename).
 */
void loadLanguage(string filename,int lines)
{
    string buffer; //Used for parsing individual lines
    members=lines;// How many entries the langdefines has
    int until=0; /*Until is used to determine how many NO_USE characters to use.
                    NO_USE characters show an unwritten line.*/

    ifstream file(filename.c_str());
    for(int index=0; index<10000; index++)
    {
        getline(file,buffer);
        if(buffer.find("$")!=-1)
            splitstr(buffer,"$");

        if(buffer.find("_")!=-1)
        {
            toStrings[index]=buffer.substr(0,buffer.find("_"));

            fromStrings[index]=buffer.substr(buffer.find("_")+1,buffer.length());
        }
        else
        {
            until=10000-index;//Second bug
            break;
        }

        for(int index=10000-until; index<10000; index++)
        {
            //\++10x is used to indicate a line not being used.
            toStrings[index]="/++10x";
            fromStrings[index]="/++10x";
        }
    }
}
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
    return lines;
}
/**
*Replace all of the strings matching the criteria.
*@param str - The string to replace it in.
*@param from- The string to find and replace.
*@param to  - What to replace the string with
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
*Splitstr is a very important function.
*This finds text in between two magic characters and removes it from the string.
*
*The translator works on an explicit basis. Every string meeting its criteria will be
*removed. This allows sensitive strings to leave before translation begins. You must place
*the sensitive string in between the two magic characters.
*Splitstr also works on langdefines files.
*@param toSplit   - The string to remove sensitive strings from.
*@param magicahar - The character used in the code file to denote a sensitive string. "$" is the standard.
*/
void splitstr(string &toSplit, string magichar)
{
    if(toSplit.find(magichar)!=-1)
    {

        stringstream buffer;

        string copy=toSplit;
        string cnholder="";
        string nope="";


        if(toSplit.find(magichar)!=-1)
            buffer<<copy.substr(0,toSplit.find(magichar));//Before first magichar

        cnholder=buffer.str();

        if(copy.find(magichar)!=-1)
            copy=copy.substr(toSplit.find(magichar)+1,toSplit.length());

        if(copy.find(magichar)!=-1)
            buffer<<copy.substr(copy.find(magichar)+1,copy.length());//Substring of one more than the next magichar and the length.

        toSplit=buffer.str();
    }
}
/**
 * Creates a file containing the old text as defined by
 * the langdefines in loadLanguage(filename,lines).
 * If this is being used for code, you must compile it yourself.
 * @param fileName  - The absolute file path to the file.
 * @param lines     - How many lines the file has. Use linec to find this.
 * @param toWriteTo - The name of the file to write the translated code to.
 * @param magichar  - The string that denotes sensitive strings. If you do not have
                    one, use something gibberish. Otherwise, use your magichar. For
                    magichar documentation, see splitstr
 */
void compile(string fileName,int lines,string toWriteTo,string magichar)
{

    string line[lines];
    ifstream reader(fileName.c_str());

    for(int index=0; index<lines; index++)
    {
        getline(reader, line[index]);
    }

    for(int index=0; index<lines; index++) // Loops through each line
    {
        for(int secInd=0; secInd<members; secInd++)//Performs replacement operations
        {
            splitstr(line[index],magichar); // splitstr removes protected strings from lines[index] IF they exist.

            if(fromStrings[secInd]!="/++10x"&&toStrings[secInd]!="/++10x")
            {
                replaceAll(line[index],fromStrings[secInd],toStrings[secInd]);
            }

        }
        cout << line[index]<<endl;
        reader.close();
    }
    ofstream writer(toWriteTo.c_str());

    for(int index=0; index<lines; index++)//Iterate through the changed lines and write them to a file.
    {
        writer << line[index]<<endl;
    }
    writer.close();
}
/**
*Runs the program
*/
void transRun(){
    string argv2[6];
    cout << "What is the total file path to the language definition file?"<<endl<<"$ ";
        cin  >> argv2[0];
        cout << endl;

        cout << "What is the total file path to the code?"<<endl<<"$ ";
        cin  >> argv2[1];
        cout << endl;

        cout << "What is the file path to the output file?"<<endl<<"$ ";
        cin  >> argv2[2];
        cout << endl;

        cout << "What is the magichar? If you do not know, type \"nothing\""<<endl<<"$ ";
        cin  >> argv2[3];
        cout << endl;

        cout << "Would you like the langdefines automatically ordered? y/m "<<endl<<"$ ";
        cin  >> argv2[4];
        cout << endl;

    if(argv2[4].find("y")!=-1)
        orderFile(argv2[0]);

    loadLanguage(argv2[0],linec(argv2[0]));
    compile(argv2[1],linec(argv2[1]),argv2[2],argv2[3]);

    cout << endl;
}
