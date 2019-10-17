#include "genetics.h"
#include <stdlib.h>
#include <math.h>
int cmd(const void * a, const void * b)
{
    Bird *x= (Bird *)a;
    Bird *y= (Bird *)b;
    return (x->fitness < y->fitness) - (x->fitness > y->fitness);
}

//function called each time all the birds die. It creates the next generation of birds
void next_generation(Bird b[])
{
    //calculating the fitness for each bird
    calculate_fitness(b);
    //sorting the birds by their fitness
    qsort(b,number_of_birds,sizeof(Bird),cmd);
    printf("best fitness: %f, worst fitness%f\n",b[0].fitness,b[number_of_birds-1].fitness);
    //breeding the first few best birds to create the rest of the generation
    breeding(b);

}

//calculating the fitness for each bird
void calculate_fitness(Bird b[])
{

    for(int i=0;i<=number_of_birds;i++)
           b[i].fitness = (double)(b[i].distance-b[i].distance_to_the_closest_gap);
}

//geneating a random number betwen 0 and 1
double random_num0_1()
{
     // srand ( time(NULL) );
     double x=(double)(rand()%100000)/100000;
    // printf("%f\n",x);
    return x;
}

//mutating all the birds just a tiny bit
void mutate(Bird b[],int i)
{
    for(int k=1;k<=b[i].brain->total_weights;k++)
        if(random_num0_1()<0.2)
            b[i].brain->weight[k]=random_num0_1();
}

//breeding of the birds
void breeding(Bird b[])
{
    int number= sqrt(number_of_birds);
    int cont=2*number+1;
    //taking the first half of the sqrt(number of birds) fittest birds and breeding them togheter.
    for(int k1=1;k1<number/2;k1++)
        for(int k2=k1+1;k2<=number/2;k2++)
            {
                breed(b,k1,k2,cont);
                mutate(b,cont);
                cont++;
            }
    //taking the first half of the sqrt(number of birds) fittest birds and breeding them togheter. (different order of the chromosomes this time)
    for(int k1=1;k1<number/2;k1++)
        for(int k2=k1+1;k2<=number/2;k2++)
            {
                breed(b,k2,k1,cont);
                mutate(b,cont);
                cont++;
            }
}

//taking the first half of the x genes and the second half of the y genes to create a new bird with all the genes combined
void breed(Bird b[],int x,int y,int cont)
{
    for(int k3=0;k3<b[x].brain->total_weights/2;k3++)
        b[cont].brain->weight[k3] = b[x].brain->weight[k3];

    for(int k3=b[x].brain->total_weights/2;k3<=b[x].brain->total_weights;k3++)
        b[cont].brain->weight[k3]=b[y].brain->weight[k3];
}
