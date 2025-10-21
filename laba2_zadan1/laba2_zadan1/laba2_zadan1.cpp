#include <iostream>
#include <iomanip>
#include <algorithm>
#include <locale>

using namespace std;

const int ROWS = 9;
const int COLS = 2;
const int SIZE = ROWS * COLS;

class Vector {
private:
    int* data;
    int size;
public:
    Vector(int size) : size(size) {
        data = new int[size];
        init();
    }

    ~Vector() {
        delete[] data;
    }

    void init() {
        for (int i = 0; i < size; i++) {
            data[i] = i * i + 1;
            if (i % 2 != 0) {
                data[i] *= -1;
            }
        }
    }

    int& operator[](int index) {
        return data[index];
    }

    const int& operator[](int index) const {
        return data[index];
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            cout << setw(5) << data[i];
        }
        cout << endl;
    }

    Vector& operator++() {
        for (int i = 0; i < size; i++) {
            ++data[i];
        }
        return *this;
    }

    Vector operator++(int) {
        Vector temp = *this;
        ++(*this);
        return temp;
    }

    Vector& operator--() {
        for (int i = 0; i < size; i++) {
            --data[i];
        }
        return *this;
    }

    Vector operator--(int) {
        Vector temp = *this;
        --(*this);
        return temp;
    }
};

class Matrix {
private:
    int** data;
    int rows, cols;
public:
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data = new int* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    int at(int i, int j) const {
        return data[i][j];
    }

    void setAt(int i, int j, int val) {
        data[i][j] = val;
    }

    void fromVector(const Vector& vec) {
        int index = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                setAt(i, j, vec[index++]);
            }
        }
    }

    void sort() {
        int temp[SIZE];
        int index = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                temp[index++] = data[i][j];
            }
        }

        std::sort(temp, temp + SIZE, greater<int>());

        index = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = temp[index++];
            }
        }
    }

    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << setw(5) << data[i][j];
            }
            cout << endl;
        }
    }
};

int main() {

    setlocale(LC_ALL, "Russian");

    Vector vec(SIZE);
    cout << "Изначальный одномерный массив:" << endl;
    vec.print();

    Matrix mat(ROWS, COLS);
    mat.fromVector(vec);

    mat.sort();
    cout << "Отсортированный двумерный массив (9x2):" << endl;
    mat.print();

    return 0;
}