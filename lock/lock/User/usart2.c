
/*
 * usart.c
 *
 *  Created on: 2022年6月9日
 *      Author: hp
 */
#include "debug.h"
#include "lcd.h"
#include "display.h"
#include "key.h"
#include "usart2.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"
//串口接收缓存区
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN];              //接收缓冲,最大USART3_MAX_RECV_LEN个字节.
u8 USART3_TX_BUF[USART3_MAX_SEND_LEN];            //发送缓冲,最大USART3_MAX_SEND_LEN字节


vu16 USART3_RX_STA=0;

void USART3_IRQHandler(void)
{
    u8 res;
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//接收到数据
    {
        res =USART_ReceiveData(USART3);
        if((USART3_RX_STA&(1<<15))==0)
        {
            if(USART3_RX_STA<USART3_MAX_RECV_LEN)   //还可以接收数据
            {
                TIM_SetCounter(TIM7,0);//计数器清空                          //计数器清空
                if(USART3_RX_STA==0)                //使能定时器7的中断
                {
                    TIM_Cmd(TIM7,ENABLE);//使能定时器7
                }
                USART3_RX_BUF[USART3_RX_STA++]=res; //记录接收到的值
                }else
                {
                    USART3_RX_STA|=1<<15;               //强制标记接收完成
                }
        }
    }

}

//初始化IO 串口2
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率

void usart3_init(u32 bound)
{
//    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    //开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    /* USART3 TX-->PD8  RX-->PD9 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           //RX，输入上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = bound;                    // 波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     // 数据位 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1;          // 停止位 1
    USART_InitStructure.USART_Parity = USART_Parity_No;             // 无校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件流控
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //使能 RX 和 TX

    USART_Init(USART3, &USART_InitStructure);

    USART_Cmd(USART3, ENABLE);                                        //开启UART

    //使能接收中断
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断

    //设置中断优先级
//    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //子优先级3
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
//    NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化VIC寄存器
//
//    TIM7_Int_Init(99,7199);     //10ms中断
//    USART3_RX_STA=0;        //清零
//    TIM_Cmd(TIM7,DISABLE);          //关闭定时器7

}

void u2_printf(char* fmt,...)
{
    u16 i,j;
    va_list ap;
    va_start(ap,fmt);
    vsprintf((char*)USART3_TX_BUF,fmt,ap);
    va_end(ap);
    i=strlen((const char*)USART3_TX_BUF);       //此次发送数据的长度
    for(j=0;j<i;j++)                            //循环发送数据
    {
      while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕
        USART_SendData(USART3,USART3_TX_BUF[j]);
    }
}
