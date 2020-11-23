#ifndef SETTINGS_H
#define SETTINGS_H
/**********************************************************//**
*   @author Wayne J Larson Jr.
*   @date   12/25/17
*   @brief  The MusicSettings constructor
**************************************************************/

#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <TGUI/TGUI.hpp>
#include <SFML/Network.hpp>
#include "Events/Id.h"

namespace tempSettings 
{
	extern std::string playerControlUp;
	extern std::string playerControlDown;
	extern sf::Vector2f wDimensions;
	
	struct PaddleSettings
	{
		std::string input;
		std::string name;
		int score;
	};

	extern PaddleSettings paddle1;
	extern PaddleSettings paddle2;
}



/**********************************************************//**
*   @brief  Settings for music
**************************************************************/
class MusicSettings: public tgui::Panel
{
    public:
        MusicSettings();
        int getVolume() const;
        int getSoundVolume() const;
    private:
        tgui::Slider::Ptr musicVolume;
        tgui::Slider::Ptr soundVolume;
        int mVolume = 200;
        int sVolume = 150;
        void onMusicVolume();
        void onSoundVolume();

};

class ServerSettings
{
    public:
        ServerSettings();
        bool isConnected();
        void init();
        void clean();
        void handleEvents();
        bool update();
        sf::Packet recieve();
        virtual ~ServerSettings();
    protected:
    private:
        sf::TcpSocket socket;
        sf::TcpListener listener;
        bool connected = false;
        int port = 4000;
        sf::IpAddress address;
};

class ClientSettings
{
    public:
        ClientSettings();
        bool isConnected();
        void init();
        void clean();
        void handleEvents();
        bool update();
        void setTimeOut(const sf::Time &newTime);
        void setIp(const sf::String newIp);
        void setPort(const int newPort);
        sf::String getIp() const;
        int getPort() const;
        virtual ~ClientSettings();
    protected:
    private:
        int port = 5000;
        sf::String ip = "127.0.0.0.1";
        sf::TcpSocket socket;
        sf::Time timeOut;
};

/**********************************************************//**
*   @brief  A singleton that contains all game settings
**************************************************************/
class Settings
{
public:
	sf::String getTitle() const;
	static Settings& inst();
	sf::Vector2f buttonSize() const;
	sf::Vector2f buttonPosition(const unsigned pos = 0) const;
    	//std::shared_ptr<PaddleSettings> paddle1;
	//std::shared_ptr<PaddleSettings> paddle2;
	std::shared_ptr<MusicSettings> musicSettings;
	std::shared_ptr<ClientSettings> clientSettings;
	std::shared_ptr<ServerSettings> serverSettings;
	sf::Vector2f screen;
	~Settings();
private:
	sf::String title;
	Settings();
	Settings operator = (const Settings settings) = delete;
	Settings(const Settings &settings) = delete;

	sf::Vector2f bSize;
	sf::Vector2f bPosition;
};


#endif
