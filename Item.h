/*
A completely redone version of Item.h
*/
#include <iostream>
using namespace std;
/**
*Like last time, this is the superstruct of all items.
*/
struct Item
{
    double width;
    double height;
    double durability;
    string name;
    bool alive;
    double power;//Electricity, or muscular strength if the item lives.
    double weight;
    short x;
    string heldItems[10];//The maximum number of held items
    short heldItemsCount;
    /**
    *Constructor for Items.
    *@param width - The width of the item.
    *@param height - How tall the object is.
    *@param durability - How durable the item is.
    *@param name - The generic name of the item.
    *@param alive - Whether or not the item is alive.
    *@param power - How powerful, if at all, the item is.
    */
    Item(double width, double height, double durability, string name, bool alive, double power, double weight)
    {
        this->width=width;
        this->height=height;
        this->durability=durability;
        this->name=name;
        this->alive=alive;
        this->power=power;
        this->weight=weight;

        heldItemsCount=0;
        x=0;
    }
    /**
    *Two items will make contact, reducing the first items durability by the second item's power.
    *This is less specialized than some of the other structure's functions.
    *@param otherItem
    **/
    void slam(Item otherItem)
    {
        this->durability-=otherItem.power;

        if(this->alive==true&&durability<=0)
            alive=false;
    }
    /**
    *Damages the item by a set amount.
    *@param amount - The amount to decrease durability by.
    */
    void damage(double amount)
    {
        this->durability-=amount;
    }
    /**
    *Adds the stats of the item to that of this item.
    *@param the item to add.
    */
    void addItem(Item toAdd)
    {

        this->width+=toAdd.width;
        this->height+=toAdd.height;//Questionable
        this->durability+=toAdd.durability;
        this->power+=toAdd.power;
        this->weight+=toAdd.weight;

        heldItems[heldItemsCount]=toAdd.name;
        heldItemsCount++;
    }
};
/**
*Human is the superstruct for all humanoids.
*/
struct human:Item
{
    string indName;
    /**
    *Constructor for humans.
        *@param indName - The name of the human, an example would be George.
        *@param width - The width of the item.
        *@param height - How tall the object is.
        *@param durability - How durable the item is.
        *@param name - The generic name of the item.
        *@param alive - Whether or not the item is alive.
        *@param power - How powerful, if at all, the item is.
    */
    human(string indName, double width, double height, double durability, string name, bool alive, double power, double weight)
        :Item(width,height, durability, name, alive, power, weight)
    {
        this->indName=indName;
    }
};
/**
*Warrior is a substruct of human, which is itself derived from struct item.
*Warriors are designed for fighting and are used in Warriors.h
*/
struct warrior:human
{
    //!How armored the warrior is.
    double defenseVal;

    //!How experienced the warrior is.
    double experience;
    //!How prepared the warrior is.
    double stamina;
    //!Whether or not the warrior is incapacitated
    bool incap;
    /**
    *Constructor for warriors.
    *@param defenseVal - How much armor the warrior has. 10 is a sane amount.
    *@param experience - How experienced the warrior is. 10 is a sane amount.
    *@param indName - The name of the human, an example would be George.
    *@param width - The width of the item.
    *@param height - How tall the object is.
    *@param durability - How durable the item is.
    *@param name - The generic name of the item.
    *@param alive - Whether or not the item is alive.
    *@param power - How powerful, if at all, the item is.
    */
    warrior(double defenseVal, double experience, string indName, double width, double height, double durability, string name, bool alive, double power, double weight):
        human(indName,width,height, durability, name, alive, power, weight)
    {
        this->defenseVal=defenseVal;
        this->experience=experience;
        this->stamina=100;
        this->alive=true;
    }
    /**
    *Strikes the warrior with an attack.
    *@param w2 - The warrior to attack.
    */
    void attack(warrior & w2)
    {
        if(!this->incap)
        {

            double damage=0;
            const int battleModifier=10;

            damage+=this->power;
            damage+=battleModifier;
            damage+=this->weight/battleModifier;
            damage+=this->experience;
            damage+=(rand()%10)*battleModifier;

            damage-=w2.defenseVal;

            if(w2.incap==true)
            {
                damage+=battleModifier;
                w2.incap=false;
            }

            if(rand()%2!=0)//50% chance
                w2.incap=true;


            w2.damage(damage);

            if(w2.durability<=0)
                w2.alive=false;

            damage=0;
        }//End if
        else this->incap=false;
    }//End attack
};
