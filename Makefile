all:  output

output:  JogoVelhaV4.o
        gcc -o JogoVelhaV4 JogoVelhaV4.o -lintelfpgaup

JogoVelhaV4.o: JogoVelhaV4.c utilsV4.h
        gcc -c JogoVelhaV4.c -lintelfpgaup -std=c99

clean:
        rm *.o


