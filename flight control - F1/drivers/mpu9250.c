#include "mpu9250.h"
#include "i2c_soft.h"
#include "mpu6050.h"
#include "mymath.h"
#include "filter.h"
char		 mpu6500_buffer[14];	

struct _sensor sensor;

MPU6050_STRUCT mpu6500;

//初始化MPU9250
//返回值:0,成功
//    其他,错误代码
u8 MPU9250_Init(void)
{
    u8 res=0;
    I2c_Soft_Init();     //初始化IIC总线
    
//    IIC_ADD_write(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0x80); //Reset ing
//    delay_ms(100); 
//    IIC_ADD_write(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0x80); //Reset ing
//    IIC_ADD_write(MPU9250_ADDR,MPU_GYRO_CFG_REG,3<<3);//设置陀螺仪满量程范围  
//    IIC_ADD_write(MPU9250_ADDR,MPU_ACCEL_CFG_REG,0<<3);//设置加速度传感器满量程范围  
//    //设置采样率200Hz
//	IIC_ADD_write(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,1);	//设置数字低通滤波器
// 	IIC_ADD_write(MPU9250_ADDR,MPU_CFG_REG,1);//设置数字低通滤波器
//    
//    
//    if(res==MPU6500_ID) //器件ID正确
//    {
//        IIC_ADD_write(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X01);  	//设置CLKSEL,PLL X轴为参考
//        IIC_ADD_write(MPU9250_ADDR,MPU_PWR_MGMT2_REG,0X00);  	//加速度与陀螺仪都工作

//    }else return 1;
// 
    

    MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X80);//复位MPU9250
    Delay_ms(100);  //延时100ms
    MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X00);//唤醒MPU9250
    Delay_ms(100);  //延时100ms
    MPU_Write_Byte(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,1);	
    MPU_Write_Byte(MPU9250_ADDR,MPU_CFG_REG,4);//设置数字低通滤波器
    MPU_Set_Gyro_Fsr(1);					        	//陀螺仪传感器,±500dps
    MPU_Set_Accel_Fsr(1);					       	 	//加速度传感器,±4g

    MPU_Write_Byte(MPU9250_ADDR,MPU_INT_EN_REG,0X00);   //关闭所有中断
	  MPU_Write_Byte(MPU9250_ADDR,MPU_USER_CTRL_REG,0X00);//I2C主模式关闭
	  MPU_Write_Byte(MPU9250_ADDR,MPU_FIFO_EN_REG,0X00);	//关闭FIFO
	  MPU_Write_Byte(MPU9250_ADDR,MPU_INTBP_CFG_REG,0X82);//INT引脚低电平有效，开启bypass模式，可以直接读取磁力计
    res=MPU_Read_Byte(MPU9250_ADDR,MPU_DEVICE_ID_REG);  //读取MPU6500的ID
    if(res==MPU6500_ID) //器件ID正确
    {
//        MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X01);  	//设置CLKSEL,PLL X轴为参考
//        MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT2_REG,0X00);  	//加速度与陀螺仪都工作
//		    MPU_Set_Rate(500);						       	//设置采样率为50Hz   
    }else return 1;
 
    res=MPU_Read_Byte(AK8963_ADDR,MAG_WIA);    			//读取AK8963 ID   
    if(res==AK8963_ID)
    {
        MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X11);		//设置AK8963为单次测量模式
    }else return 1;

    
    return 0;
}

//设置MPU9250陀螺仪传感器满量程范围
//fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU9250_ADDR,MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围  
}
//设置MPU9250加速度传感器满量程范围
//fsr:0,±2g;1,±4g;2,±8g;3,±16g
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU9250_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围  
}

//设置MPU9250的数字低通滤波器
//lpf:数字低通滤波频率(Hz)
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU9250_ADDR,MPU_CFG_REG,data);//设置数字低通滤波器  
}

//设置MPU9250的采样率(假定Fs=1KHz)
//rate:4~1000(Hz)
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
 	return MPU_Set_LPF(rate/2);	//自动设置LPF为采样率的一半
}

