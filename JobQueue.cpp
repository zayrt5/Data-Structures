#include "JobQueue.hpp"
#include <iostream>

using namespace std;



JobQueue::JobQueue(){
    queueFront = 0;
    queueEnd = 0;
    counter = 0;
}

bool JobQueue::isEmpty(){
    //shout out my homies teaching me this one. less lines if / else
    bool endOut = (counter == 0) ? 1 : 0;
    return endOut;
}

bool JobQueue::isFull(){
    bool endOut = (counter == 20) ? 1 : 0;
    return endOut;
}

void JobQueue::enqueue(string job){
    if(!isFull()){
        if(isEmpty()){
            queue[0] = job;
            queueEnd = 1;
            counter++;
        }
        else if(queueEnd == 19){
            queue[queueEnd] = job;
            queueEnd = 0;
            counter++;
        }
        else{
            queue[queueEnd] = job;
            queueEnd++;
            counter++;
        }
    }
    else{
        cout << "Queue full, cannot add new job" << endl;
    }
}

void JobQueue::dequeue(){
    if(isEmpty()){
        cout << "Queue empty, cannot dequeue a job" << endl;
        return;
    }
    else{
        if(queueFront == 19){
            queue[queueFront] = "";
            queueFront = 0;
            counter --;
        }
        else{
            queue[queueFront] = "";
            queueFront++;
            counter--;
        }
    }
}

string JobQueue::peek(){
    if(isEmpty()){
        cout << "Queue empty, cannot peek" << endl;
        return "";
    }
    else{
        return queue[queueFront];
    }
}

int JobQueue::queueSize(){
    return counter;
}






