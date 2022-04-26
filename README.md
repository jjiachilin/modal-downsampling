divide a d dimensional array into 

input: 
- d dimensional image
- L is log2(shape(d))
- I downsampled image is defined as the image of size (2^(Ln-1)) for n in (1,d)

ie. 2d dimensional image size (4,8)
     L1 = log2(4) = 2
     L2 = log2(8) = 3

output:
yield I downsampled images where I = 1,…,min{Ln}

ie. I = 1, 2
then 1 downsampled image divides original image into 2x2 blocks and chooses most common value in that block 
then 2 downsampled image divides original image into 4x4 block and chooses most common value in that block

some assumptions i make: the input image is divisible into blocks of powers of 2’s

tasks:
- try brute force implementation single threaded for single I
    - just split into blocks, take mode (hash table), add to new, smaller array
- do single threaded for multiple I
- get familiar with multithreading library
- multithread the parts for different I
- multithread finding the modes of each block

Multithreading structure:
- root thread -> responsible for splitting blocks for different values of I
                - gives the split blocks to child thread for each value of I
                - child thread spawns child threads per block to process
- data structures
    - original image should be shared among the child threads and never mutated
    - each child thread should have its own output array which is passed to parent
    - each child child thread should have a hash table kept which is created and destroyed with its lifecycle
- theres no shared writing to data structures so we should not have data races

OOP details:
- have separate classes for splitting task, downsampling task, mode task

Implementation details:
- MAKE EFFICIENT USE OF RAM, i guess this means child threads access the same data structure on the heap

aspects of evaluation:
- organization
- oop
- memory management
    - prob just means freeing memory when its no longer needed -> in child child threads


Usage:
give a txt file as argument to the executable
main parses the txt file into a boost multi array