//得到温度值
//返回值:温度值(扩大了100倍)
short MPU_Get_Temperature(void)
{
    u8 buf[2]; 
    short raw;
	float temp;
	MPU_Read_Len(MPU9250_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=21+((double)raw)/333.87;  
    return temp*100;;
}
//得到陀螺仪值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    u8 buf[6],res; 
	res=MPU_Read_Len(MPU9250_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//得到加速度值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}

//得到磁力计值(原始值)
//mx,my,mz:磁力计x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
u8 MPU_Get_Magnetometer(int16_t *mx,int16_t *my,int16_t *mz)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(AK8963_ADDR,MAG_XOUT_L,6,buf);
	if(res==0)
	{
		*mx=((u16)buf[1]<<8)|buf[0];  
		*my=((u16)buf[3]<<8)|buf[2];  
		*mz=((u16)buf[5]<<8)|buf[4];
	} 	
    MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X11); //AK8963每次读完以后都需要重新设置为单次测量模式
    return res;;
}

//IIC连续写
//addr:器件地址 
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
    u8 i;
    I2c_Soft_Start();
    I2c_Soft_SendByte((addr<<1)|0); //发送器件地址+写命令
    if(I2c_Soft_WaitAsk())          //等待应答
    {
        I2c_Soft_Stop();
        return 1;
    }
    I2c_Soft_SendByte(reg);         //写寄存器地址
    I2c_Soft_WaitAsk();             //等待应答
    for(i=0;i<len;i++)
    {
        I2c_Soft_SendByte(buf[i]);  //发送数据
        if(I2c_Soft_WaitAsk())      //等待ACK
        {
            I2c_Soft_Stop();
            return 1;
        }
    }
    I2c_Soft_Stop();
    return 0;
} 

//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
    I2c_Soft_Start();
    I2c_Soft_SendByte((addr<<1)|0); //发送器件地址+写命令
    if(I2c_Soft_WaitAsk())          //等待应答
    {
        I2c_Soft_Stop();
        return 1;
    }
    I2c_Soft_SendByte(reg);         //写寄存器地址
    I2c_Soft_WaitAsk();             //等待应答
	  I2c_Soft_Start();                
    I2c_Soft_SendByte((addr<<1)|1); //发送器件地址+读命令
    I2c_Soft_WaitAsk();             //等待应答
    while(len)
    {
        if(len==1)
        {
            *buf=I2c_Soft_ReadByte(0);//读数据,发送nACK 
//            IIC_NAck();
        }
        else 
        {
            *buf=I2c_Soft_ReadByte(1);		//读数据,发送ACK  
//            IIC_Ack(); //发送ACK 
        }
        len--;
        buf++;  
    }
    I2c_Soft_Stop();                 //产生一个停止条件
    return 0;       
}

//IIC写一个字节 
//devaddr:器件IIC地址
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Byte(u8 addr,u8 reg,u8 data)
{
    I2c_Soft_Start();
    I2c_Soft_SendByte((addr<<1)|0); //发送器件地址+写命令
    if(I2c_Soft_WaitAsk())          //等待应答
    {
        I2c_Soft_Stop();
        return 1;
    }
    I2c_Soft_SendByte(reg);         //写寄存器地址
    I2c_Soft_WaitAsk();             //等待应答
    I2c_Soft_SendByte(data);        //发送数据
    if(I2c_Soft_WaitAsk())          //等待ACK
    {
        I2c_Soft_Stop();
        return 1;
    }
    I2c_Soft_Stop();
    return 0;
}

//IIC读一个字节 
//reg:寄存器地址 
//返回值:读到的数据
u8 MPU_Read_Byte(u8 addr,u8 reg)
{
    u8 res;
    I2c_Soft_Start();
    I2c_Soft_SendByte((addr<<1)|0); //发送器件地址+写命令
    I2c_Soft_WaitAsk();             //等待应答
    I2c_Soft_SendByte(reg);         //写寄存器地址
    I2c_Soft_WaitAsk();             //等待应答
	  I2c_Soft_Start();                
    I2c_Soft_SendByte((addr<<1)|1); //发送器件地址+读命令
    I2c_Soft_WaitAsk();             //等待应答
    res=I2c_Soft_ReadByte(0);		    //读数据,发送nACK  

    I2c_Soft_Stop();                 //产生一个停止条件
    return res;  
}



