rm ./bin/*
gcc -g -c ./main.c -o ./bin/main.o
gcc -g -c ./bmp-read-utils.c -o ./bin/bmp-read-utils.o
gcc -g -c ./cmd-utils.c -o ./bin/cmd-utils.o
gcc ./bin/main.o ./bin/bmp-read-utils.o ./bin/cmd-utils.o -o ./bin/app.exe
