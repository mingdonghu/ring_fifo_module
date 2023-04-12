/**
 * @file ring_fifo.h
 * @author David Hu (hmd_hubei_cn@163.com)
 * @brief  环形缓冲区(环形队列)的实现
 * @version 1.0
 * @date 2023-04-13
 * 
 * @copyright Copyright (c) 2023 David 
 * 
 */

#ifndef __RING_FIFO_H__
#define __RING_FIFO_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define DATA_TYPE unsigned char
typedef DATA_TYPE data_t;

#define RING_FIFO_SIZE  100

// #define DYNAMIC_INSTANT_CREATE

#ifndef DYNAMIC_INSTANT_CREATE
#define STATIC_INSTANT_CREATE_ENABLE 1
#define DYNAMIC_INSTANT_CREATE_ENABLE 0
#else
#define STATIC_INSTANT_CREATE_ENABLE 0
#define DYNAMIC_INSTANT_CREATE_ENABLE 1
#endif /* DYNAMIC_INSTANT_CREATE */

typedef struct ring_fifo_struct {
    data_t data_buf[RING_FIFO_SIZE];    /* 缓冲区 */
    int w_op;                   /* 写操作 */
    int r_op;                   /* 读操作 */
} ring_fifo_t;

typedef struct ring_fifo_struct *p_ring_fifo_t;

// public function declare
p_ring_fifo_t ring_fifo_init(void);
int ring_fifo_write(p_ring_fifo_t p_ring_fifo, data_t data);
int ring_fifo_read(p_ring_fifo_t p_ring_fifo, data_t *p_data);
int ring_fifo_is_empty(p_ring_fifo_t p_ring_fifo);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RING_FIFO_H__ */

/* **************** copyright @ 2023 David Hu   *** END OF FILE *** */
