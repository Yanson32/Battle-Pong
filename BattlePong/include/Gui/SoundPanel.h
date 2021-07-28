#ifndef GUI_SOUNDPANEL_H
#define GUI_SOUNDPANEL_H
#include "Gui/IntroState/OptionsPanel.h"
class DebugDraw;
namespace Gui
{
    class SoundPanel: public OptionsPanel
    {
        public:
            SoundPanel(DebugDraw *debugDraw);
            void init();
            virtual ~SoundPanel();
        protected:
            tgui::Slider::Ptr effectsSlider;
            tgui::Label::Ptr effectsLable;

            tgui::Slider::Ptr musicSlider;
            tgui::Label::Ptr musicLable;

    };
}

#endif // GUI_SOUNDPANEL_H
