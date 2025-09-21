/*

suppose 3 rods A B C, and N disks, 
the obj. is to move from A to C all the N
for this B will be helper rod

in each step, 1 disk is moved, from src to des

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

// for animation we can use arrays


class stack {
public: // Make members public to be accessible
    int arr[4];
    int topP;

    // Default constructor for an empty stack
    stack() {
        topP = -1; // Correct initialization for an empty stack
        for (int i = 0; i < 4; i++) {
            arr[i] = 0;
        }
    }

    // Constructor to initialize from an array
    stack(int source_arr[], int length) {
        topP = -1; // Start empty before pushing
        for (int i = 0; i < length; i++) {
            push(source_arr[i]);
        }
    }

    // Corrected push method
    void push(int n) {
        if (topP >= 3) return; // Prevent stack overflow
        topP++;
        arr[topP] = n;
    }

    // Pop method (your logic was correct, but needs an underflow check)
    int pop() {
        if (topP < 0) return 0; // Prevent stack underflow, return 0 or some error
        int ret = arr[topP];
        topP--;
        return ret;
    }

    // Corrected print method
    void print() {
        for (int i = 0; i <= topP; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};


void towerOfHanoiWithArr(
    int N, 
    stack& S, stack& D, stack& H, // For the LOGIC
    stack& A, stack& B, stack& C  // For PRINTING
) {
    if (N == 0) {
        return;
    }

    // Recursive call 1: Pass A, B, C along unchanged for printing
    towerOfHanoiWithArr(N - 1, S, H, D, A, B, C);

    // Perform the move
    D.push(S.pop());

    // *** THE CORRECTED PRINT BLOCK ***
    // Now, we print the original stacks in their fixed order every time.
    std::cout << "A: "; A.print();
    std::cout << "B: "; B.print();
    std::cout << "C: "; C.print();
    std::cout << "--------------------\n";

    // Recursive call 2: Pass A, B, C along unchanged for printing
    towerOfHanoiWithArr(N - 1, H, D, S, A, B, C);
}


// void towerOfHanoi(int N, int src, int des, int help){

//     if (N==0)
//     {
//         return;
//     }
//     // the source is still the source, the helper rod becomes the new src, will the des becomes the temp helper
//     towerOfHanoi(N-1,src,help,des);
//     std::cout << "disk:" <<N<<" from " <<src <<" to "<<des<<std::endl;
//     towerOfHanoi(N-1,help,des,src);

    

// }

void print(int N, int A, int B){
    std::cout << "disk:" <<N<<" from " <<A <<" to "<<B<<std::endl;
}

// void towerOfHanoi(int N, int A, int B, int C){

//     if (N==0)
//     {
//         return;
//     }
//     towerOfHanoi(N-1,A,C,B);
//     print(N,A,B);
//     towerOfHanoi(N-1,C,B,A);

// }

void towerOfHanoi(int N, int src, int des){

    int help =  6-(src+des); // 6=help+src+des

    if (N==0)
    {
        return;
    }
    // before moving the N disks to des, move N-1 disks to help
    towerOfHanoi(N-1,src,help);
    // after doing that display the movement of the Nth disk
    print(N,src,des);
    // now move the remaining N-1 disks from help to des
    towerOfHanoi(N-1,help,des);

    

}

int main(){

    
    
    //            src des help
    //             V   V   V
    towerOfHanoi(3,1 , 2   );
    

    // for visuals

    // int arr[3]={3,2,1};
    
    // stack A(arr,3);
    // stack B;
    // stack C;

    // A.print();
    // B.print();
    // C.print();
    
    // towerOfHanoiWithArr(3,A,B,C,A,B,C);


    return 0;
}