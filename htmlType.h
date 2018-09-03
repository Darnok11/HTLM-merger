/********************************************
* htmlType object to store html
* TODO: Structure as linked link list for graph (DOM)
*********************************************/

// #include <iostream>
// #include <vector>
// #include <string.h>
// #include "utf8/source/utf8.h"

using namespace std;

class htmlType {
private:
   vector<string> tags;
   vector<string> end_tags;
   vector<string> unique_tags;
   vector<string> ids;
   vector<string> attr_val;
   vector<string> attr;
   vector<string> void_tags;
   vector<string> start_tags;
   vector<string> content;

public:

   std::vector<string> getContent();
   std::vector<string> getStartTags();
   std::vector<string> getVoidTags();
   std::vector<string> getAttr();
   std::vector<string> getAttrVal();

   std::string convertToUTF8(string &word);

   bool isTag(string word);
   bool isStartTag(string word);
   bool isAttr(string word);
   bool isVoidTag(string word);
   bool isEndTag(string word);
   bool isUniqueTag(string word);
   //precondition: global flags are declared!!
   void insertTag(string word);
   void insertStartTag(string word);
   void insertEndTag(string word);
   void insertAttr(string word);
   void insertAttrVal(string word);
   void insertVoidTag(string word);
   void insertUniqueTag(string word);
   void insertContent(string word);

   void printTags();
   void printEndTags();
   void printAttr();
   void printVoidTags();
   void printUniqueTags();
   void printContent();

   int numberOfMatchingTags(string word);
   bool checkEndTag(string word);
   bool interpretWord(std::string word, int i); //main function
   //precondition: global flags and initial state must be declared
   bool interpretWords(vector<string> words);
   void error(int e, int i, string word); //e number of error to print out, i which word
};
//methods
/*********************************************/
std::vector<string> htmlType::getContent() {
   return content;
}
std::vector<string> htmlType::getStartTags() {
   return start_tags;
}
std::vector<string> htmlType::getVoidTags() {
   return void_tags;
}
std::vector<string> htmlType::getAttr() {
   return attr;
}
std::vector<string> htmlType::getAttrVal() {
   return attr_val;
}
/*********************************************/
std::string htmlType::convertToUTF8(std::string &str) {
 //The function will replace any invalid UTF-8 sequence with a Unicode replacement character
   std::string temp;
   utf8::replace_invalid(str.begin(), str.end(), back_inserter(temp));
   str = temp;
   return str;
}
/*********************************************/
void htmlType::insertTag(string word) {
   tags.push_back(word);
}
void htmlType::insertStartTag(string word) {
   start_tags.push_back(word);
}
void htmlType::insertEndTag(string word) {
   end_tags.push_back(word);
}
void htmlType::insertAttr(string word) {
   attr.push_back(word);
}
void htmlType::insertAttrVal(string word) {
   attr_val.push_back(word);
}
void htmlType::insertVoidTag(string word) {
   void_tags.push_back(word);
}
void htmlType::insertUniqueTag(string word) {
   unique_tags.push_back(word);
}
void htmlType::insertContent(string word) {
   string tmp = convertToUTF8(word); //TODO
   content.push_back(tmp);
}
/*********************************************/
void htmlType::printTags(){
   int index = 0;
   cout << endl;
   cout << "-----tags-----" << endl;
   for(auto const &tag: tags) {
      cout << index << ": "<< tag << endl;
      cout << "----------" << endl;
      index++;
   }
   cout << endl;
}
/*********************************************/
void htmlType::printContent(){
   int index = 0;
   cout << endl;
   cout << "-----content-----" << endl;
   for(auto const &value: content) {
      cout << index << ": "<< value << endl;
      cout << "----------" << endl;
      index++;
   }
   cout << endl;
}
/*********************************************/
void htmlType::printEndTags(){
   int index = 0;
   cout << endl;
   cout << "-----end_tags-----" << endl;
   for(auto const &value: end_tags) {
      cout << index << ": "<< value << endl;
      cout << "----------" << endl;
      index++;
   }
   cout << endl;
}
/*********************************************/
void htmlType::printVoidTags(){
   int index = 0;
   cout << endl;
   cout << "-----void_tags-----" << endl;
   for(auto const &value: void_tags) {
      cout << index << ": "<< value << endl;
      cout << "----------" << endl;
      index++;
   }
   cout << endl;
}
/*********************************************/
void htmlType::printUniqueTags(){
   int index = 0;
   cout << endl;
   cout << "-----unique_tags-----" << endl;
   for(auto const &value: unique_tags) {
      cout << index << ": "<< value << endl;
      cout << "----------" << endl;
      index++;
   }
   cout << endl;
}
/*********************************************/
void htmlType::printAttr(){
   int index = 0;
   cout << endl;
   cout << "------------------attributes" << endl;
   for(auto const &value: attr) {
      cout << index << ": "<< value << endl;
      cout << "----------" << endl;
      index++;
   }
   cout << endl;
}
/*********************************************/
//how many tags
int htmlType::numberOfMatchingTags(string word) {
   int i = 0;
   for (auto const &tag: tags ) {
      if (word == tag) {
         i++;
      }
   }
   return i;
}
/*********************************************/
bool htmlType::isTag(string word){
   for (auto const &tag : TAGS ) {
      if (word == tag) {
         return true;
      }
   }
   return false;
}
/*********************************************/
bool htmlType::isEndTag(string word){
   //serach trough start tags and chack odd number
   if (numberOfMatchingTags(word) % 2) {//if odd
      return 1;
   }
   return 0;
}
/*********************************************/
bool htmlType::isAttr(string word){
   //ATTRIBUTES are global atributes
   for (auto const &attr : ATTRIBUTES ) {
      if (word == attr) {
         return true;
      }
   }
   return false;
}
/*********************************************/
bool htmlType::isVoidTag(string word){
   //attrs are global atributes
   for (auto const &tag : VOID_TAGS ) {
      if (word == tag) {
         return true;
      }
   }
   return false;
}
/*********************************************/
bool htmlType::isUniqueTag(string word){
   //attrs are global atributes
   for (auto const &tag : UNIQUE_TAGS ) {
      if (word == tag) {
         return true;
      }
   }
   return false;
}
/*********************************************/
vector<string> errors = {
      "In comment there can not be <!--.", //0
      "Program require closing end tag '>'. ", //1
      "This is not end tag.", //2
      "Void or start tag is required.", //3
      "Program required closing start tag '>' .", //4
      "Program required closing void tag '/>'.", //5
      "Wrong word in start tag. Check if attribute values are separated with =' attr ' delimiters." //6
};
void htmlType::error(int e, int i, string word){
   cout << "ERROR" << endl;
   // cout << errors[e] << "\nword: " << i << endl;
   cout << e << ": " <<  errors[e] << " For " << i << " word: " << word << endl;
   exit(1);
}
/*********************************************/
bool htmlType::interpretWords(vector<string> words){
   int i = 0; //to tell which word in file
   for (auto &word : words) {
      if (!interpretWord(word, i)) {
         return 0;
      }
      i++;
   }
   return 1;
}
/*********************************************/
#include "interpretWord.h"
