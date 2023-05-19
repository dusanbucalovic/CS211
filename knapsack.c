#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct ItemType {
    char name[32];
    int weight;
    long value;
    int selected;
} ItemType;


int itemTypesSize;
int capacity;
ItemType* itemTypes;
int maxValue;
int **K;


int readFile(char*);
int knapSack(int W, ItemType *itemTypes, int n);


int main(int argc, char ** argv){
    char *input;
    int i;
    if(argc!=3) {
        printf("\nError: Invalid number of arguments!\n\n");
        return 0;
    }

    capacity = atoi(argv[1]);

    input = argv[2];

    readFile(input);

    if(itemTypesSize <= 0){
        printf("\nError: Invalid number of items!\n\n");
        return 0;
    }

    for(i = 0; i<itemTypesSize; i++) {
        if(itemTypes[i].weight <= 0 || itemTypes[i].value <= 0){
            printf("\nError: Invalid item values!\n\n");
            return 0;
        }
    }

    maxValue = knapSack(capacity, itemTypes, itemTypesSize);


    int totalWeight = 0;

   
    for(i = 0; i<itemTypesSize; i++) {
        if(itemTypes[i].selected > 0) {
            totalWeight += itemTypes[i].weight;
            printf("%s\n", itemTypes[i].name);
    }
    }

    printf("%d / %d\n",maxValue, totalWeight);

    free(itemTypes);
    for (i = 0; i <= itemTypesSize; i++){
        free(K[i]);
  }
    free(K);

    return 0;
}

int readFile(char * filename) {

    FILE *fp;
    char num[255];
    int i=0,j=0;
    char line[4096];

    fp = fopen(filename,"r");
    if(fp == NULL) {
        printf("\nERROR in opening the file!\n\n");
        return 0;
    }

    char ch;
    ch=fgetc(fp);
    
    while(ch!='\n'){
            num[j++]=ch;
            ch=fgetc(fp);
    }
    num[j]='\n';
    itemTypesSize = atoi(num);

    

    itemTypes = malloc(itemTypesSize * sizeof *itemTypes); 
    for (i = 0; i < itemTypesSize; i++)
    {
        if(fgets(line, sizeof(line), fp) == NULL)
             return -1;

        if (sscanf(line, "%31s %d %ld",itemTypes[i].name, &itemTypes[i].weight, &itemTypes[i].value) != 3)
            return -1;
    itemTypes[i].selected = 0;
    }
    return 0;
}

// Returns the maximum value that
// can be put in a knapsack of capacity W
//int knapSack(int W, int wt[], int val[], int n)
int knapSack(int W, ItemType *itemTypes, int n)
{
    int i, w;
    //int K[n + 1][W + 1];
        K = (int **)malloc((n+1) * sizeof(int *));
    for (i=0; i<(n+1); i++) {
       K[i] = (int *)malloc((W+1) * sizeof(int));
        }

    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (itemTypes[i - 1].weight <= w)
                K[i][w] = MAX(itemTypes[i - 1].value
                          + K[i - 1][w - itemTypes[i - 1].weight],
                          K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

        //Get the selected elements
        for(i=0;i<n;i++)
            itemTypes[i].selected=0;

        w=W;i=itemTypesSize;
        while(K[i][w]!=0) {
            if(K[i][w] == K[i-1][w]){
                i=i-1;
            }
            else{
                itemTypes[i-1].selected=1;
                w=w-itemTypes[i-1].weight;
                i=i-1;
            }
        }

    return K[n][W];
}
