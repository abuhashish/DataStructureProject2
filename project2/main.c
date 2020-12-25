#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
typedef struct nod
{
    char equation[50];
    int isvalid;
    char* reason;
    char postfix[50];
    float result;
    int isresult;
    struct node * next;
} eq;
typedef struct node* ptrnode;
typedef ptrnode stack;
struct node{
char Element;
ptrnode next;
};
int IsEmpty(struct node* S){
return S->next==NULL;

}
stack CreateStack(){
stack s;
s = (struct node*)malloc(sizeof(struct node));
if(s==NULL)
    printf("out of space!");
s->next==NULL;
MakeEmpty(s);
return s;
}
void MakeEmpty(stack s){
if(s==NULL)
printf("out of space!");
while(!IsEmpty(s))
    Pop(s);
}
void Pop(stack s){
ptrnode firstcell;
if(IsEmpty(s))
    printf("Empty stack");
else{
    firstcell=s->next;
    s->next=s->next->next;
    free(firstcell);
}
}

char top(stack s){
if(!IsEmpty(s))
    return s->next->Element;
}

void Push(int y,stack s){
ptrnode temp;
temp=(stack)malloc(sizeof(struct node));
if(temp==NULL)
    printf("out of space!");
else{
    temp->Element= y;
    temp->next=s->next;
    s->next=temp;
 }
}
void disposestack(stack s){
MakeEmpty(s);
free(s);
}
struct nod* CreateNod(struct nod*);
int main()
{
    int choice;
       struct nod *l1;
       stack s1;
      l1=CreateNod(NULL);
      s1 = (struct node*)malloc(sizeof(struct node));
    s1->next=NULL;

     do
    {
        //Asking the user to choose an option
        printf("----------------------------------------------------------------------------\n\n\n\n");
        printf("----------------------------------------------------------------------------\n\n");
        printf("1.Read the data From File\n2.Check Validity\n");
        printf("3.Convert To Postfix\n");
        printf("4.Evaluate the PostFix\n");
        printf("5.Print Invalid Equations\n");
        printf("6.Print All Equations to File\n");
        printf("7.Exit\n");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
        readFile(l1);
            break;

        case 2:

        isValid(l1);
            break;

        case 3:
        Convert(l1,s1);
            break;

        case 4:
        postfixEval(l1,s1);
            break;
        case 5:
        print(l1);
            break;

        case 6:
        printtofile(l1);
            break;


        default:
            printf("Please try again,You have to enter a number from 1 to 7 \n\n");
            break;
        }
    }
    while(choice != 7);

    return 0;

}



void readFile (struct nod* l1){              // this function will take a path for a file from the user, and read the expressions in this file and save them in the given linked list
                                    // it will return 1 if the file opened successfully, otherwise it will return zero
    FILE *in;
    char path[100];
    char string [20][100];
    char myline[200];
    int i=0;
    printf("Enter the path of the file please:\n");

    scanf("%s",path);

    in = fopen(path,"r");

    if (in == NULL){
        printf("the file does not exist\n");
        return;
    }
        while (!feof(in)) {
       fgets(myline,200,in);
      strcpy(string[i],myline);

       i++;;

   }
    int lines=i;
    for(int i=lines;i>=0;i--)
        add(string[i],l1,l1);



fclose(in);


}
void add(char equation[],eq* L,eq* P){
eq* temp;
temp = (eq*)malloc(sizeof(eq));
strcpy(temp->equation,equation);

temp->next = P->next;

P->next = temp;
}
struct nod* CreateNod(struct nod* L){
if(L != NULL)
DeleteList( L );
L = (struct nod*)malloc(sizeof(struct nod));
if(L == NULL)
printf("Out of memory!\n");
L->next = NULL;
return L;
}
void DeleteList(struct nod* L){
struct node* P;
struct node* temp;
P = L->next;
L->next = NULL;
while(P != NULL){
temp = P->next;
free(P);
P=temp;
}
}

