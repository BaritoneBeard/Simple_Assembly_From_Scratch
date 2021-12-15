# SimpleAssemblyFromScratch
Creating an Assembly Language

Code copyright by Margaret Black, Nicholas Almeder.

<h3> emulator.c </h3>

there is code that will turn bits into methods able to be coded with.

<h3> program.txt </h3>

there is the human-readable breakdown of the bits that are being made into methods

# Instructions

```ADD``` ```0111aabb```: adds value equal to register aa to value equal to register bb, stores result in register aa.

```SUB``` ```0001aabb```: subtracts value equal to register aa from value equal to register bb, stores result in register aa.

```STORE``` ```0011aabb```: stores bits from register aa into memory at address equal to register bb.

```LOAD``` ```0010aabb```: loads memory from adress equal to register aa into register bb.

```SKIP``` ```0100xx00```: skips the next instruction if register xx is equal to 0.

```SKIPNZ``` ```0100xx01```: skips the next instruction if register xx is not equal to 0.

```JALR``` ```0101aaaa```: jumps to line at location equal to register aa.

```SLI``` ```11aabbcc```: takes bits aa and cc and stores them into register bb.

```HALT``` ```00000001```: halts the program. This is when the program knows to stop parsing.



Emulator, Pipeline, and Cycle purposely do not have instructions, ask for a demonstration.
