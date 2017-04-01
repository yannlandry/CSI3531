all: clean producer consumer

producer: clean
	gcc -o producer producer.c catalan.c -lm

consumer: clean
	gcc -o consumer consumer.c

clean:
	rm -f producer consumer
