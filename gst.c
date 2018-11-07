
#include "gst.h"
#include "bst.h"

typedef struct gst GST;

GST *newGST(int (*c)(void *, void *));
void setGSTdisplay(GST *t, void (*d)(void *, FILE *));
void setGSTswapper(GST *t, void (*s)(TNODE *, TNODE *));
void setGSTfree(GST *t, void (*)(void *));
TNODE *getGSTroot(GST *t);
void setGSTroot(GST *t, TNODE *replacement);
void setGSTsize(GST *t, int s);
TNODE *insertGST(GST *t, void *value);
void *findGST(GST *t, void *key);
TNODE *locateGST(GST *t, void *key);
int deleteGST(GST *t, void *key);
TNODE *swapToLeafGST(GST *t, TNODE *node);
void pruneLeafGST(GST *t, TNODE *leaf);
int sizeGST(GST *t);
void statisticsGST(GST *t, FILE *fp);
void displayGST(GST *t, FILE *fp);
int debugGST(GST *t, int level);
void freeGST(GST *t);

/* extensions of BST */
void *unwrapGST(TNODE *n);
int freqGST(GST *g, void *key);
int duplicatesGST(GST *g);