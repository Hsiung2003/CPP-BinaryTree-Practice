#include "BinaryTree.h"
using namespace std;

template<typename K, typename V>
BinaryTree<K, V>::BinaryTree() {
    makeEmpty();
}

/**
 *  Returns the number of entries stored in the dictionary.  Entries with
 *  the same key (or even the same key and value) each still count as
 *  a separate entry.
 *  @return number of entries in the dictionary.
 **/
template<typename K, typename V>
int BinaryTree<K, V>::size() {
    return tsize;
}

/**
 *  Tests if the dictionary is empty.
 *
 *  @return true if the dictionary has no entries; false otherwise.
 **/
template<typename K, typename V>
bool BinaryTree<K, V>::isEmpty() {
    return size() == 0;
}

template<typename K, typename V>
void BinaryTree<K, V>::insertHelper(Entry<K, V>* entry, const K& key, BinaryTreeNode<K, V>* node) {
    if (key.compareTo(node->entry->getkey()) <= 0) {
        if (node->leftChild == NULL) {
            node->leftChild = new BinaryTreeNode<K, V>(entry, node);
        }
        else {
            insertHelper(entry, key, node->leftChild);
        }
    }
    else {
        if (node->rightChild == NULL) {
            node->rightChild = new BinaryTreeNode<K, V>(entry, node);
        }
        else {
            insertHelper(entry, key, node->rightChild);
        }
    }
}

/**
 *  Create a new Entry object referencing the input key and associated value,
 *  and insert the entry into the dictionary.
 *  Multiple entries with the same key (or even the same key and
 *  value) can coexist in the dictionary.
 *
 *  @param key the key by which the entry can be retrieved.
 *  @param value an arbitrary object.
 **/
template<typename K, typename V>
void BinaryTree<K, V>::insert(const K& key, const V& value) {
    Entry<K, V>* entry = new Entry<K, V>(key, value);
    if (root == NULL) {
        root = new BinaryTreeNode<K, V>(entry);
    }
    else {
        insertHelper(entry, key, root);
    }
    tsize++;
}

/**
 *  Search for a node with the specified key, starting from "node".  If a
 *  matching key is found (meaning that key1.compareTo(key2) == 0), return
 *  a node containing that key.  Otherwise, return null.
 *
 *  Be sure this method returns null if node == null.
 **/
template<typename K, typename V>
BinaryTreeNode<K, V>* BinaryTree<K, V>::findHelper(const K& key, BinaryTreeNode<K, V>* node) {
    if (node == NULL) {
        return NULL;
    }
    int compareResult = key.compareTo(node->entry->getkey());
    if (compareResult == 0) {
        return node;
    }
    else if (compareResult < 0) {
        return findHelper(key, node->leftChild);
    }
    else {
        return findHelper(key, node->rightChild);
    }
    return NULL;
}

/**
 *  Search for an entry with the specified key.  If such an entry is found,
 *  return true; otherwise return false.
 *
 *  @param key the search key.
 *  @return an entry containing the key and an associated value, or null if
 *          no entry contains the specified key.
 **/
template<typename K, typename V>
Entry<K, V>* BinaryTree<K, V>::find(const K& key) {
    BinaryTreeNode<K, V>* node = findHelper(key, root);
    if (node == NULL) {
        return NULL;
    }
    else {
        return node->entry;
    }
}

/**
 *  Remove an entry with the specified key.  If such an entry is found,
 *  remove it from the table.
 *  If several entries have the specified key, choose one arbitrarily, then
 *  remove it.
 *
 *  @param key the search key.
 */
template<typename K, typename V>
void BinaryTree<K, V>::remove(const K& key) {
    BinaryTreeNode<K, V>* node = findHelper(key, root);
    //BinaryTreeNode<K, V>* temp = NULL;

    if (node == NULL) {
        return;
    }
    //two children
    if (node->leftChild != NULL && node->rightChild != NULL) {
        BinaryTreeNode<K, V>* successor = node->rightChild;
        while (successor->leftChild != NULL) {
            successor = successor->leftChild;
        }
        //update parent of the successor's right child
        if (successor->parent != node) {
            successor->parent->leftChild = successor->rightChild;
            if (successor->rightChild != NULL) {
                successor->rightChild->parent = successor->parent;
            }
        }
        else {
            //the sucessor is the immediate right child of the node to remove
            node->rightChild = successor->rightChild;
            if (successor->rightChild != NULL) {
                successor->rightChild->parent = node;
            }
        }
        node->entry = successor->entry;
        node = successor;
    }

    //one or no children
    else {
        BinaryTreeNode<K, V>* child = NULL;
        if (node->leftChild != NULL)
            child = node->leftChild;
        else if (node->rightChild != NULL)
            child = node->rightChild;

        if (node->parent != NULL) {
            if (node == root) {
                root = child;
            }
            else {
                BinaryTreeNode<K, V>* parent = node->parent;
                if (parent->leftChild == node) {
                    parent->leftChild = child;
                }
                else {
                    parent->rightChild = child;
                }
                if (child != NULL) {
                    child->parent = parent;
                }
            }
            delete node;
        }
        tsize--;
        return;
    }
}
/**
    *  Remove all entries from the dictionary.
    */
template<typename K, typename V>
void BinaryTree<K, V>::makeEmpty() {
    makeEmptyHelper(root);
    root = NULL;
    tsize = 0;
}

template<typename K, typename V>
void BinaryTree<K, V>::makeEmptyHelper(BinaryTreeNode<K, V>* node) {
    if (node != NULL) {
        makeEmptyHelper(node->leftChild);
        makeEmptyHelper(node->rightChild);
        delete node;
    }
}

/**
    *  Convert the tree into a string.
    **/
template<typename K, typename V>
std::string BinaryTree<K, V>::toString() {
    if (root == NULL) {
        return "";
    }
    else {
        return root->toString();
    }
}

