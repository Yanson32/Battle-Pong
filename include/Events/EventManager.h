#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <GameUtilities/Event/EventManager.h>

class EventManager: public GU::Evt::EventManager
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
