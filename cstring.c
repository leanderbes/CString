#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define strequ(a, b) (!strcmp((a), (b)))

int main(int argc, char *argv[]) {
        const char **in_paths = calloc(argc, sizeof (const char *));
        int in_count = 0;
        int SINGLE_LINE = 0;
        int HEX = 0;

        for (int i = 1; i < argc; ++i) {
                if (strequ(argv[i], "--single-line"))
                        SINGLE_LINE = 1;
                else if (strequ(argv[i], "--hex"))
                        HEX = 1;
                else
                        if (argv[i][0] == '-') {
                                fprintf(stderr, "Invalid command-line option'%s'!\n", argv[i]);
                                return 1;
                        }
                        else {
                                in_paths[in_count] = argv[i];
                                ++in_count;
                        }
        }

        if (!in_count)
                goto use_stdin;

        for (int i = 0; i < in_count && in_paths[i]; ++i) {
                FILE *in;
                FILE *out;
                goto use_file_path;
use_stdin:
                in = stdin;
                out = fopen("a.str", "w");
                goto translate_loop;
use_file_path:  ;
                char *out_path = malloc((strlen(in_paths[i]) + 5) * sizeof (char));
                sprintf(out_path, "%s.str", in_paths[i]);

                in = fopen(in_paths[i], "r");
                out = fopen(out_path, "w");

                if (!in) {
                        fprintf(stderr, "Could not open file '%s'!\n", in_paths[i]);
                        return 1;
                }
                if (!out) {
                        fprintf(stderr, "Could not open file '%s'!\n", out_path);
                        return 1;
                }

                free(out_path);
translate_loop:
                putc('"', out);
                for (;;) {
                        int c = getc(in);
                        if (HEX) {
                                if (c != EOF)
                                        fprintf(out, "\\x%02x", c);
                                else {
                                        putc('"', out);
                                        goto end;
                                }
                        }
                        else switch (c) {
                                case '\\':
                                        fputs("\\\\", out);
                                        break;
                                case '"':
                                        fputs("\\\"", out);
                                        break;
                                case '\n':
                                        if (SINGLE_LINE)
                                                fputs("\\n", out);
                                        else
                                                fputs("\\n\"\n\"", out);
                                        break;
                                case EOF:
                                        fprintf(out, "\"%s", SINGLE_LINE ? "" : "\n");
                                        goto end;
                                default:
                                        putc(c, out);
                        }
                }
end:
                if (!in_count)
                        fclose(in);
                fclose(out);
        }

        free(in_paths);

        return 0;
}
