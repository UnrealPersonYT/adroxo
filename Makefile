# =========================================
# Adroxo Build System (STABLE FINAL FIX)
# =========================================

# -----------------------------------------
# OS detection
# -----------------------------------------
ifeq ($(OS),Windows_NT)
    RM = del /Q
    MKDIR = mkdir
    SEP = \\
    NULL = NUL
    COPY = copy
else
    RM = rm -f
    MKDIR = mkdir -p
    SEP = /
    NULL = /dev/null
    COPY = cp
endif

# -----------------------------------------
# Compiler detection
# -----------------------------------------
CC :=

ifeq ($(OS),Windows_NT)
    ifneq ($(shell where gcc 2> NUL),)
        CC := gcc
    endif
    ifeq ($(CC),)
        ifneq ($(shell where clang 2> NUL),)
            CC := clang
        endif
    endif
    ifeq ($(CC),)
        ifneq ($(shell where cl 2> NUL),)
            CC := cl
        endif
    endif
else
    ifneq ($(shell which gcc 2> /dev/null),)
        CC := gcc
    endif
    ifeq ($(CC),)
        ifneq ($(shell which clang 2> /dev/null),)
            CC := clang
        endif
    endif
    ifeq ($(CC),)
        ifneq ($(shell which cl 2> /dev/null),)
            CC := cl
        endif
    endif
endif

ifeq ($(CC),)
$(error No supported compiler found)
endif

# -----------------------------------------
# Build config
# -----------------------------------------
SRC = src$(SEP)adroxo.c
OBJ = lib$(SEP)adroxo.o

ifeq ($(CC),gcc)
    CFLAGS = -O3 -march=native
    OUT = lib$(SEP)libadroxo.a
    AR = ar
    ARFLAGS = rcs

else ifeq ($(CC),clang)
    CFLAGS = -O3 -march=native
    OUT = lib$(SEP)libadroxo.a
    AR = ar
    ARFLAGS = rcs

else ifeq ($(CC),cl)
    CFLAGS = /O2 /GL /Oi /Ot /fp:fast /nologo /c
    OUT = lib$(SEP)adroxo.lib
    AR = lib
    ARFLAGS = /nologo /OUT:$(OUT)
endif

# -----------------------------------------
# Build rules
# -----------------------------------------
all: $(OUT)

lib:
	@mkdir lib 2>$(NULL) || true

ifeq ($(CC),cl)
$(OBJ): $(SRC) | lib
	$(CC) $(CFLAGS) $(SRC) /Fo$(OBJ)
else
$(OBJ): $(SRC) | lib
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)
endif

ifeq ($(CC),cl)
$(OUT): $(OBJ)
	$(AR) $(ARFLAGS) $(OBJ)
	$(RM) "$(OBJ)"
else
$(OUT): $(OBJ)
	$(AR) $(ARFLAGS) $(OUT) $(OBJ)
	$(RM) $(OBJ)
endif

# =========================================
# INSTALL SYSTEM (FIXED + SIMPLE + WORKING)
# =========================================

# Default install root
ROOT ?=

ifeq ($(ROOT),)
ifeq ($(OS),Windows_NT)
    ROOT = C:/dev/adroxo
else
    ROOT = /usr/local
endif
endif

install: $(OUT)
	@echo Root: $(ROOT)

ifeq ($(OS),Windows_NT)

	@mkdir "$(ROOT)" 2>NUL || true
	@mkdir "$(ROOT)\include" 2>NUL || true
	@mkdir "$(ROOT)\lib" 2>NUL || true

	@copy /Y include\adroxo.h "$(ROOT)\include\adroxo.h" >NUL
	@copy /Y "$(OUT)" "$(ROOT)\lib\" >NUL

else

	@mkdir -p "$(ROOT)/include"
	@mkdir -p "$(ROOT)/lib"

	@cp include/adroxo.h "$(ROOT)/include/adroxo.h"
	@cp "$(OUT)" "$(ROOT)/lib"

endif

	@echo Installation complete.

# -----------------------------------------
# CLEAN
# -----------------------------------------
clean:
	$(RM) lib$(SEP)* 2>$(NULL) || true