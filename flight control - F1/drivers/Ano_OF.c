#include "ano_of.h"
#include "PID.h"
#include "time.h"
#include "Trance.h"
#include "ultrasonic.h"


uint8_t		OF_QUA,OF_LIGHT;
int8_t		OF_DX,OF_DY;
int16_t		OF_DX2,OF_DY2,OF_DX2FIX,OF_DY2FIX;
uint16_t	OF_ALT,OF_ALT2;
int16_t		OF_GYR_X,OF_GYR_Y,OF_GYR_Z;
int16_t		OF_GYR_X2,OF_GYR_Y2,OF_GYR_Z2;
int16_t		OF_ACC_X,OF_ACC_Y,OF_ACC_Z;
int16_t		OF_ACC_X2,OF_ACC_Y2,OF_ACC_Z2;
float		OF_ATT_ROL,OF_ATT_PIT,OF_ATT_YAW;
float		OF_ATT_S1,OF_ATT_S2,OF_ATT_S3,OF_ATT_S4;

void AnoOF_DataAnl(uint8_t *data_buf,uint8_t num);
	
void AnoOF_GetOneByte(uint8_t data)
{
	static uint8_t _datatemp[50];
	static u8 _data_len = 0,_data_cnt = 0;
	static u8 state = 0;
	
	if(state==0&&data==0xAA)
	{
		
		state=1;
		_datatemp[0]=data;
			
	}
	else if(state==1&&data==0x22)	//Դ��ַ
	{
		state=2;
		_datatemp[1]=data;
	}
	else if(state==2)			//Ŀ�ĵ�ַ
	{
		state=3;
		_datatemp[2]=data;
	}
	else if(state==3)			//������
	{
		state = 4;
		_datatemp[3]=data;
	}
	else if(state==4)			//����
	{
		state = 5;
		_datatemp[4]=data;
		_data_len = data;
		_data_cnt = 0;
	}
	else if(state==5&&_data_len>0)
	{
		_data_len--;
		_datatemp[5+_data_cnt++]=data;
		if(_data_len==0)
			state = 6;
	}
	else if(state==6)
	{
		state = 0;
		_datatemp[5+_data_cnt]=data;
		AnoOF_DataAnl(_datatemp,_data_cnt+6);//anoof_data_ok = 1 ;//

	}
	else
		state = 0;
}

