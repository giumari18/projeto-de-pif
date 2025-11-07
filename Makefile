# Makefile - Versão Corrigida

# Variáveis do Projeto
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = cli_exec
SRCDIR = src
INCDIR = include
BUILDDIR = build

# Caminho para os arquivos .c
SOURCES = $(wildcard $(SRCDIR)/*.c)
# Converte os caminhos dos .c para os caminhos dos .o, colocando-os em build/
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

# Regra principal: 'make all' ou 'make' (gera o executável em build/)
all: $(BUILDDIR)/$(TARGET)

# Cria a pasta build se ela não existir
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Linkagem: Cria o executável a partir dos arquivos .o
$(BUILDDIR)/$(TARGET): $(OBJECTS) | $(BUILDDIR)  # Garante que BUILDDIR exista antes de tentar linkar
	$(CC) $(CFLAGS) $^ -o $@

# Compilação: Regra para compilar cada arquivo .c para .o
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Limpeza: Remove arquivos gerados
clean:
	rm -rf $(BUILDDIR)/*

# Rodar (Opcional)
run: $(BUILDDIR)/$(TARGET)
	./$(BUILDDIR)/$(TARGET) ajuda

.PHONY: all clean run