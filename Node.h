#ifndef MNKSOLVER_NODE_H
#define MNKSOLVER_NODE_H

class Node {
public:
    Node(int* array, int arraySize, int position, int value) {
        this->situation = new int[arraySize]();
        for(int i = 0; i < arraySize; i++)
            this->situation[i] = array[i];
        this->situation[position] = value;
    }
    int* situation;
    ~Node() {
        delete[] situation;
    }
};

#endif //MNKSOLVER_NODE_H
