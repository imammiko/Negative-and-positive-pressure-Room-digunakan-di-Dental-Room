 
#define MAXSTACK 10
  
class Stack { 
    int top; 
  
public: 
    int a[MAXSTACK]; // Maximum size of Stack 
  
    Stack() { top = -1; } 
    bool push(int x); 
    int pop(); 
    int peek(); 
    bool isEmpty(); 
}; 
  
bool Stack::push(int x) 
{ 
    if (top >= (MAXSTACK - 1)) {  
        return false; 
    } 
    else { 
        a[++top] = x;  
        return true; 
    } 
} 
  
int Stack::pop() 
{ 
    if (top < 0) {  
        return 0; 
    } 
    else { 
        int x = a[top--]; 
        return x; 
    } 
} 
int Stack::peek() 
{ 
    if (top < 0) { 
        return 0; 
    } 
    else { 
        int x = a[top]; 
        return x; 
    } 
} 
  
bool Stack::isEmpty() 
{ 
    return (top < 0); 
} 
  
// Driver program to test above functions 
 
