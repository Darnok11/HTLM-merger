#include <iostream>
using namespace std;
/**************************************************
An iterator is an object that produces each element of a container, such as a linked list, one element at a time.
**************************************************/
// Definition of the node
template<class Type>
struct nodeType {
   Type info;
   nodeType<Type> *link;
};
/**************************************************/
template<class Type>
class linkedListIterator {
public:
   //constructor, destructor
   linkedListIterator(); //constructor
   linkedListIterator(nodeType<Type> *ptr); //constructor with parameter current = ptr
   ~linkedListIterator(); //destructor
   //operators
   Type operator*(); //dereferencing operator returns the info of the current node
   linkedListIterator<Type> operator++(); //overload operator ++ is changed to the next node.
   bool operator==(const linkedListIterator<Type>& right) const; //overload operator == | Returns true if equal iterators
   bool operator!=(const linkedListIterator<Type>& right) const; //overload operator != | Returns true if not equal iterators

private:
   nodeType<Type> *current; //poiter for current node in the linked list
};
/**************************************************/
template<class Type>
linkedListIterator<Type>::linkedListIterator(){
   current = NULL;
}
/**************************************************/
template<class Type>
linkedListIterator<Type>::linkedListIterator(nodeType<Type> *ptr){
   current = ptr;
}
/**************************************************/
template<class Type>
linkedListIterator<Type>::~linkedListIterator(){
   delete current;
}
/**************************************************/
template<class Type>
Type linkedListIterator<Type>::operator* (){
   return current->info;
}
/**************************************************/
template <class Type>
linkedListIterator<Type> linkedListIterator<Type>::operator++ (){
   current = current->link;
   return *this;
}
/**************************************************/
template <class Type>
bool linkedListIterator<Type>::operator==(const linkedListIterator<Type>& right) const {
   return (current == right.current);
}
/**************************************************/
template <class Type>
bool linkedListIterator<Type>::operator!=(const linkedListIterator<Type>& right) const {
   return (current != right.current);
}
/**************************************************/
// int main(){
//    std::cout << "program ready" << '\n';
//    //create iterator of int Type
//    return 0;
// }
