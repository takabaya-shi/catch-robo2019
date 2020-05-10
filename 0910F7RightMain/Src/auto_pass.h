/*
 * auto_pass.h
 *
 *  Created on: 2019/09/12
 *      Author: tomok
 */

#ifndef AUTO_PASS_H_
#define AUTO_PASS_H_

#define AUTO_CIRCLE_BUTTON  1
#define AUTO_TRIANGLE_BUTTON  2
#define AUTO_SQUARE_BUTTON  3

//自動のプログラムから帰ってきたことを表すフラグ。吸引の保持に使う
#define AUTO_RETUEN_FLAG 10

#define AUTO_RETUEN_BOX_FLAG 11
#define AUTO_RETUEN_WORK_FLAG 12
#define AUTO_ESCAPE_FLAG 13
#define AUTO_CENTER_FLAG 14
#define AUTO_CORNER_FLAG 15

void Auto_Set(uint16_t *auto_flag,uint16_t *button_flag);
void Auto_SetPosWork(uint16_t *auto_work_flag);
void Auto_SetPosBOX(uint16_t *auto_BOX_flag);
void Auto_SetEscape(uint16_t *auto_button_flag);
void Auto_SetCenter(uint16_t *auto_center_flag);
void Auto_SetCorner(uint16_t *auto_corner_flag);
extern int auto_count;
extern uint16_t MSW_Z_MIN_FLAG;
extern uint16_t MSW_Z_MAX_FLAG;
extern uint16_t MSW_BOX_Z_MIN_FLAG;
extern uint16_t MSW_BOX_Z_MAX_FLAG;
extern uint16_t MSW_WORK_Z_MIN_FLAG;
extern uint16_t MSW_WORK_Z_MAX_FLAG;

#endif /* AUTO_PASS_H_ */
