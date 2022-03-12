CC=C:/MinGW/MinGW/bin/gcc.exe
CFLAGS=-ansi -O3 -Wall -Wextra -Wpedantic -Wparentheses \
      -Wformat=2 -Wno-unused-parameter -Wshadow \
      -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
      -Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
			-pedantic-errors -Wuninitialized \
			-Wmissing-declarations -Wconversion -Wdouble-promotion \
			-Wfloat-equal -Wbad-function-cast -Wno-unknown-pragmas -Wno-unused-function \

# GCC warnings that Clang doesn't provide:
ifeq ($(CC),gcc)
    CFLAGS += -Wjump-misses-init -Wlogical-op
endif


ROOT="$(realpath .)"

ODIR=obj
BDIR=bin
SDIR=src
IDIR=-Iinclude -IGL/include
ASSETS_DIR=assets

TARGET=main.exe
LDLIBS=-L$(ROOT)/GL/lib
LIBS=-lopengl32 -lglu32 -lglut32 -lglui32 -lglaux

SRC=$(wildcard $(SDIR)/*.c)
OBJ=$(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(SRC))
BIN=$(addprefix $(BDIR)/,$(TARGET))
LIB=$(addprefix $(LDLIBS)/,$(LIBS))

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c $< $(CFLAGS) $(IDIR) -o $@ 

.PHONY:Debug
Debug: $(OBJ)
	$(CC) $^ $(CFLAGS) -o $(BIN) -lgdi32 $(LDLIBS) $(LIBS)
	copy $(ASSETS_DIR)\* $(BDIR)\$(ASSETS_DIR)\ /Y

.PHONY: run
run:
	$(BIN)

.PHONY: clean
clean:
	del $(ODIR) $(BDIR)

