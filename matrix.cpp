#include "matrix.h"
#include<iostream>

using namespace std;

Matrix::Matrix(int rows=0,int cols=0)
{
    this->rows=rows;
    this->cols=cols;
    m=new float*[this->rows];
    for(int i=0;i<this->rows;i++)
    {
       m[i]=new float[this->cols];
    }
}

void Matrix::init_rand()
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
              m[i][j]=float(rand())/RAND_MAX;
        }
    }
}

void Matrix::set_fill(int n)
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            m[i][j]=n;
        }
    }
}


ostream& operator<<(ostream& output,const Matrix& matrix)
{
    for(int i=0;i<matrix.rows;i++)
    {
        for(int j=0;j<matrix.cols;j++)
        {
             output<<matrix.m[i][j]<<" ";
        }
        output<<"\n";
    }
    return output;
}

Matrix operator+(const Matrix& m1,const Matrix& m2)
{
    if(m1.rows==m2.rows && m1.cols==m2.cols)
    {
        Matrix temp(m1.rows,m2.cols);
        for(int i=0;i<temp.rows;i++)
        {
            for(int j=0;j<temp.cols;j++)
            {
                temp.m[i][j]=m1.m[i][j]+m2.m[i][j];
            }
        }
        return temp;
    }
    return Matrix();
}