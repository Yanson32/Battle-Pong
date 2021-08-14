#include "Gui/IntroState/SoundPanel.h"
//#include "Event/Object.h"
#include "Events/EventManager.h"
#include "Macros.h"
#include "Settings.h"
#include <GameUtilities/Event/OnSliderChanged.h>
#include <GameUtilities/Event/PlayMusic.h>
#include "Gui/SliderId.h"

namespace Gui
{
    SoundPanel::SoundPanel(DebugDraw *debugDraw):
    OptionsPanel::OptionsPanel(sf::String("Sound"))
    {
        UNUSED(debugDraw); 
         
        //Create effects slider
        effectsSlider = tgui::Slider::create(0, 100);
        effectsSlider->setValue(Settings::music.mVolume); 
        effectsSlider->onValueChange([&](){
            Settings::music.sVolume = effectsSlider->getValue();
            EventManager::inst().Post<GU::Evt::OnSliderChanged>(sliderId::SOUND_EFFECTS, Settings::music.sVolume);
        });
        getContentPane()->append("Sound Effects", effectsSlider);

        musicSlider = tgui::Slider::create(0, 100);
        musicSlider->setValue(Settings::music.sVolume);
        musicSlider->onValueChange([&](){
            Settings::music.mVolume = musicSlider->getValue();
            EventManager::inst().Post<GU::Evt::OnSliderChanged>(sliderId::MUSIC, Settings::music.mVolume);
        });
        getContentPane()->append("Music Volume", musicSlider);

             
        musicBox = tgui::ComboBox::create();
        musicBox->addItem("Zombies");
        musicBox->addItem("Dreams"); 
        musicBox->setSelectedItem(Settings::music.currentSong.toAnsiString());
        musicBox->onItemSelect([&](){
            if(musicBox->getSelectedItem() == "Zombies")
            {
                EventManager::inst().Post<GU::Evt::PlayMusic>("Resources/Music/Electro_Zombies.ogg");
                Settings::music.currentSong = "Zombies";
            }
            else if(musicBox->getSelectedItem() == "Dreams") 
            {    
                EventManager::inst().Post<GU::Evt::PlayMusic>("Resources/Music/the_field_of_dreams.ogg");
                Settings::music.currentSong = "Dreams";
            }
            else
            {     
                EventManager::inst().Post<GU::Evt::PlayMusic>("");
                Settings::music.currentSong = "";
            } 

                
        });
        getContentPane()->append("Music Selection", musicBox);
    }
    void SoundPanel::init(const int &width, const int &height)
    {
        tabs->select("Sound");
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);
    }
    SoundPanel::~SoundPanel()
    {

    }
}
