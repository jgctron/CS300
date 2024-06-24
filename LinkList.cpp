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

