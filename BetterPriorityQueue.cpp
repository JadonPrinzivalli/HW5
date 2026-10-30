// Assistance: ChatGPT
#include "BetterPriorityQueue.h"

bool BetterPriorityQueue::Contains(BPQNode node) const {
    for (size_t i = 0; i < this->c.size(); i++) {
        if (this->c[i] == node) {
            return true;
        }
    }
    return false;
}

bool BetterPriorityQueue::Update(BPQNode node) {
    for (size_t i = 0; i < this->c.size(); i++) {
        if (this->c[i] == node) {
            // Dijkstra only needs improvements, not equal or larger distances.
            if (node.pri >= this->c[i].pri) {
                return false;
            }
            this->c[i].pri = node.pri;

            // A lower priority may need to move toward the root of the min-heap.
            while (i > 0) {
                size_t parent = (i - 1) / 2;
                if (this->c[parent].pri <= this->c[i].pri) {
                    break;
                }
                BPQNode temp = this->c[parent];
                this->c[parent] = this->c[i];
                this->c[i] = temp;
                i = parent;
            }
            return true;
        }
    }
    return false;
}

string BetterPriorityQueue::BPQNodeToString(BPQNode node) {
    return "(" + to_string(node.gnode) + ", pri: " + to_string(node.pri) + ")";
}

string BetterPriorityQueue::ToString() const {
    string result = "[";
    for (size_t i = 0; i < this->c.size(); i++) {
        if (i != 0) {
            result += ", ";
        }
        result += BPQNodeToString(this->c[i]);
    }
    return result + "]";
}
