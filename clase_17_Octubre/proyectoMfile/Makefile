GCC = gcc
FLAGS = -Wall
CFLAGS = -lm

# Lista de ejecutables que deseas crear
PROGS = principalpd principalhd

# Lista de archivos fuente
SRCS = principalhd.c principalpd.c modulohd.c modulopd.c

# Generar los nombres de los objetos a partir de los nombres de los archivos fuente
OBJS = $(SRCS:.c=.o)

all: $(PROGS)

principalpd: principalpd.o modulohd.o modulopd.o
	$(GCC) $(FLAGS) -o $@ $^ $(CFLAGS)

principalhd: principalhd.o modulohd.o modulopd.o
	$(GCC) $(FLAGS) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(GCC) $(FLAGS) -c $< -o $@ $(CFLAGS)

clean:
	$(RM) $(PROGS) $(OBJS)
