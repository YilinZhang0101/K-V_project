# K-V SkipList
## Introduction

## a. Create New File and Remote
a. git init

b. git remote add origin Url

c. ssh protocol (.isa)

d. git add .

e. git command -m " "

f. git push

## b. Semicolon
a. Class declarations introduce a new type. The semicolon at the end of a class declaration is part of the syntax that defines a complete declaration, similar to how a semicolon completes a variable declaration or a function prototype.

b. Method implementations within a class are considered complete once the closing brace of the method's body is reached. The syntax for a method body does not include a semicolon as part of its definition, whether it's defined inside or outside of the class declaration.

c. for example:
skipListNode() {}

## c. why 'node_level+1'?

this->skipList = new skipListNode<K, V> *[node_level+1];

the default level is 0, which includes all the nodes. If the level for one node is k, it means this node will present at level 0, 1, ..., k

## d. why need {} in declaration part?
defines a default constructor for the class.

If you instantiate a skipListNode using this default constructor, you must ensure that skipList is properly initialized before using it, to avoid undefined behavior (such as segmentation faults when accessing unallocated memory).

## e. 'skipListNode(K key, V val, int);'

when declaring a function or a constructor in a class definition, it only need to specify the types of the parameters.

## insert node

### initiate skiplist
create a head node, make it easy to search.

### random level
use 'rank() % 2' to realize the propability of 1/2

### array for keeping previous nodes
if random level is larger than the level of current skiplist, the exceeding part should keep head node as previous nodes