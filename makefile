# Nombre del archivo ejecutable
TARGET = comuna

# Archivos fuente del programa
SRCS = comuna.c

# Compilador a utilizar
CC = gcc

# Opciones de compilación
CFLAGS = -Wall

# Regla para compilar los archivos fuente
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Regla para limpiar los archivos objeto y el ejecutable
clean:
	rm -f $(TARGET) *.o
