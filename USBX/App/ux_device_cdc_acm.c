/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ux_device_cdc_acm.c
  * @author  MCD Application Team
  * @brief   USBX Device applicative file
  ******************************************************************************
    * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "ux_device_cdc_acm.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
UX_SLAVE_CLASS_CDC_ACM  *cdc_acm;
UX_SLAVE_CLASS_CDC_ACM  *cdc2_acm;

uint8_t cdc_acm_buffer[] = "MY CDC INSTANCE 1 - Package: x \r\n";
uint8_t cdc2_acm_buffer[] = "MY CDC INSTANCE 2 - Package: x \r\n";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  USBD_CDC_ACM_Activate
  *         This function is called when insertion of a CDC ACM device.
  * @param  cdc_acm_instance: Pointer to the cdc acm class instance.
  * @retval none
  */
VOID USBD_CDC_ACM_Activate(VOID *cdc_acm_instance)
{
  /* USER CODE BEGIN USBD_CDC_ACM_Activate */
	cdc_acm = (UX_SLAVE_CLASS_CDC_ACM *)cdc_acm_instance;
  /* USER CODE END USBD_CDC_ACM_Activate */

  return;
}

/**
  * @brief  USBD_CDC_ACM_Deactivate
  *         This function is called when extraction of a CDC ACM device.
  * @param  cdc_acm_instance: Pointer to the cdc acm class instance.
  * @retval none
  */
VOID USBD_CDC_ACM_Deactivate(VOID *cdc_acm_instance)
{
  /* USER CODE BEGIN USBD_CDC_ACM_Deactivate */
  UX_PARAMETER_NOT_USED(cdc_acm_instance);
  /* USER CODE END USBD_CDC_ACM_Deactivate */

  return;
}

/**
  * @brief  USBD_CDC_ACM_ParameterChange
  *         This function is invoked to manage the CDC ACM class requests.
  * @param  cdc_acm_instance: Pointer to the cdc acm class instance.
  * @retval none
  */
VOID USBD_CDC_ACM_ParameterChange(VOID *cdc_acm_instance)
{
  /* USER CODE BEGIN USBD_CDC_ACM_ParameterChange */
  UX_PARAMETER_NOT_USED(cdc_acm_instance);
  /* USER CODE END USBD_CDC_ACM_ParameterChange */

  return;
}

/* USER CODE BEGIN 1 */
VOID USBD_CDC2_ACM_Activate(VOID *cdc_acm_instance)
{
	cdc2_acm = (UX_SLAVE_CLASS_CDC_ACM*) cdc_acm_instance;
}

VOID USBD_CDC2_ACM_Deactivate(VOID *cdc_acm_instance)
{

	return;
}

VOID USBD_CDC2_ACM_ParameterChange(VOID *cdc_acm_instance)
{

	return;
}

VOID usbx_cdc_acm_write_thread_entry(ULONG thread_input)
{

	ULONG actual_length, buffsize;
	UX_SLAVE_DEVICE *device;
	uint8_t index, counter = 48;

	UX_PARAMETER_NOT_USED(thread_input);

	for(index = 0; index < sizeof(cdc_acm_buffer); index++)
		if(cdc_acm_buffer[index] == 'x')
			break;

	device = &_ux_system_slave->ux_system_slave_device;

	buffsize = sizeof(cdc_acm_buffer);

	while(1)
	{
		if ((device->ux_slave_device_state == UX_DEVICE_CONFIGURED) && (cdc_acm != UX_NULL))
		{
			cdc_acm_buffer[index] = counter;

			ux_device_class_cdc_acm_write(cdc_acm, (UCHAR *)(&cdc_acm_buffer[0]), buffsize, &actual_length);

			if(counter == 57)
				counter = 48;
			else
				counter++;
		}
		ux_utility_thread_sleep(20);
	}
}


VOID usbx_cdc2_acm_write_thread_entry(ULONG thread_input)
{
	ULONG actual_length, buffsize;
	UX_SLAVE_DEVICE *device;
	uint8_t index, counter = 48;

	UX_PARAMETER_NOT_USED(thread_input);

	for(index = 0; index < sizeof(cdc2_acm_buffer); index++)
			if(cdc2_acm_buffer[index] == 'x')
				break;

	device = &_ux_system_slave->ux_system_slave_device;

	buffsize = sizeof(cdc2_acm_buffer);

	while(1)
	{
		if ((device->ux_slave_device_state == UX_DEVICE_CONFIGURED) && (cdc2_acm != UX_NULL))
		{
			cdc2_acm_buffer[index] = counter;

			ux_device_class_cdc_acm_write(cdc2_acm, (UCHAR *)(&cdc2_acm_buffer[0]), buffsize, &actual_length);

			if(counter == 57)
				counter = 48;
			else
				counter++;
		}

		ux_utility_thread_sleep(20);
	}
}
/* USER CODE END 1 */
