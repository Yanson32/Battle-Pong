#ifndef EVENT_ID_H
#define EVENT_ID_H
#include <GameUtilities/Event/Id.h>

enum EventId
{
    CHANGE_STATE            = GU::Evt::Id::CHANGE_STATE,
    PUSH_STATE              = GU::Evt::Id::PUSH_STATE,
    POP_STATE               = GU::Evt::Id::POP_STATE,
    MUSIC_VOLUME_CHANGED    = GU::Evt::Id::MUSIC_VOLUME_CHANGED,
    PLAY_MUSIC              = GU::Evt::Id::PLAY_MUSIC,
    PLAY_SOUND              = GU::Evt::Id::PLAY_SOUND,
    SOUND_VOLUME_CHANGED    = GU::Evt::Id::SOUND_EFFECTS_VOLUME_CHANGED,
	CLICK                   = GU::Evt::Id::CLICK,
    SLIDER_CHANGED          = GU::Evt::Id::SLIDER_CHANGED,
    ON_CHECK                = GU::Evt::Id::ON_CHECK,
    BALL_COLLISION,
    GOAL_COLLISION,
    LEFT_GOAL_COLLISION,
    RIGHT_GOAL_COLLISION,
	PADDLE_COLLISION,
};

#endif // ID_H
