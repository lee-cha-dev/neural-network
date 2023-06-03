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
void neuron_create_weights(struct Neuron *n, double min, double max, int size_weights){
    // CREATE A RANDOM ARRAY OF WEIGHTS
//    printf("\nCreating weights\n");

    // SET SEED -- NEEDS TO BE DONE IN ORDER TO SET GET RANDOM VALUES
    srand(time(NULL));

    // GET PAST INITIAL (PREDICTABLE) VALUE
    get_random_double(&min, &max);

    for(int i = 0; i < size_weights; ++i){
        n->weights[i] = get_random_double(&min, &max);
    }
}

// INITIALIZATION FUNCTION FOR NEURONS
// THE WEIGHTS AND BIASES NEED TO BE RANDOMLY GENERATED, SO
// A FUNCTION WOULD BE THE MOST EFFICIENT ROUTE
// THIS WAY IT CAN BE SKIPPED IF THE USER WANTS TO HAND PICK EACH
// NEURON'S PARAMETERS
void neuron_init(struct Neuron *pN, int size_of_weights, double min, double max){
    // ALLOCATE SPACE TO THE POINTERS INSIDE THE STRUCT
    pN->weights = malloc(sizeof(double[size_of_weights]));
    pN->bias = malloc(sizeof(double));

    // CREATE AND SET THE VALUES FOR THE WEIGHTS TO A RANDOM DOUBLE -- RANDOMNESS MAY
    // BE PREDICTABLE ***
    neuron_create_weights(pN, min, max, size_of_weights);

    *pN->bias = get_random_double(&min, &max);
}

// NEURON FUNCTIONS TO SET INDIVIDUAL VALUES -- MAY BE UNNECESSARY --
void neuron_set_weight(struct Neuron *pN, int index, double value){
    pN->weights[index] = value;
}

void neuron_set_bias(struct Neuron *pN, double value){
    *pN->bias = value;
}

// LAYER FUNCTIONS START
void layer_init(struct Layer *pL, int size_of_layer, double min, double max, int size_of_next_layer){
    // SET LAYER SIZE
    pL->layer_size = malloc(sizeof(int));
    *pL->layer_size = size_of_layer;

    pL->neurons = malloc(sizeof(struct Neuron[size_of_layer]));

    pL->number_of_weights_per_neuron = size_of_next_layer;

    for (int i = 0; i < size_of_layer; ++i){
        // CREATE NEURON TO BE ADDED TO ARRAY
        struct Neuron *temp_neuron;
        temp_neuron = malloc(sizeof(struct Neuron));

        // INITIALIZE NEURON'S WEIGHTS AND BIAS -- PASS SIZE OF NEXT LAYER FOR WEIGHTS
        neuron_init(temp_neuron, size_of_next_layer, min, max);

        // PASS THE NEURON INTO THE ARRAY
        pL->neurons[i] = *temp_neuron;

        // FREE THE NEURON'S POINTER AND SET TO NULL
        free(temp_neuron);
        temp_neuron = NULL;
    }
}

