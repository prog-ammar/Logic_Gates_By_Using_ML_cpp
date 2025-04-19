class Matrix
{
    private:
    double** m;
    int rows;
    int cols;

    public:
    Matrix(int rows,int cols);
    Matrix(int rows,int cols,double* ptr);
    void init_rand(int low,int high);
    void set_fill(int n);
    friend ostream& operator<<(ostream& output,const Matrix& matrix);
    friend Matrix operator+(const Matrix& m1,const Matrix& m2);
    friend Matrix operator*(const Matrix& m1,const Matrix& m2);
};