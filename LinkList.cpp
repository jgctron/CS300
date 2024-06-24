#include <iostream>
#include <string>

using namespace std;

struct Bid {
    string bidId;
    string title;
    string fund;
    double amount;

    Bid() : amount(0.0) {}
};

struct Node {
    Bid bid;
    Node* next;

    Node() : next(nullptr) {}
    Node(Bid aBid) : bid(aBid), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
};

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {}

LinkedList::~LinkedList() {
    Node* current = head;
    Node* next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::Append(Bid bid) {
    Node* newNode = new Node(bid);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void LinkedList::Prepend(Bid bid) {
    Node* newNode = new Node(bid);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}

void LinkedList::PrintList() {
    Node* current = head;
    while (current != nullptr) {
        cout << current->bid.bidId << ": " << current->bid.title << " | "
             << current->bid.amount << " | " << current->bid.fund << endl;
        current = current->next;
    }
}

void LinkedList::Remove(string bidId) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->bid.bidId == bidId) {
            if (previous == nullptr) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            if (current->next == nullptr) {
                tail = previous;
            }
            delete current;
            return;
        }
        previous = current;
        current = current->next;
    }
}

Bid LinkedList::Search(string bidId) {
    Node* current = head;
    while (current != nullptr) {
        if (current->bid.bidId == bidId) {
            return current->bid;
        }
        current = current->next;
    }
    return Bid();  // Return an empty bid if not found
}

int main() {
    LinkedList list;

    // Example usage:
    Bid bid1;
    bid1.bidId = "123";
    bid1.title = "Laptop";
    bid1.fund = "General Fund";
    bid1.amount = 150.0;

    Bid bid2;
    bid2.bidId = "456";
    bid2.title = "Tablet";
    bid2.fund = "General Fund";
    bid2.amount = 100.0;

    list.Append(bid1);
    list.Prepend(bid2);
    list.PrintList();

    Bid foundBid = list.Search("123");
    if (!foundBid.bidId.empty()) {
        cout << "Found bid: " << foundBid.bidId << " | " << foundBid.title << " | " << foundBid.amount << " | " << foundBid.fund << endl;
    } else {
        cout << "Bid not found." << endl;
    }

    list.Remove("123");
    list.PrintList();

    return 0;
}










Reflection and Pseudocode Document
Reflection:
Purpose of the Code: The purpose of this code is to implement a singly linked list in C++ to manage a collection of bids. It includes functionality to append, prepend, print, remove, and search bids in the list.

Techniques Implemented:
Append: Adds a bid to the end of the list by adjusting the tail pointer.
Prepend: Adds a bid to the front of the list by adjusting the head pointer.
PrintList: Traverses the list and prints each bid.
Remove: Removes a bid based on its ID by traversing the list and adjusting pointers to exclude the target node.
Search: Traverses the list to find a bid by its ID and returns the bid if found.

Challenges Encountered and Solutions:
Initializer List Error: The initial code used initializer lists to create Bid objects, which caused compilation errors. This was resolved by explicitly setting each member of the Bid structure.
Memory Management: Ensuring proper deletion of nodes to avoid memory leaks. This was managed by implementing a destructor that traverses the list and deletes each node.


Pseudocode:
Append(bid)
Create a new node with the bid
If head is null
    Set head and tail to the new node
Else
    Set tail's next to the new node
    Update tail to the new node

Prepend(bid)
Create a new node with the bid
If head is null
    Set head and tail to the new node
Else
    Set the new node's next to head
    Update head to the new node

PrintList()

Start with the head node
While current node is not null
    Print the current node's bid details
    Move to the next node

Remove(bidId)

Start with the head node and previous node as null
While current node is not null
    If current node's bidId matches
        If previous node is null
            Update head to current's next
        Else
            Set previous node's next to current's next
        If current's next is null
            Update tail to previous
        Delete current node
        Return
    Move to the next node with previous set to current

Search(bidId)

Start with the head node
While current node is not null
    If current node's bidId matches
        Return the current node's bid
    Move to the next node
Return an empty bid if not found


