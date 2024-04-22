#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **argv)
{
    char *prompt = "$ ";
    char *lineptr;
    size_t n = 0;

    // void variables
    (void)ac; (void)argv;

    printf("%s", prompt);
    getline(&lineptr, &n, stdin);

    free(lineptr);
    return (0);
}