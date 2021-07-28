#ifndef GUI_DEVPANEL_H
#define GUI_DEVPANEL_H
#include "Gui/IntroState/OptionsPanel.h"
#include <Box2D/Common/b2Math.h>
class DebugDraw;
namespace Gui
{
    class DevPanel: public OptionsPanel
    {
        public:
            DevPanel();
            void init(const sf::String selected, const int32 flags);
            virtual ~DevPanel();
        protected:
            tgui::CheckBox::Ptr aabb;
            tgui::CheckBox::Ptr shapes;
            tgui::CheckBox::Ptr joints;
            tgui::CheckBox::Ptr centerOfMass;
            tgui::CheckBox::Ptr pair;
    };
}
#endif // GUI_DEVPANEL_H
