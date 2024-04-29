// Copyright 2024 NNTU-CS
#include "train.h"

Train::Train() {
    countOp = 0;
    first = nullptr;
    Cage{ false, nullptr, nullptr };
}

void Train::addCage(bool a) {
    if (!first) {
        first = new Cage;
        first->light = a;
        first->prev = first;
        first->next = first;
    } else {
        Cage* dnext = first;
        while (dnext->next != first)
            dnext = dnext->next;
        Cage* temp = new Cage;
        temp->light = a;
        temp->prev = dnext;
        temp->next = first;
        dnext->next = temp;
        first->prev = temp;
    }
}

int Train::getOpCount() {
    return countOp;
}

int Train::getLength() {
    int count1 = 0;
    int count2 = 0;
    Cage* rep = first;
    if (rep->light == false) {
        rep->light = true;
        rep = rep->next;
        count1++;
        while (true) {
            while (rep->light != true) {
                count1++;
                rep = rep->next;
            }
            rep = rep->prev;
            count2++;
            while (rep->light != true) {
                count2++;
                rep = rep->prev;
            }
            if (count2 == count1) {
                countOp = count1 * 2;
                return count1;
            }
        }
    } else {
        int count = 0;
        int result = 0;
        bool final = true;
        Cage* current = first;
        do {
            current = current->next;
            count++;
            result++;
            if (current->light) {
                current->light = false;
                for (int i = count; i > 0; i--) {
                    current = current->prev;
                    result++;
                }
                if (!current->light) {
                    countOp = result;
                    return count;
                } else {
                    count = 0;
                }
            } else {
                continue;
            }
        } while (final);
    }
    return 0;
}
