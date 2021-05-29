*.PHONY = all clean mrproper install

IDIR = include
ODIR = obj
BINDIR = bin
SRCDIR = src

CC = gcc
CFLAGS = -I$(IDIR) -Wall -std=c99

SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(SRC:$(SRCDIR)/%.c=$(ODIR)/%.o)
TARGET=BoEPassRmvr

all: makedirs $(BINDIR)/$(TARGET)

makedirs:
	@mkdir -p $(BINDIR)
	@mkdir -p $(ODIR)

$(BINDIR)/$(TARGET): $(OBJ)
	$(CC) -o $@ $^

$(OBJ): $(ODIR)/%.o :  $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf $(ODIR)

mrproper: clean
	@rm -rf $(BINDIR)

install:
	@mkdir -p ~/$(TARGET)
	@cp $(BINDIR)/$(TARGET) ~/$(TARGET)
