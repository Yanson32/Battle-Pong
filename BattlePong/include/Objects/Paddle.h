#ifndef PADDLE_H
#define PADDLE_H
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

#include "ObjectBase.h"
#include "Input/Input.h"
#include "Events/EventId.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <array>
#include "Objects/ObjectId.h"

class Ball;
class b2Body;
class Paddle: public ObjectBase<sf::ConvexShape>
{
    public:
        Paddle(std::shared_ptr<b2World> world, const ObjectId &newId, const std::array<sf::Vector2f, 4> vert);
        void setPosition(const sf::Vector2f &position);
        sf::Vector2f getPosition() const;
        void handleInput(const Ball &ball);
        void setInput(std::unique_ptr<Input> newInput);
        void move(const sf::Vector2f &direction);
        virtual void update();
        ~Paddle();
    private:
        std::unique_ptr<Input> input;
        b2Body *jointBody = nullptr;
        b2PrismaticJoint *prisJoint;
};

#endif
