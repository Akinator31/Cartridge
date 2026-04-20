GBDK_HOME = /opt/gbdk
LCC = $(GBDK_HOME)/bin/lcc
CFLAGS = -Wf--std=c11

.PHONY: all re clean fclean

all: game.gb

game.gb: src/main.c
	$(LCC) $(CFLAGS) -o $@ $^

run: all
	retroarch -L /usr/lib/libretro/gambatte_libretro.so game.gb

re: fclean
	$(MAKE) all

clean:
	rm -f *.o *.noi *.map *.sym

fclean: clean
	rm -f *.gb