#include <string>
#include <string.h>
#include <fstream>

#define DOCUMENT_START      "---"
#define DOCUMENT_END        "..."
#define COMMENT_SYMBOL      "#"
#define PAIR_DELIM          ": "

#define SINGLE_QUOTE_CHAR       '\''
#define DOUBLE_QUOTE_CHAR       '"'
#define COMMENT_CHAR            '#'
#define INLINE_ARRAY_CHAR       '['
#define INLINE_DICTIONARY_CHAR  '{'

#define REMOVE_DELIM(value, delim_pos, delim)   (((string) (value)).substr (delim_pos + strlen (delim)))
#define HAS_SINGLE_QUOTES(value)                (((string) value).front () == '\'' && ((string) (value)).find_last_of ('\'') != 0)
#define HAS_DOUBLE_QUOTES(value)                (((string) value).front () == '"' && ((string) (value)).find_last_of ('"') != 0)
#define REMOVE_INLINE_COMMENTS(value)          (HAS_SINGLE_QUOTES (value) || HAS_DOUBLE_QUOTES (value) ? (((string) value).find_last_of (SINGLE_QUOTE_CHAR) < ((string) value).find_last_of (COMMENT_CHAR) || ((string) value).find_last_of (DOUBLE_QUOTE_CHAR) < ((string) value).find_last_of (COMMENT_CHAR) ? ((string) value).substr (0,((string) value).find_last_of (COMMENT_CHAR)) : value) : ((string) value).substr (0, ((string) value).find (COMMENT_SYMBOL)))

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
