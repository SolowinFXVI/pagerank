#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "../include/structures.h"

double SEUIL=0.000001;

int DEBUG = 0; //displays matrix
int DEBUG_2 = 0; //advanced debug
int DEBUG_3 = 0;
int DEBUG_FREES = 0;
int DEBUG_READ = 0;
static int nodeCount = 0;
static int totalNodes = 0;
static int shown = 0;

/*void insert_fin(node_t P[], double val, int column, int row){
    
    node_t * newNode = malloc(sizeof(node_t));
    if(newNode == NULL){
        fprintf(stderr, "Unable to allocate memory for new node\n");
        exit(-1);
    }
    newNode->column = column;
    newNode->row = row;
    newNode->val = val;
    newNode->next = NULL;

    
    if(P[column].next != NULL){
        node_t * iterator = P[column].next;
        while(iterator->next != NULL){
            iterator = iterator->next;
        }
        iterator->next = newNode;
    }
    else{
        P[column].next = newNode;
    }
    nodeCount++;
    if(((nodeCount * 100)/totalNodes == 10) && (shown==0)){
        printf("Loading 10%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 20) && (shown==1)){
        printf("Loading 20%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 30) && (shown==2)){
        printf("Loading 30%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 40) && (shown==3)){
        printf("Loading 40%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 50) && (shown==4)){
        printf("Loading 50%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 60) && (shown==5)){
        printf("Loading 60%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 70) && (shown==6)){
        printf("Loading 70%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 80) && (shown==7)){
        printf("Loading 80%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 90) && (shown==8)){
        printf("Loading 90%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 99) && (shown==9)){
        printf("Loading 100%% \n");
        shown++;
    }
    if(DEBUG)printf("Added node : %d \n", nodeCount);
}*/

