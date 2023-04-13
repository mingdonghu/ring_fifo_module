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

#pragma pack(1) // 1字节对齐
typedef struct ring_fifo_struct {
    data_t data_buf[RING_FIFO_SIZE];    /* 缓冲区 */
    int w_op;                   /* 写操作 */
    int r_op;                   /* 读操作 */
} ring_fifo_t;
#pragma pack() // 恢复默认对齐

typedef struct ring_fifo_struct *p_ring_fifo_t;

// public function declare
/**
 * @brief 环形队列写入数据
 * 
 * @return p_ring_fifo_t
 * NULL: 创建失败
 * 非NULL: 创建成功
 */  
p_ring_fifo_t ring_fifo_create(void);

/**
 * @brief 销毁环形队列
 * @param [in] p_ring_fifo [环形队列首地址] 
 * @return int 
 * -1: 环形队列未初始化
 * 0: 成功
 */
int ring_fifo_destroy(p_ring_fifo_t p_ring_fifo);

/**
 * @brief 向环形队列中写入数据
 * @param [in] p_ring_fifo [环形队列首地址]
 * @param [in] data [写入的数据] 
 * @return int 
 * -1: 环形队列未初始化
 * -2: 环形队列已满
 * 0: 写入数据成功
 */
int ring_fifo_write(p_ring_fifo_t p_ring_fifo, data_t data);

/**
 * @brief 从环形队列中读取数据
 * @param [in] p_ring_fifo [环形队列首地址]
 * @param [out] p_data [读取的数据]
 * @return int 
 * -1: 环形队列未初始化
 * -2: 环形队列已空
 * 0: 读取数据成功
 */
int ring_fifo_read(p_ring_fifo_t p_ring_fifo, data_t *p_data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RING_FIFO_H__ */

/* **************** copyright @ 2023 David Hu   *** END OF FILE *** */
