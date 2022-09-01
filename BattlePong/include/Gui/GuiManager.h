#ifndef GUIMANAGER_H
#define GUIMANAGER_H
#include <TGUI/TGUI.hpp>
#include "Gui/CustomPanel.h"

namespace GU
{
    namespace Gui
    {
        class GuiManager
        {
            public:
                GuiManager(tgui::Gui &newGui);
                void push(std::shared_ptr<Gui::CustomPanel> newGui);
                void pop(std::shared_ptr<Gui::CustomPanel> newGui);
                virtual ~GuiManager();
            protected:
            private:
                tgui::Gui &gui;
                std::stack<std::shared_ptr<Gui::CustomPanel>> guiStack;
        };
    }
}
#endif // GUIMANAGER_H
