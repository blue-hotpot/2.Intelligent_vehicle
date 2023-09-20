#ifndef __CAR_MOVE_H__
#define __CAR_MOVE_H__

#include "main.h"
#include "tim.h"
#include "gpio.h"
#define   SG90_Right_90     __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,5)		//��ת90��
//#define   SG90_Right_45		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,10)		
//#define   SG90_Front		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,15)		//�������
//#define   SG90_Left_45		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,20)		//��ת45��
#define   SG90_Left_90		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,25)
#define Right_Light HAL_GPIO_ReadPin(Right_GPIO_Port,Right_Pin)
void SG90_Left_45(void);
void SG90_Front(void);
void SG90_Right_45(void);
#define Left_Light HAL_GPIO_ReadPin(Left_GPIO_Port, Left_Pin)
// ��ת
void Car_Right(void);
// ��ת
void Car_Left(void);
// ����
void Car_Back(void);
// ǰ��
void Car_Go(void);
// ֹͣ
void Car_Stop(void);
// ����С������
void Car_Dir_Com(uint8_t CarCommand);
// ѭ��
void Car_XunJi(void);
// �������������뺯��
long long Senor_Using(void);

#endif /* __CAR_MOVE_H__ */
