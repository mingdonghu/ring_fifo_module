#include "ring_fifo.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
  p_ring_fifo_t p_ring_fifo = ring_fifo_create();
  if (p_ring_fifo == NULL) {
    printf("ring_fifo_create failed\n");
    return -1;
  }
  printf("ring_fifo_create success\n");

  for (int i = 0; i < 50; i++) {
    int ret = ring_fifo_write(p_ring_fifo, (data_t)i);
    if (ret != 0) {
      printf("ring_fifo_write failed\n");
      return -1;
    }
    printf("write data = %d\n", p_ring_fifo->data_buf[i]);
  }
  printf("--------------------\n");
  data_t data_from_ringfifo = 0;
  for (int i = 0; i < 50; i++) {
    int ret = ring_fifo_read(p_ring_fifo, &data_from_ringfifo);
    if (ret != 0) {
      printf("ring_fifo_read failed\n");
      return -1;
    }
    printf("read data = %d\n", data_from_ringfifo);
  }

  int ret = ring_fifo_destroy(p_ring_fifo);
  if (ret != 0) {
    printf("ring_fifo_destroy failed\n");
    return -1;
  }
  printf("ring_fifo_destroy success\n");

  return 0;
}
