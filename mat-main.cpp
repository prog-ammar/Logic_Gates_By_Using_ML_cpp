#include<iostream>
#include "matrix.cpp"

using namespace std;

int main()
{
  // double input[]={0,0,0,1,1,0,1,1};
  // double output[]={0,1,1,0};
  // int size[]={2,2,1};
  // int s=sizeof(size)/sizeof(size[0]);
  // NeuralNetwork nn(3,size,s,Matrix(4,2,input),Matrix(4,1,output));
  // nn.train();
  // Matrix y=nn.get_output();
  // cout<<"\nResult : ";
  // cout<<y;

   double input[] = {
        0, 0, 0, 0,
        0, 0, 1, 0, 
        0, 1, 0, 1 ,
        0, 1, 1, 1,
        1, 0, 0, 0,
        1, 0, 1, 1,
        1, 1, 0, 1,
        1, 1, 0, 1
    };

    double output[] = {
        0,0,   0,
        1,0,   0, 
        1,1,   0, 
        0,0,   1, 
        1,0,   0,
        0,0,   1,
        0,0,   1,
        0,0,   1,
    };

    // Define layer sizes: 3 inputs → 4 hidden → 1 output
    int size[] = {4, 4, 3};
    int s = sizeof(size) / sizeof(size[0]);

    // Create network
    NeuralNetwork nn(3, size, s, Matrix(8, 4, input), Matrix(8, 3, output));
    
    // Train network
    nn.train();
    
    // Display output
    Matrix y = nn.get_output();
    std::cout << "\nResult : \n\nSum:\t\tCarry:";
    std::cout << y;
}