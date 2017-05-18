#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "Vector.h"

class NeuralNetwork
{
    // weights[i][j] is the input weight from neuron i to neuron j
    f64** weights;
    // k parameter of logistic sigmoid function
    f64 steepness;
    // learning rate
    f64 learningRate;
    // the size of the weight matrix
    u32 weightSize;
    // number of inputs
    u32 numInputs;
    // number of hidden neurons
    u32 numHidden;

    // logistic sigmoid function for neuron activation
    f64 activation(f64 sum);

    // we store the previous activation results of all the hidden neurons
    // for reference if we are told to update weights
    // this is deleted and replaced if feedInputs is called again
    f64* lastHiddenActivation;
    // same as above; store the previous activation result of the output neuron
    f64 lastOutputActivation;

public:

    // Construct network with given number of input and hidden layer neurons
    // Assume 1 output
    // steep = steepness, rate = learningRate
    NeuralNetwork(u32 inputs, u32 hidden, f64 steep, f64 rate);

    // Feed the list of inputs forward through the network,
    // return the output
    f64 feedInputs(Vector<f64>& inputs);

    // Correct the weights in the network to more closely match the
    // expected output
    void correctWeights(Vector<f64>& inputs, f64 expectedOutput);
    
};

#endif
