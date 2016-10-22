INC= -I inc/
FLAGS=-d -h -c
ENCODE=./encode $(FLAGS) files/inputs/sample3.wav files/output/output.bin
DECODE=./decode files/output/output.bin files/output/output.wav
WFLAGS=-Wall -g -O0 -std=c99

all: classes
	@gcc ./src/encoder.c $(INC) -o encode ./obj/file_manager.o ./obj/bit_manager.o ./obj/diferenca.o ./obj/carreira.o ./obj/huffman.o ./obj/fila.o -lm $(WFLAGS) 
	@gcc ./src/decoder.c $(INC) -o decode ./obj/file_manager.o ./obj/bit_manager.o ./obj/diferenca.o ./obj/carreira.o ./obj/huffman.o ./obj/fila.o -lm $(WFLAGS)  
	@echo "! Compilado com sucesso !"
	@echo
	@echo "Para codificar, utilize:"
	@echo "./encode -d -c -h <entrada.wav> <saida.bin>"
	@echo "As flags -d -c -h sao opcionais e podem ser inseridas em qualquer ordem"
	@echo
	@echo "Para decodificar, utilize:"
	@echo "./decode <entrada.bin> <saida.wav>"

classes:
	@gcc -c ./src/file_manager.c $(INC) -o ./obj/file_manager.o $(WFLAGS) 
	@gcc -c ./src/bit_manager.c $(INC) -o ./obj/bit_manager.o $(WFLAGS) 
	@gcc -c ./src/diferenca.c $(INC) -o ./obj/diferenca.o $(WFLAGS) 
	@gcc -c ./src/carreira.c $(INC) -o ./obj/carreira.o $(WFLAGS) 
	@gcc -c ./src/huffman.c $(INC) -o ./obj/huffman.o $(WFLAGS) 
	@gcc -c ./src/fila.c $(INC) -o ./obj/fila.o $(WFLAGS) 

clean:
	@rm -f ./obj/*.o encode decode
	@find -name "*~" | xargs rm -rf

memco:
	@valgrind --track-origins=yes --max-stackframe=10880352 $(ENCODE)

memdec:
	@valgrind --track-origins=yes --max-stackframe=10880352 $(DECODE)

encoder:
	@echo "Apenas para testes..."
	@$(ENCODE)

decoder:
	@echo "Apenas para testes..."
	@$(DECODE)