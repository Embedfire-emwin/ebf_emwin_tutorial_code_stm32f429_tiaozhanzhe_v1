 /**
  ******************************************************************************
  * @file    bsp_xxx.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   spi flash �ײ�Ӧ�ú���bsp 
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� STM32 F429 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./fatfs/drivers/fatfs_flash_spi.h"

static volatile DSTATUS TM_FATFS_FLASH_SPI_Stat = STA_NOINIT;	/* Physical drive status */

#ifdef  USB_SPI_TIMEOUT
static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;   
static  uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);
#endif

/*******************************************************************************
* Function Name  : SPI_FLASH_Init
* Description    : Initializes the peripherals used by the SPI FLASH driver.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
DSTATUS TM_FATFS_FLASH_SPI_disk_initialize(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* ʹ�� FLASH_SPI ��GPIO ʱ�� */
  /*!< SPI_FLASH_SPI_CS_GPIO, SPI_FLASH_SPI_MOSI_GPIO, 
       SPI_FLASH_SPI_MISO_GPIO,SPI_FLASH_SPI_SCK_GPIO ʱ��ʹ�� */
  RCC_AHB1PeriphClockCmd (FLASH_SPI_SCK_GPIO_CLK | FLASH_SPI_MISO_GPIO_CLK|FLASH_SPI_MOSI_GPIO_CLK|FLASH_CS_GPIO_CLK, ENABLE);

  /*!< SPI_FLASH_SPI ʱ��ʹ�� */
  FLASH_SPI_CLK_INIT(FLASH_SPI_CLK, ENABLE);
 
  //�������Ÿ���
  GPIO_PinAFConfig(FLASH_SPI_SCK_GPIO_PORT,FLASH_SPI_SCK_PINSOURCE,FLASH_SPI_SCK_AF); 
	GPIO_PinAFConfig(FLASH_SPI_MISO_GPIO_PORT,FLASH_SPI_MISO_PINSOURCE,FLASH_SPI_MISO_AF); 
	GPIO_PinAFConfig(FLASH_SPI_MOSI_GPIO_PORT,FLASH_SPI_MOSI_PINSOURCE,FLASH_SPI_MOSI_AF); 
  
  /*!< ���� SPI_FLASH_SPI ����: SCK */
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
  
  GPIO_Init(FLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);
  
	/*!< ���� SPI_FLASH_SPI ����: MISO */
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN;
  GPIO_Init(FLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);
  
	/*!< ���� SPI_FLASH_SPI ����: MOSI */
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI_PIN;
  GPIO_Init(FLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);  

	/*!< ���� SPI_FLASH_SPI ����: CS */
  GPIO_InitStructure.GPIO_Pin = FLASH_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(FLASH_CS_GPIO_PORT, &GPIO_InitStructure);

  /* ֹͣ�ź� FLASH: CS���Ÿߵ�ƽ*/
  SPI_FLASH_CS_HIGH();

  /* FLASH_SPI ģʽ���� */
  // FLASHоƬ ֧��SPIģʽ0��ģʽ3���ݴ�����CPOL CPHA
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(FLASH_SPI, &SPI_InitStructure);

  /* ʹ�� FLASH_SPI  */
  SPI_Cmd(FLASH_SPI, ENABLE);

	/* ʹ SPI_FLASH ���� 4 �ֽڵ�ַģʽ */
	SPI_FLASH_Mode_Init();

	
	return TM_FATFS_FLASH_SPI_disk_status();

}

DSTATUS TM_FATFS_FLASH_SPI_disk_status(void)
{
	FLASH_DEBUG_FUNC();
	if(sFLASH_ID == SPI_FLASH_ReadID())			/*���FLASH�Ƿ���������*/
	{
		return TM_FATFS_FLASH_SPI_Stat &= ~STA_NOINIT;	/* Clear STA_NOINIT flag */
	}else
	{
		return TM_FATFS_FLASH_SPI_Stat |= STA_NOINIT;
	}
}

