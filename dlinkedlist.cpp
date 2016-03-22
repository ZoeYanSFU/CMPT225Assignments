// File:        dlinkedlist.cpp
// Author:      Meihui Yan & Jiameng Duan
// Date:        January 31, 2016
// Description: Definition of a customer complaint queue class for CMPT 225 assignment 2
#include <iostream>
#include <stdexcept>
using namespace std;

#ifdef _DLINKEDLIST_H_

// helper function for deep copy
// Used by copy constructor and operator=
template <class T>
void DLinkedList<T>::CopyList(const DLinkedList<T>& ll)
{
    Node<T>* ptrOne = nullptr;
    Node<T>* ptrTwo = nullptr;
    Node<T>* copyNode = nullptr;
    if (ll.IsEmpty())
        std::cout<<"the parameter is an empty linkedlist"<<endl;
    else
    {
        front = new Node<T>(*(ll.front));
        front->data = ll.front->data;
        front->prev = ll.front->prev;
        front->next = ll.front->next;

        ptrOne = front;

        ptrTwo = ll.front->next;

        while(ptrTwo)
        {
            Node<T>*A = new Node<T>(ptrTwo->data);
            ptrOne->next = A;
            A->prev = ptrOne;
            A->next = nullptr;
            ptrTwo = ptrTwo->next;
            ptrOne = ptrOne->next;
        }
        ptrOne->next = nullptr;
        back = ptrOne;
        size = ll.size;
    }
}

 // helper function for deep delete
// Used by destructor and copy/assignment
template <class T>
void DLinkedList<T>::DeleteList()
{
    if(IsEmpty())
    {
        std::cout<<"there is nothing in this list"<<endl;
    }
    else
    {
        Node<T>* temp ;
        Node<T>* deleted;
        temp = front;
        deleted = front;
        while(temp != nullptr)
        {
            deleted = temp;
            temp = temp->next;
            delete deleted;
        }
        size = 0;
    }


}

//default constructor
template <class T>
DLinkedList<T>::DLinkedList()
{
    size = 0;
    front = nullptr;
    back = nullptr;
}
 // copy constructor, performs deep copy of list elements
template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T> & ll)
{
    CopyList(ll);
}

 // destructor
template <class T>
DLinkedList<T>::~DLinkedList()
{
    DeleteList();
}

// Inserts an item at the front of the list
// POST:  List contains item at position 0
// PARAM: item = item to be inserted
template <class T>
void DLinkedList<T>::InsertFront(T item)
{
    if(this->IsEmpty())//if the list is empty , front will also be back after the insertion
    {
        Node<T>* newFront;
        newFront = new Node<T>(item);
        newFront->data = item;
        front = newFront;
        back = front;
        size++;
    }
    else
    {
        Node<T>* newFront = new Node<T>(item);
        newFront->data = item;
        newFront->next = front;
        newFront->prev = nullptr;
        front = newFront;
        size++;
    }
}

// Inserts an item at the back of the list
// POST:  List contains item at back
// PARAM: item = item to be inserted
template <class T>
void DLinkedList<T>::InsertBack(T item)
{
      if(this->IsEmpty())   //if the list is empty , front will also be back after the insertion
    {
        Node<T>* newFront = new Node<T>(item);
        back = newFront;
        front = back;
        size++;
    }
    else
    {
        Node<T>* newBack = new Node<T>(item);
        back->next = newBack;
        newBack->next = nullptr;
        newBack->prev = back;
        back = newBack;
        size++;
    }
}

// Inserts an item in position p (0-indexed)
// Throws exception for invalid index
// PRE:   0 <= p <= size
// POST:  List contains item at position p
// PARAM: item = item to be inserted, p = position where item will be inserted
template <class T>
void DLinkedList<T>::InsertAt(T item, int p)
{

        if(p>size || p<0 || IsEmpty())
        {
			throw out_of_range("empty or position larger than size or position is less than zero");
        }
        else if(p == 0)     //insert at the front
            InsertFront(item);
        else if(p == size)  //insert at the back
            InsertBack(item);  // insert at other positions
        else
        {
            Node<T>* temp = new Node<T>(front->data);
            temp = front;
            for(int i = 0; i < p-1; i++)   //let temp points to position p.
                temp = temp->next;
            Node<T>* newNode = new Node<T>(item);  //create new node to relink
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
            size++;
        }





}


