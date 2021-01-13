/* @Author
Student Name: <Muhammet Derviş Kopuz>
Student ID : <504201531>
Date: <13/01/2021> */

#include<fstream>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>

#include "data_structs.h"

using namespace std;

int main(int argc, char* argv[])
{
  //const char* filename = "data.txt";
  const char* filename = argv[1];

  ifstream file(filename);

  if(!file)
  {
    cerr << "Cannot open file" << endl;
    return EXIT_FAILURE;
  }

  string firstInput;
  int secondInput;
  int linesRead = 0;
  int taskCount = 0;
  int taskRead = 0;
  Process* newProcess = new Process;
  newProcess->task_stack.init();
  Queue inputQueue;
  inputQueue.init();
  while(file >> firstInput >> secondInput) {
    
    if (linesRead == 0)
    {
      newProcess->name = firstInput;
      newProcess->priority = secondInput;
    } else if (linesRead == 1)
    {
      newProcess->arrival_time = stoi(firstInput);
      newProcess->task_count = secondInput;
      taskCount = secondInput;

      newProcess->deadline = newProcess->arrival_time;
    } else
    {
      Subtask* newSubtask = new Subtask;
      newSubtask->name = firstInput;
      newSubtask->duration = secondInput;
      newSubtask->next = NULL;
      taskRead++;

      newProcess->deadline += newSubtask->duration;

      newProcess->task_stack.push(newSubtask);
      delete newSubtask;
    }
    linesRead++;
  
    if (taskRead == taskCount && !taskRead==0 && !taskCount==0)
    {
      linesRead = 0;
      taskCount = 0;
      taskRead = 0;
      inputQueue.queue(newProcess);
      newProcess->task_stack.init();
    }
    
  }
  delete newProcess;

  //multiqueue
  MultiQueue* multiqueue = new MultiQueue;
  multiqueue->init();
  int time = 0;
  int specialCondCounter = 0;
  int lateness = 0;

  while (!inputQueue.isEmpty() || !multiqueue->isEmpty())
  {
    if(!inputQueue.isEmpty())
    {
      Process* front= inputQueue.front();
      if (front->arrival_time <= time)
      {
        //Add to multiqueue
        Process* process = inputQueue.dequeue();
        multiqueue->queue(process);
        delete process;

        if (!inputQueue.isEmpty())
        {
          Process* nextFront = inputQueue.front();
          if (nextFront->arrival_time <= time)
          {
            continue;
          }
        }
      }
    }

    if (specialCondCounter == 2 && multiqueue->queues[2].isEmpty())
    {
      specialCondCounter = 0;
    }

    //scheduler for multiqueue
    //priority 1
    if (!multiqueue->queues[0].isEmpty())
    {
      Process* currentProcess = multiqueue->queues[0].front();
      Subtask* currentSubtask = currentProcess->task_stack.pop();

      time += currentSubtask->duration;
      cout<<currentProcess->name<<" "<<currentSubtask->name<<endl;

      //task stack boşaldıysa processi uçur
      if (currentProcess->task_stack.isEmpty())
      {
        lateness += time - currentProcess->deadline;
        delete multiqueue->dequeue(1);
      }
      delete currentSubtask;
      
    } else if (!multiqueue->queues[2].isEmpty() && specialCondCounter == 2)
    //priority 3 & cond active
    {
      Process* currentProcess = multiqueue->queues[2].front();
      Subtask* currentSubtask = currentProcess->task_stack.pop();

      time += currentSubtask->duration;
      cout<<currentProcess->name<<" "<<currentSubtask->name<<endl;

      //task stack boşaldıysa processi uçur
      if (currentProcess->task_stack.isEmpty())
      {
        lateness += time - currentProcess->deadline;
        delete multiqueue->dequeue(3);
      }
      specialCondCounter = 0;
      delete currentSubtask;

    } else if (!multiqueue->queues[1].isEmpty())
    //priority 2
    {
      Process* currentProcess = multiqueue->queues[1].front();
      Subtask* currentSubtask = currentProcess->task_stack.pop();

      time += currentSubtask->duration;
      cout<<currentProcess->name<<" "<<currentSubtask->name<<endl;

      //task stack boşaldıysa processi uçur
      if (currentProcess->task_stack.isEmpty())
      {
        lateness += time - currentProcess->deadline;
        delete multiqueue->dequeue(2);
      }
      delete currentSubtask;
      
      specialCondCounter++;

    } else if (!multiqueue->queues[2].isEmpty())
    //priority 3
    {
      Process* currentProcess = multiqueue->queues[2].front();
      Subtask* currentSubtask = currentProcess->task_stack.pop();

      time += currentSubtask->duration;
      cout<<currentProcess->name<<" "<<currentSubtask->name<<endl;

      //task stack boşaldıysa processi uçur
      if (currentProcess->task_stack.isEmpty())
      {
        lateness += time - currentProcess->deadline;
        delete multiqueue->dequeue(3);
      }
      specialCondCounter = 0;
      delete currentSubtask;

    } else
    {
      time++;
    }
     
  }
  
  cout<<"Cumulative Lateness: "<<lateness<<endl;
  multiqueue->close();
  delete multiqueue;
  return EXIT_SUCCESS;
  
}