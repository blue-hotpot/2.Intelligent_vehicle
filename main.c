/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "CAR_MOVE.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern uint8_t TIM4CH1_CAP_STA;
extern uint16_t TIM4CH1_CAP_VAL;


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
int fputc(int ch, FILE *f)
{
  uint8_t temp[1] = {ch};
  HAL_UART_Transmit(&huart1, temp, 1, 2);  // huart1�Ǵ���1�����ʹ������������Ҫ�����������
  return ch;
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
//	uint8_t i = 0;
	
	uint8_t length_res[10];  // ����һ��������ǰ���ľ���
//	uint8_t Car_Command= 4;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	
	printf("��������С��������Ʋ��Գ���");
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
//	Car_Dir_Com(Car_Command);		
//	Car_Go();
	HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_1);  // һ��Ҫ����TIM4ͨ��1�Ĳ����ж�
  __HAL_TIM_ENABLE_IT(&htim4,TIM_IT_UPDATE);  // һ��Ҫ����TIM4�ĸ����ж�
  printf("This is TIM_CAP test...\n");
		
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		SG90_Front();   //�������
		HAL_Delay(100);
		length_res[0] =Senor_Using();  //��ǰ���������������
		HAL_Delay(100);
		if(length_res[0]>30.00)       //���ǰ���������30cm  ǰ��
		{
			Car_Go();
		}	
				
		if(length_res[0]<30.00)     //���ǰ������С��30����  ͣ�������Ҿ���
		{
			Car_Stop();  
			SG90_Left_45();      //�����ת45�Ȳ��
			HAL_Delay(700);		
			length_res[1] =Senor_Using();    //�Ѳ�������Ž�����
			
			SG90_Right_45();     //�����ת45�Ȳ��
			HAL_Delay(700);	
			length_res[4] =Senor_Using();     //�Ѳ�������Ž�����				
				
			SG90_Front();           //�������
			HAL_Delay(100); 
			if(length_res[1]>length_res[4])    //�����ߵľ�������ұߵľ���
			{
				do                        //�������
				{
				SG90_Front();
				HAL_Delay(10);
				length_res[0] =Senor_Using();	//�ظ���ǰ���ľ���ͬʱ��ת
				HAL_Delay(10);						
				Car_Left();
				}
				while(length_res[0]<30.00);		//һֱת��ǰ���������30cm		
			}
			if(length_res[1]<length_res[4])    //����ұߵľ��������ߵľ���
			{
				do
				{
				SG90_Front();
				HAL_Delay(10);
				length_res[0] =Senor_Using();  //�ظ���ǰ���ľ���ͬʱ��ת
				HAL_Delay(10);						
				Car_Right();
				}
				while(length_res[0]<30.00);		//һֱת��ǰ���������30cm
			}
				
		}
//		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_SET);
//		HAL_Delay(1);
//		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_RESET);
//		
//		HAL_Delay(500);
//    if(TIM4CH1_CAP_STA & 0X80)    // ���һ�θߵ�ƽ����
//    {
//      temp = TIM4CH1_CAP_STA & 0X3F;
//      temp *= 1000;            // �����ʱ��
//      temp = (temp+TIM4CH1_CAP_VAL)/58.0;	// �ܵĸߵ�ƽʱ��
//      printf("High level duration:%lld cm\r\n",temp);
//      TIM4CH1_CAP_STA = 0;		// ׼����һ�β���
//		}
		
    /* USER CODE END WHILE */
		
    /* USER CODE BEGIN 3 */
  }
			
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
