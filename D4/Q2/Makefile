all: clean fifo lru

fifo: clean
	gcc -o fifo fifo.c minheap.c page.c

lru: clean
	gcc -o lru lru.c

clean:
	rm -f fifo lru
