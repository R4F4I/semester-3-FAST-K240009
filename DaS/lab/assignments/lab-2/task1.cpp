/*

Task#1
You are tasked with implementing a dynamic matrix class in C++ that supports the following
operations: Dynamic Matrix Creation: Create a dynamic 2D array (matrix) with rows and columns
specified by the user. Matrix Resizing: Implement a method to resize the matrix. The new size
should be provided as input (new rows and columns). If the new size is larger, initialize the new
elements with a given value. If the new size is smaller, truncate the matrix. Matrix Transposition:
Implement a method to transpose the matrix (rows become columns and vice versa). Matrix

Lab Manual 02

Printing: Implement a method to print the matrix. After add 2 to each odd index then print the
array. Memory Deallocation: Ensure proper memory management, including deallocation of the
dynamic matrix when no longer needed.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>
#include <iomanip>

using namespace std;

// matrices are of type float
class Matrix{
    
public:
int row, col;
float **matrix;

    Matrix(int row, int col){
        // creating a matrix...
        matrix = new float *[row]; // declare a list of pointers, with size row
        for (size_t i = 0; i < row; i++){
            matrix[i] = new float[col];
            for (size_t j = 0; j < col; j++)
            {
                matrix[i][j] = 0;
            }
        }
        
        
        this->row = row;
        this->col = col;
    }

// Matrix Resizing
void resize(int newRow, int newCol, float initialValue = 0.0) { // init value added incase the matrix needs to be expanded
    
    float **newMatrix = new float* [newRow];
    
    for (int i = 0; i < newRow; ++i) {
    
        newMatrix[i] = new float[newCol];
    
        // copy the old matrix's values into the new one
        for (int j = 0; j < newCol; ++j) {
    
            if (i < row && j < col) {
                newMatrix[i][j] = matrix[i][j];
    
            } else {
                newMatrix[i][j] = initialValue;
            }
        }
    }

    // Deallocate old matrix
    for (int i = 0; i < row; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    // reassign to the class attribute as newMatrix is in heap
    matrix = newMatrix;
    row = newRow;
    col = newCol;
}

// Matrix Transposition
void transpose() {

    float **transposedMatrix = new float *[col];
    
    for (int i = 0; i < col; ++i) {
        transposedMatrix[i] = new float[row];
        
        for (int j = 0; j < row; ++j) {
            transposedMatrix[i][j] = matrix[j][i];
        }
    }

    // Deallocate old matrix
    for (int i = 0; i < row; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    matrix = transposedMatrix;

    // Swap row and col
    int temp = row;
    row = col;
    col = temp;
}

// Matrix Printing
void printMatrix() {

    for (int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j){
            std::cout <<std::setw(3)<< matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

};


int main(){

    // adding cout values for debugging ...
    cout << "Matrix created with " << endl;
    Matrix m(3, 3);
    cout << "Matrix created with " << endl;
    cout << "Matrix created with " << m.row << " rows and " << m.col << " columns." << endl;

    

    m.printMatrix();
    // Initialize matrix with some values
    int count = 1;
    for (int i = 0; i < m.row; ++i) {
        for (int j = 0; j < m.col; ++j) {
            m.matrix[i][j] = count++;
        }
    }



    cout << "Original Matrix:" << endl;
    m.printMatrix();

    // Add 2 to odd indices
    for (int i = 0; i < m.row; ++i) {
        for (int j = 0; j < m.col; ++j) {
            if ((i * m.col + j) % 2 != 0) { // Check if the linear index is odd
                m.matrix[i][j] += 2;
            }
        }
    }
    cout << "Matrix after adding 2 to odd indices:" << endl;
    m.printMatrix();

    m.resize(4, 5, 100.0);
    cout << "resizing to 4x5:" << endl;
    m.printMatrix();

    m.transpose();
    cout << "mat transpose:" << endl;
    m.printMatrix();
    




    return 0;
}
