#ifndef PADDLEHUD_H
#define PADDLEHUD_H
#include <TGUI/TGUI.hpp>
#include "Settings.h"
#include <memory>

class PaddleHud: public tgui::Panel
{
    public:
        PaddleHud(Settings::PaddleSettings &newPaddleSettings);
        void setScore(const int newScore);
        void setName(const sf::String &name);
        virtual ~PaddleHud();
    protected:
    private:
        Settings::PaddleSettings &paddleSettings;
        tgui::Label::Ptr scoreLabel;
        tgui::Label::Ptr panleLable;
};

#endif // PADDLEHUD_H
