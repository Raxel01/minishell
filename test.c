// // #include <stdio.h>
// #include <stdlib.h>
#include "./Header/Parsing.h" 

int unsetenvo(const char *name, char **environ) {
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) {
        errno = EINVAL;  // Invalid argument
        return -1;
    }

    // Iterate through the environment variables to find and remove the specified variable.
    for (int i = 0; environ[i] != NULL; i++) {
        if (strncmp(environ[i], name, strlen(name)) == 0 && environ[i][strlen(name)] == '=') {
            // Shift all subsequent environment variables to overwrite this one.
            while (environ[i + 1] != NULL) {
                environ[i] = environ[i + 1];
                i++;
            }
            environ[i] = NULL;
            return 0;
        }
    }

    // If the variable is not found, it is considered "unset."
    return 0;
}

int main ()
{
    // t_my_env *envc;
    int a =200;
    // envc = import_env(env);
    // unsetenvo("OLDPWD", envc->m_env);
    to_uns(atoi("-7"));
    // printf ("c = %u\n", c);
    return (0);
}