//******读取MPU9250数据****************************************
void READ_MPU9250_ACCEL(void)
{ 
    
    mpu6500_buffer[0]=MPU_Read_Byte(MPU9250_ADDR,MPU_ACCEL_XOUTL_REG); 
    mpu6500_buffer[1]=MPU_Read_Byte(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG);
    sensor.acc.origin.x=	((int16_t)mpu6500_buffer[1]<<8)|mpu6500_buffer[0];             //读取计算X轴数据

    mpu6500_buffer[2]=MPU_Read_Byte(MPU9250_ADDR,MPU_ACCEL_YOUTL_REG);
    mpu6500_buffer[3]=MPU_Read_Byte(MPU9250_ADDR,MPU_ACCEL_YOUTH_REG);
    sensor.acc.origin.y =	((int16_t)mpu6500_buffer[3]<<8)|mpu6500_buffer[2];             //读取计算Y轴数据
    
    mpu6500_buffer[4]=MPU_Read_Byte(MPU9250_ADDR,MPU_ACCEL_ZOUTL_REG);
    mpu6500_buffer[5]=MPU_Read_Byte(MPU9250_ADDR,MPU_ACCEL_ZOUTH_REG);
    sensor.acc.origin.z =	((int16_t)mpu6500_buffer[5]<<8)|mpu6500_buffer[4];             //读取计算Z轴数据
    
    

}

void READ_MPU9250_GYRO(void)
{ 
    
    mpu6500_buffer[8]=MPU_Read_Byte(MPU9250_ADDR,MPU_GYRO_XOUTL_REG); 
    mpu6500_buffer[9]=MPU_Read_Byte(MPU9250_ADDR,MPU_GYRO_XOUTH_REG);
    sensor.gyro.origin.x =	((u16)mpu6500_buffer[9]<<8)|mpu6500_buffer[8];

    mpu6500_buffer[10]=MPU_Read_Byte(MPU9250_ADDR,MPU_GYRO_YOUTL_REG);
    mpu6500_buffer[11]=MPU_Read_Byte(MPU9250_ADDR,MPU_GYRO_YOUTH_REG);
    sensor.gyro.origin.y =	((u16)mpu6500_buffer[11]<<8)|mpu6500_buffer[10];

    mpu6500_buffer[12]=MPU_Read_Byte(MPU9250_ADDR,MPU_GYRO_ZOUTL_REG);
    mpu6500_buffer[13]=MPU_Read_Byte(MPU9250_ADDR,MPU_GYRO_ZOUTH_REG);
    sensor.gyro.origin.z =	((u16)mpu6500_buffer[13]<<8)|mpu6500_buffer[12]; 

	
}

void READ_MPU9250_MAG(void)
{ 
    char BUF[6];
    BUF[0]=MPU_Read_Byte (MPU9250_ADDR,MAG_XOUT_L);
    BUF[1]=MPU_Read_Byte (MPU9250_ADDR,MAG_XOUT_H);
    sensor.mag.origin.x =((u16)BUF[1]<<8)|BUF[0];

    BUF[2]=MPU_Read_Byte(MPU9250_ADDR,MAG_YOUT_L);
    BUF[3]=MPU_Read_Byte(MPU9250_ADDR,MAG_YOUT_H);
    sensor.mag.origin.y  =	((u16)BUF[3]<<8)|BUF[2];
                           //读取计算Y轴数据
     
    BUF[4]=MPU_Read_Byte(MPU9250_ADDR,MAG_ZOUT_L);
    BUF[5]=MPU_Read_Byte(MPU9250_ADDR,MAG_ZOUT_H);
    sensor.mag.origin.z  =	((u16)BUF[5]<<8)|BUF[4];
 					       //读取计算Z轴数据
}

void Get_mpu_6500_offest(void)
{
    u16 cnt=200;
    sensor.acc.temp.x=0;
	sensor.acc.temp.y=0;
	sensor.acc.temp.z=0;
	
	sensor.gyro.temp.x=0;
	sensor.gyro.temp.y=0;
	sensor.gyro.temp.z=0;
    
    while(cnt--)       //循环采集2000次   求平均
	 {
        READ_MPU9250_ACCEL();
        READ_MPU9250_GYRO();

        sensor.gyro.temp.x+= sensor.gyro.origin.x;
        sensor.gyro.temp.y+= sensor.gyro.origin.y;
        sensor.gyro.temp.z+= sensor.gyro.origin.z;

        sensor.acc.temp.x+= sensor.acc.origin.x;
        sensor.acc.temp.y+= sensor.acc.origin.y;
        sensor.acc.temp.z+= sensor.acc.origin.z;
    }
    cnt=200;
    sensor.gyro.quiet.x=(sensor.gyro.temp.x/cnt);
    sensor.gyro.quiet.y=sensor.gyro.temp.y/cnt;
    sensor.gyro.quiet.z=sensor.gyro.temp.z/cnt;

    sensor.acc.quiet.x=(sensor.acc.temp.x/cnt);
    sensor.acc.quiet.y=sensor.acc.temp.y/cnt;
    sensor.acc.quiet.z=sensor.acc.temp.z/cnt;
    
    
}


