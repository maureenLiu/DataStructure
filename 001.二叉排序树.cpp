/*************************************************************************
	> File Name: 001.二叉排序树.cpp
	> Author: Maureen 
	> Mail: Maureen@qq.com 
	> Created Time: 三  2/17 11:48:12 2021
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define KEY(node) node ? node->key : 0
#define SIZE(node) (node ? node->size : 0)

typedef struct Node {  
    int key;
    int size; //统计每棵树的节点个数
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->size = 1;
    p->lchild = p->rchild = NULL;
    return p;
}

void update_size(Node *root) {
    root->size = SIZE(root->lchild) + SIZE(root->rchild) + 1;
    return ;
}

Node *insert(Node *root, int key) {
    if (root == NULL) return getNewNode(key);
    if (key == root->key) return root;
    if (key < root->key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    update_size(root);
    return root;
}

int search(Node *root, int key) {
    if (root == NULL) return 0;
    if (key == root->key) return 1;
    if (key < root->key) return search(root->lchild, key);
    return search(root->rchild, key);
} 

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NULL) return NULL;
    if (key < root->key) root->lchild = erase(root->lchild, key);
    else if (key > root->key) root->rchild = erase(root->rchild, key);
    else {
        //删除度为0和1的节点
        if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else { //删除度为2的节点
            //找到要删除的节点的前驱
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    update_size(root);
    return root;
}


void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void inorder_traversal(Node *root) {
    if (root == NULL) return ;
    inorder_traversal(root->lchild);
    printf("(%d[%d], %d, %d)\n", KEY(root), SIZE(root), KEY(root->lchild), KEY(root->rchild));
    inorder_traversal(root->rchild);
    return ;
}

int main() {
    int op, val;
    Node *root = NULL;
    while (~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 0: {
                root = insert(root, val);
            } break;
            case 1: {
                root = erase(root, val);
            } break;
            case 2: {
                printf("Search Result: %d\n", search(root, val));
            } break;
        }
        if (op != 2) {
            inorder_traversal(root); 
        }
    }

    return 0;
}
