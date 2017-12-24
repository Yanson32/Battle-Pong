#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H
#include <Box2D/Box2D.h>

class ContactListener: public b2ContactListener
{
    public:
        ContactListener();
        virtual void BeginContact(b2Contact* contact) override;
        virtual ~ContactListener();
        bool IsBall(b2Fixture* fixture);
    protected:
    private:
};

#endif // CONTACTLISTENER_H
