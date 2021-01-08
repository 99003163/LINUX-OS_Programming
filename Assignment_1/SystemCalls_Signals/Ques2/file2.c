#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE * file1;
    char fpath[100];
    char ch;
    int chars, words, lines;
    file1 = fopen("sample.txt", "r");
    if (file1 == NULL)
    {
        printf("\n Can't open file.\n Check if file exists.\n");

        exit(EXIT_FAILURE);
    }

    chars = words = lines = 0;
    while ((ch = fgetc(file1)) != EOF)
    {
        chars++;

        /* Check for line */
        if (ch == '\n' || ch == '\0')
            lines++;

        /* Check for words */
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
            words++;
    }
    if (chars > 0)
    {
        words++;
        lines++;
    }
    printf("\n");
    printf("Number of characters present = %d\n", chars);
    printf("Number of words present      = %d\n", words);
    printf("Number of lines present     = %d\n", lines);

    fclose(file1);

    return 0;
}
