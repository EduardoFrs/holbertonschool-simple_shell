#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Parnt PID: %d\n", getppid());
    return (0);
}