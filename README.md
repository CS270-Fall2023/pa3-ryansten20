# PA3 tail command (100 pts)

## Learner Objectives
At the conclusion of this programming assignment, participants should be able to:
* Use **`open`**,**`close`**, **`read`** and **`write`** system calls.
* Work with the `string.h` library
* Read and understand code written by someone else


## Program Details
### Part 1 (80 pts)
For this assignment, you will be required to write your own version of the Linux `tail` command. This command has many different options. Read the `manpage` for the `tail` command. 
* You only need to implement the default `tail` command, with options `-n NUM_OF_LINES` and with option`-n +START_LINE`.
* You must use system calls for outputting to the console and for working with the file. Do not use `printf`, `readf`, `writef`, etc.
* Add `makefile` to build your function. For simplicity of implementation, assume that all lines in the input file are less than 256 bytes.
* If you used dynamic memory allocation, test for memory leaks (see instruction below)

### Part 2 (20 pts)
After you are done with your program, search online for the (default) implementation of tail (or ask ChartGPT).  Copy the online implementation in the folder `otherTail` or include the URL in the summary. Compare your implementation with online implementation, and write a summary in the `compare.*` document. I am not interested in line-by-line write of. Compare the general idea of displaying the last n lines from the file.

## Challenge Yourself Beyond The Scope of the PA (Not Required EC 20 pts)
* Adjust your program so that it works for a line of any length (longer than 256 characters). Make sure to test it for the situation when the line length in the file is a few times longer than the buffer you are using for reading from the file. You will need dynamically allocate memory. You may use the C function `malloc` or `calloc`. Don't use system calls for memory allocation.
### Test for memory leaks
Test your program for memory leaks
* on Linux - use Valgrind tool
````
sudo apt install valgrind
gcc -Wall -g *.c
valgrind --leak-check=full ./myTail test.txt
````
* on Mac (M1-M2) use leaks tool
````
gcc -Wall -g *.c
leaks --atExit -- ./myTail test.txt
````
> Note: no space between `--` and `atExit`, space between `--` and name of the executable.

## Submitting Assignments
1. Test your code in the Codespace.
2. Ensure that you `push` your local copy of this PA's repo to GitHub. Verify that the code in GitHub is the same code you have on your local computer.
3. You may continue to update and push your code into this repo as long as it is before the deadline.
4. It is VERY IMPORTANT that besides pushing the code to GitHub you still submit the GitHub URL of this programming assignment in Canvas. This allows the instructor to be notified of your final submission and that you are ready for grading.

> **_NOTE: By submitting your code to be graded, you are stating that your submission does not violate the Academic Integrity Policy outlined in the syllabus._**
