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

    if(detail=true)
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
