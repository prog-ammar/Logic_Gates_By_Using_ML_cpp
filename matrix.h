#include <iostream>

using namespace std;


class Matrix
{
    private:
    double** m;
    int rows;
    int cols;

    public:
    Matrix();
    Matrix(int rows,int cols);
    Matrix(const Matrix& other);
    Matrix(int rows,int cols,double p[]);
    void init_rand(int low,int high);
    void set_fill(int n);
    int get_rows() const;
    int get_cols() const;
    Matrix get_row(int i);
    void sigmoid();
    double& matrix_at(int i,int j);
    friend Matrix return_transpose(Matrix& x);
    friend ostream& operator<<(ostream& output,const Matrix& matrix);
    friend Matrix operator+(const Matrix& m1,const Matrix& m2);
    friend Matrix operator*(const Matrix& m1,const Matrix& m2);
    Matrix& operator=(const Matrix& other);
    ~Matrix();
};

class Weights
{
    public:
    Matrix* a;
    Matrix* w;
    Matrix* b;
    Matrix* da;
    Matrix* db;
    Matrix* dw;
    int layers;
    int* sizes;
    Weights(int layers,int size[],int l);
    void init_rand(int l,int h);
    void set_fill(int x);
    ~Weights();
};

class NeuralNetwork
{
    private:
    int layers;
    Matrix* input;
    Matrix* output;
    Weights* xr;
    int* sizes;

    public:
    NeuralNetwork(int layers,int size[],int l,Matrix input,Matrix output);
    float cost();
    void forward_xr();
    void train();
    Matrix get_output();
    ~NeuralNetwork();
};