#ifndef MNKSOLVER_VECTOR_H
#define MNKSOLVER_VECTOR_H

template <class T>
class Vector {
public:
    Vector();
    void push_back(T elementToAdd);
    void clear();
    T& operator [] (int idx);
    int size();
    void deleteAt(int index);
    ~Vector();
private:
    T* rawArray;
    int arraySize;
    int sizeBooked;
    void widthArray(T elementToAdd);
};

template<class T>
Vector<T>::Vector() {
    this->rawArray = new T[1]();
    this->arraySize = 0;
    this->sizeBooked = 1;
}

template<class T>
void Vector<T>::push_back(T elementToAdd) {
    this->arraySize++;
    if(this->arraySize <= sizeBooked)
        rawArray[arraySize-1] = elementToAdd;
    else widthArray(elementToAdd);
}

template<class T>
void Vector<T>::widthArray(T elementToAdd) {
    T* newArray = new T[this->sizeBooked*2]();
    for (int i = 0; i < this->sizeBooked; i++)
        newArray[i] = this->rawArray[i];
    newArray[this->sizeBooked] = elementToAdd;
    delete[] this->rawArray;
    this->rawArray = newArray;
    this->sizeBooked *= 2;
}

template<class T>
void Vector<T>::clear() {
    delete[] this->rawArray;
    this->rawArray = new T[1]();
    this->arraySize = 0;
    this->sizeBooked = 1;
}

template<class T>
Vector<T>::~Vector() {
    delete[] this->rawArray;
}

template<class T>
T &Vector<T>::operator[](int idx) {
    return this->rawArray[idx];
}

template<class T>
int Vector<T>::size() {
    return this->arraySize;
}

template<class T>
void Vector<T>::deleteAt(int index) {
    for(int i = index; i < this->arraySize-1; i++)
        rawArray[index] = rawArray[index+1];
    this->arraySize--;
}

#endif //MNKSOLVER_VECTOR_H
