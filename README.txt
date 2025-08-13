=========================================================================================
I made this program to improve my C programming skills, specifically in File I/O, 
as well as to improve my ability to handle larger projects. While making this program, 
I decided that I would eventually upload it to my GitHub; because of this I tried to 
write the program in a way that would be educational to those new to programming. That 
is why it has very detailed comments.

The program's purpose is to automate the process of making diagrams for data 
structures. Given what the user specifies through command line arguments, 
the program will send the output to a '.txt' file located in the same directory 
as the program files. Users can also specify if they would like randomly generated 
values to be put into the diagrams.

Ideally, your code should not be full of comments. You should only comment a block 
or line of code if it is not obvious what the code is doing. But if you ever write code 
that is not obvious, you should ask yourself why it's not and first try to make it more 
readable.
Remember, the code you write will almost certainly be looked at, or worked on by others. 
So, when you write code, always keep that in mind and try to consider how it will look 
to people reading it for the first time.

Helpful links for those who want to learn more:
http://www.cplusplus.com/reference/
https://en.wikibooks.org/wiki/C_Programming/Stream_IO
https://www.gnu.org/software/make/manual/make.html
https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
https://editorconfig.org
=========================================================================================
Supported data structures are as follows:

arrays (arr), 2D arrays (2da)

linked list node (ln, this will give you space to optionally include addresses 
for the nodes location, the arrow pointing to the next node/NULL, 
and have a spot to include the address of the next node's address), struct node (sn)

array of linked lists (aol), array of structures (aos, if the user wants 
they can describe what the elements of the struct node are (within reason))

stack (stk), queue (que)

tree (tre), trie (tri)
=========================================================================================
Stuff to fix:

FIXME: Fix the top and bottom of linked list nodes only printing 1 character.
FIXME: Fix alignment on indices on array implementation of stack/queue.
=========================================================================================
Stuff to do:

TODO: Standardize all user input statements? Use fgets() for everything?
TODO: Expand the input arrays used so that there is extra space to see if the user went
      over the specified size limit? Then I could check to make sure they followed the
      instructions, and return if they didn't.
TODO: Additional functionallity: Add the ability to skip any prompting, like when 
      it shows you what you entered.
TODO: Additional functionallity: Make it so that if this program is included 
      with another program that makes like a tree/trie/linked list or whatever, 
      this program can print out the contents of the other programs data.
TODO: Additional functionallity: Make it so that there is an option to use the program 
      in the terminal window, rather than printing to an output file.
TODO: Additional functionallity: Add a verbose CLA option that prints a short summary 
      of the data structure chosen (like description and complexities of basic 
      operations).
TODO: Additional functionallity: Add the ability for users to name their custom vars 
      in their custom structs.
TODO: Allow users to do addition arguments like '-type=sn' instead of 'sn'?
TODO: Create like a settings/options struct to hold all the users settings. 
      Then you can pass around the struct instead of a bunch of vars.
TODO: Move universal helper functions to a seperate file (create_topAndBot)?
TODO: Update 'decPlaces' handling with integers vs floating points. It's current
      implementation is more integer friendly than double friendly.
TODO: Change 'quantity' in the context of '2da' to mean how many 2D arrays the user
      wants? Like 3 means they will type in the dimensions of 3 2D arrays to be made.

SAMPLE COMMAND LINE ARGUMENT: see printMenu() function in DataDiagrams.c

TODO: Update these (And turn them into macros???)
NOTE: Return values from main() for debugging purposes are as follows:
         '-1' - invalid input
         '0'  - normal exit
         '1'  - user forced exit
         '2'  - error with a function like "fopen" occured
=========================================================================================
