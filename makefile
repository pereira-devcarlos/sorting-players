# Automatizando o makefile

# Nome do projeto
PROJ_NAME=sorter


# Arquivos .c e .h na pasta src
C_SOURCE=$(wildcard src/*.c)
H_SOURCE=$(wildcard src/*.h)
# Arquivos objeto na pasta src
OBJ=$(C_SOURCE:.c=.o)

# Compilador
CC=gcc

# Flags (opções) para o compilador
CC_FLAGS=-c         \
         -Wall      \
		 -g         \
         -pedantic

#########################
# Compilação e linkagem #
#########################
all: $(PROJ_NAME)


$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^


src/%.o: src/%.c src/%.h
	$(CC) $(CC_FLAGS) -o $@ -c $<


src/main.o: src/main.c $(H_SOURCE)
	$(CC) $(CC_FLAGS) -o $@ -c $<


clean:
	rm -rf src/*.o $(PROJ_NAME) *~