JAVA_SOURCES := $(wildcard *.java)
JAVA_TARGETS := $(patsubst %.java,%.class,$(JAVA_SOURCES))
C_SOURCES    := $(wildcard *.[ch])
C_TARGETS    := client-td-connreuse server-concurrent-td-connreuse 

CFLAGS  := -std=c17 -O2 -g3 -Wall -Werror -pedantic -fsanitize=address,undefined -Wformat -Werror=format-security -Werror=array-bounds
LDFLAGS := -fsanitize=address,undefined -fpie -Wl,-pie

# If homebrew is installed, add library and include path
ifneq "$(shell brew -v)" ""
  LDFLAGS += -L$(shell brew --prefix)/lib
  CFLAGS += -I$(shell brew --prefix)/include
endif

ifeq ($(USE_LIBUNISTRING),yes)
  CFLAGS += -DUSE_LIBUNISTRING=1
  LDFLAGS += -lunistring
endif

.PHONY: clean

all: $(C_TARGETS) $(JAVA_TARGETS)

# dependencies

# client-naive: client-naive.o
# server-concurrent-naive: server-concurrent-naive.o
client-td-connreuse: client-td-connreuse.o rxb.o utils.o
client-td-connreuse.o: client-td-connreuse.c rxb.h utils.h
server-concurrent-td-connreuse: server-concurrent-td-connreuse.o rxb.o utils.o
server-concurrent-td-connreuse.o: server-concurrent-td-connreuse.c rxb.h utils.h

%.class: %.java
	javac $<

clean:
	@rm -rf $(C_TARGETS) $(JAVA_TARGETS) *.zip *.o *.dSYM *~

