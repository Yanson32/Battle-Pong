#ifndef PONG_ENGIN_H
#define PONG_ENGIN_H

#include <GameUtilities/Engin/Engin.h>
#include <GameUtilities/Event/EventManager.h>
#include <GameUtilities/Log/LogManager.h>
#include <GameUtilities/Log/LogFormatter.h>

class Game: public GU::Engin::Engin, public GU::Evt::EventManager
{
    public:
        Game();
        GU::Log::LogManager logManager;
        void setPop(const bool pop);
        bool getPop() const; 
    private:
        bool m_pop = false;
};
#endif
