#include <iostream>
#define SIZE 100

using namespace std;

class stack {
  int s[SIZE];
  int top;
public:
  stack(){
    top = 0;
  }
  void push(int item);
  int pop();

  void display();
  void display(int index);
};

void stack::push(int item){
  if(top == SIZE){
    cout << "Stack Overflow" << endl;
    return;
  }
  s[top++] = item;
}

int stack::pop(){
  if(top == 0){
    cout << "Stack Underflow" << endl;
    return -1;
  }
  return s[--top];
}

void stack::display(){
  if (top == 0) {
    cout << "Stack is empty" << endl;
    return;
  }

  for(int i = 0; i < top; i++) {
    cout << s[i] << " ";
  }
  cout << endl;
}

void stack::display(int index){
  if (index < 0 || index >= top) {
    cout << "Invalid index" << endl;
    return;
  }
  cout << "Element at index " << index << ": " << s[index] << endl;
}

int main(){
  stack st;
  st.push(31);
  st.push(27);
  st.push(56);
  st.display();
  st.display(2);
  cout << "Popped element: " << st.pop() << endl;
  st.display();

  return 0;
}
