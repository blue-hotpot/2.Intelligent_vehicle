#include "CAR_MOVE.h"
#include "tim.h"
uint8_t dirInc = 1;  // ����仯���� 1 = ������0 = �ݼ�
uint16_t PulseWidth = 0;  // ����
uint8_t a = 0;

// ǰ��
void Car_Go(void)
{
	
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_SET);
}


// ����
void Car_Back(void)
{
	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, GPIO_PIN_SET);
}
 
// ��ת
void Car_Left(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,50);
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_SET);
} 
 
// ��ת
void Car_Right(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,50);
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);

	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_SET);
}
// ֹͣ
void Car_Stop(void)
{
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_RESET);

}

// ����һ������С������ĺ�����
// CarCommand�����ǿ���С��������1->ǰ����2->���ˣ�3->��ת��4->��ת
void Car_Dir_Com(uint8_t CarCommand)
{
	if(CarCommand == 1)
		Car_Go();  // ǰ��
	if(CarCommand == 2)
		Car_Back();  // ����
	if(CarCommand == 3)
		Car_Left();  // ��ת
	if(CarCommand == 4)
		Car_Right();  // ��ת
}
// ѭ��
void Car_XunJi(void)
{
	if(Right_Light == GPIO_PIN_SET)  // �Ҳ��⵽����
	{
		if(Left_Light == GPIO_PIN_SET)  // ����⵽����
		{
			Car_Go();  // ͬʱ��⵽���߾�ֱ��
		}
		else
		{
			Car_Right();  // ֻ���Ҳ��⵽���ߣ���ת
		}
		
	}
	if(Left_Light == GPIO_PIN_SET)
	{
		Car_Left();  // ֻ������⵽���ߣ���ת
	}	
	else
	{
		Car_Go();  // �������඼û�м�⵽���߾�ֱ��
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
// ����ʵ�ֶ�ʱ���Ļص�����
/* TIM3 init function */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	// ����Ļص�������ʹ���ת��
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
		// ���������������CCR�Ĵ�����ֵ�����޸�PWM����ռ�ձ�
//		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, PulseWidth);
	}
}

// ʹ��TIM4ͨ��1�����벶���ܲ����ӷ����źŵ������ź�����Ҫ��ʱ��
// �����յ��źź����ʱ�����ص��������м���ó�����
//2����ģ��TRIG�˿ڷ��ʹ���10us�ĸߵ�ƽ�źţ����ա��յ�ECHO�����ź��ǣ��򿪶�ʱ����ʼ��ʱ��
//3���������ź���ʧ���رն�ʱ����
//4��ͨ����ʱ����ʱʱ����ȷ������

uint8_t TIM4CH1_CAP_STA = 0;                        // ���벶��״̬
uint16_t TIM4CH1_CAP_VAL;                           // ���벶��ֵ
// �жϷ�����������Զ���������ص�����������Ƕ�ʱ�������жϴ���ĺ���
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM4)                      // �ж϶�ʱ��4�Ƿ����ж�
    {
        if((TIM4CH1_CAP_STA & 0X80) == 0)           // ��δ�ɹ�����
        {
            if(TIM4CH1_CAP_STA & 0X40)              // �Ѿ����񵽸ߵ�ƽ
            {		
                if((TIM4CH1_CAP_STA & 0X3F) == 0X3F)// �ߵ�ƽʱ��̫���ˣ����������
                {	
                    TIM4CH1_CAP_STA |= 0X80;        // ���Ϊ���һ�β���
                    TIM4CH1_CAP_VAL += 1;       // ������ֵ
                }
                else
                {
                    TIM4CH1_CAP_STA++;              // ��û���������ֻ��TIM5CH1_CAP_STA�Լ�
                }                
            }	
        }
    }
}

// ��ʱ�����벶���жϴ���ص��������ú����� HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim) �лᱻ����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if((TIM4CH1_CAP_STA & 0X80) == 0)               // ��δ�ɹ�����
    {
		if(TIM4CH1_CAP_STA & 0X40)                  // ����һ���½���
        {		
			TIM4CH1_CAP_STA |= 0X80;	            // ��ǳɹ�����һ�θߵ�ƽ����
			TIM4CH1_CAP_VAL = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_1); // ��ȡ��ǰ�ļ�����ֵ
			TIM_RESET_CAPTUREPOLARITY(&htim4, TIM_CHANNEL_1);	                // ���ԭ��������		
			TIM_SET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_1, TIM_ICPOLARITY_RISING);// ���������ز���
		}
		else
        {
			TIM4CH1_CAP_STA = 0;                    // ����Զ����״̬�Ĵ���
			TIM4CH1_CAP_VAL = 0;                    // ��ղ���ֵ
			TIM4CH1_CAP_STA |= 0X40;	            // ��ǲ���������
			__HAL_TIM_DISABLE(&htim4);              // �رն�ʱ��
			__HAL_TIM_SET_COUNTER(&htim4, 0);       // ������ֵ����
			TIM_RESET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_1);	// һ��Ҫ�����ԭ��������	����			
			TIM_SET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);   // �����½��ز���
			__HAL_TIM_ENABLE(&htim4);               // ʹ�ܶ�ʱ��		
		}	
	}
}
// �������������뺯��
long long Senor_Using(void)
{
	long long temp = 0;// ����һ���������Դ洢���񵽵�ʱ�� long long����Ϊ�˷�ֹ�������
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_RESET);
		
	HAL_Delay(500);
  if(TIM4CH1_CAP_STA & 0X80)    // ���һ�θߵ�ƽ����
  {
		temp = TIM4CH1_CAP_STA & 0X3F;
		temp *= 1000;            // �����ʱ��
		temp = (temp+TIM4CH1_CAP_VAL)/58.0;	// �ܵĸߵ�ƽʱ��
//		printf("High level duration:%lld cm\r\n",temp);
		TIM4CH1_CAP_STA = 0;		// ׼����һ�β���
	}
	return temp;
}
