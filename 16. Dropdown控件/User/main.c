/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   FreeRTOS v9.0.0 + STM32 ����ģ��
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
#include <stdio.h>

/* FreeRTOSͷ�ļ� */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
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
/* STemWINͷ�ļ� */
#include "GUI.h"
#include "DIALOG.h"
#include "DropdownDLG.h"
/* �ļ�ϵͳ */
#include "ff.h"
#include "diskio.h"
#include "integer.h"

/**************************** ������ ********************************/
/* 
 * ��������һ��ָ�룬����ָ��һ�����񣬵����񴴽���֮�����;�����һ��������
 * �Ժ�����Ҫ��������������Ҫͨ�������������������������������Լ�����ô
 * ����������ΪNULL��
 */
/* ���������� */
static TaskHandle_t AppTaskCraete_Handle = NULL;
/* TPAD������ */
static TaskHandle_t TPAD_Task_Handle = NULL;
/* LED������ */
static TaskHandle_t LED_Task_Handle = NULL;
/* Key������ */
static TaskHandle_t Key_Task_Handle = NULL;
/* Touch������ */
static TaskHandle_t Touch_Task_Handle = NULL;
/* GUI������ */
static TaskHandle_t GUI_Task_Handle = NULL;

/********************************** �ں˶����� *********************************/
/*
 * �ź�������Ϣ���У��¼���־�飬�����ʱ����Щ�������ں˵Ķ���Ҫ��ʹ����Щ�ں�
 * ���󣬱����ȴ����������ɹ�֮��᷵��һ����Ӧ�ľ����ʵ���Ͼ���һ��ָ�룬������
 * �ǾͿ���ͨ��������������Щ�ں˶���
 *
 * �ں˶���˵���˾���һ��ȫ�ֵ����ݽṹ��ͨ����Щ���ݽṹ���ǿ���ʵ��������ͨ�ţ�
 * �������¼�ͬ���ȸ��ֹ��ܡ�������Щ���ܵ�ʵ��������ͨ��������Щ�ں˶���ĺ���
 * ����ɵ�
 * 
 */
 
/******************************* ȫ�ֱ������� ************************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩȫ�ֱ�����
 */
KEY Key1,Key2;

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
static void AppTaskCreate(void);

static void TPAD_Task(void* parameter);
static void LED_Task(void* parameter);
static void Key_Task(void* parameter);
static void Touch_Task(void* parameter);
static void GUI_Task(void* parameter);

static void BSP_Init(void);
static void BL8782_PDN_INIT(void);

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	
	/* ������Ӳ����ʼ�� */
	BSP_Init();
	
	xReturn = xTaskCreate((TaskFunction_t)AppTaskCreate,/* ������ں��� */
											 (const char*    )"AppTaskCreate",/* �������� */
											 (uint16_t       )512,					/* ����ջ��С */
											 (void*          )NULL,					/* ������ں������� */
											 (UBaseType_t    )1,						/* ��������ȼ� */
											 (TaskHandle_t   )&AppTaskCraete_Handle);/* ������ƿ�ָ�� */
	/* ����������� */
	if(pdPASS == xReturn)
		vTaskStartScheduler();/* �������񣬿������� */
	else
		return -1;
	
	while(1);/* ��������ִ�е����� */
}

/**
  * @brief ���񴴽�����
  * @note Ϊ�˷���������е����񴴽������������������
  * @param ��
  * @retval ��
  */
static void AppTaskCreate(void)
{
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	
	taskENTER_CRITICAL();//�����ٽ���
	
	xReturn = xTaskCreate((TaskFunction_t)TPAD_Task,/* ������ں��� */
											 (const char*    )"TPAD_Task",/* �������� */
											 (uint16_t       )128,       /* ����ջ��С */
											 (void*          )NULL,      /* ������ں������� */
											 (UBaseType_t    )7,         /* ��������ȼ� */
											 (TaskHandle_t   )&TPAD_Task_Handle);/* ������ƿ�ָ�� */
	if(pdPASS == xReturn)
		printf("����TPAD_Task����ɹ���\r\n");
	
	xReturn = xTaskCreate((TaskFunction_t)LED_Task,/* ������ں��� */
											 (const char*    )"LED_Task",/* �������� */
											 (uint16_t       )128,       /* ����ջ��С */
											 (void*          )NULL,      /* ������ں������� */
											 (UBaseType_t    )6,         /* ��������ȼ� */
											 (TaskHandle_t   )&LED_Task_Handle);/* ������ƿ�ָ�� */
	if(pdPASS == xReturn)
		printf("����LED1_Task����ɹ���\r\n");
	
	xReturn = xTaskCreate((TaskFunction_t)Key_Task,/* ������ں��� */
											 (const char*      )"Key_Task",/* �������� */
											 (uint16_t         )256,     /* ����ջ��С */
											 (void*            )NULL,    /* ������ں������� */
											 (UBaseType_t      )5,       /* ��������ȼ� */
											 (TaskHandle_t     )&Key_Task_Handle);/* ������ƿ�ָ�� */
	if(pdPASS == xReturn)
		printf("����Key_Task����ɹ���\r\n");
	
	xReturn = xTaskCreate((TaskFunction_t)Touch_Task,/* ������ں��� */
											 (const char*      )"Touch_Task",/* �������� */
											 (uint16_t         )256,     /* ����ջ��С */
											 (void*            )NULL,    /* ������ں������� */
											 (UBaseType_t      )4,       /* ��������ȼ� */
											 (TaskHandle_t     )&Touch_Task_Handle);/* ������ƿ�ָ�� */
	if(pdPASS == xReturn)
		printf("����Touch_Task����ɹ���\r\n");
	
	xReturn = xTaskCreate((TaskFunction_t)GUI_Task,/* ������ں��� */
											 (const char*      )"GUI_Task",/* �������� */
											 (uint16_t         )1024,      /* ����ջ��С */
											 (void*            )NULL,      /* ������ں������� */
											 (UBaseType_t      )3,         /* ��������ȼ� */
											 (TaskHandle_t     )&GUI_Task_Handle);/* ������ƿ�ָ�� */
	if(pdPASS == xReturn)
		printf("����GUI_Task����ɹ���\r\n");
	
	vTaskDelete(AppTaskCraete_Handle);//ɾ��AppTaskCreate����
	
	taskEXIT_CRITICAL();//�˳��ٽ���
}

