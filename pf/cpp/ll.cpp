#include <iostream>
using namespace std;

class LinkedList {
  class Node {
    public:
      int data;
    	Node* next;
      Node(int value){
        data = value;
        next = nullptr;
      }
  };

  Node* head;

  public:
    LinkedList() {
      head = nullptr;
    }

    ~LinkedList() {
      Node* curr;
      while(curr){
        Node* temp = curr;
        curr = curr->next;
        delete temp;
      }
    }

    void insertFront(int value) {
      Node* newNode = new Node(value);
      newNode->next = head;
      head = newNode;
    }

    void insertBack(int value) {
      Node* newNode = new Node(value);

      if (!head) {
        head = newNode;
        return;
      }

      Node* temp = head;
      while (temp->next) {
        temp = temp->next;
      }
      temp->next = newNode;
    }

    void deleteValue(int value) {
      if (!head) return;

      if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
      }

      Node* current = head;
      while (current->next && current->next->data != value) {
        current = current->next;
      }

      if (current->next) {
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
      }
    }

    void display() const {
      Node* temp = head;
      while (temp) {
        cout << temp->data << " -> ";
        temp = temp->next;
      }
      cout << "NULL" << endl;
    }
};

int main() {
  LinkedList list;

  list.insertBack(10);
  list.insertBack(20);
  list.insertFront(5);
  list.insertBack(30);

  cout << "Linked List: ";
  list.display();

  list.deleteValue(20);
  cout << "After deleting 20: ";
  list.display();

  return 0;
}