void isValid(struct nod* l1){
    int k=0;
    int m=0;
    l1=l1->next;

    while(l1->next!=NULL){
        for(int i=0;i<strlen(l1->equation);i++){
            if(l1->equation[i]== '('||l1->equation[i]=='[') //as in the 2nd equation.
                k++;
            if(l1->equation[i]== ')'||l1->equation[i]==']')
                m++;
            if(i!=0)
            if (l1->equation[i]=='['||l1->equation[i]=='('){
                if(l1->equation[i-1]=='+'||l1->equation[i-1]=='-'||l1->equation[i-1]=='*'||l1->equation[i-1]=='/'){
                }
                else{
                l1->isvalid=1;
                l1->reason=("there is no operator before [");
            }
        }
            if((l1->equation[i]=='('||l1->equation[i]=='[')&&(l1->equation[i+1]==')'||l1->equation[i+1]==']')){
                l1->isvalid=1;
                l1->reason=("There is no number between  () or []");
            }
            if(l1->equation[0]=='+'||l1->equation[0]=='*'||l1->equation[0]=='/'){
                l1->isvalid=1;
                l1->reason=("you cannot start an equation with operation");
            }
           if((l1->equation[i]=='('||l1->equation[i]=='[')&&(l1->equation[i+1]=='+'||l1->equation[i+1]=='-'||l1->equation[i+1]=='*'||l1->equation[i+1]=='/')){
                l1->isvalid=1;
                l1->reason=("you cannot place an operation directly after parentheses");
              }

       if ( l1->equation[i] == ')' && l1->equation[i+1] == '(' ){
            strcpy(l1->reason, "two opposite Parentheses without an operator between them )(");
            l1 -> isvalid = 1;

        }
         if ( isdigit(l1->equation[i]) && l1->equation[i+1] == ' ' ){


            if (isdigit(l1->equation[i+2])){
                strcpy(l1->reason, "space between numbers, missed operator");
                l1 -> isvalid = 1;

            }
         }
            if ( l1->equation[i] == '*' || l1->equation[i] == '/' ||l1->equation[i]=='+'||l1->equation[i]=='-'){
                if (l1->equation[i+1] == '\0'){
                strcpy(l1->reason, "operator at last without a number after it");
                l1 -> isvalid =1;

            }
            }
              if ( l1->equation[i] == '*' || l1->equation[i] == '/' ||l1->equation[i]=='+'||l1->equation[i]=='-'){
                      if ( l1->equation[i+1] == '*' || l1->equation[i+1] == '/' ||l1->equation[i+1]=='+'||l1->equation[i+1]=='-'){
                        strcpy(l1->reason,"two operations without a number between them");
                        l1->isvalid=1;
                      }

            }
         }

            if(k!=m){
            l1->isvalid=1;
            l1->reason=("invalid: (	is	not	closed");
            }
            k=0;
            m=0;
            if(l1->isvalid==1)
            printf("%s %s\n",l1->reason,l1->equation);
            if(l1->isvalid==0)
            printf("valid %s\n",l1->equation);
l1=l1->next;
    }

}


