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
void output(char *argv[], opt * options);

int main(int argc, char *argv[]) { 
    (void) argc;
    (void) argv;
    
    opt options = {0};
    parser(argc,argv,&options);
    // printf("b: %d\n", options.b);
    // printf("e: %d\n", options.e);
    // printf("n: %d\n", options.n);
    // printf("s: %d\n", options.s);
    // printf("t: %d\n", options.t);
    // printf("v: %d\n________________________________\n\n", options.v);
    output(argv,&options);
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

void output(char *argv[], opt * options){
    FILE *fp = fopen(argv[optind], "r");
    if (fp) {
        char current;
        int counter = 0, str_count = 0, non_str_count = 0, flag = 1;
        while ((current = fgetc(fp)) != EOF) {
            if (options -> b && !(options -> n)){
                if (current != '\n'){
                    if (counter == 0){
                        
                        printf("%6d\t", ++str_count);
                        
                        counter = 1;
                    } 
                }   else {
                        counter = 0;
 
                }

                if(current == '\n' && flag == 1) {
                    if (options -> v){
                        printf("^M");
                    }
                    if (options -> e){
                        printf("$");
                    }
                }
            } 

            if (options -> n){
                
                if (counter == 0){
                    printf("%6d\t", ++str_count);
                    counter = 1;
                }
                if(current == '\n' && flag == 1) {
                    counter = 0;
                    if (options -> v){
                        printf("^M");
                    }
                    if (options -> e){
                        printf("$");
                    }
                }

            }

            if (options -> s){
                if (current == '\n'){
                    non_str_count++;
                } else {
                    non_str_count = 0;
                }

                if (non_str_count < 3){
                    if (options -> v && current == '\n'){
                        printf("^M");
                    }
                    if (options -> e && current == '\n'){
                        printf("$");
                    }

                    if (options -> t && current == '\t'){
                        printf("^I");
                    } else {
                        printf("%c", current);  
                    }
                    
                } 

                if (non_str_count < 2){
                    flag = 1;
                } else {
                    flag = 0;
                }

            } else{
                if (options -> v && current == '\n'){
                        printf("^M");
                }
                if (options -> e && current == '\n'){
                    printf("$");
                }

                if (options -> t && current == '\t'){
                        printf("^I");
                } else {
                        printf("%c", current);  
                }
            }
            
        }

    } else {
        printf("no such file");
    }
}