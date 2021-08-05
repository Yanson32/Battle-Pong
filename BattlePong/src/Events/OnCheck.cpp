#include "Events/OnCheck.h"
#include "Events/Id.h"
OnCheck::OnCheck(const int newCheckBoxId, const bool newChecked):
EventBase(EventId::ON_CHECK),
checkboxId(newCheckBoxId),
checked(newChecked)
{
    //ctor
}

OnCheck::~OnCheck()
{
    //dtor
}
