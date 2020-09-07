#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <getopt.h>

void print_usage(const char *msg)
{
    if (msg) printf("Error: %s\n", msg);
    printf("Usage:");
    printf("\tfluid_filters [CMD] [INPUT]\n\n");
    printf(
        "\t--abs      Returns the absolute value of a number\n"
        "\t-h         print this help message.\n"
    );
}

char *absolute(char *str)
{
    char *vdtor, *token, *dot = ".";
    if(*(str) == '-' && strlen(str) == 1) return "ERROR1";
    if(*(str) == '-') str +=1;

    vdtor = strdup(str);
    if(strstr(vdtor, dot)) {
        token = strsep(&vdtor, dot);
        while(*token) if(isdigit(*token++) == 0) return "ERROR2";
    }
    while(*vdtor) if(isdigit(*vdtor++) == 0) return "ERROR3";
    return str;
}

int ceil(char *str)
{
    char *input, *token, *dot = ".", *dash = "-";
    int incr = 0;

    input = strdup(str);
    if(strstr(input, dot)) {
        token = strsep(&input, dot);
        if(*input > *dot && *token != *dash) incr = 1;
    }

    return atoi(str)+incr;
}

static struct option longopts[] = {
    {"abs", required_argument, NULL, 0x001},
    {"ceil", required_argument, NULL, 0x002},
    {"help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0},
};

int main(int argc, char **argv)
{
    int opt;

    while( (opt = getopt_long(argc, argv, "a:b:h", longopts, NULL)) != -1) {

        switch (opt)
        {
        case 0x001:
            printf("%s\n", absolute(*(argv+2)));
            break;
        case 0x002:
            printf("%d\n", ceil(*(argv+2)));
            break;
        case 'h':
            print_usage(NULL);
        default:
            break;
        }
    }
    return 0;
}