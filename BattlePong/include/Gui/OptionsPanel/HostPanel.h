#ifndef HOST_PANEL_H
#define HOST_PANEL_H

#include "Gui/CustomPanel.h"
#include <TGUI/TGUI.hpp>
class HostPanel: public Gui::CustomPanel
{
    public:
        HostPanel();
        void init(const int &width, const int &height);
        ~HostPanel();
    private:
        tgui::Button::Ptr backBtn;
        tgui::Label::Ptr publicIpLabel;
        tgui::Label::Ptr publicIpAdress;
        tgui::Label::Ptr localIpLabel;
        tgui::Label::Ptr localIpBox;
        tgui::Label::Ptr portLabel;
        tgui::EditBox::Ptr portBox;
        tgui::Button::Ptr hostButton;
};
#endif
