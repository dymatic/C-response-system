#include <sstream>
//Home brewed
#include "LibMath.h"
#include "Translator.h"
//!Acts as an efficient storage variable for numbers.
double globalNumTemp;
//!Acts as an efficient storage variable for text.
string globalStringTemp;

/**
*Appends Input.txt and Output.txt so the program can "learn".
*@param input - The input that the program did not know.
*@param output - What the program should respond with next time.
*/
void learn(string input, string output)
{
    fstream inputs;
    fstream outputs;

    inputs.open("Input.txt",fstream::in|fstream::out|fstream::app);
    inputs <<endl<<input;
    inputs.close();

    outputs.open("Output.txt", fstream::in|fstream::out|fstream::app);
    outputs <<endl<<output;
    outputs.close();
}
string cleanup(string & message)
{
    char letters[message.length()];
    string returnMessage;

    for(unsigned int index=0; index<message.length(); index++)
        letters[index]=message.at(index);


    for(unsigned int index=0; index<message.length(); index++)
        letters[index]=tolower(letters[index]);

    for(unsigned int index=0; index<message.length(); index++)
        returnMessage+=letters[index];
    return returnMessage;
}
/**
*Formulates a random response for a file of nouns, adjectives, adverbs, and verbs.
*Nouns.txt, Verbs.txt, Adj.txt, Adv.txt will all be created read from.
*@param filelength - The number of lines in the file.
*/
string randomResponse(int filelength)
{
    ifstream nouns("Nouns.txt");
    ifstream verbs ("Verbs.txt");
    ifstream adjs("Adj.txt");
    ifstream advs("Adv.txt");

    string noun[filelength];
    string verb[filelength];
    string adj[filelength];
    string adv[filelength];

    stringstream sentence;

    int decider;

    for(int index=0; index<filelength; index++)
    {
        getline(nouns, noun[index]);

        getline(verbs, verb[index]);

        getline(adjs, adj[index]);

        getline(advs, adv[index]);
    }//Assignment loop

    nouns.close();
    verbs.close();
    adjs.close();
    advs.close();

    decider=rand()%4;//There are several styles of sentences. This chooses that.
    switch(decider)
    {
    case 0:
        sentence<<"The "<<adj[rand()%filelength]<<" "<<noun[rand()%filelength]<<" "<<adv[rand()%filelength];
        sentence<<" "<<verb[rand()%filelength]<<"ed the "<<adj[rand()%filelength]<<" "<<noun[rand()%filelength]<<"s.";
        break;

    case 1:
        sentence << "I "<<adv[rand()%filelength]<<" "<<verb[rand()%filelength]<<"ed the "<<adj[rand()%filelength]<<" "<<noun[rand()%filelength]<<".";
        break;

    case 2:
        sentence << noun[rand()%filelength]<<"s "<<verb[rand()%filelength]<<" "<<noun[rand()%filelength]<<"s.";
        break;

    case 4:
    sentence << "The "<<noun[rand()%filelength]<<" was "<<verb[rand()%filelength]<<"ed by the "<<noun[rand()%filelength]<<".";
    }
    return sentence.str();
}
/**
*Looks through Input.txt for a match to what the user said, and returns the corresponding line in Output.txt.
*This function will call learn(input, learning) in order to learn if input is not found.
*@param toRespondTo - The input message
*@return output - The message if it is found.
*/
string formulateResponse(string toRespondTo)
{
    string output;
    string possibleInputs[100000];
    string possibleOutputs[100000];

    ifstream inputs("Input.txt");
    ifstream outputs("Output.txt");

    for(int index=0; index<100000; index++) //100000 is a lot, but it's the maximum amount of queries this robot can make.
    {
        getline(inputs, globalStringTemp);

        if(globalStringTemp.find("~!")==-1)
            possibleInputs[index]=globalStringTemp;

        getline(outputs, globalStringTemp);

        if(globalStringTemp.find("~!")==-1)
            possibleOutputs[index]=globalStringTemp;
    }

    outputs.close();
    inputs.close();

    bool good=false;//Whether or not the statement was found.

    for(unsigned int index=0; index<1000; index++)
    {
        if(possibleInputs[index].find(toRespondTo)!=-1||toRespondTo.find("~!")!=-1)
        {
            (possibleOutputs[index].find("~!")==-1)?//This is just an extra measure.
            output=possibleOutputs[index]
                   :output="Comment detected.";
            good=true;
        }
        else if((possibleInputs[index].length()==toRespondTo.length())&&(possibleInputs[index].at(0)==toRespondTo.at(0))&&(rand()%10==5))//Wing
        {
            output=possibleOutputs[index];
            good=true;
        }

        else if(((rand()%100)==6)&&index==980)//1% Chance of this happening.
        {
            output=randomResponse(200);
            good=true;
        }
    }
//This will only execute if proper output is not found
    if(good==false)
    {
        cout << "I do not know how to respond. Type an acceptable answer: "<<endl;
        cout << "> ";
        getline(cin, globalStringTemp);
        cout << endl;

        learn(toRespondTo, globalStringTemp);
        return globalStringTemp;
    }
    else
    {
        if(toRespondTo.find("~!")==-1)
            return output;
        else return "Comment detected.";
    }
    good=false;
}
/**
*Crunch commands allow the user to play games, make random sentences, and execute external commands.
*@return -1 if the user has requested termination, 0 otherwise.
*/
short crunch()
{
    globalNumTemp=0;
    globalStringTemp="";
    do
    {

        cout << "Enter the command. ls lists commands."<<endl;
        cout <<"> ";
        getline(cin, globalStringTemp);
        cout << endl;
        if(globalStringTemp=="quit")
            return -1;
        if(globalStringTemp.find("game")!=-1)
        {
            cout << "Name a game. The games are any systems games through terminal, ball, launch, population, skip, and warriors."<<endl;
            cout << "> ";
            getline(cin, globalStringTemp);
            cout << endl;

            if(globalStringTemp.find("launch")!=-1)
                launch();

            if(globalStringTemp.find("ball")!=-1)
            {
                throwBall();
            }

            if(globalStringTemp=="skip")
            {
                skip(rand()%10);
            }
            if(globalStringTemp.find("warr")!=-1)
            {
                //Warrior.name stuff
                globalStringTemp="";
                cout <<"Your warriors name: ";
                getline(cin, globalStringTemp);
                cout << endl;

                warrior warrior0(10.,10.,globalStringTemp,2.,6.,300.,"fighter",true,13.,190.);

                globalStringTemp="";
                cout <<"His opponent's name: ";
                getline(cin, globalStringTemp);
                cout << endl;

                warrior warrior1(10.,10.,globalStringTemp,2.,6.,300.,"fighter",true,13.,190.);
                warriors(warrior0, warrior1);
            }//If warrior
            if(globalStringTemp.find("pop")!=-1)
            {
                populationGame();
            }

        }
        if(globalStringTemp.find("terminal")!=-1)//Totally not needed
        {
            globalStringTemp="";
            cout << "Enter the shell command."<<endl;
            cout << "> ";
            getline(cin, globalStringTemp);
            cout << endl;
            char *query = (char*)globalStringTemp.c_str();
            system(query);
            system(" ");//Shoddy but functional
            cout << endl;
        }
        if(globalStringTemp.find("transl")!=-1)
        transRun();

        if(globalStringTemp.find("booky")!=-1)
            booky();

        if(globalStringTemp=="desc")
        {
            globalStringTemp="";
            cout << "Name the command."<<endl;
            cout << "> ";
            getline(cin, globalStringTemp);
            cout << endl;

            if(globalStringTemp.find("quit")!=-1)
                cout << "Quits the program."<<endl;

            if(globalStringTemp.find("terminal")!=-1)
                cout << "Runs a command in the system shell."<<endl;

            if(globalStringTemp=="ls")
                cout << "Lists available commands and returns you to the AI."<<endl;

            if(globalStringTemp=="lsn")
                cout << "Lists available commands and returns control to program command."<<endl;

            if(globalStringTemp=="desc")
                cout << "Describes program commands. You obviously know how to use this one."<<endl;

            if(globalStringTemp=="rand")
                cout << "Returns a random sentence."<<endl;

            if(globalStringTemp=="game")
                cout << "Plays one of various games included."<<endl;

            if(globalStringTemp=="booky")
                cout << "A time management program to help mitigate bookwork."<<endl;

            if(globalStringTemp=="math")
                cout << "Utilizes my math library to perform mathematical functions on data. Scientific, geometrical, and algebraic functions are included."<<endl;

            if(globalStringTemp=="transl")
                cout << "Utilizes Langdiff to translate a file from a custom language."<<endl;
        }
        if(globalStringTemp=="lsn")
        {
            cout <<"quit, terminal, ls, lsn, rand, game, booky, math, transl, desc. To describe what each does, use desc."<<endl;
        }
    }
    while(globalStringTemp=="lsn"); //Loops back to the crunch command menu. This replaces a goto.
    if(globalStringTemp=="ls")
    {
        cout <<"quit, terminal, ls, lsn, rand, game, booky, math, transl, desc. To describe what each does, use desc."<<endl;
    }
    if(globalStringTemp.find("rand")!=-1)
    {
        cout <<"MESSAGE: "<< randomResponse(200)<<endl;
    }
    if(globalStringTemp.find("spew")!=-1)//This is a hidden feature since it would not be used very often. That may be changed in the future.
    {
        globalNumTemp=0;
        cout << "How intsense would you like the output?"<<endl;
        cout << "> ";
        cin  >> globalNumTemp;
        cout << endl;

        spew(globalNumTemp);
        cout << endl<<endl;
    }
    if(globalStringTemp.find("math")!=-1)
    {
        do
        {
            cout << "Type a mathematic command. lsm lists them."<<endl;
            cout << "> ";
            cin  >> globalStringTemp;
            cout << endl;
            if(globalStringTemp=="lsm")
            {
                cout << "square, mean, stdDev, rectArea, rectVol, triArea, pyThagSide, pyThagHypot, circum, circArea,"<<endl;
                cout << "sphereVol, cylArea, cylVol, coneArea, coneVol, denisty, celToFar, farToCel, farToKelv,"<<endl;
                cout << "celToKelv, kelvToCel, kelvToFar, microToSec, secToMicro."<<endl<<endl;
            }
        }
        while(globalStringTemp=="lsm");  //END LSM if//END LSM loop
        //START mathematical commands.
        if(globalStringTemp=="square")
        {
            cout << "Number: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Square: "<<square(globalNumTemp)<<endl;
        }
        if(globalStringTemp=="mean")
        {
            cout << "How many points of data: ";
            cin  >> globalNumTemp;//Here globalNumTemp acts as a holder for the amount of data.
            cout << endl;

            double data[(int)globalNumTemp];

            for(int index=0; index<(int)globalNumTemp; index++)
            {
                cout << "Data point "<<(index+1)<<": ";
                cin  >> data[index];
                cout << endl;
            }
            cout << "The mean is: "<<mean(data, (int)globalNumTemp)<<endl;
        }//END mean

        if(globalStringTemp=="stdDev")
        {
            cout << "How many points of data: ";
            cin  >> globalNumTemp;//Here globalNumTemp acts as a holder for the amount of data.
            cout << endl;

            double data[(int)globalNumTemp];

            for(int index=0; index<(int)globalNumTemp; index++)
            {
                cout << "Data point "<<(index+1)<<": ";
                cin  >> data[index];
                cout << endl;
            }
            cout << "The standard deviation is: "<<stdDev(data, (int)globalNumTemp)<<endl;
        }//END stdDev

        if(globalStringTemp=="rectArea")
        {
            double side2;

            cout << "Length of side 1: ";
            cin  >> globalNumTemp;//Here globalNumTemp is side 1.
            cout << endl;

            cout << "Length of side 2: ";
            cin  >> side2;
            cout << endl;

            cout << "Area: "<<rectangularArea(globalNumTemp, side2)<<endl;
        }//END rectArea

        if(globalStringTemp=="rectVol")
        {
            double side2, height;

            cout << "Length of side 1: ";
            cin  >> globalNumTemp;//Here globalNumTemp is side 1.
            cout << endl;

            cout << "Length of side 2: ";
            cin  >> side2;
            cout << endl;

            cout << "Height: ";
            cin  >> height;
            cout << endl;

            cout << "Volume: "<<rectangularVolume(globalNumTemp, side2, height)<<endl;
        }//END rectVol

        if(globalStringTemp=="triArea")
        {
            double height;

            cout << "Base: ";
            cin  >> globalNumTemp;//globalNumTemp is acting as the base length.
            cout << endl;

            cout << "Height: ";
            cin  >> height;
            cout << endl;

            cout << "Area: "<<triangularArea(globalNumTemp, height)<<endl;
        }//END triArea

        if(globalStringTemp=="pyThagHypot")
        {
            double side2;

            cout << "Side 1: ";
            cin  >> globalNumTemp;//globalNumTemp is side 1 of a right triangle.
            cout << endl;

            cout << "Side 2: ";
            cin  >> side2;
            cout << endl;

            cout << "Hypotenuse: "<<pyThagHypotenuse(globalNumTemp, side2)<<endl;
        }//END pyThagHypot

        if(globalStringTemp=="pyThagSide")
        {
            double hypotenuse=0;

            cout << "Side 1: ";
            cin  >> globalNumTemp;//globalNumTemp is side 1 of a right triangle.
            cout << endl;

            cout << "Hypotenuse: ";
            cin  >> hypotenuse;
            cout << endl;

            cout << "Side 2: "<<pyThagSide(globalNumTemp, hypotenuse)<<endl;
        }//END pyThagSide

        if(globalStringTemp=="circum")
        {
            cout << "Radius: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Circumference: "<<circumference(globalNumTemp)<<endl;
        }//END circum

        if(globalStringTemp=="circArea")
        {
            cout << "Radius: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Area: "<<circularArea(globalNumTemp)<<endl;
        }//END circArea

        if(globalStringTemp=="sphereVol")
        {
            cout << "Radius: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Volume: "<<sphericalVolume(globalNumTemp)<<endl;
        }//END sphereVol

        if(globalStringTemp=="cylArea")
        {
            double height;

            cout << "Radius: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Height: ";
            cin  >> height;
            cout << endl;

            cout << "Area: "<<cylindricalArea(globalNumTemp, height)<<endl;
        }//END cylArea

        if(globalStringTemp=="cylVol")
        {
            double height;

            cout << "Radius: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Height: ";
            cin  >> height;
            cout << endl;

            cout << "Volume: "<<cylindricalVolume(globalNumTemp, height)<<endl;
        }//END cylVol

        if(globalStringTemp=="coneArea")
        {
            double height, slant;
            cout << "Radius: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Height: ";
            cin  >> height;
            cout << endl;

            cout << "Slant: ";
            cin  >> slant;
            cout << endl;

            cout << "Area: "<<coneArea(globalNumTemp, height, slant)<<endl;
        }//END coneArea

        if(globalStringTemp=="coneVol")
        {
            double height;

            cout << "Radius: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Height: ";
            cin  >> height;
            cout << endl;

            cout << "Volume: "<<coneVolume(globalNumTemp, height)<<endl;
        }//END coneVol

        if(globalStringTemp=="density")
        {
            double volume;

            cout << "Mass: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Volume: ";
            cin  >> volume;
            cout << endl;

            cout << densityOf(globalNumTemp, volume)<<endl;
        }//END density

        if(globalStringTemp=="celToFar")
        {
            cout << "Temperature in Celcius: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Fahrenheit: "<<convertCelciusToFahrenheit(globalNumTemp)<<endl;
        }//END celToFar

        if(globalStringTemp=="farToCel")
        {
            cout << "Temperature in Fahrenheit: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Celcius: "<<convertFahrenheitToCelcius(globalNumTemp)<<endl;
        }

        if(globalStringTemp=="farToKel")
        {
            cout << "Temperature in Fahrenheit: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Kelvin: "<<(convertFahrenheitToCelcius(globalNumTemp)-273.15)<<endl;
        }//END farToKelv

        if(globalStringTemp=="celToKelv")
        {
            cout << "Temperature in Celcius: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Kelvin: "<<(globalNumTemp-273.15)<<endl;
        }//END celToKelv

        if(globalStringTemp=="kelvToFar")
        {
            cout << "Temperature in Kelvin: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Fahrenheit: "<<(convertCelciusToFahrenheit(273.15+globalNumTemp))<<endl;
        }//END kelvToFar

        if(globalStringTemp=="kelvToCel")
        {
            cout << "Temperature in Celcius: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << "Celcius: "<<(273.15+globalNumTemp)<<endl;
        }//END kelvToCel

        if(globalStringTemp=="microToSec")
        {
            cout << "Microseconds: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << microToSec(globalNumTemp)<<"Seconds"<<endl;
        }//END microToSec

        if(globalStringTemp=="secToMicro")
        {
            cout << "Seconds: ";
            cin  >> globalNumTemp;
            cout << endl;

            cout << secToMicro(globalNumTemp)<<"Microseconds"<<endl;
        }

        cout << endl;
    }//END math microToSec, secToMicro.
    globalStringTemp="";
    globalNumTemp=0.;
    return 0;
}//END crunch
