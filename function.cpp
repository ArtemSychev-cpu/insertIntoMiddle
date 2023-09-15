#include<mutex>
#include<queue>

struct Node
{
    int value;
    Node* next;
    std::mutex* node_mutex;
    Node(int value) : value(value), next(nullptr), node_mutex(nullptr) {}
};

class FineGrainedQueue
{
    Node* head;
    std::mutex* queue_mutex;
public:
    void insertIntoMiddle(int value, int pos);
};

void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    Node* newNode = new Node(value); 

    int currentPos = 0;
    queue_mutex->lock();    
    Node* current = head;

    while (currentPos < pos - 1 && current->next != nullptr)     
    {
        current = current->next;
        currentPos++;
    }
    current->node_mutex->lock();    
    queue_mutex->unlock();          

    Node* next = current->next;     

    current->next = newNode;
    newNode->next = next;          
    current->node_mutex->unlock();  
}