DRESULT TM_FATFS_FLASH_SPI_disk_ioctl(BYTE cmd, char *buff)
{


	  FLASH_DEBUG_FUNC();
	switch (cmd) {
		case GET_SECTOR_COUNT:
			*(DWORD * )buff = 2560;		//sector����   
		break;
		case GET_SECTOR_SIZE :     // Get R/W sector size (WORD)

			*(WORD * )buff = 4096;		//flash��Сд��ԪΪҳ��256�ֽڣ��˴�ȡ2ҳΪһ����д��λ
		break;
		case GET_BLOCK_SIZE :      // Get erase block size in unit of sector (DWORD)
			*(DWORD * )buff = 1;		//flash��1��sectorΪ��С������λ
		break;
		case CTRL_ERASE_SECTOR:
		break;
		case CTRL_SYNC :
		break;
	}
	return RES_OK;
}

DRESULT TM_FATFS_FLASH_SPI_disk_read(BYTE *buff, DWORD sector, UINT count)
{
	FLASH_DEBUG_FUNC();
	if ((TM_FATFS_FLASH_SPI_Stat & STA_NOINIT)) 
	{
		return RES_NOTRDY;
	}
	sector+=1536;//����ƫ�ƣ��ⲿFlash�ļ�ϵͳ�ռ�����ⲿFlash����6M�ռ�
	SPI_FLASH_BufferRead(buff, sector <<12, count<<12);
	return RES_OK;
}

DRESULT TM_FATFS_FLASH_SPI_disk_write(BYTE *buff, DWORD sector, UINT count)
{
	uint32_t write_addr;  
	FLASH_DEBUG_FUNC();
	sector+=1536;//����ƫ�ƣ��ⲿFlash�ļ�ϵͳ�ռ�����ⲿFlash����4M�ռ�
	write_addr = sector<<12;    
	SPI_FLASH_SectorErase(write_addr);
	SPI_FLASH_BufferWrite(buff,write_addr,4096);
	return RES_OK;
}

/*******************************************************************************
* Function Name  : SPI_FLASH_SectorErase
* Description    : Erases the specified FLASH sector.
* Input          : SectorAddr: address of the sector to erase.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_SectorErase(u32 SectorAddr)
{
  /* ����FLASHдʹ������ */
  SPI_FLASH_WriteEnable();
  SPI_FLASH_WaitForWriteEnd();
  /* �������� */
  /* ѡ��FLASH: CS�͵�ƽ */
  SPI_FLASH_CS_LOW();
  /* ������������ָ��*/
  SPI_FLASH_SendByte(W25X_SectorErase);
  /*���Ͳ���������ַ�ĸ�8λ*/
  SPI_FLASH_SendByte((SectorAddr & 0xFF000000) >> 24);
  /*���Ͳ���������ַ����ǰ8λ*/
  SPI_FLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
  /* ���Ͳ���������ַ���к�8λ */
  SPI_FLASH_SendByte((SectorAddr & 0xFF00) >> 8);
  /* ���Ͳ���������ַ�ĵ�8λ */
  SPI_FLASH_SendByte(SectorAddr & 0xFF);
  /* ֹͣ�ź� FLASH: CS �ߵ�ƽ */
  SPI_FLASH_CS_HIGH();
  /* �ȴ��������*/
  SPI_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_BulkErase
