#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int ac, char **av, char **env);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
char *_getenv(const char *name);