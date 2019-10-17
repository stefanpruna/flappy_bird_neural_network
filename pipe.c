#include "pipe.h"

//set up the initial values for a pipe
void pipe_initial_values(Pipe* p)
{
    for(int k=0;k<number_of_birds;k++)
        p->scored[k]=false;
  p->height=400;
  p->width=70;
  p->velocity=10;
  p->x=420;
  pipe_random_generation(p);
}

//update he pipe position (the pipe moves to the left)
void pipe_update(Pipe* p)
{
  p->x-=(float) p->velocity;
  p->boundsTop.x= (int) p->x;
  p->boundsBottom.x=(int) p->x;
}

//generate a random pipe
void pipe_random_generation(Pipe* p)
{
  p->x=SCREEN_WIDTH;
  //generate a random value betwen 145 and 170 for the spacing betwen 2 pipes
  p->freeSpace =145+ rand() % 25;
  p-> center = rand() % (SCREEN_HEIGHT-350) +130;
  p->bottomHeight = SCREEN_HEIGHT -(p->center + p->freeSpace/2);
  p->topHeight = p->center - p->freeSpace/2;

  //generating the positions of the top and buttom pipe. Those positions are relative to the free space betwen them.
  p->boundsBottom.x= (int) p->x;
  p->boundsBottom.y = (int)p->center+p->freeSpace/2;
  p->boundsBottom.w=(int)p->width;
  p->boundsBottom.h =(int) p->height;

  p->boundsTop.x = (int)p->x;
  p->boundsTop.y = (int) p->center - p->freeSpace/2 - p->height;
  p->boundsTop.h= (int)p->height;
  p->boundsTop.w = (int)p->width;
}

bool colision(Pipe* p,Bird* b)
{
  //CHECKING THE TOP PIPE COLLISION
      //if the right of the bird touches the left of the top pipe
      if(b->dest.x + b->dest.w >= p->boundsTop.x)
      //if the left of the bird did not pass the right position of the pipe
      if(b->dest.x <=p->boundsTop.x + p->boundsTop.w)
      //if the buttom of the bird is higher then the buttom of the pipe (bird is offscreen)
      if(b->dest.y<=p->boundsTop.y+p->boundsTop.h)
      return true;
  //CHECKING THE BOTTOM PIPE COLLISION
      //if the right of the bird touches the left of the bottom pipe
      if(b->dest.x+b->dest.w >=p->boundsBottom.x)
      //if the left of the bird did not pass the right position of the pipe
      if(b->dest.x <= p->boundsBottom.x +p->boundsBottom.w)
      //if the bird is lower than the top of the bottom pipe
      if(b->dest.y + b->dest.h >= p->boundsBottom.y)
      //if the bird is higher than the bottom of the pipe
      if(b->dest.y<=p->boundsBottom.y+p->boundsBottom.h)
      return true;
  return false;
}
void pipe_scored(Pipe* p,Bird* b,int j)
{
  //if the pipe hasn't been scored yet and the x position of the bird is greater than the x position of the pipe then the pipe is scored
    if(p->scored[j]==false && p->x < b->x)
      {
        b->score++;
        p->scored[j]=true;
     }
}
