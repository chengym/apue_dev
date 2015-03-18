#include <string.h>　
#include <stdio.h>　

int main(void)
{
    FILE *stream;
    char string[] = "This is a test";
    int ch;

    /* open a file for update */
    stream = open("file", "w+");
 
    /* write a string into the file */
    fwrite(string, strlen(string), 1, stream);
 
    /* seek to the beginning of the file */
    fseek(stream, 0, SEEK_SET);
    do {
        /* read a char from the file */
        ch = fgetc(stream);
        /* display the character */
        putchar(ch);
    } while (ch != EOF);

    fclose(stream);
    return 0;
}
