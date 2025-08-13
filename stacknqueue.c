// ==================================================================
// stacknqueue.c
// By Austin T. (Github: Knights879)
// ==================================================================
// Implements the stack diagram (stk) and queue diagram (que)
// ==================================================================

#include "DataDiagrams.h"

// Prints the array implementation of a "stk" or "que"
int print_sq_arr(int decPlaces, int hole, int quantity, char material, char rngFill,
                 int largestVal, char dataStruct, FILE **ofp)
{
   int i = 0;  // will be used for loops and indexing
   int size;   // will be used to calculate 'topAndBot'
   int firstCaretLoc;   // will be used for labeling (if needed)
   int secondCaretLoc;  // will be used for labeling (if needed)
   char wall;  // will be the character used on the side of each node
   char *topAndBot;  // will store the top and bottom of the diagram

   /* Step 1: Determine the values for the variables defined above */

   // Determine size
   size = 1 + (hole + 1) * quantity;
   // Use 'size' to alloc space for 'topAndBot'
   topAndBot = malloc(sizeof(char) * size + 1);
   // Check to make sure malloc() did not return NULL
   if (topAndBot == NULL)
      return 1;
   // Create the string that represents 'topAndBot'
   create_topAndBot(decPlaces, size, material, topAndBot);
   // Check to see if error occured in create_topAndBot()
   if (topAndBot == NULL)
      return 1;

   // Determine the location of the carets
   firstCaretLoc = 1 + (hole / 2);
   secondCaretLoc = size - (hole / 2) - (hole % 2);

   // Determine the roof and wall materials
   wall = (material == '+') ? '|' : '#';

   /* Step 2: Print the diagram */

   // Print the indices
   fprintf(*ofp, "%*s%d", 1 + (hole / 2), " ", i);
   for (i = 1; i < quantity; i++)
      fprintf(*ofp, "%*s%d", (hole / 2) + 1 + (hole / 2), " ", i);

   // Print the top of the array diagram and the first wall
   fprintf(*ofp, "\n%s\n%c", topAndBot, wall);

   // Print the middle of the array diagram
   for (i = 0; i < quantity; i++)
   {
      // NOTE: This can be done in one line, but wouldn't be reader friendly
      if (rngFill == 'y')
         fprintf(*ofp, " %*d %c", decPlaces, get_rand_int(largestVal), wall);
      else // rngFill == 'n'
         fprintf(*ofp, " %*s %c", decPlaces, " ", wall);
   }

   // Print the bottom of the array diagram
   fprintf(*ofp, "\n%s\n", topAndBot);

   // Print the labels for the top and bottom of the stack or queue
   // Only label if there is enough space TODO: try to even when there isn't space
   if (secondCaretLoc >= 9)
   {
      // Print the carets
      fprintf(*ofp, "%*s^%*s^\n", firstCaretLoc, " ",
              secondCaretLoc - 2 - firstCaretLoc, " ");
      // Print the labels
      fprintf(*ofp, "%*s%s%*s%s\n", firstCaretLoc - 3, " ",
              (dataStruct == 's') ? "bottom" : "front",
              secondCaretLoc - 2 - firstCaretLoc - ((dataStruct == 's') ? 4 : 3), " ",
              (dataStruct == 's') ? "top" : "back");
   }

   /* Step 3: Clean up */

   // NOTE: ALWAYS remember to free any dynamically allocated memory
   free(topAndBot);

   return 0;
}

// Prints a "stk" or "que" node (linked list implementation)
void print_sq_ll_node(int decPlaces, int hole, int quantity, char material, char rngFill,
                      int largestVal, char dataStruct, int address, FILE **ofp)
{
   int i;  // used for looping
   char roof = (material == '+') ? '-' : '#'; // will be the char used on the top and bottom of each node
   char wall = (material == '+') ? '|' : '#'; // will be the char used on the side of each node

   // Print the address (if requested)
   if (address != -1)
      fprintf(*ofp, "0x%03d\n", address * 4);

   // Print the top and first wall of the node
   fprintf(*ofp, "%c", material);
   for (i = 0; i < hole; i++)
      fprintf(*ofp, "%c", roof);
   fprintf(*ofp, "%c\n%c", material, wall);

   // Print the hole within the node
   if (rngFill == 'y')
      fprintf(*ofp, " %*d %c", decPlaces, get_rand_int(largestVal), wall);
   else // rngFill == 'n'
      fprintf(*ofp, " %*s %c", decPlaces, " ", wall);

   // Print the label, if necessary
   if (address == 0)
      fprintf(*ofp, " < %s\n", (dataStruct == 's') ? "top" : "front");
   else if (address == quantity - 1)
      fprintf(*ofp, " < %s\n", (dataStruct == 's') ? "bottom" : "back");
   else // Don't print a label
      fprintf(*ofp, "\n");

   // Print the bottom of the node
   fprintf(*ofp, "%c", material);
   for (i = 0; i < hole; i++)
      fprintf(*ofp, "%c", roof);
   fprintf(*ofp, "%c\n", material);
}

