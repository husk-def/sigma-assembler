
#include "files.h"
#include "list.h"
#include "token.h"
#include "preprocessor.h"
#include "lexer.h"
#include "parser.h"
#include <assert.h>

int
main(int argc, char **argv)
{
    /* variables */
    char            word[25];
    int             check;
    FILE*           fp;
        /* points to the beginning of a list, should not be changed! */
    node_t*         ls_begin = init_list();          
    node_t*         node;
    node_t*         pnode;
        /* hardcoded path, todo change this */
        /* use command line arguments for input and output */
    char     path[30] = "./example/";
    char     lower_path[30] = "./example/mid";
    char     lower_uncomment_path[30] = "./example/mid_c";

    if (argc <= 2) {
        printf("error: insufficient number of arguments\n\t[in_file:20] [out_file:20]\n\n");
        exit(1);
    }

    strncat(path, argv[1], 15);

    printf("%s\n", path);
    

    node = ls_begin;
    
    /* implementation */
    save_node(*ls_begin);

    assert(generate_regexes() == 0);

    assert(export_add_trailing_newline(path) == 0);

    assert(export_lower_case(path, lower_path) == 0);

    assert(export_uncommented(lower_path, lower_uncomment_path) == 0);

    assert(lexical_analysis(lower_uncomment_path, get_saved_node()) == 0);

    print_list(get_saved_node());

	printf("\n*******************************************************************************************\n\n");

	assert(syntax_analysis(get_saved_node()));

	print_list(get_saved_node());

    deinit_list_from(&ls_begin);
    free_regexes();
    exit(0);
}
