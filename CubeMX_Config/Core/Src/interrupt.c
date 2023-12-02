#include "interrupt.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==&htim6) // 10Hz
    {
      connected_flag = false;
    }

    if((htim==&htim7)&&(remote_already_seen)) // 400Hz
    {
      control();
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart==&huart4)
  {
    TIM6->CNT=0;
    remote_already_seen = true;
    connected_flag = true;
    HAL_UART_Receive_IT (&huart4, transmit, 7);
  }
}