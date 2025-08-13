// ==================================================================
// arrays.c
// By Austin T. (Github: Knights879)
// ==================================================================
// Implements the array diagram (arr) and 2D array diagram (2da)
// ==================================================================

#include "DataDiagrams.h"

// Sets up the local vars for arr() and two_d_arr()
// NOTE: Since largestVal and quantity are not being updated they can be passed
//       by value
static void set_local_vars(int largestVal, int quantity, int *decPlaces, int *hole, int *size)
{
   // Determine decPlaces. NOTE: If largestVal = INT_MIN then decPlaces is already set
   if (largestVal != INT_MIN)
      *decPlaces = find_dec_places(largestVal);

   // Now that the number of decimal places is known, "hole" can be calculated
   *hole = 2 + *decPlaces;

   // Now find size
   *size = 1 + (*hole + 1) * quantity;
}

// Creates the top and bottom of the array diagram
void create_topAndBot(int decPlaces, int size, char material, char *topAndBot)
{
   int i;  // used for looping

   if (material == '#')
   {
      for (i = 0; i < size; i++)
         topAndBot[i] = '#';
   }
   else if (material == '+')
   {
      for (i = 0; i < size; i++)
      {
         // Adding 3 to decPlaces will give the indices of the '+'
         // NOTE: 0 % n = 0 for any positive integer n
         if (i % (decPlaces + 3) == 0)
            topAndBot[i] = '+';
         else
            topAndBot[i] = '-';
      }
   }
   else
   {
      printf("Wut. material = '%c' %d\n", material, (int)material);
      topAndBot = NULL;
      return;
   }

   topAndBot[size] = '\0';  // NOTE: Don't forget the null terminator!
}

/*
 █████  ██████  ██████
██   ██ ██   ██ ██   ██
███████ ██████  ██████
██   ██ ██   ██ ██   ██
██   ██ ██   ██ ██   ██
*/
// Creates the "arr" 'dType'
int arr(int quantity, char material, char rngFill, int largestVal, FILE **ofp)
{
   int i = 0;  // used in for loops
   int size;   // used to calculate 'topAndBot'
   int hole;   // the space needed to represent data entries in the diagram
   int decPlaces = 1;  // used to find the length of 'largestVal'
   char *topAndBot;    // stores the top and bottom of the diagram

   /* Step 1: Determine the values for the variables defined above */

   set_local_vars(largestVal, quantity, &decPlaces, &hole, &size);

   // Use 'size' to alloc space for 'topAndBot'
   topAndBot = malloc(sizeof(char) * size + 1);
   // You should always check to make sure malloc() did not return NULL
   if (topAndBot == NULL)
      return 1;
   // Create the string that represents 'topAndBot'
   create_topAndBot(decPlaces, size, material, topAndBot);
   // Check to see if error occured in create_topAndBot()
   if (topAndBot == NULL)
      return 1;

   /* Step 2: Print the diagram to the output file */

   // Print the indices
   fprintf(*ofp, "%*s%d", 1 + (hole / 2), " ", i);
   for (i = 1; i < quantity; i++)
      fprintf(*ofp, "%*s%d", (hole / 2) + 1 + (hole / 2), " ", i);

   // Print the top of the array diagram and the first wall
   fprintf(*ofp, "\n%s\n%c", topAndBot, (material == '+') ? '|' : '#');

   // Print the middle of the array diagram
   for (i = 0; i < quantity; i++)
   {
      if (rngFill == 'y')
         fprintf(*ofp, " %*d %c", decPlaces, get_rand_int(largestVal), (material == '+') ? '|' : '#');
      else // rngFill == 'n'
         fprintf(*ofp, " %*s %c", decPlaces, " ", (material == '+') ? '|' : '#');
   }

   // Print the bottom of the array diagram
   fprintf(*ofp, "\n%s\n", topAndBot);

   /* Step 3: Clean up */

   // NOTE: ALWAYS remember to free any dynamically allocated memory
   free(topAndBot);

   return 0;
}

