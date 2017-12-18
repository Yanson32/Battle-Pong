#include <GameUtilities/Engin/Engin.h>
#include "States/IntroState.h"
#include <iostream>
#include <Box2D/Box2D.h>



int main()
{




	Engin::Engin engin;
	engin.Push<IntroState>();

	while (engin.IsRunning())
	{
		engin.HandleEvents();
		engin.Update();
		engin.Draw();
	}

}
