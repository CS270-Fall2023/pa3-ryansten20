#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 4096
#define MAX_LINES 200

int main(int argc, char **argv) {


    char buffer[BUF_SIZE];
    ssize_t bytesread;
    int numOfLines = 0;
    int startPosition = 0;

    //check for only tail or -n num of lines or -n +start line
    int input = 0;
    if(argc != 4 && argc != 2)
    {
        perror("Incorrect Usage.");
        exit(1);
    }
    else if (argc == 4 && strcmp(argv[1],"-n") == 0 ) {

        input = open(argv[3], O_RDONLY);
        if (input == -1) {
            perror("Opening input file");
            exit(1);
        }
        printf("File is open\n");
        //+START_LINE
        if (strchr(argv[2], '+') != NULL)
        {
            startPosition = atoi(argv[2] + 1); //skip + char
            numOfLines = 10;
        }
            //NUM_OF_LINES
        else
        {
            startPosition = 0;
            numOfLines = atoi(argv[2]); //LAST N LINES
        }
    }
        //ONLY WANT THE LAST 10 LINES
    else{
        input = open(argv[1], O_RDONLY);
        if (input == -1) {
            perror("Opening input file");
            exit(1);
        }
        printf("File is open\n");
        numOfLines = 10; //automatically set if 10 lines are requested
    }


    bytesread = read(input, buffer, BUF_SIZE);

    if (close(input) == -1) {
        perror("Closing File");
        exit(1);
    }

    char newlines[MAX_LINES];
    int index = 0, count = 0;
    newlines[0] = -1;

    for (int i = 0; i < bytesread; i++) {
        if (buffer[i] == '\n' || i == bytesread - 1)
        {
            newlines[++count] = i;
        }
    }

    char **lines = malloc((count + 1) * sizeof(char *));

    for (int i = 0; i < count; i++) {
        int start_index = newlines[i] + 1;
        int length = newlines[i + 1] - start_index;

        if (buffer[newlines[i + 1]] != '\n')
            length++;

        lines[i] = malloc((length + 1) * sizeof(char));
        strncpy(lines[i], buffer + start_index, length);
        lines[i][length] = '\0';
    }


    int startLine = 0; //default startline is at 0
    int linesToPrint = numOfLines; //lines to print is either 10 or what the user enters

    //there was a + in the input
    if(startPosition > 0) {

        startLine = startPosition; //adjust startLine to new position
        //prints 10 lines by default
        for (int i = startLine; i < startLine + numOfLines; i++) {
            write(1, lines[i], strlen(lines[i]));
            write(1, "\n", 1);
            free(lines[i]);
        }
        free(lines);
    }

        //no plus in the input
    else {

        startLine = count - linesToPrint; //start printing lines from lines to print
        //lines to print is set to what user put in

        for (int i = startLine; i < startLine + linesToPrint; i++) {
            write(1, lines[i], strlen(lines[i]));
            write(1, "\n", 1);
            free(lines[i]);
        }
        free(lines);
    }
    return 0;
}