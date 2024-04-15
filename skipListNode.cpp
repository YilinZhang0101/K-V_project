#include <cstring>
#include <iostream>
#include <cstdlib>

template <typename K, typename V>
class skipListNode{
public:
    skipListNode() {}   // or skipListNode();
    skipListNode(K key, V val, int node_level);
    ~skipListNode();

    skipListNode<K, V> ** nextPtr;
    int node_level;

    K get_key() const;
    V get_value() const;
    void set_value(V val);

private:
    K key;
    V val;
};

template <typename K, typename V> 
//to ensure that the key and val arguments are not modified within the constructor.
//copy is expensive
skipListNode<K, V>::skipListNode(const K key, const V val, int node_level) {
    this->key = key;
    this->val = val;
    this->node_level = node_level;
    this->nextPtr = new skipListNode<K, V>  *[node_level + 1];
    // each element of the array is a pointer to a skipListNode<K, V> object. 
    int size = sizeof(skipListNode<K, V>*) * (node_level + 1);
    memset(this->nextPtr, 0, size);
};

template <typename K, typename V>
//do not modify any member variables of the class instances on which they are called.
skipListNode<K, V>::~skipListNode() {
    delete[] nextPtr;
};

template <typename K, typename V>
//do not modify any member variables of the class instances on which they are called.
K skipListNode<K, V>::get_key() const {
    return this->key;
};

template <typename K, typename V>
V skipListNode<K, V>::get_value() const {
    return this->val;
};

template <typename K, typename V>
void skipListNode<K, V>::set_value(V val) {
    return this->val = val;
};

int main() {
    int Key, Value, Level;
    std::cin >> Key >> Value >> Level;

    skipListNode<int, int> *newNode = new skipListNode<int, int>(Key, Value, Level);
    std::cout << newNode->get_key() << " " << newNode->get_value() << std::endl;

    delete newNode;
    return 0;
}