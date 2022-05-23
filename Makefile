main_cli:
	gcc -c main.c local.c
	gcc -o main_cli main.o local.o

clean:
	rm main_cli