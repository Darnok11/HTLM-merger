#include <iostream>
#include "linkedListIterator.h"
using namespace std;

template<class Type>
class tagTypeList {
public:
   const tagTypeList<Type>& operator=(const tagTypeList<Type>&);
   void initializeList(); //init to empty state
   bool isEmpty() const;
   void print() const; //output data contained in each node
   int length() const; //return number of nodes in a list
   void removeList(); //remove all nodes from a list
   Type front() const; //return first ele from a list
   Type back() const; //return last ele from a list

   virtual bool search(const Type& searchItem) const = 0; //does ele is in the list. if yes return true
   virtual void insertFirst(const Type& newItem) = 0; //insert newItem at the beginning of the list
   virtual void insertLast(const Type& newItem) = 0; //insert newItem at the end of the list
   virtual void deleteNode(const Type& deleteItem) = 0; //delete deleteItem from the list.
   linkedListIterator<Type> begin(); //return iterator at the begging of the linked list
   linkedListIterator<Type> end(); //return iterator at the end of the linked list
   tagTypeList(); //default constructor
   tagTypeList(const tagTypeList<Type>& otherList); //copy constructor
   ~tagTypeList(); //destructor
protected:
   int count; //number of ele in the list
   nodeType<Type> *first; //pointer to first ele in the list
   nodeType<Type> *last; //pointer to last ele in the list
private:
   void copyList(const tagTypeList<Type>& otherList); //copy of other list
};
/**************************************************/
template<class Type>
bool tagTypeList<Type>::isEmpty() const {
   return (first == NULL);
}
/**************************************************/
// constructor
template<class Type>
tagTypeList<Type>::tagTypeList(){
   first = NULL;
   last = NULL;
   count = 0;
   //first = last = count = 0;
}
/**************************************************/
// destructor
template<class Type>
tagTypeList<Type>::~tagTypeList(){
   removeList(); //simply
}
/**************************************************/
template<class Type>
void tagTypeList<Type>::removeList(){
   nodeType<Type> *tmp;
   while (tmp != NULL) {
      tmp = first;
      first = first->link;
      delete tmp;
   }

   last = NULL;
   count = 0;
}
/**************************************************/
//print the data contained in each node
template<class Type>
void tagTypeList<Type>::print() const {
   nodeType<Type> *current;

   current = first;
   while (current != NULL) {
      std::cout << "data in the node: " << current->info << '\n';
      current = current->link;
   }
} //end print
/**************************************************/
//initializes the list to an empty state
template<class Type>
void tagTypeList<Type>::initializeList(){
   removeList(); //simply
}
/**************************************************/
//how many nodes are in the list?
template<class Type>
int tagTypeList<Type>::length() const {
   return count;
}
/**************************************************/
//returns the info contained in the first node
template<class Type>
Type tagTypeList<Type>::front() const {
   //precondition: list can not be empty
   assert(!isEmpty());
   return first->info;
}//end front
/**************************************************/
template<class Type>
Type tagTypeList<Type>::back() const {
   //precondition: list can not be empty
   assert(!isEmpty());
   return last->info;
} //end back
/**************************************************/
//returns an iterator to the first node
template<class Type>
linkedListIterator<Type> tagTypeList<Type>::begin(){
   linkedListIterator<Type> tmp(first);//constructor with parameter! - current = ptr
   return tmp;
}
/**************************************************/
//returns an iterator to the last node
template<class Type>
linkedListIterator<Type> tagTypeList<Type>::end(){
   linkedListIterator<Type> tmp(NULL);//constructor with parameter! - current = ptr
   return tmp;
}
/**************************************************/



//COPY LIST
/**************************************************/
template <class Type>
void tagTypeList<Type>::copyList(const tagTypeList<Type>& otherList){
   nodeType<Type> *newNode; //pointer to create a node
   nodeType<Type> *current; //pointer to traverse the list
   if (first != NULL){ //if the list is nonempty, make it empty
      removeList();
   }

   if (otherList.first == NULL){ //otherList is empty
      first = NULL;
      last = NULL;
      count = 0;
   } else {
      current = otherList.first;
      count = otherList.count;
      first = new nodeType<Type>;  //create the node
      first->info = current->info; //copy the info
      first->link = NULL; //set the link field of the node to NULL
      last = first;   //make last point to the first node
      current = current->link; //make current point to the next
      // node

      //copy the remaining list
      while (current != NULL){
         newNode = new nodeType<Type>;  //create a node
         newNode->info = current->info; //copy the info
         newNode->link = NULL; //set the link of newNode to NULL
         last->link = newNode; //attach newNode after last
         last = newNode; //make last point to the actual last
         //node
         current = current->link; //make current point to the
         //next node
      }//end while
   } //end else
}//end copy
/**************************************************/
template <class Type>
tagTypeList<Type>::tagTypeList(const tagTypeList<Type>& otherList){ //copy constructor
   first = NULL;
   copyList(otherList);
}
/**************************************************/
// overload the assignment operator
template <class Type>
const tagTypeList<Type>& tagTypeList<Type>::operator=(const tagTypeList<Type>& otherList){
   if (this != &otherList){ //avoid self-copy
      copyList(otherList);
   }
   //end else
   return *this;
}
/**************************************************/

// int main(){
//    std::cout << "program ready" << '\n';
//    return 0;
// }