// NEURAL NETWORK STARTS HERE
void neural_network_init(struct NeuralNetwork *pNN, int size_of_nn, double min, double max, int input_layer_size, int output_layer_size, int min_hlayer_size, int max_hlayer_size){
    pNN->number_of_layers = size_of_nn;     // SIZE OF NN INCLUDES THE OUTPUT AND INPUT LAYERS

    pNN->layers = malloc(sizeof(struct Layer[size_of_nn]));

    // SET SEED -- NEEDS TO BE DONE IN ORDER TO SET GET RANDOM VALUES
    get_random_double(&min, &max);
    get_random_int(&min_hlayer_size, &max_hlayer_size);

    int current_size = input_layer_size;
    int next_layer_size;

    for(int i = 0; i < size_of_nn - 1; ++i){
        // CREATE NEW LAYER
        struct Layer *l = malloc(sizeof(struct Layer));

        // SET THE NEXT LAYER'S SIZE -- THIS IS CURRENTLY NOT WORKING -- RANDOMNESS WILL BE
        // IMPLEMENTED AT A LATER STAGE
        next_layer_size = get_random_int(&min_hlayer_size, &max_hlayer_size);


        // INIT NEW LAYER
        layer_init(l, current_size, min, max, next_layer_size);

        // ASSIGN THE NEW LAYER TO THE NEURAL NETWORK
        pNN->layers[i] = *l;

        // RELEASE THE TEMP LAYER
        free(l);
        l = NULL;

        // UPDATE THE CURRENT SIZE FOR THE NEXT ITERATION/LAYER -- ALLOWS WEIGHTS OF PREVIOUS LAYER
        // TO MATCH THE NEURONS IN THE CURRENT LAYER
        current_size = next_layer_size;
    }
    // CREATE OUTPUT LAYER

    // CREATE NEW LAYER
    struct Layer *l = malloc(sizeof(struct Layer));

    // INIT NEW LAYER -- SET THE NEXT LAYER TO ONE -- THIS WILL MOST LIKELY BE CHANGED
    // ONCE THE CODE FOR PASSING DATA HAS WRITTEN. ITS MORE OF REPRESENTATION OF THE NEURON RIGHT NOW
    layer_init(l, output_layer_size, min, max, 1);

    // ASSIGN THE NEW LAYER TO THE NEURAL NETWORK
    pNN->layers[size_of_nn - 1] = *l;

    // RELEASE THE TEMP LAYER
    free(l);
    l = NULL;
}

// THIS IS NOT A REAL RANDOM NUMBER GENERATOR. IT IS PREDICTABLE, BUT
// WILL BE OKAY FOR THE TIME BEING.
// ONCE THE NEURAL NETWORK STRUCT, AND THE LEARNING ALGORITHMS
// ARE COMPLETE THIS WILL NEED TO BE FIXED -- IS FINE RIGHT NOW TO SIMULATE RANDOMNESS
double get_random_double(const double *min, const double *max){
//    srand((double) time( ));
//    double value = (float) rand() / (float)(RAND_MAX);
    double value;
    value = (double)rand() / ((double) RAND_MAX + 1);
    return (*min + value * (*max - *min));
}

double get_random_int(const int *min, const int *max){
//    int value;
//    value = (int)rand() / ((int) RAND_MAX + 1);
//    return (*min + value * (*max - *min));
    int total = *min + *max;
    return round(total / 2);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WITH THE LOOPS IN NEURAL_NETWORK_INIT, I THINK I CAN CALL MALLOC JUST ONCE, AND                                    //
// THEN REASSIGN THE VALUES TO THE ADDRESS. THEN, ONCE THE FUNCTION IS FINISHED, I COULD                              //
// FREE UP THE MEMORY.                                                                                                //
// IT SEEMS REDUNDANT TO CALL MALLOC SOME MANY TIMES WHEN THE SPACE SHOULD BE THE SAME                                //
//                                                                                                                    //
// THOUGH THERE WILL MOST LIKELY NEED TO BE A FUNCTION THAT DEALLOCATES FROM NEURONS, LAYERS, AND NEURONS.            //
// IN THIS LIBRARY'S CURRENT STATE, I AM FAIRLY SURE THAT THERE ARE MEMORY LEAKS DUE TO ONLY RELEASING                //
// THE LAYER'S POINT, BUT NOT THE NEURONS POINTERS THAT POINT TO THE WEIGHTS;                                         //
//                                                                                                                    //
// THIS SHOULD CREATE A MEMORY LEAK -- THIS WILL BE A PRIORITY TO ADDRESS                                             //
//                                                                                                                    //
// POSSIBLY CREATE A FUNCTION THAT WILL TAKE IN A LAYER'S POINT AND RELEASE ALL                                       //
// MEMORY DOWN TO THE NEURON'S WEIGHTS.                                                                               //
// THIS MIGHT BE SOMETHING COULD BE HANDLED ON A SEPARATE PROCESS (PROCESSES WILL COME LATER).                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
