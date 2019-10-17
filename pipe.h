#ifndef PIPE_H
#define PIPE_H
#include "bird.h"
#include <stdlib.h>
#include <time.h>
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
extern const int number_of_birds;
typedef struct
{
  double topHeight;  //height of the top pipe
  double bottomHeight;  //height for the bottom pipe
  int freeSpace;  //the free space betwen the pipes
  int width;   //the width of the pipe
  int height;   //the height of the pipe
  double velocity;  //the velocity that the pipe is moving to the left
  SDL_Rect boundsTop;   //the top pipe position
  SDL_Rect boundsBottom;  //the bottom pipe position
  bool scored[400];   //if the bird passed through the pipe without touching it, scored is true
  double x,y;    //the x and y positions for the pipe
  int center;
} Pipe;
void pipe_initial_values(Pipe* p);
void pipe_update(Pipe* p);
void pipe_random_generation(Pipe* p);
bool colision(Pipe* p,Bird* b);
void pipe_scored(Pipe* p,Bird* b,int j);
#endif
