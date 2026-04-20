GBDK_HOME = /opt/gbdk
LCC = $(GBDK_HOME)/bin/lcc
CFLAGS = -Wall -Wextra -Iinclude
RETROARCH = retroarch
GAMBATTE_CORE ?= $(firstword $(wildcard /usr/lib/x86_64-linux-gnu/libretro/gambatte_libretro.so /usr/lib/libretro/gambatte_libretro.so))

.PHONY: all re clean fclean

all: game.gb

SRC = $(shell find src/ -type f -name "*.c")

game.gb: $(SRC)
	$(LCC) $(CFLAGS) -o $@ $^

run: all
	@if [ -z "$(GAMBATTE_CORE)" ]; then \
		echo "Error: gambatte_libretro.so not found."; \
		echo "Install libretro-gambatte or set GAMBATTE_CORE=/path/to/gambatte_libretro.so"; \
		exit 1; \
	fi
	$(RETROARCH) -L $(GAMBATTE_CORE) game.gb

re: fclean
	$(MAKE) all

clean:
	rm -f *.o *.noi *.map *.sym

fclean: clean
	rm -f *.gb