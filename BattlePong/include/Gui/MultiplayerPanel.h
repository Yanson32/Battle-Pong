#ifndef MULTIPLAYER_PANEL_H
#define MULTIPLAYER_PANEL_H

#include "Gui/CustomPanel.h"
#include <TGUI/TGUI.hpp>
class MultiplayerPanel: public Gui::CustomPanel
{
    public:
        MultiplayerPanel();
        ~MultiplayerPanel();
    private:
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
#endif
