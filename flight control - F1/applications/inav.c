#include "include.h"
#include "ano_of.h"
#include "mpu6050.h"

void inav_predict(float dt,float x[2],float acc)
{
    if(dt != 0)
    {
        if(acc<100)
            acc = 0.0f;
        acc = acc/4096*9.8f;
        x[0] += x[1] *dt +acc *dt/2.0f;
        x[1] += acc*dt;
        
    }
}

void inav_correct(float e,float dt,float x[2],int i,float w)
{
    if(dt != 0 && abs(e)>0.01f)
    {
        float ewdt = e*w*dt;
        x[i] += ewdt;
        if( i == 0)
        {
            x[1] += w*ewdt;
        }
    }
}

float x_dis[2]= {0,0};
float err_x;
void inav_calution(float dt)
{
    inav_predict(dt,x_dis,mpu6050.Acc.x);
    err_x = OF_DX2/100.f - x_dis[1];
    
    inav_correct(err_x,dt,x_dis,1,0.8);
    
}


