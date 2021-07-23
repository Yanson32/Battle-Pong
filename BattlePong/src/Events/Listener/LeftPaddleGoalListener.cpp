#include "Events/Listeners/LeftPaddleGoalListener.h"
#include "Macros.h"

LeftPaddleGoalListener::LeftPaddleGoalListener()
{
    //ctor
}

void LeftPaddleGoalListener::OnEvent(GU::Evt::EventPtr event)
{
    UNUSED(event);
    //std::cout << "LeftPaddleGoalListener event" << std::endl;
}

LeftPaddleGoalListener::~LeftPaddleGoalListener()
{
    //dtor
}
