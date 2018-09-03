/*********************************************************/
// Konrad Grzyb 227305
// graphs are inputed from the file where each row end by -999
/*********************************************************/

#include <iostream>
#include <fstream> //http://www.cplusplus.com/reference/fstream/ifstream/

#include "queue.h" //queue needed for BFS
// #include "linkedList.h"
#include "unorderedLinkedList.h"

using namespace std;

class graphType { //using adjacency list
public:
   bool isEmpty() const; //check if grpah is empty
   void createGraph(); //take graph from the file
   void removeGraph();
   void printGraph();
   bool checkRules(); //check if cell value apply to the rules
   void breadthFirstTraversal(); //vertices of the graph are checked using breadth first traversar
   void breadthFirstTraversal(); //vertices of the graph are checked using Iterative Deepening Search

   graphType(int size = 0); //constructor
   ~graphType(); //destructor
protected:
   int max; //max size of the graph
   int size; //current # of
   linkedListType<int> *graph;
private:
};
/*********************************************************/
bool graphType::isEmpty() const {
   return size == 0;
}
/*********************************************************/
void graphType::createGraph(){
   //prompt file name
   ifstream infile; //Input stream class to operate on files
   char fname[50];
   int v, av; //av

   if (size == 0) { //if the graph is not empty, make it empty
      removeGraph();
   }
   //store file name
   std::cout << "enter file name: " << '\n';
   std::cin >> fname;
   std::cout << '\n';

   //open file
   infile.open(fname);
   if (!infile) {
      std::cout << "can not open file :(" << '\n';
      return;
   }

   infile >> size;
   for (int i = 0; i < size; i++) {
      infile >> v;
      infile >> av;
      while (av != -999) { //store row
         graph[v].insertLast(av);
         infile >> av;
      }
   }
   infile.close();
}
/*********************************************************/
void graphType::removeGraph(){
   for (int i = 0; i < size; i++) {
      graph[i].removeList();
      size = 0;
   }
}
/*********************************************************/
void graphType::printGraph(){
   std::cout << "printing the graph: " << '\n';
   for (int i = 0; i < size; i++) {
      graph[i].print();
   }
   std::cout << '\n';
}
/*********************************************************/
// constructor
graphType::graphType(int x){
   max = x;
   size = 0;
   graph = new linkedListType<int>[x]; //error!!!
}
/*********************************************************/
// destructor
graphType::~graphType(){
   removeGraph();
}
/*********************************************************/
void graphType::breadthFirstTraversal(){
   queueType<int> queue;
   bool *visited;
   visited = new bool[size];
   for (int i = 0; i < size; i++){
      visited[i] = false;   //initialize the array visited to false
   }
   linkedListIterator<int> graphIt;

   for (int index = 0; index < size; index++){
      if (!visited[index]){
         queue.addQueue(index);
         visited[index] = true;
         cout << "index: " << index << '\n';

         while (!queue.isEmpty()){
            int u = queue.front();
            queue.deleteQueue();
            for (graphIt = graph[u].begin();
               graphIt != graph[u].end();
               ++graphIt){
               int w = *graphIt;
               if (!visited[w]){
                  queue.addQueue(w);
                  visited[w] = true;
                  cout << "w: " << w << "\n";
               }
            }

         } //end while
   }
   delete [] visited;
}//end breadthFirstTraversal


/*********************************************************/
int main(){
   std::cout << "program is ready" << '\n';
   return 0;
}
