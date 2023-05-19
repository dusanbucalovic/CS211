#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <ctype.h>
#include <stdbool.h>


typedef struct varLL{
char name[17];
int value;
struct varLL* next;
}varLL;


typedef struct gateLL{
char name[17];
struct varLL* inputs;
struct varLL* outputs;
struct gateLL* next;
}gateLL;

varLL* create(varLL* temphead,char* name);
void travers(varLL* temphead);
int convert(int dec);
void printma(int** matrix,int row,int col, int input);
gateLL* createGate(gateLL* temphead,char* name,varLL * inputs, varLL * outputs);
void traversg(gateLL* temphead);
void traversnum(varLL* temphead);
int findint(char* name, varLL* head);
int findout(char* name,int n, varLL* head);
int notgate(int input);
int andgate(int input1,int input2);
int orgate(int input1,int input2);
int nandgate(int input1,int input2);
int norgate(int input1,int input2);
int xorgate(int input1,int input2);


int tokenType(char g[17]){

  if(strcmp(g,"PASS")==0){
    return 1;
  }
  if(strcmp(g,"NOT")==0){
    return 1;
  }
  if(strcmp(g,"AND")==0){
    return 1;
  }
  if(strcmp(g,"OR")==0){
    return 1;
  }
  if(strcmp(g,"NAND")==0){
    return 1;
  }
  if(strcmp(g,"NOR")==0){
    return 1;
  }
  if(strcmp(g,"XOR")==0){
    return 1;
  }
  if(strcmp(g,"DECODER")==0){
    return 1;
  }
  if(strcmp(g,"MULTIPLEXER")==0){
    return 1;
  }
  if(strcmp(g,":")==0){
    return 10;
  }
  return 0;
}

char * processVar(varLL * inputHead, varLL * outputHead, char * var){
  varLL * ptr = inputHead;

  bool found = false;
  while(ptr!=NULL){
    if(strcmp(ptr->name, var)==0){
      found = true;
      break;
    }
    ptr=ptr-> next;
  }



  ptr = outputHead;
  while(ptr!=NULL){
    if(strcmp(ptr->name, var)==0){
    found = true;
    }
    ptr=ptr-> next;
  }

  if(!found){
  for(int i = 0; var[i]; i++){
    var[i] = tolower(var[i]);
  }
}
  return var;
}




int main(int argc, char** argv){

int i =0;
int j = 0;
int k =0;



char* name=malloc(17*sizeof(char));
char* x=malloc(17*sizeof(char));

varLL* inputHead=NULL;
varLL* outputHead=NULL;


  FILE* fl;
  fl=fopen(argv[1],"r");
  if(fl==NULL){
    printf("wrong file name\n");
    return 0;
  }



  int input = 0;
  fscanf(fl, "%16s", name);
  while ((fscanf(fl, "%16s", name) == 1) && strcmp(name, "OUTPUT") != 0) {
        input++;
        inputHead=create(inputHead,name);
  }


  printf("INPUT VARS: ");
  varLL * ptr = inputHead;
  while(ptr!=NULL){
    printf("%s, ",ptr->name);
    ptr=ptr->next;
  }
  printf("\n");




int output = 0;
while ((fscanf(fl, " %16s", name) == 1) && tokenType(name)==0){
      output++;
      outputHead=create(outputHead,name);
}

printf("OUTPUT VARS: ");
ptr = outputHead;
while(ptr!=NULL){
  printf("%s, ",ptr->name);
  ptr=ptr->next;
}
printf("\n");

int result=pow(2,input);


int** matrix=malloc(result*sizeof(int*));
for(i=0;i<result;i++){
  matrix[i]=(int*)malloc((input+output)*sizeof(int));
}

bool zero = true;
int interval = (result/2);
for(int i =0; i <input;i++){
    for(int j =0; j<result; j++){

      if(j%interval==0){
        zero = !zero;
      }
      if(zero){
        matrix[j][i] = 1;
      }
      else{
        matrix[j][i] = 0;
      }
    }
    interval/=2;
  }

gateLL* gate=NULL;

x = name;

varLL *in = NULL;
varLL * out = NULL;
bool isIn = true;

//char * operation[17];

do{

int type = tokenType(x);


  switch(type){
    case 10:
    isIn = false;
    break;

    case 1:
    gate = createGate(gate,x,in,out);
    printf("GATE: %s\n",x);
    in = NULL;
    out = NULL;
    isIn = true;

    break;

    case 0:
    if(isIn==true){
      printf("input: %s \n", x);
      in= create(in,x);
      gate->inputs = in;
    }
    else{
      printf("output: %s \n", x);
      out=create(out,x);
      gate->outputs = out;

  }
  break;
  }


}while(fscanf(fl,"%16s",x)==1);


gateLL * ptr1 = gate;
while(ptr1!=NULL){
  printf("%s\n",ptr1->name );

  varLL * ptr2 = NULL;
  ptr2 =  ptr1->inputs;
  printf("INPUTS: ");

  while(ptr2!=NULL){
    printf("%s ",ptr2->name);
    ptr2 = ptr2->next;
  }
  ptr2 = ptr1-> outputs;
  printf("\nOUTPUTS: ");
  while(ptr2!=NULL){
    printf("%s, ",ptr2->name);
    ptr2 = ptr2->next;
  }
  printf("\n");

  ptr1 = ptr1->next;
}


for(i=0;i<result;i++){
  varLL* pt=inputHead;
  for(j=0;j<input;j++){
    pt->value=matrix[i][j];
    pt=pt->next;
  }


gateLL* move=gate;
while(move!=NULL){

  move=move->next;

}

  pt=outputHead;
  for(k=input;k<(input+output);k++){
    matrix[i][k]=pt->value;
    pt=pt->next;
    }
}
  printma(matrix,result,(input+output),input);

return 0;
}


