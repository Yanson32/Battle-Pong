#ifndef WRITE_LOG_H
#define WRITE_LOG_H
#include "Engin/Game.h"

class WriteLog
{
    public:
        WriteLog(Game &game);
        static void write(Game &game);
        virtual ~WriteLog();
    private:
        Game &m_game;
};

#endif

