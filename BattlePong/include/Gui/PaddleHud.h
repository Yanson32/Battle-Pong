#ifndef PADDLEHUD_H
#define PADDLEHUD_H
#include <TGUI/TGUI.hpp>
#include "Settings.h"
#include <memory>


namespace Gui
{
    class PaddleHud: public tgui::Panel
    {
        public:
            PaddleHud(const std::string &input, std::string &name, int &score);
            void setScore(const int newScore);
            void setName(const sf::String &name);
            virtual ~PaddleHud();
        protected:
        private:
            std::string m_input;
            std::string m_name;
            int m_score;
            tgui::Label::Ptr scoreLabel;
            tgui::Label::Ptr panleLable;
    };
}
#endif // PADDLEHUD_H
