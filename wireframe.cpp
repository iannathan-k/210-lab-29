// Include all headers

#include <iostream>
#include <map>
#include <array>
#include <list>
#include <random>
#include <fstream>
#include <ctime>

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

const int DURATION = 36;

const string FILE_NAME = "start.txt";

const string SYSTEM_1 = "CORE";
const string SYSTEM_2 = "COOLING";
const string SYSTEM_3 = "WASTE";
const string SYSTEM_1_PREFIX = "BOILER";
const string SYSTEM_2_PREFIX = "ROD";
const string SYSTEM_3_PREFIX = "PUMP";

// Define function to simulate reactor over 1 time period
    // Parameters: map of components
void step(map<string, array<list<string>, 3>>&);
// Define function to print reactor at time
    // Parameters: map of components
void output(const map<string, array<list<string>, 3>>&);
void loadData(map<string, array<list<string>, 3>>&, string);
string genRand(int, int);

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
    
    loadData(reactor, FILE_NAME);
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
        cout << "\t" << system.first << ":" << endl;
         // 80% probability of fluctuations
        int prob = rand() % MAX + 1; // Generates numbers 1 to 100 inclusive
        if (prob <= PROB_FLUX) {
            cout << "\t\tNormal Fluctuations Occuring..." << endl;
            fluctuate(system.second);
        }

        // Deactivate an element
        prob = rand() % MAX + 1;
        if (prob <= PROB_DEACT) {
            cout << "\t\tDeactivating an element..." << endl;
            deactivateElement(system.second);
        }

        // Active an element
        prob = rand() % MAX + 1;
        if (prob <= PROB_ACT) {
            cout << "\t\tActivating an element..." << endl;
            activateElement(system.second, system.first);
        }

        // Temperature surge!!!
        prob = rand() % MAX + 1;
        if (prob <= PROB_MELT) {
            cout << "\t\t!! EMERGENCY !! Power Surge Occuring!!!!" << endl;
            surge(system.second);
        }
    }
}

void output(const map<string, array<list<string>, 3>>& reactor) {
    // For each system
        // Output active elements
        // Output electricity draws
        // Output temperatures
    cout << "+++++ SNAPSHOT +++++" << endl;

    for (auto system : reactor) {
        cout << "\t" << system.first << ":" << endl;
        cout << "\t\tActive Components: "; 
        for (auto data : system.second[ELE_LIST]) {
            cout << data << " ";
        }
        cout << endl;

        cout << "\t\tPower Draws: "; 
        for (auto data : system.second[POWER_LIST]) {
            cout << data << " ";
        }
        cout << endl;

        cout << "\t\tTemperatures: "; 
        for (auto data : system.second[TEMP_LIST]) {
            cout << data << " ";
        }
        cout << endl;
    }
}

void activateElement(array<list<string>, 3>& system, string system_name) {
    if (system[ELE_LIST].size() >= DATA_COUNT) { // Prevent runaway activation :P
        cout << "\t\tMax elements already activated..." << endl;
        return;
    }

    string prefix = "";
    if (system_name == SYSTEM_1) {
        prefix = SYSTEM_1_PREFIX;
    } else if (system_name == SYSTEM_2) {
        prefix = SYSTEM_2_PREFIX;
    } else if (system_name == SYSTEM_3) {
        prefix = SYSTEM_3_PREFIX;
    }
    prefix += "_" + to_string(system[ELE_LIST].size() + 1);

    system[ELE_LIST].push_back(prefix);
    system[POWER_LIST].push_back(genRand(MIN_POWER, MAX_POWER) + "MW");
    system[TEMP_LIST].push_back(genRand(MIN_TEMP, MAX_TEMP) + "C");
}

void deactivateElement(array<list<string>, 3>& system) {
    if (system[ELE_LIST].size() <= 0) {
        cout << "\t\tNo element to deactivate..." << endl;
        return;
    }

    system[ELE_LIST].pop_back();
    system[POWER_LIST].pop_back();
    system[TEMP_LIST].pop_back();
}

void fluctuate(array<list<string>, 3>& system) {
    // Fluctuate Powers
    for (string& power : system[POWER_LIST]) {
        power = genRand(MIN_POWER, MAX_POWER) + "MW";
    }

    // Fluctuare Temps
    for (string& temp : system[TEMP_LIST]) {
        temp = genRand(MIN_TEMP, MAX_TEMP) + "C";
    }
}

void surge(array<list<string>, 3>& system) {
    // Surge Powers
    for (string& power : system[POWER_LIST]) {
        power = genRand(MIN_MELTDOWN_POWER, MAX_MELTDOWN_POWER) + "MW";
    }

    // Surge Temps
    for (string& temp : system[TEMP_LIST]) {
        temp = genRand(MIN_MELTDOWN_TEMP, MAX_MELTDOWN_TEMP) + "C";
    }
}

void loadData(map<string, array<list<string>, 3>>& reactor, string file_name) {
    ifstream fin;
    fin.open(file_name);

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

    fin.close();
}

string genRand(int min, int max) {
    return to_string(rand() % (max - min + 1) + min);
}