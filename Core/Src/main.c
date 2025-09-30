/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../lvgl/lvgl.h"
#include "../lvgl/ui/ui.h"
#include "../XPT2064/XPT2064.h"
#include "../XPT2064/lv_drv.h"
#include "../ILI9341/core.h"
#include "../ILI9341/lv_driver.h"
#include <stdio.h>
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
ADC_HandleTypeDef hadc1;

CAN_HandleTypeDef hcan1;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi2_tx;

/* USER CODE BEGIN PV */
static void MX_NVIC_Init(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_ADC1_Init(void);
static void MX_CAN1_Init(void);
/* USER CODE BEGIN PFP */
CAN_FilterTypeDef sFilterConfig;
CAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[8];

CAN_TxHeaderTypeDef   TxHeader;
uint8_t               TxData[8];
uint32_t              TxMailbox;
uint8_t counter;
static lv_disp_draw_buf_t disp_buf;

#define ILI_SCR_HORIZONTAL 320
#define ILI_SCR_VERTICAL   240
#define BUFFOR_SCR_ROWS 24

static lv_color_t buf_1[ILI_SCR_HORIZONTAL * BUFFOR_SCR_ROWS] ;
static lv_color_t buf_2[ILI_SCR_HORIZONTAL * BUFFOR_SCR_ROWS] ;
static lv_disp_drv_t disp_drv;

uint8_t battery_level;
uint8_t velocity=0;
uint32_t lastupdate = 0;
bool left_blink_active = false;
bool right_blink_active = false;

lv_color_t new_color;
lv_chart_series_t * ser1;

static void buttonAB_handler(lv_event_t * e)
 {
     lv_event_code_t code = lv_event_get_code(e);
     if (code == LV_EVENT_CLICKED) {
    	 memcpy(TxData, "RAB", 3);
    	 char buf[16]= "0    0-0    0";
    	 lv_label_set_text(objects.ab_status, buf);
    	 lv_obj_set_style_text_align(objects.ab_status, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    	 HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
     }
}
static void buttonReturnHome_handler(lv_event_t * e)
{
     lv_event_code_t code = lv_event_get_code(e);
     if (code == LV_EVENT_CLICKED) {
    	 loadScreen(SCREEN_ID_MAIN);
     }
}
 static void gesture_event_handler(lv_event_t * e) {
	  lv_indev_wait_release(lv_indev_get_act());
	  lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());

      switch(dir) {
          case LV_DIR_BOTTOM: // Swipe down
        	  loadScreen(SCREEN_ID_STATS_SYSTEM);
              break;
          default:
              break;
      }
  }
static void update_display_task(void) {

	lv_color_t new_color = (velocity<120 ? lv_palette_main(LV_PALETTE_GREEN) :
	                		velocity<200 ? lv_palette_main(LV_PALETTE_YELLOW) :
	                						lv_palette_main(LV_PALETTE_RED));

	lv_obj_set_style_arc_color(objects.velocity_curve, new_color, LV_PART_INDICATOR);
	lv_arc_set_value(objects.velocity_curve, velocity);
	lv_obj_set_style_text_align(objects.velocity_digit, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
	lv_obj_set_style_text_color(objects.velocity_digit,new_color , LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_label_set_text_fmt(objects.velocity_digit, "%d", velocity);
  }

static void update_battery_arc(lv_timer_t * t) {
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	float volt = HAL_ADC_GetValue(&hadc1) * 3.3f/4095.0f * 4.24f;
	float pct  = (volt - 8.25f)/(12.6f - 8.25f) * 100.0f;
	battery_level = (uint8_t)pct;
	HAL_ADC_Stop(&hadc1);
	lv_arc_set_value(objects.fuel, 100- battery_level);
}

static void update_battery_chart(lv_timer_t * t) {
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	float volt = HAL_ADC_GetValue(&hadc1) * 3.3f/4095.0f * 4.24f;
	float pct  = (volt - 8.25f)/(12.6f - 8.25f) * 100.0f;
	battery_level = (uint8_t)pct;
	HAL_ADC_Stop(&hadc1);
    lv_chart_set_next_value(objects.battery_db, ser1, battery_level);
    lv_chart_refresh(objects.battery_db);

}
static void update_left_right_sign(lv_timer_t * t) {
	static bool blink_state = false;
	blink_state = !blink_state;

	if (left_blink_active) {
	    if (blink_state)
	        lv_obj_clear_flag(objects.left_sign, LV_OBJ_FLAG_HIDDEN);
	    else
	        lv_obj_add_flag(objects.left_sign, LV_OBJ_FLAG_HIDDEN);
	} else {
	    lv_obj_add_flag(objects.left_sign, LV_OBJ_FLAG_HIDDEN);
	}

	if (right_blink_active) {
	    if (blink_state)
	        lv_obj_clear_flag(objects.right_sign, LV_OBJ_FLAG_HIDDEN);
	    else
	        lv_obj_add_flag(objects.right_sign, LV_OBJ_FLAG_HIDDEN);
	} else {
	    lv_obj_add_flag(objects.right_sign, LV_OBJ_FLAG_HIDDEN);
	}
}
 // ---------------------------------
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, RxData)==HAL_OK){
		char buf_id[32];
		char buf_data[32];
		snprintf(buf_id, sizeof(buf_id), "Income ID: %02lX", RxHeader.StdId);
		snprintf(buf_data, sizeof(buf_data), "Data: %02X %02X %02X", RxData[2], RxData[1], RxData[0]);

		lv_label_set_text(objects.message_stat_1, buf_id);
		lv_label_set_text(objects.message_stat_2, buf_data);

		if(RxHeader.StdId == 0x00){
			uint8_t msg = RxData[0];
			uint8_t b2 = (msg >> 2) & 0x01;
			uint8_t b1 = (msg >> 1) & 0x01;
			uint8_t b0 = msg & 0x01;
			char buf[16];
			snprintf(buf, sizeof(buf), "%d    %d-%d    %d", b2, b1,b1, b0);
			lv_label_set_text(objects.ab_status, buf);
			lv_obj_set_style_text_align(objects.ab_status, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

		}
		if(RxHeader.StdId == 0x01){
			velocity = RxData[0];
			char buf;
			switch (RxData[1]){
				case 1: buf = 'R'; break;
				case 2: buf = 'N'; break;
				case 3: buf = 'D'; break;
				default: buf = 'P'; break;
			}
			lv_label_set_text_fmt(objects.gear_status, "%c", buf);
			lv_label_set_text_fmt(objects.gear_lever, "%c", buf);
			lv_label_set_text_fmt(objects.velocity_stat_digit, "%d", velocity);
			update_display_task();
			if(RxData[2] == 1){
				lv_obj_clear_flag(objects.brake_sign, LV_OBJ_FLAG_HIDDEN);
				lv_label_set_text(objects.brake_digit, "Pressed");
			}else{
				lv_obj_add_flag(objects.brake_sign, LV_OBJ_FLAG_HIDDEN);
				lv_label_set_text(objects.brake_digit, "Released");
			}
			lv_arc_set_value(objects.rpm_curve, RxData[3]);
		}
		if(RxHeader.StdId == 0x02){
			uint8_t msg = RxData[0];

			// Extract individual bits
			uint8_t b6 = (msg >> 6) & 0x01;
			uint8_t b5 = (msg >> 5) & 0x01;
			uint8_t b4 = (msg >> 4) & 0x01;
			uint8_t b3 = (msg >> 3) & 0x01;
			uint8_t b2 = (msg >> 2) & 0x01;
			uint8_t b1 = (msg >> 1) & 0x01;
			uint8_t b0 = msg & 0x01;
			lv_label_set_text_fmt(objects.light_status, "%d%d%d%d%d%d%d",
									b6,b5,b4,b3,b2,b1,b0);
			// Headlight Modes (Auto, Low, High) — only one should show
			if (b0) {
			    lv_obj_clear_flag(objects.autolight, LV_OBJ_FLAG_HIDDEN);
			    lv_obj_add_flag(objects.highbeam, LV_OBJ_FLAG_HIDDEN);
			    lv_obj_add_flag(objects.lowbeam, LV_OBJ_FLAG_HIDDEN);
			} else if (b1) {
			    lv_obj_clear_flag(objects.lowbeam, LV_OBJ_FLAG_HIDDEN);
			    lv_obj_add_flag(objects.highbeam, LV_OBJ_FLAG_HIDDEN);
			    lv_obj_add_flag(objects.autolight, LV_OBJ_FLAG_HIDDEN);
			} else if (b2) {
			    lv_obj_clear_flag(objects.highbeam, LV_OBJ_FLAG_HIDDEN);
			    lv_obj_add_flag(objects.lowbeam, LV_OBJ_FLAG_HIDDEN);
			    lv_obj_add_flag(objects.autolight, LV_OBJ_FLAG_HIDDEN);
			} else {
			    // All off
			    lv_obj_add_flag(objects.autolight, LV_OBJ_FLAG_HIDDEN);
			    lv_obj_add_flag(objects.lowbeam, LV_OBJ_FLAG_HIDDEN);
			    lv_obj_add_flag(objects.highbeam, LV_OBJ_FLAG_HIDDEN);
			}

			// Position Light (b3)
			if (b3) {
			    lv_obj_clear_flag(objects.position_light, LV_OBJ_FLAG_HIDDEN);
			} else {
			    lv_obj_add_flag(objects.position_light, LV_OBJ_FLAG_HIDDEN);
			}

			// Left Turn Signal (b4) — toggle for blinking effect
			if (b4 == 1)
			    left_blink_active = true;
			else
			    left_blink_active = false;

			if (b5 == 1)
			    right_blink_active = true;
			else
			    right_blink_active = false;

			// Hazard Warning (b6)
			if (b6) {
			    lv_obj_clear_flag(objects.hazard_sign, LV_OBJ_FLAG_HIDDEN);
			} else {
			    lv_obj_add_flag(objects.hazard_sign, LV_OBJ_FLAG_HIDDEN);
			}
	}
}
}


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
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_ADC1_Init();
  MX_CAN1_Init();
  /* USER CODE BEGIN 2 */
  MX_NVIC_Init();
   /* USER CODE BEGIN 2 */
  HAL_CAN_Start(&hcan1);
  TxHeader.StdId = 0x03;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.DLC = 8;
  TxHeader.TransmitGlobalTime = DISABLE;

  sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
  sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.SlaveStartFilterBank = 14;
  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterIdHigh = 0;
  //   sFilterConfig.FilterIdLow = 0;
  sFilterConfig.FilterMaskIdHigh = 0x7FC << 5;
  //   sFilterConfig.FilterMaskIdLow = 0x0000;
  HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING); // Enable FIFO0 message pending interrupt

  ILI9341_Init();
  XPT2046_Init(&hspi1, EXTI9_5_IRQn);
  HAL_Delay(30);

  lv_init();
  lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, ILI_SCR_HORIZONTAL * BUFFOR_SCR_ROWS);
  lv_disp_drv_init(&disp_drv);              /*Basic initialization*/
  disp_drv.draw_buf = &disp_buf;            /*Set an initialized buffer*/
  disp_drv.flush_cb = ILI9341_flush;        /*Set a flush callback to draw to the display*/
  disp_drv.hor_res = ILI_SCR_HORIZONTAL;    /*Set the horizontal resolution in pixels*/
  disp_drv.ver_res = ILI_SCR_VERTICAL;      /*Set the vertical resolution in pixels*/
  lv_disp_drv_register(&disp_drv);          /*Register the driver and save the created display objects*/

  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type =LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = lvXPT2064_Read;
  lv_indev_drv_register(&indev_drv);
  HAL_Delay(10);


  ui_init();
  lv_obj_set_width(objects.velocity_digit, 28);
  lv_chart_set_type(objects.battery_db, LV_CHART_TYPE_LINE);
  ser1 = lv_chart_add_series(objects.battery_db, lv_palette_main(LV_PALETTE_PURPLE), LV_CHART_AXIS_PRIMARY_Y);

