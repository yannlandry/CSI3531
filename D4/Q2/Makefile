all: clean fifo lru

fifo: clean
	gcc -o fifo fifo.c minheap.c page.c util.c

lru: clean
	gcc -o lru lru.c page.c util.c

clean:
	rm -f fifo lru
