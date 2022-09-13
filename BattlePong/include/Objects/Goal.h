#ifndef GOAL_H
#define GOAL_H
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
#include "Objects/ObjectBase.h"
#include "Events/EventId.h"
#include <SFML/System/Vector2.hpp>
#include <array>
#include "Objects/ObjectId.h"

class Goal: public ObjectBase<sf::ConvexShape>
{
    public:
        Goal(std::shared_ptr<b2World> world, ObjectId newId, const std::array<sf::Vector2f, 4> vert);
        void update() override;
        virtual ~Goal();
    protected:
    private:
};

#endif // GOAL_H
