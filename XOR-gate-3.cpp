#include<iostream>
#include<math.h>

using namespace std;

//Change train_xor it can generate every gate 

int train_xor[][3]=
{
    {0,0,0},
    {0,1,1},
    {1,0,1},
    {1,1,0}
};

int train_or[][3]=
{
    {0,0,0},
    {0,1,1},
    {1,0,1},
    {1,1,1}
};

int train_nand[][3]=
{
    {0,0,1},
    {0,1,1},
    {1,0,1},
    {1,1,0}
};

int train_and[][3]=
{
    {0,0,0},
    {0,1,0},
    {1,0,0},
    {1,1,1}
};

struct Weights
{
    float w1;
    float w2;
    float b;
};


float rand_gen()
{
    return float(rand())/float(RAND_MAX);
}

int size_train=sizeof(train_xor)/sizeof(train_xor[0]);

float sigmoid(float x)
{
    return 1.0f / (1.0f + exp(-x));
}


Weights training(float w1,float w2,float b,int train[][3])
{
    Weights A;
    float learn_rate=1e-1;

    for(int i=0;i<16000;i++)
    {
       float dw1=0.0f;
       float dw2=0.0f;
       float db=0.0f;
       for(int j=0;j<size_train;j++)
       {
        float y=w1*train[j][0]+w2*train[j][1]+b;
        dw1+=-2.0f*train[j][0]*(train[j][2]-sigmoid(y));
        dw2+=-2.0f*train[j][1]*(train[j][2]-sigmoid(y));
        db+=-2.0f*(train[j][2]-sigmoid(y));
       }
       dw1/=size_train;
       dw2/=size_train;
       db/=size_train;

       w1-=learn_rate*dw1;
       w2-=learn_rate*dw2;
       b-=learn_rate*db;
    }
    A.w1=w1;
    A.w2=w2;
    A.b=b;
    return A;
}

float forward(Weights or1,Weights nand,Weights and1,int x1,int x2)
{
    float nand_output=sigmoid(nand.w1*x1+nand.w2*x2+nand.b);
    float or_output=sigmoid(or1.w1*x1+or1.w2*x2+or1.b);
    return sigmoid(and1.w1*nand_output+and1.w2*or_output+and1.b);
}


int main()
{
   srand(time(0));
   float w1=rand_gen();
   float w2=rand_gen();
   float b=rand_gen();

   Weights or1=training(w1,w2,b,train_or);
   Weights nand=training(w1,w2,b,train_nand);
   Weights and1=training(w1,w2,b,train_and);
   

   cout<<"\nResults : "<<endl;
   
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        cout<<i<<" ^ "<<j<<" : "<<forward(or1,nand,and1,i,j)<<endl;
    }

}