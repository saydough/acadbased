#include <iostream>
#include <cstdlib>
#include <string>

#define MAX_SIZE 100
using namespace std;

struct Node {
    int value;
    struct Node* next;
};

struct Queue {
    int count;
    struct Node* rear;
    struct Node* front;
};

struct Queue* createEmptyQueue(void) {
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->count = 0;
    
    return queue;
}

bool isFull(struct Queue* queue) {
    return queue->count == MAX_SIZE;
}

bool isEmpty(struct Queue* queue) {
    return queue->count == 0;
}

void enqueue(struct Queue* queue, int item) {
    if (!isFull(queue)) {
        //create a new node
        struct Node* newItem = (struct Node*) malloc(sizeof(struct Node));
        newItem->value = item;
        newItem->next = NULL;

        if (queue->rear != NULL) {
            queue->rear->next = newItem;
        }

        queue->rear = newItem;

        queue->count++;

        if (queue->front == NULL) {
            queue->front = newItem;
        }
    }
}

int dequeue(struct Queue* queue) {
    if (!isEmpty(queue)) {
		struct Node* firstItem = queue->front;
        
		//assign front to next node
		if (firstItem != NULL) {
			queue->front =  firstItem->next;
		}
        
		queue->count--;
        
		if (queue->front == NULL) {
			queue->rear = NULL;
		}
		
		return firstItem->value;
	}
	
	return 0;
}

int peek(struct Queue* queue) {
	return !isEmpty(queue) ?  queue->front->value : 0;
}

void rearFirst(struct Queue* q){
    struct Node* temp = NULL;
    while(!isEmpty(q)){
        struct Node* current = q->front;
        dequeue(q);
        current->next = temp;
        temp = current;
    }

    while(temp != NULL){
        enqueue(q, temp->value);
        temp = temp->next;
    }
}

struct Queue* subtract(struct Queue* que, int num){
    rearFirst(que);
    while(num > 0 && que->front != NULL){ //num = 10, firstval = 5
        if(num >= que->front->value){
            num -= que->front->value;
            dequeue(que);
        }
        else{
            que->front->value -= num;
            num = 0;
        }
    }
    rearFirst(que);
    return que;
}
int main(void) {
    char ope;
    int num = 0, count = 0;
    struct Queue* queue = createEmptyQueue();
    do{
        cout << "Enter operation " << ++count << ": ";
        cin >> ope;

        switch(ope){
            case '+':
                cin >> num;
                enqueue(queue, num);
                break;
            case '-':
                dequeue(queue);
                break;
            case 'c':
                cin >> num;
                subtract(queue, num);
                break;
        }
    }
    while(ope != '0');
    
    struct Node* print = queue->front;
    while(print != nullptr){
        if(print != queue->front){
            cout << " -> ";
        }
        cout << print->value;
        print = print->next;
    }
    return 0;
}
