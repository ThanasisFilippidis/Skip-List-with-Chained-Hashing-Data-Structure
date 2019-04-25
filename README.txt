This strucure is intented to be used for records regarding students of our university. The max insertion complexity is O(n) where n is the number of records already in our structure. Depending on the type of queries the access cost is O(1) or O(n). For special queries of range we can have a linear cost O(k) where k is the number of records of interest.

To achieve an O(n) access to the records a skip-list (http://cgi.di.uoa.gr/~ad/k22/skiplist-note.pdf , ftp://ftp.cs.umd.edu/pub/skipLists/skiplists.pdf) was used. Moreover to achieve O(k) range queries chained hashing was used (https://en.wikibooks.org/wiki/Data_Structures/Hash_Tables#Chaining). The actions that are available to be performed in the structure are query for specific student id, modify for gpa, delete, average, find, percentile and more. For a detailed description in Greek see Εκφώνηση 1ης Εργασιας.pdf


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
