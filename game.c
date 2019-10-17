//The flappy bird game
#include "game.h"

int main()
{

  Engine gameEngine;

  //Start the sdl and create window
  if(!gameInitialisation(&gameEngine))
     printf("Failed to initiasate\n");
  else
      //load the images
      if(!LoadImages(&gameEngine))
         printf("Failed to load media");
      else
        {
          SDL_Event e;

           //While game is not closed
           while(gameEngine.gstate != QUITTING)
              {
                //handle Events
                  handleInput(&gameEngine,&e);
                //Update game
                  updateGame(&gameEngine);
                //render Frame
                  renderFrame(&gameEngine);
              }
            //close the sdl and dealocate memory
          closeGame(&gameEngine);
        }
    return 0;
}