void insert_head(node_t P[], double val, int column, int row){
    if(P[column].next == NULL){
        if(P[column].row == -1){ //vide
            P[column].column= column;
            P[column].row=row;
            P[column].val = val;
            P[column].next = NULL;
        }
        else{ //pas de suivant
            node_t * newNode = malloc(sizeof(node_t));
            if(newNode == NULL){
            fprintf(stderr, "Unable to allocate memory for new node\n");
            exit(-1);
            }
            newNode->column = column;
            newNode->row = row;
            newNode->val = val;
            newNode->next = NULL;
            P[column].next = newNode;
        }
        
    }
    else{//suivants
        node_t * newNode = malloc(sizeof(node_t));
        if(newNode == NULL){
            fprintf(stderr, "Unable to allocate memory for new node\n");
            exit(-1);
        }
        newNode->column = column;
        newNode->row = row;
        newNode->val = val;
        newNode->next = P[column].next;
        P[column].next = newNode;
    }    
    nodeCount++;
        if(((nodeCount * 100)/totalNodes == 10) && (shown==0)){
        printf("Loading 10%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 20) && (shown==1)){
        printf("Loading 20%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 30) && (shown==2)){
        printf("Loading 30%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 40) && (shown==3)){
        printf("Loading 40%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 50) && (shown==4)){
        printf("Loading 50%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 60) && (shown==5)){
        printf("Loading 60%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 70) && (shown==6)){
        printf("Loading 70%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 80) && (shown==7)){
        printf("Loading 80%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 90) && (shown==8)){
        printf("Loading 90%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 99) && (shown==9)){
        printf("Loading 100%% \n");
        shown++;
    }
    if(DEBUG)printf("filled existing node : %d \n", nodeCount);
}

void print_list(node_t * head){
    node_t * current = head;
    while (current != NULL) {
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
        printf("could not open file \n");
        exit(-2);
    }
    fscanf(file,"%d",&matrix_size);
    fscanf(file,"%d",&dummy);
    fclose(file);
    return matrix_size;
}

int get_totalNodes(char * path){
    int dummy = -1;
    int nodes = -1;
    FILE * file = fopen(path,"r");
    if(file == NULL){
        printf("could not open file \n");
        exit(-2);
    }
    fscanf(file, "%d", &dummy);
    fscanf(file, "%d", &nodes);
    fclose(file);
    return nodes;
}

void init_matrix(int matrix_size,node_t P[],char * path){
    FILE *file = fopen(path,"r");
    if(file==NULL){
        if(DEBUG_2)printf("could not open file \n");
        exit(1);
    }
    int row = 0;
    int numberOfElements = 0;
    int dummmyMatrixSize = 0;
    int repsInALine = 0;
    int column = 0;
    double val = 0.0;

    fscanf(file, "%d", &numberOfElements);
    fscanf(file, "%d", &dummmyMatrixSize);

    for (int i = 0; i < matrix_size; i++)
    {
        fscanf(file, "%d", &row);
        fscanf(file, "%d", &repsInALine);
        if(DEBUG_READ)printf("row: %d, reps:%d \n", row-1, repsInALine);
        for (int j = 0; j < repsInALine; j++)
        {
            fscanf(file, "%d %lf", &column, &val);
            if(DEBUG_READ)printf("decider:col:%d,row:%d,val:%lf \n", column-1, row-1, val);
            //if(P[column-1].row == -1){
                //if(DEBUG_READ)printf("going for the head \n");
                insert_head(P,val, column-1, row-1);
            /*}
            else{
                if(DEBUG_READ)printf("going for the tail \n");
                insert_fin(P,val, column-1, row-1);
            }*/
            
        }
    }
    

    fclose(file);
}

void print_matrix(int matrix_x_size, int y,node_t P[]){
    printf("\n############## MATRIX ###############\n");
    for (int x = 0; x < matrix_x_size; x++)
    {
        print_list(&P[x]);
        printf("\n");
    }
    printf("############## EOF MATRIX ###############\n");
}

void init_PI(int matrix_size, double PI[]){
    for(int i = 0; i < matrix_size; i++){
        PI[i]=1.0/matrix_size;
        if(DEBUG_2)printf(" PI[%d]_wrote:%lf ",i,(1.0/matrix_size));
    }
}

void print_G(int matrix_size, double G[]){
    printf("\n######## PI #########\n");
    for(int i = 0; i < matrix_size; i++){
        printf("%lf ",G[i]);
    }
    printf("\n######## EOF PI ########\n");
}



void compute(int matrix_size, int y, node_t P[], double G[]){ //PI * P
    double res = 0.0;
    double res_prec = 0.0;
    double * TMP = malloc(sizeof(double) * matrix_size);
    //double TMP[matrix_size];
    for (int k = 0; k < matrix_size; k++)
    {
        TMP[k]=0.0;
    }
    for (int i = 0; i < matrix_size; i++)
    {
        node_t current = P[i];
        while (current.next != NULL)
        {
            res_prec = res;
            res = res + (current.val * G[current.row]);
            if(DEBUG_3)printf("compute:(res:%lf=res_prec%lf + (val:%lf*PI[%d]:%lf)\n",res,res_prec,current.val,current.row,G[current.row]);
            current.column = current.next->column;
            current.row = current.next->row;
            current.val = current.next->val;
            current.next = current.next->next;
        }
        res_prec = res;
        res = res + (current.val * G[current.row]);
        if(DEBUG_3)printf("compute:(res:%lf=res_prec%lf + (val:%lf*PI[%d]:%lf)\n",res,res_prec,current.val,current.row,G[current.row]);
        TMP[i]=res;
        res=0.0;
        current.column = -1;
        current.row = -1;
        current.val = -1;
        current.next = NULL;
    }
    for (int j = 0; j < matrix_size; j++)
    {
        G[j]=TMP[j];
    }
    free(TMP);
}

int compare_prev(int matrix_size, double PREV_G[], double G[]){
    for (int i = 0; i < matrix_size; i++)
    {
        if(fabs(G[i]-PREV_G[i]) > SEUIL){
            return 1;
        }
    }
    return 0;
}



void free_matrix(node_t P[], int matrix_size) {
    
    for (int i = matrix_size-1; i >= 0; i--) {
        if(DEBUG_FREES) printf("free column %d \n", i);
        while(P[i].next != NULL){
            if(DEBUG_FREES){
                printf("next = %p ", P[i].next);
                printf("next->val = %lf ", P[i].next->val);
            }    
            node_t * current = P[i].next;
            if(current->next != NULL){
                node_t * next = current->next;
                P[i].next = next;
                free(current);
                if(DEBUG_FREES)printf("freed \n");
            }
            else{
                P[i].next = NULL;
                free(current);
                if(DEBUG_FREES)printf("freed \n");
            }
        }
    }
}

node_t * alloc_Matrix(int matrix_size){
    return malloc(matrix_size * sizeof(node_t));
}

void zero_matrix(node_t P[], int matrix_size){
    for (int i = 0; i < matrix_size; i++)
    {
        P[i].column=i;
        P[i].row=-1;
        P[i].val=-1;
        P[i].next=NULL;
        /*printf("column %d",P[i].column);
        printf("row %d",P[i].row);
        printf("val %lf",P[i].val);
        printf("next %d",P[i].next);*/
    }
}

void times_alpha(int matrix_size, double G[] , double alpha){
    for (int i = 0; i < matrix_size; i++)
    {
        G[i] = G[i] * alpha;
    }
}

void calculate_f(int matrix_size, node_t P[], double G[], double blob_1[]){
    double res = 0.0;
    for(int i= 0 ; i < matrix_size; i++){
        node_t current = P[i];
        while(current.next != NULL){
            res = res + current.val;
            if(res > 0.0){
                blob_1[i] = 0;
                break;
            }
            current.column = current.next->column;
            current.row = current.next->row;
            current.val = current.next->val;
            current.next = current.next->next;
        }
        if(res == 0.0){
            blob_1[i] = 1;
        }
    }
}

void addBlob(int matrix_size, double alpha,node_t P[], double G[], double PREV_G[]){
    double * blob_1 = malloc(sizeof(double) * matrix_size);
    double * blob_2 = malloc(sizeof(double) * matrix_size);
    double * blobs = malloc(sizeof(double) * matrix_size);

    for(int s = 0; s < matrix_size; s++){
        blob_1[s] = 0;
        blob_2[s] = 0;
        blobs[s] = 0;
    }

    /*blob_1*/
    calculate_f(matrix_size, P, G, blob_1);
    for(int i = 0; i < matrix_size; i++){
        blob_1[i] = blob_1[i] * PREV_G[i];
    }
    times_alpha(matrix_size, blob_1, alpha);// *alpha
    times_alpha(matrix_size, blob_1, 1); // *e

    /*blob_2*/
    for(int j=0; j <matrix_size; j++){
        blob_2[j] = (1.0-alpha)/matrix_size;
    }
    times_alpha(matrix_size, blob_2, 1);// *e
    /*
      blobs = blob1 + blob2
    */
   for(int l = 0; l < matrix_size; l++){
       blobs[l] = blob_1[l] + blob_2[l];
   }

   //G+blobs
    for(int k = 0; k < matrix_size; k++){
        G[k] = G[k] + blobs[k];
    }
    free(blob_1);
    free(blob_2);
    free(blobs);
}

void run(char * path){
    struct timeval tv3, tv4;
    double alpha = 0.85;
    int matrix_size = get_matrix_size(path);
    totalNodes = get_totalNodes(path);
    int ite = 0;
    double  * PI = malloc(matrix_size * sizeof(double));
    double  * PREV_G = malloc(matrix_size * sizeof(double));
    double * G = malloc(matrix_size * sizeof(double));
    node_t * P = alloc_Matrix(matrix_size);
    if (P == NULL)
    {
        printf("Allocation Error");
        exit(1);
    }
    if(DEBUG)printf("created P matrix %d\n", matrix_size);
    zero_matrix(P,matrix_size);
    if(DEBUG)printf("zeroed P matrix \n");
    init_matrix(matrix_size,P,path);
    if(DEBUG)printf("initialized P matrix \n");
    if(DEBUG)print_matrix(matrix_size,matrix_size,P);
    printf("Matrix size %d\n", matrix_size);
    init_PI(matrix_size,PI);
    //if(DEBUG)print_G(matrix_size,G);
    if(DEBUG)print_matrix(matrix_size,matrix_size,P);
    for(int j = 0; j < matrix_size; j++){
        G[j] = PI[j];
        PREV_G[j] = PI[j];
    }
    gettimeofday(&tv3, NULL);
    do
    {
        for(int i = 0; i < matrix_size; i++){
            PREV_G[i] = G[i];
        }
        compute(matrix_size,matrix_size,P,G);
        times_alpha(matrix_size,G,alpha);
        addBlob(matrix_size, alpha, P, G, PREV_G);
        ite++;
        if(ite % 250 == 0){
            printf("Iteration : %d \n", ite);
        }
    }while ((compare_prev(matrix_size,PREV_G, G) == 1) && (ite < 10000)); //TODO change to 10000
    gettimeofday(&tv4, NULL);
    //print_G(matrix_size,G);
    printf("%d iterations\n", ite);
    printf("Compute time = %f seconds \n", (double) (tv4.tv_usec - tv3.tv_usec)/ 1000000 + (double) (tv4.tv_sec - tv3.tv_sec));
    free_matrix(P,matrix_size);
    free(P);
    free(PI);
    free(PREV_G);
    free(G);
}

int main(){
    printf("STARTING \n");
    //char * path = "./res/GraphesWebTest/web1.txt";
    //char * path = "./res/Stanford.txt/Stanford.txt";
    //char * path = "./res/wb_cs_stanford.txt/wb-cs-stanford.txt";
    //char * path = "./res/Stanford_BerkeleyV2.txt/Stanford_BerkeleyV2.txt";
    char * path = "./res/wikipedia_20051105V2.txt/wikipedia-20051105V2.txt";
    //char * path = "./res/wb_edu.txt/wb-edu.txt";
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    run(path);
    gettimeofday(&tv2, NULL);
    printf("Execution time = %f seconds \n", (double) (tv2.tv_usec - tv1.tv_usec)/ 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
    exit(0);
}

//TODO verifier que chaque ligne est stocastique
