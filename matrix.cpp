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


ostream& operator<<(ostream& output,const Matrix& matrix)
{
    output<<fixed;
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

Matrix::~Matrix()
{
    if (m != nullptr)
    {
        for (int i = 0; i < rows; ++i)
            delete[] m[i];
        delete[] m;
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
    dw=new Matrix [layers-1];
    db=new Matrix [layers-1];
    da=new  Matrix [layers-1];

    for(int i=0;i<layers;i++)
    {
        a[i]= Matrix(1,sizes[i]);
    }

    for(int i=0;i<layers-1;i++)
    {
        w[i]=Matrix(sizes[i],sizes[i+1]);
        b[i]=Matrix(1,size[i+1]);
        dw[i]=Matrix(sizes[i],sizes[i+1]);
        db[i]=Matrix(1,sizes[i+1]);
        da[i]=Matrix(1,sizes[i+1]);
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



void Weights::init_rand(int l,int h)
{
   for(int i=0;i<layers-1;i++)
    {
        w[i]=Matrix(sizes[i],sizes[i+1]);
        w[i].init_rand(l,h);
        b[i]=Matrix(1,sizes[i+1]);
        b[i].init_rand(l,h);
    }
}

void Weights::set_fill(int x)
{
    for(int i=0;i<layers-1;i++)
    {
        w[i].set_fill(x);
        b[i].set_fill(x);
        a[i+1].set_fill(x);
    }

}



Weights::~Weights()
{
    delete []a;
    delete []b;
    delete []w;
    delete []db;
    delete []dw;
    delete []da;
    delete []sizes;
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
    xr->init_rand(0,1);
    *this->input=input;
    *this->output=output;
    
}




void NeuralNetwork::forward_xr()
{
    for(int i=0;i<layers-1;i++)
    {
        xr->a[i+1]=xr->a[i]*xr->w[i];
        xr->a[i+1]=xr->a[i+1]+xr->b[i];
        xr->a[i+1].sigmoid();
    }

    // xr->a[2]=xr->a[1]*xr->w[1];
    // xr->a[2]=xr->a[2]+xr->b[1];
    // xr->a[2].sigmoid();
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
            float d=xr->a[layers-1].matrix_at(0,j)-y.matrix_at(0,j);
            cost+=d*d;
        }
    }
    return cost/input->get_rows();
}



void NeuralNetwork::train()
{
    float learn_rate=1e-1;
    int eps=1000;
    for(int i=0;i<10000;i++)
    {
        for(int j=0;j<layers-1;j++)
        {
            xr->da[j].set_fill(0);
            xr->db[j].set_fill(0);
            xr->dw[j].set_fill(0);
        }

        for(int l=0;l<input->get_rows();l++)
        {
            Matrix x=input->get_row(l);
            Matrix y=output->get_row(l);

            xr->a[0]=x;
            forward_xr();

            xr->da[layers-2].matrix_at(0,0)=2.0f * (xr->a[layers-1].matrix_at(0, 0) - y.matrix_at(0, 0));
   
            for(int layer=layers-2;layer>=0;layer--)
            {
                Matrix prev_transpose=return_transpose(xr->a[layer]);
                Matrix prev_w_sample = prev_transpose * xr->da[layer];
                Matrix prev_b_sample = xr->da[layer];

                xr->dw[layer]=xr->dw[layer]+prev_w_sample;
                xr->db[layer]=xr->db[layer]+prev_b_sample;

                if(layer>0)
                {
                  Matrix w_transpose=return_transpose(xr->w[layer]);
                  Matrix da_prev = xr->da[layer] * w_transpose;

                  for(int j=0;j<xr->a[layer].get_cols();j++)
                  {
                    double sigmoid_deriv=xr->a[layer].matrix_at(0,j)*(1.0f - xr->a[layer].matrix_at(0,j));
                    xr->da[layer-1].matrix_at(0,j) = da_prev.matrix_at(0,j)*sigmoid_deriv;
                   }
                }
            }

        int num_samples = input->get_rows();
        for(int l=0;l<layers-1;l++)
        {   
            for(int k = 0; k < xr->dw[l].get_rows(); k++) 
            {
            for(int j = 0; j < xr->dw[l].get_cols(); j++) 
            {
                xr->dw[l].matrix_at(k,j) /= num_samples;
            }
        }
        }
        
        
        for(int l=0;l<layers-1;l++)
        {
          for(int k = 0; k < xr->db[l].get_rows(); k++)
          {
            for(int j=0; j<xr->db[l].get_cols();j++)
            {
               xr->db[l].matrix_at(k,j)/= num_samples;
            }
          }
        } 
        
       
        
        // Update weights and biases using gradient descent
        // w = w - learning_rate * dw
        // b = b - learning_rate * db
        

        for(int l=0;l<layers-1;l++)
        {
          for(int k = 0; k < xr->b[l].get_rows(); k++)
          {
            for(int j=0; j<xr->b[l].get_cols();j++)
            {
               xr->b[l].matrix_at(k,j) -= learn_rate * xr->db[l].matrix_at(k,j);
            }
          }
        } 

        for(int l=0;l<layers-1;l++)
        {
          for(int k = 0; k < xr->w[l].get_rows(); k++)
          {
            for(int j=0; j<xr->w[l].get_cols();j++)
            {
               xr->w[l].matrix_at(k,j) -= learn_rate * xr->dw[l].matrix_at(k,j);
            }
          }
        } 
        
    }
    }
}


Matrix NeuralNetwork::get_output()
{
   Matrix result(output->get_rows(),output->get_cols());
   for(int i=0;i<input->get_rows();i++)
   {
    Matrix input_row=input->get_row(i);
    xr->a[0]=input_row;
    forward_xr();
    result.matrix_at(i,0)=xr->a[layers-1].matrix_at(0,0);
   }
   return result;
}

NeuralNetwork::~NeuralNetwork()
{
    delete input;
    delete output;
    delete xr;
    delete[] sizes;
}



