/*
This file is created by :
Luu Viet Anh Tran a1713568
Le Dinh Minh Long a1701729

Final Version Created on 9th September 2018

For Assignment 1 Operating System
*/








//import libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//creating a node struct for storing data, each node struct represent a client
struct Node
{
  
  
  //variables that are used for calculation
  int age;        //age
  int totalTime; //total time needed to finish a client
  int noOfRun;   //number of run that has be ran
  int ranTime;   //total time that has been ran, counted in time units



  //variables that need to be displayed at the end
  char* customerID; 
  int arrivalTime;  
  int priority;     
  int end;       
  int ready;
  int cpu;
  int waiting;
  
  struct Node* next;  
};


//a queue struct to store nodes
struct Queue
{
  struct Node* front;
  struct Node* back;
};

//a global variable to keep track of time
int time = 0;


//a function to create a new client
struct Node* createBlock(int my_age, int my_totaltime, int my_noofrun, int my_rantime, char* my_customerID, int my_arrivalTime, int my_priority, int my_end, int my_ready, int my_cpu, int my_waiting)
{
  
  struct Node* currentNode;
  currentNode = (struct Node*)malloc(sizeof(struct Node));

  currentNode->age = my_age;
  currentNode->totalTime = my_totaltime;
  currentNode->noOfRun = my_noofrun;
  currentNode->ranTime = my_rantime;
  currentNode->customerID = my_customerID;
  currentNode->arrivalTime = my_arrivalTime;
  currentNode->priority = my_priority;
  currentNode->end = my_end;
  currentNode->ready = my_ready;
  currentNode->cpu = my_cpu;
  currentNode->waiting = my_waiting;


  currentNode->next = NULL;

  return currentNode;

}

//a function to create a new queue
struct Queue* createQueue()
{
  struct Queue* q;
  q = (struct Queue*)malloc(sizeof(struct Queue));

  q->front = NULL;
  q->back = NULL;
  return q;
}

//a function to display the queue that is passed in
void display(struct Queue* q)
{
  int i = 0;
  if(q->front == NULL)
  {
    printf("queue is empty\n");
  }
  else
  {
    struct Node* curr = q->front;

    //traversing the list
    while(curr->next != NULL)
    {
      printf("%s-->", curr->customerID);
      curr = curr->next;
      
    }

    // at this point, curr pointer is pointing to the last block
    printf("%s-->NULL\n", curr->customerID);

  }
  
}


//a function to push a new client into a queue
struct Queue* Push(struct Queue* q, struct Node* block)
{ 
  struct Node* curr = block;

  if(q->back == NULL) //if queue is currently empty
  {
    q->back = curr;
    q->front = curr;
    return q;
  }

  q->back->next = curr;
  q->back = curr;
  curr->next = NULL; 

  
  return q;
}

//a function to pop the front of the queue out and return the front value
struct Node* Pop(struct Queue* q)
{
  if(q->front == NULL) 
  {
    return NULL;
  }


  struct Node* curr = q->front;
  q->front = q->front->next;
  

  if(q->front == NULL) 
  {
    q->back = NULL;
  }

  return curr;

}


//a function to swap 2 nodes, by swapping their data
void swap(struct Node * a, struct Node * b)
{
  //swap age
  int temp = a->age;
  a->age = b->age;
  b->age = temp;
  
  //swap totalTime
  int temp2 = a->totalTime;
  a->totalTime = b->totalTime;
  b->totalTime = temp2;

  //swap noOfRun
  int temp3 = a->noOfRun;
  a->noOfRun = b->noOfRun;
  b->noOfRun = temp3;

  //swap ranTime
  int temp4 = a->noOfRun;
  a->noOfRun = b->noOfRun;
  b->noOfRun = temp4;


  //swap customerID
  char* temp5 = (char *)malloc((strlen(a->customerID) + 1) * sizeof(char));   
  strcpy(temp5,a->customerID);
  strcpy(a->customerID,b->customerID);
  strcpy(b->customerID,temp5);
  free(temp5);

  //swap arrival time
  int temp6 = a->arrivalTime;
  a->arrivalTime = b->arrivalTime;
  b->arrivalTime = temp6;

  //swap priority
  int temp7 = a->priority;
  a->priority = b->priority;
  b->priority = temp7;

  //swap end
  int temp8 = a->end;
  a->end = b->end;
  b->end = temp8;

  //swap ready
  int temp9 = a->ready;
  a->ready = b->ready;
  b->ready = temp9;

  //swap cpu
  int temp10 = a->cpu;
  a->cpu = b->cpu;
  b->cpu = temp10;

  //swap waiting
  int temp11 = a->waiting;
  a->waiting = b->waiting;
  b->waiting = temp11;

  
}