varLL* create(varLL* temphead,char* name){
  if(temphead==NULL){
    temphead=malloc(sizeof(varLL));
    strcpy(temphead->name,name);
    temphead->next=NULL;
    return temphead;
  }
  varLL* pt=temphead;
  while(pt->next!=NULL){
    pt=pt->next;
  }
varLL* new=malloc(sizeof(varLL));
strcpy(new->name,name);
new->next=NULL;
pt->next=new;
return temphead;

}

void travers(varLL* temphead){
  varLL* pt=temphead;
  while(pt!=NULL){
    printf("%s->",pt->name);
    pt=pt->next;
  }
  printf("\n");
  return;
}
void traversnum(varLL* temphead){
  varLL* pt=temphead;
  while(pt!=NULL){
    printf("%d->",pt->value);
    pt=pt->next;
  }
    printf("\n");
  return;
}
void printma(int** matrix,int row,int col, int input){

int i,j;
for(i=0;i<row;i++){
  for(j=0;j<col;j++){
    if(j-input==0){
      printf("| %d", matrix[i][j]);
    }

    else{
      printf("%d",matrix[i][j]);
    }
    if(j!=col-1){
      printf(" ");
    }
  }
  printf("\n");
}

}

int notgate(int input){
  if(input==1){
    return 0;
  }
  if(input==0){
    return 1;
  }
  return 2;
}

int andgate(int input1,int input2){
  if(input1==1&&input2==1){
    return 1;
  }

  return 0;
}

int orgate(int input1,int input2){
  if(input1==1||input2==1){
    return 1;
  }

  return 0;
}

int nandgate(int input1,int input2){
  if(input1==0&&input2==0){
    return 1;
  }

  return 0;
}

int passgate(int input){
  return input;
}

int norgate(int input1,int input2){
  if(input1==1||input2==1){
    return 0;
  }

  return 1;
}

int xorgate(int input1,int input2){
  if(input1==1&&input2==0){
   return 1;
    }else if(input1==0&&input2==1){

    return 1;
      }else{

  return 0;
}
}
gateLL* createGate(gateLL* temphead,char* name,varLL * inputs, varLL * outputs){
  if(temphead==NULL){
    temphead=malloc(sizeof(gateLL));
    strcpy(temphead->name,name);
    temphead->inputs = inputs;
    temphead-> outputs = outputs;
    temphead->next=NULL;
    return temphead;
  }
gateLL* pt=temphead;
  while(pt->next!=NULL){
    pt=pt->next;
  }
gateLL* new=malloc(sizeof(gateLL));
strcpy(new->name,name);
temphead->inputs = inputs;
temphead-> outputs = outputs;
new->next=NULL;
pt->next=new;
return temphead;

}
void traversg(gateLL* temphead){
  gateLL* pt=temphead;
  while(pt!=NULL){
    printf("%s->",pt->name);
    pt=pt->next;
  }
    printf("\n");
  return;
}
int findint(char* name, varLL* head){

  varLL* pt=head;

  while(pt!=NULL){
    if(pt->name[strlen(pt->name)-1]==name[strlen(name)-1]){

    if(pt->name[strlen(pt->name)-2]==name[strlen(name)-2]){

      return pt->value;
      }
    }
    pt=pt->next;
    }
    return 2;
  };
int findout(char* name,int n, varLL* head){
  varLL* pt=head;
  while(pt!=NULL){
    if(pt->name[strlen(pt->name)-1]==name[strlen(name)-1]){
    if(pt->name[strlen(pt->name)-2]==name[strlen(name)-2]){
    
      pt->value=n;
      return 1;
      }
    }
      pt=pt->next;
  }
    return 2;


  };