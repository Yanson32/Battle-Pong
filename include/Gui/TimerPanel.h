#ifndef TIMERPANEL_H
#define TIMERPANEL_H

#include <TGUI/TGUI.hpp>

namespace Gui
{
    class TimerPanel: public tgui::Panel
    {
        public:
            TimerPanel();
            void init();
            void setTime(const int newTime);
            int getTime()const;
            virtual ~TimerPanel();
        protected:
        private:
            tgui::Label::Ptr text;
            tgui::Label::Ptr time;
            tgui::HorizontalLayout::Ptr layout;
    };
}
#endif // TIMERPANEL_H
