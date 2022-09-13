#ifndef EVENT_ID_H
#define EVENT_ID_H
/*************************************************************************
*                           COPYRIGHT NOTICE
* Battle Pong is a clone of the classic pong game.
* Copyright (C) 2017 Wayne J Larson Jr. 
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 3 as 
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
***************************************************************************/
#include <GameUtilities/Event/EventId.h>

enum EventId
{
    CHANGE_STATE            = static_cast<int>(GU::Evt::EventId::CHANGE_STATE),
    PUSH_STATE              = static_cast<int>(GU::Evt::EventId::PUSH_STATE),
    POP_STATE               = static_cast<int>(GU::Evt::EventId::POP_STATE),
    MUSIC_VOLUME_CHANGED    = static_cast<int>(GU::Evt::EventId::MUSIC_VOLUME_CHANGED),
    PLAY_MUSIC              = static_cast<int>(GU::Evt::EventId::PLAY_MUSIC),
    PLAY_SOUND              = static_cast<int>(GU::Evt::EventId::PLAY_SOUND),
    SOUND_VOLUME_CHANGED    = static_cast<int>(GU::Evt::EventId::SOUND_EFFECTS_VOLUME_CHANGED),
    CLICK                   = static_cast<int>(GU::Evt::EventId::CLICK),
    SLIDER_CHANGED          = static_cast<int>(GU::Evt::EventId::SLIDER_CHANGED),
    ON_CHECK                = static_cast<int>(GU::Evt::EventId::ON_CHECK),
    ON_COMBO_CHANGED        = static_cast<int>(GU::Evt::EventId::ON_COMBO_CHANGED),
    LOG                     = static_cast<int>(GU::Evt::EventId::LOG),
    ON_TEXT_CHANGED         = static_cast<int>(GU::Evt::EventId::ON_TEXT_CHANGED),
    GU_HIGHEST              = static_cast<int>(GU::Evt::EventId::HIGHEST),
    BALL_COLLISION,
    GOAL_COLLISION,
    LEFT_GOAL_COLLISION,
    RIGHT_GOAL_COLLISION,
	PADDLE_COLLISION,
};

#endif // ID_H
