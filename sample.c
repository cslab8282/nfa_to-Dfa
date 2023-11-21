#include <stdio.h>
#include <stdlib.h>

struct node {
    int st;
    struct node *link;
};

struct node1 {
    int nst[20];
};

void insert(int, char, int);
int findalpha(char);
void findfinalstate(void);
int insertdfastate(struct node1);
int compare(struct node1, struct node1);
void printnewstate(struct node1);

static int set[20], nostate, noalpha, s, notransition, nofinal, start, finalstate[20], c, r;
int complete = -1;
char alphabet[20];
struct node1 hash[20];
struct node *transition[20][20] = {NULL};

void main() {
    struct node *temp;
    struct node1 newstate = {0}, tmpstate = {0};

    printf("Enter the number of alphabets? (use 'e' as epsilon)\n");
    printf("Enter No of alphabets and alphabets?\n");
    scanf("%d", &noalpha);
    getchar();
    for (int i = 0; i < noalpha; i++) {
        alphabet[i] = getchar();
        getchar();
    }
    printf("Enter the number of states, start state, number of final states, and final states?\n");
    scanf("%d %d %d", &nostate, &start, &nofinal);
    for (int i = 0; i < nofinal; i++)
        scanf("%d", &finalstate[i]);
    printf("Enter the number of transitions?\n");

    scanf("%d", &notransition);
    printf("Enter transitions in the form: qno alphabet qno\n");

    for (int i = 0; i < notransition; i++) {
        scanf("%d %c%d", &r, &c, &s);
        insert(r, c, s);
    }

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            hash[i].nst[j] = 0;

    complete = -1;
    int i = -1;
    printf("\nEquivalent DFA.....\nTrnsitions of DFA\n");

    newstate.nst[start] = start;
    insertdfastate(newstate);

    while (i != complete) {
        i++;
        newstate = hash[i];
        for (int k = 0; k < noalpha; k++) {
            c = 0;
            for (int j = 1; j <= nostate; j++)
                set[j] = 0;

            for (int j = 1; j <= nostate; j++) {
                int l = newstate.nst[j];
                if (l != 0) {
                    temp = transition[l][k];
                    while (temp != NULL) {
                        if (set[temp->st] == 0) {
                            c++;
                            set[temp->st] = temp->st;
                        }
                        temp = temp->link;
                    }
                }
            }
            printf("\n");
            if (c != 0) {
                for (int m = 1; m <= nostate; m++)
                    tmpstate.nst[m] = set[m];

                if (insertdfastate(tmpstate)) {
                    printnewstate(newstate);
                    printf("%c\t", alphabet[k]);
                    printnewstate(tmpstate);
                    printf("\n");
                }
            } else {
                printnewstate(newstate);
                printf("%c\tNULL\n", alphabet[k]);
            }
        }
    }

    printf("\nStates of DFA:\n");
    for (int i = 0; i <= complete; i++)
        printnewstate(hash[i]);

    printf("\nAlphabets:\n");
    for (int i = 0; i < noalpha; i++)
        printf("%c\t", alphabet[i]);

    printf("\nStart State: q%d\n", start);

    printf("Final states:\n");
    findfinalstate();
}

int insertdfastate(struct node1 newstate) {
    for (int i = 0; i <= complete; i++)
        if (compare(hash[i], newstate))
            return 0;

    hash[++complete] = newstate;
    return 1;
}

int compare(struct node1 a, struct node1 b) {
    for (int i = 1; i <= nostate; i++)
        if (a.nst[i] != b.nst[i])
            return 0;

    return 1;
}

void insert(int r, char c, int s) {
    int j = findalpha(c);
    if (j == 999) {
        printf("error\n");
        exit(0);
    }

    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->st = s;
    temp->link = transition[r][j];
    transition[r][j] = temp;
}

int findalpha(char c) {
    for (int i = 0; i < noalpha; i++)
        if (alphabet[i] == c)
            return i;

    return 999;
}

void findfinalstate() {
    for (int i = 0; i <= complete; i++)
        for (int j = 1; j <= nostate; j++)
            for (int k = 0; k < nofinal; k++)
                if (hash[i].nst[j] == finalstate[k]) {
                    printnewstate(hash[i]);
                    printf("\t");
                    j = nostate;
                    break;
                }
}

void printnewstate(struct node1 state) {
    printf("{");
    for (int j = 1; j <= nostate; j++)
        if (state.nst[j] != 0)
            printf("q%d,", state.nst[j]);
    printf("}\t");
}
