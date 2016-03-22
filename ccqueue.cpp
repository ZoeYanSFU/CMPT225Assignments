// File name: ccqueue.cpp
// Author:      Meihui Yan & Jiameng Duan
// Date:        January 31, 2016
// Description: Definition of a customer complaint queue class for CMPT 225 assignment 2
#include "ccqueue.h"
#include "dlinkedlist.h"
#include "ticket.h"
#include <string>
#include <iostream>
using namespace std;

// default constructor
// maxticketid begins at 0
// note that tickets does not need to be re-declared

CCQueue::CCQueue()
{
    maxticketid = 0;    // largest-valued ticketid. Used to generate new tickets to insert
}

// enqueues a new ticket at the back of the ticket queue and returns true
// ticketid is assigned automatically as 1+maxticketid if enqueueing is possible
// does not enqueue and returns false if either parameter is empty string
// POST:  new ticket with supplied parameters is added to back of tickets,
//        maxticketid is incremented
// PARAM: customer and complaint fields to pass  to Ticket constructor
bool CCQueue::Add(string customer, string complaint)
{
    if(customer=="" || complaint=="")
        return false;
    else
    {
        maxticketid++;
        unsigned int num = maxticketid;
        Ticket A(num, customer, complaint);
        this->tickets.InsertBack(A);
        return true;
    }
}

// removes and returns an item from the front of the ticket queue
// throws a logic_error if the ticket queue is empty
// POST:  first item of the ticket queue is removed
Ticket CCQueue::Service()
{

    if(this->tickets.IsEmpty())
    {
        throw logic_error("ticket is empty");

    }
    else
    {

//this->tickets.RemoveAt(0);
        return this->tickets.RemoveAt(0);

    }


}

// moves an item towards the front of the queue by 1 position and returns true
// returns false if supplied index is 0 (first item) or outside the list boundaries
// POST:  DLinkedList items at position and position-1 swap spots in the list
// PARAM: initial index of item to move up
bool CCQueue::MoveUp(int index)
{
    if(index == 0 || index >= this->tickets.Size())
        return false;
    else
    {
        if(index == 1)  //if the ticket is on the second position of the list
        {
            Node<Ticket>* copyOfticketOnIndex  = new Node<Ticket>(this->tickets.ElementAt(1)); //copy the ticket on that position
            this->tickets.InsertFront(copyOfticketOnIndex->data);   //insert it at the front
            this->tickets.RemoveAt(2);//delete the one on third position which is the one we copied from

        return true;
        }
        else
        {
//            if the ticket is in the middle of the list


            Node<Ticket>* copyOfticketOnIndex = new Node<Ticket>(this->tickets.ElementAt(index)); //copy the ticket on that position
            this->tickets.InsertAt(copyOfticketOnIndex->data,index-1);//insert it at the position which is two position ahead of the index
            this->tickets.RemoveAt(index+1);//after the insertion, delete the original one

            return true;


        }
    }
}

// moves an item towards the back of the queue by 1 position and returns true
// returns false if supplied index is the last item or outside the list boundaries
// POST:  DLinkedList items at position and position+1 swap spots in the list
// PARAM: initial index of item to move down
bool CCQueue::MoveDown(int index)
{


    if(index == this->tickets.Size()-1 || index>maxticketid)//check whether the position of this item is on the last position
        return false;
    else
    {
        if(index == this->tickets.Size()-2) //if the position of the ticket is on the second last position of the list
        {
            Node<Ticket>* copyOfticketOnIndex = new Node<Ticket> (this->tickets.ElementAt(index));//copy the one on that index
            this->tickets.InsertBack(copyOfticketOnIndex->data);//insert it at the back;
            this->tickets.RemoveAt(index);//delete the one on the original position because the index was not incremented
        }
        else
        {
            // if the position of the ticket is in the middle of the list
            Node<Ticket>* copyOfticketOnIndex = new Node<Ticket> (this->tickets.ElementAt(index));//copy the one on that index
            this->tickets.InsertAt(copyOfticketOnIndex->data,index+2);//insert it at the position which is one more position behind it
            this->tickets.RemoveAt(index);//delete the one on the original position because the index was not incremented

        }
    }


}

// ACCESSORS

// returns the number of tickets
/////////////////////////////////////////////////////////////////////////////////////////////
int CCQueue::Size() const
{
    return  this->tickets.Size();

}
//////////////////////////////////////////////////////////////////////////////////////////////
// returns a formatted string with the ticket queue contents
// You may use this function to check the contents of your queue
// You do not need to copy this into your .cpp file
