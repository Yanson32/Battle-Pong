#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H
#include "Input.h"

class PlayerInput: public Input
{
    public:
        PlayerInput(Paddle &newPaddle);
        virtual void handleInput(const Ball &ball) override;
        virtual ~PlayerInput();
    protected:
    private:
};

#endif // PLAYERINPUT_H
