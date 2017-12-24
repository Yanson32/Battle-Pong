#ifndef SOUNDLISTENER_H
#define SOUNDLISTENER_H
#include <GameUtilities/Event/Listener.h>
#include <SFML/Audio/Sound.hpp>

class SoundListener: public Evt::Listener
{
    public:
        SoundListener();
        virtual void OnEvent(Evt::EventPtr event) override;
        virtual ~SoundListener();
    protected:
    private:
        sf::Sound listenerSound;
};

#endif // SOUNDLISTENER_H
