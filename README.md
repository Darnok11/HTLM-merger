
`Semester: 7
Author: Konrad Grzyb
Subject: HTML Merger
Course: ECOTE - Compaling Technique`

## General overview and assumptions
Program is written in C++ and is about to merge 2 html files into one. Program may also be treated as strict HTML5 parser and c++ DOM (Document Object Model) builder.

1. Program storing html elements as C++ class objects and check errors comparing to proper objects. At this stage first algorithm is used.
2. After proper storing two "html" c++ objects program compering content, tag and attributes of objects and generate new file with listed repeated those elements.

## Functional requirements
*(with algorithms at design level, detailed syntax of an input language if appropriate, transformation rules if appropriate, etc.)*

### Detailed Syntax
W3C Recommendations from 3rd October 2017 (HTML 5.1 2nd Edition) under W3C Patent Policy from 5th February 2004 can derive important patterns for HTML 5.1 language.
The W3C Patent Policy governs the handling of patents in the process of producing Web standards.
As included in status of document: "this specification defines the 2nd edition of the 5th major version, first minor revision of the core language of the World Wide Web: the Hypertext Markup Language (HTML). In this version, a significant error with HTML 5.1 has been rectified, as noted in the Errata corrected section."
source: "https://www.w3.org/TR/html51/".

### Input language
Program parsing files HTML 5 defined by Standard Mode of document type declaration <!DOCTYPE html>. In any other case program will trigger semantic error. Program do not interpret xhtml and xml syntax i.e: "Content-type:application/xhtml+xml" in header will not work.
Program require using metadata of charset using UTF-8 characters encoding.

Program require elements (unique tags) in such order:
<!DOCTYPE html><html><head></head><body></body></html>

Not unique elements can occur just between <body> and </body> tags.

We can interpret html syntax by symbols: "<", ">", "/>", "<!--", "-->", "<!" which consists of several key components, including those called tags (opening and closing and their attributes), character-based data types, character references and entity references.
For example we have <a> tag which is called opening or start tag and require closing tag or end tag </a>. Some void elements or empty elements (those without content) are self closing tags <img />.

Attribute values, and content are not interpreted and at hence program is case-insensitive with respect to content and attribute values. Just UTF-8 charset is checked. However program is case-sensitive with respect to tags and attributes names which are adequate to the names from the vector of strings.

We can specify special characters as:
`< `- character that opening start tag - OT
`</` - character that opening end tag - OET
`>` - character that closing start or end tag we will call closing tag character - CT
`/>` - character that closing void (empty) tag - CVT
`<!--` - open comment - OC
`-->` - closing comment - CC
`", '` - delimiters that storing attribute values (strings) - AV
`= ` - character included in start tag outside AV that opening attribute value - OAV

By this properties we can expect certain situations on which we can set flags in our program and expect particular states before element:
- after OT or OET there must be tag.
- after tag or attribute there can not be tag.
- after tag there can occur just only attribute, CT or CVT.
- after CT or CVT there occur content (comments), OT or OCT.
- inside start tag there can not be content.
- tags must be paired in particular order: there can not be unpaired (odd) closing tag between paired tags i.e. for a: <a><p><div></div></a></p>.

At hence we can say that:
- attributes and tags are always specified in the start tag
- content is outside tags and is not interpreted
- attribute's values must be separated with delimiter `='value'`.

# Implementation
## General architecture
Program parsing and storing object (by given names in "console" arguments) that contains tag and attributes names, attributes values and content.
Program checking if input file is to big, and while storing content checking UTF-8 syntax.
After lexical analysis words are stored in vector string. At the end null character is inserted as a mark of end of the file.
When lexical analysis is performed a file state is checked, action is performed and state is changed.

Tags and attributes names are compared with those specified in the list and semantic is checked (semantic analysis). User can specify some of properties of html elements in the list i.e. lowercasing or uppercasing of attributes and tags names i.e.: for `data-*`. Some of properties are non editable and stay private like specification of parents for "html" element or closing tag for void element `br`.

