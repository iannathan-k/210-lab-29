#include <iostream>
#include <array>
#include <list>

using namespace std;

// COMSC-210 | Lab 29 | Ian Kusmiantoro

bool testFluctuate(const array<list<string>, 3>& reactor) {
    array<list<string>, 3> copy = reactor;

    fluctuate(copy);

    if (copy[0] != reactor[0]) {
        // Fluctuate should not affect the elements!
        return false;
    }

    for (int i = 1; i < 3; i++) {
        if (copy[i] != reactor[i]) {
            return true; // We found the array to be different, so we can it did successfully fluctuate
        }
    }

    return false;
}

bool testActivate(const array<list<string>, 3>& reactor) {
    array<list<string>, 3> copy = reactor;

    activateElement(reactor, "CORE");

    for (int i = 0; i < 3; i++) {
        if (copy[i].size() != reactor[i].size() + 1) {
            return false; // Did not only add 1 element!
        }
    }

    return true;
}

bool testDeactive(const array<list<string>, 3>& reactor) {
    array<list<string>, 3> copy = reactor;

    deactivateElement(reactor);

    for (int i = 0; i < 3; i++) {
        if (copy[i].size() != reactor[i].size() - 1) {
            return false; // Did not only remove 1 element!
        }
    }

    return true;
}

bool testMeltdown(const array<list<string>, 3>& reactor) {
    array<list<string>, 3> copy = reactor;

    surge(copy);

    if (copy[0] != reactor[0]) {
        // Fluctuate should not affect the elements!
        return false;
    }

    for (int i = 1; i < 3; i++) {
        if (copy[i] != reactor[i]) {
            return true; // We found the array to be different, so we can it did successfully fluctuate
        }
    }

    return false;
}