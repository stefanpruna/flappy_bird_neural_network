#include "bird.h"

//setting up the initial values for the bird
void bird_initialisation(Bird* b,int generation_number)
{
  if(generation_number==1)
  {
      b->brain=genann_init(5,1,4,1);
      genann_randomize(b->brain);
  }
  b->score=0;
  b->dest.w=53;
  b->dest.h=53;
  b->dest.x=150;
  b->x=30;
  b->gravity= 2.6;
  b->lift=18;
  b->y=30;
  b->dead=false;
  b->velocity=0;
  b->distance=0;
}

//birdUpdate updates the position of bird on the screen and its velocity
void birdUpdate(Bird* b)
{
  if(b->y<SCREEN_HEIGHT)
  {
  b->velocity += b->gravity;
  b->dest.y=(int) b->y;
  b->y+=(float) b->velocity;
  if(b->jumped==true)
  {
    b->velocity=0;
    b->velocity+= -b->lift;
    b->dest.y= (int) b->y;
    b->y+=(float) b->velocity;
    b->jumped=false;
  }
  b->distance+=10;
 }
}
