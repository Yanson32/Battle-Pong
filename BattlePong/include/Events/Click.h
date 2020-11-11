#ifndef CLICK_H
#define CLICK_H
#include "Events/EventBase.h"

class Click: public EventBase
{
    public:
        Click(const int newButtonId);
        const int buttonId = -1;
        virtual ~Click();
    protected:
    private:

};

#endif // CLICK_H
