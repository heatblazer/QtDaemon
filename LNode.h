#ifndef LNODE_H
#define LNODE_H
typedef struct LNode {
    int index;
    char* data;
    char* begin;
    LNode* next;

} LNode;

#endif // LNODE_H
