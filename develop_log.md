# K-V SkipList
## Introduction


## Key Point
### Apr 10th

#### Create New File and Remote
a. git init

b. git remote add origin Url

c. ssh protocol (.isa)

d. git add .

e. git command -m " "

f. git push

#### Semicolon
a. Class declarations introduce a new type. The semicolon at the end of a class declaration is part of the syntax that defines a complete declaration, similar to how a semicolon completes a variable declaration or a function prototype.

b. Method implementations within a class are considered complete once the closing brace of the method's body is reached. The syntax for a method body does not include a semicolon as part of its definition, whether it's defined inside or outside of the class declaration.

c. for example:
skipListNode() {}

#### why 'node_level+1'?

this->skipList = new skipListNode<K, V> *[node_level+1];

the default level is 0, which includes all the nodes. If the level for one node is k, it means this node will present at level 0, 1, ..., k