/*************/
void MPU6500_Read(void)
{
	I2C_FastMode = 1;
	IIC_Read_nByte(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,14,(u8 *)mpu6500_buffer);
}


static s32 sum_temp[7]={0,0,0,0,0,0,0};
static u16 acc_sum_cnt = 0,gyro_sum_cnt = 0;

void MPU6500_Data_Offset()
{
#ifdef ACC_ADJ_EN

	if(mpu6050.Acc_CALIBRATE == 1)
	{

		if(my_sqrt(my_pow(mpu6050.Acc_I16.x)+my_pow(mpu6050.Acc_I16.y)+my_pow(mpu6050.Acc_I16.z)) < 2500)
		{
			sensor_setup.Offset.mpu_flag = 1;
		}
		else if(my_sqrt(my_pow(mpu6050.Acc_I16.x)+my_pow(mpu6050.Acc_I16.y)+my_pow(mpu6050.Acc_I16.z)) > 2600)
		{
			sensor_setup.Offset.mpu_flag = 0;
		}
						
		acc_sum_cnt++;
		sum_temp[A_X] += mpu6500.Acc_I16.x;
		sum_temp[A_Y] += mpu6500.Acc_I16.y;
		sum_temp[A_Z] += mpu6500.Acc_I16.z - 65536/16;   // +-8G
		sum_temp[TEM] += mpu6500.Tempreature;

    if( acc_sum_cnt >= OFFSET_AV_NUM )
		{
			mpu6500.Acc_Offset.x = sum_temp[A_X]/OFFSET_AV_NUM;
			mpu6500.Acc_Offset.y = sum_temp[A_Y]/OFFSET_AV_NUM;
			mpu6500.Acc_Offset.z = sum_temp[A_Z]/OFFSET_AV_NUM;
			mpu6500.Acc_Temprea_Offset = sum_temp[TEM]/OFFSET_AV_NUM;
			
//			GY_530.ACC_z_zero = acc_vector ;
			acc_sum_cnt =0;
			mpu6500.Acc_CALIBRATE = 0;
			Param_SaveAccelOffset(&mpu6500.Acc_Offset);
			sum_temp[A_X] = sum_temp[A_Y] = sum_temp[A_Z] = sum_temp[TEM] = 0;
		}	
	}

#endif

	if(mpu6050.Gyro_CALIBRATE)
	{
		gyro_sum_cnt++;
		sum_temp[G_X] += mpu6500.Gyro_I16.x;
		sum_temp[G_Y] += mpu6500.Gyro_I16.y;
		sum_temp[G_Z] += mpu6500.Gyro_I16.z;
		sum_temp[TEM] += mpu6500.Tempreature;

    if( gyro_sum_cnt >= OFFSET_AV_NUM )
		{
			mpu6500.Gyro_Offset.x = (float)sum_temp[G_X]/OFFSET_AV_NUM;
			mpu6500.Gyro_Offset.y = (float)sum_temp[G_Y]/OFFSET_AV_NUM;
			mpu6500.Gyro_Offset.z = (float)sum_temp[G_Z]/OFFSET_AV_NUM;
			mpu6500.Gyro_Temprea_Offset = sum_temp[TEM]/OFFSET_AV_NUM;
			gyro_sum_cnt =0;
			if(mpu6050.Gyro_CALIBRATE == 1)
				Param_SaveGyroOffset(&mpu6500.Gyro_Offset);
			mpu6500.Gyro_CALIBRATE = 0;
			sum_temp[G_X] = sum_temp[G_Y] = sum_temp[G_Z] = sum_temp[TEM] = 0;
		}
	}
}