Everything between start tag and end tag is a content which is not parsed including comments (just two` <!--` symbols can't occur), `javascript` syntax in case of <script> element, cascade `styleshit` syntax in case of `<style>` element etc.
PROGRAM DO NOT STORE COMMENTS.

We can see that there are 4 different environments in which program acting differently. It is content space which include comment space, start tag space, void tag space and end tag space. Program by optimisation performing interpretation of words occurring in those environments in order of lightest to heaviest calculations: content -> end tag -> void tag -> start tag.
Optimisation of a code is also included in interpretation of cases i.e.: if we are in start tag and we know that word is not a delimiter, tag or attribute than it can be just only an attribute value.

Program can trigger error if end tag is wrong (there is even number of tags of given type) not if end tag is in wrong place i.e:
<a></p></a> will not trigger error. When error is founded program is terminated proper message is given with place of the interpreted word. After program will not parse next input html.

Program checking syntax of html 5 but not i.e. children and parents of given tags and their attributes.

Structure of the program is forced "from top" by placing at the beginning UNIQUE_STRUCTURE_START and at the end UNIQUE_STRUCTURE_END of the file.

Inside body of the output file first repeated tags are placed then attributes and at the end content.

## Data structures
All data from files are stored in class called "htmlType" as string type. Those data are compared with list of proper such objects to verify syntax.

## Module descriptions
*with algorithms at implementation level*

`Classes:
/*********************************************/
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
}


Global variables
/*********************************************/
vector<string> DELIMITERS = {"<!--", "-->", "</", "/>", "<", ">", "='", "'"};//need to be sorted from the longest to shortest
vector<string> TAGS = {"!DOCTYPE", "head", "body", "html", "h1", "a", "div", "p"};
vector<string> ATTRIBUTES = {"br", "img", "html", "class"};
vector<string> UNIQUE_TAGS = {"br", "img"};
vector<string> VOID_TAGS = {"br", "img"};
string UNIQUE_STRUCTURE_START = "<!DOCTYPE html>\n<html lang='en'>\n<head>\n<meta charset='utf-8'>\n      <title></title>\n   </head>\n   <body>";
//*<-- insert proper content
string UNIQUE_STRUCTURE_END = "\n   </body>\n</html>";

Flags
/*********************************************/
bool FCT, FVAL, FTAG, FSTAG, FVTAG, FATTR;
bool ENV[] = {1, 0, 0, 0}; //init flags


Methods for parsing the file included in main.cpp
/*********************************************/
int sizeOfFile(fstream *file);
bool ifEqual(fstream *file1, fstream *file2);
void checkEndOfFile(fstream *file);
bool isEndOfFile(fstream *file);
void checkSize(fstream *file);
void printVector(vector<string> v);
vector<string> split(string s, string delim);
//precondition: using isDelimiter function
bool valid_utf8_file(const char* file_name);
//check if string align with utf8 charset
vector<string> splitWords(vector<string> words, string delim); //
bool isDelimiter(string word); //precondition: DELIMITERS as global variable must be declared
std::vector<string> storeHTML(const char* path);
void createHTML(htmlType *html1, htmlType *html2);


Pseudo algorithm for storing the files
/*********************************************/

1. store file
2. prepare words to interpret
   2.1 parse file by white spaces
   2.2 parse file by delimiters
   2.3 reset states
3. Create class tagType for file
3. take word (delimiter or delimiter free)
4. check if word is non empty
   4.1 if is empty than check state
   4.2 check end of file
   4.3 go to 1'st point
5. check if word is a content
5. check if word is a comment
6. check if word is a delimiter
7. check if word is a tag
8. check if word is an attribute
9. if word is not comment, delimiter, tag or attribute than it is a content.
10. go to 3'rd point.
`
On every conditional block particular error may occur!

## Input/output description
On input and output program require proper (align with functional requirements) HTML object which is stored in c++ class.

## Others
Because of lack of time program is not checking the structure of html and proper semantic i.e.: there can not be link attribute in html tag or html tag can not have parents. (this is included in TODO).


# Functional test cases
*Program build executable file from main.cpp i.e run in console: .\main.exe ".\test_cases\1.1.html" ".\test_cases\1.2.html*

Program should terminates when error will occur and output message should be given:
1. bad string in start tag
2. bad string in end tag
3. wrong end tag
4. bad delimiter place for `<`
5. bad delimiter place for `>`
6. bad delimiter place for `<!--`
7. bad delimiter place for `</`
8. bad delimiter place for `/>`
9. bad delimiter for attribute value `""`
10. long html

Program should generate proper output html file (index.html):
*compare all with example*
11. repeated content
12. repeated attributes
13. repeated tags
14. same input files
