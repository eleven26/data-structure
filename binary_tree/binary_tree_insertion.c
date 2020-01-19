//
// Created by ruby on 2020/1/16.
//

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

// 二叉树节点
// BiTree: 二叉树
typedef struct BiNode {
    ElemType data;
    struct BiNode *lchild;
    struct BiNode *rchild;
} BiNode, *BiTree;

/**
 * 前序遍历二叉树
 *
 * @param biTree
 */
void PreOrderTraverse(BiTree biTree)
{
    if (biTree == NULL)
        return;

    printf("%d ", biTree->data);
    PreOrderTraverse(biTree->lchild);
    PreOrderTraverse(biTree->rchild);
}

/**
 * 中序遍历二叉树
 *
 * @param biTree
 */
void InOrderTraverse(BiTree biTree)
{
    if (biTree == NULL)
        return;

    InOrderTraverse(biTree->lchild);
    printf("%d ", biTree->data);
    InOrderTraverse(biTree->rchild);
}

/**
 * 后序遍历二叉树
 *
 * @param biTree
 */
void PostOrderTraverse(BiTree biTree)
{
    if (biTree == NULL)
        return;

    PostOrderTraverse(biTree->lchild);
    PostOrderTraverse(biTree->rchild);
    printf("%d ", biTree->data);
}

/**
 * 创建新的节点
 *
 * @param e 节点保存的数据
 * @return BiNode
 */
BiNode *NewNode(ElemType e)
{
    BiNode *biNode = (BiNode*)malloc(sizeof(BiNode));

    biNode->lchild = NULL;
    biNode->data = e;
    biNode->rchild = NULL;

    return biNode;
}

int main()
{
    // 初始化根节点
    BiTree biTree = (BiNode*)malloc(sizeof(BiNode));
    biTree->lchild = NULL;
    biTree->rchild = NULL;
    biTree->data = 10;

    // 插入节点
    biTree->lchild = NewNode(11);
    biTree->lchild->lchild = NewNode(7);
    biTree->lchild->rchild = NewNode(12);

    biTree->rchild = NewNode(9);
    biTree->rchild->lchild = NewNode(15);
    biTree->rchild->rchild = NewNode(8);

    printf("前序遍历: ");
    PreOrderTraverse(biTree);
    printf("\n");
    printf("中序遍历: ");
    InOrderTraverse(biTree);
    printf("\n");
    printf("后序遍历: ");
    PostOrderTraverse(biTree);
    printf("\n");

    return 0;
}
