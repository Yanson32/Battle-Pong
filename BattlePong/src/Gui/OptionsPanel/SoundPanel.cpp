#include "Gui/OptionsPanel/SoundPanel.h"
//#include "Event/Object.h"
#include "Events/EventManager.h"
#include "Macros.h"
#include "Settings.h"
#include <GameUtilities/Event/OnSliderChanged.h>
#include <GameUtilities/Event/OnComboChanged.h>
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
        effectsSlider->setValue(Settings::soundVolume);
        effectsSlider->onValueChange([&](){
            Settings::soundVolume = effectsSlider->getValue();
            EventManager::inst().post<GU::Evt::OnSliderChanged>(Gui::id::SOUND_EFFECTS, Settings::soundVolume);
        });
        getContentPane()->append("Sound Effects", effectsSlider);

        musicSlider = tgui::Slider::create(0, 100);
        musicSlider->setValue(Settings::musicVolume);
        musicSlider->onValueChange([&](){
            Settings::musicVolume = musicSlider->getValue();
            EventManager::inst().post<GU::Evt::OnSliderChanged>(Gui::id::MUSIC, Settings::musicVolume);
        });
        getContentPane()->append("Music Volume", musicSlider);


        musicBox = tgui::ComboBox::create();
        musicBox->addItem("Zombies");
        musicBox->addItem("Dreams");
        musicBox->setSelectedItem(Settings::currentSong.toAnsiString());
        musicBox->onItemSelect([&](){
                EventManager::inst().post<GU::Evt::OnComboChanged>(Gui::id::MUSIC_COMBO, musicBox->getSelectedItemIndex());
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