* Description    : Erases the entire FLASH.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BulkErase(void)
{
  /* ����FLASHдʹ������ */
  SPI_FLASH_WriteEnable();

  /* ���� Erase */
  /* ѡ��FLASH: CS�͵�ƽ */
  SPI_FLASH_CS_LOW();
  /* �����������ָ��*/
  SPI_FLASH_SendByte(W25X_ChipErase);
  /* ֹͣ�ź� FLASH: CS �ߵ�ƽ */
  SPI_FLASH_CS_HIGH();

  /* �ȴ��������*/
  SPI_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_PageWrite
* Description    : Writes more than one byte to the FLASH with a single WRITE
*                  cycle(Page WRITE sequence). The number of byte can't exceed
*                  the FLASH page size.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the FLASH,
*                    must be equal or less than "SPI_FLASH_PageSize" value.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
  /* ����FLASHдʹ������ */
  SPI_FLASH_WriteEnable();

  /* ѡ��FLASH: CS�͵�ƽ */
  SPI_FLASH_CS_LOW();
  /* дҳдָ��*/
  SPI_FLASH_SendByte(W25X_PageProgram_4BYTE);
	
  /*����д��ַ�ĸ�8λ*/
  SPI_FLASH_SendByte((WriteAddr & 0xFF000000) >> 24);
  /*����д��ַ����ǰ8λ*/
  SPI_FLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
  /*����д��ַ���к�8λ*/
  SPI_FLASH_SendByte((WriteAddr & 0xFF00) >> 8);
  /*����д��ַ�ĵ�8λ*/
  SPI_FLASH_SendByte(WriteAddr & 0xFF);

  if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
  {
     NumByteToWrite = SPI_FLASH_PerWritePageSize;
     FLASH_ERROR("SPI_FLASH_PageWrite too large!");
  }

  /* д������*/
  while (NumByteToWrite--)
  {
    /* ���͵�ǰҪд����ֽ����� */
    SPI_FLASH_SendByte(*pBuffer);
    /* ָ����һ�ֽ����� */
    pBuffer++;
  }

  /* ֹͣ�ź� FLASH: CS �ߵ�ƽ */
  SPI_FLASH_CS_HIGH();

  /* �ȴ�д�����*/
  SPI_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_BufferWrite
* Description    : Writes block of data to the FLASH. In this function, the
*                  number of WRITE cycles are reduced, using Page WRITE sequence.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
#if 0  
  u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

  Addr = WriteAddr % SPI_FLASH_PageSize;
  count = SPI_FLASH_PageSize - Addr;
  NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

  if (Addr == 0) /* WriteAddr is SPI_FLASH_PageSize aligned  */
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
  else /* WriteAddr is not SPI_FLASH_PageSize aligned  */
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      if (NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
      {
        temp = NumOfSingle - count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
      }
      else
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;

      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      if (NumOfSingle != 0)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
  
#else
  u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
	
	/*mod�������࣬��writeAddr��SPI_FLASH_PageSize��������������AddrֵΪ0*/
  Addr = WriteAddr % SPI_FLASH_PageSize;
	
	/*��count������ֵ���պÿ��Զ��뵽ҳ��ַ*/
  count = SPI_FLASH_PageSize - Addr;	
	/*�����Ҫд��������ҳ*/
  NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
	/*mod�������࣬�����ʣ�಻��һҳ���ֽ���*/
  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

	 /* Addr=0,��WriteAddr �պð�ҳ���� aligned  */
  if (Addr == 0) 
  {
		/* NumByteToWrite < SPI_FLASH_PageSize */
    if (NumOfPage == 0) 
    {
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
			/*�Ȱ�����ҳ��д��*/
      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }
			
			/*���ж���Ĳ���һҳ�����ݣ�����д��*/
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
	/* ����ַ�� SPI_FLASH_PageSize ������  */
  else 
  {
		/* NumByteToWrite < SPI_FLASH_PageSize */
    if (NumOfPage == 0) 
    {
			/*��ǰҳʣ���count��λ�ñ�NumOfSingleС��д����*/
      if (NumOfSingle > count) 
      {
        temp = NumOfSingle - count;
				
				/*��д����ǰҳ*/
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;
				
				/*��дʣ�������*/
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
      }
      else /*��ǰҳʣ���count��λ����д��NumOfSingle������*/
      {				
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
			/*��ַ����������count�ֿ������������������*/
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;
			
			/*������ҳ��д��*/
      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }
			/*���ж���Ĳ���һҳ�����ݣ�����д��*/
      if (NumOfSingle != 0)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }

#endif  
}

/*******************************************************************************
* Function Name  : SPI_FLASH_BufferRead
* Description    : Reads a block of data from the FLASH.
* Input          : - pBuffer : pointer to the buffer that receives the data read
*                    from the FLASH.
*                  - ReadAddr : FLASH's internal address to read from.
*                  - NumByteToRead : number of bytes to read from the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, uint32_t NumByteToRead)
{
  /* ѡ��FLASH: CS�͵�ƽ */
  SPI_FLASH_CS_LOW();

  /* ���� �� ָ�� */
  SPI_FLASH_SendByte(W25X_ReadData_4BYTE);
	
  /* ���� �� ��ַ��8λ */
  SPI_FLASH_SendByte((ReadAddr & 0xFF000000) >> 24);
  /* ���� �� ��ַ��ǰ8λ */
  SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  /* ���� �� ��ַ�к�8λ */
  SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  /* ���� �� ��ַ��8λ */
  SPI_FLASH_SendByte(ReadAddr & 0xFF);
  
	/* ��ȡ���� */
  while (NumByteToRead--)
  {
    /* ��ȡһ���ֽ�*/
    *pBuffer = SPI_FLASH_SendByte(Dummy_Byte);
    /* ָ����һ���ֽڻ����� */
    pBuffer++;
  }

  /* ֹͣ�ź� FLASH: CS �ߵ�ƽ */
  SPI_FLASH_CS_HIGH();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_ReadID
* Description    : Reads FLASH identification.
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
u32 SPI_FLASH_ReadID(void)
{
  u32 Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

  /* ��ʼͨѶ��CS�͵�ƽ */
  SPI_FLASH_CS_LOW();

  /* ����JEDECָ���ȡID */
  SPI_FLASH_SendByte(W25X_JedecDeviceID);

  /* ��ȡһ���ֽ����� */
  Temp0 = SPI_FLASH_SendByte(Dummy_Byte);

  /* ��ȡһ���ֽ����� */
  Temp1 = SPI_FLASH_SendByte(Dummy_Byte);

  /* ��ȡһ���ֽ����� */
  Temp2 = SPI_FLASH_SendByte(Dummy_Byte);

  /* ֹͣͨѶ��CS�ߵ�ƽ */
  SPI_FLASH_CS_HIGH();

	/*�����������������Ϊ�����ķ���ֵ*/
  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

  return Temp;
}
/*******************************************************************************
* Function Name  : SPI_FLASH_ReadID
* Description    : Reads FLASH identification.
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
u32 SPI_FLASH_ReadDeviceID(void)
{
  u32 Temp = 0;

  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "RDID " instruction */
  SPI_FLASH_SendByte(W25X_DeviceID);
  SPI_FLASH_SendByte(Dummy_Byte);
  SPI_FLASH_SendByte(Dummy_Byte);
  SPI_FLASH_SendByte(Dummy_Byte);
  
  /* Read a byte from the FLASH */
  Temp = SPI_FLASH_SendByte(Dummy_Byte);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  return Temp;
}
/*******************************************************************************
* Function Name  : SPI_FLASH_StartReadSequence
* Description    : Initiates a read data byte (READ) sequence from the Flash.
*                  This is done by driving the /CS line low to select the device,
*                  then the READ instruction is transmitted followed by 3 bytes
*                  address. This function exit and keep the /CS line low, so the
*                  Flash still being selected. With this technique the whole
*                  content of the Flash is read with a single READ instruction.
* Input          : - ReadAddr : FLASH's internal address to read from.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_StartReadSequence(u32 ReadAddr)
{
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Read from Memory " instruction */
  SPI_FLASH_SendByte(W25X_ReadData_4BYTE);

  /* Send the 24-bit address of the address to read from -----------------------*/
  /* Send ReadAddr high nibble address byte */
  SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  /* Send ReadAddr medium nibble address byte */
  SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  /* Send ReadAddr low nibble address byte */
  SPI_FLASH_SendByte(ReadAddr & 0xFF);
}


 /**
  * @brief  ʹ��SPI��ȡһ���ֽڵ�����
  * @param  ��
  * @retval ���ؽ��յ�������
  */
u8 SPI_FLASH_ReadByte(void)
{
  return (SPI_FLASH_SendByte(Dummy_Byte));
}


 /**
  * @brief  ʹ��SPI����һ���ֽڵ�����
  * @param  byte��Ҫ���͵�����
  * @retval ���ؽ��յ�������
  */
u8 SPI_FLASH_SendByte(u8 byte)
{
  SPITimeout = SPIT_FLAG_TIMEOUT;

  /* �ȴ����ͻ�����Ϊ�գ�TXE�¼� */
  while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET)
   {
    if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(0);
   }

  /* д�����ݼĴ�������Ҫд�������д�뷢�ͻ����� */
  SPI_I2S_SendData(FLASH_SPI, byte);

  SPITimeout = SPIT_FLAG_TIMEOUT;

  /* �ȴ����ջ������ǿգ�RXNE�¼� */
  while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET)
   {
    if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
   }

  /* ��ȡ���ݼĴ�������ȡ���ջ��������� */
  return SPI_I2S_ReceiveData(FLASH_SPI);
}

