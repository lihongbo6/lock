/*
 * key.c
 *
 *  Created on: 2022Äê6ÔÂ6ÈÕ
 *      Author: hp
 */
#include "debug.h"
#include "lcd.h"
#include "display.h"
#include "key.h"

u8 keyboard[2][6]={
        {1,2,3,4,5,6},
        {7,8,9,10,11,12}
};


enum Judge Judge_Value;
enum Judge Add_Value;
enum Judge OpenMV_Value;
u8 Judge_data=0;
u8 Judge_OpenMV=1;
u8 Add_data=0;
u8 num=1;
u8 X_key=0;
u8 Y_key=0;
u8 flag_enter=0;
u8 flag_JudgeFR=0;
u8 flag_InFR=0;
u8 flag_OpenMV=0;
u8 flag_dispaly_OpenMV=0;
/*******************************************************************************
* Function Name  : EXTI0_INT_INIT
* Description    : Initializes EXTI0 collection.
* Input          : None
* Return         : None
*******************************************************************************/
void EXTI_INT_INIT(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_13;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
      GPIO_Init(GPIOD, &GPIO_InitStructure);



  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource1);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource5);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource6);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource13);


  EXTI_InitStructure.EXTI_Line=EXTI_Line0|EXTI_Line1|EXTI_Line2|EXTI_Line3|EXTI_Line4|EXTI_Line5|EXTI_Line6|EXTI_Line13;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : EXTI0_IRQHandler
* Description    : This function handles EXTI0 Handler.
* Input          : None
* Return         : None
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
  {
      if(flag_InFR==0&&flag_JudgeFR==0&&flag_OpenMV==0)
      {

          if (Judge_OpenMV%2)
          {
              OpenMV_Value=Right;
          }
          else
          {
              OpenMV_Value=Wrong;
          }
          flag_OpenMV=1;//Wake UP

      }
    EXTI_ClearITPendingBit(EXTI_Line0);     /* Clear Flag */
  }
}

/*******************************************************************************
* Function Name  : EXTI0_IRQHandler
* Description    : This function handles EXTI0 Handler.
* Input          : None
* Return         : None
*******************************************************************************/
void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
  {
      Y_key--;
    if(Y_key==255)
        Y_key=1;
    EXTI_ClearITPendingBit(EXTI_Line1);     /* Clear Flag */
  }
}

/*******************************************************************************
* Function Name  : EXTI0_IRQHandler
* Description    : This function handles EXTI0 Handler.
* Input          : None
* Return         : None
*******************************************************************************/
void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
  {
      Y_key++;
      if(Y_key>1)
          Y_key=0;
    EXTI_ClearITPendingBit(EXTI_Line2);     /* Clear Flag */
  }
}

void EXTI3_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
  {
      X_key++;
      if(X_key>5)
          X_key=0;
    EXTI_ClearITPendingBit(EXTI_Line3);     /* Clear Flag */
  }
}


void EXTI4_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
  {
      if(flag_InFR==0&&flag_JudgeFR==0&&flag_OpenMV==0)
      {
          if(Judge_data%2==0)
              Judge_Value=Right;
          else
              Judge_Value=Wrong;
          flag_JudgeFR=1;;//sw1
          Judge_data++;
      }
    EXTI_ClearITPendingBit(EXTI_Line4);     /* Clear Flag */
  }
}

void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line6)!=RESET)
  {
    X_key--;
    if(X_key==255)
        X_key=5;
    EXTI_ClearITPendingBit(EXTI_Line6);     /* Clear Flag */
  }else {
      if(EXTI_GetITStatus(EXTI_Line5)!=RESET)
        {

          if(flag_InFR==0&&flag_JudgeFR==0&&flag_OpenMV==0)
          {
              if(Add_data%2==1)
                  Add_Value=Right;
              else
                  Add_Value=Wrong;
              flag_InFR=1;//sw2
              Add_data++;
          }
          EXTI_ClearITPendingBit(EXTI_Line5);     /* Clear Flag */
        }
}
}

void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line13)!=RESET)
  {
      flag_enter=1;
    EXTI_ClearITPendingBit(EXTI_Line13);     /* Clear Flag */
  }
}


