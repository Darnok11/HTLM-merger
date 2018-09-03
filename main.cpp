
/********************************************
* subject: ECOTE
* author:  Konrad Grzyb
* nr:      227305
* date:    6.11.2018
*********************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <list>

using namespace std;

#include "GLOBAL_VARIABLES.h"
#include "utf8/source/utf8.h"
#include "htmlType.h"



/********************************************
* function declaration
*********************************************/
int sizeOfFile(fstream *file);
bool ifEqual(fstream *file1, fstream *file2);
void checkEndOfFile(fstream *file);
bool isEndOfFile(fstream *file);
void checkSize(fstream *file);
void printVector(vector<string> v);
vector<string> split(string s, string delim); //precondition: using isDelimiter function
bool valid_utf8_file(const char* file_name);
vector<string> splitWords(vector<string> words, string delim); //
bool isDelimiter(string word); //precondition: DELIMITERS as global variable must be declared
std::vector<string> storeHTML(const char* path);
void createHTML(htmlType *html1, htmlType *html2);
void compare(std::vector<string> v1, std::vector<string> v2, ofstream *HTML);


/********************************************
** MAIN
*********************************************/
int main(int argc, char const *argv[]) {
   htmlType html1, html2;
   vector<string> html1_words, html2_words;

   // store files
   const char* file_path_1 = argv[1];
   const char* file_path_2 = argv[2];

   //create objects from files
   html1_words = storeHTML(file_path_1);
   html2_words = storeHTML(file_path_2);

   if (html1.interpretWords(html1_words)) {
      if (html2.interpretWords(html2_words)) {
         //create output file index.html
         createHTML(&html1, &html2);
      }
   }
   return 0;
} //end main

/********************************************
* functions definitions
*********************************************/
int sizeOfFile(fstream *file){
   int size;
   file->seekg(0, ios::end);
   size = file->tellg();
   file->seekg(0, ios::beg);
   return size;
}
/*********************************************/

void checkSize(fstream *file){
   if (sizeOfFile(file) > 1024) {
      std::cout << "File is too big." << '\n';
      exit(1);
   }
}
/*********************************************/

void printVector(vector<string> v){
   int index = 0;
   cout << endl;
   cout << "-----words-----" << endl;
   for(auto const &value: v) {
      cout << index << ": "<< value << endl;
      cout << "----------" << endl;
      index++;
   }
   cout << endl;
   index = 0;
}
/*********************************************/

void clearState(fstream *file){
   std::cout << "Reseting the file state." << '\n';
   file->clear();
}
/*********************************************/

bool isEndOfFile(fstream *file){
   return (file->rdstate() ^ ifstream::eofbit) == 0;
}
/*********************************************/
void checkEndOfFile(fstream *file){
   if (isEndOfFile(file)) {
      std::cout << "this is EOF." << '\n';
      clearState(file);
   } else {
      std::cout << "this is not EOF. There is white character after?" << '\n';
   }
}
/*********************************************/

std::vector<std::string> split(std::string stringToBeSplitted, std::string delimeter) {
   std::vector<std::string> splittedString;
   int startIndex = 0;
   int  endIndex = 0;
   if (!isDelimiter(stringToBeSplitted)) {
      //do not split delimiters like <!-- on < !-- by <
      while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() ) {
         std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
         if (!val.empty()) {
            splittedString.push_back(val);
         }
         //push also delimiter
         splittedString.push_back(delimeter);
         startIndex = endIndex + delimeter.size();
      }
      if(startIndex < stringToBeSplitted.size()) {
         std::string val = stringToBeSplitted.substr(startIndex);
         if (!val.empty()) {
            splittedString.push_back(val);
         }
      }
      return splittedString;
   }
   splittedString.push_back(stringToBeSplitted);
   return splittedString;
}
/*********************************************/

bool isDelimiter(string word) {
   //check if word is delimiter
   for( auto const &delim : DELIMITERS ) {
      if (word == delim) {
         return true;
      }
   }
   return false;
}
/*********************************************/

