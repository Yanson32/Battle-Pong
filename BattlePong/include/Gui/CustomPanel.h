#ifndef GUI_CUSTOMPANEL_H
#define GUI_CUSTOMPANEL_H
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
#include <TGUI/TGUI.hpp>
#include <memory>

namespace Gui
{
    class ContentPane;
    class CustomPanel: public tgui::ScrollablePanel
    {
        public:
            CustomPanel();
            void resize(const int &width, const int &height);
            std::shared_ptr<ContentPane> getContentPane(); 
            virtual ~CustomPanel();
        protected:
            tgui::Panel::Ptr spacer;
            tgui::VerticalLayout::Ptr mainLayout;
            tgui::HorizontalLayout::Ptr tabLayout;
            std::shared_ptr<ContentPane> contentPane = nullptr; 
            tgui::HorizontalLayout::Ptr buttonLayout;
            int buttonTextSize = 30;
    };


    class ContentPane: public tgui::ScrollablePanel
    {
        public:
            ContentPane();
            bool append(const tgui::String &label, std::shared_ptr<tgui::Widget> widget); 
            bool append(tgui::HorizontalLayout::Ptr layout);
            void appendHeader(const tgui::String &header);
            void append(const tgui::String &label, std::shared_ptr<tgui::CheckBox> check);
            void appendSpace(); 
            tgui::VerticalLayout::Ptr mainLayout;
            virtual ~ContentPane();
            int count = 0; 
            const int HEIGHT = 40; 
    };

}


#endif // GUI_CUSTOMPANEL_H
