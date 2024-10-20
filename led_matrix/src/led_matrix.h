#ifndef LED_MATRIX_H_
#define LED_MATRIX_H_

#include "../../led_matrix_bsp/ps7_cortexa9_0/include/sleep.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xgpiops.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xil_printf.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xparameters.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xscugic.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xttcps.h"
#include "platform.h"

#define COL_ADDR XPAR_PIXEL_CTRL_BASEADDR
#define CTRL_ADDR (XPAR_PIXEL_CTRL_BASEADDR + 8)
#define COLORS 3
#define HEIGHT 8
#define WIDTH 8

void reset_matrix();
void set_matrix();
void set_all();
void test(int col);

#endif /* LED_MATRIX_H_ */
