#ifndef GUI_DEVPANEL_H
#define GUI_DEVPANEL_H
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
#include <Box2D/Common/b2Math.h>
class DebugDraw;

namespace Gui
{
    class DevPanel: public OptionsPanel
    {
        public:
            DevPanel();
            void init(const int32 flags, const int &width, const int &height);
            virtual ~DevPanel();
        protected:
            tgui::CheckBox::Ptr aabb;
            tgui::CheckBox::Ptr shapes;
            tgui::CheckBox::Ptr joints;
            tgui::CheckBox::Ptr centerOfMass;
            tgui::CheckBox::Ptr pair;

            tgui::EditBox::Ptr log;

            tgui::ComboBox::Ptr logLevelComboBox;
            tgui::EditBox::Ptr velocityIterationsBox;
            tgui::EditBox::Ptr positionIterationsBox;
            tgui::EditBox::Ptr frameRateBox;
            tgui::EditBox::Ptr ballSpeedBox;
            tgui::EditBox::Ptr paddleSpeedBox;
            tgui::EditBox::Ptr wallThicknessBox;
            tgui::EditBox::Ptr ballRadiusBox;
            void onLogLevel();
    };
}
#endif // GUI_DEVPANEL_H
