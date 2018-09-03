/********************************************
* global variable and flags declaration
*********************************************/

vector<string> DELIMITERS = {"<!--", "-->", "</", "/>", "<", ">", "='", "'"};//need to be sorted from the longest to shortest

vector<string> TAGS = {"!DOCTYPE", "a", "abbr", "acronym", "abbr", "address", "applet", "object", "article", "aside", "audio", "b", "basefont", "bdi", "bdo", "big", "blockquote", "body", "button", "canvas", "caption", "center", "cite", "code", "data", "datalist", "dd", "del", "details", "dfn", "dialog", "dir", "ul", "div", "dl", "dt", "em", "fieldset", "figcaption", "figure", "figure", "font", "footer", "form", "frame", "frameset", "h1", "h6", "head", "header", "html", "i", "iframe", "ins", "kbd", "label", "legend", "fieldset", "li", "main", "map", "mark", "menu", "menuitem", "meter", "nav", "noframes", "noscript", "object", "ol", "optgroup", "option", "output", "p", "picture", "pre", "progress", "q", "rp", "rt", "ruby", "s", "samp", "script", "section", "select", "small", "video", "audio", "span", "strike", "del", "s", "strong", "style", "sub", "summary", "details", "sup", "svg", "table", "tbody", "td", "template", "textarea", "tfoot", "th", "thead", "time", "title", "tr", "video", "audio", "tt", "u", "ul", "var", "video"};

vector<string> ATTRIBUTES = {"accept", "accept-charset", "accesskey", "action", "align", "alt", "async", "autocomplete", "autofocus", "autoplay", "bgcolor"
"border", "charset", "checked", "cite", "class", "color"
"cols", "colspan", "content", "contenteditable", "contextmenu", "controls", "coords", "data", "datetime", "default", "defer", "dir", "dirname", "disabled", "download", "draggable", "dropzone", "enctype", "for", "form", "formaction", "headers", "height", "hidden", "high", "html", "href", "hreflang", "equiv", "id", "ismap", "kind", "label", "lang", "list", "loop", "low", "max", "maxlength", "media", "method", "min", "multiple", "muted", "name", "novalidate", "onabort", "onafterprint", "onbeforeprint", "onblur", "onbeforeunload", "oncanplay", "oncanplaythrough", "onchange", "onclick", "oncontextmenu", "oncopy", "oncuechange", "oncut", "ondblclick", "ondrag", "ondragend", "ondragenter", "ondragleave", "ondragover", "ondragstart", "ondrop", "ondurationchange", "onemptied", "onended", "onerror", "onfocus", "onhashchange", "oninput", "oninvalid", "onkeydown", "onkeypress", "onkeyup", "onload", "onloadeddata", "onloadedmetadata", "onloadstart", "onmousedown", "onmousemove", "onmouseout", "onmouseover", "onmouseup", "onmousewheel", "onoffline", "ononline", "onpageshow", "onpaste", "onpause", "onplay", "onplaying", "onprogress", "onratechange", "onreset", "onresize", "onscroll", "onsearch", "onseeked", "onseeking", "onselect", "onshow", "onstalled", "onsubmit", "onsuspend", "ontimeupdate", "ontoggle", "onunload", "onwaiting", "onwheel", "open", "optimum", "pattern", "placeholder", "poster", "preload", "readonly", "rel", "required", "reversed", "rows", "rowspan", "sandbox", "scope", "selected", "shape", "size", "sizes", "span", "spellcheck", "src", "srcdoc", "srclang", "att", "srcset", "start", "step", "style", "tabindex", "target", "title", "translate", "type", "usemap", "value", "width", "wrap"};

vector<string> VOID_TAGS = {"area", "base", "br", "br", "col", "colgroup", "command", "embed", "hr", "img", "input", "keygen", "link", "meta", "param", "source", "track", "wbr"};


vector<string> UNIQUE_TAGS = {"!DOCTYPE", "html", "head", "body"};

string UNIQUE_STRUCTURE_START = "<!DOCTYPE html>\n<html lang='en'>\n<head>\n<meta charset='utf-8'>\n      <title></title>\n   </head>\n   <body>";
//*<-- insert proper content
string UNIQUE_STRUCTURE_END = "\n   </body>\n</html>";
/********************************************
* setting flags for states
*********************************************/
bool FCT, FVAL, FTAG, FSTAG, FVTAG, FATTR;
bool ENV[] = {1, 0, 0, 0}; //init flags
/*********************************************/
