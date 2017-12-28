#ifndef MUSICVOLUMECHANGED_H
#define MUSICVOLUMECHANGED_H
#include "Events/EventBase.h"

class MusicVolumeChanged: public EventBase
{
    public:
        MusicVolumeChanged();
        int volume = 255;
        virtual ~MusicVolumeChanged();
    protected:
    private:
};

#endif // MUSICVOLUMECHANGED_H
