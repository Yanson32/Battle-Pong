#ifndef GUI_CUSTOMPANEL_H
#define GUI_CUSTOMPANEL_H
#include <TGUI/TGUI.hpp>
namespace Gui
{
    class CustomPanel: public tgui::Panel
    {
        public:
            CustomPanel();
            virtual ~CustomPanel();
        protected:
            tgui::Panel::Ptr spacer;
            tgui::VerticalLayout::Ptr mainLayout;
            tgui::HorizontalLayout::Ptr tabLayout;
            tgui::HorizontalLayout::Ptr layout1;
            tgui::HorizontalLayout::Ptr layout2;
            tgui::HorizontalLayout::Ptr layout3;
            tgui::HorizontalLayout::Ptr layout4;
            tgui::HorizontalLayout::Ptr layout5;
            tgui::HorizontalLayout::Ptr layout6;
            tgui::HorizontalLayout::Ptr buttonLayout;
            int buttonTextSize = 30;
    };
}
#endif // GUI_CUSTOMPANEL_H
