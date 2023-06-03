#ifndef NEURAL_NETWORK_LIBRARY_H
#define NEURAL_NETWORK_LIBRARY_H

#include <stdlib.h>
#include <time.h>

// STRUCTS
struct Neuron {
    double *weights;                    // AN ARRAY OF WEIGHTS
    double *bias;                       // A SINGLE BIASES FOR THE NEURON -- MIGHT CHANGE THIS TO AN ARRAY LATER
};

struct Layer {
    struct Neuron *neurons;             // ARRAY OF NEURONS
    int *layer_size;                    // SIZE OF THE LAYER
    int number_of_weights_per_neuron;   // NUMBER OF WEIGHTS EACH NEURON HAS
};

struct NeuralNetwork {
    struct Layer *layers;               // ARRAY OF LAYERS - INCLUDES INPUT AND OUTPUT LAYERS
    int number_of_layers;
};

// THE MATRIX MULTIPLICATION WILL MOST DEFINITELY NEED TO ACCESS MEMORY IN BLOCKS. I WOULD LIKE TO
// AVOID USING AN EXTERNAL LIBRARY DUE TO LIMITING LEARNING.

// SETTING/HANDLING THE NEURON'S VALUES
void neuron_initialize_weights_bias(struct Neuron *pN, int size_of_weights, double min, double max);
void neuron_set_neuron_weights(int number_of_weights, struct Neuron *n, const double *values);
void neuron_create_weights(struct Neuron *n, double min, double max, int size_weights);
void neuron_set_weight(struct Neuron *pN, int index, double value);
void neuron_set_bias(struct Neuron *pN, double value);

// SETTING && HANDLING THE LAYER'S VALUES
void layer_init(struct Layer *pL, int size_of_layer, double min, double max, int size_of_next_layer);

// SETTINGS && HANDLING THE NEURAL NETWORK'S VALUES
void neural_network_init(struct NeuralNetwork *pNN, int size_of_nn, double min, double max);

// RANDOM NUMBER GENERATION
double get_random_double(const double *min, const double *max);

#endif //NEURAL_NETWORK_LIBRARY_H
