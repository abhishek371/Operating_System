#include<stdio.h>
#include<stdlib.h>

struct Node {
    int from;
    int size;
    struct Node *nxt;
};
#define store struct Node

store *freeMem, *allocated;

void insertSorted(store *node, int from, int size) {
    if (!node) {
        store *tmp = (store *) malloc(sizeof(store));
        tmp->from = from;
        tmp->size = size;
        freeMem = tmp;
    } else if ((node->from < from && node->nxt && node->nxt->from > from) || !node->nxt) {
        store *tmp = (store *) malloc(sizeof(store));
        tmp->from = from;
        tmp->size = size;
        tmp->nxt = node->nxt;
        node->nxt = tmp;
        return;
    }
    insertSorted(node->nxt, from, size);
}

store *headInsert(store *node, int from, int size) {
    store *tmp = (store *) malloc(sizeof(store));
    tmp->from = from;
    tmp->size = size;
    tmp->nxt = node;
    return tmp;
}

store *indexDelete(store *node, int index) {
    int c = 1;
    while (1) {
        if (c == index) {
            store *tmp = node->nxt;
            node->nxt = node->nxt->nxt;
            return tmp;
        }
        c++;
        node = node->nxt;
    }
}

void print(store *node, int from) {
    if (!node) {
        return;
    }
    if (from) {
        printf("%d ", node->from);
    }
    printf("%d\n", node->size);
    print(node->nxt, from);
}

void combine(store *node) {
    if (node->size == 0) {
        if (node->nxt) {
            node->from = node->nxt->from;
            node->size = node->nxt->size;
            node->nxt = node->nxt->nxt;
        } else {
            freeMem = NULL;
        }
    } else if (node->nxt && node->from + node->size == node->nxt->from) {
        node->size += node->nxt->size;
        node->nxt = node->nxt->nxt;
        combine(node);
    } else if (node->nxt) {
        combine(node->nxt);
    }
}

int listLen(store *node) {
    int l = 0;
    while (node) {
        l++;
        node = node->nxt;
    }
    return (l);
}

store *firstF(store *node, int size) {
    while (node) {
        if (node->size >= size && size > 0) {
            return node;
        } else {
            node = node->nxt;
        }
    }
    return (NULL);
}

store *bestF(store *node, int size) {
    int min = 1000;
    store *tmp = NULL;
    while (node) {
        if (node->size - size < min && node->size - size >= 0 && size > 0) {
            min = node->size - size;
            tmp = node;
        } else {
            node = node->nxt;
        }
    }
    return (tmp);
}

store *worstF(store *node, int size) {
    int max = -1;
    store *tmp = NULL;
    while (node) {
        if (node->size - size > max && node->size - size >= 0 && size > 0) {
            max = node->size - size;
            tmp = node;
        } else {
            node = node->nxt;
        }
    }
    return (NULL);
}

main() {
    printf("\nTotal memory : 1000 Units \n");
    freeMem = headInsert(NULL, 1, 1000);
    int loop = 1;
    while (loop) {

        // combine free spaces
        combine(freeMem);

        // print free memory
        print(freeMem, 1);

        int c;
        printf("\n\n1. Add a new process\n2. Remove process\n3. Exit\nEnter choice: ");
        scanf("%d", &c);
        switch (c) {
            case 1:
                printf("\nEnter  size of process: ");
                int s;
                scanf("%d", &s);
                printf("\nEnter fit to use:\n1. First fit\n2. Best fit\n3. Worst fit\n$ ");
                int f;
                scanf("%d", &f);
                store *r = NULL;
                switch (f) {
                    case 1:
                        r = firstF(freeMem, s);
                        break;
                    case 2:
                        r = bestF(freeMem, s);
                        break;
                    case 3:
                        r = worstF(freeMem, s);
                        break;
                    default:
                        printf("\nInvalid\n");
                        break;
                }
                if (!r) {
                    printf("\nMemory  not  allocated\n\n");
                } else {
                    // allocate memory
                    allocated = headInsert(allocated, r->from, s);
                    r->from += s;
                    r->size -= s;
                    printf("Memory allocated\n\n");
                }
                break;
            case 2:
                if (listLen(allocated) > 0) {
                    printf("\nRunning processes:\n");
                    print(allocated, 0);
                    printf("\n\nEnter index of process to be stopped: ");
                    int p;
                    scanf("%d", &p);
                    // stop process
                    if (p == 0) {
                        insertSorted(freeMem, allocated->from, allocated->size);
                        allocated = allocated->nxt;
                    } else {
                        store *tmp = indexDelete(allocated, p);
                        if (freeMem->from < tmp->from) {
                            insertSorted(freeMem, tmp->from, tmp->size);
                        } else {
                            freeMem = headInsert(freeMem, tmp->from, tmp->size);
                        }
                    }
                } else {
                    printf("\nNo running processes!\n");
                }
                break;
            case 3:
                loop = 0;
                break;
            default:
                printf("\nInvalid input\n\n");
                break;
        }
    }
}
