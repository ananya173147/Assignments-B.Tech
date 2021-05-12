/*
Assignment 4
Roll Number: CS19B1004
Name: Ananya Mantravadi

*/
#include<stdio.h>
#include<stdlib.h>

typedef struct qnode {              /* Nodes of a linked list implementation of queue */
	int data;
	struct qnode* next;
}qnode;


typedef struct queue {              /* Pointers to the first and last nodes of the queue */
    struct qnode *head, *tail;
}queue;

typedef struct graph {              /* Adjacency list implementation of graph that contains an array of queues */
    int n;
    _Bool* gray_v;                    //array indicating color: visited vertex is gray (= 1), else white (= 0)
    struct queue* array;
}graph;

/* Sorts the queues in graph in ascending order and returning pointer to the same graph*/
struct graph* sort_queues(graph* g){
    int n;
    for(n=0;n<g->n;++n){
    /* If the queue is empty, return nothing */
    if (g->array[n].head==NULL)
        return NULL;

    /* curr traverses starting from g->array[n].head and curr_next points to node next to curr */
    qnode* curr = (qnode*)malloc(sizeof(qnode));
    qnode* curr_nex = (qnode*)malloc(sizeof(qnode));

    /* If curr's data is greater than curr_nex's data, we swap the data of curr and curr_nex */
    int temp;
    for(curr = g->array[n].head; curr!=NULL; curr = curr->next){
        for(curr_nex = curr->next; curr_nex!=NULL; curr_nex = curr_nex->next){
            if(curr->data > curr_nex->data){
                temp = curr->data;
                curr->data = curr_nex->data;
                curr_nex->data = temp;
            }
        }
    }
    /* De-allocating memory */
    free(curr);
    free(curr_nex);
    }

return g;
}

/* Adding an item at the end of the queue */
void enqueue(int value, queue* Q){
    /* Creating a new node which stores k and pointing its next pointer to NULL*/
    qnode* new_node = (qnode*)malloc(sizeof(qnode));
    new_node->data = value;

    /* If this would be the only node after adding, it will be the first and last node of the queue */
    if (Q->head == NULL) {
        Q->head = new_node;
        Q->tail = new_node;
        Q->tail->next = NULL;
    }

    /* Adding a node to a non-empty queue*/
    else {
        Q->tail->next = new_node;
        Q->tail = new_node;
        Q->tail->next = NULL;
    }
}

/* Removing and returning the first value in the queue */
int dequeue(queue* Q){
    /* If the queue is empty, return nothing */
    if (Q->head==NULL)
        return 0;

    /* Storing the first node's data in a temp node and moving "first" one node ahead*/
    qnode* temp = (qnode*)malloc(sizeof(qnode));
    temp = Q->head;
    int value = temp->data;

    /* Removing the first node */
    Q->head = Q->head->next;

    /* If there was only one node, then removing the first node will make it empty */
    if (Q->head == NULL)
        Q->tail = NULL;
    /* De-allocating memory */
    free(temp);

return value;
}

/* Adding an item at the end of the queue */
void add_edge(int vertex, int value, struct graph* g){
    /* Self-loop case */
    if(vertex==value)
        return;

    qnode* new_node = (qnode*)malloc(sizeof(qnode));
    new_node->data = value;
    /* If this would be the only node after adding, it will be the first and last node of the queue */
    if (g->array[vertex].head == NULL) {
        g->array[vertex].head = new_node;
        g->array[vertex].tail = new_node;
        g->array[vertex].tail->next = NULL;
    }
    /* Adding a node to a non-empty queue*/
    else {
        g->array[vertex].tail->next = new_node;
        g->array[vertex].tail = new_node;
        g->array[vertex].tail->next = NULL;
    }
}

void bfs(struct graph* g, int vertex){
    /* Initialising queue */
    queue* Q = (queue*)malloc(sizeof(queue));
    Q->head=Q->tail=NULL;

    qnode* curr = (qnode*)malloc(sizeof(qnode));
    g->gray_v[vertex] = 1;
    enqueue(vertex,Q);
    while(Q->head!=NULL){
        int curr_vertex = dequeue(Q);
        printf("%d ",curr_vertex);
        curr = g->array[curr_vertex].head;
        while(curr!=NULL){
                int adj_vertex = curr->data;
                if(!g->gray_v[adj_vertex]){
                    g->gray_v[adj_vertex] = 1;
                    enqueue(adj_vertex,Q);
                }
                curr = curr->next;
        }
    }
    free(curr);
    free(Q);
    printf("\n");
}

int main(){
char choice;
int i,n, startVertex, endVertex,count = 0;
scanf("%d",&n);

struct graph* g = (struct graph*)malloc(sizeof(struct graph));
g->n = n;
g->array = (struct queue*)malloc(n*sizeof(struct queue));
for(i=0;i<n;++i){
    g->array[i].head = NULL;
    g->array[i].tail = NULL;
}
g->gray_v = malloc(n*sizeof(_Bool));
for(i=0;i<n;i++)
    g->gray_v[i] = 0;
while(scanf(" %c",&choice)!=-1){
    if(choice == 'N'){
        char delimiter;
        scanf("%d", &startVertex);
        while(scanf("%d%c", &endVertex, &delimiter)){ // Add the edge (startVertex, endVertex) to your graph here.
            add_edge(startVertex,endVertex,g);
            add_edge(endVertex,startVertex,g);  //undirected graph
            if(delimiter == '\n') break; // Detecting end of line.
       }
     }
    else if(choice == 'B'){
        if(count==0){
            sort_queues(g);
            count = 1;
        }
        for(i=0;i<n;i++)
            g->gray_v[i] = 0;
        scanf("%d",&startVertex);
        bfs(g,startVertex);
    }
}

return 0;
}
