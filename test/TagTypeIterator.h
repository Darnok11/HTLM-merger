#include <iostream>
#include <string>
#include <vector>

using namespace std;
/**************************************************/
// Definition of the node
template<class Type>
struct nodeType {
   Type info; //here are attr and other information about tag
   nodeType<Type> *link;
};
/**************************************************/
template<class Type>
class tagTypeIterator {
public:
   //constructor, destructor
   tagTypeIterator(); //constructor
   tagTypeIterator(nodeType<Type> *ptr); //constructor with parameter current = ptr
   ~tagTypeIterator(); //destructor
   //operators
   Type operator*(); //overload operator * it returs the info contained in the node
   tagTypeIterator<Type> operator++(); //overload operator ++ is changed to the next node.
   bool operator==(const tagTypeIterator<Type>& right) const; //overload operator == | Returns true if equal iterators
   bool operator!=(const tagTypeIterator<Type>& right) const; //overload operator != | Returns true if not equal iterators

private:
   nodeType<Type> *current; //poiter for current node in the linked list
};
/**************************************************/
template<class Type>
tagTypeIterator<Type>::tagTypeIterator(){
   current = NULL;
}
/**************************************************/
template<class Type>
tagTypeIterator<Type>::tagTypeIterator(nodeType<Type> *ptr){
   current = ptr;
}
/**************************************************/
template<class Type>
tagTypeIterator<Type>::~tagTypeIterator(){
   delete current;
}
/**************************************************/
template <class Type>
tagTypeIterator<Type> tagTypeIterator<Type>::operator++(){
   current = current->link;
   return *this;
}
/**************************************************/
template <class Type>
bool tagTypeIterator<Type>::operator==(const tagTypeIterator<Type>& right) const {
   return (current == right.current);
}
/**************************************************/
template <class Type>
bool tagTypeIterator<Type>::operator!=(const tagTypeIterator<Type>& right) const {
   return (current != right.current);
}
/**************************************************/
// int main(){
//    std::cout << "program ready" << '\n';
//    //create iterator of int Type
//    return 0;
// }
