#ifndef SCOREPANEL_H
#define SCOREPANEL_H
#include <TGUI/TGUI.hpp>
#include <string>

namespace GU
{
    namespace Gui
    {
        class ScorePanel:
        public tgui::Panel
        {
            public:
                ScorePanel(const sf::String &text);
                void setScore(const int newScore);
                int getScore() const;
                virtual ~ScorePanel();
            protected:
            private:
                tgui::Label::Ptr paddleLable;
                std::string text;
                int score = 0;
                //tgui::Label::Ptr scoreLable;
                //int score = 0;
        };
    }
}
#endif // SCOREPANEL_H
