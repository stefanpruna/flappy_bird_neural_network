#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include "pipe.h"
#include "text.h"
#include "genetics.h"
#include "inteligence.h"
const int SCREEN_HEIGHT;
const int SCREEN_WIDTH;
typedef enum g_state
{
  START,PLAYING,GAME_OVER,QUITTING
} GAME_STATE;
typedef enum game_mode
{
  ZERO_PLAYERS,ONE_PLAYER
} GAME_MODE;
typedef struct
{
  TTF_Font* font; //games font
  Bird bird[350];   //structure for the bird
  Pipe pipe[400];   //structure for the pipes
  int number_of_pipes;   //integer that holds the number of pipes
  SDL_Texture* bird_image;    //the image of the bird
  SDL_Texture* background;  //the image for the background
  SDL_Texture* pipe_image;   //the image for the pipe
  SDL_Texture* ground_image;  //the image for the ground
  SDL_Renderer* render;   //the renderer
  SDL_Window* window;      //the window
  GAME_STATE gstate;      //game state
  GAME_MODE g_mode;
  SDL_Rect ground_dest;    //position for the ground image
  int high_score;          //high score
  Text text_score;         //the text for the score displayed top left
  Text shadow_text_score;   //the black text that goes behind the score (looks like a shadow)
  Text game_Over_text;      //the text for the game over screen
  Text game_Over_text_shadow;   //the shadow for the game over screen text
  Text start_game_text;       //the text for the start game screen
  Text start_game_text_shadow;    //the shadow for the start game screen
  char char_score[4];        //the score can't really be more than 3 digits
  char high_score_char[4];   //neither the high score
  int closest_pipe;
  int number_of_dead_birds;
  int generation_number;

}Engine;
void text_setup (Engine* e);
SDL_Texture* loadTexture(char *path,Engine* e);
bool gameInitialisation(Engine* e);
void integer_to_text(char txt[],int score);
bool LoadImages(Engine* e);
void ground_initial_values(Engine* e);
void bird_initial_values(Engine* e);
void handleInput(Engine* e, SDL_Event* event);
void updateGame(Engine* e);
int max(int a,int b);
void renderFrame(Engine* e);
void game_reset(Engine* e);
void closeGame(Engine* e);
