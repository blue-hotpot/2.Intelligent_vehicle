#ifndef __CAR_MOVE_H__
#define __CAR_MOVE_H__

#include "main.h"
#include "tim.h"
#include "gpio.h"
#define   SG90_Right_90     __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,5)		//右转90度
//#define   SG90_Right_45		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,10)		
//#define   SG90_Front		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,15)		//舵机摆正
//#define   SG90_Left_45		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,20)		//左转45度
#define   SG90_Left_90		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,25)
#define Right_Light HAL_GPIO_ReadPin(Right_GPIO_Port,Right_Pin)
void SG90_Left_45(void);
void SG90_Front(void);
void SG90_Right_45(void);
#define Left_Light HAL_GPIO_ReadPin(Left_GPIO_Port, Left_Pin)
// 右转
void Car_Right(void);
// 左转
void Car_Left(void);
// 后退
void Car_Back(void);
// 前进
void Car_Go(void);
// 停止
void Car_Stop(void);
// 控制小车方向
void Car_Dir_Com(uint8_t CarCommand);
// 循迹
void Car_XunJi(void);
// 超声波测量距离函数
long long Senor_Using(void);

#endif /* __CAR_MOVE_H__ */
