#include <iostream>
#include <sstream>
using namespace std;
struct item
{
    double height;
    double width;
    double weight;

    string name;
    string stateOfMatter;

    bool flammable;

    /**
    *Item is the base structure for all subclasses.
    *Every item should have these properties.
    *@param height - The height of the object (feet).
    *@param width  - The width of the object (feet).
    *@param weight - The weight of the object. (Pounds)
    *@param name   - The GENERIC name of the item. Birch wood, for example, would be wood.
    *@param state  - The state of matter. The common states of matter are liquid, solid, and gas.
    *@param flame  - Whether or not the item is flammable.
    */
    item(double h, double w,double weight, string n,
         string state, bool flame)
    {
        this->height=h;
        this->width=w;
        this->weight=weight;
        this->name=n;
        this->flammable=flame;
        this->stateOfMatter=state;
    }

};
struct wood:item
{
    string type;
    double age;
    wood(string type, double age, double h, double w,double weight, string n,
         string state, bool flame):item(h,w,weight,n,state,flame)
    {
        this->type=type;
        this->age=age;
    }
    /**
    *This will set the wood on fire, destroying it.
    *Only flammable items can be burned, but all wood should be declared as flammable.
    *@param the wood to burn.
    *@return 1 if the wood is burnt, 0 if it was not burnt.
    */
    short burn(wood toBurn)
    {
        if(toBurn.flammable==true)
        {
            this->type="Charcoal";

            height/=5.;
            width/=5.;
            weight/=5;
            name="Burnt wood";
            stateOfMatter="Solid";
            flammable=true;
            return 1;
        }
        else return 0;
    }
    /**
    *Returns information regarding the status of the wood.
    *@param the wood to retrieve.
    *@return A string representing the stats.
    */
    string getStats(wood toGet)
    {
        stringstream collector;
        string toReturn;
        //Substruct specific variables.
        collector << "Type: ";
        collector <<toGet.type;
        collector <<"\nAge: ";
        collector <<toGet.age;
        //Superstruct variables.
        collector <<"\nHeight: ";
        collector <<toGet.height;
        collector <<" feet.";
        collector <<"\nWidth: ";
        collector <<toGet.width;
        collector <<" feet.";
        collector <<"\nWeight: ";
        collector <<toGet.weight;
        collector <<" pounds.";
        collector <<"\nGeneric name: ";
        collector <<toGet.name;
        collector <<"\nState of Matter: ";
        collector <<toGet.stateOfMatter;
        collector <<"\nFlammable: ";

        if(toGet.flammable==true)
            collector <<"Yes.";
        else
            collector << "No.";

        collector <<"\n";

        return collector.str();
    }
};
struct firePlace:item
{
    bool status;
    double heat;

    firePlace(bool status, double heat,double h, double w,double weight, string n,
              string state, bool flame) :item(h,w,weight, n,
                          state,  flame)
    {
        this->status=status;
        this->heat=heat;
    }
    void flickStatus()
    {
        if(this->status==true)
            this->status=false;
        else this->status=true;
    }
    string getStats(firePlace toGet)
    {
        stringstream collector;

        if(status==true)
            collector <<"\nOn: Yes.";
        else
            collector << "\nOn: No.";

        collector << "\nHeat: "<<heat;
        collector <<"\nHeight: ";
        collector <<toGet.height;
        collector <<" feet.";
        collector <<"\nWidth: ";
        collector <<toGet.width;
        collector <<" feet.";
        collector <<"\nWeight: ";
        collector <<toGet.weight;
        collector <<" pounds.";
        collector <<"\nGeneric name: ";
        collector <<toGet.name;
        collector <<"\nState of Matter: ";
        collector <<toGet.stateOfMatter;
        collector <<"\nFlammable: ";
        if(toGet.flammable==true)
            collector <<"Yes.";
        else
            collector << "No.";
        collector <<"\n";
        return collector.str();
    }
};
/*
What I've learned from this program:
Use stringstream and stringstream.str();




*/

