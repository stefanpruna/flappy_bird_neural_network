#include "bird.h"
#include <time.h>
extern const int number_of_birds;

void next_generation(Bird b[]);
double random_num0_1();
void calculate_fitness(Bird b[]);
int random_pick_based_onProbability(Bird b[]);
void pick_a_bird(Bird b[],int i);
void breed(Bird b[],int x,int y,int cont);
void breeding(Bird b[]);
int cmd(const void * a, const void * b);
