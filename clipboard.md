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

### Quotes in env_vars

- export sq="'"
- echo $sq test$sq'hello'world
- export dq='"'
- echo $dq test$dq'hello'world

### redirection

cat > outfile < Makefile
cat > outfile > outfile2 < Makefile > outfile3 < outfile > outfile2 < src/minishell/main.c
cat >> outfile >> outfile2 < Makefile >> outfile3 < outfile > outfile2 < src/minishell/main.c
echo >test"$USER"
echo >>test"$USER"
echo ">>test"$USER""
echo ">>t"test

### parsing

- return error when encounter \ or ; and unclosed quotes when parsing arguments
- fix if there is nothing at all
- fix if theres nothing between pipes

### cd
- cd multiple arguments has special message
- cd with 2 arguemts 
	- [oh-my-zsh](https://github.com/ohmyzsh/ohmyzsh/issues/6452)
	- [ibm docs](https://www.ibm.com/docs/en/zos/2.3.0?topic=descriptions-cd-change-working-directory)
- cd with > 2 arguemts
- cd - (goes to OLDPWD)
- cd no argument return to root
- cd -n no option

## To not fix

### Trimming spaces in env_vars when not within quotes
- export bad="     bad     "
- echo $bad
- echo "$bad"

## To-do

### parsing: single character in the beginning
< test.txt echo hello (valid)
e test (invalid)