// Include all headers

#include <iostream>
#include <map>
#include <array>
#include <list>
#include <random>

using namespace std;

const int MAX = 100;
const int MAX_POWER = 250000;
const int MIN_POWER = 100000;
const int MAX_TEMP = 1000;
const int MIN_TEMP = 250;

// Define function to simulate reactor over 1 time period
    // Parameters: map of components
void step(map<string, array<list<string>, 3>>&);
// Define function to print reactor at time
    // Parameters: map of components
void output(const map<string, array<list<string>, 3>>&);

// Define main
int main() {
    srand(time(0));
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

    reactor["core"][0].push_back("ROD_1");
    reactor["core"][0].push_back("ROD_2");
    reactor["core"][1].push_back("250MW");
    reactor["core"][2].push_back("367C");

    output(reactor);
    step(reactor);
    output(reactor);

    return 0;
}

void step(map<string, array<list<string>, 3>>& reactor) {
    int prob = rand() % MAX; // Generates numbers 0 to 99 inclusive

    // 80% probability of fluctuations
    if (prob < 80) {
        for (string& power : reactor["core"][1]) {
            power = static_cast<string>(rand() % MAX_POWER);
        }
    }
    // For each system
        // Randomly fluctuate electricity and temperature
        // Randomly decide to start a meltdown
        // Randomly decide to active/deactive any components

    for (auto& system : reactor) {
        // Dummy code just pops something
        system.second[0].pop_back();
    }
}

void output(const map<string, array<list<string>, 3>>& reactor) {
    // For each system
        // Output active elements
        // Output electricity draws
        // Output temperatures

    for (auto system : reactor) {
        cout << "Active Components: "; 
        for (auto data : system.second[0]) {
            cout << data << " ";
        }
        cout << endl;

        cout << "Power Draws: "; 
        for (auto data : system.second[1]) {
            cout << data << " ";
        }
        cout << endl;

        cout << "Temperatures: "; 
        for (auto data : system.second[2]) {
            cout << data << " ";
        }
        cout << endl;
    }
}