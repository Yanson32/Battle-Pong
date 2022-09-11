#ifndef GUI_DEVPANEL_H
#define GUI_DEVPANEL_H
#include "Gui/OptionsPanel/OptionsPanel.h"
#include <Box2D/Common/b2Math.h>
class DebugDraw;

namespace Gui
{
    class DevPanel: public OptionsPanel
    {
        public:
            DevPanel();
            void init(const int32 flags, const int &width, const int &height);
            virtual ~DevPanel();
        protected:
            tgui::CheckBox::Ptr aabb;
            tgui::CheckBox::Ptr shapes;
            tgui::CheckBox::Ptr joints;
            tgui::CheckBox::Ptr centerOfMass;
            tgui::CheckBox::Ptr pair;

            tgui::EditBox::Ptr log;

            tgui::ComboBox::Ptr logLevelComboBox;
            tgui::EditBox::Ptr velocityIterationsBox;
            tgui::EditBox::Ptr positionIterationsBox;
            tgui::EditBox::Ptr frameRateBox;
            tgui::EditBox::Ptr ballSpeedBox;
            tgui::EditBox::Ptr paddleSpeedBox;
            tgui::EditBox::Ptr wallThicknessBox;
            tgui::EditBox::Ptr ballRadiusBox;
            void onLogLevel();
    };
}
#endif // GUI_DEVPANEL_H