#include "timer3.h"
#include "include.h"
#include "PID_out.h"
#include "image.h"


u8 warning_flag=0;
 
extern uint8_t Ov7725_vsync;
extern OV7725_MODE_PARAM cam_mode;
long int Camera_Data_Buff[2][100]={0};
uint16_t camera_dis_buf[100][100];
uint16_t camera_dis2_buf[100][100];
uint16_t camera_dis3_buf[100][100];
uint16_t camera_min_data[2][100];
unsigned char tx_buff[4][260];
u8 send_buff[5500];
unsigned char Usart1_sand1_buff[19204];
extern unsigned  char deal_buff[4][128];
int f_count=0;

u8 mid_line[2][64] ;
	

void PC_send_data(void)
{
	Usart1_sand1_buff[0] =  0x01;
	Usart1_sand1_buff[1] =  0xfe;
	
	Usart1_sand1_buff[5*64+2] = 0xfe;
	Usart1_sand1_buff[5*64+3] = 0x01;
	Usart1_Send(Usart1_sand1_buff,5*64+4);
	
	/*************************/
//	tx_buff[1][0] =  0x02;
//	tx_buff[1][1] =  0xfd;
//	
//	tx_buff[1][256+2] =  0xfd;
//	tx_buff[1][256+3] =  0x02;
//	Usart1_Send(tx_buff[1],260);

}

int main(void)
{ 
	//��������
	u8 lcd_id[12];				//���LCD ID�ַ���
	u8 retry=0;
	float time;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();      //��ʼ����ʱ����
	uart_init(9600);		//��ʼ�����ڲ�����Ϊ115200
    Uart2_Init(115200);
	LED_Init();					  //��ʼ��LED
	LED0=1;
	I2c_Soft_Init();
	OLED_Init();
	tim3_init(10000-1,8400-1);
	//LCD��ʼ�� 
// 	LCD_Init();           //��ʼ��LCD FSMC�ӿ�
//	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id����
//	LCD_Clear(WHITE);
//	POINT_COLOR=RED;      //������ɫ����ɫ
	
	mid_x_line.horizontal_64_old = 64;
	mid_x_line.vertical_64_old = 64;
	position.dri_flag  =1;
	position.sound_flag = 0;
	position.take_off_flag =0;
	
	/* ov7725 gpio ��ʼ�� */
	OV7725_GPIO_Config();
	//���OV7725�Ƿ������ɹ�
	while(OV7725_Init() != SUCCESS)
	{
		retry++;
		if(retry>5)
		{
			OLED_P6x8Str(0,0,"No!");
			LCD_ShowString(30,40,210,24,24,"NO OV7725");	
			while(1);
		}
	}
	
		/*��������ͷ����������ģʽ*/
//	OV7725_Special_Effect(cam_mode.effect);
	/*����ģʽ*/
	OV7725_Light_Mode(cam_mode.light_mode);
	/*���Ͷ�*/
	OV7725_Color_Saturation(cam_mode.saturation);
	/*���ն�*/
	OV7725_Brightness(cam_mode.brightness);
	/*�Աȶ�*/
	OV7725_Contrast(cam_mode.contrast);
	/*����Ч��*/
	OV7725_Special_Effect(cam_mode.effect);
	
	/*����ͼ�������ģʽ��С*/
	OV7725_Window_Set(cam_mode.cam_sx,
														cam_mode.cam_sy,
														cam_mode.cam_width,
														cam_mode.cam_height,
														cam_mode.QVGA_VGA);
	Ov7725_vsync = 0;

	OLED_P6x8Str(0,0,"oK!");
//	oled_dis_str();
	while(1)
	{
		if( Ov7725_vsync == 2 )
		{
			
			time = Get_Cycle_T(0)/1000.0f;								
			ImagDisp(cam_mode.lcd_sx,
								cam_mode.lcd_sy,
								cam_mode.cam_width,
								cam_mode.cam_height);			/*�ɼ�����ʾ*/
			flight_data(time);
			
//			PC_send_data();
			
            OLED_P6x8data(0,0,time);
//            f_count++;
			
			
//			Draw_line(0,6,128,deal_buff[1]);
//			Draw_line(0,5,128,deal_buff[2]);
			
			Ov7725_vsync = 0;	

		}
//        Usart1_Send(&warning_flag,1);

				
	}
}
