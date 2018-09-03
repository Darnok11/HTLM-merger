#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

/**************************************************/
// Definition of the node. Prepared for second version of program
template<class T>
struct Tag {
   tagType info;
   Tag<T> *link;
};
/**************************************************/

class tagType {
private:
   string name;
   std::vector<string> attr; //atributes of tag
   std::vector<string> ids;
   std::vector<string> cotent; //content
public:
   void printAttr();
   void printIds();
   void printContent();
}

void tagType::printAttr(){
   int index = 0;
   cout << endl;
   cout << "-----words-----" << endl;
   for(auto const &value: attr) {
      cout << index << ": "<< value.name << endl;
      cout << "----------" << endl;
      index++;
   }
   cout << endl;
}

void tagType::printIds(){
   int index = 0;
   cout << endl;
   cout << "-----words-----" << endl;
   for(auto const &value: attr) {
      cout << index << ": "<< value.name << endl;
      cout << "----------" << endl;
      index++;
   }
   cout << endl;
}

void tagType::printContent(){
   int index = 0;
   cout << endl;
   cout << "-----words-----" << endl;
   for(auto const &value: attr) {
      cout << index << ": "<< value.name << endl;
      cout << "----------" << endl;
      index++;
   }
   cout << endl;
}

int main(){
   return 0;
}
