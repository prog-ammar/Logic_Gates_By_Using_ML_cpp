#include<iostream>
#include<math.h>

using namespace std;

//Change train_xor it can generate every gate 
//Train Xor on nand or output

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


float cost_func(float w1,float w2,float b)
{
    float result=0.0f;
    for(int i=0;i<size_train;i++)
    {
        float x1=train_xor[i][0];
        float x2=train_xor[i][1];
        float y=x1*w1+x2*w2+b;

        float distance=train_xor[i][2]-sigmoid(y);
        result+=distance*distance;
    }
    return result/float(size_train);
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


Weights training_and(float w1,float w2,float b,int train[][3],Weights or1,Weights nand)
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
        float nand_output=sigmoid(nand.w1*train_xor[j][0]+nand.w2*train_xor[j][1]+nand.b);
        float or_output=sigmoid(or1.w1*train_xor[j][0]+or1.w2*train_xor[j][1]+or1.b);
        int expected_output=train_xor[j][2];
        float y=w1*or_output+w2*nand_output+b;
        dw1+=-2.0f*or_output*(expected_output-sigmoid(y));
        dw2+=-2.0f*nand_output*(expected_output-sigmoid(y));
        db+=-2.0f*(expected_output-sigmoid(y));
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

int main()
{
   srand(time(0));
   float w1=rand_gen();
   float w2=rand_gen();
   float b=rand_gen();

   Weights or1=training(w1,w2,b,train_or);
   Weights nand=training(w1,w2,b,train_nand);
   Weights and1=training_and(w1,w2,b,train_and,or1,nand);

   cout<<"\nResults : "<<endl;
   
    for(int i=0;i<size_train;i++)
    {
        float nand_output=sigmoid(nand.w1*train_xor[i][0]+nand.w2*train_xor[i][1]+nand.b);
        float or_output=sigmoid(or1.w1*train_xor[i][0]+or1.w2*train_xor[i][1]+or1.b);
        cout<<"Expected : "<<train_xor[i][2]<<" | Actual : "<<sigmoid(and1.w1*or_output+and1.w2*nand_output+and1.b)<<endl;
    }

}