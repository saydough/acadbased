#include <iostream>
#include <cstdlib>
#define MAX_SIZE 100
using namespace std;

struct Stack {
    int top;
    int value;
    struct Stack* next;
};

struct Stack* createEmptyStack(void) {
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->top = -1;

    return stack;
}

bool isFull(struct Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int item) {
    if (!isFull(stack)) {
        struct Stack* nextNode = stack->next;

        struct Stack* newNode = (struct Stack*) malloc(sizeof(struct Stack));
        stack->next = newNode;
		newNode->value = item;
        newNode->next = nextNode;

        stack->top++;
    }
}

int pop(struct Stack* stack) {
    if (!isEmpty(stack)) {
        struct Stack* firstNode = stack->next;
        struct Stack* secondNode = firstNode->next;

        stack->next = secondNode;
        stack->top--;

        int value = firstNode->value;
        free(firstNode);
        return value;
    }

    return 0;
}

int peek(struct Stack* stack) {
	return (!isEmpty(stack)) ? stack->next->value : 0;
}

void display(struct Stack* stack) {
	struct Stack* current = stack->next;
	while (current != NULL) {
		cout << current->value << endl;
        current = current->next;
    }
}

int main(void) {
    char op;
    int number = 0, counter = 0;
    struct Stack* stack = createEmptyStack();
    struct Stack* minStack = createEmptyStack();

    do{
        cout << "Enter operation " << ++counter << ": ";
        cin >> op;

        if(op == '+'){
            cin >> number;
            push(stack, number);

            if(isEmpty(minStack) || number <= peek(minStack)){
                push(minStack, number);
            }
        }
        else if(op == '-'){
            int popped = pop(stack);

            if(popped == peek(minStack)){
                pop(minStack);
            }
        }
    }
    while(op != '#');

    cout << "Minimum element: " << peek(minStack);

    while(!isEmpty(stack)){
        pop(stack);
    }
    free(stack);
    free(minStack);
    return 0;
}
