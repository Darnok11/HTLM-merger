/********************************************
* Method for htmlType class which
* fill htmlType object with data
*********************************************/
bool htmlType::interpretWord(string word, int i) {
   if (word == "") {
      //this is end of file
      cout << "End of file.\nHTML File is properly parsed." << endl;
      return 1;
   }
   if (ENV[0]) { //insert content
      // cout << "in content\n" << word << endl;
      // cout << "--------------------" << endl;
      if (ENV[1]) { //if in comment (not storing anything!)
         // cout << "in comment\n" << word << endl;
         // cout << "--------------------" << endl;

         if (word == "<!--") { error(0, i, word); }
         if (word == "-->") {
            // cout << "end comment\n" << word << endl;
            // cout << "--------------------" << endl;

            ENV[1] = 0;
         }
         return 1;
      }
      // check end content
      if (word == "<!--") {
         // cout << "start comment\n" << word << endl;
         // cout << "--------------------" << endl;


         ENV[1] = 1; //start comment
         return 1;
      } else if (word == "</") {
        // cout << "go out from content go to end tag\n" << word << endl;
        // cout << "--------------------" << endl;


        ENV[2] = 1; //go into end tag
        ENV[0] = 0; //go out from content
        return 1;
     } else if (word == "<") {
         // cout << "go out from content go to start tag\n" << word << endl;
         // cout << "--------------------" << endl;

         ENV[3] = FTAG = 1; //go into start tag
         ENV[0] = 0; //go out from content
         return 1;
      }
      //not ended content - insert whatever occur
      // cout << "insert content\n" << word << endl;
      // cout << "--------------------" << endl;

      insertContent(word);
      return 1;
   } //if in content


   /*********************************************/
   if (ENV[2]) {
      // cout << "End tag environment\n" << word << endl;
      // cout << "--------------------" << endl;

      if (FCT) {//after end tag
         // cout << "After end tag" << endl;
         // cout << "--------------------" << endl;
         if (word == ">") {//</>

            // cout << "Program closing end tag and starting content.\n";
            // cout << "--------------------" << endl;


            ENV[2] = 0; //close end tag
            ENV[0] = 1; //start content
            FCT = 0;
            return 1;
         }
         error(1, i, word);
      }
      //just can be end tag
      if (isEndTag(word)) {
         // cout << "Program insertEndTag\n" << word << endl;
         // cout << "--------------------" << endl;
         insertTag(word);
         FCT = 1;
         return 1;
      }
      error(2, i, word); //not end tag
   }

   /*********************************************/
   if (ENV[3]) { //start tag space: tag, attr, >, />
      // cout << "Start tag environment set by < and ended with > or />:\n " << word << endl;
      // cout << "--------------------" << endl;
      if (FVAL) {//not interpreted attribute value
            // cout << "This is attr value:\n" << word << endl;
            // cout << "--------------------" << endl;
         if (word == "'") { //close attribute value
            FVAL = FATTR = 0;
            return 1;
         }
         insertAttrVal(word);
         return 1;
      }
      if (FATTR && !FVAL) {
         if (word == "='") {
            // cout << "Starting adding attriburte values:\n" << word << endl;
            // cout << "--------------------" << endl;
            FVAL = 1; //open values
            return 1;
         }
      }
      if (FTAG) { //tag flag set by <
         // cout << "Tag req in env 3: " << word << endl;
         if (isTag(word)) {
            // cout << "Program insert start tag. Req ending by >:\n" << word << endl;
            // cout << "--------------------" << endl;

            FTAG = 0;
            FSTAG = 1;
            insertTag(word);
            insertStartTag(word);
            return 1;
         }
         if (isVoidTag(word)) {
            // cout << "Program insert void tag. Req ending by />: \n" << word << endl;
            // cout << "--------------------" << endl;

            FTAG = 0;
            FVTAG = 1;
            insertVoidTag(word);
            return 1;
         }
         error(3, i, word); //this is not tag or void tag
      }


      if (word == ">") { //avoid <>
         if (FSTAG) {
            // cout << "Program closing start tag environment:\n" << word << endl;
            // cout << "--------------------" << endl;

            ENV[3] = FSTAG = FATTR = 0;
            ENV[0] = 1;
            return 1;
            /* code */
         }
         error(4, i, word); // required >
      }
      if (word == "/>") {
         if (FVTAG) {
            // cout << "Program closing void tag environment:\n" << word << endl;
            // cout << "--------------------" << endl;

            ENV[3] = FVTAG = FATTR = 0;
            ENV[0] = 1;
            return 1;
         }
         error(5, i, word);  // required />
      }
      //must be attr
      // cout << "Check if " << word << " is attribute" << endl;
      // cout << "--------------------" << endl;

      if (isAttr(word)) {
         // cout << "this is attribute\n" << word << endl;
         // cout << "--------------------" << endl;

         insertAttr(word);
         FATTR = 1;
         return 1;
      } //TODO: attribute values?
      error(6, i, word);
   }
}
