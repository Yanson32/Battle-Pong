#include "Gui/IntroState/ControlPanel.h"
#include "Settings.h"
#include "Macros.h"

namespace Gui
{
    ControlPanel::ControlPanel(DebugDraw *debugDraw):
    OptionsPanel::OptionsPanel("Controls")
    {
        UNUSED(debugDraw);

        //Create up button editbox
        upEditBox = tgui::EditBox::create();
	    upEditBox->setText(Settings::playerControlUp);
        getContentPane()->append("Up", upEditBox);


        //Create down button editbox
        downEditBox = tgui::EditBox::create();
        downEditBox->setText(Settings::playerControlDown); 
	    getContentPane()->append("Up", downEditBox);

    }

    void ControlPanel::init(const int &width, const int &height)
    {
        tabs->select("Controls");
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);

    }
    ControlPanel::~ControlPanel()
    {

    }
}
