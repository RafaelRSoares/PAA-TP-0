# Compilar apenas os .o
compile:
	@gcc -c main.c arte.c

# Construir o executável a partir dos .o
build: main.o arte.o
	@gcc main.o arte.o -o trabalho0

# Rodar o programa
run: build
	@./trabalho0

# Limpar arquivos temporários
clean:
	@rm -f *.o trabalho0
