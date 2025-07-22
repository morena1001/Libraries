#include <iostream>
#include "yaml_parser/yaml_parser.h"

using namespace std;

int main (int argc, char **argv) {
    // string felt = "throw";
    // string a = "hello";
    // int b = 19;
    // int c[5] = {0, 1, 2, 3, 4};
    // string *d = &felt;
    // void *p = &a;
    // cout << *(string *)p << endl;

    // Terminate early if the program does not have a file name in its arguments
    if (argc < 1)   return 0;

    string file_name = argv[1];
    yaml_parser parser (&file_name);
    
    return 0;
}