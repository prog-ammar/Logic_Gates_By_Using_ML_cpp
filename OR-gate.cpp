#include<iostream>
#include<time.h>
#include<math.h>
#include<iomanip>

using namespace std;


int train_or[][3]=
{
    {0,0,0},
    {0,1,1},
    {1,0,1},
    {1,1,1}
};

int size_train=sizeof(train_or)/sizeof(train_or[0]);

float rand_gen()
{
    return float(rand())/float(RAND_MAX);
}

float sigmoid(float x)
{
    return 1.0f / (1.0f + exp(-x));
}

float cost_func(float w1,float w2,float b)
{
    float result=0.0f;
    for(int i=0;i<size_train;i++)
    {
        float x1=train_or[i][0];
        float x2=train_or[i][1];
        float y=x1*w1+x2*w2+b;

        float distance=train_or[i][2]-sigmoid(y);
        result+=distance*distance;
    }
    return result/float(size_train);
}

int main()
{
    srand(time(0));
    float w1=rand_gen();
    float w2=rand_gen();
    float b=rand_gen();

    float learn_rate=1e-1;

    for(int i=0;i<1600000;i++)
    {
       float dw1=0.0f;
       float dw2=0.0f;
       float db=0.0f;
       for(int j=0;j<size_train;j++)
       {
        float y=w1*train_or[j][0]+w2*train_or[j][1]+b;
        float sigmoid_deriv=sigmoid(y)*(1.0f-sigmoid(y));
        dw1+=-2.0f*train_or[j][0]*(train_or[j][2]-sigmoid(y))*sigmoid_deriv;
        dw2+=-2.0f*train_or[j][1]*(train_or[j][2]-sigmoid(y))*sigmoid_deriv;
        db+=-2.0f*(train_or[j][2]-sigmoid(y))*sigmoid_deriv;
       }
       dw1/=size_train;
       dw2/=size_train;
       db/=size_train;

       w1-=learn_rate*dw1;
       w2-=learn_rate*dw2;
       b-=learn_rate*db;
    }
    cout<<"w1 : "<<w1<<"\nw2 : "<<w2<<"\nb : "<<b<<"\ncost : "<<cost_func(w1,w2,b)<<endl;
    
    cout<<"\nResults : "<<endl;
    for(int i=0;i<size_train;i++)
    {
        cout<<"Expected : "<<train_or[i][2]<<" | Actual : "<<fixed<<setprecision(3)<<sigmoid(w1*train_or[i][0]+w2*train_or[i][1]+b)<<endl;
    }

}