static void Transform(float itx,float ity,float itz,float *it_x,float *it_y,float *it_z)
{
	*it_x = itx;
	*it_y = ity;
	*it_z = itz;

}

static s16 FILT_BUF[ITEMS][(FILTER_NUM + 1)];
static uint8_t filter_cnt = 0,filter_cnt_old = 0;

static float mpu6500_tmp[ITEMS];
static float mpu_fil_tmp[ITEMS];
static float test_ang =0,test_ang_old=0,test_ang_d,test_fli_a,test_i;

void MPU6500_Data_Prepare(float T)
{	
	u8 i;
	s32 FILT_TMP[ITEMS] = {0,0,0,0,0,0,0};
//	float auto_offset_temp[3];
  float Gyro_tmp[3];
	

	MPU6500_Data_Offset(); //????

	/*??buffer????*/
	mpu6500.Acc_I16.x = ((((int16_t)mpu6500_buffer[0]) << 8) | mpu6500_buffer[1]) ;
	mpu6500.Acc_I16.y = ((((int16_t)mpu6500_buffer[2]) << 8) | mpu6500_buffer[3]) ;
	mpu6500.Acc_I16.z = ((((int16_t)mpu6500_buffer[4]) << 8) | mpu6500_buffer[5]) ;
 
	mpu6500.Gyro_I16.x = ((((int16_t)mpu6500_buffer[ 8]) << 8) | mpu6500_buffer[ 9]) ;
	mpu6500.Gyro_I16.y = ((((int16_t)mpu6500_buffer[10]) << 8) | mpu6500_buffer[11]) ;
	mpu6500.Gyro_I16.z = ((((int16_t)mpu6500_buffer[12]) << 8) | mpu6500_buffer[13]) ;

	Gyro_tmp[0] = mpu6500.Gyro_I16.x ;//
	Gyro_tmp[1] = mpu6500.Gyro_I16.y ;//
	Gyro_tmp[2] = mpu6500.Gyro_I16.z ;//

	mpu6500.Tempreature = ((((int16_t)mpu6500_buffer[6]) << 8) | mpu6500_buffer[7]); //tempreature
	mpu6500.TEM_LPF += 2 *3.14f *T *(mpu6500.Tempreature - mpu6500.TEM_LPF);
	mpu6500.Ftempreature = mpu6050.TEM_LPF/340.0f + 36.5f;

//======================================================================
	if( ++filter_cnt > FILTER_NUM )	
	{
		filter_cnt = 0;
		filter_cnt_old = 1;
	}
	else
	{
		filter_cnt_old = (filter_cnt == FILTER_NUM)? 0 : (filter_cnt + 1);
	}
//10 170 4056
	/* ???????? */
	if(sensor_setup.Offset.mpu_flag == 0)
	{
		mpu6500_tmp[A_X] = (mpu6500.Acc_I16.x - mpu6500.Acc_Offset.x) ;
		mpu6500_tmp[A_Y] = (mpu6500.Acc_I16.y - mpu6500.Acc_Offset.y) ;
		mpu6500_tmp[A_Z] = (mpu6500.Acc_I16.z - mpu6500.Acc_Offset.z) ;
	}
	else
	{
		mpu6500_tmp[A_X] = 2*(mpu6500.Acc_I16.x - mpu6500.Acc_Offset.x) ;
		mpu6500_tmp[A_Y] = 2*(mpu6500.Acc_I16.y - mpu6500.Acc_Offset.y) ;
		mpu6500_tmp[A_Z] = 2*(mpu6500.Acc_I16.z - mpu6500.Acc_Offset.z - 2048) ;
	}
	
	mpu6500_tmp[G_X] = Gyro_tmp[0] - mpu6500.Gyro_Offset.x ;//
	mpu6500_tmp[G_Y] = Gyro_tmp[1] - mpu6500.Gyro_Offset.y ;//
	mpu6500_tmp[G_Z] = Gyro_tmp[2] - mpu6500.Gyro_Offset.z ;//
	
	
	mpu6500.TEMP_Acc_I16.x = mpu6500_tmp[A_X] ;
	mpu6500.TEMP_Acc_I16.y = mpu6500_tmp[A_Y] ;
	mpu6500.TEMP_Acc_I16.z = mpu6500_tmp[A_Z] ;
	
//	mpu6050.TEMP_Gyro_I16.x = mpu6050_tmp[G_X] ;
//	mpu6050.TEMP_Gyro_I16.y = mpu6050_tmp[G_Y] ;
//	mpu6050.TEMP_Gyro_I16.z = mpu6050_tmp[G_Z] ;	
	

//	/* ?????????? */
//	FILT_BUF[A_X][filter_cnt] = mpu6050_tmp[A_X];
//	FILT_BUF[A_Y][filter_cnt] = mpu6050_tmp[A_Y];
//	FILT_BUF[A_Z][filter_cnt] = mpu6050_tmp[A_Z];
	FILT_BUF[G_X][filter_cnt] = mpu6500_tmp[G_X]; 
	FILT_BUF[G_Y][filter_cnt] = mpu6500_tmp[G_Y];
	FILT_BUF[G_Z][filter_cnt] = mpu6500_tmp[G_Z];

	for(i=0;i<FILTER_NUM;i++)
	{
//		FILT_TMP[A_X] += FILT_BUF[A_X][i];
//		FILT_TMP[A_Y] += FILT_BUF[A_Y][i];
//		FILT_TMP[A_Z] += FILT_BUF[A_Z][i];
		FILT_TMP[G_X] += FILT_BUF[G_X][i];
		FILT_TMP[G_Y] += FILT_BUF[G_Y][i];
		FILT_TMP[G_Z] += FILT_BUF[G_Z][i];
	}


//	mpu_fil_tmp[A_X] = (float)( FILT_TMP[A_X] )/(float)FILTER_NUM;
//	mpu_fil_tmp[A_Y] = (float)( FILT_TMP[A_Y] )/(float)FILTER_NUM;
//	mpu_fil_tmp[A_Z] = (float)( FILT_TMP[A_Z] )/(float)FILTER_NUM;


	mpu_fil_tmp[G_X] = (float)( FILT_TMP[G_X] )/(float)FILTER_NUM;
	mpu_fil_tmp[G_Y] = (float)( FILT_TMP[G_Y] )/(float)FILTER_NUM;
	mpu_fil_tmp[G_Z] = (float)( FILT_TMP[G_Z] )/(float)FILTER_NUM;

	
/****************************************************/
//	mpu_fil_tmp[A_X] = lpf2pApply(&LPF2filter,mpu6050.TEMP_Acc_I16.x);
//	mpu_fil_tmp[A_Y] = lpf2pApply(&LPF2filter,mpu6050.TEMP_Acc_I16.y);
//	mpu_fil_tmp[A_Z] = lpf2pApply(&LPF2filter,mpu6050.TEMP_Acc_I16.z);
	
/****************************************************/

	imuAccIIRLPFilter(&mpu6500.TEMP_Acc_I16, //int16  xyz
				  &accelLPF, //int16 xyz
				  &accelStoredFilterValues, //int32 storevalues xyz 
                 (int32_t)imuAccLpfAttFactor);// Attenuation  maybe error
/**************************************************/		 
	/*????*/
	Transform(accelLPF.x,accelLPF.y,accelLPF.z,&mpu6050.Acc.x,&mpu6050.Acc.y,&mpu6050.Acc.z);
	Transform(mpu_fil_tmp[G_X],mpu_fil_tmp[G_Y],mpu_fil_tmp[G_Z],&mpu6050.Gyro.x,&mpu6050.Gyro.y,&mpu6050.Gyro.z);

//	Transform(mpu_fil_tmp[A_X],mpu_fil_tmp[A_Y],mpu_fil_tmp[A_Z],&mpu6050.Acc.x,&mpu6050.Acc.y,&mpu6050.Acc.z);
//	Transform(mpu_fil_tmp[G_X],mpu_fil_tmp[G_Y],mpu_fil_tmp[G_Z],&mpu6050.Gyro.x,&mpu6050.Gyro.y,&mpu6050.Gyro.z);

	mpu6050.Gyro_deg.x = mpu6050.Gyro.x *TO_ANGLE;
	mpu6050.Gyro_deg.y = mpu6050.Gyro.y *TO_ANGLE;
	mpu6050.Gyro_deg.z = mpu6050.Gyro.z *TO_ANGLE;
	

	
//======================================================================
}

