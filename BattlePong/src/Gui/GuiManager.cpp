#include "Gui/GuiManager.h"
#include "Macros.h"


namespace GU
{
    namespace Gui
    {
        GuiManager::GuiManager(tgui::Gui &newGui):
        gui(newGui)
        {
            //ctor
        }

        void GuiManager::push(std::shared_ptr<Gui::CustomPanel> newGui)
        {
            gui.removeAllWidgets();
            gui.add(newGui);
            guiStack.push(newGui);
        }

        void GuiManager::pop(std::shared_ptr<Gui::CustomPanel> newGui)
        {
            UNUSED(newGui);

            if(!guiStack.empty())
            {
                guiStack.pop();
            }
        }

        GuiManager::~GuiManager()
        {
            //dtor
        }
    }
}
