This is the command line minesweeper Version 1.0

To enjoy this wonder, you need to have g++ installed and add its directory to the PATH.

If it is not installed download it from here: https://sourceforge.net/projects/mingw-w64/

Then follow these instructions to add the folder that contains the g++.exe to the PATH: 

https://codingbee.net/powershell/powershell-make-a-permanent-change-to-the-path-environment-variable

To compile the files, go to the folder where you downloaded them and execute

g++ -c Cell.cpp Grid.cpp Mat2D.cpp main.cpp

Then make the executable with

g++ -o minesweeper.exe Cell.o Grid.o Mat2D.o Main.o

Finally execute .\cmd_minesweeper.exe

HAVE FUN!!!
