#include <stdio.h>
#include <stdlib.h>

struct Node{
    int key;
    int height;
    struct Node* left;
    struct Node* right;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct Node* node) {
    if(node == NULL) {
        return 0;
    } else {
        return node->height;
    }
}

int getBalance(struct Node* node) {
    if(node == NULL) {
        return 0;
    } else {
        return height(node->left) - height(node->right);
    }
}

struct Node* rotateRight(struct Node* node) {
    struct Node* leftChild = node->left;
    struct Node* subTree = leftChild->right;

    leftChild->right = node;
    node->left = subTree;

    node->height = max(height(node->left), height(node->right)) + 1;
    leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;

    return leftChild;
}

struct Node* rotateLeft(struct Node* node) {
    struct Node* rightChild = node->right;
    struct Node* subTree = rightChild->left;

    rightChild->left = node;
    node->right = subTree;

    node->height = max(height(node->left), height(node->right)) + 1;
    rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;

    return rightChild;
}

struct Node* createNewNode(int key) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insertNode(struct Node* node, int key) {
    if(node == NULL) {
        return createNewNode(key);
    }

    if(key < node->key) {
        node->left = insertNode(node->left, key);
    } else if(key > node->key) {
        node->right = insertNode(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balanceFactor = getBalance(node);

    if(balanceFactor > 1 && key < node->left->key) {
        return rotateRight(node);
    }
    if(balanceFactor < -1 && key > node->right->key) {
        return rotateLeft(node);
    }
    if(balanceFactor > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if(balanceFactor < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void preOrder(struct Node* node) {
    if(node != NULL) {
        printf("%d ", node->key);
        preOrder(node->left);
        preOrder(node->right);
    }
}

int main() {
    struct Node* root = NULL;

    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 25);

    preOrder(root);
    return 0;
}
