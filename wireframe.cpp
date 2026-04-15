// Include all headers

#include <iostream>
#include <map>
#include <array>
#include <list>
#include <random>

using namespace std;

// Define function to simulate reactor over 1 time period
    // Parameters: map of components
void step(map<string, array<list<string>, 3>>&);
// Define function to print reactor at time
    // Parameters: map of components
void output(const map<string, array<list<string>, 3>>&);

// Define main
int main() {

    // Declare the map
    map<string, array<list<string>, 3>> reactor;
    // Initialize the map
    // Open file

    // If file successfully opens
        // Read data and populate
        // Insert appropriate data to appropriate systems

        // Begin time based simulation
        // For 72 Intervals
            // Step
            // Print
    // Else
        // Raise error
    // Close file

    return 0;
}

void step(map<string, array<list<string>, 3>>& reactor) {
    // For each system
        // Randomly fluctuate electricity and temperature
        // Randomly decide to start a meltdown
        // Randomly decide to active/deactive any components
}

void output(const map<string, array<list<string>, 3>>& reactor) {
    // For each system
        // Output active elements
        // Output electricity draws
        // Output temperatures

    for (auto system : reactor) {
        for (auto data : system.second) {
            
        }
    }
}