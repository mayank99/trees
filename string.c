#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include "string.h"

struct STRING
    {
    char *value;
    };

STRING *
newSTRING(char *x)
    {
    STRING *p = malloc(sizeof(STRING));
    assert(p != 0);
    p->value = x;
    return p;
    }

char * 
getSTRING(STRING *v)
    {
    return v->value;
    }

char * 
setSTRING(STRING *v,char *x)
    {
    char *old = v->value;
    v->value = x;
    return old;
    }

void 
displaySTRING(void *v,FILE *fp)
    {
    fprintf(fp,"%s",getSTRING((STRING *) v));
    }


int 
compareSTRING(void *v,void *w)
    {
    return strcmp(getSTRING(v), getSTRING(w));
    }


void
freeSTRING(void *v)
    {
    free((STRING *) v);
    }
