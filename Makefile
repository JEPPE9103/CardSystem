PROG = main.exe 
SRC = main.c safeinput.c safeinput.h funktioner.c funktioner.h
CFLAGS = -g -Wall -Wextra  -Wundef -pedantic -Werror
LIBS = 

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC)  $(LIBS) 

clean:
	rm -f $(PROG)

.PHONY: all clean