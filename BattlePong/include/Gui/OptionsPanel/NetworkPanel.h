#ifndef GUI_NETWORKPANEL_H
#define GUI_NETWORKPANEL_H
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
#include "Gui/OptionsPanel/OptionsPanel.h"

namespace Gui
{
    class NetworkPanel: public OptionsPanel
    {
        public:
            NetworkPanel();
            void init(const int &width, const int &height);
            virtual ~NetworkPanel();
        protected:
            tgui::Label::Ptr publicIpLabel;
            tgui::Label::Ptr publicIp;
            
            tgui::Label::Ptr localIpLabel;
            tgui::Label::Ptr localIp;

            tgui::Label::Ptr portBoxLabel;
            tgui::Label::Ptr portBox;
    };
}
#endif // GUI_SOUNDPANEL_H
