# Work in Progress

## What is it?

The program's purpose is to automate the process of making diagrams for data structures. Given what the user specifies through command line arguments, the program will send the output to a '.txt' file located in the same directory as the program files. Users can also specify if they would like randomly generated values to be put into the diagrams.

## How to run it?

Step 1: Make sure you have an enviroment to compile and run C programs. There are a couple of ways to do this, but I use Windows Subsystem for Linux (WSL).

Step 2: Either clone this repo or download the files on to your computer.

Step 3: At the command line, move into the directory with all the files, and run the `make` command.

Step 4: At the command line, run `./dd`.

For help, run `./dd help`.

### Supported Data Structures

- `arr` = (1D) array
- `2da` = (2D) array
- `ln` = linked list node(s)
- `sn` = struct node
- `stk` = stack (both array and linked list implementations available)
- `que` = queue (both array and linked list implementations available)

### Planned Data Structures

- `aol` = array of linked lists
- `aos` = array of struct nodes
- `tre` = tree
- `tri` = trie

### Debugging

There is a `make` rule for debugging that can be run with the command: `make debug`.

Return values from main() for debugging purposes are as follows:

- `-1` - invalid input
- `0`  - normal exit
- `1`  - user forced exit
- `2`  - error with a function like "fopen" occured

## Why make it?

I made this program to improve my C programming skills, specifically in File I/O, as well as to improve my ability to handle larger projects. While making this program, I decided that I would eventually upload it to my GitHub; because of this I tried to write the program in a way that would be educational to those new to programming. That is why it has very detailed comments.

Ideally, your code should not be full of comments. You should only comment a block or line of code if it is not obvious what the code is doing. But if you ever write code that is not obvious, you should ask yourself why it's not and first try to make it more readable. Remember, the code you write will almost certainly be looked at, or worked on by others. So, when you write code, always keep that in mind and try to consider how it will look to people reading it for the first time.

Helpful links for those who want to learn more:

- `C` [Library](https://cplusplus.com/reference/clibrary/)
- `C` [Input/Output Tutorial](https://en.wikibooks.org/wiki/C_Programming/Stream_IO)
- `make` [Specification/Library](https://www.gnu.org/software/make/manual/make.html)
- `make` [Tutorial](https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)
- `.editorconfig` [Tutorial](https://editorconfig.org)

## Q&A

> Why the big block comments?

They allow you to easily see where functions start in editor's minimap. I don't use them anymore, but liked them a lot when I started the project.
