#ifndef AI_H
#define AI_H
#include "Input.h"


class AI: public Input
{
    public:
        AI(Paddle &newPaddle);
        virtual void handleInput(const Ball &ball) override;
        virtual ~AI();
    protected:
    private:
};

#endif // AI_H
