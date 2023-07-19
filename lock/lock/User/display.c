/*
 * display.c
 *
 *  Created on: 2022Äê6ÔÂ5ÈÕ
 *      Author: hp
 */
#include "debug.h"
#include "lcd.h"
#include "display.h"
#include "key.h"
#include "PWM.h"

int i=0,j=0;
int BlinkLine_Count=0;
u8 enternum_pos_X=0;
u8 Record_PassWord[4]={0,0,0,0};
u8 PassWord[4]={0,0,0,0};
u8 time_error_count=0;
u8 flag_warning=0;
int x_warning=0,y_warning=0;
u8 flag_reshow=0;

void Display_1(u16 x, u16 y)
{
    LCD_DrawLine(x+5,y+2,x+5,y+22);
    LCD_DrawLine(x+6,y+2,x+6,y+22);
    LCD_DrawLine(x+7,y+2,x+7,y+22);
    LCD_DrawLine(x+0,y+23,x+11,y+23);
    LCD_DrawLine(x+0,y+24,x+11,y+24);
    LCD_DrawLine(x+2,y+6,x+6,y+6);
    LCD_DrawLine(x+2,y+7,x+6,y+7);
}

void Display_keyboard(void)
{
    LCD_ShowNum(0,40,1,1,32,1);
    LCD_ShowNum(40,40,2,1,32,1);
    LCD_ShowNum(80,40,3,1,32,1);
    LCD_ShowNum(120,40,4,1,32,1);
    LCD_ShowNum(160,40,5,1,32,1);
    LCD_ShowNum(200,40,6,1,32,1);
    LCD_ShowNum(0,80,7,1,32,1);
    LCD_ShowNum(40,80,8,1,32,1);
    LCD_ShowNum(80,80,9,1,32,1);
    LCD_ShowNum(120,80,0,1,32,1);
    LCD_ShowString(160, 80, 32, 0, "D");
    LCD_ShowString(200, 80, 32, 0, "Y");
    LCD_ShowNum(40,0,Record_PassWord[0],1,32,1);
    LCD_ShowNum(80,0,Record_PassWord[1],1,32,1);
    LCD_ShowNum(120,0,Record_PassWord[2],1,32,1);
    LCD_ShowNum(160,0,Record_PassWord[3],1,32,1);

}

void Display_BlinkLine(u8 num)
{
    u8 pos_x=(num-1)%6*40,pos_y=(num-1)/6*40;

    BlinkLine_Count++;
    if(BlinkLine_Count>60000)
        BlinkLine_Count=0;
    if(BlinkLine_Count<30000)
        LCD_Fill(pos_x+0,pos_y+70,pos_x+20,pos_y+70,WHITE);
    else if(BlinkLine_Count>30000&&BlinkLine_Count<60000)
        LCD_Fill(pos_x+0,pos_y+70,pos_x+20,pos_y+70,BLACK);
}

void Clear_Line(u8 num)
{
    u8 pos_x=(num-1)%6*40,pos_y=(num-1)/6*40;
    LCD_Fill(pos_x+0,pos_y+70,pos_x+20,pos_y+70,BLACK);
}

void Display_EnterNum(u8 num)
{
    if(num<10)
    {
        LCD_ShowNum(enternum_pos_X*40+40,0,num,1,32,1);
//        LCD_ShowNum(160,120,enternum_pos_X,1,32,1);
        Record_PassWord[enternum_pos_X]=num;
        enternum_pos_X++;
    }
    else if (num==10)
    {
        LCD_ShowNum(enternum_pos_X*40+40,0,0,1,32,1);
//        LCD_ShowNum(160,120,enternum_pos_X,1,32,1);
        Record_PassWord[enternum_pos_X]=0;
        enternum_pos_X++;
    }
    else if(num==11)
    {
        enternum_pos_X--;
        if (enternum_pos_X==255)
            enternum_pos_X=3;
        Record_PassWord[enternum_pos_X]=0;
        LCD_ShowNum(enternum_pos_X*40+40,0,0,1,32,1);
//        LCD_ShowNum(160,120,enternum_pos_X,1,32,1);
    }
    else if (num==12)
    {
        if (Record_PassWord[0]==PassWord[0]&&Record_PassWord[1]==PassWord[1]&&Record_PassWord[2]==PassWord[2]&&Record_PassWord[3]==PassWord[3])
        {
            LCD_Fill(0,120,200,160,BLACK);
            LCD_ShowString(0, 120, 32, 0, "PW Right");
            Open_door();
        }
        else
        {
            LCD_Fill(0,120,200,160,BLACK);
            LCD_ShowString(0, 120, 32, 0, "PW Error");
//            Close_door();
            time_error_count++;
        }
    }
    if(enternum_pos_X>3)
        enternum_pos_X=0;
}







void Display_Warning(void)
{
    LCD_Clear(BLACK);
    LCD_SetColor(0x18E3, RED);
    LCD_DrawRectangle(40, 80, 200, 160, 1);
    LCD_ShowString(64, 104, 32, 0, "Warning");
//    Close_door();
}

void Keep_Warning(void)
{
    x_warning++;
    if(x_warning>6000)
    {
        x_warning=0;
        y_warning++;
        if(y_warning>60000)
            y_warning=60000;
    }
    if(y_warning>3&&x_warning>0)
    {
        flag_warning=0;
        x_warning=0;
        y_warning=0;
        flag_reshow=1;
    }
}
