#include	<stdio.h>

char *strerror(int error)
{
    static char mesg[30];

    sprintf(mesg, "Unknown error (%d)", error);
    return (mesg);
}
