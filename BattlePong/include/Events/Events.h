#ifndef EVENTS_H
#define EVENTS_H
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

#include "GameUtilities/Event/Pop.h"
#include "GameUtilities/Event/ChangeState.h"
#include "GameUtilities/Event/PushState.h"
#include "GameUtilities/Event/PlayMusic.h"
#include "GameUtilities/Event/PlaySound.h"
#include "GameUtilities/Event/MusicVolumeChanged.h"
#include "GameUtilities/Event/SoundVolumeChanged.h"
#include "GameUtilities/Event/OnSliderChanged.h"
#include "GameUtilities/Event/Click.h"

#include "Events/BallCollision.h"
#include "Events/EventManager.h"
#include "Events/GoalCollision.h"
#include "Events/EventId.h"
#include "Events/LeftPaddleGoal.h"
#include "Events/PaddleCollision.h"
#include "Events/RightPaddleGoal.h"

#endif // EVENTS_H
