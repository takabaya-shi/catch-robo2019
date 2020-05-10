/*
 * controller.c
 *
 *  Created on: 2019/09/07
 *      Author: tomok
 */

#include "controller.h"

extern SPI_HandleTypeDef hspi3;

//static関数プロトタイプ宣言
static float NormalizeStick(int16_t, int16_t);
static void PSControllerSelect(void);
static void PSControllerDeselect(void);
static void PSControllerWait(void);
/*
void PSControllerGetData(uint16_t *button){
	uint8_t txdata[10] = {0x01,0x42};
	uint8_t rxdata[10] = {};

	CONTROLLER_SPI_HANDLER.Init.FirstBit = SPI_FIRSTBIT_LSB;
	HAL_SPI_Init(&CONTROLLER_SPI_HANDLER);

	PSControllerSelect();
	PSControllerWait();
	for(uint8_t i =0;i<3;i++){
		HAL_SPI_TransmitReceive(&CONTROLLER_SPI_HANDLER,&txdata[i],&rxdata[i],1,0xFFFF);
		PSControllerWait();

	}
	PSControllerDeselect();

	rxdata[3] = ~rxdata[3];
	rxdata[4] = ~rxdata[4];
	*button = ((rxdata[3]<<8) + rxdata[4]);
}
*/
/*
 * プレステコントローラ通信
 * @param
 * @return	受信データを16ビットで返す
 */
void PSControllerGetData(uint16_t *button , analog_stick_norm *left_norm, analog_stick_norm * right_norm, analog_stick_polar *left_polar, analog_stick_polar *right_polar) {
	analog_stick left_offset, right_offset;
	int8_t data_num;
	uint8_t tx_data[10] = {0x01, 0x42};
	uint8_t rx_data[10] = {};

	//オフセット設定
	left_offset.x = 128;
	left_offset.y = 128;
	right_offset.x = 128;
	right_offset.y = 128;

	//通信設定変更
	CONTROLLER_SPI_HANDLER.Init.FirstBit = SPI_FIRSTBIT_LSB;
	HAL_SPI_Init(&CONTROLLER_SPI_HANDLER);

	//通信開始
	PSControllerSelect();
	PSControllerWait();
	for (uint8_t i = 0; i < 3; i++) {
		HAL_SPI_TransmitReceive(&CONTROLLER_SPI_HANDLER, &tx_data[i], &rx_data[i], 1, 0xFFFF);
		PSControllerWait();
	}

	//アナログスティックを使用するかを確認
	if ((rx_data[1] & 0x0F) == 0x03) {data_num = 3 + 6;}	//使用する場合
	else 							 {data_num = 3 + 2;}	//使用しない場合

	//アナログスティック読み込み
	for (int8_t i = 3; i < data_num; i++) {
		HAL_SPI_TransmitReceive(&CONTROLLER_SPI_HANDLER, &tx_data[i], &rx_data[i], 1, 0xFFFF);
		PSControllerWait();
	}
	PSControllerDeselect();

	//ボタンの処理
	//全ビット反転、16ビットに結合して返す
	rx_data[3] = ~rx_data[3];
	rx_data[4] = ~rx_data[4];
	*button = ((rx_data[3] << 8) + rx_data[4]);

	//アナログスティックの処理
	//スティックの値を-1~1に正規化
	if ((rx_data[1] & 0x0F) == 0x03) {		//アナログスティックを使用する場合
		//(x,y)を-1~1に正規化したもの
		left_norm->x  = NormalizeStick(rx_data[7] - left_offset.x,  left_offset.x);
		left_norm->y  = NormalizeStick(rx_data[8] - left_offset.y,  left_offset.y)  * (-1);
		right_norm->x = NormalizeStick(rx_data[5] - right_offset.x, right_offset.x);
		right_norm->y = NormalizeStick(rx_data[6] - right_offset.y, right_offset.y) * (-1);

		//半径1の極座標表示に変換
		//左スティック
		left_polar->r = fminf(sqrtf(powf(left_norm->x, 2) + powf(left_norm->y, 2)), 1.0f);;
		if (left_polar->r < ANALOG_STICK_DEADZONE) {
			left_polar->r = 0;
		}
		if (left_polar->r != 0) {
			left_polar->theta = (180 * asinf(left_norm->y / left_polar->r)) / M_PI;
			if (left_norm->x > 0 && left_norm->y > 0) {			//第一象限
				;
			} else if (left_norm->x < 0 && left_norm->y > 0) {	//第二象限
				left_polar->theta = 180 - left_polar->theta;
			} else if (left_norm->x < 0 && left_norm->y < 0) {	//第三象限
				left_polar->theta = 180 - left_polar->theta;
			} else {											//第四象限
				left_polar->theta = 360 + left_polar->theta;
			}
		} else {
			left_polar->theta = 0;
		}

		//右スティック
		right_polar->r = fminf(sqrtf(powf(right_norm->x, 2) + powf(right_norm->y, 2)), 1.0f);
		if (right_polar->r < ANALOG_STICK_DEADZONE) {
			right_polar->r = 0;
		}
		if (right_polar->r != 0) {
			right_polar->theta = (180 * asinf(right_norm->y / right_polar->r)) / M_PI;
			if (right_norm->x > 0 && right_norm->y > 0) {			//第一象限
				;
			} else if (right_norm->x < 0 && right_norm->y > 0) {	//第二象限
				right_polar->theta = 180 - right_polar->theta;
			} else if (right_norm->x < 0 && right_norm->y < 0) {	//第三象限
				right_polar->theta = 180 - right_polar->theta;
			} else {											//第四象限
				right_polar->theta = 360 + right_polar->theta;
			}
		} else {
			right_polar->theta = 0;
		}
	} else {		//アナログスティックを使用しない場合は全てゼロ
		left_norm->x  = 0;
		left_norm->y  = 0;
		right_norm->x = 0;
		right_norm->y = 0;

		left_polar->r      = 0;
		left_polar->theta  = 0;
		right_polar->r     = 0;
		right_polar->theta = 0;
	}
}

//ノイズ？をはじく
int filter(uint16_t button, analog_stick_norm left_norm, analog_stick_norm  right_norm, analog_stick_polar left_polar, analog_stick_polar right_polar){
	uint16_t flag = 1;

	if(button == 42405 || button == 48830){
		flag = 0;
	}
	if(left_norm.x*100.0 == 100 || left_norm.x*100.0 == -29){
		flag = 0;
	}
	return flag;
}

/*
 * スティックの値を-1 ~ 1に正規化
 * @param
 * @return
 */
static float NormalizeStick(int16_t stick, int16_t offset) {
	if (stick > 0) {
		return ((float)stick / (0xFF - offset));
	} else {
		return ((float)stick / offset);
	}
}


static void PSControllerSelect(void){
	//HAL_GPIO_WritePin(CONTROLLER1_CS_PORT,CONTROLLER1_CS_PIN,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CONTROLLER_CS_PORT,CONTROLLER_CS_PIN,GPIO_PIN_RESET);
}

static void PSControllerDeselect(void){
	//HAL_GPIO_WritePin(CONTROLLER1_CS_PORT,CONTROLLER1_CS_PIN,GPIO_PIN_SET);
	HAL_GPIO_WritePin(CONTROLLER_CS_PORT,CONTROLLER_CS_PIN,GPIO_PIN_SET);

}

static void PSControllerWait(void){
	volatile uint32_t i;
	for(i=0;i<30;i++);
}

