#include "neural_network_lib.h"
#include <stdio.h>

// NN STARTS HERE
void nn_init(struct NN *pNN, double min_weight_val, double max_weight_val, int input_layer_size, int output_layer_size, int min_hlayer_size, int max_hlayer_size){
    //---ALLOCATE SPACE TO LAYERS
    // INPUT LAYER: POINTERS(LAYER) -> POINTERS(NEURON) -> DOUBLE(WEIGHT)
    pNN->input_layer = malloc(input_layer_size * sizeof(double**));

    // HIDDEN LAYER: POINTERS(LAYERS) -> POINTERS(LAYER) -> POINTERS(NEURON) -> DOUBLE(WEIGHT)
    int hidden_layer_size = (min_hlayer_size + max_hlayer_size) / 2;        // WILL EVENTUALLY RETURN RANDOM VAL WITHIN RANGE
    pNN->hidden_layers = malloc(hidden_layer_size * sizeof(double***));

    // OUTPUT LAYER: POINTERS(LAYER) TO POINTERS(NEURON) TO DOUBLE(WEIGHT)
    pNN->output_layer = malloc(output_layer_size * sizeof(double**));

    //---ALLOCATE SPACE TO BIASES - EACH NEURON HAS ONE BIAS VALUE
    // INPUT LAYER BIASES: POINTERS(LAYER) -> DOUBLE(BIAS)
    pNN->input_layer_biases = malloc(input_layer_size * sizeof(double*));

    // HIDDEN LAYERS: POINTERS(LAYERS) -> POINTERS(LAYER) -> DOUBLE(BIAS)
    pNN->hidden_layers_biases = malloc(hidden_layer_size * sizeof(double**));

    // OUTPUT LAYER: POINTER(LAYER) -> DOUBLE(BIAS)
    pNN->output_layer_biases = malloc(output_layer_size * sizeof(double*));

    // CREATE THE POINTERS AND THE VALUES THEY ARE POINTING TO

    // CREATE THE INPUT LAYER
    pNN->input_layer_size = input_layer_size;
//    int next_layer_size = get_random_int(&min_weight_val, &max_weight_val);
    int next_layer_size = (min_hlayer_size + max_hlayer_size) / 2;

    for(int i = 0; i < input_layer_size; ++i){
        // SET THE NEURON ARRAY THAT IS POINTING TO A WEIGHT TO THE SIZE OF THE NEXT LAYER
        // THIS WILL ENSURE EACH NEURON HAS ENOUGH WEIGHTS TO MATCH THE NEXT LAYER
        // pNN->input_layer[i] is at the neuron
        pNN->input_layer[i] = malloc(next_layer_size * sizeof(double));

        // pNN->input_layer[i][j] is at the double variable
        // INIT THE WEIGHT VALUES -- WORKING WITHIN THE
        for(int j = 0; j < next_layer_size; ++j){
            // ALLOCATE SPACE FOR DOUBLE AND ASSIGN IT TO 0.0
            pNN->input_layer[i][j] = (double)j;
        }
    }

    // SETTING FIRST HIDDEN LAYER SIZE FOR FREE_NN TESTING
    pNN->hidden_layer_sizes = malloc(hidden_layer_size * sizeof(int));  // MOVE THIS TO MEM INIT @TOP

    // CODES NEEDS TO BE RAN WITHIN TEST ENV -- STARTS
    //------------------------------------------------------------------------------------------------------------//

    // CREATE THE HIDDEN LAYERS
    // ACCESSING INDIVIDUAL HIDDEN LAYERS
    for(int i = 0; i < hidden_layer_size; ++i){
        pNN->hidden_layer_sizes[i] = next_layer_size;
        pNN->hidden_layers[i] = malloc(next_layer_size * sizeof(double**));

        // UPDATE CURRENT LAYER
        int current_layer = next_layer_size;
        next_layer_size = (min_hlayer_size + max_hlayer_size) / 2;

        // CREATE NEURONS WITHIN EACH HIDDEN LAYER
        for(int j = 0; j < current_layer; ++j){
            pNN->hidden_layers[i][j] = malloc(next_layer_size * sizeof(double));

            // ASSIGN DOUBLE VALUES TO WEIGHT OF EACH NEURON
            for(int k = 0; k < next_layer_size; ++k){
                pNN->hidden_layers[i][j][k] = 0.00;
            }
        }
    }
    //------------------------------------------------------------------------------------------------------------//
    // CODES NEEDS TO BE RAN WITHIN TEST ENV -- ENDS
}

void free_nn_pointers(struct NN *pNN, int input_layer_size){
    // FREE INPUT LAYER
    for(int i = 0; i < pNN->input_layer_size; ++i){
        free(pNN->input_layer[i]);
        pNN->input_layer[i] = NULL;
    }
    free(pNN->input_layer);
    pNN->input_layer = NULL;

    // FREE HIDDEN LAYER

    // FREE OUTPUT LAYER
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
