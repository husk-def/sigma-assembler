
#define DEBUG "--debug"
#define NODEB "--no-debug"

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
        /* points to the beginning of a list, should not be changed! */
    node_t*         ls_begin = init_list();
        /* hardcoded path, todo change this */
        /* use command line arguments for input and output */
    char     path[50] = "./example/";
    char     lower_path[50] = "./example/mid";
    char     lower_uncomment_path[50] = "./example/mid_c";
	char	 output_path[50] = "./example/";
    char     debug[20];

    if (argc != 3) {
        printf("error: insufficient number of arguments\n\t[in_file:20]\n\t[--no-debug/--debug]\n\n");
        exit(1);
    }

    strncat(path, argv[1], 15);
	strncat(output_path, argv[1], 15);
	strncat(output_path, ".out", 15);

    strcpy(debug, argv[2]);

    printf("%s\n", path);
	printf("%s\n", output_path);

    /* implementation */
    save_node(*ls_begin);

    assert(generate_regexes() == 0);

    assert(export_add_trailing_newline(path) == 0);

    assert(export_lower_case(path, lower_path) == 0);

    assert(export_uncommented(lower_path, lower_uncomment_path) == 0);

    assert(lexical_analysis(lower_uncomment_path, get_saved_node()) == 0);

	//print_list(get_saved_node());

	printf("\n*******************************************************************************************\n\n");

	convert_literals(get_saved_node());

	err_t e = syntax_analysis(get_saved_node());

	//print_list(get_saved_node());

	if (e) {
		printf("\n\nERR: %d at Line: %d\n\n", e, get_line_num());
	}

	replace_labels(get_saved_node());
	if (!strcmp(debug, DEBUG)) {
        print_list(get_saved_node());
    }

	parse(get_saved_node(), output_path);

    deinit_list_from(&ls_begin);
    free_regexes();
    exit(0);
}
