.PHONY:clean

CC = gcc
CFLAGS = -Wall -g
OBJ = test
OBJS = test.o ring_fifo.o
RM = rm

${OBJ}:${OBJS}
	@${CC} ${CFLAGS} $^ -o $@ 
test.o:test.c
	@${CC} ${CFLAGS} -E $^ -o test.i
	@${CC} ${CFLAGS} -S test.i -o test.s
	@${CC} ${CFLAGS} -c $^ -o $@
ring_fifo.o:ring_fifo.c
	@${CC} ${CFLAGS} -E $^ -o ring_fifo.i
	@${CC} ${CFLAGS} -S ring_fifo.i -o ring_fifo.s
	@${CC} ${CFLAGS} -c $^ -o $@
clean:
	@${RM} ${OBJ} ${OBJS} *.i *.s