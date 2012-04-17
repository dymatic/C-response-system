/**
*Stores population and how many days have gone buy without disaster.
*/
struct world
{

    int timesWithout; //Times without disaster or population boom
    int population;

    string name;
    world(int p, string s)
    {
        population=p;
        name=s;
    }
};
/**
*Determines whether or not a disaster will occur.
*@param w - The world where the disaster chance is being calculated.
*@return the probability that the world will have a disaster.
*/
int willDisaster(world w)
{
    if(w.timesWithout<=1)
        return 10;
    else return w.timesWithout*10;
}
/**
*The world loses a random number of people. The number can be as high as the total population.
*@param w - The world where the disaster will occur.
*/
void disaster(world & w)
{
    w.population-=rand()%w.population;
}
/**
*Calculates the chance of a population boom based on how long it has been
* since a disaster or a boom. Disasters are slightly more likely.
*@param w - The world where chance is being calculated.
*
*/
int willBoom(world w)
{
    if(w.timesWithout<=1)
        return 10;//Uses chance to increase the chance of a boom.
    else return w.timesWithout*10;
}
/**
*Adds a random number of people to the population. This number can be as high as the current population.
*@param w- The world where the boom will occur.
*/
void boom(world & w)
{
    w.population+=rand()%w.population;//Randomly adds people, decreasing with population.
}
/**
*Plays a simulation of a town during a time of an advanced rate of death.
*The function will output and ask for input.
*/
void populationGame()
{

    int initPop;
    string initName;

    world w(100000, "Kelton"); //Just in case...

    cout << "Initial Population: ";
    cin  >> initPop;
    cout << "\nTown name: ";
    cin  >> initName;
    cout << endl;

    w.name=initName;
    w.population=initPop;

    int temp=-36;

    cout << "Population of " <<w.name <<" over time."<<endl;
    cout << "Initial population is "<<w.population<<"." <<endl;

    for(int index=0; index<100; index++)
    {

        temp=w.population;

        if(willDisaster(w)>=rand()%100)
        {
            disaster(w);
            w.timesWithout=0;
        }
        else w.timesWithout++;

        if(willBoom(w)>=rand()%100)
        {
            boom(w);
            w.timesWithout=0;
        }
        else w.timesWithout++;

        if(temp!=*&w.population)
            cout <<"Day "<<index<<": "<< w.population <<endl;
    }//End body loop
    cout << "*Only days where population was lost or gained were shown."<<endl;
    cout << "**This simulation emulates a town under an exponentially spreading disease."<<endl;
}
/**
*Launches a bullet at the speed of binary!
**/
void launch()
{
    double initVel=0.;
    double initHeight=0.;

    unsigned int counter=0;
    do
    {
        cout <<"Initial velocity (feet/sec): ";
        cin >> initVel;
        cout << "\nInitial height (feet): ";
        cin >> initHeight;
    }
    while((initVel>=0||initVel<=0)&&(initHeight>=0||initHeight<=0));
    cout << "Round fired! Stats about to show."<<endl;

    double height=initHeight;
    double vel=initVel;

    for(int index=0; vel>0&&height>0; index++)
    {
        cout << "Second "<<counter<<": "<<height<<"feet, "<<vel<<" feet/second."<<endl<<endl;

        vel-=32+index;
        height-=(vel/(vel-index));
        counter++;
    }
    if(height<0)
        height=0;

    bool detail;
    if(vel<0&&height>0)
        detail=true;
    if(vel<0)
    {
        vel=0;
    }
    cout <<"Firing complete. Advanced stats:" <<endl<<endl;

    cout << "==================================="<<endl;
    cout << "     Advanced stats"      <<endl;
    cout << "==================================="<<endl;

    cout <<"\n          Time: \t "<<counter<<" seconds"<<endl;

    if(detail=true)
        cout <<"*";

    cout <<"Final Velocity: \t "<<vel<<" feet/sec";
    cout <<"\n  Final height: \t "<<height<<" feet" <<endl <<endl;

    if(detail==true)
    {
        cout << "*You may be thinking that a velocity of 0 and a height above 0 is impossible. However, only forward motion is calculated by this applet."<<endl;
        cout << "If this is the case, the bullet is moving at terminal velocity. That is the fastest gravity and wind resistance allow it to fall."<<endl<<endl;
    }
}
/**
*Throws a virtual ball at the roof.
*@param strength - How hard to throw the ball
*/
void throwBall()
{

    short score=0;

    double strength=0.;

    for(double total=0; abs(score)<5;)
    {
        cout << "Throw strength: ";
        cin  >> strength;
        cout << endl;
        strength-=rand()%50;
        total=(strength+(rand()%50));
        cout << "After wind speed you threw: "<<total<<endl;
        if(total<50)
            score--;

        if(total>100)
            score--;

        if(total>50&&total<100)
            score++;

        cout << "Your score is: "<<score<<"."<<endl;
    }
    if(score>0)
        cout << "You won!"<<endl;
    else cout << "You lost."<<endl;
}

