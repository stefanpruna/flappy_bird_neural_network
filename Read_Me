Neural network that learns to play the game Flappy, using genetic algorithm. The game uses SDL functions for graphics.

The process I used to create the birds for the next generation is at follows:
1. Calculate the fitness for each of the birds (The fitness is equal to the distance the birds has flown - the distance to the closest gap)
2. Sort the birds by their fitness
3. Pick the first sqrt(n) birds where "n" is the number of birds.
4. Breed them toghether to create a new generation of birds.
5. Mutate every bird in the new generation by a tiny bit.

To run this game you need the SDL librarie for fonts and images.
To install them type in the command line : 
 $sudo apt-get install libsdl2-ttf-dev
 $sudo apt-get install libsdl-image1.2-dev
I added a make file for this project.
To compile the game type: make all  
To run the game type: ./flappyBird
