/* @Author
Student Name: <Muhammet Derviş Kopuz>
Student ID : <504201531>
Date: <13/01/2021> */

#include<fstream>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include <sstream>

#include "data_structs.h"

using namespace std;

int main(int argc, char* argv[])
{
  const char* filename = "data.txt";
  //const char* filename = argv[1];

  ifstream file(filename);

  if(!file)
  {
    cerr << "Cannot open file" << endl;
    return EXIT_FAILURE;
  }

  string firstInput;
  int secondInput;
  int linesRead = 0;
  string line;
  Process* newProcess = new Process;
  newProcess->task_stack.init();
  Queue inputQueue;
  inputQueue.init();
  while(getline(file, line)) {

    //cout<<line<<endl;
    istringstream iss(line);
    //cout<<line<<endl;
    //getline(file,line);
    //cout<<line<<endl;
    iss >> firstInput >> secondInput;
    //cout<<processName<<"  "<< priority<<endl;
    
    if (line == "")
    {
      linesRead = 0;
      inputQueue.queue(newProcess);
      newProcess->task_stack.init();
      continue;
    }
  
    if (linesRead == 0)
    {
      newProcess->name = firstInput;
      newProcess->priority = secondInput;
    } else if (linesRead == 1)
    {
      newProcess->arrival_time = stoi(firstInput);
      newProcess->task_count = secondInput;

      newProcess->deadline = newProcess->arrival_time;
    } else
    {
      Subtask* newSubtask = new Subtask;
      newSubtask->name = firstInput;
      newSubtask->duration = secondInput;
      newSubtask->next = NULL;

      newProcess->deadline += newSubtask->duration;

      newProcess->task_stack.push(newSubtask);
      //cout<<newProcess->task_stack.head->name<<endl;
    }
    linesRead++;
    
    

  }
  inputQueue.queue(newProcess); //push last process
  delete newProcess;

  //multiqueue
  MultiQueue* multiqueue = new MultiQueue;
  multiqueue->init();
  int time = 0;
  int specialCondCounter = 0;
  int lateness = 0;

  while (!inputQueue.isEmpty() || !multiqueue->queues[0].isEmpty() ||
  !multiqueue->queues[1].isEmpty() || !multiqueue->queues[2].isEmpty())
  {
    if(!inputQueue.isEmpty())
    {
      Process* front= inputQueue.front();
        if (front->arrival_time <= time)
        {
          //Add to multiqueue
          Process* process = inputQueue.dequeue();
          multiqueue->queue(process);

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
        multiqueue->dequeue(1);
      }
      
    } else if (!multiqueue->queues[1].isEmpty() && 
    (specialCondCounter == 0 || specialCondCounter == 1))
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
        multiqueue->dequeue(2);
      }
      
      specialCondCounter++;
      if (specialCondCounter == 2 && multiqueue->queues[2].isEmpty())
      {
        specialCondCounter == 0;
      }

    } else if (!multiqueue->queues[2].isEmpty() && specialCondCounter == 2)
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
        multiqueue->dequeue(3);
      }
      specialCondCounter = 0;
    }

    //sadece 3.queue kalma durumu
    if (multiqueue->queues[0].isEmpty() && multiqueue->queues[1].isEmpty()
    && !multiqueue->queues[2].isEmpty())
    {
      Process* currentProcess = multiqueue->queues[2].front();
      Subtask* currentSubtask = currentProcess->task_stack.pop();

      time += currentSubtask->duration;
      cout<<currentProcess->name<<" "<<currentSubtask->name<<endl;

      //task stack boşaldıysa processi uçur
      if (currentProcess->task_stack.isEmpty())
      {
        lateness += time - currentProcess->deadline;
        multiqueue->dequeue(3);
      }
    }
    
    
    
    



    
    
    //cout<<"sa"<<endl;
  }
  

  cout<<"Cumulative Lateness: "<<lateness<<endl;
  getchar();

}