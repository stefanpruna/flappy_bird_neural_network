#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
typedef struct
{
  char text[200];   //the text
  SDL_Surface* TextSurface;   //surface for the text
  SDL_Rect dest;   //the position of the text
  SDL_Color TextColor;   //the color of the text
  SDL_Texture* text_texture;   //the texture for the text
} Text;
void score_initial_values(Text* t,int color);
void textUpdate (Text* t,char txt[],TTF_Font* f);
void game_text_initial_values(Text* t,char txt[],TTF_Font* f,int color);
void game_over_text_initial_values(Text* t,char txt[],TTF_Font* f,int color);
