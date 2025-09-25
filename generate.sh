#!/bin/bash

# Formatear archivos C
c_formatter_42 $(find . -type f \( -name "*.c" -o -name "*.h" \))

# Nombre del programa
NAME="${1:-programa}"

# Subdirectorio opcional
SUBSYSTEM_PATH="$2"
if [ -n "$SUBSYSTEM_PATH" ]; then
    SUBSYSTEM_LIB="$SUBSYSTEM_PATH/$(basename "$SUBSYSTEM_PATH").a"
else
    SUBSYSTEM_LIB=""
fi

# Flags de link opcionales
LINK_FLAGS="$3"

# Configuración del compilador
CC="cc"
CFLAGS="-Wall -Wextra -Werror"

# Directorios de includes
INCLUDES=$(find . -type f -name "*.h" -exec dirname {} \; | sort -u | awk '{printf " -I%s", $0}')

# Directorios
SRC_DIR="./"
OBJ_DIR="obj"

# Lista de fuentes
if [ -n "$SUBSYSTEM_PATH" ]; then
    SRCS=$(find "$SRC_DIR" -type f -name "*.c" ! -path "$SUBSYSTEM_PATH/*" | tr '\n' ' ')
else
    SRCS=$(find "$SRC_DIR" -type f -name "*.c" | tr '\n' ' ')
fi

# Generar Makefile
cat > Makefile <<EOL
CC      = $CC
CFLAGS  = $CFLAGS
INCLUDES = $INCLUDES

OBJ_DIR = $OBJ_DIR
NAME    = $NAME

SRCS    = $SRCS
OBJS    = \$(SRCS:%.c=\$(OBJ_DIR)/%.o)
EOL

# Añadir LINK_FLAGS solo si existe
if [ -n "$LINK_FLAGS" ]; then
    echo "LINK_FLAGS = $LINK_FLAGS" >> Makefile
fi

# Reglas para subdirectorio o compilación normal
if [ -n "$SUBSYSTEM_PATH" ]; then
cat >> Makefile <<EOL
SUBSYSTEM_PATH = $SUBSYSTEM_PATH
SUBSYSTEM_LIB  = $SUBSYSTEM_LIB

all: subsystems \$(NAME)

subsystems:
	\$(MAKE) -C \$(SUBSYSTEM_PATH) all

\$(NAME): \$(OBJS) \$(SUBSYSTEM_LIB)
	\$(CC) \$(CFLAGS) \$(INCLUDES) -o \$@ \$^ \$(LINK_FLAGS)
EOL
else
cat >> Makefile <<EOL
all: \$(NAME)

\$(NAME): \$(OBJS)
	\$(CC) \$(CFLAGS) \$(INCLUDES) -o \$@ \$^ \$(LINK_FLAGS)
EOL
fi

# Reglas comunes
cat >> Makefile <<'EOL'

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
EOL

if [ -n "$SUBSYSTEM_PATH" ]; then
cat >> Makefile <<EOL
	\$(MAKE) -C \$(SUBSYSTEM_PATH) clean
	rm -rf \$(OBJ_DIR)
EOL
else
cat >> Makefile <<EOL
	rm -rf \$(OBJ_DIR)
EOL
fi

cat >> Makefile <<'EOL'

fclean: clean
EOL

if [ -n "$SUBSYSTEM_PATH" ]; then
cat >> Makefile <<EOL
	\$(MAKE) -C \$(SUBSYSTEM_PATH) fclean
	rm -f \$(NAME)
EOL
else
cat >> Makefile <<EOL
	rm -f \$(NAME)
EOL
fi

cat >> Makefile <<'EOL'

re: fclean all

.PHONY: all clean fclean re subsystems
EOL

echo "Makefile generado correctamente con nombre de programa: $NAME"
if [ -n "$SUBSYSTEM_PATH" ]; then
    echo "Incluyendo subdirectorio: $SUBSYSTEM_PATH"
fi