vector<string> splitWords(vector<string> words, string delim) {
   vector<string> splited_word, vector_of_words;

   for (auto &word : words) {
      splited_word = split(word, delim);
      vector_of_words.insert(vector_of_words.end(), splited_word.begin(), splited_word.end());
   }
   return vector_of_words;
}
/*********************************************/

bool valid_utf8_file(const char* file_name) {
   ifstream ifs(file_name);
   if (!ifs)
   return false; // even better, throw here

   istreambuf_iterator<char> it(ifs.rdbuf());
   istreambuf_iterator<char> eos;

   return utf8::is_valid(it, eos);
}

/*********************************************/

std::vector<string> storeHTML(const char* path) {
   vector<string> words, html, tmp, v0, v1, v2, v3, v4, v5, v6, v7;
   string word;
   //if html is open
   fstream HTML(path, ios::in | ios::out | ios::binary);
   if (!HTML.is_open() ) {
      cout << "Could not open HTML: " << path << endl;
      exit(1);
   }
   //check if file is to big
   checkSize(&HTML);
   //deviding on words and storing in vector
   if(HTML.is_open()){
      while (HTML >> word) {
         html.push_back(word);
      }
      //close file
      HTML.close();
   }

   //TODO: RECURSION FOR splitWords

   tmp = splitWords(html, DELIMITERS[0]);
   v0.insert(v0.end(), tmp.begin(), tmp.end());

   tmp = splitWords(v0, DELIMITERS[1]);
   v1.insert(v1.end(), tmp.begin(), tmp.end());

   tmp = splitWords(v1, DELIMITERS[2]);
   v2.insert(v2.end(), tmp.begin(), tmp.end());

   tmp = splitWords(v2, DELIMITERS[3]);
   v3.insert(v3.end(), tmp.begin(), tmp.end());

   tmp = splitWords(v3, DELIMITERS[4]);
   v4.insert(v4.end(), tmp.begin(), tmp.end());

   tmp = splitWords(v4, DELIMITERS[5]);
   v5.insert(v5.end(), tmp.begin(), tmp.end());

   tmp = splitWords(v5, DELIMITERS[6]);
   v6.insert(v6.end(), tmp.begin(), tmp.end());

   tmp = splitWords(v6, DELIMITERS[7]);
   v7.insert(v7.end(), tmp.begin(), tmp.end());
   v7.push_back(""); //insert at the end null character to know that this is the end of file

   html.clear(); //copy v7 to html1 object
   html.insert(html.end(), v7.begin(), v7.end());
   return html;
}
/*********************************************/
//TODO: structure, delimiters
void createHTML(htmlType *html1, htmlType *html2) {
   std::vector<string> v1, v2;
   std::ofstream HTML("index.html");

   // start forming structure
   // elements are sorted with html1 order
   HTML << UNIQUE_STRUCTURE_START;
   HTML << "<h1> Repeated tags </h1>" << endl;
   v1 = html1->getStartTags();
   v2 = html2->getStartTags();
   compare(v1, v2, &HTML);
   v1.clear();
   v2.clear();

   HTML << "<h1> Repeated attributes </h1>" << endl;
   v1 = html1->getAttr();
   v2 = html2->getAttr();
   compare(v1, v2, &HTML);
   v1.clear();
   v2.clear();

   HTML << "<h1> Repeated content </h1>" << endl;
   v1 = html1->getContent();
   v2 = html2->getContent();
   compare(v1, v2, &HTML);
   v1.clear();
   v2.clear();
   // for (auto const &html1_attr : html1->getAttr()) {
   //    for (auto const &html2_attr : html2->getAttr()) {
   //       if (html1_attr == html2_attr) {
   //          HTML << html1_attr << endl;
   //       }
   //    }
   // }
   HTML << UNIQUE_STRUCTURE_END;
   HTML.close();
}
/*********************************************/
void compare(std::vector<string> v1, std::vector<string> v2, ofstream *HTML) {
   for (size_t i = 0; i < v1.size(); i++) {
      for (size_t j = 0; j < v2.size(); j++) {
         if (v1[i] == v2[j]) {
            *HTML << v1[i] << endl;
            i++; //do not multiply values
         }
      }
   }
}//end compare
/*********************************************/
