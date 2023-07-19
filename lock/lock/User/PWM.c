/*
 * PWM.c
 *
 *  Created on: 2022Äê6ÔÂ26ÈÕ
 *      Author: hp
 */

#include "debug.h"
#include "PWM.h"


uint16_t speed=500;
float Angle;
void initPwm(void)

{

    GPIO_InitTypeDef GPIO_InitStructure={0};

        TIM_OCInitTypeDef TIM_OCInitStructure={0};

        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

        RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE );

        RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;

        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

        GPIO_Init( GPIOB, &GPIO_InitStructure );

        TIM_TimeBaseInitStructure.TIM_Period = 20000-1;

        TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;

        TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

        TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;

        TIM_TimeBaseInit( TIM3, &TIM_TimeBaseInitStructure);

        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;

        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

        TIM_OCInitStructure.TIM_Pulse = 0;

        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

        TIM_OC3Init( TIM3, &TIM_OCInitStructure );

        TIM_OC4Init( TIM3, &TIM_OCInitStructure );

        TIM_CtrlPWMOutputs(TIM3, ENABLE );

        TIM_OC3PreloadConfig( TIM3, TIM_OCPreload_Disable );

        TIM_OC4PreloadConfig( TIM3, TIM_OCPreload_Disable );

        TIM_ARRPreloadConfig( TIM3, ENABLE );

        TIM_Cmd( TIM3, ENABLE );

}


//void foward(void)
//
//{
//
//    GPIO_WriteBit(GPIOE, GPIO_Pin_13,Bit_RESET);
//
//    GPIO_WriteBit(GPIOE, GPIO_Pin_15,Bit_RESET);
//
//    TIM_SetCompare3(TIM3, speed);
//
//    TIM_SetCompare4(TIM3, speed);
//
//}
void Servo_SetAngle(float Angle)
{
    TIM_SetCompare3(TIM3,Angle / 180 * 2000 + 500);
}


void Open_door(void)
{
    Servo_SetAngle(50);

           Delay_Ms(2000);

           Servo_SetAngle(0);
           //speed=speed+1000;

}

//void Close_door(void)
//{
//    Set_PWM_Dutycycle(TIM3_CH4,250);
//}