/*
██████  ██████       █████  ██████  ██████
     ██ ██   ██     ██   ██ ██   ██ ██   ██
 █████  ██   ██     ███████ ██████  ██████
██      ██   ██     ██   ██ ██   ██ ██   ██
███████ ██████      ██   ██ ██   ██ ██   ██
*/
// Creates the "2da" 'dType'
// NOTE: Ideally, Step 2 occurs before Step 1, but it can't because 'sizOfIndex' depends
//       on 'numRows' and 'numCols' to be known.
int two_d_arr(int quantity, char material, char rngFill, int largestVal, FILE **ofp)
{
   int i, j;     // used as looping variables
   int size;     // used to calculate 'topAndBot'
   int hole;     // keeps track of the gaps in the diagram where the data will go
   int numCols;  // the number of columns in the diagram
   int numRows;  // the number of rows in the 2D array
   int decPlaces = 1;     // used to find the "length" of largestVal
   int largestIndex = 0;  // represents the number of decimal places of the largest index
   char displayIndices;   // stores user input
   char indexInDiagram;   // stores user input
   char *topAndBot;       // stores the top and bottom of the diagram
   char input[11];        // stores the user's inputs

   /* Step 1: Ask about the dimension of the 2D array and printing options */

   // Ask the user for the dimensions of the 2D array
   printf("\nYou specified the quantity to be %d.\n", quantity);
   printf("The diagram to represent the 2D array will be of the form, a[n][m], ");
   printf("where 'n' is the number of rows and 'm' is the number of columns.\n");
   printf("Please enter two numbers, in the range [1, 100), in the form - # #\n- ");
   if (fgets(input, 11, stdin) == NULL)
      return -1;
   sscanf(input, "%d %d", &numRows, &numCols);

   // Check for valid user input
   if (numRows < 1 || numRows > 99 || numCols < 1 || numCols > 99)
      return -1;

   // Ask the user if they would like indices to be diplayed
   printf("Would you like the indices to be displayed on the sides of the diagram? (y or n) -");
   displayIndices = (char)getchar();
   clear_input_buffer();
   // Check for valid user input
   if (displayIndices != 'y' && displayIndices != 'n')
      return -1;

   // Ask the user if they would like to have the indices displayed in the cells
   if (displayIndices == 'y' && rngFill == 'n')
   {
      printf("Since you specified you do not want random values to fill the diagram and ");
      printf("would like indices to be displayed, would you like the indices to be displayed ");
      printf("inside the diagram? (NOTE: this may change the size of each cell.) (y or n) -");
      indexInDiagram = (char)getchar();
      clear_input_buffer();
      // Check for valid user input
      if (indexInDiagram != 'y' && indexInDiagram != 'n')
         return -1;
   }

   // If indices are to be printed, then determine if largestVal has to be adjusted when:
   // Indices to be printed in margin
   if ((displayIndices == 'y' && indexInDiagram == 'n') && largestVal < 1000)
      largestVal = 1000;
   // Indices to be printed in diagram
   if (indexInDiagram == 'y' && (largestVal < 1000 || largestVal > 9999))
      largestVal = 1000;

   /* Step 2: Determine the values for the variables defined above */

   // Find out the largest index value for spacing purposes
   largestIndex = (numRows > numCols) ? find_dec_places(numRows) : find_dec_places(numCols);

   // We need to check if the indices are to be printed around the diagram.
   // If yes, we need to make sure that "hole" will be large enough, otherwise the
   // indices might start to not line up properly above their appropriate columns
   if (displayIndices == 'y' && indexInDiagram == 'n')
   {
      // Find decPlaces
      decPlaces = find_dec_places(largestVal);

      // This loop will make decPlaces a valid size if it is not already
      while (decPlaces + 2 < (2 * largestIndex) + 4)
         decPlaces++;

      // Now set the local vars
      set_local_vars(INT_MIN, numCols, &decPlaces, &hole, &size);
      // ??? TODO: Will INT_MIN be a problem since quantity was set to INT_MIN in main
   }
   else // No need to worry about such adjustments
      set_local_vars(largestVal, numCols, &decPlaces, &hole, &size);

   // Use 'size' to alloc space for 'topAndBot'
   topAndBot = malloc(sizeof(char) * size + 1);
   // You should also check to make sure malloc() did not return NULL
   if (topAndBot == NULL)
      return 2;
   // Create the string that represents 'topAndBot'
   create_topAndBot(decPlaces, size, material, topAndBot);
   // Check to see if error occured in create_topAndBot()
   if (topAndBot == NULL) // NOTE: Is this necessary?
      return 2;

   /* Step 3: Print the diagram to the output file */

   // LABEL: 00 | Print with indices
   if (displayIndices == 'y')
   {
      fprintf(*ofp, "Given a 2D array named \"a\", \"a\" can be thought of as an ");
      fprintf(*ofp, "ixj matrix (i rows, j columns).\n");
      fprintf(*ofp, "a[%d][%d] - %d x %d\n\n", numRows, numCols, numRows, numCols);

      // LABEL: -00a | Indices will be put in the diagram
      if (indexInDiagram == 'y')
      {
         // Print the top and middle of the diagram
         for (i = 0; i < numRows; i++)
         {
            // Print the top of the array diagram and the first wall
            fprintf(*ofp, "%s\n%c", topAndBot, (material == '+') ? '|' : '#');

            // Print the body of the diagram
            for (j = 0; j < numCols; j++)
               fprintf(*ofp, "[%d][%d]%c", i, j, (material == '+') ? '|' : '#');

            fprintf(*ofp, "\n");
         }

         // Print the bottom of the diagram
         fprintf(*ofp, "%s\n", topAndBot);
      }
      // LABEL: -00b | Indices will be around the margins
      else
      {
         // First print the column indices
         fprintf(*ofp, "%*s", (2 * largestIndex) + 4 + 2, " ");

         for (i = 0; i < numCols; i++)
         {
            // Print the indices
            fprintf(*ofp, "[%*d][%*d]", largestIndex, 0, largestIndex, i);
            // Print the spaces inbetween the indices
            fprintf(*ofp, "%*s", (hole + 1) - (2 * largestIndex + 4), " ");
         }

         fprintf(*ofp, "\n");

         // Then print the top and body of the array diagram
         for (i = 0; i < numRows; i++)
         {
            // Print the 'topAndBot' bar
            fprintf(*ofp, "%*s %s\n", (2 * largestIndex) + 4, " ", topAndBot);
            // Print the row indices
            fprintf(*ofp, "[%*d][%*d] ", largestIndex, i, largestIndex, 0);
            // Print the first wall
            fprintf(*ofp, "%c", (material == '+') ? '|' : '#');

            // Print the cells
            for (j = 0; j < numCols; j++)
            {
               if (rngFill == 'y')
                  fprintf(*ofp, " %*d %c", decPlaces, get_rand_int(largestVal), (material == '+') ? '|' : '#');
               else // rngFill == 'n'
                  fprintf(*ofp, " %*s %c", decPlaces, " ", (material == '+') ? '|' : '#');
            }

            fprintf(*ofp, "\n");
         }

         // Finally print the last line
         fprintf(*ofp, "%*s %s\n", 2 * largestIndex + 4, " ", topAndBot);
      }
   }
   // LABEL: 01 | Print without indices
   else // displayIndices == 'n'
   {
      // Print the top and middle of the diagram
      for (i = 0; i < numRows; i++)
      {
         // Print the top of the array diagram and the first wall
         fprintf(*ofp, "%s\n%c", topAndBot, (material == '+') ? '|' : '#');

         // Print the body of the diagram
         for (j = 0; j < numCols; j++)
         {
            if (rngFill == 'y')
               fprintf(*ofp, " %*d %c", decPlaces, get_rand_int(largestVal), (material == '+') ? '|' : '#');
            else // rngFill == 'n'
               fprintf(*ofp, " %*s %c", decPlaces, " ", (material == '+') ? '|' : '#');
         }

         fprintf(*ofp, "\n");
      }

      // Print the bottom of the diagram
      fprintf(*ofp, "%s\n", topAndBot);
   }

   /* Step 4: Clean up */

   // NOTE: ALWAYS remember to free any dynamically allocated memory
   free(topAndBot);

   return 0;
}