void print(struct nod* l1){
l1=l1->next;

while(l1->next!=NULL){
        if(l1->isvalid==1)
        printf("%s  %s\n",l1->equation,l1->reason);
        l1=l1->next;
}
}
void mystrcat (char *str, char c){     // this function will append the given char to the given string without a space after it

    char Char[2];
    Char[0] = c;
    Char[1] = '\0';

    strcat(str, Char);              // appending the character to the string
}
 void Convert(struct nod* l1,stack s1){
l1=l1->next;

    while(l1->next!=NULL){
    if(l1->isvalid==0){
        for(int i=0;i<strlen(l1->equation);i++){
                   if(l1->equation[i]=='(')
                l1->equation[i]='[';
                if(l1->equation[i]==')')
                l1->equation[i]=']';
                if(isdigit(l1->equation[i])>0){
                    strncat(  l1->postfix,&l1->equation[i],1);
            }
                    if(l1->equation[i]=='^'){
                        if(top(s1)=='^'){
                    mystrcat(l1->postfix,top(s1));
                    Pop(s1);
                    Push(l1->equation[i],s1);
                        }
                    if(top(s1)=='*'||top(s1)=='/'||top(s1)=='+'||top(s1)=='-'||IsEmpty(s1)||top(s1)=='['){
                    Push(l1->equation[i],s1);

            }

                }
                if(l1->equation[i]=='*'||l1->equation[i]=='/'){
                               if(top(s1)=='^'||top(s1)=='*'||top(s1)=='/'){
                                mystrcat(l1->postfix,top(s1));
                                Pop(s1);
                                Push(l1->equation[i],s1);
                    }

                if(top(s1)=='+'||top(s1)=='-'||IsEmpty(s1)||top(s1)=='[')
                    Push(l1->equation[i],s1);
        }
            if(l1->equation[i]=='+'||l1->equation[i]=='-'){
                     if(top(s1)=='^'||top(s1)=='*'||top(s1)=='/'||top(s1)=='+'||top(s1)=='-'){
                    mystrcat(l1->postfix,top(s1));
                                Pop(s1);
                        Push(l1->equation[i],s1);
                    }

                if(top(s1)=='['||IsEmpty(s1)){
                    Push(l1->equation[i],s1);
                }
            }
                   if(l1->equation[i]=='['){
                        Push(l1->equation[i],s1);
                    }
                if(l1->equation[i]==']'){
                       while(top(s1)!='['){
                        mystrcat(l1->postfix,top(s1));
                        Pop(s1);
                    }
                        Pop(s1);
                  }
                  if(l1->equation[i]=='='){
                    for(i;i<strlen(l1->equation);i++){
                        if(isdigit(l1->equation[i]))
                            l1->isresult=l1->equation[i]-'0';
                    }
                  }


                    }
                while(!IsEmpty(s1)){
                mystrcat(l1->postfix,top(s1));
                Pop(s1);
                }
        }
  if(l1->isvalid==1)
            printf("for this equation %s there is no postfix because its %s\n",l1->equation,l1->reason);
            if(l1->isvalid==0)
            printf("he postfix of equation %s  is %s\n",l1->equation,l1->postfix);
    l1=l1->next;
    }


 }

float operation(int a, int b, char op) {

   if(op == '+')
      return b+a;
   else if(op == '-')
      return b-a;
   else if(op == '*')
      return b*a;
   else if(op == '/')
      return b/a;
   else if(op == '^')
      return pow(b,a);
   else
      return 0;
}
float scanNum(char ch) {
   int value;
   value = ch;
   value=(float) (value-'0');
   return value;
}

int isOperator(char ch) {
   if(ch == '+'|| ch == '-'|| ch == '*'|| ch == '/' || ch == '^')
      return 1;
   return -1;
}

int isOperand(char ch) {
   if(ch >= '0' && ch <= '9')
      return 1;
   return -1;
}
void postfixEval(struct nod* l1,struct node* s1) {
   int a, b;
   l1=l1->next;
    while(l1->next!=NULL){
        if(l1->isvalid==0){
                for(int i=0;i<strlen(l1->postfix); i++) {
                if(isOperator(l1->postfix[i]) != -1) {
                a = top(s1);
                Pop(s1);
                b = top(s1);
                Pop(s1);
                Push(operation(a, b, l1->postfix[i]),s1);
            }
                else if(isOperand(l1->postfix[i]) > 0) {
                Push(scanNum(l1->postfix[i]),s1);
            }
         }
            l1->result=top(s1);
            printf("the evaluation of equation %s is %f\n",l1->equation,l1->result);
      }
            l1=l1->next;
   }

}
void printtofile(struct nod* l1){
      FILE *out_file=fopen("output.txt","w");
l1=l1->next;
while(l1->next!=NULL){

    if(l1->isvalid==0&&l1->isresult==0){

            fprintf(out_file,"%==>valid %s      %s      %f \n",l1->equation,l1->postfix,l1->result);
    }
    else if(l1->isvalid==0&&l1->isresult!=0){
         if(l1->isresult==l1->result)
                fprintf(out_file,"==>valid%s      %s      %f the result was true\n",l1->equation,l1->postfix,l1->result);
            if(l1->isresult!=l1->result)
                fprintf(out_file,"==>valid%s    %s      %f the result was not true\n",l1->equation,l1->postfix,l1->result);
            }
    else
        fprintf(out_file,"==>invalid %s\n",l1->equation);

l1=l1->next;
}
fclose(out_file);
}



