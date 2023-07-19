/*
 * key.h
 *
 *  Created on: 2022Äê6ÔÂ6ÈÕ
 *      Author: hp
 */

#ifndef KEY_H_
#define KEY_H_

enum Judge
{
     Right=1,
     Wrong
};

extern u8 keyboard[2][6];
extern u8 num;
extern u8 X_key;
extern u8 Y_key;
extern u8 flag_enter;
extern u8 flag_JudgeFR;
extern u8 flag_InFR;
extern u8 flag_OpenMV;
extern u8 flag_dispaly_OpenMV;
extern u8 Judge_OpenMV;

extern enum Judge Judge_Value;
extern enum Judge Add_Value;
extern enum Judge OpenMV_Value;

void EXTI0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI9_5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI15_10_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void EXTI_INT_INIT(void);



#endif /* KEY_H_ */