/**
  * @brief ���ݰ�����������
  * @note ��
  * @param ��
  * @retval ��
  */
static void TPAD_Task(void* parameter)
{
	/* ���ݰ�����ʼ�� */
	TPAD_Init();
	
	while(1)
	{
		if(TPAD_Scan(0))
		{
			BEEP_ON;
			vTaskDelay(50);
			BEEP_OFF;
		}
		vTaskDelay(50);
	}
}

/**
  * @brief LED��������
  * @note ��
  * @param ��
  * @retval ��
  */
static void LED_Task(void* parameter)
{
	while(1)
	{
		LED3_ON;
		vTaskDelay(1000);
    LED3_OFF;
		vTaskDelay(1000);
	}
}

/**
  * @brief ������������
  * @note ��
  * @param ��
  * @retval ��
  */
static void Key_Task(void* parameter)
{
	while(1)
	{
		Key_RefreshState(&Key1);//ˢ�°���״̬
		Key_RefreshState(&Key2);//ˢ�°���״̬
		if(Key_AccessTimes(&Key1,KEY_ACCESS_READ)!=0)//���������¹�
		{
			LED2_TOGGLE;
			Key_AccessTimes(&Key1,KEY_ACCESS_WRITE_CLEAR);
		}
		if(Key_AccessTimes(&Key2,KEY_ACCESS_READ)!=0)//���������¹�
		{
			LED1_TOGGLE;
			Key_AccessTimes(&Key2,KEY_ACCESS_WRITE_CLEAR);
		}
		vTaskDelay(50);
	}
}

/**
  * @brief ���������������
  * @note ��
  * @param ��
  * @retval ��
  */
static void Touch_Task(void* parameter)
{
	while(1)
	{
		GT9xx_GetOnePiont();
		vTaskDelay(20);
	}
}

/**
  * @brief GUI��������
  * @note ��
  * @param ��
  * @retval ��
  */
static void GUI_Task(void* parameter)
{
	/* ��ʼ��GUI */
	GUI_Init();
	/* �����໺�� */
	WM_MULTIBUF_Enable(1);
	
	while(1)
	{
		MainTask();
	}
}

/**
  * @brief �弶�����ʼ��
  * @note ���а����ϵĳ�ʼ�����ɷ��������������
  * @param ��
  * @retval ��
  */
static void BSP_Init(void)
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
	
	/* LED ��ʼ�� */
	LED_GPIO_Config();
	/* ���ڳ�ʼ��	*/
	Debug_USART_Config();
	/* ��������ʼ�� */
	Beep_GPIO_Config();
	/* ������ʼ�� */
	Key1_GPIO_Config();
	Key2_GPIO_Config();
	KeyCreate(&Key1,GetPinStateOfKey1);
	KeyCreate(&Key2,GetPinStateOfKey2);
	/* ��������ʼ�� */
	GTP_Init_Panel();	
	/* SDRAM��ʼ�� */
  SDRAM_Init();
	/* LCD��ʼ�� */
	LCD_Init();
  /* ����WIFIģ�� */
  BL8782_PDN_INIT();
  /* �����ļ�ϵͳ������ʱ���SD����ʼ�� */
	/*Ĭ�ϲ�ʹ��SD��������SD�����ؼ���ʼ���������ڲ�����SD���ǳ���Ῠ����while(1)ѭ��*/
//  result = f_mount(&fs,"0:",1);
//	if(result != FR_OK)
//	{
//		printf("SD����ʼ��ʧ�ܣ���ȷ��SD������ȷ���뿪���壬��һ��SD�����ԣ�\n");
//		while(1);
//	}
}

/**
  * @brief BL8782_PDN_INIT
  * @note ��ֹWIFIģ��
  * @param ��
  * @retval ��
  */
static void BL8782_PDN_INIT(void)
{
  /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOG, ENABLE); 							   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
  GPIO_Init(GPIOG, &GPIO_InitStructure);	
  
  GPIO_ResetBits(GPIOG,GPIO_Pin_9);  //����WiFiģ��
}

/*********************************************END OF FILE**********************/

