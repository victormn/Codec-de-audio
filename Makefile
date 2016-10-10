CFLAGS= -I headers/

all: classes
	@#gcc ./src/encoder.c -o encoder
	@gcc ./src/encoder.c $(CFLAGS) -o encoder ./obj/file_manager.o
	@echo "! Compilado com sucesso !"
	@echo
	@echo "Para rodar, utilize:"
	@echo "./encoder -d -c -h <entrada.wav> <saida.bin>"
	@echo "As flags -d -c -h sao opcionais e podem ser inseridas em qualquer ordem"

classes:
	@gcc -c ./src/file_manager.c $(CFLAGS) -o ./obj/file_manager.o

clean:
	@rm -f ./obj/*.o encoder
	@find -name "*~" | xargs rm -rf

memorycheck:
	@valgrind ./encoder
