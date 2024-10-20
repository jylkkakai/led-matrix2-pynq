
#include "led_matrix.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/sleep.h"

void reset_matrix() {
  volatile int *ctrl_addr = (int *)CTRL_ADDR;
  const size_t bits = 24 * 6;

  *ctrl_addr = 1;
  // Set brightness to 1 for all channels
  for (size_t i = 0; i < bits; i++) {
    *ctrl_addr &= ~0x8;
    *ctrl_addr |= 0x10;
    *ctrl_addr |= 0x8;
  }
  *ctrl_addr |= 0x2;
  // *ctrl_addr &= ~0x2;
  *ctrl_addr |= 0x4;
}

void set_pixel(uint8_t y, uint8_t r, uint8_t g, uint8_t b) {

  volatile int *ctrl_addr = (int *)CTRL_ADDR;
  uint8_t col[HEIGHT][COLORS] = {0};
  col[y][0] = b;
  col[y][1] = g;
  col[y][2] = r;
  for (size_t i = 0; i < HEIGHT; i++) {
    for (size_t j = 0; j < COLORS; j++) {
      uint8_t data = col[i][j];
      for (size_t k = 0; k < 8; k++) {
        if (data & 0x80)
          *ctrl_addr |= 0x10;
        else
          *ctrl_addr &= ~0x10;

        *ctrl_addr &= ~0x8;
        data = data < 1;
        *ctrl_addr |= 0x8;
      }
    }
  }
  *ctrl_addr |= 0x2;
  *ctrl_addr &= ~0x2;
}

void set_matrix() {

  volatile int *col_addr = (int *)COL_ADDR;
  *col_addr = 0x8;
  set_pixel(1, 0xff, 0x0, 0x0);
}

void set_all() {
  volatile int *ctrl_addr = (int *)CTRL_ADDR;
  volatile int *col_addr = (int *)COL_ADDR;
  *col_addr = 0x0;
  *ctrl_addr |= 0x4;
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < HEIGHT * COLORS; j++) {
      *ctrl_addr &= ~0x8;
      *ctrl_addr |= 0x10;
      *ctrl_addr |= 0x8;
    }
    *col_addr = (1 << i);
    // *col_addr = pow(2, i);
    *ctrl_addr |= 0x2;
    *ctrl_addr &= ~0x2;
    // sleep(1);
  }
  // *ctrl_addr |= 0x2;
  // *ctrl_addr &= ~0x2;
}

void test(int col) {
  volatile int *ctrl_addr = (int *)CTRL_ADDR;
  volatile int *col_addr = (int *)COL_ADDR;
  *col_addr = col;
  *ctrl_addr |= 0x4;
  for (size_t i = 0; i < 24 * 8; i++) {
    *ctrl_addr &= ~0x8;
    *ctrl_addr |= 0x10;
    *ctrl_addr |= 0x8;
  }
  *ctrl_addr |= 0x2;
  *ctrl_addr &= ~0x2;
}
