#include "inteligence.h"
#include <math.h>
const int INFINIT = INT_MAX;
//think
int max2(int a,int b)
{
  if(a>=b)
    return a;
  return b;
}

//function that takes a number and produces a number betwen 0 and 1 using the sigmoid function
double act_sigmoid(double a)
{
    if (a < -45.0) return 0;
    if (a > 45.0) return 1;
    return 1.0 / (1 + exp(-a));
}

//proccesing of the neural network for each bird
double think(Bird *b,Pipe *p)
{
    //giving 5 inputs
    double input[5];
    //the y position of the bird
    input[0]=(double)b->y/SCREEN_HEIGHT;
    //the x position of the closest pipe
    input[1]=(double)p->x/SCREEN_WIDTH;
    //the height of the buttom pipe
    input[2]=(double)p->bottomHeight/SCREEN_HEIGHT;
    //the height of the top pipe
    input[3]=(double)p->topHeight/SCREEN_HEIGHT;
    //the position of the gap betwen the pipes
    input[4]=(double)p->center/SCREEN_HEIGHT;
    //expected output
    const double output[2]={0.4999,0.5001};
    //training the neural network
        genann_train(b->brain, input, output, 4);
    //returning the output of the neural network
    return *genann_run(b->brain, input);


//function that returns the closest pipe on the right of the bird
}
int closest_pipe(Bird *b,Pipe p[],int number_of_pipes)
{
   int closest=1;
   double closest_distance = INFINIT;
    for(int i=max2(1,number_of_pipes-3);i<=number_of_pipes;i++)
        {
            double distance = p[i].x -b->x;
            if(distance<closest_distance && distance>0)
            {
                closest=i;
                closest_distance = distance;
                if(b->dead==false)
                   if(b->x>(p[i+1].x-p[i].x)/2)
                   //calculating the distance from the bird to the center of the gap betwen the pipes
                    b->distance_to_the_closest_gap=sqrt((double)(p[closest].center-b->y)*(p[closest].center-b->y)+(double)((p[closest].x-b->x)*(p[closest].x-b->x)));
            }
            else
                if(distance<0)
                {
                    closest++;
                    closest_distance = p[closest].x - b->x;
                }
        }

      return closest;
}
