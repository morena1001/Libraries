#include <string>
#include <fstream>

#define DOCUMENT_START      "---"
#define DOCUMENT_END        "..."
#define COMMENT_SYMBOL      "#"

enum value_type { _STRING, _INTEGER, _FLOAT, _NAN, _INF, _NULL, _BOOL, _LIST, _DICTIONARY, _HEAD };

typedef struct Pair_Node {
    int id;
    enum value_type type;
    void *data;
    Pair_Node *next;
} pair_node_t;

typedef struct Doc_Node {
    pair_node_t *head_pair;
    Doc_Node *next;
} doc_node_t;


class yaml_parser {
    doc_node_t *head_doc;
    std::ifstream *file;

    /* Only '.yml' or '.yaml' files types are accepted */
    bool Check_Input_File_Type (std::string *file_name);

    /* Make sure first non-comment line is made up of three dashees */
    bool Check_Document_Existence ();

    // /* Iterate through all lines of the file, skipping comments and parsing key value pairs.
    //    Returns number of errors, with 0 corresponding to no errors found */
    // int Parse_File ();

    public:
        /* Attempts to open the given file, instantiates a head that points to the file,
           and parses all key value pairs in the file */
        yaml_parser (std::string *file_name);

        /* Iterate through all lines of the file, skipping comments and parsing key value pairs.
           Returns number of errors, with 0 corresponding to no errors found */
        int Parse_File ();

};