float Ano_OF_time;
float Ano_OF_dis_x;
float Ano_OF_dis_y;
void AnoOF_DataAnl(uint8_t *data_buf,uint8_t num)
{
	u8 sum = 0;
	for(u8 i=0;i<(num-1);i++)
		sum += *(data_buf+i);
	if(!(sum==*(data_buf+num-1)))		return;		
	
	if(*(data_buf+3)==0X51)//������Ϣ
	{
		if(*(data_buf+5)==0)//ԭʼ������Ϣ
		{
			OF_QUA 		= *(data_buf+6);
			OF_DX  		= *(data_buf+7);
			OF_DY  		= *(data_buf+8);
			OF_LIGHT  	= *(data_buf+9);
		}
		else if(*(data_buf+5)==1)//�ںϺ������Ϣ
		{
			Ano_OF_time = Get_Cycle_T(5)/1000000.0f;
			OF_QUA 		= *(data_buf+6);
			OF_DX2		= (int16_t)(*(data_buf+7)<<8)|*(data_buf+8) ;
			OF_DY2		= (int16_t)(*(data_buf+9)<<8)|*(data_buf+10) ;
			OF_DX2FIX	= (int16_t)(*(data_buf+11)<<8)|*(data_buf+12) ;
			OF_DY2FIX	= (int16_t)(*(data_buf+13)<<8)|*(data_buf+14) ;
			OF_LIGHT  	= *(data_buf+19);
			
            Ano_OF_dis_x += Ano_OF_time*OF_DX2FIX;
			Ano_OF_dis_y += Ano_OF_time*OF_DY2FIX;
            
			CCD_CTRL_PID.shell_error = OF_DX2FIX * Ano_OF_time ;
			CCD_CTRL_PID.shell_Pout += pid_setup.groups.hc_sp.kd * CCD_CTRL_PID.shell_error ;
			CCD_CTRL_PID.shell_Pout = LIMIT(CCD_CTRL_PID.shell_Pout , -40,40);
			
			CCD_CTRL_PID.error = OF_DX2FIX  + camera_Trance.PID_out_V +CCD_CTRL_PID.error_ff;
			CCD_CTRL_PID.merrer += CCD_CTRL_PID.error *Ano_OF_time;
			CCD_CTRL_PID.merrer = LIMIT(CCD_CTRL_PID.merrer ,-60,60);
			CCD_CTRL_PID.devir = CCD_CTRL_PID.error - CCD_CTRL_PID.error_old ;
			CCD_CTRL_PID.error_old =CCD_CTRL_PID.error ;
			
			CCD_CTRL_PID_H.shell_error = OF_DY2FIX * Ano_OF_time ;
			CCD_CTRL_PID_H.shell_Pout +=  pid_setup.groups.hc_sp.kd * CCD_CTRL_PID_H.shell_error ;
			CCD_CTRL_PID_H.shell_Pout = LIMIT(CCD_CTRL_PID_H.shell_Pout , -40,40);
			
			CCD_CTRL_PID_H.error = OF_DY2FIX + camera_Trance.PID_out_H + CCD_CTRL_PID_H.error_ff;
			CCD_CTRL_PID_H.merrer += CCD_CTRL_PID_H.error *Ano_OF_time;
			CCD_CTRL_PID_H.merrer = LIMIT(CCD_CTRL_PID_H.merrer ,-60,60);
			CCD_CTRL_PID_H.devir = CCD_CTRL_PID_H.error - CCD_CTRL_PID_H.error_old ;
			CCD_CTRL_PID_H.error_old =CCD_CTRL_PID_H.error ;
		}
	}
	if(*(data_buf+3)==0X52)//�߶���Ϣ
	{
		if(*(data_buf+5)==0)//ԭʼ�߶���Ϣ
		{
			OF_ALT = (uint16_t)(*(data_buf+6)<<8)|*(data_buf+7) ;
		}
		else if(*(data_buf+5)==1)//�ںϺ�߶���Ϣ
		{
			OF_ALT2 = (uint16_t)(*(data_buf+6)<<8)|*(data_buf+7) ;
		}
	}
//	if(*(data_buf+3)==0X53)//��������
//	{
//		if(*(data_buf+5)==0)//ԭʼ����
//		{
//			OF_GYR_X = (int16_t)(*(data_buf+6)<<8)|*(data_buf+7) ;
//			OF_GYR_Y = (int16_t)(*(data_buf+8)<<8)|*(data_buf+9) ;
//			OF_GYR_Z = (int16_t)(*(data_buf+10)<<8)|*(data_buf+11) ;
//			OF_ACC_X = (int16_t)(*(data_buf+12)<<8)|*(data_buf+13) ;
//			OF_ACC_Y = (int16_t)(*(data_buf+14)<<8)|*(data_buf+15) ;
//			OF_ACC_Z = (int16_t)(*(data_buf+16)<<8)|*(data_buf+17) ;
//		}
//		else if(*(data_buf+5)==1)//�˲�������
//		{
//			OF_GYR_X2 = (int16_t)(*(data_buf+6)<<8)|*(data_buf+7) ;
//			OF_GYR_Y2 = (int16_t)(*(data_buf+8)<<8)|*(data_buf+9) ;
//			OF_GYR_Z2 = (int16_t)(*(data_buf+10)<<8)|*(data_buf+11) ;
//			OF_ACC_X2 = (int16_t)(*(data_buf+12)<<8)|*(data_buf+13) ;
//			OF_ACC_Y2 = (int16_t)(*(data_buf+14)<<8)|*(data_buf+15) ;
//			OF_ACC_Z2 = (int16_t)(*(data_buf+16)<<8)|*(data_buf+17) ;
//		}
//	}
//	if(*(data_buf+3)==0X54)//��̬��Ϣ
//	{
//		if(*(data_buf+5)==0)//ŷ���Ǹ�ʽ
//		{
//			OF_ATT_ROL = ((int16_t)(*(data_buf+6)<<8)|*(data_buf+7))  ;
//			OF_ATT_PIT = ((int16_t)(*(data_buf+8)<<8)|*(data_buf+9))  ;
//			OF_ATT_YAW = ((int16_t)(*(data_buf+10)<<8)|*(data_buf+11))  ;
//		}
//		else if(*(data_buf+5)==1)//��Ԫ����ʽ
//		{
//			OF_ATT_S1 = ((int16_t)(*(data_buf+6)<<8)|*(data_buf+7)) * 0.0001 ;
//			OF_ATT_S2 = ((int16_t)(*(data_buf+8)<<8)|*(data_buf+9)) * 0.0001 ;
//			OF_ATT_S3 = ((int16_t)(*(data_buf+10)<<8)|*(data_buf+11)) * 0.0001 ;
//			OF_ATT_S4 = ((int16_t)(*(data_buf+12)<<8)|*(data_buf+13)) * 0.0001 ;
//		}
//	}
}

