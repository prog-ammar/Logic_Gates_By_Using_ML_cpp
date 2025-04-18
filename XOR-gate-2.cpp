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


struct Xor
{
    float or_w1;
    float or_w2;
    float or_b;
    float nand_w1;
    float nand_w2;
    float nand_b;
    float and_w1;
    float and_w2;
    float and_b;
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


Xor gen_rand_all()
{
    Xor m;
    m.or_w1=rand_gen();
     m.or_w2=rand_gen();
     m.or_b=rand_gen();
     m.nand_w1=rand_gen();
     m.nand_w2=rand_gen();
     m.nand_b=rand_gen();
     m.and_w1=rand_gen();
     m.and_w2=rand_gen();
     m.and_b=rand_gen();
     return m;
}


float forward(Xor m, float x1, float x2)
{
    float a = sigmoid(m.or_w1*x1 + m.or_w2*x2 + m.or_b);
    float b = sigmoid(m.nand_w1*x1 + m.nand_w2*x2 + m.nand_b);
    return sigmoid(a*m.and_w1 + b*m.and_w2 + m.and_b);
}


Xor training(Xor a)
{
    Xor A;
    float learn_rate=1e-1;

    for(int i=0;i<16000;i++)
    {
       float dw1=0.0f;
       float dw2=0.0f;
       float dw3=0.0f;
       float dw4=0.0f;
       float dw5=0.0f;
       float dw6=0.0f;
       float db1=0.0f;
       float db2=0.0f;
       float db3=0.0f;
       for(int j=0;j<size_train;j++)
       {
        float y=a.or_w1*train_or[j][0]+a.or_w2*train_or[j][1]+a.or_b;
        dw1+=-2.0f*train_or[j][0]*(train_or[j][2]-sigmoid(y));
        dw2+=-2.0f*train_or[j][1]*(train_or[j][2]-sigmoid(y));
        db1+=-2.0f*(train_or[j][2]-sigmoid(y));

        y=a.nand_w1*train_nand[j][0]+a.nand_w2*train_nand[j][1]+a.nand_b;
        dw3+=-2.0f*train_nand[j][0]*(train_nand[j][2]-sigmoid(y));
        dw4+=-2.0f*train_nand[j][1]*(train_nand[j][2]-sigmoid(y));
        db2+=-2.0f*(train_nand[j][2]-sigmoid(y));

        y=a.and_w1*train_and[j][0]+a.and_w2*train_and[j][1]+a.and_b;
        dw5+=-2.0f*train_and[j][0]*(train_and[j][2]-sigmoid(y));
        dw6+=-2.0f*train_and[j][1]*(train_and[j][2]-sigmoid(y));
        db3+=-2.0f*(train_and[j][2]-sigmoid(y));
       }
       dw1/=size_train;
       dw2/=size_train;
       db1/=size_train;

       dw3/=size_train;
       dw4/=size_train;
       db2/=size_train;

       dw5/=size_train;
       dw6/=size_train;
       db3/=size_train;

       a.or_w1-=learn_rate*dw1;
       a.or_w2-=learn_rate*dw2;
       a.or_b-=learn_rate*db1;

       a.nand_w1-=learn_rate*dw3;
       a.nand_w2-=learn_rate*dw4;
       a.nand_b-=learn_rate*db2;

       a.and_w1-=learn_rate*dw5;
       a.and_w2-=learn_rate*dw6;
       a.and_b-=learn_rate*db3;
    }
    return a;
}

int main()
{
    srand(time(0));
    Xor xor_1=gen_rand_all();
    Xor ans=training(xor_1);

    printf("------------------------------\n");
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            printf("%zu ^ %zu = %f\n", i, j, forward(ans,i,j));
        }
    }
    printf("------------------------------\n");
    printf("\"OR\" neuron:\n");
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            printf("%zu | %zu = %f\n", i, j, sigmoid(ans.or_w1*i + ans.or_w2*j + ans.or_b));
        }
    }
    printf("------------------------------\n");
    printf("\"NAND\" neuron:\n");
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            printf("~(%zu & %zu) = %f\n", i, j, sigmoid(ans.nand_w1*i + ans.nand_w2*j + ans.nand_b));
        }
    }
    printf("------------------------------\n");
    printf("\"AND\" neuron:\n");
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            printf("%zu & %zu = %f\n", i, j, sigmoid(ans.and_w1*i + ans.and_w2*j + ans.and_b));
        }
    }
    return 0;
    
}