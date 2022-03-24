# Parsing
## fixed

- echo -na $USER
- echo -na test$USER
- echo -na $USERtest
- echo -na $USER $USER
- echo -na "test"
- echo -nat "hello world"
- echo -na "$USER"
- echo -na "test$USER"
- echo -na $USER$USER
- echo -na "$USER$USER"
- echo -na "$USER $USER"
- echo -na "test test"
- echo -na "$USERtest"
- echo -na -t "hello world'"          'helloworad "'
- echo "test" (no optinos)

## redirection

cat > outfile < Makefile

cat > outfile > outfile2 < Makefile > outfile3 < outfile > outfile2 < src/minishell/main.c

cat >> outfile >> outfile2 < Makefile >> outfile3 < outfile > outfile2 < src/minishell/main.c