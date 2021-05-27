*.PHONY = all clean mrproper install

IDIR = include
ODIR = obj
BINDIR = bin
SRCDIR = src

CXX = gcc
CXXFLAGS = -I$(IDIR) $(shell pkg-config --cflags SDL2_image) -Wall -std=c++11 -DCOLORFUL_OUTPUT
LDFLAGS = -lstdc++ $(shell pkg-config --libs SDL2_image)

SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJ=$(SRC:$(SRCDIR)/%.cpp=$(ODIR)/%.o)
TARGET=BoEMapsExtract

all: makedirs $(BINDIR)/$(TARGET)

makedirs:
	@mkdir -p $(BINDIR)
	@mkdir -p $(ODIR)

$(BINDIR)/$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ): $(ODIR)/%.o :  $(SRCDIR)/%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	@rm -rf $(ODIR)

mrproper: clean
	@rm -rf $(BINDIR)
install:
	@mkdir -p ~/$(TARGET)
	@cp $(BINDIR)/$(TARGET) ~/$(TARGET)
	@cp -r ressources ~/$(TARGET)/ressources
