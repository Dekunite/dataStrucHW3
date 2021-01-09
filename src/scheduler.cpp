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

  while (!inputQueue.isEmpty())
  {
    Process* process = inputQueue.dequeue();
    if (process->priority == 1)
    {
      multiqueue->queues[0].queue(process);
    } else if (process->priority == 2)
    {
      multiqueue->queues[1].queue(process);
    } else if (process->priority == 3)
    {
      multiqueue->queues[2].queue(process);
    }
    
    
    
  }
  

  getchar();


}