/**
 * @file ring_fifo.c
 * @author David Hu (hmd_hubei_cn@163.com)
 * @brief  环形缓冲区(环形队列)实现
 * @version 1.0
 * @date 2023-04-13
 * 
 * @copyright Copyright (c) 2023 David Hu
 * 
 */

// include header file
#include "ring_fifo.h"

#include <stdio.h>

#include <string.h>

#if DYNAMIC_INSTANT_CREATE_ENABLE
#include <stdlib.h>
#endif  // DYNAMIC_INSTANT_CREATE_ENABLE
// -----

// private variable definition
#if STATIC_INSTANT_CREATE_ENABLE
static ring_fifo_t gs_ring_fifo;
#endif  // STATIC_INSTANT_CREATE_ENABLE

typedef enum bool_enum {
  FALSE,
  TRUE
} bool_t;
static bool_t gs_is_create = FALSE;
// -----

// private function declaration
static int ring_fifo_is_empty(p_ring_fifo_t p_ring_fifo);

static int ring_fifo_is_full(p_ring_fifo_t p_ring_fifo);

// -----


/**
 * @brief 环形队列写入数据
 * 
 * @return p_ring_fifo_t
 * NULL: 创建失败
 * 非NULL: 创建成功
 */  
p_ring_fifo_t ring_fifo_create(void) {
#if STATIC_INSTANT_CREATE_ENABLE
  memset((unsigned char*)&gs_ring_fifo, 0, sizeof(ring_fifo_t));
  gs_is_create = TRUE;
  return &gs_ring_fifo;
#endif  // STATIC_INSTANT_CREATE_ENABLE

#if DYNAMIC_INSTANT_CREATE_ENABLE
  p_ring_fifo_t p_ring_fifo = (p_ring_fifo_t)malloc(sizeof(ring_fifo_t));
  if (p_ring_fifo == NULL) {
    printf("malloc ring_fifo_t failed\n");
    return NULL;
  }
  memset((unsigned char*)p_ring_fifo, 0, sizeof(ring_fifo_t));
  gs_is_create = TRUE;
  return p_ring_fifo;
#endif  // DYNAMIC_INSTANT_CREATE_ENABLE

  gs_is_create = FALSE;
  return NULL;
}

/**
 * @brief 销毁环形队列
 * @param [in] p_ring_fifo [环形队列首地址] 
 * @return int 
 * -1: 环形队列未初始化
 * 0: 成功
 */
int ring_fifo_destroy(p_ring_fifo_t p_ring_fifo) {
  if ((p_ring_fifo == NULL) && 
    (gs_is_create == TRUE)) {
    return -1;
  }

#if STATIC_INSTANT_CREATE_ENABLE
  memset((unsigned char*)&gs_ring_fifo, 0, sizeof(ring_fifo_t));
#endif  // STATIC_INSTANT_CREATE_ENABLE

#if DYNAMIC_INSTANT_CREATE_ENABLE
  free(p_ring_fifo);
#endif  // DYNAMIC_INSTANT_CREATE_ENABLE

  return 0;
}

/**
 * @brief 判断环形队列是否为空
 * 
 * @param p_ring_fifo 
 * @return int 
 * -1: 环形队列未初始化
 * 0: 环形队列未空
 * 1: 环形队列已空
 */
int ring_fifo_is_empty(p_ring_fifo_t p_ring_fifo) {
  if (p_ring_fifo == NULL) {
    return -1;
  }

  if (p_ring_fifo->w_op == p_ring_fifo->r_op) {
    return 1;
  }

  return 0;
}

/**
 * @brief 判断环形队列是否已满
 * 
 * @param p_ring_fifo 
 * @return int 
 * -1: 环形队列未创建
 * 0: 环形队列未满
 * 1: 环形队列已满
 */
int ring_fifo_is_full(p_ring_fifo_t p_ring_fifo) {
  if ((p_ring_fifo == NULL) && 
    (gs_is_create == TRUE)) {
    return -1;
  }

  if ((p_ring_fifo->w_op - p_ring_fifo->r_op) == RING_FIFO_SIZE) {
    return 1;
  }

  return 0;
}

/**
 * @brief 向环形队列中写入数据
 * @param [in] p_ring_fifo [环形队列首地址]
 * @param [in] data [写入的数据] 
 * @return int 
 * -1: 环形队列未初始化
 * -2: 环形队列已满
 * 0: 写入数据成功
 */
int  ring_fifo_write(p_ring_fifo_t p_ring_fifo, data_t data) {
  if ((p_ring_fifo == NULL) && 
    (gs_is_create == TRUE)) {
    printf("ring_fifo is not init\n");
    return -1;
  }

  if (ring_fifo_is_full(p_ring_fifo)) {
    printf("ring_fifo is full\n");
    return -2;
  }

  data_t* p_data_buf_index =  (data_t*)p_ring_fifo->data_buf;
  p_data_buf_index += (p_ring_fifo->w_op % RING_FIFO_SIZE);
  *p_data_buf_index = data;
  p_ring_fifo->w_op++;

  return 0;
}

/**
 * @brief 从环形队列中读取数据
 * @param [in] p_ring_fifo [环形队列首地址]
 * @param [out] p_data [读取的数据]
 * @return int 
 * -1: 环形队列未初始化
 * -2: 环形队列已空
 * 0: 读取数据成功
 */
int ring_fifo_read(p_ring_fifo_t p_ring_fifo, data_t* p_data) {
  if ((p_ring_fifo == NULL) && 
    (gs_is_create == TRUE)) {
    printf("ring_fifo is not init\n");
    return -1;
  }

  if (ring_fifo_is_empty(p_ring_fifo)) {
    printf("ring_fifo is empty\n");
    return -2;
  }

  data_t* p_data_buf_index =  (data_t*)p_ring_fifo->data_buf;
  p_data_buf_index += (p_ring_fifo->r_op % RING_FIFO_SIZE);
  *p_data = *p_data_buf_index;
  p_ring_fifo->r_op++;

  return 0;
}



/* **************** copyright @ 2023 David Hu   *** END OF FILE *** */
