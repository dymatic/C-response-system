#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string *fromStrings=new string[10000];//C++ members
string *toStrings=new string[10000]; // Custom language members
void splitstr(string &c,string s);
void replaceAll(std::string& str,  std::string& from,  std::string& to);
int linec(string);
int members=0;                     //  The number of members

/**
*Orders the langdefines by line length.
*This prevents the replacing of smaller words in
*larger ones. This is an exact copy of the function in NSL,
*with the addition of title checking.
*@param filepath - The path to the file
*@param ltor - True (1) if the largest goes first, false (0) otherwise.
*/
void orderFile(string filepath, bool ltor)
{
    ifstream file(filepath.c_str());
    int nlines=linec(filepath);
    ofstream writer(filepath.c_str());
    string lines[nlines];//Contains all of the lines

    for(int index=0; index<nlines; index++) //Make container
        getline(file,lines[index]);

    for(int index=0; index<nlines-1; index++) //Iterate through positions
    {
        if(ltor)
        {
            if(lines[index].find("$")!=-1&&lines[index].find("@")==-1)
                    splitstr(lines[index],"$");//Cuts the comment if the allow character is not present.

            while(lines[index].length()<lines[index+1].length())
            {//Checks the line before it, changes them, and subtracts one from index.
                bool title=false;//Whether or not it is a title line (===)
                string buffer=lines[index];

                if(lines[index].find("===")!=-1)
                    title=true;

                lines[index]=lines[index+1];
                lines[index+1]=buffer;
                index--;

                if(title&&index==0)
                    break;//Will not enroach on the title, despite size.
            }
        }
        else
        {
            while(lines[index].length()>lines[index+1].length())
            {
               //Checks the line before it, changes them, and subtracts one from index.
                bool title=false;//Whether or not it is a title line (===)
                string buffer=lines[index];

                if(lines[index].find("===")!=-1)
                    title=true;

                lines[index]=lines[index+1];
                lines[index+1]=buffer;
                index--;

                if(title&&index==0)
                    break;//Will not enroach on the title, despite size.
            }//End while for backwards
        }//End else that determines whether or not to do it forwards or backwards.
        writer<<lines[index]<<endl;//Write the ordered array
    }//End main for

    file.close();
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
     string title="===";//Used for language titles on the first line of a langdefines
    string replaceWith="Language Title: ";
    int until=0; /*Until is used to determine how many NO_USE characters to use.
                    NO_USE characters show an unwritten line.*/

    ifstream file(filename.c_str());
    for(int index=0; index<10000; index++)
    {
        getline(file,buffer);
        if(buffer.find("$")!=-1&&buffer.find("@")==-1) //String is split if let_symbol is here
        {
            splitstr(buffer,"$");//Replace in between the comments
        }
        else if(buffer.find("@")!=-1) //Let symbol is deleted
        {
            buffer.replace(buffer.find("@"),buffer.find("@"),"");
        }
        if(buffer.find("===")!=-1&&index==0)
        {
            replaceAll(buffer,title,replaceWith);
            cout << buffer<<endl;
            index--;
            continue;
        }
        //This marks the end of all of the file syntax and the beginning of the real language scraping.
        if(buffer.find("_")!=-1)
        {
            toStrings[index]=buffer.substr(0,buffer.find("_"));//Tostrings is first half of underscore

            fromStrings[index]=buffer.substr(buffer.find("_")+1,buffer.length());//From is last half of underscore

        }
        else
        {
            until=10000-index;//How many null characters to write
            break;
        }
    }
    for(int index=10000-until; index<10000; index++)
    {
        //\++10x is used to indicate a line not being used.
        toStrings[index]="/++10x";
        fromStrings[index]="/++10x";
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
    string *buffer=new string;

    for(; getline(file,*buffer);)
        lines++;

    file.close();
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
        string nope="";//replaceall needs a reference.

        if(toSplit.find(magichar)!=-1)//Put the text before first magichar in buffer
            buffer<<copy.substr(0,toSplit.find(magichar));

        if(copy.find(magichar)!=-1)//Make copy equal to the whole string minues the part up to the first magichar
            copy=copy.substr(toSplit.find(magichar)+1,toSplit.length());

        if(copy.find(magichar)!=-1)//Put the position of the magichar+1 in the buffer.
            buffer<<copy.substr(copy.find(magichar)+1,copy.length());

        toSplit=buffer.str();
    }//End if
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
    ofstream writer(toWriteTo.c_str());
    cout << lines<<endl;


    for(int index=0; index<lines; index++) // Loops through each line
    {
        getline(reader, line[index]);
        for(int secInd=0; secInd<members; secInd++)//Performs replacement operations
        {
            splitstr(line[index],magichar); // splitstr removes protected strings from lines[index] IF they exist.

            if(fromStrings[secInd]!="/++10x"&&toStrings[secInd]!="/++10x")//NULL string to ensure quality.
            {
                replaceAll(line[index],fromStrings[secInd],toStrings[secInd]);
            }

        }//END for replacements

        writer << line[index]<<endl;

    }
    writer.close();
    reader.close();
}
/**
*Compiles a set of files in a Noran Make File.
*iCompile stands for Iterative Compilation
*The syntax for a Noran Make File is infile_outfile_magichar
*@param nmfPath - The path to the Noran Make File
*/
void iCompile(string nmfPath)
{
    ifstream nmf(nmfPath.c_str());
    int nmflength = linec(nmfPath);

    for(int index=0; index<nmflength; index++)
    {
        string buffer;
        string inFile, outFile, magichar;

        getline(nmf,buffer);
        //in_out_mag
        inFile=buffer.substr(0,buffer.find("_"));
        buffer=buffer.substr(buffer.find("_")+1,buffer.length());
        //out_mag
        outFile=buffer.substr(0,buffer.find("_"));
        buffer=buffer.substr(buffer.find("_")+1,buffer.length());
        //mag
        magichar=buffer;
        compile(inFile,linec(inFile.c_str()),outFile,magichar);
    }
}
/**
*Runs the program
*/
void transRun(){
 string argv2[6];
        char choice='a';
        cout << "What is the total file path to the language definition file?"<<endl<<"$ ";
        cin  >> argv2[0];
        cout << endl;

        cout << "Would you like the langdefines automatically ordered? y or n "<<endl<<"$ ";
        cin  >> argv2[4];
        cout << endl;

        cout << "Are you using a Noran Make File? y/n"<<endl<<"$ ";
        cin  >> choice;
        cout << endl;

        if(choice=='y')
            {
                if(argv2[4].find("Y")!=-1)
                    orderFile(argv2[0],true);

                string filename;
                cout << "What is the path to the Noran Make File?"<<endl<<"$ ";
                cin  >> filename;
                cout << endl;

                iCompile(filename);
            }else{
        cout << "What is the total file path to the code?"<<endl<<"$ ";
        cin  >> argv2[1];
        cout << endl;

        cout << "What is the file path to the output file?"<<endl<<"$ ";
        cin  >> argv2[2];
        cout << endl;

        cout << "What is the magichar? If you do not know, type \"nothing\""<<endl<<"$ ";
        cin  >> argv2[3];
        cout << endl;

    }
    if(argv2[4].find("y")!=-1)
        orderFile(argv2[0],true);

    loadLanguage(argv2[0],linec(argv2[0]));
    compile(argv2[1],linec(argv2[1]),argv2[2],argv2[3]);
    cout << endl;
}
