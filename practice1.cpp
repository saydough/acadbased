#include <iostream>
#include <cstdlib>
#define MAX_SIZE 100
using namespace std;

struct Stack{
    int top;
    string value;
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

void push(struct Stack* stack, string item) {
    if (!isFull(stack)) {
        struct Stack* nextNode = stack->next;

        struct Stack* newNode = (struct Stack*) malloc(sizeof(struct Stack));
        stack->next = newNode;
		newNode->value = item;
        newNode->next = nextNode;

        stack->top++;
    }
}

string pop(struct Stack* stack) {
    if (!isEmpty(stack)) {
        struct Stack* firstNode = stack->next;
        struct Stack* secondNode = firstNode->next;

        stack->next = secondNode;
        stack->top--;

        return firstNode->value;
    }

    return "";
}

string peek(struct Stack* stack) {
	return (!isEmpty(stack)) ? stack->next->value : "";
}

string reverse(string str){
    string s = "";
    for(int i = str.length() - 1; i >= 0; i--){
        s += str[i];
    }
    return s;
}

bool balanceChecker(struct Stack* stack, string str){
    struct Stack* left = createEmptyStack();
    struct Stack* right = createEmptyStack();
    struct Stack* store = createEmptyStack();
    string s;
    s = reverse(str);
    
    for(int i = 0; i < str.length() / 2; i++){
        push(left, string(1, str[i]));
    }
    for(int i = 0; i < s.length() / 2; i++){
        push(right, string(1, s[i]));
    }

    for(int i=0; i < str.length(); i++){
        if(peek(left) == "("){
            if(peek(right) == ")"){
                pop(left);
                pop(right);
            }
        }
        if(peek(left) == ")"){
            if(peek(right) == "("){
                pop(left);
                pop(right);
            }
        }
        if(peek(left) == "{"){
            if(peek(right) == "}"){
                pop(left);
                pop(right);
            }
        }
        if(peek(left) == "["){
            if(peek(right) == "]"){
                pop(left);
                pop(right);
            }
        }
    }
    if(isEmpty(left) && isEmpty(right)){
        return true;
    }
    else{
        return false;
    }
}

int main(void) {
    string exp;

    struct Stack* stack = createEmptyStack();
    cout << "Enter string: ";
    cin >> exp;

    if(exp.length() % 2 == 1){
        cout << "False";
    }
    else{
        if(balanceChecker(stack, exp)){
            cout << "True";
        }
        else{cout << "False";}
    }
    
    return 0;
}
