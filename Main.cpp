#include "States/IntroState.h"
#include <iostream>
#include <Box2D/Box2D.h>
#include "Game.h"
#include "States/PlayState.h"
int main()
{




	Game engin;
	engin.Push<IntroState>(engin);

	while (engin.IsRunning())
	{
		engin.HandleEvents();
		engin.Update();
		engin.Draw();
	}

}
