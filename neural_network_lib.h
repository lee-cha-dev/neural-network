#ifndef NEURAL_NETWORK_LIBRARY_H
#define NEURAL_NETWORK_LIBRARY_H

#include <stdlib.h>
#include <time.h>


struct Neuron {
    double *weights;        // AN ARRAY OF WEIGHTS
    double *bias;           // A SINGLE BIASES FOR THE NEURON -- MIGHT CHANGE THIS TO AN ARRAY LATER
    int *size_weights;
};

// SETTING/HANDLING THE NEURON'S VALUES
void neuron_initialize_weights_bias(struct Neuron *pN, int size_of_weights, double min, double max);
void neuron_set_neuron_weights(int number_of_weights, struct Neuron *n, const double *values);
void neuron_create_weights(struct Neuron *n, const double *min, const double *max);
void neuron_set_weight(struct Neuron *pN, int index, double value);
void neuron_set_bias(struct Neuron *pN, double value);

// RANDOM NUMBER GENERATION
double get_random_double(const double *min, const double *max);

#endif //NEURAL_NETWORK_LIBRARY_H
