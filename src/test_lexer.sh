#!/bin/bash

SRC_DIR="./lexer"
INCLUDE_DIR="../includes"
INCLUDE_LIBFT="./libft"
TEST_EXEC="test_lexer"

SRC_FILES="$SRC_DIR/lexer.c"

gcc -I$INCLUDE_DIR -I$INCLUDE_LIBFT $SRC_FILES -o $TEST_EXEC

if [ $? -eq 0 ]; then
    echo "Compilation réussie."
    echo "Exécution du programme de test..."
    ./$TEST_EXEC
else
    echo "Erreur de compilation."
    exit 1
fi
