struct warrior
{
    double health;
    double strength;
    bool incap;
    bool alive;
    string name;
    /**
    *Constructor for Warrior. Pretty soon Item.h will become the base of warriors.
    *@param health - The starting health, designed to be 1000.
    *@param strength - How strong the warrior is. This may change based on health.
    *@param incap - This is used to determine whether the warrior can go on their next move. Set this to false.
    *@param name - The name of the warrior
    */
    warrior(double health, double strength, bool incap, string name)
    {
        this->health=health;
        this->strength=strength;
        this->incap=incap;
        this->alive=true;
        this->name=name;
    }
    /**
    *Damage will remove a set amount of health from the warrior.
    *@param amount - The amount of health to take away.
    */
    void damage(double amount)
    {
        if(this->alive==true)
            this->health-=amount;

        if(this->health<=0)
            this->alive=false;
    }
};

/**
*For the amusement of the user two warriors will enter combat with one another.
*@param w1 - One warrior
*@param w2 - The other warrior.
*@param flipState - A fairness moderator that will keep turns in check. It is set via recursion.
*@return true if w1 wins, false otherwise. IN THE EVENT OF A TIE, A RANDOM NUMBER GUESSES THE WINNER.
*/
bool fight(warrior &w1, warrior& w2, bool flipState)
{
    cout <<"    /\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\"<<endl;
    cout <<"    ===========WARRIORS================="<<endl;
    cout <<"    /\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\"<<endl;
    do
    {
        const int battleModifier=5;
        double damage=0;
        unsigned int tempNum;//Determines who will go first.
        int times=0;//Keeps track of how many loops the program takes.
        tempNum=rand();//Even or odd will be tested.
        //Warrior 1
        if(flipState&&w1.incap!=true||(times==0&&tempNum%2!=0))
        {
w1Override:

            damage+=w1.strength;
            damage+=battleModifier;

            if(w2.incap==true)
                damage+=battleModifier;

            if(rand()%2!=0)
                w2.incap=true;
            damage+=(rand()%10)*battleModifier;

            w2.damage(damage);
        }//End if
        else if (w1.incap==true)
            w1.incap=false;
        damage=0;
        if(!flipState&&w2.incap!=true||(times==0&&tempNum%2==0))
        {
w2Override:

            damage+=w2.strength;
            damage+=battleModifier;

            if(w1.incap==true)
                damage+=battleModifier;
            if(rand()%2!=0)
                w1.incap=true;
            damage+=(rand()%10)*battleModifier;

            w1.damage(damage);
        }//End if
        else if(w2.incap==true)
            w2.incap=false;

        flipState=!flipState;
        times++;

        if(w1.health>0)
        {

            cout <<w1.name<<": "<<w1.health<<" hp remaining. ";
            if(w1.health>w2.health)
                cout <<"(winning)";
            else if (w1.health<w2.health)
                cout <<"(losing)";
            else if (w1.health==w2.health)
                cout <<"(tie)";

            cout <<endl;
        }
        else cout <<w1.name<<": "<<"0"<<" hp remaining."<<endl;

        if(w2.health>0)
            cout <<w2.name<<": "<<w2.health<<" hp remaining."<<endl;

        else cout <<w2.name<<": "<<"0"<<" hp remaining."<<endl;
        cout << endl;
        usleep(100000);
    }
    while(w1.alive==true&&w2.alive==true);

    if(w1.health!=w2.health)
        return w1.health>w2.health;
    else return rand()%2!=0;
}