/*******************************************************************************
* Function Name  : SPI_FLASH_SendHalfWord
* Description    : Sends a Half Word through the SPI interface and return the
*                  Half Word received from the SPI bus.
* Input          : Half Word : Half Word to send.
* Output         : None
* Return         : The value of the received Half Word.
*******************************************************************************/
u16 SPI_FLASH_SendHalfWord(u16 HalfWord)
{
  
  SPITimeout = SPIT_FLAG_TIMEOUT;

  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET)
  {
    if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(2);
   }

  /* Send Half Word through the FLASH_SPI peripheral */
  SPI_I2S_SendData(FLASH_SPI, HalfWord);

  SPITimeout = SPIT_FLAG_TIMEOUT;

  /* Wait to receive a Half Word */
  while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET)
   {
    if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(3);
   }
  /* Return the Half Word read from the SPI bus */
  return SPI_I2S_ReceiveData(FLASH_SPI);
}


 /**
  * @brief  ��FLASH���� дʹ�� ����
  * @param  none
  * @retval none
  */
void SPI_FLASH_WriteEnable(void)
{
  /* ͨѶ��ʼ��CS�� */
  SPI_FLASH_CS_LOW();

  /* ����дʹ������*/
  SPI_FLASH_SendByte(W25X_WriteEnable);

  /*ͨѶ������CS�� */
  SPI_FLASH_CS_HIGH();
}

 /**
  * @brief  �ȴ�WIP(BUSY)��־����0�����ȴ���FLASH�ڲ�����д�����
  * @param  none
  * @retval none
  */
