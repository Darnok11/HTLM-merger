#include <iostream>
#include "linkedList.h"
using namespace std;

template<class Type>
class unorderedLinkedList: public linkedListType<Type>{ //taken from linked list
public:
   bool search(const Type& item) const; //determine if search item is in the list
   void insertFirst(const Type& item); //insert new item on the beginning of the list
   void insertLast(const Type& item); //insert new item on the end of the list
   void removeNode(const Type& item); //fn to delete item from the list
private:
};
/*********************************************************/
template<class Type>
bool unorderedLinkedList<Type>::search(const Type& item) const {
   nodeType<Type> *current;//pointer to traverse the list
   bool found = false;

   current = first;
   while (current != NULL && !found){ //search the list
      if (current->info == searchItem){ //searchItem is found
         found = true;
      } else {
         current = current->link;
      }
   }
   return found;
}//end search
/*********************************************************/
template<class Type>
void unorderedLinkedList<Type>::insertFirst(const Type& item){
   nodeType<Type> *tmp;
   tmp = new nodeType<Type>;
   tmp->info = item;
   tmp->link = first; //insert before first
   first = tmp;
   count++;

   if (last == NULL) {//
      last = tmp;
   }
}
/*********************************************************/
template<class Type>
void unorderedLinkedList<Type>::insertLast(const Type& item){
   nodeType<Type> *tmp;
   tmp = new nodeType<Type>;
   tmp->info = item;
   tmp->link = NULL;

   if (first == NULL) {
      first = tmp;
      last = tmp;
   }  else {
      last->link = item; //insert item after last
      last = item;

      count++;
   }

}
/*********************************************************/
template <class Type>
void unorderedLinkedList<Type>::deleteNode(const Type& item){
   nodeType<Type> *current; //pointer to traverse the list
   nodeType<Type> *trailCurrent; //pointer just before current
   bool found;

   if(first == NULL){ //Case 1; the list is empty.
      cout << "Cannot delete from an empty list." << "\n";
   } else {
      if(first->info == item){ //Case 2
         current = first;
         first = first->link;
         count--;
         if (first == NULL){ //the list has only one node
            last = NULL;
            delete current;
         } else {///search the list for the node with the given info
         found = false;
         trailCurrent = first;  //set trailCurrent to point
         //to the first node
         current = first->link; //set current to point to
         //the second node
            while (current != NULL && !found){
               if (current->info != item){
                  trailCurrent = current;
                  current = current-> link;
               } else {
                  found = true;
               }
            }//end while
         }
      }
      if (found){ //Case 3; if found, delete the node
         trailCurrent->link = current->link;
         count--;
         if(last == current){ //node to be deleted was the
            //last node
            last = trailCurrent; //update the value of last
            delete current;  //delete the node from the list
         } else {
         cout << "The item to be deleted is not in the list" << "\n";
         }
      }
   }//end else
} //end deleteNode
/*********************************************************/
int main(){
   return 0;
}
