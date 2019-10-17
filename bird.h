#ifndef BIRD_H
#define BIRD_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "genann.h"
#define SCROLL_SPEED (300)
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
typedef struct
{
  genann *brain;
  double x,y;   //the x and y positions of the bird
  double velocity;   //birds velocity
  double gravity;     //worlds gravity
  float lift;       //the lift applied to the velocity if the player jumped
  bool jumped;      //variable that holds true if the player jumped
  SDL_Rect dest;    //birds positions
  int score;       //players score
  bool dead;
  double fitness;
  double distance_to_the_closest_gap;
  int distance;
} Bird;
void bird_initialisation(Bird* b,int generation_number);
void birdUpdate(Bird* b);
#endif
