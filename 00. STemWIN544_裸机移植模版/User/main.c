/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   STemWIN �������ģ��
  *********************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
/*******************************************************************************
 * ������ͷ�ļ�
 ******************************************************************************/
/* ������Ӳ��bspͷ�ļ� */
#include "./led/bsp_led.h" 
#include "./beep/bsp_beep.h" 
#include "./usart/bsp_debug_usart.h"
#include "./TouchPad/bsp_touchpad.h"
#include "./lcd/bsp_lcd.h"
#include "./touch/bsp_i2c_touch.h"
#include "./touch/gt9xx.h"
#include "./key/bsp_key.h"
#include "./sdram/bsp_sdram.h"
#include "./systick/bsp_Systick.h"
/* STemWINͷ�ļ� */
#include "GUI.h"
#include "DIALOG.h"
#include "MainTask.h"
/* FATFS */
#include "ff.h"
#include "diskio.h"
#include "integer.h"

 /*
 *************************************************************************
 *                             ȫ�ֱ�������
 *************************************************************************
 */
FATFS   fs;								/* FatFs�ļ�ϵͳ���� */
FIL     file;							/* file objects */
UINT    bw;            		/* File R/W count */
FRESULT result; 
FILINFO fno;
DIR dir;

/*
*************************************************************************
*                             ��������
*************************************************************************
*/

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  /* CRC��emWinû�й�ϵ��ֻ������Ϊ�˿�ı���������
   * ����STemWin�Ŀ�ֻ������ST��оƬ���棬���оƬ���޷�ʹ�õġ�
   */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
	
  /*
	 * STM32�ж����ȼ�����Ϊ4����4bit��������ʾ��ռ���ȼ�����ΧΪ��0~15
	 * ���ȼ�����ֻ��Ҫ����һ�μ��ɣ��Ժ������������������Ҫ�õ��жϣ�
	 * ��ͳһ��ͬһ�����ȼ����飬ǧ��Ҫ�ٷ��飬�мǡ�
	 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
  /* ����ϵͳ�δ�ʱ�� */
  SysTick_Init();
	/* LED ��ʼ�� */
	LED_GPIO_Config();
	/* ���ڳ�ʼ��	*/
	Debug_USART_Config();
	/* ��������ʼ�� */
	Beep_GPIO_Config();
	/* ��������ʼ�� */
	GTP_Init_Panel();
//	/* �����ļ�ϵͳ������ʱ���SD����ʼ�� */
//  result = f_mount(&fs,"0:",1);
//	if(result != FR_OK)
//	{
//		printf("SD����ʼ��ʧ�ܣ���ȷ��SD������ȷ���뿪���壬��һ��SD�����ԣ�\n");
//		while(1);
//	}
	/* SDRAM��ʼ�� */
	SDRAM_Init();
	/* LCD��ʼ�� */
	LCD_Init();
  
  /* ��ʼ��GUI */
	GUI_Init();
	/* ���������� */
	WM_MULTIBUF_Enable(1);
  
  while(1)
  {
    MainTask();
  }
}

/*********************************************END OF FILE**********************/