//a function to sort a queue of client, using Bubble Sort algorithm
void Sort(struct Node* head)
{
  //a flag to mark swapped and an iterator i
  int swapped,i;
  struct Node * ptr1;
  struct Node * ptr2 = NULL;

  //checking for empty list

  if(head == NULL)
  {
    return;
  }

  
  do 
  {
    swapped = 0;
    ptr1 = head; //have ptr1 starting at head

    while(ptr1->next != ptr2)
    {
      //if one element's arrival time is bigger than the next's
      if(ptr1->arrivalTime > ptr1->next->arrivalTime)
      {
        swap(ptr1,ptr1->next);
        swapped = 1;
      }

      //if is done or nothing is done, keep moving to the next
      ptr1 = ptr1->next;
    }
    ptr2 = ptr1;
  }
  while(swapped == 1);

}




//a function to check if a queue is empty
int isEmpty(struct Queue* q)
{
  if(q->front == NULL)
  {
    return 1;
  }
  return 0;
}


//a function to delete an arbitrary node in the queue, except for the last node
void deleteNode1(struct Queue* q, struct Node* curr, struct Node* currp) 
{

    struct Node* temp;
    temp = curr->next; 

    //swap data;
    curr->customerID = curr->next->customerID;
    curr->arrivalTime = curr->next->arrivalTime;
    curr->priority = curr->next->priority;
    curr->age = curr->next->age;
    curr->totalTime = curr->next->totalTime;
    curr->noOfRun = curr->next->noOfRun;
    curr->ranTime = curr->next->ranTime;
    curr -> cpu = curr -> next -> cpu;
    curr -> end = curr -> next -> end;
    curr -> ready = curr -> next -> ready;
    curr -> waiting = curr -> next -> waiting;

    curr->next = temp->next;

    if (curr -> next == NULL) {
      q->back = curr;
    }

    if (currp == NULL)  {
      q->front = curr;
    }

    free(temp); 
  
}

//a function used to delete the last node in the queue
void deleteNode2(struct Queue* q, struct Node* currp) 
{
  q->back = currp;  
  currp->next = NULL;
}

//a deleteNode function to encapsulate deleteNode1 and deleteNode2
void deleteNode(struct Queue* q, char* key)
{
  struct Node* iter;
  iter = q->front;

  struct Node* prev;
  prev = NULL;
  
  //traversing through the list
  while(iter != NULL)
  {

    if(strcmp(iter->customerID,key) == 0) 
    {
      if(prev == NULL && iter->next == NULL) //if queue has only one node
      {

        Pop(q);
      }
      else if(iter->next == NULL) // if it is the last node
      {
        deleteNode2(q,prev);
      }
      else  //if it is a normal case, not the last node
      {
        deleteNode1(q,iter,prev);
      }
      
    }

    prev = iter;
    iter = iter->next;
  }

}



//a function to display the final output
void displayOutput(struct Queue* finishQ)
{
  printf("Index\tPriority\tArrival\tEnd\tReady\tCPU_Time\tWaiting\n");

  struct Node* iter;
  iter = finishQ->front;

  if(iter == NULL)  {
    printf("Nothing in the queue \n");
    return;
  }

  //traversing the queue
  while(iter->next != NULL)
  {

    printf("%s\t%i\t%i\t%i\t%i\t%i\t%i\n",iter->customerID,iter->priority,iter->arrivalTime,iter->end,iter->ready,iter->cpu,iter->waiting);
    iter = iter->next;
  }
  printf("%s\t%i\t%i\t%i\t%i\t%i\t%i\n",iter->customerID,iter->priority,iter->arrivalTime,iter->end,iter->ready,iter->cpu,iter->waiting);
}


//a function to traverse through every element of other queues and increase all the client's age by 1
//the idea is to skip aging the running client, so we pass in q2->next instead of q2->front if the running client
//is in q2, we do the same thing for q3. If the running client is in q1, we don't need to care and can pass 
//in both q2->front and q3->front
void iterate1(struct Node* q2Start, struct Node* q3Start)
{
  struct Node* curr;

  //increase age of clients in q2
  curr = q2Start;


  while(curr != NULL)
  {
    curr->age++;
  
    curr = curr->next;
  }



  //increase age of clients in q3
  curr = q3Start;

  while(curr != NULL)
  {
    curr->age++;
   
    curr = curr->next;
  }


}

