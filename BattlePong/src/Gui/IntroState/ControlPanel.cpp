#include "Gui/IntroState/ControlPanel.h"
#include "Settings.h"
#include "Macros.h"

namespace Gui
{
    ControlPanel::ControlPanel(DebugDraw *debugDraw):
    OptionsPanel::OptionsPanel("Controls")
    {
        UNUSED(debugDraw);

        //Create up button lable
        upLabel = tgui::Label::create("Up");
        layout2->add(upLabel);


        //Create up button editbox
        upEditBox = tgui::EditBox::create();
	upEditBox->setText(Settings::playerControlUp);
        layout2->add(upEditBox);


        //Create down button lable
        downLabel = tgui::Label::create("Down");
        layout3->add(downLabel);
	 
        //Create down button editbox
        downEditBox = tgui::EditBox::create();
        downEditBox->setText(Settings::playerControlDown); 
	layout3->add(downEditBox);

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