// Removes and returns an item from position p (0-indexed)
// Throws exception if list is empty or index invalid
// PRE:   0 <= p < size
// POST:  Item is removed from list
// PARAM: p = position from where item will be removed
template <class T>
T DLinkedList<T>::RemoveAt(int p)
{

    //only one node
    //remove front
    //remove last
    //position is in the middle
  
    if(p>size || p<0 ||IsEmpty())
    {
        throw out_of_range("empty or position larger than size or position is less than zero");
    }
    else
    {
        if(size == 1 && p==0)   //remove the front
        {
            Node<T>* deleted= new Node<T>(front->data);
            T Data = front->data;
            deleted = front;
            front = nullptr;
            back = nullptr;
			delete deleted;
            size--;
            return Data;

        }
        else if(p==0)        //remove the front
        {
            Node<T>* deleted= front;
            T Data = front->data;
            front = front->next;
			front->prev = nullptr;
            size--;
            delete deleted;
            return Data;
        }
        else if (p == size-1)   //remove the back
        {
           Node<T>* deleted= back;
           T Data = back->data;
           back = back -> prev;
		   back->next = nullptr;
           size--;
           delete deleted;
           return Data;
        }
        else
        {
            Node<T>* deleted= front;
            Node<T>* temp= front;
            int i = 0;
            while(i!=p)
            {
                temp = temp -> next;
                i++;
            }
            deleted = temp;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            T Data = temp->data;
            size--;
            delete deleted;
            return Data;

        }



    }
}

// Removes duplicates from the list, preserving existing order of remaining items.
// The first occurrence of any duplicate (relative to the front of the list)
//   is the one which remains.
// We have not yet learned about efficiency so you may implement this in any way
//   as long as the resulting list satisfies the requirement above.
// PRE:
// POST:  List contains no duplicates, front and back point to the appropriate nodes
// PARAM:
template <class T>
void DLinkedList<T>::RemoveDuplicates()
{
    if(this->IsEmpty()||this->size == 1)
    {
        cout<<"this list contains either 1 or nothing"<<endl;
    }
    else  //assuming this following code will work on the case that the list contains at least two nodes
    {

        Node<T>* hold = new Node<T>(this->front->data);  //
        Node<T>* itr = new Node<T>(this->front->data);//iterate through the rest list to compare with hold
        int holdPos = 0; //the position of hold
        int itrPos = 1;  //position of itr
        hold = front;
        while (hold != nullptr)
        {
            itr = hold->next;
            while(itr != nullptr)
            {

                if (itr->data == hold->data)  //if we find duplicate as the hold
                {
                    itr = itr->next;   //move to the next ptr first
                    this->RemoveAt(itrPos); //remove the current one
                }
                else      //no match, keep iterating
                 {
                     itr = itr->next;
                     itrPos++;
                 }

            }
            hold = hold->next;  //
            holdPos++;
            itrPos= holdPos+1;
        }
    {

    }
    }

}

// Returns size of list
template <class T>
int DLinkedList<T>::Size() const
{
    return size;
}

// Returns whether the list is empty
template <class T>
bool DLinkedList<T>::IsEmpty() const
{
    if (front == nullptr)
        return true;
    else
        return false;
}

// Returns existence of item
template <class T>
bool DLinkedList<T>::Contains(T item) const
{
    if(IsEmpty())
    {
        return false;
    }
    else
    {
         Node<T>* temp = new Node<T>(item);
         temp = front;
         while(temp != nullptr)
         {
             if(temp->data == item)
                return true;
             else
                temp = temp->next;
         }
         return false;
    }


}

// Returns item at index (0-indexed)
// Throws exception for invalid index
template <class T>
T DLinkedList<T>::ElementAt(int p) const
{


    if(p>size || p<0 ||IsEmpty())
    {
        throw p;
    }
    else
    {
         Node<T>* temp;
         temp = front;
         for(int i = 0; i < p; i++)   //let temp points to position p.
            temp = temp->next;
         return temp->data;
    }

}

// overloaded assignment operator
// must work in the following cases:
// list2 = list1 -> general case
// list2 = list2 -> should do nothing
template <class T>
DLinkedList<T>& DLinkedList<T>::operator=(const DLinkedList<T>& ll)
{
    if(this == &ll)
    {
        std::cout<<"you cannot copy yourself"<<endl;
    }
    else
    {
        DeleteList();
        CopyList(ll);
    }
    return *this;
//return some value

}


#endif
//template class DLinkedList<Ticket>;
//template class DLinkedList<int>;
//template class Node<Ticket>;
