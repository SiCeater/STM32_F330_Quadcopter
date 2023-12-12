#include "imu.h"

void check_imu()
{
  uint8_t RxData=0;
  read_register(MPUREG_WHOAMI|READ,&RxData);
  if(RxData==0x75)
  {
    //ici un indicateur physique ex buzzer
    if(debug)
      print_to_console("\nSPI IMU               : detected",33);
  }
}

void self_test_gyro()
{
  char tab [4] = {0};
  uint8_t xg_st_data = 0;
  uint8_t yg_st_data = 0;
  uint8_t zg_st_data = 0;

  read_register(MPUREG_SELF_TEST_X_GYRO,&xg_st_data);
  read_register(MPUREG_SELF_TEST_Y_GYRO,&yg_st_data);
  read_register(MPUREG_SELF_TEST_Z_GYRO,&zg_st_data);

  // ici traitement de la reponse plus indicateur physique buzzer

  if(debug)
  {
    print_to_console("\nIMU gyro self test X  : ",25);
    sprintf(tab,"%d",xg_st_data);
    print_to_console(tab,3);

    print_to_console("\nIMU gyro self test Y  : ",25);
    sprintf(tab,"%d",yg_st_data);
    print_to_console(tab,3);

    print_to_console("\nIMU gyro self test Z  : ",25);
    sprintf(tab,"%d",zg_st_data);
    print_to_console(tab,3);
  }
}
void self_test_accel()
{
  char tab [4] = {0};
  uint8_t xa_st_data = 0;
  uint8_t ya_st_data = 0;
  uint8_t za_st_data = 0;

  read_register(MPUREG_SELF_TEST_X_ACCEL,&xa_st_data);
  read_register(MPUREG_SELF_TEST_Y_ACCEL,&ya_st_data);
  read_register(MPUREG_SELF_TEST_Z_ACCEL,&za_st_data);

  // ici traitement de la reponse plus indicateur physique buzzer

  if(debug)
  {
    print_to_console("\nIMU accel self test X : ",25);
    sprintf(tab,"%d",xa_st_data);
    print_to_console(tab,3);

    print_to_console("\nIMU accel self test Y : ",25);
    sprintf(tab,"%d",ya_st_data);
    print_to_console(tab,3);

    print_to_console("\nIMU accel self test Z : ",25);
    sprintf(tab,"%d",za_st_data);
    print_to_console(tab,3);
  }
}

void read_register(uint8_t addr , uint8_t* result)
{
  uint8_t RxData=0;
  addr|=READ;
  HAL_GPIO_WritePin(gyro_CS_GPIO_Port,gyro_CS_Pin,GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi1, &addr, 1,1000);
  HAL_GPIO_WritePin(gyro_CS_GPIO_Port,gyro_CS_Pin,GPIO_PIN_SET);
  HAL_GPIO_WritePin(gyro_CS_GPIO_Port,gyro_CS_Pin,GPIO_PIN_RESET);
  HAL_SPI_Receive(&hspi1, &RxData, 1,1000);
  HAL_GPIO_WritePin(gyro_CS_GPIO_Port,gyro_CS_Pin,GPIO_PIN_SET);
  *result=RxData;
}

