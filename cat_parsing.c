#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

typedef struct options{
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
}opt;

void parser(int argc, char *argv[], opt * options);

int main(int argc, char *argv[]) { 
    (void) argc;
    (void) argv;
    
    opt options = {0};
    parser(argc,argv,&options);
    printf("%d\n", options.b);
    printf("%d\n", options.e);
    printf("%d\n", options.n);
    printf("%d\n", options.s);

    printf("%d\n", options.v);
    printf("%d\n", options.t);
    return 0;
}

void parser(int argc, char *argv[], opt * options){
    int opt;
    int opt_index;

    const struct option long_options[] = {
        {"number-nonblank", 0, 0, 'b'},
        {"show-ends", 0, 0, 'e'},
        {"number", 0, 0, 'n'},
        {"squeeze-blank", 0, 0, 's'},
        {"show-tabs", 0, 0, 't'},
        {"show-nonprinting", 0, 0, 'v'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv,"+benstvTE", long_options, &opt_index)) != -1){
        switch (opt)
        {
        case 'b':
            options -> b = 1;
        break;
        case 'e':
            options -> e = 1;
            options -> v = 1;
        break;
        case 'E':
            options -> e = 1;
            options -> v = 0;
        break;
        case 'n':
            options -> n = 1;
        break;
        case 's':
            options -> s = 1;
        break;
        case 't':
            options -> t = 1;
            options -> v = 1;
        break;
        case 'T':
            options -> t = 1;
            options -> v = 0;
        break;
        default:
            printf("usage benstv");
            exit(-1);
            break;
        }
    }
}
