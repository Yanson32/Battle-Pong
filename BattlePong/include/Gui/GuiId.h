#ifndef GUI_ID_H 
#define GUI_ID_H 
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
namespace Gui 
{
    enum id
    {
        START,
        MULTIPLAYER,
        OPTIONS,
        GENERAL_TAB,
        CONTROLS_TAB,
        VIDEO_TAB,
        SOUND_TAB,
        NETWORK_TAB,
        DEV_TAB,
        INTRO_PANEL,
        HOST,
        CONNECT,
        CREDITS,
        BACK,
        CONNECT_PANEL_BACK,
        OPTIONS_PANEL_BACK,
        MULTIPLAYER_PANEL_BACK,
        HOST_PANEL_BACK,
        FRAME_RATE, 
        VELOCITY_ITERATIONS,
        POSITION_ITERATIONS,
        DEBUG_AABB,
        DEBUG_SHAPE,
        DEBUG_MASS,
        DEBUG_JOINTS,
        DEBUG_PAIRS,
        DEBUG_LOG,
        MUSIC,
        SOUND_EFFECTS,
        THEME,
        BACKGROUND,
        BALL_SPEED,
        PADDLE_SPEED,
        WALL_THICKNESS,
        BALL_RADIUS,
        MUSIC_COMBO
    };
}
#endif 
