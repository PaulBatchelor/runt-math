NAME = math

LIBS = -lm -lrunt
CFLAGS = -fPIC -O3 -Wall -ansi -g

# Local Runt
LIBS += -L$(HOME)/.runt/lib 
CFLAGS += -I$(HOME)/.runt/include -I../ -I../nodes

# Runt Plumber 
LIBS += -lrunt_plumber -lsporth -lsoundpipe

OBJ = math.o

default: librunt_$(NAME).a rnt$(NAME)

librunt_$(NAME).a: $(OBJ)
	$(AR) rcs $@ $(OBJ)

rnt$(NAME): parse.c $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: librunt_$(NAME).a rnt$(NAME)
	mkdir -p ~/.runt/lib
	mkdir -p ~/.runt/bin
	mkdir -p ~/.runt/include
	mkdir -p ~/.runt/plugins
	cp librunt_$(NAME).a ~/.runt/lib
	cp rnt$(NAME) ~/.runt/bin

clean: 
	rm -rf librunt_$(NAME).a $(OBJ) 
	rm -rf rnt$(NAME)
