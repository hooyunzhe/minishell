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
- "echo" '-n' "'   hello"      '   "world'
- echo -na "$USER1_"
- echo -na "$USER_"
- echo -na "$USER test" test
- echo -na "$USER_" test "test"
- echo "hello"world
- echo "hello""world"'test'
- echo ' $USER"world"'test
- echo "$USER"'$USER'
- echo "'test' $USER "hello ' $USER"world"'test

## redirection

cat > outfile < Makefile

cat > outfile > outfile2 < Makefile > outfile3 < outfile > outfile2 < src/minishell/main.c

cat >> outfile >> outfile2 < Makefile >> outfile3 < outfile > outfile2 < src/minishell/main.c

0 > 0 1 2 3
1,2,3 > X

iq isd
0  1 = 1
0  0 = 0
1  1 = 0
1  0 = 1