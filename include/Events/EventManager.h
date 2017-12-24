#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <GameUtilities/Event/Manager.h>

class EventManager: public Evt::Manager
{
    public:
        static EventManager& inst();
        virtual ~EventManager();
    private:
        EventManager();
        EventManager operator = (const EventManager eventManager) = delete;
        EventManager(const EventManager &EventManager) = delete;
};
#endif // EVENTMANAGER_H
