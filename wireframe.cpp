// Include all headers

#include <iostream>
#include <map>
#include <array>
#include <list>
#include <random>
#include <fstream>

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

const int PROB_FLUX = 80;
const int PROB_ACT = 15;
const int PROB_DEACT = 20;
const int PROB_MELT = 5;

const int DATA_LENGTH = 3;
const int DATA_COUNT = 12;

const int DURATION = 48;

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
void fluctuate(array<list<string>, 3>&);
void surge(array<list<string>, 3>&);

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

    ifstream fin;
    fin.open("initial.txt");

    if (!fin.good()) {
        cout << "Something went wrong with reading" << endl;
        exit(1);
    }

    for (int j = 0; j < DATA_COUNT; j++) {
        for (int i = 0; i < DATA_LENGTH; i++) {
            string input;
            fin >> input;

            reactor[SYSTEM_1][i].push_back(input);
        }

        for (int i = 0; i < DATA_LENGTH; i++) {
            string input;
            fin >> input;

            reactor[SYSTEM_2][i].push_back(input);
        }

        for (int i = 0; i < DATA_LENGTH; i++) {
            string input;
            fin >> input;

            reactor[SYSTEM_3][i].push_back(input);
        }
    }
    
    output(reactor);

    for (int i = 1; i <= DURATION; i++) {
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
        if (prob <= PROB_FLUX) {
            cout << "Normal Fluctuations Occuring..." << endl;
            fluctuate(system.second);
        }

        // Deactivate an element
        prob = rand() % MAX + 1;
        if (prob <= PROB_DEACT && system.second[ELE_LIST].size() > 0) {
            cout << "Deactivating an element..." << endl;
            deactivateElement(system.second);
        }

        // Active an element
        prob = rand() % MAX + 1;
        if (prob <= PROB_ACT) {
            cout << "Activating an element..." << endl;
            activateElement(system.second, system.first);
        }

        // Temperature surge!!!
        prob = rand() % MAX + 1;
        if (prob <= PROB_MELT) {
            cout << "!! EMERGENCY !! Power Surge Occuring!!!!" << endl;
            surge(system.second);
        }
    }
}

void output(const map<string, array<list<string>, 3>>& reactor) {
    // For each system
        // Output active elements
        // Output electricity draws
        // Output temperatures
    cout << "++++++++++ SNAPSHOT ++++++++++" << endl;

    for (auto system : reactor) {
        cout << "~~~~~~~~ " << system.first << " ~~~~~~~~" << endl;
        cout << "Active Components: "; 
        for (auto data : system.second[ELE_LIST]) {
            cout << data << " ";
        }
        cout << endl;

        cout << "Power Draws: "; 
        for (auto data : system.second[POWER_LIST]) {
            cout << data << " ";
        }
        cout << endl;

        cout << "Temperatures: "; 
        for (auto data : system.second[TEMP_LIST]) {
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
        prefix = "PUMP_";
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

void fluctuate(array<list<string>, 3>& system) {
    // Fluctuate Powers
    for (string& power : system[POWER_LIST]) {
        power = to_string(rand() % (MAX_POWER - MIN_POWER + 1) + MIN_POWER) + "MW";
    }

    // Fluctuare Temps
    for (string& temp : system[TEMP_LIST]) {
        temp = to_string(rand() % (MAX_TEMP - MIN_TEMP + 1) + MIN_TEMP) + "C";
    }
}

void surge(array<list<string>, 3>& system) {
    // Surge Powers
    for (string& power : system[POWER_LIST]) {
        power = to_string(rand() % (MAX_MELTDOWN_POWER - MIN_MELTDOWN_POWER + 1) + MIN_MELTDOWN_POWER) + "MW";
    }

    // Surge Temps
    for (string& temp : system[TEMP_LIST]) {
        temp = to_string(rand() % (MAX_MELTDOWN_TEMP - MIN_MELTDOWN_TEMP + 1) + MIN_MELTDOWN_TEMP) + "C";
    }
}