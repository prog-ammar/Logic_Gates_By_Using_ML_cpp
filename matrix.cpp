#include "matrix.h"

using namespace std;



Matrix::Matrix(int rows,int cols)
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
        for(int j=0;i<cols;j++)
        {
            m[i][j]=n;
        }
    }
}


ostream& operator<<(ostream& output,Matrix matrix)
{
    for(int i=0;i<matrix.rows;i++)
    {
        for(int j=0;j<matrix.cols;j++)
        {
             output<<matrix.m[i][j]<<" ";
        }
        output<<"\n";
    }
    output<<"\n";
    return output;
}