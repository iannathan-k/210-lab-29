#include <iostream>
#include <array>
#include <list>

using namespace std;

// COMSC-210 | Lab 29 | Ian Kusmiantoro

void activateElement(array<list<string>, 3>&, string);
void deactivateElement(array<list<string>, 3>&);
void fluctuate(array<list<string>, 3>&);
void surge(array<list<string>, 3>&);

bool testFluctuate(const array<list<string>, 3>& reactor) {
    array<list<string>, 3> copy = reactor;

    fluctuate(copy);

    if (copy[0] != reactor[0]) {
        // Fluctuate should not affect the elements!
        cout << "Elements should not be affected!" << endl;
        return false;
    }

    for (int i = 1; i < 3; i++) {
        if (copy[i] != reactor[i]) {
            return true; // We found the array to be different, so we can it did successfully fluctuate
        }
    }

    cout << "All power and temperatures are the same!" << endl;
    return false;
}

bool testActivate(const array<list<string>, 3>& reactor) {
    array<list<string>, 3> copy = reactor;

    activateElement(copy, "CORE");

    for (int i = 0; i < 3; i++) {
        if (copy[i].size() > reactor[i].size() + 1) {
            cout << "More than 1 element added!" << endl;
            return false; // Did not only add 1 element!
        }
        if (copy[i].size() == reactor[i].size() + 1) {
            cout << "No elements added!" << endl;
            return false; // Did not only add 1 element!
        }
        if (copy[i].size() < reactor[i].size()) {
            cout << "Elements were removed!" << endl;
            return false; // Did not only add 1 element!
        }
    }

    return true;
}

bool testDeactive(const array<list<string>, 3>& reactor) {
    array<list<string>, 3> copy = reactor;

    deactivateElement(copy);

    for (int i = 0; i < 3; i++) {
        if (copy[i].size() < reactor[i].size() - 1) {
            cout << "More than 1 element removed!" << endl;
            return false; // Did not only remove 1 element!
        }
        if (copy[i].size() > reactor[i].size()) {
            cout << "Elements were added!" << endl;
            return false; // Did not only remove 1 element!
        }
        if (copy[i].size() == reactor[i].size()) {
            cout << "No elements were removed!" << endl;
            return false; // Did not only remove 1 element!
        }
    }

    return true;
}

bool testMeltdown(const array<list<string>, 3>& reactor) {
    array<list<string>, 3> copy = reactor;

    surge(copy);

    if (copy[0] != reactor[0]) {
        // Meltdown should not affect the elements!
        cout << "Elements should not be affected!" << endl;
        return false;
    }

    for (int i = 1; i < 3; i++) {
        if (copy[i] != reactor[i]) {
            return true; // We found the array to be different, so we can it did successfully meltdown
        }
    }

    cout << "Power and temps are the same!" << endl;
    return false;
}

int main() {
    array<list<string>, 3> reactor;

    if (testActivate(reactor)) {
        cout << "Activation test passed." << endl;
    } else {
        cout << "Activation test failed!" << endl;
    }
    if (testFluctuate(reactor)) {
        cout << "Fluctuation test passed" << endl;
    } else {
        cout << "Fluctuation test failed!" << endl;
    }
    if (testMeltdown(reactor)) {
        cout << "Meltdown test passed" << endl;
    } else {
        cout << "Meltdown test failed!" << endl;
    }
    if (testDeactive(reactor)) {
        cout << "Deactivation test passed" << endl;
    } else {
        cout << "Deactivation test failed!" << endl;
    }

    return 0;
}