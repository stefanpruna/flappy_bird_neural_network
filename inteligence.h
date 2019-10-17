#include "bird.h"
#include "pipe.h"
#include <time.h>
#include <limits.h>
double act_sigmoid(double a) ;
double think(Bird *b,Pipe* p);
int closest_pipe(Bird *b,Pipe* p,int number_of_pipes);
