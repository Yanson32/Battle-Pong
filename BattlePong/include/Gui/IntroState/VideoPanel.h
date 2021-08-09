#ifndef GUI_VIDEOPANEL_H
#define GUI_VIDEOPANEL_H
#include "Gui/IntroState/OptionsPanel.h"

namespace Gui
{
    class VideoPanel: public OptionsPanel
    {
        public:
            VideoPanel();
            void init(const int &width, const int &height);
            
            tgui::Label::Ptr themeLabel; 
            tgui::ComboBox::Ptr themeCombo;
            
            tgui::Label::Ptr backgroundLable;
            tgui::ComboBox::Ptr backgroundCombo;
            
            tgui::Label::Ptr resolutionLable;
            tgui::ComboBox::Ptr resolutionCombo;
            
            virtual ~VideoPanel();
    };
}

#endif 