// Prints the linked list implementation of a "stk" or "que"
void print_sq_ll(int decPlaces, int hole, int quantity, char material, char rngFill,
                 int largestVal, char dataStruct, char showAddress, FILE **ofp)
{
   int i;  // used for looping

   // Print the first node
   print_sq_ll_node(decPlaces, hole, quantity, material, rngFill, largestVal,
                    dataStruct, (showAddress == 'y') ? 0 : -1, ofp);

   // Determine how many spaces are needed to indent the arrow
   int offset = 1 + (hole / 2); // NOTE: the head of the arrow will be offset without the +1

   // Print the remaining nodes
   for (i = 1; i < quantity; i++)
   {
      // Print the arrow
      if (dataStruct == 's')
         fprintf(*ofp, "%*s/|\\\n%*s|\n%*s|\n", offset - 1, " ", offset, " ", offset, " ");
      else // dataStruct == 'q'
         fprintf(*ofp, "%*s|\n%*s|\n%*s\\|/\n", offset, " ", offset, " ", offset - 1, " ");

      // Print the node
      print_sq_ll_node(decPlaces, hole, quantity, material, rngFill, largestVal,
                       dataStruct, (showAddress == 'y') ? i : -1, ofp);
   }
}

/*
███████ ████████  █████   ██████ ██   ██          ██████  ██    ██ ███████ ██    ██ ███████
██         ██    ██   ██ ██      ██  ██          ██    ██ ██    ██ ██      ██    ██ ██
███████    ██    ███████ ██      █████           ██    ██ ██    ██ █████   ██    ██ █████
     ██    ██    ██   ██ ██      ██  ██          ██ ▄▄ ██ ██    ██ ██      ██    ██ ██
███████    ██    ██   ██  ██████ ██   ██ ███████  ██████   ██████  ███████  ██████  ███████
                                                     ▀▀
*/
// Creates the "stk" and "que" 'dType'
int stack_queue(int quantity, char material, char rngFill, int largestVal, char dataStruct, FILE **ofp)
{
   int hole;  // will keep track of the gaps in the diagram where the data will go
   int retVal = 0;     // will be used for error handling in print_sq_arr()
   int decPlaces = 1;  // will be used to find the length of 'largestVal'
   char type = ' ';    // will be used to determine how the stack or queue is represented
   char showAddress = ' ';  // will be used to determine if node addresses are displayed

   /* Step 1: Determine the values for the variables defined above */

   // Determine decPlaces. NOTE: If largestVal = INT_MIN then decPlaces is already set
   if (largestVal != INT_MIN)
      decPlaces = find_dec_places(largestVal);
   // Now that the number of decimal places is known, 'hole' can be calculated
   hole = 2 + decPlaces;

   /* Step 2: Ask about stack or queue options */

   // Ask the user if they would like an array or a linked list representation
   printf("%s can be represented using arrays or linked lists. ", (dataStruct == 's') ? "Stacks" : "Queues");
   printf("Type 'a' for array representation or 'l' for linked list representation:\n-");
   type = (char)getchar();
   clear_input_buffer();
   // Check for valid user input
   if (type != 'a' && type != 'l')
      return -1;

   // Ask the user if they would like the address of each node to be displayed
   if (type == 'l')
   {
      printf("Would you like the address of each node displayed? (y or n)\n-");
      showAddress = (char)getchar();
      clear_input_buffer();
      // Check for valid user input
      if (showAddress != 'y' && showAddress != 'n')
         return -1;
   }

   /* Step 3: Print the diagram to the output file */

   // Determine what data structure will be used to represent the stack or queue
   if (type == 'a')
      retVal = print_sq_arr(decPlaces, hole, quantity, material, rngFill, largestVal, dataStruct, ofp);
   else // type == 'l'
      print_sq_ll(decPlaces, hole, quantity, material, rngFill, largestVal, dataStruct, showAddress, ofp);

   // TODO: Figure out how to get a retval when ll is selected
   return retVal;
}
