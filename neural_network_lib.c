#include "neural_network_lib.h"
#include <stdio.h>

// SET THE SIZE OF WEIGHTS TO THE NUMBER OF REQUIRED WEIGHTS FOR THE NEURAL CONNECTIONS
void neuron_set_neuron_weights(int number_of_weights, struct Neuron *pN, const double *values){

    // ITERATE THROUGH THE ARRAY THAT WAS CREATED FOR THIS NEURON'S WEIGHTS
    for (int i = 0; i < number_of_weights; ++i){
        pN->weights[i] = values[i];
    }

    // THE INT POINTER ARRAY THAT WAS PASSED IN CONTAINING THE WEIGHTS WILL
    // BE FREED AND SET TO NULL AFTER THIS FUNCTION IS CALLED.
    // THIS IS ASSUMING THAT ANOTHER FUNCTION DOES NOT CREATE THE RANDOM VALUES
    // AND CALLS THIS FUNCTION TO HANDLE ASSIGNING THE WEIGHTS TO THE STRUCT
}

// TAKES IN A CONST INT AND CREATE A RANDOM ARRAY OF INTS FOR THE NEURON'S WEIGHTS
// MIGHT TURN THIS INTO ON FUNCTION BY ITSELF, BUT MAY HAVE AN INITIALIZATION FUNCTION
// AND A SET OF FUNCTION TO SPECIFICALLY MUTATE A NEURON INDIVIDUALLY
void neuron_create_weights(struct Neuron *n, const double *min, const double *max){
    // CREATE A RANDOM ARRAY OF WEIGHTS
    printf("\nCreating weights\n");

    // SET SEED -- NEEDS TO BE DONE IN ORDER TO SET GET RANDOM VALUES
    srand(time(NULL));

    // GET PAST INITIAL (PREDICTABLE) VALUE
    get_random_double(min, max);

    for(int i = 0; i < *n->size_weights; ++i){
        n->weights[i] = get_random_double(min, max);
    }
}

// INITIALIZATION FUNCTION FOR NEURONS
// THE WEIGHTS AND BIASES NEED TO BE RANDOMLY GENERATED, SO
// A FUNCTION WOULD BE THE MOST EFFICIENT ROUTE
// THIS WAY IT CAN BE SKIPPED IF THE USER WANTS TO HAND PICK EACH
// NEURON'S PARAMETERS
void neuron_initialize_weights_bias(struct Neuron *pN, int size_of_weights, double min, double max){
    // ALLOCATE SPACE TO THE POINTERS INSIDE THE STRUCT
    pN->weights = malloc(sizeof(double[size_of_weights]));
    pN->bias = malloc(sizeof(double));
    pN->size_weights = malloc(sizeof(int));

    // SET THE SIZE OF WEIGHTS ARRAY
    *pN->size_weights = size_of_weights;

    // CREATE AND SET THE VALUES FOR THE WEIGHTS TO A RANDOM DOUBLE -- RANDOMNESS MAY
    // BE PREDICTABLE ***
    neuron_create_weights(pN, &min, &max);

    *pN->bias = get_random_double(&min, &max);
}

// NEURON FUNCTIONS TO SET INDIVIDUAL VALUES -- MAY BE UNNECESSARY --
void neuron_set_weight(struct Neuron *pN, int index, double value){
    pN->weights[index] = value;
}

void neuron_set_bias(struct Neuron *pN, double value){
    *pN->bias = value;
}

double get_random_double(const double *min, const double *max){
//    srand((double) time( ));
//    double value = (float) rand() / (float)(RAND_MAX);
    double value;
    value = (double)rand() / ((double) RAND_MAX + 1);
    return (*min + value * (*max - *min));
}

