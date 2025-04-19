class Matrix
{
    private:
    float** m;
    int rows;
    int cols;

    public:
    Matrix(int rows,int cols);
    void init_rand();
    void set_fill(int n);
    friend ostream& operator<<(ostream& output,const Matrix& matrix);
    friend Matrix operator+(const Matrix& m1,const Matrix& m2);
    friend Matrix operator*(const Matrix& m1,const Matrix& m2);
};