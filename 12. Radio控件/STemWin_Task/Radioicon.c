/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Bitmap Converter (ST) for emWin V5.44.                      *
*        Compiled Nov 10 2017, 08:52:20                              *
*                                                                    *
*        (c) 1998 - 2017 Segger Microcontroller GmbH & Co. KG        *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: Radio                                                 *
* Dimensions:  16 * 16                                               *
* NumColors:   16bpp: 65536                                          *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmRadioUnsel;
extern GUI_CONST_STORAGE GUI_BITMAP bmRadioSel;

static GUI_CONST_STORAGE unsigned short _acRadioUnsel[] = {
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7BE, 0xCE58, 0xAD54, 0xA512, 0xA512, 0xAD54, 0xCE58, 0xF7DE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xC617, 0x9CD2, 0xD6BA, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFDF, 0xDEBA, 0xA4F2, 0xC617, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xAD53, 0xBDD6, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xC5F6, 0xAD53, 0xFFFF, 0xFFFF,
  0xFFFF, 0xC617, 0xBDD6, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xC5F6, 0xC617, 0xFFFF,
  0xF7BE, 0x9CD2, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xA4F2, 0xF7DE,
  0xCE58, 0xD6BA, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xD6BA, 0xCE58,
  0xAD54, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xB574,
  0xA512, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xA512,
  0xA512, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xA512,
  0xAD54, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDE, 0xAD54,
  0xCE58, 0xD6BA, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xD6BA, 0xCE58,
  0xF7BE, 0x9CD2, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xA4F2, 0xF7DE,
  0xFFFF, 0xC617, 0xBDF6, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xC5F6, 0xC617, 0xFFFF,
  0xFFFF, 0xFFFF, 0xAD53, 0xBDD6, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xC5F6, 0xAD53, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xC617, 0x9CD1, 0xDEBA, 0xF7DE, 0xFFFF, 0xFFFF, 0xFFFF, 0xD6BA, 0xA4F2, 0xC617, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7DE, 0xCE58, 0xAD54, 0xA512, 0xA512, 0xAD54, 0xCE58, 0xF7DE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
};

GUI_CONST_STORAGE GUI_BITMAP bmRadioUnsel = {
  16, // xSize
  16, // ySize
  32, // BytesPerLine
  16, // BitsPerPixel
  (unsigned char *)_acRadioUnsel,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP565
};

static GUI_CONST_STORAGE unsigned long _acRadioSel[] = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x1674C5B9, 0x6171C0B8, 0x9771C1B8, 0xDC72C2B8, 0xDC72C2B8, 0x9771C1B8, 0x6171C0B8, 0x1674C5B9, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x7072C2B8, 0xE572C2B9, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xE572C2B9, 0x7072C2B8, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0xAF72C2B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xAF72C2B8, 0x00000000, 0x00000000,
  0x00000000, 0x5270C1B7, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0x5270C1B7, 0x00000000,
  0x2E6FBCB7, 0xEF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xC271C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xEF71C1B8, 0x2E6FBCB7,
  0x6572C0B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0x7F70C1B9, 0x00000000, 0xC271C1B8, 0xFF71C1B8, 0xFF71C1B8, 0x6572C0B8,
  0x8E71C2B9, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0x7F70C1B9, 0x00000000, 0x7F70C1B9, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0x8E71C2B9,
  0xB571C1B9, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0x5572C0B7, 0xB271C1B9, 0xFF71C1B8, 0xFF71C1B8, 0x7F70C1B9, 0x00000000, 0x7F70C1B9, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xB571C1B9,
  0xA271C0B8, 0xFF71C1B8, 0xFF71C1B8, 0xBF71C2B8, 0x00000000, 0x0F77CCBB, 0xCD71C1B8, 0x7F70C1B9, 0x00000000, 0x7F70C1B9, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xA271C0B8,
  0x7A71C0B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xCA72C1B8, 0x00000000, 0x2471BFB8, 0x00000000, 0x7F70C1B9, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0x7A71C0B8,
  0x5070BFB6, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xED71C2B8, 0x00000000, 0x7F70C1B9, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0x5070BFB6,
  0x00000000, 0x9B72C0B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0x9B72C0B8, 0x00000000,
  0x00000000, 0x0971C6C6, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0x0971C6C6, 0x00000000,
  0x00000000, 0x00000000, 0x3970C0B7, 0xF571C2B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xF571C2B8, 0x3970C0B7, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xA771C0B7, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xFF71C1B8, 0xA771C0B7, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x1B71C6BD, 0x4070BFB7, 0x6871C2B8, 0x6871C2B8, 0x4070BFB7, 0x1B71C6BD, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

GUI_CONST_STORAGE GUI_BITMAP bmRadioSel = {
  16, // xSize
  16, // ySize
  64, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)_acRadioSel,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMPM8888I
};

/*************************** End of file ****************************/
