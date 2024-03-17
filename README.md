# p4dummy
P4Dummy showcases how a p4-formatter can be written for the official P4 compiler ([P4C](https://github.com/p4lang/p4c)). It does nothing but apply a series of compiler checks and echo the final version of the program using [toP4.cpp](https://github.com/p4lang/p4c/blob/main/frontends/p4/toP4/toP4.cpp).

## Requirements
P4Dummy is written as an extension to [P4C](https://github.com/p4lang/p4c). It has no other dependencies. P4C extensions are symlinked into the `extensions` folder of P4C and are automatically picked up once CMake is run. An example workflow could be:
```
cd p4c/
mkdir extensions
cd extensions
git clone https://github.com/Anshul-Johri-1/p4dummy
cd p4c/build
cmake ..
make -j4
```
This assumes that P4C is setup correctly Instructions can be found [here](https://github.com/p4lang/p4c#dependencies).

Afterwards, the `p4dummy` executable can be found in the `p4c/build`folder.

## Usage
Executing P4Dummy will simply output p4 program. If an output file is passed as argument, it will output the p4 program to the specified file, otherwise it will echo the program.
```
./build/p4dummy input.p4
# This will output program to terminal


./build/p4dummy input.p4 output.p4
# This will output program to output.p4
```
#### Note: 
This repository is modified from https://github.com/fruffy/p4dummy/
