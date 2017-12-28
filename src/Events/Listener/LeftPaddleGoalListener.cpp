#include "Events/Listeners/LeftPaddleGoalListener.h"
#include <iostream>

LeftPaddleGoalListener::LeftPaddleGoalListener()
{
    //ctor
}

void LeftPaddleGoalListener::OnEvent(Evt::EventPtr event)
{
    std::cout << "LeftPaddleGoalListener event" << std::endl;
}

LeftPaddleGoalListener::~LeftPaddleGoalListener()
{
    //dtor
}
