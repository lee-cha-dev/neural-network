#include "neural_network_lib.h"

#include <stdio.h>

void neural_network_test(){
    printf("\nNeural library\n");
}

// SET THE SIZE OF WEIGHTS TO THE NUMBER OF REQUIRED WEIGHTS FOR THE NEURAL CONNECTIONS
void neuron_set_neuron_weights(int number_of_weights, struct Neuron *n, const double *values){
    n->weights = malloc(sizeof(double[number_of_weights]));

    // ITERATE THROUGH THE ARRAY THAT WAS CREATED FOR THIS NEURON'S WEIGHTS
    for (int i = 0; i < number_of_weights; ++i){
        n->weights[i] = values[i];
    }

    // THE INT POINTER ARRAY THAT WAS PASSED IN CONTAINING THE WEIGHTS WILL
    // BE FREED AND SET TO NULL AFTER THIS FUNCTION IS CALLED.
    // THIS IS ASSUMING THAT ANOTHER FUNCTION DOES NOT CREATE THE RANDOM VALUES
    // AND CALLS THIS FUNCTION TO HANDLE ASSIGNING THE WEIGHTS TO THE STRUCT
}

// TAKES IN A CONST INT AND CREATE A RANDOM ARRAY OF INTS FOR THE NEURON'S WEIGHTS
// MIGHT TURN THIS INTO ON FUNCTION BY ITSELF, BUT MAY HAVE AN INITIALIZATION FUNCTION
// AND A SET OF FUNCTION TO SPECIFICALLY MUTATE A NEURON INDIVIDUALLY
void neuron_create_weights(const int *neural_connections){
    // CREATE A RANDOM ARRAY OF WEIGHTS
}

// INITIALIZATION FUNCTION FOR NEURONS
// THE WEIGHTS AND BIASES NEED TO BE RANDOMLY GENERATED, SO
// A FUNCTION WOULD BE THE MOST EFFICIENT ROUTE
// THIS WAY IT CAN BE SKIPPED IF THE USER WANTS TO HAND PICK EACH
// NEURON'S PARAMETERS
void neuron_initialize_weights_bias(struct Neuron *pN, int size_of_weights){
    // ALLOCATE SPACE TO THE POINTERS INSIDE THE STRUCT
    pN->weights = malloc(sizeof(double[size_of_weights]));
    pN->bias = malloc(sizeof(double));
    pN->size_weights = malloc(sizeof(int));

    // CREATE AND SET THE VALUES FOR THE WEIGHTS TO 0
    // CALL neuron_create_weights(); HERE IN LUE OF CALLOC
    double *values;
    values = calloc(size_of_weights, sizeof(double));

    // WILL MOVE AWAY FROM CALLOC AND MOVE TO A RANDOM DOUBLE VALUE GENERATOR
    // THIS WILL NEED TO ALLOW FOR AN ACCEPTABLE RANGE BASED ON TWO PASSED IN VALUES
    // -- MOST LIKELY DOUBLE VALUES

    // SET THE SIZE OF WEIGHTS ARRAY
    *pN->size_weights = size_of_weights;

    // CALL FUNCTION TO SET THE WEIGHTS
    neuron_set_neuron_weights(
            size_of_weights,
            pN,
            values
    );
}

// NEURON FUNCTIONS TO SET INDIVIDUAL VALUES -- MAY BE UNNECESSARY --
void neuron_set_weight(struct Neuron *pN, int index, double value){
    pN->weights[index] = value;
}

void neuron_set_bias(struct Neuron *pN, double value){
    *pN->bias = value;
}

