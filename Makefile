# test

CC=gcc
CARGS=-Wall -O2 -g
LINKS=-lm -lGL -lGLU -lSDL2
EXE=engine

# Directories
SOURCES = src src/lua src/lua-api
# Files
CFILES = $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))
OBJ = $(CFILES:.c=.o)
BACKUPS = $(foreach dir,$(SOURCES),$(wildcard $(dir)/*~))

all: $(EXE)

quicktest: all
	@echo "Launching ..."
	@./$(EXE)

$(EXE): $(OBJ)
	$(CC) $(CARGS) $(OBJ) $(LINKS) -o $(EXE)

$(EXE)-opti:
	$(CC) $(CARGS) -O2 $(OBJ) $(LINKS) -o $(EXE)

%.o: %.c
	$(CC) $(CARGS) -o $@ -c $^ $(CFLAGS)

clean:
	rm -rf $(OBJ)

mrproper: clean
	rm -rf $(EXE)
	rm -rf $(BACKUPS)

wait-and-bleed: mrproper quicktest

