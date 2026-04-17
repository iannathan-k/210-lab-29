// Include all headers

#include <iostream>
#include <map>
#include <array>
#include <list>
#include <random>

using namespace std;

const int ELE_LIST = 0;
const int POWER_LIST = 1;
const int TEMP_LIST = 2;

const int MAX = 100;
const int MAX_POWER = 250000;
const int MIN_POWER = 100000;
const int MAX_TEMP = 1000;
const int MIN_TEMP = 250;
const int MAX_MELTDOWN_TEMP = 3000;
const int MIN_MELTDOWN_TEMP = 1200;
const int MAX_MELTDOWN_POWER = 1000000;
const int MIN_MELTDOWN_POWER = 500000;

const string SYSTEM_1 = "CORE";
const string SYSTEM_2 = "COOLING";
const string SYSTEM_3 = "WASTE";

// Define function to simulate reactor over 1 time period
    // Parameters: map of components
void step(map<string, array<list<string>, 3>>&);
// Define function to print reactor at time
    // Parameters: map of components
void output(const map<string, array<list<string>, 3>>&);

void activateElement(array<list<string>, 3>&, string);
void deactivateElement(array<list<string>, 3>&);

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

    reactor[SYSTEM_1][ELE_LIST].push_back("BOILER_1");
    reactor[SYSTEM_1][POWER_LIST].push_back("250MW");
    reactor[SYSTEM_1][TEMP_LIST].push_back("367C");
    reactor[SYSTEM_2][ELE_LIST].push_back("ROD_1");
    reactor[SYSTEM_2][POWER_LIST].push_back("250MW");
    reactor[SYSTEM_2][TEMP_LIST].push_back("367C");
    reactor[SYSTEM_3][ELE_LIST].push_back("TANK_1");
    reactor[SYSTEM_3][POWER_LIST].push_back("250MW");
    reactor[SYSTEM_3][TEMP_LIST].push_back("367C");

    output(reactor);

    for (int i = 1; i <= 24; i++) {
        cout << "===== HOUR " << i << " =====" << endl;
        step(reactor);
        output(reactor);
    }

    return 0;
}

void step(map<string, array<list<string>, 3>>& reactor) {

    // For each system
        // Randomly fluctuate electricity and temperature
        // Randomly decide to start a meltdown
        // Randomly decide to active/deactive any components

    for (auto& system : reactor) {
        cout << "~~~~~~~~ " << system.first << " ~~~~~~~~" << endl;
         // 80% probability of fluctuations
        int prob = rand() % MAX + 1; // Generates numbers 0 to 99 inclusive
        if (prob < 80) {
            cout << "Normal Fluctuations Occuring..." << endl;
            // Fluctuate Powers
            for (string& power : system.second[1]) {
                power = to_string(rand() % (MAX_POWER - MIN_POWER + 1) + MIN_POWER) + "MW";
            }

            // Fluctuare Temps
            for (string& temp : system.second[2]) {
                temp = to_string(rand() % (MAX_TEMP - MIN_TEMP + 1) + MIN_TEMP) + "C";
            }
        }

        // Deactivate an element
        prob = rand() % MAX + 1;
        if (prob < 15 && system.second[0].size() > 0) {
            cout << "Deactivating an element..." << endl;
            deactivateElement(system.second);
        }

        // Active an element
        prob = rand() % MAX + 1;
        if (prob < 20) {
            cout << "Activating an element..." << endl;
            activateElement(system.second, system.first);
        }

        // Temperature surge!!!
        prob = rand() % MAX + 1;
        if (prob < 5) {
            cout << "!! EMERGENCY !! Power Surge Occuring!!!!" << endl;
            for (string& power : system.second[1]) {
                power = to_string(rand() % (MAX_MELTDOWN_POWER - MIN_MELTDOWN_POWER + 1) + MIN_MELTDOWN_POWER) + "MW";
            }

            for (string& temp : system.second[2]) {
                temp = to_string(rand() % (MAX_MELTDOWN_TEMP - MIN_MELTDOWN_TEMP + 1) + MIN_MELTDOWN_TEMP) + "C";
            }
        }
    }
}

void output(const map<string, array<list<string>, 3>>& reactor) {
    // For each system
        // Output active elements
        // Output electricity draws
        // Output temperatures
    cout << "~~~~~~~ CURRENT ~~~~~~~~" << endl;

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

void activateElement(array<list<string>, 3>& system, string system_name) {
    string prefix = "BOILER_";
    if (system_name == SYSTEM_2) {
        prefix = "ROD_";
    } else if (system_name == SYSTEM_3) {
        prefix = "TANK_";
    }

    system[ELE_LIST].push_back(prefix + to_string(system[ELE_LIST].size() + 1));
    system[POWER_LIST].push_back(to_string(rand() % (MAX_POWER - MIN_POWER + 1) + MIN_POWER) + "MW");
    system[TEMP_LIST].push_back(to_string(rand() % (MAX_TEMP - MIN_TEMP + 1) + MIN_TEMP) + "C");
    
}

void deactivateElement(array<list<string>, 3>& system) {
    system[ELE_LIST].pop_back();
    system[POWER_LIST].pop_back();
    system[TEMP_LIST].pop_back();
}