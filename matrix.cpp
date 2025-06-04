#include<iostream>
#include<iomanip>
#include<math.h>

using namespace std;

#include "matrix.h"

Matrix::Matrix(int rows=0,int cols=0)
{
    this->rows=rows;
    this->cols=cols;
    m=new double*[this->rows];
    for(int i=0;i<this->rows;i++)
    {
        m[i]=new double[this->cols];
    }
}

Matrix::Matrix(int rows,int cols,double** ptr)
{
    this->rows=rows;
    this->cols=cols;
    m=new double*[this->rows];
    for(int i=0;i<this->rows;i++)
    {
        m[i]=new double[this->cols];
    }
    if(ptr!=nullptr)
    {
        for(int i=0;i<this->rows;i++)
        {
            for(int j=0;j<this->cols;j++)
            {
                m[i][j]=ptr[i][j];
            }
        }
    }
}

void Matrix::init_rand(int low,int high)
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
              m[i][j]=double((float(rand())/RAND_MAX)*(high-low)+low);
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


void Matrix::sigmoid()
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            m[i][j]=1.0f/(1.0f+expf(-m[i][j]));
        }
    }
}


ostream& operator<<(ostream& output,const Matrix& matrix)
{
    for(int i=0;i<matrix.rows;i++)
    {
        output<<"\n[ ";
        for(int j=0;j<matrix.cols;j++)
        {
            output<<matrix.m[i][j]<<" ";
        }
        output<<"]";
    }
    output<<"\n";
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

Matrix operator*(const Matrix& m1,const Matrix& m2)
{
   if(m1.cols==m2.rows)
   {
    Matrix temp(m1.rows,m2.cols);
    temp.set_fill(0);
    for(int i=0;i<temp.rows;i++)
    {
        for(int j=0;j<temp.cols;j++)
        {
            for(int k=0;k<m2.cols;k++)
            {
                temp.m[i][j]+=m1.m[i][k]*m2.m[k][i];
            }
        }
        
    }
    return temp;
   }
   return Matrix();
}
