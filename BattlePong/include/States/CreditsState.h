#ifndef BP_CREDITS_STATE_H
#define BP_CREDITS_STATE_H
#include <GameUtilities/Engin/Frame.h>
#include "States/StateBase.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Box2D/DebugDraw.h"
#include <TGUI/TGUI.hpp>

class CreditsState: public StateBase
{
  public:
    CreditsState(GU::Engin::Engin& engin, sf::RenderWindow &newWindow, DebugDraw &debugDraw, tgui::Gui &newGui);
    virtual void HandleEvents(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override;
    virtual void Update(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override;
    virtual void Draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override;
    void handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event, std::shared_ptr<GU::Engin::Frame> frame);
    void sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame);
    virtual void Init(std::shared_ptr<GU::Engin::Frame> frame) ;
    virtual void Clean(std::shared_ptr<GU::Engin::Frame> frame) override;
    virtual ~CreditsState();
};

#endif
