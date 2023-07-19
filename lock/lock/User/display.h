/*
 * display.h
 *
 *  Created on: 2022Äê6ÔÂ5ÈÕ
 *      Author: hp
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_


#define  FS_Right  1
#define  FS_Wrong  2

#define  Add_FS_Success  1
#define  Add_FS_Fail  2

#define  OpenMv_Right  1
#define  OpenMv_Wrong  2


extern int BlinkLine_Count;
extern u8 Record_PassWord[4];
extern u8 PassWord[4];
extern u8 time_error_count;
extern u8 flag_warning;
extern int x_warning;
extern int y_warning;
extern u8 flag_reshow;

void Display_1(u16 x, u16 y);
void Display_keyboard(void);
void Display_BlinkLine(u8 num);
void Clear_Line(u8 num);
void Display_EnterNum(u8 num);
void Display_JudgeFR(void);
void Display_AddFR(void);
void Display_OpenMV(void);
void Display_Warning(void);
void Keep_Warning(void);

#endif /* DISPLAY_H_ */
