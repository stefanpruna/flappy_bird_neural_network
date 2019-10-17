#include "text.h"

//setting up the initial values of the score. the variable "color" is 1 if the color is white and 2 if the color is black->the shadow
void score_initial_values(Text* t,int color)
{
  if(color==1)
  {
    t->TextColor.r=255;
    t->TextColor.g=255;
    t->TextColor.b=255;
    t->TextColor.a=255;
    t->dest.x=20;
    t->dest.y=20;
    t->dest.w=100;
    t->dest.h=20;
  }
  else
  {
    t->TextColor.r=0;
    t->TextColor.g=0;
    t->TextColor.b=0;
    t->TextColor.a=0;
    t->dest.x=19;
    t->dest.y=21;
    t->dest.w=100;
    t->dest.h=20;
  }
}

//creating a surface from a text
void textUpdate (Text* t,char txt[],TTF_Font* f)
{
  t->TextSurface= TTF_RenderText_Solid(f,txt,t->TextColor);
}

//setting up the possition for the start screen text
void game_text_initial_values(Text* t,char txt[],TTF_Font* f,int color)
{

  if(color==1)
  {
    t->TextColor.r=255;
    t->TextColor.g=255;
    t->TextColor.b=255;
    t->TextColor.a=255;
    t->dest.x=SCREEN_WIDTH/2-250;
    t->dest.y=SCREEN_HEIGHT/2-150;
 }
  else
  {
    t->TextColor.r=0;
    t->TextColor.g=0;
    t->TextColor.b=0;
    t->TextColor.a=0;
    t->dest.x=SCREEN_WIDTH/2-250-1;
    t->dest.y=SCREEN_HEIGHT/2-150+1;
  }
  t->TextSurface= TTF_RenderText_Blended_Wrapped(f,txt,t->TextColor,640);
  t->dest.w=t->TextSurface->w;
  t->dest.h=t->TextSurface->h;

}

//setting up the possition for the game over screen text
void game_over_text_initial_values(Text* t,char txt[],TTF_Font* f,int color)
{

  if(color==1)
  {
    t->TextColor.r=255;
    t->TextColor.g=255;
    t->TextColor.b=255;
    t->TextColor.a=255;
    t->dest.x=SCREEN_WIDTH/2-180;
    t->dest.y=SCREEN_HEIGHT/2-180;
 }
  else
  {
    t->TextColor.r=0;
    t->TextColor.g=0;
    t->TextColor.b=0;
    t->TextColor.a=0;
    t->dest.x=SCREEN_WIDTH/2-180-1;
    t->dest.y=SCREEN_HEIGHT/2-180+1;
  }
  t->TextSurface= TTF_RenderText_Blended_Wrapped(f,txt,t->TextColor,640);
  t->dest.w=t->TextSurface->w;
  t->dest.h=t->TextSurface->h;

}
