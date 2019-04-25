# Readme

Thanasis Filippidis sdi1400215@di.uoa.gr


## Compile

To compile run `make`


## Run

Command line options:
 * -l operations: filename of input file 
 * -b hashentries: integer number of hashtable

Invocation:

    ./stucs -l operations -b hashentries
	or
    ./stucs -b hashentries -l operations


## Implementation Notes


### Skiplist

For the skiplist the implementation followed was exactly the one given by the instructor's notes.The MaxLevel of the array forward is defined inside the skiplist.hpp as well as the MaxValue, the value of the terminating node.


### Hashtable

For the Hashtable there is a modification to the typical implementation. I decided to have a hash table where each cell of the table contains a list of lists of nodes, where each node is a student. Let me explain myself. Each cell has a list of all the postcodes that hash to that cell. Each node of that list is a list of a postcode, meaning that each node has a list of all the students that live in this postcode.
With this modification I have an easier access to functions that need all the students of a certain postcode because they are accessed in O(1) complexity.
