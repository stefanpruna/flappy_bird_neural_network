#include "engine.h"
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;
const int number_of_birds=307;
int numar=0;
unsigned int lastTime=0,curentTime=0;

//function that loads a texture

SDL_Texture* loadTexture(char *path,Engine* e)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load (path);
    if(surface == NULL)
       printf("Failed to load image,error%s\n",IMG_GetError());
    else
      {
        texture = SDL_CreateTextureFromSurface (e->render,surface);
        if(texture == NULL)
           printf("Unable to create texture from surface,error:%s\n",IMG_GetError());
        SDL_FreeSurface (surface);
      }
     return texture;
}

//game initialisation

bool gameInitialisation(Engine* e)
{
    if ( SDL_Init (SDL_INIT_VIDEO) < 0)
      {
              printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
              return false;
      }

    //create the window

    e->window = SDL_CreateWindow ("FlappyBird",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(e->window==NULL)
      {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
      }

    //create renderered window

    e->render = SDL_CreateRenderer (e->window,-1,SDL_RENDERER_ACCELERATED);
    if(e->render == NULL)
    {
       printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
       return false;
    }

    //font initialisation

    if(TTF_Init()==-1)
    {
      printf("TTF_SDL could not initialize: TTF_Error: %s\n", TTF_GetError());
      return false;
    }

    //loading font

    e -> font = TTF_OpenFont("resources/fBirdFont.TTF",24);
    if(e->font==NULL)
    {
       printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
       return false;
    }
    //setup the text
    text_setup(e);
    //setting up the initial values for:the bird, pipe,score and ground;
    e->generation_number=1;
    bird_initial_values(e);
    pipe_initial_values(&e->pipe[0]);
    pipe_initial_values(&e->pipe[1]);
    score_initial_values(&e->text_score,1);
    score_initial_values(&e->shadow_text_score,2);
    ground_initial_values(e);
    //game state is start
    e->gstate=START;
    e->g_mode=ONE_PLAYER;
    e->high_score=0;
    integer_to_text(e->high_score_char,0);
    //the initial number of pipes is 0
    e->number_of_pipes=0;
    e->number_of_dead_birds=0;
    return true;

}

//function that sets up the text for the start screen and for the game over screen

void text_setup(Engine* e)
{
  game_text_initial_values(&e->start_game_text,"                  Flappy Bird \n\nPress [space] to start the game and jump\n\n       Press [Esc] to exit the game",e->font,1);
  game_text_initial_values(&e->start_game_text_shadow,"                  Flappy Bird \n\nPress [space] to start the game and jump\n\n       Press [Esc] to exit the game",e->font,2);
  strcpy(e->game_Over_text.text,"        Wanna play again?\n\n  Press [Esc] to exit the game \n\nPress [Space] to start the game");
}

//function that sets up the initial values for the screen

void ground_initial_values(Engine* e)
{
  e->ground_dest.x=0;
  e->ground_dest.y=SCREEN_HEIGHT-30;
  e->ground_dest.w=SCREEN_WIDTH;
  e->ground_dest.h=80;
}

//function that transforms an integer into a string

void integer_to_text(char txt[],int score)
{
  int nr_digits=0;
  int x=score;
  if(score==0)
  {
    txt[0]='0';
    txt[1]='\0';
  }
  else
  {
    //get the number of digits from the number
    while(score)
     {
      nr_digits++;
      score=score/10;
     }
    int i=nr_digits-1;
    while(x)
     {
       txt[i]=x%10+'0';
       x=x/10;
       i--;
     }
     //put the NULL charachter at the end of the string.
    txt[nr_digits]= '\0';
  }
}

//loading the images using loadTexture()

bool LoadImages(Engine* e)
{
  //loading the pipe
  e->pipe_image = loadTexture("resources/pipe.png",e);
  if(e->pipe_image==NULL)
  return false;

  //loading the bird
  e->bird_image= loadTexture("resources/fbird.png",e);
  if(e->bird_image == NULL)
  return false;

  //loading the background
  e->background = loadTexture("resources/bg.png",e);
  if(e->background == NULL)
  return false;

  //loading the ground
  e->ground_image=loadTexture("resources/ground.png",e);
  if(e->ground_image==NULL)
  return false;

  return true;


}

//function that calls bird_initialisation. the function bird_initialisation is in bird.c

void bird_initial_values(Engine* e)
{
    for(int i=0;i<number_of_birds;i++)
      bird_initialisation(&e->bird[i],e->generation_number);
}

//function that handles the input

void handleInput(Engine* e, SDL_Event* event)
{
    if(e->gstate==START || e->gstate==GAME_OVER)
    if(e->number_of_dead_birds==number_of_birds)
       {
         e->gstate=PLAYING;
         game_reset(e);
       }
   while(SDL_PollEvent(event)!=0)
   {
     //if player clicks on the X icon on the top right, the game closes
     if(event->type== SDL_QUIT)
        e->gstate= QUITTING;
     else
     {

       //if a key is pressed
      if(event->type == SDL_KEYDOWN)
      {
        //if the pressed key is escape, the game closes
        if(event->key.keysym.sym==SDLK_ESCAPE)
        e->gstate=QUITTING;

        //if the game is either on the start menu screen or the game over one
        if(e->gstate==START)
                //if the pressed key is space, start the game and reset the initial values
        if(event->key.keysym.sym==SDLK_SPACE)
           {
             e->gstate=PLAYING;
             //game_reset(e);
           }

           //if the state of the game is playing, pressing space makes the bird jump
        if(e->gstate== PLAYING)
        if(event->key.keysym.sym==SDLK_SPACE && e->g_mode==ONE_PLAYER)
          e->bird[0].jumped= true;
      }
     }
   }
}

//function that updates the values for the game
void updateGame(Engine* e)
{
        for(int i=0;i<number_of_birds;i++)
          {
              e->closest_pipe=closest_pipe(&e->bird[i],e->pipe,e->number_of_pipes);
              if(e->bird[i].dead==false && think(&e->bird[i],&e->pipe[e->closest_pipe])>0.5)
                      e->bird[i].jumped=true;

                //printf("%f",think(&e->bird[i],&e->pipe[e->closest_pipe]));
          }
  //if the game state is either playing or game over, the bird position is still changhing
  //during the game over screen the bird just falls and it doesnt accept jump input from player
   if(e->gstate==PLAYING || e->gstate==GAME_OVER)
   for(int i=0;i<number_of_birds;i++)
     birdUpdate(&e->bird[i]);
  //if the state of the game is playing
   if(e->gstate==PLAYING)
   {
     //if the bird hits the ground, game is over
     for(int i=0;i<number_of_birds;i++)
      {
          if(e->bird[i].dest.y> SCREEN_HEIGHT- e->ground_dest.h && e->bird[i].dead==false)
            {
                e->number_of_dead_birds++;
                e->bird[i].dead=true;
            }
          if(e->number_of_dead_birds==number_of_birds)
             e->gstate=GAME_OVER;
      }
     //there can not be more than 3 pipes on screen, but at the start of the game there are less than 3
     for(int i=max(e->number_of_pipes-3,0);i<=e->number_of_pipes;i++)
       pipe_update(&e->pipe[i]);
     curentTime= SDL_GetTicks();
     //if 1.3 seconds have passed since the last pipe was generated, generate a pipe
     if(curentTime > lastTime +1300)
       {
        e->number_of_pipes++;
        pipe_initial_values(&e->pipe[e->number_of_pipes]);
        pipe_random_generation(&e->pipe[e->number_of_pipes]);
        lastTime = curentTime;
       }
       //check for the collision with the bird for each of the pipes on the screen
     for(int i=max(e->number_of_pipes-3,1);i<=e->number_of_pipes;i++)
       {
         for(int j=0;j<number_of_birds;j++)
            {
                if(colision(&e->pipe[i],&e->bird[j])==true && e->bird[j].dead==false)
                    {
                        e->number_of_dead_birds++;
                        e->bird[j].dead=true;
                    }
                    if(e->bird[j].dead == false)
                    pipe_scored(&e->pipe[i],&e->bird[j],j);
            }
        if(e->number_of_dead_birds==number_of_birds)
          e->gstate=GAME_OVER;
       }
       //transfom the score into a char
      integer_to_text(e->char_score,e->bird[0].score);
      //update the score
      char s[100]="score: ";
      strcat(s,e->char_score);
      textUpdate(&e->text_score,s,e->font);
      textUpdate(&e->shadow_text_score,s,e->font);
      //create the texture for the score
      e->text_score.text_texture=SDL_CreateTextureFromSurface(e->render,e->text_score.TextSurface);
      e->shadow_text_score.text_texture=SDL_CreateTextureFromSurface(e->render,e->shadow_text_score.TextSurface);
  }
  //if the game is on the start screen create the texture for the start screen text
    if(e->gstate==START)
      {
        e->start_game_text_shadow.text_texture=SDL_CreateTextureFromSurface(e->render,e->start_game_text_shadow.TextSurface);
        e->start_game_text.text_texture=SDL_CreateTextureFromSurface(e->render,e->start_game_text.TextSurface);
      }
  //if the game is on the game over screen
    if(e->gstate==GAME_OVER)
      {
        //if the score is higher than the last high score, update the high score
          if(e->bird[0].score>e->high_score)
          {
            integer_to_text(e->high_score_char,e->bird[0].score);
            e->high_score=e->bird[0].score;
          }
          //creating the game over screen text
          char s[100]="         Your score is: ";
          strcat(s,e->char_score);
          strcat(s,"\n");
          char high_score[100]="\n      Your high score is: ";
          strcat(high_score,e->high_score_char);
          strcat(s,high_score);
          strcat(s,"\n\n");
          strcat(s,e->game_Over_text.text);
          //updating the positions and the color for each text (the text and it's shadow)
          game_over_text_initial_values(&e->game_Over_text,s,e->font,1);
          game_over_text_initial_values(&e->game_Over_text_shadow,s,e->font,2);
          //creating a texture from each text surface
          e->game_Over_text_shadow.text_texture=SDL_CreateTextureFromSurface(e->render,e->game_Over_text_shadow.TextSurface);
          e->game_Over_text.text_texture=SDL_CreateTextureFromSurface(e->render,e->game_Over_text.TextSurface);
      }
}

//function that returns the greater number from 2 numbers
int max(int a,int b)
{
  if(a>=b)
    return a;
  return b;
}

//rendering the new frame
void renderFrame(Engine* e)
{
  // clear the Frame
  SDL_RenderClear(e->render);
  //render the background
  SDL_RenderCopy(e->render,e->background,NULL,NULL);
  //render the pipes, there can not be more than 3 pipes on the screen
  for(int i=max(1,e->number_of_pipes-3);i<=e->number_of_pipes;i++)
  {
    SDL_RenderCopyEx(e->render,e->pipe_image,NULL, &e->pipe[i].boundsTop,0,NULL,SDL_FLIP_NONE);
    SDL_RenderCopyEx(e->render,e->pipe_image,NULL,&e->pipe[i].boundsBottom,0,NULL,SDL_FLIP_VERTICAL);

  }

  //if the game is playing
  if(e->gstate==PLAYING)
  {
    //render the score and it's shadow
  SDL_RenderCopy(e->render,e->shadow_text_score.text_texture,NULL,&e->shadow_text_score.dest);
  SDL_RenderCopy(e->render,e->text_score.text_texture,NULL,&e->text_score.dest);
  //render the bird
  for(int i=0;i<number_of_birds;i++)
  if(e->bird[i].dead == false)
  SDL_RenderCopyEx(e->render,e->bird_image , NULL,&e->bird[i].dest,e->bird[i].velocity,NULL,SDL_FLIP_NONE);
  //render the ground
  SDL_RenderCopy(e->render,e->ground_image,NULL,&e->ground_dest);
  SDL_FreeSurface(e->text_score.TextSurface);
  SDL_FreeSurface(e->shadow_text_score.TextSurface);
  }
  //if the game is over (the player has died)
  if(e->gstate==GAME_OVER)
   {
     //render the text for the "game over" screen
     SDL_RenderCopy(e->render,e->game_Over_text_shadow.text_texture,NULL,&e->game_Over_text_shadow.dest);
     SDL_RenderCopy(e->render,e->game_Over_text.text_texture,NULL,&e->game_Over_text.dest);
     //render the bird
     SDL_RenderCopyEx(e->render,e->bird_image , NULL,&e->bird[0].dest,e->bird[0].velocity,NULL,SDL_FLIP_NONE);
     //render the ground
     SDL_RenderCopy(e->render,e->ground_image,NULL,&e->ground_dest);
     SDL_FreeSurface(e->game_Over_text.TextSurface);
     SDL_FreeSurface(e->game_Over_text_shadow.TextSurface);
   }
   //if the game in on the start screen, render the start screen text
   if(e->gstate==START)
   {
     //render the "game start" text
     SDL_RenderCopy(e->render,e->start_game_text_shadow.text_texture,NULL,&e->start_game_text_shadow.dest);
     SDL_RenderCopy(e->render,e->start_game_text.text_texture,NULL,&e->start_game_text.dest);

   }
   //render the screen
  SDL_RenderPresent(e->render);
  SDL_UpdateWindowSurface(e->window);
  SDL_Delay(1000/20);
}

//if the player wants to play again after dying, reset
void game_reset(Engine* e)
{
  e->generation_number++;
 printf("generation:%d ",e->generation_number);
  int maximum=0;
  for(int i=0;i<number_of_birds;i++)
     if(e->bird[i].score>maximum)
     maximum=e->bird[i].score;
     printf("best score:%d ",maximum);
  next_generation(e->bird);
  bird_initial_values(e);
  e->number_of_dead_birds=0;
  e->number_of_pipes=0;
}

//SDL functions closing
void closeGame(Engine* e)
{
    //Deallocate textures
    SDL_DestroyTexture(e->bird_image);
    SDL_DestroyTexture(e->background);
    SDL_DestroyTexture(e->pipe_image);
    SDL_DestroyTexture(e->ground_image);
    e->background= NULL;
    e->bird_image = NULL;
    e->pipe_image = NULL;
    e->ground_image=NULL;

    //Dealocate renderer
    SDL_DestroyRenderer(e->render);
    e->render=NULL;

    //Destroy The window
    SDL_DestroyWindow (e->window);
    e->window=NULL;

    //Dealocate font
    TTF_CloseFont(e->font);
    e->font=NULL;

    //quit SDL
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
