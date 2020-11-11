#ifndef MUSICLISTENER_H
#define MUSICLISTENER_H
#include <GameUtilities/Event/Listener.h>
#include <SFML/Audio/Music.hpp>

class MusicListener: public GU::Evt::Listener
{
    public:
        MusicListener();
        virtual void OnEvent(GU::Evt::EventPtr event) override;
        virtual ~MusicListener();
    protected:
    private:
        static sf::Music music;
};



#endif // MUSICLISTENER_H