void SPI_FLASH_WaitForWriteEnd(void)
{
  u8 FLASH_Status = 0;

  /* ѡ�� FLASH: CS �� */
  SPI_FLASH_CS_LOW();

  /* ���� ��״̬�Ĵ��� ���� */
  SPI_FLASH_SendByte(W25X_ReadStatusReg);

  SPITimeout = SPIT_FLAG_TIMEOUT;
  /* ��FLASHæµ����ȴ� */
  do
  {
    /* ��ȡFLASHоƬ��״̬�Ĵ��� */
    FLASH_Status = SPI_FLASH_SendByte(Dummy_Byte);	 

    {
      if((SPITimeout--) == 0) 
      {
        SPI_TIMEOUT_UserCallback(4);
        return;
      }
    } 
  }
  while ((FLASH_Status & WIP_Flag) == SET); /* ����д���־ */

  /* ֹͣ�ź�  FLASH: CS �� */
  SPI_FLASH_CS_HIGH();
}


//�������ģʽ
void SPI_Flash_PowerDown(void)   
{ 
  /* ѡ�� FLASH: CS �� */
  SPI_FLASH_CS_LOW();

  /* ���� ���� ���� */
  SPI_FLASH_SendByte(W25X_PowerDown);

  /* ֹͣ�ź�  FLASH: CS �� */
  SPI_FLASH_CS_HIGH();
}   

//����
void SPI_Flash_WAKEUP(void)   
{
  /*ѡ�� FLASH: CS �� */
  SPI_FLASH_CS_LOW();

  /* ���� �ϵ� ���� */
  SPI_FLASH_SendByte(W25X_ReleasePowerDown);

  /* ֹͣ�ź� FLASH: CS �� */
  SPI_FLASH_CS_HIGH();                   //�ȴ�TRES1
}   

 /**
  * @brief  ʹ SPI_FLASH ���� 4 �ֽڵ�ַģʽ
  * @param  none
  * @retval none
  */
void SPI_FLASH_Mode_Init(void)
{
	uint8_t Temp;
	
	/*ѡ�� FLASH: CS �� */
	SPI_FLASH_CS_LOW();
	
	/* ����״̬�Ĵ��� 3 ���� */
	SPI_FLASH_SendByte(W25X_ReadStatusRegister3); 
	
	Temp = SPI_FLASH_SendByte(Dummy_Byte);
	
	/* ֹͣ�ź� FLASH: CS �� */
	SPI_FLASH_CS_HIGH();
	
	if((Temp&0x01) == 0)
	{
		/*ѡ�� FLASH: CS �� */
		SPI_FLASH_CS_LOW();
		
		/* ����4�ֽ�ģʽ */
		SPI_FLASH_SendByte(W25X_Enter4ByteMode);
		
		/* ֹͣ�ź� FLASH: CS �� */
		SPI_FLASH_CS_HIGH();
	}
}
	



#ifdef  USB_SPI_TIMEOUT
/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */
static  uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* �ȴ���ʱ��Ĵ���,���������Ϣ */
  FLASH_ERROR("SPI �ȴ���ʱ!errorCode = %d",errorCode);
  return 0;
}
#endif
   
/*********************************************END OF FILE**********************/
