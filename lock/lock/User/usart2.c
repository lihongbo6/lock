
/*
 * usart.c
 *
 *  Created on: 2022��6��9��
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
//���ڽ��ջ�����
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN];              //���ջ���,���USART3_MAX_RECV_LEN���ֽ�.
u8 USART3_TX_BUF[USART3_MAX_SEND_LEN];            //���ͻ���,���USART3_MAX_SEND_LEN�ֽ�


vu16 USART3_RX_STA=0;

void USART3_IRQHandler(void)
{
    u8 res;
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//���յ�����
    {
        res =USART_ReceiveData(USART3);
        if((USART3_RX_STA&(1<<15))==0)
        {
            if(USART3_RX_STA<USART3_MAX_RECV_LEN)   //�����Խ�������
            {
                TIM_SetCounter(TIM7,0);//���������                          //���������
                if(USART3_RX_STA==0)                //ʹ�ܶ�ʱ��7���ж�
                {
                    TIM_Cmd(TIM7,ENABLE);//ʹ�ܶ�ʱ��7
                }
                USART3_RX_BUF[USART3_RX_STA++]=res; //��¼���յ���ֵ
                }else
                {
                    USART3_RX_STA|=1<<15;               //ǿ�Ʊ�ǽ������
                }
        }
    }

}

//��ʼ��IO ����2
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������

void usart3_init(u32 bound)
{
//    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    //����ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    /* USART3 TX-->PD8  RX-->PD9 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           //RX����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = bound;                    // ������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     // ����λ 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1;          // ֹͣλ 1
    USART_InitStructure.USART_Parity = USART_Parity_No;             // ��У��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��Ӳ������
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //ʹ�� RX �� TX

    USART_Init(USART3, &USART_InitStructure);

    USART_Cmd(USART3, ENABLE);                                        //����UART

    //ʹ�ܽ����ж�
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�

    //�����ж����ȼ�
//    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //�����ȼ�3
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
//    NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ���
//
//    TIM7_Int_Init(99,7199);     //10ms�ж�
//    USART3_RX_STA=0;        //����
//    TIM_Cmd(TIM7,DISABLE);          //�رն�ʱ��7

}

void u2_printf(char* fmt,...)
{
    u16 i,j;
    va_list ap;
    va_start(ap,fmt);
    vsprintf((char*)USART3_TX_BUF,fmt,ap);
    va_end(ap);
    i=strlen((const char*)USART3_TX_BUF);       //�˴η������ݵĳ���
    for(j=0;j<i;j++)                            //ѭ����������
    {
      while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������
        USART_SendData(USART3,USART3_TX_BUF[j]);
    }
}
