# BrainFuck Compiler in C++

## Dependancy
- This Compiler for brainfuck requires the NASM Assembler to assemble the executable and ld to link the main.o into a valid elf.
- This Project is built using make.

## Build
- Run make build-main to compile the compiler. it will create an executable called bfc.
- run mak asm if you have NASM and ld to turn the main.asm file into a valid executable.

## Alternate Build
- Run the build.sh to make the executable if you don't have make.

## Usage
- You can also use make to run the compiler through make
``` bash
make build-run args="[bf source code]"
```
or directly use the bfc executable.
``` bash
bfc [bf source code].
```
- The bfc executable can be freely moved and used anywhere since it does require anything after been compiled.
- The bfc will produce a simple NASM main.asm file from a single bf source file, you will need NASM and ld to turn it into a valid executable.

# Example
The Project has a HelloWorld.bf file that can be used to test the compiler.
``` bash
make build-run args="HelloWorld.bf"
make asm
./main
```
or
``` bash
bfc "HelloWorld.bf"
nasm -f elf64 main.asm -o main.o
ld main.o -o main
chmod +x main
./main
```
once run it should output
``` bash
Hello World!
```
