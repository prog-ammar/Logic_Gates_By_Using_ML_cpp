#include<iostream>
#include "matrix.cpp"

using namespace std;

int main()
{
  double input[]={0,0,0,1,1,0,1,1};
  double output[]={1,0,0,1};
  int size[]={2,2,1};
  NeuralNetwork nn(3,size,3,Matrix(4,2,input),Matrix(4,1,output));
  nn.train();
  Matrix s=nn.get_output();
  cout<<"\nResult : ";
  cout<<s;
}