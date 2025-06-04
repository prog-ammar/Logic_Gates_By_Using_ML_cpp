#include<iostream>
#include "matrix.cpp"

using namespace std;

int main()
{
  Matrix w1(2,2);
  Matrix b1(1,2);
  Matrix w2(2,1);
  Matrix b2(1,1);

  w1.init_rand(0,1);
  w2.init_rand(0,1);
  b1.init_rand(0,1);
  b2.init_rand(0,1);

  w1.sigmoid();
  w2.sigmoid();
  b1.sigmoid();
  b2.sigmoid();

  cout<<w1;
  cout<<b1;
  cout<<w2;
  cout<<b2;
}