//  lv_obj_add_event_cb(objects.button1, button1_handler, LV_EVENT_ALL, NULL);
//  lv_obj_add_event_cb(objects.button2, button2_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.title_stat, buttonReturnHome_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.rab_btn, buttonAB_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.main, gesture_event_handler, LV_EVENT_GESTURE, NULL);
//
//  lv_label_set_recolor(objects.message_stat_1, true);
//  lv_label_set_recolor(objects.message_stat_2, true);


  lv_timer_create(update_battery_arc, 8000, NULL);
  lv_timer_create(update_battery_chart, 24000, NULL);
  lv_timer_create(update_left_right_sign, 500, NULL);
  lv_obj_add_flag(objects.brake_sign, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.position_light, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.autolight, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.lowbeam, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.highbeam, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.hazard_sign, LV_OBJ_FLAG_HIDDEN);

  uint32_t last = HAL_GetTick();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	 // lv_task_handler();
	  uint32_t now = HAL_GetTick();
	  if (now - last >= 20) {
	      lv_task_handler();  // every 20ms = 50FPS max
	      last = now;
	  }
	  lv_tick_inc(5);
	  XPT2046_Task();

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 6;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_11TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI1_CS_Touch_GPIO_Port, SPI1_CS_Touch_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, TFT_RST_Pin|TFT_DC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : SPI1_CS_Touch_Pin */
  GPIO_InitStruct.Pin = SPI1_CS_Touch_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI1_CS_Touch_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TOUCH_IRQ_Pin */
  GPIO_InitStruct.Pin = TOUCH_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TOUCH_IRQ_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TFT_CS_Pin */
  GPIO_InitStruct.Pin = TFT_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TFT_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TFT_RST_Pin TFT_DC_Pin */
  GPIO_InitStruct.Pin = TFT_RST_Pin|TFT_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* EXTI9_5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
  /* DMA1_Stream4_IRQn interrupt configuration */
  NVIC_SetPriority(DMA1_Stream4_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(DMA1_Stream4_IRQn);
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == TOUCH_IRQ_Pin)
	{
		XPT2046_IRQ();
	}
}
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
