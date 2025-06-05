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

double& Matrix::matrix_at(int i,int j)
{
    return m[i][j];
}

Matrix return_transpose(Matrix& x)
{
    Matrix temp(x.cols,x.rows);
    for(int i=0;i<temp.rows;i++)
    {
        for(int j=0;j<temp.cols;j++)
        {
            temp.m[i][j]=x.m[j][i];
        }
    }
    return temp;
}

void NeuralNetwork::forward_xr()
{
    xr->a[1]=xr->a[0]*xr->w[0];
    xr->a[1]=xr->a[1]+xr->b[0];
    xr->a[1].sigmoid();

    xr->a[2]=xr->a[1]*xr->w[1];
    xr->a[2]=xr->a[2]+xr->b[1];
    xr->a[2].sigmoid();
}

NeuralNetwork::NeuralNetwork(int layers,int size[],int l,Matrix input,Matrix output)
{
    this->sizes=new int[l];
    for(int i=0;i<l;i++)
    {
        this->sizes[i]=size[i];
    }
    this->layers=layers;
    this->input=new Matrix;
    this->output=new Matrix;
    this->xr=new Weights(layers,size,l);
    *this->input=input;
    *this->output=output;
    
}

void NeuralNetwork::train()
{
    float learn_rate=1e-1;
    int eps=1000;
    for(int i=0;i<10000;i++)
    {
        Matrix dw[2];
        Matrix db[2];
        Matrix da[2];

        dw[0] = Matrix(2, 2);
        dw[1] = Matrix(2, 1);
        db[0] = Matrix(1, 2);
        db[1] = Matrix(1, 1);
        da[0] = Matrix(1,2);
        da[1] = Matrix(1,1);
        
        dw[0].set_fill(0);
        dw[1].set_fill(0);
        db[0].set_fill(0);
        db[1].set_fill(0);
        da[0].set_fill(0);
        da[1].set_fill(1);

        for(int i=0;i<input->get_rows();i++)
        {
            Matrix x=input->get_row(i);
            Matrix y=output->get_row(i);

            xr->a[0]=x;
            forward_xr();
   
            da[1].matrix_at(0,0)=2.0f * (xr->a[2].matrix_at(0, 0) - y.matrix_at(0, 0));

            Matrix a1_transpose=return_transpose(xr->a[1]);
            Matrix dw1_sample = a1_transpose * da[1];
            Matrix db1_sample = da[1];

            Matrix w1_transpose=return_transpose(xr->w[1]);
            Matrix da1_pre = da[1] * w1_transpose;

            for(int j=0;j<2;j++)
            {
                float sigmoid_value=xr->a[1].matrix_at(0,j);
                float sigmoid_deriv= sigmoid_value*(1.0f-sigmoid_value);
                da[0].matrix_at(0,j)=da1_pre.matrix_at(0,j)*sigmoid_deriv;
            }

            Matrix a0_transpose=return_transpose(xr->a[0]);
            Matrix dw0_sample = a0_transpose * da[0];
            Matrix db0_sample = da[0];


            dw[1] = dw[1] + dw1_sample;
            db[1] = db[1] + db1_sample;
            dw[0] = dw[0] + dw0_sample;
            db[0] = db[0] + db0_sample;


        int num_samples = input->get_rows();
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                if(i < dw[0].get_rows() && j < dw[0].get_cols()) {
                    dw[0].matrix_at(i,j) /= num_samples;
                }
            }
        }
        
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 1; j++) {
                if(i < dw[1].get_rows() && j < dw[1].get_cols()) {
                    dw[1].matrix_at(i,j) /= num_samples;
                }
            }
        }
        
        for(int i = 0; i < 1; i++) {
            for(int j = 0; j < 2; j++) {
                if(i < db[0].get_rows() && j < db[0].get_cols()) {
                    db[0].matrix_at(i,j)/= num_samples;
                }
            }
        }
        
        for(int i = 0; i < 1; i++) {
            for(int j = 0; j < 1; j++) {
                if(i < db[1].get_rows() && j < db[1].get_cols()) {
                    db[1].matrix_at(i,j) /= num_samples;
                }
            }
        }
        
        // Update weights and biases using gradient descent
        // w = w - learning_rate * dw
        // b = b - learning_rate * db
        
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                xr->w[0].matrix_at(i,j) -= learn_rate * dw[0].matrix_at(i,j);
            }
        }
        
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 1; j++) {
                xr->w[1].matrix_at(i,j) -= learn_rate * dw[1].matrix_at(i,j);
            }
        }
        
        for(int i = 0; i < 1; i++) {
            for(int j = 0; j < 2; j++) {
                xr->b[0].matrix_at(i,j) -= learn_rate * db[0].matrix_at(i,j);
            }
        }
        
        for(int i = 0; i < 1; i++) {
            for(int j = 0; j < 1; j++) {
                xr->b[1].matrix_at(i,j) -= learn_rate * db[1].matrix_at(i,j);
            }
        }
        }
    }
}


Weights::Weights(int layers,int size[],int l)
{
    this->layers=layers;
    this->sizes=new int[l];
    for(int i=0;i<l;i++)
    {
        this->sizes[i]=size[i];
    }

    a=new Matrix[layers];
    w=new Matrix[layers-1];
    b=new Matrix[layers-1];

    for(int i=0;i<layers;i++)
    {
        a[i]= Matrix(1,sizes[i]);
    }

    for(int i=0;i<layers-1;i++)
    {
        w[i]=Matrix(sizes[i],sizes[i+1]);
        w[i].init_rand(0,1);
        b[i]=Matrix(1,sizes[i+1]);
        b[i].init_rand(0,1);
    }

    // a[0]=Matrix(1,2);
    // w[0]=Matrix(2,2);
    // w[1]=Matrix(2,1);
    // b[0]=Matrix(1,2);
    // b[1]=Matrix(1,1);
    // a[1]=Matrix(1,2);
    // a[2]=Matrix(1,1);

    // for(int i=0;i<2;i++)
    // {
    //     w[i].init_rand(0,1);
    //     b[i].init_rand(0,1);
    // }
}

Weights::~Weights()
{
    delete []a;
    delete []b;
    delete []w;
    delete []sizes;
}



float NeuralNetwork::cost()
{
    float cost=0;
    for(int i=0;i<input->get_rows();i++)
    {
        Matrix x=input->get_row(i);
        Matrix y=output->get_row(i);

        xr->a[0]=Matrix(x);
        forward_xr();
        for(int j=0;j<output->get_cols();j++)
        {
            float d=xr->a[2].matrix_at(0,j)-y.matrix_at(0,j);
            cost+=d*d;
        }
    }
    return cost/input->get_rows();
}

Matrix NeuralNetwork::get_output()
{
   Matrix result(4,1);
   for(int i=0;i<input->get_rows();i++)
   {
    Matrix input_row=input->get_row(i);
    xr->a[0]=input_row;
    forward_xr();
    result.matrix_at(i,0)=xr->a[2].matrix_at(0,0);
   }
   return result;
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
