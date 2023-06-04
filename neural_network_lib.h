#ifndef NEURAL_NETWORK_LIBRARY_H
#define NEURAL_NETWORK_LIBRARY_H

#include <stdlib.h>
#include <time.h>
#include <math.h>

//******************************************************************//
// MIGHT BE BETTER TO USE ONLY ONE STRUCT AND HAVE POINTERS TO
// POINTERS FOR ARRAYS.
// THIS WOULD ENSURE THAT POINTERS ARE NOT BEING
// LOST IN OTHER STRUCTURES
// THIS COULD REMOVE THE LEVELS OF CODE ABSTRACTION THAT WERE
// OCCURRING WITH USING NEURON AND LAYER STRUCTS.
// THE PREVIOUS APPROACH WAS CREATING MEMORY LEAKS,
// AND A SINGULAR STRUCT IS LESS CONVOLUTED.
//******************************************************************//

struct NN {
    double **input_layer;
    double ***hidden_layers;
    double **output_layer;

    double **input_layer_biases;
    double ***hidden_layers_biases;
    double **output_layer_biases;

    int number_of_hidden_layers;
};

// THE MATRIX MULTIPLICATION WILL MOST DEFINITELY NEED TO ACCESS MEMORY IN BLOCKS. I WOULD LIKE TO
// AVOID USING AN EXTERNAL LIBRARY DUE TO LIMITING LEARNING.

// SETTING && HANDLING THE NN'S VALUES
void nn_init(struct NN *pNN, double min_weight_val, double max_weight_val, int input_layer_size, int output_layer_size, int min_hlayer_size, int max_hlayer_size);

// RANDOM NUMBER GENERATION
double get_random_double(const double *min, const double *max);
double get_random_int(const int *min, const int *max);

#endif //NEURAL_NETWORK_LIBRARY_H
