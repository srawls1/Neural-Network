#include "NeuralNetwork.h"
#include <string>
#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;
using std::string;

f64 myAbs(f64 n)
{
    return (n < 0.0) ? -1.0 * n : n;
}

Vector<f64> getInputs(u32 numInputs)
{
    Vector<f64> inputs(numInputs);
    cout << "Enter a sequence of 0's and 1's" << endl;
    string input;
    while (inputs.size() < numInputs)
    {
        cout << (numInputs - inputs.size()) << " remaining" << endl;
        cin >> input;
        for (u32 i = 0; i < input.length() && inputs.size() < numInputs; ++i)
        {
            switch (input[i])
            {
                case '0': inputs.add(0.f); break;
                case '1': inputs.add(1.f); break;
                default: cout << "Unrecognized character: " << input[i] << endl;
            }
        }
    }
    return inputs;
}

Vector<Vector<f64>> getInputSets(Vector<f64>& flips)
{
    Vector<Vector<f64>> inputSets(flips.size() / 2);
    for (u32 i = 0; i < flips.size() / 2; ++i)
    {
        Vector<f64> inputSet(flips.size() / 2);
        for (u32 j = 0; j < flips.size() / 2; ++j)
        {
            inputSet.add(flips[i + j]);
        }
        inputSets.add(inputSet);
    }
    return inputSets;
}

Vector<f64> getOutputs(Vector<f64>& flips)
{
    Vector<f64> outputs(flips.size() / 2);
    for (u32 i = 0; i < flips.size() / 2; ++i)
    {
        outputs.add(flips[flips.size() / 2 + i]);
    }
    return outputs;
}

void trainNetwork(NeuralNetwork& network, Vector<Vector<f64>>& inputSets, Vector<f64> outputs, f64 correctness)
{
    f64 currentlyCorrect;
    while (currentlyCorrect < correctness)
    {
        currentlyCorrect = 0.0;
        for (u32 i = 0; i < inputSets.size(); ++i)
        {
            f64 result = network.feedInputs(inputSets[i]);
            //cout << "Result: " << result << "; Desired: " << outputs[i] << endl;
            f64 error = result - outputs[i];
            if (myAbs(error) < 0.5)
            {
                currentlyCorrect += 1.0 / inputSets.size();
            }
            network.correctWeights(inputSets[i], outputs[i]);
        }
        //cout << "Currently correct: " << currentlyCorrect << endl;
    }
}

void startPrediction(NeuralNetwork& network, Vector<f64> allInputs, u32 numInputs)
{
    u32 correctGuesses = 0, totalGuesses = 0;
    while (true)
    {
        Vector<f64> inputs(numInputs);
        for (u32 i = 0; i < numInputs; ++i)
        {
            inputs.add(allInputs[allInputs.size() - numInputs + i]);
        }
        i32 prediction = (network.feedInputs(inputs) < 0.5) ? 0 : 1;
        i32 nextInput;
        cout << "I have predicted your next flip. Enter your flip now." << endl;
        cout << "Enter anything besides 0 or 1 to quit" << endl;
        cin >> nextInput;
        allInputs.add((f64)nextInput);
        if ((nextInput != 0 && nextInput != 1) || !cin)
        {
            break;
        }
        cout << "I predicted " << prediction << ". You entered " << nextInput << endl;
        if (nextInput == prediction)
        {
            ++correctGuesses;
            cout << "I win!" << endl;
        }
        else
        {
            cout << "You win this time" << endl;
        }
        ++totalGuesses;
    }
    cout << "I guessed your input correctly "
        << (float)correctGuesses / totalGuesses * 100.f << "% of the time."
        << endl;
}

int main(u32 argc, char** argv)
{
    u32 numInputs = 32;
    u32 hiddenNeurons = 16;
    f64 learningRate = 0.1f;
	f64 steepness = 5.f;
    f64 correctness = 0.8f;

    for (u32 i = 1; i < argc - 1; ++i)
    {
        if (strncmp(argv[i], "-h", 2) == 0)
        {
            hiddenNeurons = atoi(argv[i + 1]);
        }
        else if (strncmp(argv[i], "-a", 2) == 0)
        {
            learningRate = atof(argv[i + 1]);
        }
        else if (strncmp(argv[i], "-c", 2) == 0)
        {
            correctness = atof(argv[i + 1]);
        }
		else if (strncmp(argv[i], "-k", 2) == 0)
		{
			steepness = atof(argv[i + 1]);
		}
    }

    Vector<f64> inputs = getInputs(64);
    Vector<Vector<f64>> inputSets = getInputSets(inputs);
    Vector<f64> outputs = getOutputs(inputs);
    NeuralNetwork network(numInputs, hiddenNeurons, steepness, learningRate);
    trainNetwork(network, inputSets, outputs, correctness);
    startPrediction(network, inputs, numInputs);
}
