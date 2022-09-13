#ifndef OBJECT_ID_H
#define OBJECT_ID_H
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

enum ObjectId
{
    BALL = 1,
    LEFT_GOAL = 2,
    RIGHT_GOAL = 4,
    LEFT_PADDLE = 8,
    RIGHT_PADDLE = 16,
    WALL = 32,
    PADDLE_STOP = 64,
    NONE = 128 
};
#endif
