#ifndef NEURAL_NETWORK_LIBRARY_H
#define NEURAL_NETWORK_LIBRARY_H

#include <stdlib.h>
#include <time.h>
#include <math.h>

// STRUCTS
struct Neuron {
    double *weights;                    // AN ARRAY OF WEIGHTS
    double bias;                       // A SINGLE BIASES FOR THE NEURON -- MIGHT CHANGE THIS TO AN ARRAY LATER
};

struct Layer {
    struct Neuron *neurons;             // ARRAY OF NEURONS
    int layer_size;                    // SIZE OF THE LAYER
    int number_of_weights_per_neuron;   // NUMBER OF WEIGHTS EACH NEURON HAS
    int next_layer_size;
};

struct NeuralNetwork {
    struct Layer *layers;               // ARRAY OF LAYERS - INCLUDES INPUT AND OUTPUT LAYERS
    int number_of_layers;
};

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

    int number_of_hidden_layers;
};

// THE MATRIX MULTIPLICATION WILL MOST DEFINITELY NEED TO ACCESS MEMORY IN BLOCKS. I WOULD LIKE TO
// AVOID USING AN EXTERNAL LIBRARY DUE TO LIMITING LEARNING.

// SETTING/HANDLING THE NEURON'S VALUES
void neuron_init(struct Neuron *pN, int size_of_weights, double min, double max);
void neuron_set_neuron_weights(int number_of_weights, struct Neuron *n, const double *values);
void neuron_free_weights(struct Neuron *pN);
void neuron_create_weights(struct Neuron *n, double min, double max, int size_weights);
void neuron_set_weight(struct Neuron *pN, int index, double value);
void neuron_set_bias(struct Neuron *pN, double value);

// SETTING && HANDLING THE LAYER'S VALUES
void layer_init(struct Layer *pL, int size_of_layer, double min, double max, int size_of_next_layer);
void layer_free_neurons(struct Layer *pL);

// SETTINGS && HANDLING THE NEURAL NETWORK'S VALUES
void neural_network_init(struct NeuralNetwork *pNN, int size_of_nn, double min, double max, int input_layer_size, int output_layer_size, int min_hlayer_size, int max_hlayer_size);

// RANDOM NUMBER GENERATION
double get_random_double(const double *min, const double *max);
double get_random_int(const int *min, const int *max);

#endif //NEURAL_NETWORK_LIBRARY_H
