#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <climits>
 
template <typename K, typename V>
class skipListNode{
public:
    skipListNode() {}   // or skipListNode();
    skipListNode(K key, V val, int node_level);
    ~skipListNode();
 
    // keep the first node's key in each level
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
 
 
 
template <typename K, typename V>
class skipList {
public:    
    skipList(int);
    ~skipList();
     
    int random_level_generate();
    skipListNode<K, V> *create_node(K, V, int);
    int find_node(K);
    int insert_node(K, V);
     
private:
    int max_level;
    int skipList_level;
    skipListNode<K, V> *skiplist_head;
    int skiplist_size;
};
 
template <typename K, typename V>
skipList<K, V>::skipList(int max_level) {
    this->max_level = max_level;
    this->skipList_level = 0;
    this->skiplist_size = 0;
    // K k;
    // V v;
    this->skiplist_head = new skipListNode<K, V>(INT_MAX, INT_MAX, max_level);
}
 
template <typename K, typename V>
skipList<K, V>::~skipList() {
    delete this->skiplist_head;
}
 
template <typename K, typename V>
skipListNode<K, V>* skipList<K, V>::create_node(K key, V val, int max_level) {
    skipListNode<K, V> *newNode = new skipListNode<K, V>(key, val, max_level);
     
    return newNode;
}
 
template <typename K, typename V>
int skipList<K, V>::find_node(K target_key) {
    // define a head node
    skipListNode<K, V> *cur = skiplist_head;
     
    // start from highest level, until the key of next node 
    // is bigger than what we want
    for(int i = skipList_level;i >= 0;i --) {
        while(cur->nextPtr[i] != NULL && cur->nextPtr[i]->get_key() < target_key) {
            cur = cur->nextPtr[i];
        }
        // jump to lower level
    }
     
    if (cur->nextPtr[0] != NULL && cur->nextPtr[0]->get_key() == target_key) {
        return 1;
    }
     
    return 0;
}
 
template <typename K, typename V>
int skipList<K, V>::insert_node(K in_key, V in_val) {
    // define a head node
    skipListNode<K, V> *cur = skiplist_head;
    // keep the previous node of insert position
    // no need to be a pointer
    skipListNode<K, V> *keep_pre[max_level+1];
    memset(keep_pre, 0, sizeof(skipListNode<K, V> *) * (max_level + 1));
     
    // start from highest level, until the key of next node 
    // is bigger than what we want
    for (int i = skipList_level;i >= 0;i --) {
        while (cur->nextPtr[i] != NULL && cur->nextPtr[i]->get_key() < in_key) {
            cur = cur->nextPtr[i];
        }
        // cur is the previous node of insert node
        keep_pre[i] = cur;
        // jump to lower level
    }
     
    if (cur->nextPtr[0] != NULL && cur->nextPtr[0]->get_key() == in_key) {
        // already exist, insert failed
        return 1;
    }
     
    int random_level = random_level_generate();
    if (random_level > skipList_level) {
        for (int i = random_level;i > skipList_level;i --) {
            keep_pre[i] = skiplist_head;
        }
        // update the skiplist level to higher one
        skipList_level = random_level;
    }
     
    skipListNode<K, V> * inserted_node = create_node(in_key, in_val, random_level);
    for (int i = random_level;i >= 0;i --) {
        inserted_node->nextPtr[i] = keep_pre[i]->nextPtr[i];
        keep_pre[i]->nextPtr[i] = inserted_node;
    }
     
    skiplist_size ++;
     
    return 0;
}

template<typename K, typename V>
int skipList<K, V>::random_level_generate(){
    int level = 1;
    while (rand() % 2) {
        level ++;
    }
    level = (level < max_level) ? level : max_level;
    
    return level;
};

 
 
int main() {
    int N, M;
    skipList<int, int> *skip_list = new skipList<int, int>(16);
    std::cin >> N >> M;
     
    for (int i = 0; i < N; i++) {
        int key;
        int value;
        std::cin >> key >> value;
        if (skip_list->insert_node(key, value) == 0) {
            std::cout << "Insert Success" << std::endl;
        } else {
            std::cout << "Insert Failed" << std::endl;
        }
    }
 
    for (int i = 0; i < M; i++) {
        int key;
        std::cin >> key;
        if (skip_list->find_node(key)) {
            std::cout << "Search Success" << std::endl;
        } else {
            std::cout << "Search Failed" << std::endl;
        }
    }   
    return 0;
}