/**
  *Simulates a battle between the warrior invoking fight an an opponent. Output is produced.
  *@param w2 - The warrior to fight.
  */
void warriors(warrior w1,warrior w2)
{
    cout <<"    /\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\"<<endl;
    cout <<"    ===========WARRIORS================="<<endl;
    cout <<"    /\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\"<<endl;
    do
    {
        if(rand()%2==0)
        {
            w1.attack(w2);
        }
        else
        {
            w2.attack(w1);
        }

        if(w1.durability>0)
        {

            cout <<w1.indName<<": "<<w1.durability<<" hp remaining. ";
            if(w1.durability>w2.durability)
                cout <<"(winning)";
            else if (w1.durability<w2.durability)
                cout <<"(losing)";
            else if (w1.durability==w2.durability)
                cout <<"(tie)";

            cout <<endl;
        }
        else cout <<w1.indName<<": "<<"0"<<" hp remaining."<<endl;

        if(w2.durability>0)
            cout <<w2.indName<<": "<<w2.durability<<" hp remaining."<<endl;

        else cout <<w2.indName<<": "<<"0"<<" hp remaining."<<endl;
        cout << endl;
        usleep(100000);

    }
    while(w1.alive&&w2.alive);
    if(w1.durability>=w2.durability)
        cout << w1.indName<<" won!"<<endl;
    else
        cout << w2.indName<<" won."<<endl;
}//End fight
/**
*Booky is a utility for time management with reading books.
*As a student I find myself wondering what an appropriate number of pages to read a day will be.
*Booky tells me exactly how to manage my time, so I figured I would hardcode it into this program.
*Like all VoidGames, this function collects input and outputs text.
*/
void booky()
{
//Even though this is a void game, its own crunch command.
    double total, on;
    int days;

    cout << "|Booky - A time management friend|"<<endl;

    cout << "How many pages does the book have?"<<endl;
    cout << "> ";
    cin  >> total;
    cout << endl;

    cout << "What page are you on? (0 is acceptable)"<<endl;
    cout << "> ";
    cin  >> on;
    cout << endl;

    cout << "How many days are left to read the book?"<<endl;
    cout << "> ";
    cin  >> days;
    cout << endl;

    cout << "You have "<<days<<" left to read "<<total<<" pages."<<endl;
    cout << "You must read "<<((total-on)/days)<<" pages every day to complete the book on time."<<endl<<endl;
}
/**
*Spews garbage text on the screen.
*@param intensity - How much output to send to the screen. This is not represented on a character-by-integer basis.
*/
void spew(int intensity)
{
    char characters[65]= {'a','b','c','d','e','f','g','h','i','j','k',
                          'l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                          '{','(','}',')','0','1','2','3','4','5','6','7','8','9',
                          '~','!','@','#','$','%','^','&','*','_','-','+','=','\n','\\','|','`','\'',
                          '\"','>','<','.',',','/','?'
                         };

    for(int index=0; index<intensity*100; index++)
    {
        cout << characters[rand()%65];
    }
}
