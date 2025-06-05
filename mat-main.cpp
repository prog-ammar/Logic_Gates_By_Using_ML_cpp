#include<iostream>
#include "matrix.cpp"

using namespace std;

int main()
{
  double input[]={0,0,0,1,1,0,1,1};
  double output[]={0,1,1,0};
  Xor xr;
  NeuralNetwork nn(2,Matrix(4,2,input),Matrix(4,1,output));
  nn.train(xr);
  Matrix s=nn.get_output(xr);
  cout<<"\nResult : ";
  cout<<s;
}