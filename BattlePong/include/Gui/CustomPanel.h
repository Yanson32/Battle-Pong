#ifndef GUI_CUSTOMPANEL_H
#define GUI_CUSTOMPANEL_H
#include <TGUI/TGUI.hpp>
#include <memory>

namespace GU
{
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

}

#endif // GUI_CUSTOMPANEL_H
