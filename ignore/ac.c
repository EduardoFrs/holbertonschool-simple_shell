#include <stdio.h>
/**
 * main - prints all arguments without using ac
 *
 * Return: Always 0.
 */

int main(int argc, char **argv)
{
    while (*argv)
    {
        printf("%s\n", *argv);
        argv++;
    }
    return (0);
}