#include <vector>
#include <sstream>
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

    decider=rand()%3;//There are several styles of sentences. This chooses that.
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
        getline(inputs, possibleInputs[index]);
        getline(outputs, possibleOutputs[index]);
    }

    outputs.close();
    inputs.close();

    for(unsigned int index=0; index<1000; index++)
    {
        if(possibleInputs[index].find(toRespondTo)!=-1)
        {
            output=possibleOutputs[index];
            goto success;
        }
        else if(possibleInputs[index].length()==toRespondTo.length()&&rand()%10==5)//There is a 10% chance for it to "wing it".
        {
            output=possibleOutputs[index];
            goto success;
        }
    }
//This will only execute if proper output is not found
failure:
    {
        string learning;

        cout << "I do not know how to respond. Type an acceptable answer: "<<endl;
        cout << "> ";
        getline(cin, learning);
        cout << endl;

        learn(toRespondTo, learning);
        return learning;
    }
success:
    {
        return output;
    }
}
/**
*Crunch commands allow the user to play games, make random sentences, and execute external commands.
*@return -1 if the user has requested termination, 0 otherwise.
*/
short crunch()
{
programCommand:

    string command;
    cout << "Enter the command. ls lists commands."<<endl;
    cout <<"> ";
    getline(cin, command);
    cout << endl;
    if(command=="quit")
        return -1;
    if(command.find("game")!=-1)
    {
        string game;
        cout << "Name a game. The games are any systems games through terminal, ball, launch, population, and warriors."<<endl;
        cout << "> ";
        getline(cin, game);
        cout << endl;

        if(game.find("launch")!=-1)
            launch();

        if(game.find("ball")!=-1)
        {
            throwBall();
        }
        if(game.find("warr")!=-1)
        {
            //Warrior.name stuff
            string name;

            cout <<"Your warriors name: ";
            getline(cin, name);
            cout << endl;

            warrior warrior0(10.,10.,name,2.,6.,300.,"fighter",true,13.,190.);

            cout <<"His opponent's name: ";
            getline(cin, name);
            cout << endl;

            warrior warrior1(10.,10.,name,2.,6.,300.,"fighter",true,13.,190.);
            warriors(warrior0, warrior1);
        }//If warrior
        if(game.find("pop")!=-1)
        {
            populationGame();
        }

    }
    if(command.find("terminal")!=-1)//Totally not needed
    {
        cout << "Enter the shell command."<<endl;
        cout << "> ";
        getline(cin, command);
        cout << endl;
        char *query = (char*)command.c_str();
        system(query);
        cout << endl;
    }
    if(command=="desc")
    {
        string toDesc;
        cout << "Name the command."<<endl;
        cout << "> ";
        getline(cin, toDesc);
        cout << endl;

        if(toDesc.find("quit")!=-1)
            cout << "Quits the program."<<endl;

        if(toDesc.find("terminal")!=-1)
            cout << "Runs a command in the system shell."<<endl;

        if(toDesc=="ls")
            cout << "Lists available commands and returns you to the AI."<<endl;

        if(toDesc=="lsn")
            cout << "Lists available commands and returns control to program command."<<endl;

        if(toDesc=="desc")
            cout << "Describes program commands. You obviously know how to use this one."<<endl;

        if(toDesc=="rand")
            cout << "Returns a random sentence."<<endl;

        if(toDesc=="game")
            cout << "Plays one of various games included."<<endl;

    }
    if(command=="lsn")
    {
        cout <<"quit, terminal, ls, lsn, rand, game, desc. To describe what each does, use desc."<<endl;
        goto programCommand;//SECOND goto of the program. Shoot me for not using loops.
    }
    if(command=="ls")
    {
        cout <<"quit, terminal, ls, lsn, rand, game, desc. To describe what each does, use desc."<<endl;
    }
    if(command.find("rand")!=-1)
    {
        cout <<"MESSAGE: "<< randomResponse(200)<<endl;
    }
    return 0;
}
