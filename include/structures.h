#ifndef STRUCTURES__H
#define STRUCTURES__H

//matrice creuse
/*
stocker les éléments non nuls
uniquement i,j P(i,j)
*/


typedef struct node{
    int column;
    int row;
    double val;
    struct node * next;
}node_t;






#endif