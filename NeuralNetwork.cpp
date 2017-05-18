#include "NeuralNetwork.h"
#include <cmath>
#include <cstdlib>


f64 NeuralNetwork::activation(f64 sum)
{
    return 1.0 / (1.0 + exp(-steepness * sum));
}

NeuralNetwork::NeuralNetwork(u32 inputs, u32 hidden, f64 steep, f64 rate)
: steepness(steep), learningRate(rate), numInputs(inputs), numHidden(hidden)
{
    lastHiddenActivation = nullptr;
    weightSize = inputs + hidden + 1;
    // initialize the weight matrix
    weights = new f64*[weightSize];
    for (u32 i = 0; i < weightSize; ++i)
    {
        weights[i] = new f64[weightSize];
        // give everything random weights to start
        for (u32 j = 0; j < weightSize; ++j)
        {
            if ((i < numInputs && numInputs <= j && j < numInputs + numHidden)
                || (numInputs <= i && i < numInputs + numHidden && j == numInputs + numHidden))
                weights[i][j] = (double)(rand() % 100) / 100.0 - 0.5;
            else
                weights[i][j] = 0.0;
        }
    }
}

f64 NeuralNetwork::feedInputs(Vector<f64>& inputs)
{
    f64* nextInputs = new f64[numHidden];
    for (u32 i = 0; i < numHidden; ++i)
        nextInputs[i] = 0.0;
    for (u32 i = 0; i < inputs.size(); ++i)
    {
        for (u32 j = 0; j < numHidden; ++j)
            nextInputs[j] += inputs[i] * weights[i][j + numInputs];
    }
    for (u32 j = 0; j < numHidden; ++j)
        nextInputs[j] = activation(nextInputs[j]);
    f64 output = 0.0;
    for (u32 j = 0; j < numHidden; ++j)
        output += nextInputs[j] * weights[numInputs + j][weightSize - 1];
    lastOutputActivation = activation(output);
    if (lastHiddenActivation != nullptr)
        delete[] lastHiddenActivation;
    lastHiddenActivation = nextInputs;
    return lastOutputActivation;
}

void NeuralNetwork::correctWeights(Vector<f64>& inputs, f64 expectedOutput)
{
    // Correct weights incoming to the output neuron
    f64 outputError = (lastOutputActivation - expectedOutput);
    outputError *= lastOutputActivation * (1.0 - lastOutputActivation) * steepness;
    for (u32 i = 0; i < numHidden; ++i)
    {
        weights[i + numInputs][numInputs + numHidden] -=
            lastHiddenActivation[i] * learningRate * outputError;
    }

    // Correct the weights incoming to the hidden layer
    for (u32 i = 0; i < numHidden; ++i)
    {
        f64 hiddenError = weights[i + numInputs][numInputs + numHidden] * outputError;
        hiddenError *= lastHiddenActivation[i] * (1.0 - lastHiddenActivation[i]) * steepness;
        for (u32 j = 0; j < numInputs; ++j)
        {
            weights[j][i + numInputs] -= inputs[j] * hiddenError * learningRate;
        }
    }
}
