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
    friend ostream& operator<<(ostream& output,Matrix matrix);
}