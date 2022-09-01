#ifndef CONNECT_PANEL_H 
#define CONNECT_PANEL_H 

#include "Gui/CustomPanel.h"
#include <TGUI/TGUI.hpp>


namespace Gui
{

    class ConnectPanel: public Gui::CustomPanel
    {
        public:
            ConnectPanel();
            void init(const int &width, const int &height);
            ~ConnectPanel();
        private:
            void onTextChanged();
            tgui::Button::Ptr backBtn;
            tgui::Label::Ptr globalIpLabel;
            tgui::Label::Ptr globalIpAdress;
            tgui::Label::Ptr localIpLabel;
            tgui::Label::Ptr localIpBox;
            tgui::Label::Ptr portLabel;
            tgui::EditBox::Ptr portBox;
            tgui::Button::Ptr hostButton;
            tgui::Button::Ptr connectButton;

            tgui::Label::Ptr ipLabel;
            tgui::EditBox::Ptr ipBox;
    };
}
#endif
