#include "Events/Listeners/RightPaddleGoalListener.h"
#include <iostream>

RightPaddleGoalListener::RightPaddleGoalListener()
{
    //ctor
}

void RightPaddleGoalListener::OnEvent(Evt::EventPtr event)
{
    std::cout << "RightPaddleGoalListener" << std::endl;
}

RightPaddleGoalListener::~RightPaddleGoalListener()
{
    //dtor
}
