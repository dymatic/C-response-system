/*
*Main handles the input using the functions provided in this file.
*/
#include <iostream>
using namespace std;
//MAIN RESPONSES
void handleCrunch(string command, bool ALLOW_CRUNCH, string noCrunchMsg){
        if(isCrnchCmd(command))
        {
            cout << endl;

            if(ALLOW_CRUNCH)
            {
                loadCrunchCommand(command);
                executeCrunch();
            }//END allowed

            else
            {
                cout << noCrunchMsg << endl;
            }//END not allowed

        }//END crunch if
}

void handleResponse(string path, int wing, bool WANT_LEARN, bool ALLOW_EXPLICIT, string command, string understood){
string target;
setupStrings(path,wing);

            target=formulateResponse(command);

            if(target=="learn(toReplyTo)"&&WANT_LEARN)   //Arrays not loaded right, WING not gotten, or new input
            {
                string learnSentence;//Response to self

                cout << "I do not know how to reply to "<<command<<", please tell me.\n";
                cout << "> ";

                getline(cin,learnSentence);
                learn(sanitizeInput(command),learnSentence);//Will try twice if blank is given

                cout << "Got it. So, " << learnSentence<<endl<<endl;
            }else if(!WANT_LEARN)
                cout << "Permission denied";//END learn

            else if(target=="exlLearned")
            {
                if(ALLOW_EXPLICIT)
                exlLearn(command);

                target="Understood.";
            }

            else if(target=="chTon not got")
                target="";

            else if(target!="learn(toReplyTo)"&&target!="chTon not got"&&target!="exlLearned"&&target!="")   //Input found, or WING gotten
            {
                cout << target<<endl;
                target=understood;
            }//END talk

            cout << endl;

            usleep(1000);
}
