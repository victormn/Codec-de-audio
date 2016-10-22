Projeto para a disciplina de Multimídia e Hipermídia @ ICMC - 2016


Alunos:

Elisa Jorge Marcatto        nUSP 7961965
Victor Marcelino Nunes      nUSP 8622381



Compilar:

Foi criado um Makefile para o projeto, portando, basta utilizar:

$make



Executar:

Para codificar, utilize (as flags -d -c -h são opcionais e podem ser inseridas em qualquer ordem):

$./encode -d -c -h <entrada.wav> <saida.bin>


Para decodificar, utilize:

$./decode <entrada.bin> <saida.wav>



Outros comandos criados no Makefile que pode ser utilizados:

Limpar executavel e arquivos ~.o
$make clean

Realiza testes utilizando arquivos contidos na pasta "files/inputs". Salva na pasta "files/output"
$make encoder
$make decoder

Verificar a memoria dos testes citados acima (para a codificação e decodificação, respectivamente)
$make memco
$make memdec

