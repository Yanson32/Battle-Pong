#ifndef GUI_GENERALPANEL_H
#define GUI_GENERALPANEL_H
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
#include "Settings.h"
#include "States/StateId.h"

class DebugDraw;

namespace Gui
{
    class GeneralPanel: public OptionsPanel
    {
        public:
            GeneralPanel(const StateId state = Settings::stateId);
            void init(const int &width, const int &height);
            virtual ~GeneralPanel();
        protected:
            tgui::ComboBox::Ptr comboBox;
            tgui::Label::Ptr comboLable;

            tgui::ComboBox::Ptr aiCombo;
            tgui::Label::Ptr aiLable;
    };
}
#endif // GUI_GENERALPANEL_H
