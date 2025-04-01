#include <iostream>
#include <limits>
#include "audio_effects.h"

void displayMenu() {
    std::cout << "\n=== Audio Effects Processor ===";
    std::cout << "\n1. Apply Echo Effect";
    std::cout << "\n2. Apply Pitch Shift";
    std::cout << "\n3. Change Speed";
    std::cout << "\n4. Show Audio Info";
    std::cout << "\n5. Save and Exit";
    std::cout << "\n6. Exit Without Saving";
    std::cout << "\nChoice: ";
}

void displayAudioInfo(const AudioData& audio) {
    std::cout << "\n=== Audio Information ===";
    std::cout << "\nSample Rate: " << audio.info.samplerate << " Hz";
    std::cout << "\nChannels: " << audio.info.channels;
    std::cout << "\nFrames: " << audio.info.frames;
    std::cout << "\nDuration: " << (audio.info.frames / static_cast<double>(audio.info.samplerate)) << " seconds";
    std::cout << "\nSamples: " << audio.samples.size() << std::endl;
}

double getValidInput(const std::string& prompt, double min, double max) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a value between " << min << " and " << max << std::endl;
        }
        else {
            break;
        }
    }
    return value;
}

int main() {
    std::cout << "=== Audio Effects Processor ===" << std::endl;

    const char* inputFile = "input.wav";
    const char* outputFile = "output.wav";

    // Load audio file
    std::cout << "Loading audio file: " << inputFile << std::endl;
    AudioData audio = loadAudioFile(inputFile);
    displayAudioInfo(audio);

    int choice = 0;
    while (choice != 5 && choice != 6) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1: {
            double delay = getValidInput("Enter echo delay (0.1-1.0 seconds): ", 0.1, 1.0);
            double decay = getValidInput("Enter echo decay (0.1-0.9): ", 0.1, 0.9);
            applyEcho(audio, delay, decay);
            std::cout << "Echo effect applied." << std::endl;
            break;
        }
        case 2: {
            double shift = getValidInput("Enter pitch shift ratio (0.5-2.0): ", 0.5, 2.0);
            pitchShift(audio, shift);
            std::cout << "Pitch shift applied." << std::endl;
            break;
        }
        case 3: {
            double speed = getValidInput("Enter speed ratio (0.5-2.0): ", 0.5, 2.0);
            changeSpeed(audio, speed);
            std::cout << "Speed changed." << std::endl;
            break;
        }
        case 4:
            displayAudioInfo(audio);
            break;
        case 5: {
            std::cout << "Saving processed audio to: " << outputFile << std::endl;
            saveAudioFile(outputFile, audio);
            std::cout << "File saved successfully. Exiting..." << std::endl;
            break;
        }
        case 6:
            std::cout << "Exiting without saving..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }

    system("pause");
    return 0;
}