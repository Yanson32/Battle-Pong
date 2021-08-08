#ifndef GUI_NETWORKPANEL_H
#define GUI_NETWORKPANEL_H
#include "Gui/IntroState/OptionsPanel.h"
namespace Gui
{
    class NetworkPanel: public OptionsPanel
    {
        public:
            NetworkPanel();
            void init(const int &width, const int &height);
            virtual ~NetworkPanel();
        protected:
            tgui::Label::Ptr globalIpLabel;
            tgui::Label::Ptr globalIp;
            
            tgui::Label::Ptr localIpLabel;
            tgui::Label::Ptr localIp;

            tgui::Label::Ptr portBoxLabel;
            tgui::Label::Ptr portBox;
    };
}

#endif // GUI_SOUNDPANEL_H
