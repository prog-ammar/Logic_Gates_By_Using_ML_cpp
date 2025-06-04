#include<iostream>
#include<iomanip>
#include<math.h>

using namespace std;

#include "matrix.h"

Matrix::Matrix(int rows,int cols)
{
    this->rows=rows;
    this->cols=cols;
    m=new double*[this->rows];
    for(int i=0;i<this->rows;i++)
    {
        m[i]=new double[this->cols];
    }
}

Matrix::Matrix()
{
    rows=cols=0;
    m=nullptr;
}

Matrix::Matrix(int rows,int cols,double p[])
{
    this->rows=rows;
    this->cols=cols;
    m=new double*[this->rows];
    for(int i=0;i<this->rows;i++)
    {
        m[i]=new double[this->cols];
    }

    int l=0;
    for(int i=0;i<this->rows;i++)
    {
        for(int j=0;j<this->cols;j++)
        {
            m[i][j]=p[l++];
        }
    }
}

Matrix::Matrix(const Matrix& other)
{
    this->rows=other.rows;
    this->cols=other.cols;
    m=new double*[this->rows];
    for(int i=0;i<this->rows;i++)
    {
        m[i]=new double[this->cols];
    }
    for(int i=0;i<this->rows;i++)
    {
        for(int j=0;j<this->cols;j++)
        {
            m[i][j]=other.m[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if(this==&other)
    {
       return *this;
    }
    
    if(m!=nullptr)
    {
         for (int i = 0; i < rows; ++i) 
         {
            delete[] m[i];
         }
        delete[] m;
    }
    rows=other.rows;
    cols=other.cols;
    m = new double*[rows];
    for (int i = 0; i < rows; ++i) 
     {
     m[i] = new double[cols];
     for (int j = 0; j < cols; ++j)
     {
         m[i][j] = other.m[i][j];
     }
     }
    return *this;
    
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

int Matrix::get_cols() const
{
    return cols;
}

int Matrix::get_rows() const
{
    return rows;
}

Matrix Matrix::get_row(int i)
{
   int n=cols;
   double p[n];
   int l=0;
   for(int j=0;j<cols;j++)
   {
    p[l++]=m[i][j];
   }
   return Matrix(1,cols,p);
}

double Matrix::matrix_at(int i,int j)
{
    return m[i][j];
}

NeuralNetwork::NeuralNetwork(int layers,Matrix input,Matrix output)
{
    this->input=new Matrix(input);
    this->output=new Matrix(output);
    this->layers=layers;
}


Xor::Xor()
{
    w[0]=Matrix(2,2);
    w[1]=Matrix(2,1);
    b[0]=Matrix(1,2);
    b[1]=Matrix(1,1);
    a[1]=Matrix(1,2);
    a[2]=Matrix(1,1);

    for(int i=0;i<2;i++)
    {
        w[i].init_rand(0,1);
        b[i].init_rand(0,1);
    }
}

void forward_xor(Xor& xr)
{
    xr.a[1]=xr.w[0]*xr.a[0];
    xr.a[1]=xr.a[1]+xr.b[0];
    xr.a[1].sigmoid();

    xr.a[2]=xr.w[1]*xr.a[1];
    xr.a[2]=xr.a[2]+xr.b[1];
    xr.a[2].sigmoid();
}

float NeuralNetwork::cost(Xor& xr)
{
    float cost=0;
    for(int i=0;i<input->get_rows();i++)
    {
        Matrix x=input->get_row(i);
        Matrix y=output->get_row(i);

        xr.a[0]=Matrix(x);
        forward_xor(xr);
        for(int j=0;j<output->get_cols();j++)
        {
            float d=xr.a[2].matrix_at(0,j)-y.matrix_at(0,j);
            cost+=d*d;
        }
    }
    return cost/input->get_rows();
}

NeuralNetwork::~NeuralNetwork()
{
    delete input;
    delete output;
}

Matrix::~Matrix()
{
    if (m != nullptr)
    {
        for (int i = 0; i < rows; ++i)
            delete[] m[i];
        delete[] m;
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
            for(int k=0;k<m1.cols;k++)
            {
                temp.m[i][j]+=m1.m[i][k]*m2.m[k][j];
            }
        }
        
    }
    return temp;
   }
   return Matrix();
}
