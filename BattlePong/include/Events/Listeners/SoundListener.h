#ifndef SOUNDLISTENER_H
#define SOUNDLISTENER_H
#include <GameUtilities/Event/Listener.h>
#include <SFML/Audio/Sound.hpp>

class SoundListener: public GU::Evt::Listener
{
    public:
        SoundListener();
        virtual void OnEvent(GU::Evt::EventPtr event) override;
        virtual ~SoundListener();
    protected:
    private:
        static sf::Sound listenerSound;
};

#endif // SOUNDLISTENER_H
