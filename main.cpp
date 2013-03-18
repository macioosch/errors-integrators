#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    // CLI options parsing
    int c;
    double dtValue;
    opterr = 0;
    while ((c = getopt(argc, argv, "mt:")) != -1)
        switch (c)
        {
        case 'm':
            fprintf(stdout, "# Dt; Euler; RK4\n");
            return 0;
        case 't':
            dtValue = atof(optarg);
            break;
        case '?':
            if (optopt == 't')
              fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint(optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            return 1;
        default:
            abort();
        }

    for (int index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);

    // output
    fprintf(stdout, "%f\n", dtValue);

    return 0;
}

