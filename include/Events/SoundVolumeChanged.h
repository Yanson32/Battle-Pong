#ifndef SOUNDVOLUMECHANGED_H
#define SOUNDVOLUMECHANGED_H
#include "Events/EventBase.h"

class SoundVolumeChanged: public EventBase
{
    public:
        SoundVolumeChanged();
        virtual ~SoundVolumeChanged();
    protected:
    private:
};

#endif // SOUNDVOLUMECHANGED_H
