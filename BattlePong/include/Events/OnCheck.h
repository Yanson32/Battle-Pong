#ifndef ON_CHECK_H 
#define ON_CHECK_H 
#include "Events/EventBase.h"

class OnCheck: public EventBase
{
    public:
        OnCheck(const int newCheckBoxId, const bool newChecked);
        const int checkboxId = -1;
        const bool checked;
        virtual ~OnCheck();
    protected:
    private:

};

#endif 
