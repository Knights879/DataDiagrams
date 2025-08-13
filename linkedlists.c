// ==================================================================
// linkedlists.c
// By Austin T. (Github: Knights879)
// ==================================================================
// Implements the linked list diagram (ln) and
// array of linked lists diagram (aol)
// ==================================================================

#include "DataDiagrams.h"

/*
██      ██ ███    ██ ██   ██ ███████ ██████      ██      ██ ███████ ████████
██      ██ ████   ██ ██  ██  ██      ██   ██     ██      ██ ██         ██
██      ██ ██ ██  ██ █████   █████   ██   ██     ██      ██ ███████    ██
██      ██ ██  ██ ██ ██  ██  ██      ██   ██     ██      ██      ██    ██
███████ ██ ██   ████ ██   ██ ███████ ██████      ███████ ██ ███████    ██
*/
// Creates the "ln" 'dType'
int linked_list(int quantity, char material, char rngFill, int largestVal, FILE **ofp)
{
   int i = 0;  // will be used for loops
   int hole;   // will keep track of the gaps in the diagram where the data will go
   int decPlaces = 1;   // will be used to find the "length" of largestVal
   int firstCaretLoc;   // will be used for labeling (if needed)
   int secondCaretLoc;  // will be used for labeling (if needed)
   char roof;  // will be the character used on the top and bottom of each node
   char wall;  // will be the character used on the side of each node
   char showAddress = ' ';  // will be used to determine if node addresses are displayed

   /* Step 1: Determine the values for the variables defined above */

   // Determine decPlaces. NOTE: If largestVal = INT_MIN then decPlaces is already set
   if (largestVal != INT_MIN)
      decPlaces = find_dec_places(largestVal);
   // Now that the number of decimal places is known, 'hole' can be calculated
   hole = 2 + decPlaces;

   // Determine the location of the carets
   firstCaretLoc = 1 + (hole / 2);
   secondCaretLoc = ((hole + 2) * quantity + (quantity - 1) * 6) - (hole / 2) - (hole % 2);

   // Determine the roof and wall materials
   roof = (material == '+') ? '-' : '#';
   wall = (material == '+') ? '|' : '#';

   // Ask the user if they would like the address of each node to be displayed
   printf("Would you like the address of each node displayed? (y or n)\n-");
   showAddress = (char)getchar();
   clear_input_buffer();

   // Check for valid user input
   if (showAddress != 'y' && showAddress != 'n')
      return -1;

   /* Step 2: Print the diagram to the output file */

   // Print the addresses (if necessary)
   if (showAddress == 'y')
   {
      // Print the first address
      fprintf(*ofp, "%*s0x000", (hole < 5) ? 0 : 1 + (hole / 2) - 2, " ");
      // Print the remaining addresses
      for (i = 1; i < quantity; i++)
         fprintf(*ofp, "%*s0x%03d", hole + 3, " ", i);
      // NOTE: Don't forget the newline!
      fprintf(*ofp, "\n");
   }

   // Print the top of the nodes
   for (i = 0; i < quantity - 1; i++)
      fprintf(*ofp, "%c%*c%c      ", material, hole, roof, material);
   fprintf(*ofp, "%c%*c%c\n", material, hole, roof, material);

   // Print the middle of the nodes
   for (i = 0; i < quantity - 1; i++)
   {
      if (rngFill == 'y')
         fprintf(*ofp, "%c %*d %c ---> ", wall, decPlaces, get_rand_int(largestVal), wall);
      else // rngFill == 'n'
         fprintf(*ofp, "%c %*s %c ---> ", wall, decPlaces, " ", wall);
   }
   // Print the middle of the last node
   if (rngFill == 'y')
      fprintf(*ofp, "%c %*d %c\n", wall, decPlaces, get_rand_int(largestVal), wall);
   else // rngFill == 'n'
      fprintf(*ofp, "%c %*s %c\n", wall, decPlaces, " ", wall);

   // NOTE: Notice that we could have printed the last node in the for loop with
   //       all the others by changing the end of the string to be printed, the
   //       " ---> ", to be "%s" and then make the corresponding additional argument,
   //       (i == quantity - 1) ? " ---> " : "\n". But doing this would make the
   //       fprintf longer, hurting readability, and would require an additional
   //       conditional check for every iteration, when it's only needed at the end

   // Print the bottom of the nodes
   for (i = 0; i < quantity - 1; i++)
      fprintf(*ofp, "%c%*c%c      ", material, hole, roof, material);
   fprintf(*ofp, "%c%*c%c\n", material, hole, roof, material);

   // Print the labels for the head and tail
   if (quantity == 1) // NOTE: No tail label in this case
      fprintf(*ofp, "%*s^\n%*s%s\n", firstCaretLoc, " ", firstCaretLoc - 3, " ", "head");
   else // quantity > 1
   {
      // Print the carets
      fprintf(*ofp, "%*s^%*s^\n", firstCaretLoc, " ", secondCaretLoc, " ");
      // Print the labels
      fprintf(*ofp, "%*s%s%*s%s\n", firstCaretLoc - 1, " ", "head",
              secondCaretLoc - 1 - firstCaretLoc + 3, " ", "tail");
   }

   return 0;
}

/*
 █████  ██████  ██████      ██      ██ ███    ██ ██   ██ ███████ ██████      ██      ██ ███████ ████████
██   ██ ██   ██ ██   ██     ██      ██ ████   ██ ██  ██  ██      ██   ██     ██      ██ ██         ██
███████ ██████  ██████      ██      ██ ██ ██  ██ █████   █████   ██   ██     ██      ██ ███████    ██
██   ██ ██   ██ ██   ██     ██      ██ ██  ██ ██ ██  ██  ██      ██   ██     ██      ██      ██    ██
██   ██ ██   ██ ██   ██     ███████ ██ ██   ████ ██   ██ ███████ ██████      ███████ ██ ███████    ██
*/
// Creates the "aol" 'dType'
int arr_of_linked_lists(int quantity, char material, char rngFill, int largestVal, FILE **ofp)
{
   //

   return 0;
}
