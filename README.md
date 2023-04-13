# ring fifo
> 通用化的环形队列模块,特点如下：
- 多平台支持(MCU/RTOS/Linux/Windows)
- 支持C99,支持C/C++编译器编译
- 支持动态/静态分配队列的内存空间
- 支持缓冲数据类型宏配置

## 1.下载
``` bash
git clone https://github.com/mingdonghu/ring_fifo_module.git
```
## 2.编译与运行示例
### 方式1：使用make工具
``` bash
make
sudo chmod +x test
./test
```
### 方式2：使用VScode工具
- 第一步，开发主机需要提前安装VScode 编译器和相应的C/C++插件以及支持C/C++语言的编译器(MSVC/GCC/MingW)
- 第二步，配置`.vscode/`目录下的task.json和launch.json文件

## 3.示例代码
```c
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

```
