#include <iostream>
#include <string>
#include <vector>
#include <list>
// #include "../utf8/source/utf8.h"


using namespace std;

vector<string> TAGS = {"!DOCTYPE", "a", "abbr", "acronym", "abbr", "address", "applet", "object", "article", "aside", "audio", "b", "basefont", "bdi", "bdo", "big", "blockquote", "body", "button", "canvas", "caption", "center", "cite", "code", "data", "datalist", "dd", "del", "details", "dfn", "dialog", "dir", "ul", "div", "dl", "dt", "em", "fieldset", "figcaption", "figure", "figure", "font", "footer", "form", "frame", "frameset", "h1", "h6", "head", "header", "html", "i", "iframe", "ins", "kbd", "label", "legend", "fieldset", "li", "main", "map", "mark", "menu", "menuitem", "meter", "nav", "noframes", "noscript", "object", "ol", "optgroup", "option", "output", "p", "picture", "pre", "progress", "q", "rp", "rt", "ruby", "s", "samp", "script", "section", "select", "small", "video", "audio", "span", "strike", "del", "s", "strong", "style", "sub", "summary", "details", "sup", "svg", "table", "tbody", "td", "template", "textarea", "tfoot", "th", "thead", "time", "title", "tr", "video", "audio", "tt", "u", "ul", "var", "video"};


int main(){
   std::vector<string> test;
   test = TAGS;

   for (auto const &word : test) {
      std::cout << "tes: " << word << '\n';
   }

   return 0;
}
