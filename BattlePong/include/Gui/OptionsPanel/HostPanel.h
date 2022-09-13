#ifndef HOST_PANEL_H
#define HOST_PANEL_H
/*************************************************************************
*                           COPYRIGHT NOTICE
* Battle Pong is a clone of the classic pong game.
* Copyright (C) 2017 Wayne J Larson Jr. 
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 3 as 
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
***************************************************************************/
#include "Gui/CustomPanel.h"
#include <TGUI/TGUI.hpp>

namespace Gui
{
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
}
#endif
