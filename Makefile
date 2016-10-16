INC= -I inc/
FLAGS=-c -d
ENCODE=./encode $(FLAGS) files/inputs/sample1.wav files/output/output.bin
DECODE=./decode files/output/output.bin files/output/output.wav

all: classes
	@gcc ./src/encoder.c $(INC) -o encode ./obj/file_manager.o ./obj/bit_manager.o ./obj/testes.o ./obj/diferenca.o ./obj/carreira.o -lm -Wall -g -O0
	@gcc ./src/decoder.c $(INC) -o decode ./obj/file_manager.o ./obj/bit_manager.o ./obj/testes.o ./obj/diferenca.o ./obj/carreira.o -lm -Wall -g -O0
	@echo "! Compilado com sucesso !"
	@echo
	@echo "Para codificar, utilize:"
	@echo "./encode -d -c -h <entrada.wav> <saida.bin>"
	@echo "As flags -d -c -h sao opcionais e podem ser inseridas em qualquer ordem"
	@echo
	@echo "Para decodificar, utilize:"
	@echo "./decode <entrada.bin> <saida.wav>"

classes:
	@gcc -c ./src/file_manager.c $(INC) -o ./obj/file_manager.o -g
	@gcc -c ./src/bit_manager.c $(INC) -o ./obj/bit_manager.o -g
	@gcc -c ./src/testes.c $(INC) -o ./obj/testes.o -g
	@gcc -c ./src/diferenca.c $(INC) -o ./obj/diferenca.o -g
	@gcc -c ./src/carreira.c $(INC) -o ./obj/carreira.o -g

clean:
	@rm -f ./obj/*.o encode
	@rm -f ./obj/*.o decode
	@find -name "*~" | xargs rm -rf

memco:
	@valgrind --track-origins=yes $(ENCODE)

memdec:
	@valgrind --track-origins=yes $(DECODE)

encoder:
	@echo "Apenas para testes..."
	@$(ENCODE)

decoder:
	@echo "Apenas para testes..."
	@$(DECODE)