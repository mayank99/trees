#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "queue.h"

void srandom(unsigned int);
long int random(void);

int
main(void)
    {
    srandom(1);
    //simple INTEGER test of BST
    BST *p = newBST(compareINTEGER);
    setBSTdisplay(p,displayINTEGER);
    setBSTfree(p,freeINTEGER);
    insertBST(p,newINTEGER(3));
    insertBST(p,newINTEGER(2));
    debugBST(p,1);
    printf("debug (in-order): ");
    displayBST(p,stdout);
    printf("\n");
    debugBST(p,0);
    printf("BST:\n");
    displayBST(p,stdout);
    INTEGER *q = newINTEGER(2);
    printf("is ");
    displayINTEGER(q,stdout);
    printf(" present? %s\n",findBST(p,q) == 0? "no" : "yes");
    INTEGER *r = newINTEGER(3);
    if (locateBST(p,r) != 0)
        {
        INTEGER *x = findBST(p,r);
        deleteBST(p,r);
        freeINTEGER(x);
        }
    debugBST(p,1);
    printf("debug (in-order): ");
    displayBST(p,stdout);
    printf("\n");
    debugBST(p,0);
    printf("BST:\n");
    displayBST(p,stdout);
    printf("is ");
    displayINTEGER(q,stdout);
    printf(" present? %s\n",findBST(p,q) == 0? "no" : "yes");
    setINTEGER(r,2);
    if (locateBST(p,r) != 0)
        {
        INTEGER *x = findBST(p,r);
        deleteBST(p,r);
        freeINTEGER(x);
        }
    debugBST(p,1);
    printf("debug (in-order): ");
    displayBST(p,stdout);
    printf("\n");
    debugBST(p,0);
    printf("BST:\n");
    displayBST(p,stdout);
    printf("is ");
    displayINTEGER(q,stdout);
    printf(" present? %s\n",findBST(p,q) == 0? "no" : "yes");
    printf("size: %d\n",sizeBST(p));
    statisticsBST(p,stdout);
    freeINTEGER(q);
    freeINTEGER(r);
    freeBST(p);
    return 0;
    }
