#include "Gui/TimerPanel.h"
#include <sstream>

namespace GU
{
    namespace Gui
    {
        TimerPanel::TimerPanel()
        {
            //ctor
            layout = tgui::HorizontalLayout::create();
            layout->setSize("100%", "100%");

            text = tgui::Label::create("Time: 0");
            text->getRenderer()->setTextColor(sf::Color::Black);
            text->setPosition("parent.width / 2 - (width / 2)", "0");
            this->add(text);

            //time = tgui::Label::create("0");
            //time->setPosition("parent.width / 4 * 3", "0");
            //time->getRenderer()->setTextColor(sf::Color::Black);
            //time->getRenderer()->setBackgroundColor(sf::Color::Green);
            //this->add(time);


        }

        void TimerPanel::init()
        {
            text->setText("Time: 0");
        }

        void TimerPanel::setTime(const int newTime)
        {
            std::stringstream ss;
            ss << newTime;
            text->setText("Time: " + ss.str());
        }

        int TimerPanel::getTime()const
        {
            std::stringstream ss(time->getText());
            int val;
            ss >> val;
            return val;
        }

        TimerPanel::~TimerPanel()
        {
            //dtor
        }
    }
}
