#ifndef INPUT_H
#define INPUT_H

class Paddle;
class Ball;
class Input
{
    public:
        Input(Paddle &newPaddle);
        virtual void handleInput(const Ball &ball);
        virtual ~Input();
    protected:
        Paddle &paddle;
};

#endif // INPUT_H
