#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "../include/structures.h"


//TODO phase 3
//TODO lecture avec fscanf()

double SEUIL=0.000001;

int DEBUG = 1; //displays matrix
int DEBUG_2 = 1; //advanced debug
int DEBUG_3 = 0;

void insert_fin(node_t * head, double val, int column, int row){
    node_t * current = head;
    node_t * newNode = (node_t*)malloc(sizeof(node_t));
    if(newNode == NULL){
        fprintf(stderr, "Unable to allocate memory for new node\n");
        exit(-1);
    }
    newNode->column=column;
    newNode->row=row;
    newNode->val=val;
    newNode->next = NULL;
    while(current->next != NULL){
        current=current->next;
    }
    current->next = newNode;
}

void insert_head(int x,node_t * P[], double val, int column, int row){
    node_t * new_node = (node_t *) malloc(sizeof(node_t));
    new_node->column= column;
    new_node->row=row;
    new_node->val = val;
    new_node->next = NULL;
    P[x]=new_node;
}

void print_list(node_t * head){
    node_t * current = head;
    while (current != NULL)
    {
        printf("||col:%d|row:%d|val:%lf||->",current->column,current->row,current->val);
        current=current->next;
    }
    printf("NULL");
}

int get_matrix_size(char * path){
    int matrix_size = -1;
    int dummy = -1;
    FILE * file = fopen(path,"r");
    if(file==NULL){
        if(DEBUG_2)printf("could not open file \n");
        exit(1);
    }
    fscanf(file,"%d",&dummy);
    fscanf(file,"%d",&matrix_size);
    fclose(file);
    return matrix_size;
}

void init_matrix(int matrix_size,node_t * P[],char * path){
    FILE *file = fopen(path,"r");
    if(file==NULL){
        if(DEBUG_2)printf("could not open file \n");
        exit(1);
    }
    double val = 0.0;
    int row = -1;
    int column = -1;
    int times = -1;
    int i = 0;
    int nbElems = -1;
    int dummy = -1;
    fscanf(file,"%d",&nbElems);
    fscanf(file,"%d",&dummy);
    while (i <= matrix_size)
    {
        fscanf(file,"%d",&row);
        fscanf(file,"%d",&times);
        for(int j=0;j < times; j++){
            fscanf(file,"%d",&column);
            fscanf(file,"%lf",&val);
            if(P[column-1]->val==-1 && P[column-1]->row==-1 && column != -1){
                P[column-1]->column=column-1;
                P[column-1]->row=row;
                P[column-1]->val=val;
                P[column-1]->next=NULL;
            }
            else
            {
                insert_fin(P[column-1],val,column-1,row-1);
            }
            if(DEBUG_2)printf("wrote(col:%d;row:%d;val:%lf;) ",P[column-1]->column,P[column-1]->row,P[column-1]->val);
            column=-1;
        }
        i++;
    }
    fclose(file);
}

void print_matrix(int x, int y,node_t * P[y]){
    int matrix_x_size = x;
    printf("\n############## MATRIX ###############\n");
    for (int x = 0; x < matrix_x_size; x++)
    {
        print_list(P[x]);
        printf("\n");
    }
    printf("############## EOF MATRIX ###############\n");
}

void init_PI(int matrix_size, double PI[matrix_size]){
    for(int i = 0; i < matrix_size; i++){
        PI[i]=1.0/matrix_size;
        if(DEBUG_2)printf(" PI[%d]_wrote:%lf ",i,(1.0/matrix_size));
    }
}

void print_PI(int matrix_size, double PI[matrix_size]){
    printf("\n######## PI #########\n");
    for(int i = 0; i < matrix_size; i++){
        printf("%lf ",PI[i]);
    }
    printf("\n######## EOF PI ########\n");
}

void compute(int matrix_size, int y, node_t * P[y], double PI[matrix_size]){ //PI * P
    double res = 0.0;
    double res_prec = 0.0;
    double TMP[matrix_size];
    for (int k = 0; k < matrix_size; k++)
    {
        TMP[k]=0.0;
    }
    for (int i = 0; i < matrix_size; i++)
    {
        node_t * current = P[i];
        while (current->next != NULL)
        {
            res_prec = res;
            res = res + (current->val*PI[current->row]);
            if(DEBUG_3)printf("compute:(res:%lf=res_prec%lf + (val:%lf*PI[%d]:%lf)\n",res,res_prec,current->val,current->row,PI[current->row]);
            current=current->next;
        }
        res_prec = res;
        res = res + (current->val*PI[current->row]);
        if(DEBUG_3)printf("compute:(res:%lf=res_prec%lf + (val:%lf*PI[%d]:%lf)\n",res,res_prec,current->val,current->row,PI[current->row]);
        TMP[i]=res;
        res=0.0;
    }
    for (int j = 0; j < matrix_size; j++)
    {
        PI[j]=TMP[j];
    }
}

int compare_prev(int matrix_size, double PREV_PI[matrix_size], double PI[matrix_size]){
    for (int i = 0; i < matrix_size; i++)
    {
        if(fabs(PI[i]-PREV_PI[i]) > SEUIL){
            return 1;
        }
    }
    return 0;
}



void free_matrix(node_t * P[], int matrix_size){
    node_t * next_node = NULL;
    for (int i = 0; i < matrix_size; i++)
    {
        node_t * head = P[i];
        if(head == NULL){
            break;
        }
        next_node = head->next;
        free(head);
        head = next_node;
    }
    
}

int main()
{
    //char * path = "./res/GraphesWebTest/web1.txt";
    char * path = "./res/petit.txt";
    int matrix_size = get_matrix_size(path);
    printf("Matrix size = %d\n",matrix_size);
    double PI[matrix_size];
    double PREV_PI[matrix_size];
    node_t * P[matrix_size];
    if(DEBUG)printf("created P matrix \n");
    for (int i = 0; i < matrix_size; i++)
    {
        node_t * init_node = (node_t *) malloc(sizeof(node_t));
        init_node->column=i;
        init_node->row=-1;
        init_node->val=-1;
        init_node->next=NULL;
        P[i]=init_node;
    }
    if(DEBUG)printf("zeroed P matrix \n");
    int ite = 0;
    init_matrix(matrix_size,P,path);
    if(DEBUG)printf("initialized P matrix \n");
    if(DEBUG)print_matrix(matrix_size,matrix_size,P);
    init_PI(matrix_size,PI);
    if(DEBUG)print_PI(matrix_size,PI);
    if(DEBUG)print_matrix(matrix_size,matrix_size,P);
    for (int i = 0; i < matrix_size; i++)
    {
        PREV_PI[i]= PI[i];
    }
    do
    {
        for(int i = 0; i < matrix_size; i++){
            PREV_PI[i] = PI[i];
        }
        compute(matrix_size,matrix_size,P,PI);
        ite++;
    }while (compare_prev(matrix_size,PREV_PI,PI) == 1 && (ite < 10000));
    printf("%d iterations\n", ite);
    
    if(DEBUG)print_PI(matrix_size,PI);
    free_matrix(P,matrix_size);
}

//TODO verifier que chaque ligne est stocastique