//a function to traverse through all the other queues and do promotion, when a client has
//enough age
void iterate2(struct Node* q2Start, struct Node* q3Start, struct Queue* q1b, struct Queue* q2, struct Queue* q3)
{
  struct Node* curr;

  //promote client in q2
  curr = q2Start;

  while(curr != NULL)
  {
    
    if(curr->age == 8)
    {
      curr->age = 0;
      curr->priority++; 
      

      if(curr->priority == 5)
      {
        
        //create a copy
        struct Node* temp;
        temp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
        //push to q1b
        Push(q1b,temp);
        
        //delete the original
        deleteNode(q2,curr->customerID);

        continue;

      }
    }

    curr = curr->next;
  }



  //promote clients in q3
  curr = q3Start;

  while(curr != NULL)
  {
    if(curr->age == 8)
    {
      curr->age = 0;
      curr->priority++;
      

      if(curr->priority == 3)
      {
        
        //create a copy
        struct Node* temp;
        temp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
        //push len q2
        Push(q2,temp);
        //delete the original
        deleteNode(q3,curr->customerID);
      }
    }



    curr = curr->next;
  }


}


//a function to distribute the clients stored in the original queue (q) into q1a, q1b, q2, q3 at the exact time
//that they arrived
void distribute(struct Node* iter, struct Queue* q, struct Queue* q1a, struct Queue* q1b, struct Queue* q2, struct Queue* q3)
{
  if(iter->priority == 6) //if priority of the client passed is 6, we put it in q1a
  { 
    
    struct Node* curr;
    curr = Pop(q);  
    struct Node* temp;
    temp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
    Push(q1a,temp);
   
  }
  if(iter->priority == 5) //if priority of the client passed is 5, we put it in q1b
  {
   
    struct Node* curr;
    curr = Pop(q); 
    struct Node* temp;
    temp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
    Push(q1b,temp);
   

  }
  if(iter->priority == 4 || iter->priority == 3 ) //if priority of the client passed is 4 or 3, we put it in q2
  {
    
    struct Node* curr;
    curr = Pop(q);  
    struct Node* temp;
    temp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
    Push(q2,temp);
    

  }
  if(iter->priority == 2 || iter->priority == 1 ) //if priority of the client passed is 2 or 1, we put it in q3
  {
    
    struct Node* curr;
    curr = Pop(q);  
    struct Node* temp;
    temp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
    Push(q3,temp);
    
  }
}


//a global struct node to point to the running client
struct Node* curr;


