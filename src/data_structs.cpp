/* @Author
Student Name: <Muhammet Derviş Kopuz>
Student ID : <504201531>
Date: <13/01/2021> */

#include <iostream>
#include "data_structs.h"

using namespace std;

void Stack::init() {
  head= NULL;
}

void Stack::close() {

  Subtask* subtask;
  while (head)
  {
    subtask = head;
    head = head->next;
    delete subtask;
  } 
}

void Stack::push(Subtask* in) {

  Subtask* newSubtask = new Subtask;
  newSubtask->name = in->name;
  newSubtask->duration = in->duration;
  newSubtask->next = head;
  head = newSubtask;
  
}

Subtask* Stack::pop() {

  Subtask* topSubtask;
  Subtask* temp;
  topSubtask = head;
  head = head->next;
  //temp = topSubtask olur mu?
  temp->name = topSubtask->name;
  temp->name = topSubtask->duration;
  delete topSubtask;
  return temp;
  
}

bool Stack::isEmpty() {

  return (head == NULL);
}


void Queue::init() {

  head = NULL;
  tail = NULL;
}

void Queue::close() {

  Process* process;
  while (head)
  {
    process = head;
    head = head->next;
    delete process;
  }
}

void Queue::queue(Process* in) {
  
  Process* newProcess = new Process;
  newProcess->name = in->name;
  newProcess->arrival_time = in->arrival_time;
  newProcess->deadline = in->deadline;
  newProcess->task_count = in->task_count;
  newProcess->priority = in->priority;
  newProcess->task_stack = in->task_stack;
  newProcess->next = NULL;

  if (isEmpty()) //first element
  {
    tail = newProcess;
    head = tail;
  } else
  {
    tail->next = newProcess;
    tail = newProcess;
  }
  
}

Process* Queue::dequeue() {

  Process* process;
  Process temp;

  process = head;
  head = head->next;
  if (head == NULL)
    tail = NULL;
  /*
  temp.name = process->name;
  temp.arrival_time = process->arrival_time;
  temp.deadline = process->deadline;
  temp.task_count = process->task_count;
  temp.priority = process->priority;
  temp.task_stack = process->task_stack;
  delete process;
  */
  return process;
  
}

bool Queue::isEmpty() {
  return (head == NULL);
}

Process* Queue::front() {
  return (head);  
}

void MultiQueue::init() {

  queues[0].init();
  queues[1].init();
  queues[2].init();

}
/*
void MultiQueue::close() {
  
}

void MultiQueue::queue(Process* in) {
  
}

Process* MultiQueue::dequeue(int priority) {
  
}

bool MultiQueue::isEmpty() {
  
}

Process* MultiQueue::front(int priority) {
  
}
*/