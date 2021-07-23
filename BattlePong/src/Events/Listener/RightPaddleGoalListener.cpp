#include "Events/Listeners/RightPaddleGoalListener.h"
#include "Macros.h"

RightPaddleGoalListener::RightPaddleGoalListener()
{
    //ctor
}

void RightPaddleGoalListener::OnEvent(GU::Evt::EventPtr event)
{
    UNUSED(event);
    //std::cout << "RightPaddleGoalListener" << std::endl;
}

RightPaddleGoalListener::~RightPaddleGoalListener()
{
    //dtor
}
