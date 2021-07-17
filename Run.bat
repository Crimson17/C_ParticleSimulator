set filename=ParticleSim
cls
gcc -I ./include ./src/*.c -o ./out/%filename%.exe -lgdi32
start ./out/%filename%.exe
