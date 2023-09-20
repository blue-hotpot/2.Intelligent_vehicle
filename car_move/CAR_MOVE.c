#include "CAR_MOVE.h"
#include "tim.h"
uint8_t dirInc = 1;  // 脉宽变化方向 1 = 递增，0 = 递减
uint16_t PulseWidth = 0;  // 脉宽
uint8_t a = 0;

// 前进
void Car_Go(void)
{
	
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_SET);
}


// 后退
void Car_Back(void)
{
	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, GPIO_PIN_SET);
}
 
// 左转
void Car_Left(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,50);
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_SET);
} 
 
// 右转
void Car_Right(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,50);
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);

	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_SET);
}
// 停止
void Car_Stop(void)
{
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_RESET);

}

// 定义一个控制小车方向的函数，
// CarCommand参数是控制小车的命，1->前进，2->后退，3->左转，4->右转
void Car_Dir_Com(uint8_t CarCommand)
{
	if(CarCommand == 1)
		Car_Go();  // 前进
	if(CarCommand == 2)
		Car_Back();  // 后退
	if(CarCommand == 3)
		Car_Left();  // 左转
	if(CarCommand == 4)
		Car_Right();  // 右转
}
// 循迹
void Car_XunJi(void)
{
	if(Right_Light == GPIO_PIN_SET)  // 右侧检测到黑线
	{
		if(Left_Light == GPIO_PIN_SET)  // 左侧检测到黑线
		{
			Car_Go();  // 同时检测到黑线就直行
		}
		else
		{
			Car_Right();  // 只有右侧检测到黑线，右转
		}
		
	}
	if(Left_Light == GPIO_PIN_SET)
	{
		Car_Left();  // 只有左侧检测到黑线，左转
	}	
	else
	{
		Car_Go();  // 左右两侧都没有检测到黑线救直行
	}
}
void SG90_Right_45(void)
{
//	HAL_TIM_Base_Start_IT(&htim3);
//	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
	a = 1;
}

void SG90_Front(void)
{
//	HAL_TIM_Base_Start_IT(&htim3);
//	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
	a = 2;
}

void SG90_Left_45(void)
{
//	HAL_TIM_Base_Start_IT(&htim3);
//	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
	a = 3;
}
// 重新实现定时器的回调函数
/* TIM3 init function */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	// 舵机的回调函数，使舵机转向
	if(htim->Instance == TIM3)
	{
		
		if(a == 1)
		{
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,10);
		}
		if(a == 2)
		{
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,15);
		}
		if(a == 3)
		{
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,20);
		}
//		if(dirInc == 1)
//		{
//			PulseWidth ++;
//			if(PulseWidth>=24)
//			{
//				PulseWidth = 24;
//				dirInc = 0;
//			}
//		}
//		if(dirInc == 0)
//		{
//			PulseWidth --;
//			if(PulseWidth <=1)
//			{
//				PulseWidth = 1;
//				dirInc = 1;
//			}
//		}
		// 这个函数用来设置CCR寄存器的值，即修改PWM波的占空比
//		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, PulseWidth);
	}
}

// 使用TIM4通道1的输入捕获功能测量从发出信号到接收信号所需要的时间
// ，接收到信号后将这个时间放入回调函数进行计算得出距离
//2、给模块TRIG端口发送大于10us的高电平信号，当收、收到ECHO回响信号是，打开定时器开始定时；
//3、当回响信号消失，关闭定时器；
//4、通过定时器定时时间来确定距离

uint8_t TIM4CH1_CAP_STA = 0;                        // 输入捕获状态
uint16_t TIM4CH1_CAP_VAL;                           // 输入捕获值
// 中断服务函数里面会自动调用这个回调函数，这个是定时器更新中断处理的函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM4)                      // 判断定时器4是否发生中断
    {
        if((TIM4CH1_CAP_STA & 0X80) == 0)           // 还未成功捕获
        {
            if(TIM4CH1_CAP_STA & 0X40)              // 已经捕获到高电平
            {		
                if((TIM4CH1_CAP_STA & 0X3F) == 0X3F)// 高电平时间太长了，做溢出处理
                {	
                    TIM4CH1_CAP_STA |= 0X80;        // 标记为完成一次捕获
                    TIM4CH1_CAP_VAL += 1;       // 计数器值
                }
                else
                {
                    TIM4CH1_CAP_STA++;              // 若没有溢出，就只让TIM5CH1_CAP_STA自加
                }                
            }	
        }
    }
}

// 定时器输入捕获中断处理回调函数，该函数在 HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim) 中会被调用
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if((TIM4CH1_CAP_STA & 0X80) == 0)               // 还未成功捕获
    {
		if(TIM4CH1_CAP_STA & 0X40)                  // 捕获到一个下降沿
        {		
			TIM4CH1_CAP_STA |= 0X80;	            // 标记成功捕获到一次高电平脉宽
			TIM4CH1_CAP_VAL = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_1); // 获取当前的计数器值
			TIM_RESET_CAPTUREPOLARITY(&htim4, TIM_CHANNEL_1);	                // 清除原来的设置		
			TIM_SET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_1, TIM_ICPOLARITY_RISING);// 设置上升沿捕获
		}
		else
        {
			TIM4CH1_CAP_STA = 0;                    // 清空自定义的状态寄存器
			TIM4CH1_CAP_VAL = 0;                    // 清空捕获值
			TIM4CH1_CAP_STA |= 0X40;	            // 标记捕获到上升沿
			__HAL_TIM_DISABLE(&htim4);              // 关闭定时器
			__HAL_TIM_SET_COUNTER(&htim4, 0);       // 计数器值清零
			TIM_RESET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_1);	// 一定要先清除原来的设置	！！			
			TIM_SET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);   // 设置下降沿捕获
			__HAL_TIM_ENABLE(&htim4);               // 使能定时器		
		}	
	}
}
// 超声波测量距离函数
long long Senor_Using(void)
{
	long long temp = 0;// 定义一个变量用以存储捕获到的时间 long long型是为了防止数据溢出
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_RESET);
		
	HAL_Delay(500);
  if(TIM4CH1_CAP_STA & 0X80)    // 完成一次高电平捕获
  {
		temp = TIM4CH1_CAP_STA & 0X3F;
		temp *= 1000;            // 溢出总时间
		temp = (temp+TIM4CH1_CAP_VAL)/58.0;	// 总的高电平时间
//		printf("High level duration:%lld cm\r\n",temp);
		TIM4CH1_CAP_STA = 0;		// 准备下一次捕获
	}
	return temp;
}
