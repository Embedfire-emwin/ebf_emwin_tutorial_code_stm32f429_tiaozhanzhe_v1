/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.44                          *
*        Compiled Nov 10 2017, 08:53:57                              *
*        (c) 2017 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

/* STemWIN头文件 */
#include "MainTask.h"


/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

/*********************************************************************
*
*       _aDialogCreate
*/

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/**
  * @brief GUI主任务
  * @note 无
  * @param 无
  * @retval 无
  */
void MainTask(void)
{
	/* 设置背景颜色 */
	GUI_SetBkColor(GUI_BLUE);
	GUI_Clear();
	
	/* 开启光标 */
	GUI_CURSOR_Show();
  
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(GUI_FONT_24_1);
  GUI_DispString("Hello World!\r\nuse FreeRTOS");
  
	while(1)
	{
		GUI_Delay(1000);
	}
}

/*************************** End of file ****************************/
