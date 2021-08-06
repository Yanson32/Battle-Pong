#include "Events/Click.h"
#include "Events/EventId.h"
Click::Click(const int newButtonId):
EventBase(EventId::CLICK),
buttonId(newButtonId)
{
    //ctor
}

Click::~Click()
{
    //dtor
}
