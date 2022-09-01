#include "Gui/OptionsPanel/SoundPanel.h"
//#include "Event/Object.h"
#include "Events/EventManager.h"
#include "Macros.h"
#include "Settings.h"
#include <GameUtilities/Event/OnSliderChanged.h>
#include <GameUtilities/Event/PlayMusic.h>
#include "Gui/GuiId.h"

namespace Gui
{
    SoundPanel::SoundPanel(DebugDraw *debugDraw):
    OptionsPanel::OptionsPanel(sf::String("Sound"))
    {
        UNUSED(debugDraw);

        getContentPane()->appendSpace();

        //Create effects slider
        effectsSlider = tgui::Slider::create(0, 100);
        effectsSlider->setValue(Settings::mVolume);
        effectsSlider->onValueChange([&](){
            Settings::sVolume = effectsSlider->getValue();
            EventManager::inst().Post<GU::Evt::OnSliderChanged>(Gui::id::SOUND_EFFECTS, Settings::sVolume);
        });
        getContentPane()->append("Sound Effects", effectsSlider);

        musicSlider = tgui::Slider::create(0, 100);
        musicSlider->setValue(Settings::sVolume);
        musicSlider->onValueChange([&](){
            Settings::mVolume = musicSlider->getValue();
            EventManager::inst().Post<GU::Evt::OnSliderChanged>(Gui::id::MUSIC, Settings::mVolume);
        });
        getContentPane()->append("Music Volume", musicSlider);


        musicBox = tgui::ComboBox::create();
        musicBox->addItem("Zombies");
        musicBox->addItem("Dreams");
        musicBox->setSelectedItem(Settings::currentSong.toAnsiString());
        musicBox->onItemSelect([&](){
            if(musicBox->getSelectedItem() == "Zombies")
            {
                EventManager::inst().Post<GU::Evt::PlayMusic>("Zombies");
            }
            else if(musicBox->getSelectedItem() == "Dreams")
            {
                EventManager::inst().Post<GU::Evt::PlayMusic>("Dreams");
            }
            else
            {
                EventManager::inst().Post<GU::Evt::PlayMusic>("");
                Settings::currentSong = "";
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
