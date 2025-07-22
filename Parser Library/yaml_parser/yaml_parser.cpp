#include <iostream>
#include <algorithm>
#include <cctype>
#include "yaml_parser.h"

using namespace std;

yaml_parser::yaml_parser (string *file_name) {
    file = new ifstream;
    file->open (*file_name, ifstream::in);

    if (file->is_open ()) {
        if (!Check_Input_File_Type (file_name))     return;
        if (!Check_Document_Existence ())           return;
        
        head_doc = new doc_node_t;

        Parse_File ();
    }
}

int yaml_parser::Parse_File () {
    string line;
    int num_errors = 0;

    string key, value;

    while (getline (*file, line)) {
        // Remove white space from key string
        key = line.substr (0, line.find_first_of (':'));
        key.erase (remove_if (key.begin(), key.end (), ::isspace), key.end ());

        // Remove ending comments
        value = line.substr (line.find_first_of (':') + 2);
        if (value.find_last_of ('"') < value.find_last_of ('#'))    value = value.substr (0, value.find_last_of ('#'));

        cout << key << " : " << value << endl;
    }

    return num_errors;
}

bool yaml_parser::Check_Input_File_Type (string *file_name) {
    string extension = file_name->substr (file_name->find_last_of ('.'));

    if (extension.compare (".yml") == 0 || extension.compare (".yaml") == 0)    return true;
    return false;
}

bool yaml_parser::Check_Document_Existence () {
    string line;
    
    /* A file can contain comments before the start-of-document line
       and a start-of-document line must be present before any key value pairs */
    while (getline (*file, line)) {
        if (line.compare (DOCUMENT_START) == 0)     return true;
        if (line.compare (COMMENT_SYMBOL) != 0)     return false;
    }
}
