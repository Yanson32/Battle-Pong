#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H
/**********************************************************//**
*   @author Wayne J Larson Jr.
*   @date   12/25/17
*   @brief  ContactListenr is a functor used by Box2D for
*           passing collision information to the user.
**************************************************************/
#include <Box2D/Box2D.h>
//#include "Events/Id.h"

class ContactListener: public b2ContactListener
{
    public:
        /**********************************************************//**
        *   @brief  Constructor
        **************************************************************/
        ContactListener();


        /**********************************************************//**
        *   @brief  Box2D calls this method when a collision is
        *           detected. Assuming the class has been registerd
        *           with Box2D.
        *   @param  contact represents a collision between two
        *           b2Fixtures.
        **************************************************************/
        virtual void BeginContact(b2Contact* contact) override;


        /**********************************************************//**
        *   @brief  This method checks a b2Fixture to see if the fixture
        *           is pongs ball object.
        *   @param  fixture a Box2D fixture that may be the games
        *           ball object.
        *   @return true when the input b2Fixture is a ball object
        *           and false otherwise.
        **************************************************************/
        bool IsBall(b2Fixture* fixture);

        bool IsGoal(b2Fixture* fixture);
        bool IsLeftGoal(b2Fixture* fixture);
        bool IsRightGoal(b2Fixture* fixture);
        void dispatchEvent(const int &id, const bool sensor) const;
        /**********************************************************//**
        *   @brief  Destructor
        **************************************************************/
        virtual ~ContactListener();

    protected:
    private:
};

#endif // CONTACTLISTENER_H
