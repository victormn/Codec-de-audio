CFLAGS= -I inc/

all: classes
	@gcc ./src/encoder.c $(CFLAGS) -o encode ./obj/file_manager.o ./obj/bit_manager.o ./obj/testes.o ./obj/diferenca.o ./obj/carreira.o -lm -Wall -g -O0
	@gcc ./src/decoder.c $(CFLAGS) -o decode ./obj/file_manager.o ./obj/bit_manager.o ./obj/testes.o ./obj/diferenca.o ./obj/carreira.o -lm -Wall -g -O0
	@echo "! Compilado com sucesso !"
	@echo
	@echo "Para codificar, utilize:"
	@echo "./encode -d -c -h <entrada.wav> <saida.bin>"
	@echo "As flags -d -c -h sao opcionais e podem ser inseridas em qualquer ordem"
	@echo
	@echo "Para decodificar, utilize:"
	@echo "./decode <entrada.bin> <saida.wav>"

classes:
	@gcc -c ./src/file_manager.c $(CFLAGS) -o ./obj/file_manager.o -g
	@gcc -c ./src/bit_manager.c $(CFLAGS) -o ./obj/bit_manager.o -g
	@gcc -c ./src/testes.c $(CFLAGS) -o ./obj/testes.o -g
	@gcc -c ./src/diferenca.c $(CFLAGS) -o ./obj/diferenca.o -g
	@gcc -c ./src/carreira.c $(CFLAGS) -o ./obj/carreira.o -g

clean:
	@rm -f ./obj/*.o encode
	@rm -f ./obj/*.o decode
	@find -name "*~" | xargs rm -rf

memco:
	@valgrind --track-origins=yes ./encode -d files/inputs/sample1.wav files/output/output.bin

memdec:
	@valgrind --track-origins=yes ./decode files/output/output.bin files/output/output.wav

encoder:
	@echo "Apenas para testes..."
	@./encode -d files/inputs/sample1.wav files/output/output.bin

decoder:
	@echo "Apenas para testes..."
	@./decode files/output/output.bin files/output/output.wav