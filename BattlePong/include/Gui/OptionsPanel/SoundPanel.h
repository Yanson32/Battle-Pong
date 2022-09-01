#ifndef GUI_SOUNDPANEL_H
#define GUI_SOUNDPANEL_H
#include "Gui/OptionsPanel/OptionsPanel.h"
class DebugDraw;

namespace GU
{
    namespace Gui
    {
        class SoundPanel: public OptionsPanel
        {
            public:
                SoundPanel(DebugDraw *debugDraw);
                void init(const int &width, const int &height);
                virtual ~SoundPanel();
            protected:
                tgui::Slider::Ptr effectsSlider;
                tgui::Label::Ptr effectsLabel;

                tgui::Slider::Ptr musicSlider;
                tgui::Label::Ptr musicLabel;

                tgui::ComboBox::Ptr musicBox;
        };
    }
}
#endif // GUI_SOUNDPANEL_H
