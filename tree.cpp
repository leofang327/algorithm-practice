#include <iostream>
#include <cstdio>
using namespace std;
#define maxSize 1001

typedef struct BTNode { // 二叉树结点定义
    int data;
    struct BTNode *lchild;
    struct BTNode *rchild;
} BTNode;

typedef struct St {
    BTNode *p;
    int lno; // 结点层号
} St;

// 层次遍历
void BFS(BTNode *t) {
    BTNode *Q[1001], *p; // Q是一个容量足够大的队列
    int front, rear;
    if (!t) return;
    front = rear = -1;
    Q[++rear] = t;
    while (front != rear) {
        p = Q[++front];
        printf("%d ", p->data);
        if (p->lchild) Q[++rear] = p->lchild;
        if (p->rchild) Q[++rear] = p->rchild;
    }
}

// 求二叉树宽度(利用层次遍历)
int btWidth(BTNode *T) {
    BTNode *q;
    St que[maxSize];
    int front = -1, rear = -1;
    int Lno, i, j, max, count;
    if (!T) return 0;
    que[++rear].p = T;
    que[rear].lno = 1;
    while (front != rear) {
        q = que[++front].p;
        Lno = que[front].lno; // 出队时记录层号
        if (q->lchild) {
            que[++rear].p = q->lchild;
            que[rear].lno = Lno+1; // 子结点层号=父结点层号+1
        }
        if (q->rchild) {
            que[++rear].p = q->rchild;
            que[rear].lno = Lno+1;
        }
    }
    max = 0;
    for (i = 1; i <= Lno; i++) { // 一共Lno层
        count = 0; // 记录层号为i的结点数
        for (j = 0; j <= rear; j++) {
            if (que[j].lno == i) count++;
        }
        // 更新最宽层结点数
        if (max < count) max = count;
    }
    return max;
}

// 求二叉树高度递归写法
int btHeight1(BTNode *T)
{
    int l, r;
    if (!T) return 0;
    else {
        l = btHeight1(T->lchild);
        r = btHeight1(T->rchild);
        return (l > r ? l : r) + 1;
    }
}

// 求二叉树高度非递归写法(利用层次遍历)
int btHeight2(BTNode *T)
{
    int front = -1, rear = -1;
    int last = 0, level = -1;
    BTNode *Q[maxSize], *p;
    if (!T) return 0;
    Q[++rear] = T;
    while (front != rear) {
        p = Q[++front];
        if (p->lchild) Q[++rear] = p->lchild;
        if (p->rchild) Q[++rear] = p->rchild;
        if (front == last) { // 刚出队的是该层最右的结点
            level++;
            last = rear; // 更新last
        }
    }
    return level;
}

#define maxn 50
int in[maxn] = {4,2,5,1,6,3,7,8}; // 中序遍历序列
int post[maxn] = {4,5,2,6,8,7,3,1}; // 后序遍历序列
int n = 8;

BTNode *createTree(int postL, int postR, int inL, int inR)
{
    BTNode *root;
    int k = 0, leftLen;
    if (postL > postR) return nullptr;
    root = (BTNode *)malloc(sizeof(BTNode));
    root->data = post[postR];
    for (k = inL; k <= inR; k++) {
        if (in[k] == post[postR]) break;
    }
    leftLen = k - inL;
    root->lchild = createTree(postL, postL+leftLen-1, inL, k-1);
    root->rchild = createTree(postL+leftLen, postR-1, k+1, inR);
    return root;
}

// 主调函数
int main() {
    BTNode *t = createTree(0, n-1, 0, n-1);
    BFS(t);
    printf("\n%d", btHeight1(t));
    return 0;
}
