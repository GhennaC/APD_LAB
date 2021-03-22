build:
	gcc mutex.c -o mutex -lpthread -Wall
	gcc barrier.c -o barrier -lpthread -Wall
	gcc multiply_seq.c -o multiply_seq -lpthread -Wall
	gcc multiply.c -o multiply -lpthread -Wall
	gcc multiply1.c -o multiply1 -lpthread -Wall
	gcc multiply2.c -o multiply2 -lpthread -Wall
	gcc strassen.c -o strassen -lpthread -Wall
run_1:
	./mutex
run_2:
	./barrier
run_3:
	./multiply 1000 2
run_4:
	./multiply1 1000 2
run_5:
	./multiply2 1000 2
run_6:
	./strassen 100
clean:
	rm -rf mutex barrier multiply_seq multiply multiply1 multiply2 strassen