int main(int argc, char* argv[])
{
  //reading input

  FILE * fp = fopen(argv[1], "r"); //create a file pointer

  if(fp == NULL)
  {
    printf("cannot open file\n"); //error handling
  }

  struct Queue* q = createQueue(); //create the original queue


  int at,prior,age,tt;
  char id[3];              //variables for storing inputs
  char *IDcopy;

  while (!feof(fp))
  {
    fscanf(fp, "%s %i %i %i %i",id,&at,&prior,&age,&tt);  //scan input


    IDcopy = malloc(sizeof(IDcopy));
    strcpy(IDcopy, id);

    //age, totaltime, noofrun,rantime,customerid,arrivaltime,priority,end,ready,cpu,waiting
    struct Node* temp = createBlock(age,tt,0,0,IDcopy,at,prior,0,0,tt,0); //create a block

    q = Push(q,temp);  //push the block to the original queue
  }


  fclose(fp);  //close file



  struct Node * head;
  head = q->front;    //create a pointer that starts at the front of the original queue

  
  Sort(head);     //pass in that pointer and sort the original queue

  //q is now sorted

  
  
  
  
  //create 4 queues for storing clients to run and 1 finish queues for storing results

  struct Queue* q1a = createQueue(); //priority 6
  struct Queue* q1b = createQueue(); //priority 5
  struct Queue* q2 = createQueue();  //priority 3 to 5
  struct Queue* q3 = createQueue();  //priority below 3
  struct Queue* finishQ = createQueue();

  

 //another pointer to iterate through the original queue
  struct Node* iter;
  iter = q->front;
  
  
  while(1)
  {


    //step 0: Check for finish client
    if (time != 0)  
    {
      if (curr -> totalTime == 0) //if there is no time left to run, a client is finished
      {
        curr -> end = time;  //mark the end time

        curr -> waiting = (curr -> end) - (curr -> cpu) - (curr -> ready); //calculate waiting time
        
        if (curr -> priority == 6)  //if that finished client priority is 6, we know it was from queue 1a
        {
          //create a block 
          struct Node* finTemp;
          finTemp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
          //send it to finish q
          Push(finishQ,finTemp);
          
          //increase age
          iterate1(q2->front,q3->front);  
          //pop the original
          Pop(q1a);
          
        }

        else if (curr -> priority == 5)//if that finished client priority is 5, we know it was from queue 1b
        {
          //same process happens again
          struct Node* finTemp;
          finTemp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
         
          Push(finishQ,finTemp);


          iterate1(q2->front,q3->front);
          Pop(q1b);
          
        }

        else if (curr -> priority == 4 || curr -> priority == 3)//if that finished client priority is 4 or 3, we know it was from queue 2
        {
          struct Node* finTemp;
          finTemp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
          
          Push(finishQ,finTemp);


          iterate1(q2->front->next,q3->front);
          Pop(q2);
          
        }

        else if (curr -> priority == 2 || curr -> priority == 1)//if that finished client priority is 2 or 1, we know it was from queue 3
        {
          struct Node* finTemp;
          finTemp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
          
          Push(finishQ,finTemp);


          iterate1(q2->front,q3->front->next);
          Pop(q3);
        }
      }
    }



    //reset curr back to front
    if (isEmpty(q1a) == 0)
    {
      curr = q1a -> front;
    }
    else if (isEmpty(q1b) == 0)
    {
      curr = q1b ->front;
    }
    else if (isEmpty(q2) == 0)
    {
      curr = q2 -> front;
    }
    else if (isEmpty(q3) == 0)
    {
      curr = q3 -> front;
    }

    //step 1: loop through all other queues to increase the age - calculate aging

    //if it is not time 0
    if(time != 0) 
    {
      //we check for priorities to know which queue it is from, so that we can pass the correct argument to iterate 1 and age q2 and q3 correctly
      if(curr->priority == 5 || curr->priority == 6) //it is from q1a or q1b
      {
        if(curr->ranTime == 5)
        {
          iterate1(q2->front,q3->front);

        }
      }
      else if(curr->priority == 4 || curr->priority == 3 ) //it is from q2
      {
        if(curr->ranTime == 10)
        {
          iterate1(q2->front->next,q3->front);

        } 
      }
      else if((curr->priority == 2 || curr->priority == 1) && curr -> next != NULL) //it is from q3
      {
        if(curr->ranTime == 20)
        {

          iterate1(q2->front,q3->front->next);

          
        }

      }
    }

    

    //step 2: distribute processes on their corresponding time

    

    while(iter != NULL && iter->arrivalTime == time)
    {

      
      //PRE-EMPTION
      //if it is not time 0
      if(time != 0)
      {
        //same process, we base on its priority to figure out which queue it belongs to
        if (iter -> priority == 6 || iter ->priority == 5) // a newArrival that belongs to q1
        {
          if (curr -> priority == 4 || curr -> priority == 3) //then we check the status of the running process (curr), which queue its in, in this case, q2
          {
            if (curr -> ranTime != 10 && curr -> noOfRun != 5) //if ran time is 10 (equals to a time quantum of q2), and it has ran 5 times
            {
              curr -> ranTime = 0; //reset ranTime
              curr -> noOfRun ++; //increase number of runs
              //increase age of every other client, except the running one
              iterate1(q2->front->next,q3->front);
              //push the client to the end of queue 2
              struct Node* preTemp;
              preTemp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
              Push(q2,preTemp);
              Pop(q2);
            }
          }
          if (curr -> priority == 2 || curr -> priority == 1) // same process happens again, for queue 3
          {
            if (curr -> ranTime != 20 && curr -> noOfRun != 2)
            {
              curr -> ranTime = 0;
              curr -> noOfRun ++;
              //iterate1 de tang age truoc
              iterate1(q2->front,q3->front->next);
              //push the client to the end of queue 3
              struct Node* preTemp;
              preTemp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
              Push(q3,preTemp);
              Pop(q3);
            }
          }
        }



        if (iter -> priority == 4 || iter->priority == 3) //if new arrival is in queue 2
        {
          if (curr -> priority == 2 || curr -> priority == 1) //and running client is in queue 3
          {
            if (curr -> ranTime != 20 && curr -> noOfRun != 2) //checks corresponding time quantum and number of run
            {
              curr -> ranTime = 0;
              curr -> noOfRun ++;

              struct Node* preTemp;
              preTemp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
              Push(q3,preTemp);
              Pop(q3);
            }
          }
        }




      }

      //preemption ends here ---------------------------
      
      distribute(iter,q,q1a,q1b,q2,q3);
      iter = iter->next;
    }

    //step 3.1: push to the end after running

    //DEMOTION

    if(time != 0) 
    {
      
      //finds out what queue the running cient belongs to
      if(curr->priority == 6) //it belongs to q1a
      {
        if(curr->ranTime == 5) //corresponding time quantum
        {
          curr -> noOfRun++; //increase number of run
          curr -> ranTime = 0; //reset rantime

          if (curr -> noOfRun == 5) //if threshold for q1a is reached, we push it down to lower priority queue -  demote push
          {
            
            curr -> priority --; //decrease priority
            curr -> noOfRun = 0; //reset number of run

            //demote push to q1b
            struct Node* deTemp;
            deTemp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
            Push(q1b,deTemp);   
            Pop(q1a);
            
              
          }
          else //if threshold is not reached, we push it back to the end of the current queue - keep push
          {
            struct Node* pTemp;
            pTemp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
            Push(q1a,pTemp);

            Pop(q1a);
            
          }
        }
      }
      else if(curr->priority == 5) //same thing happen for q1b
      {
        if (curr->ranTime == 5)
        {
          curr -> noOfRun ++;
          curr -> ranTime = 0;

          if (curr -> noOfRun == 5) { //demote push
            curr -> priority --;
            curr -> noOfRun = 0;
           
              
            struct Node* deTemp;
            deTemp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
            Push(q2,deTemp);

            Pop(q1b);
          
            
          
          } 
          else //keep push
          {
            struct Node* pTemp;
            pTemp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
            Push(q1b,pTemp);


            Pop(q1b);
            
          }
        }
      }
      else if(curr->priority == 4 || curr->priority == 3 ) //same thing happen for q2
      {
        if(curr->ranTime == 10)
        {
          curr -> noOfRun ++;
          curr -> ranTime = 0;
          if (curr -> noOfRun == 2) { //demote push
            
            curr -> priority --;
            

            curr -> noOfRun = 0;
            if (curr -> priority == 2)  {
              
              struct Node* deTemp;
              deTemp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
              Push(q3,deTemp);


              Pop(q2);
              
            }
            else //keep push
            {
              struct Node* pTemp;
              pTemp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
              Push(q2,pTemp);

              Pop(q2);
              
            }
          } 

        }
      }
      else if(curr->priority == 2 || curr->priority == 1) //same thing for q3
      {
        if(curr->ranTime == 20)
        {
          
          curr -> noOfRun = 0;
          curr -> ranTime = 0; //but this time we only have keep push, because there is no lower priority queue to demote to
          struct Node* pTemp;
          pTemp = createBlock(curr->age,curr->totalTime,curr->noOfRun,curr->ranTime,curr->customerID,curr->arrivalTime,curr->priority,curr->end,curr->ready,curr->cpu,curr->waiting);
          Push(q3,pTemp);

          Pop(q3);
          
        }
      }


    }



    //step 3.2: Promotion

    iterate2(q2->front,q3->front,q1b,q2,q3);


    //step 4: Actually running the clients


    if(isEmpty(q1a) == 0)  //if q1a is not empty -> run q1a immediately
    {
      curr = q1a->front;
      if ((curr -> totalTime) == (curr -> cpu)) { //run the first time
        curr -> ready = time; //mark ready time
      }
   
      curr->ranTime ++;
      curr->totalTime --;
      curr->age = 0;

    }
    else if(isEmpty(q1b) == 0) //if q1a is empty -> check q1b right away
    {
      curr = q1b->front;
      if (curr -> totalTime == curr -> cpu) { //run the first time
        curr -> ready = time;
      }
     
      curr->ranTime ++;
      curr->totalTime --;
      curr -> age = 0;

    }
    else if(isEmpty(q2) == 0) // if q1b is empty, then we check q2
    {
      curr = q2->front;
      if (curr -> totalTime == curr -> cpu) { //run the first time
        curr -> ready = time;
      }

      curr->ranTime ++;
      curr->totalTime --;
      curr -> age = 0;

    }
    else if(isEmpty(q3) == 0) // if q2 is empty, then we run q3
    {
      curr = q3->front;
      if (curr -> totalTime == curr -> cpu) { //run the first time
        curr -> ready = time;
      }
      
      curr->ranTime ++;
      curr->totalTime --;
      curr -> age = 0;

    }
    
    

    //after running, we check if all 4 queues are empty, if yes, then we terminate the main loop
    if (isEmpty(q1a) == 1 && isEmpty(q1b) == 1 && isEmpty(q2) == 1 && isEmpty(q3) == 1) //stopping condition
    {
      break;
    }

    
    time ++;



  
  }
  
  //at this point, all the finished client have been pushed to finishQ, so we display the finishQ using the function
  //we wrote above
  displayOutput(finishQ);

  return 0;
}