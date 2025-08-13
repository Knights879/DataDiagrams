// ==================================================================
// structs.c
// By Austin T. (Github: Knights879)
// ==================================================================
// Implements the struct node diagram (sn) and
// array of struct nodes diagram (aos)
// ==================================================================

#include "DataDiagrams.h"

/*
Explanation for calculating the length of the longest line to get 'size'
------------------------------------------------------------------------
names:
   0: var name of the struct
   1-3: var names of the ints
   4-6: var names of the doubles
   7-9: var names of the chars

length of struct name line:
   '| name: "names[0].length" |'
      = 12 + names[0].length
length of var name lines
   '| name: "names[1-9].length" |'
      = 12 + max(names[i].length)
length of data type lines:
   '| -type: "int" |'
      = 16
   '| -type: "double" |'
      = 19
   '| -type: "char" |'
      = 17
length of value lines:
   int:
   '| -value: decPlaces |'
      = 12 + decPlaces
   double:
   '| -value: decPlaces |'
      = 12 + decPlaces
   char:
   '| -value: A |'
      = 12 + 1 = 13
*/
// Sets up the local var 'size' for struct_node() and arr_of_structs()
static int get_size(char *names[MAX_NUM_CUSTOM_STRUCT_NAMES], int nums[3], double dubs[3], char chars[3], int decPlaces)
{
   int i = 0;  // loop index
   int tempLen = 0;  // the length of the current custom value
   int currMax = 0;  // the length of the current longest line

   // Check the names
   while (i < MAX_NUM_CUSTOM_STRUCT_NAMES)
   {
      if (names[i] != NULL)
      {
         // NOTE: sizeof(str) would return the amount of memory allocated for a string,
         //       whereas strlen(str) will return the number of characters in a string.
         tempLen = (int)strlen(names[i]) + 12;  // So we only have to calculate it once

         // Update the current longest line, if necessary
         if (tempLen > currMax)
            currMax = tempLen;
      }

      // Increment
      i++;  // Could put the '++' in the strlen() call but better here for readability
   }
   // Reset i
   i = 0;

   // Check the integers
   // First, check the type line (if there is at least one int)
   if (currMax < 16 && nums [0] != INT_MIN)
      currMax = 16;
   // Last, check the value lines (if there are any ints)
   while (i < 3 && nums[i] != INT_MIN)
   {
      tempLen = find_dec_places(nums[i]) + 12;

      if (tempLen > currMax)
         currMax = tempLen;

      i++;
   }
   i = 0;

   // Check the doubles
   // First, check the type line (if there is at least one double)
   if (currMax < 19 && dubs[0] != DBL_MIN)
      currMax = 19;
   // Last, check the value lines (if there are any doubles)
   while (i < 3 && dubs[i] != DBL_MIN)
   {
      char tempString[decPlaces + 1];  // used to ensure proper length of user decimal values
      snprintf(tempString, sizeof(tempString), "%f", dubs[i]);
      tempLen = (int)strlen(tempString) + 12;

      if (tempLen > currMax)
         currMax = tempLen;

      i++;
   }
   i = 0;

   // Check the characters
   // First, check the type line (if there is at least one char)
   if (currMax < 17 && chars[0] != CHAR_MIN)
      currMax = 17;
   // Last, check the value lines (if there are any chars)
   while (i < 3 && chars[i] != CHAR_MIN)
   {
      tempLen = 13;  // Single character so 1 + 12

      if (tempLen > currMax)
         currMax = tempLen;

      i++;
   }

   return currMax;
}

/*
███████ ████████ ██████  ██    ██  ██████ ████████     ███    ██  ██████  ██████  ███████
██         ██    ██   ██ ██    ██ ██         ██        ████   ██ ██    ██ ██   ██ ██
███████    ██    ██████  ██    ██ ██         ██        ██ ██  ██ ██    ██ ██   ██ █████
     ██    ██    ██   ██ ██    ██ ██         ██        ██  ██ ██ ██    ██ ██   ██ ██
███████    ██    ██   ██  ██████   ██████    ██        ██   ████  ██████  ██████  ███████
*/
// Used for making struct nodes
int struct_node(int quantity, char material, char rngFill, int largestVal, FILE **ofp)
{
   int i;  // index in for loops
   int j;  // keeps track of stop and a second index for looping
   int size;  // used to calculate 'topAndBot' and 'inside'
   int stop = 0;  // will determine when to stop printing 'inside' between variables
   int decision = 0;   // used for setting up custom structs (if needed)
   int decPlaces = 1;  // used to find the "length" of largestVal
   char custom = ' ';  // used to determine if the user wants to custom fill the struct
   char showAddress = ' ';  // used to determine if node addresses are displayed
   char *inside;     // will store seperator between variables inside the diagram
   char *topAndBot;  // will store the top and bottom of the diagram
   char *names[MAX_NUM_CUSTOM_STRUCT_NAMES];     // stores custom variable names (if needed)
   int nums[3] = { INT_MIN, INT_MIN, INT_MIN };  // stores custom ints (if needed)
   char chars[3] = { CHAR_MIN, CHAR_MIN, CHAR_MIN };  // stores custom chars (if needed)
   double dubs[3] = { DBL_MIN, DBL_MIN, DBL_MIN };    // stores custom doubles (if needed)
   char input[11];  // stores the user's input
   // TODO: Try using a 'roof' and 'wall' char to potentially simplify printing

   /* Step 1: Determine the values for the variables defined above */

   decPlaces = find_dec_places(largestVal);

   // Null-initialize 'names'
   for (i = 0; i < MAX_NUM_CUSTOM_STRUCT_NAMES; i++)
      names[i] = NULL;

   // Ask the user if they would like the address of each node to be displayed
   printf("Would you like the address of each node displayed? (y or n)\n-");
   showAddress = (char)getchar();
   clear_input_buffer();
   // Check for valid user input
   if (showAddress != 'y' && showAddress != 'n')
      return -1;

   // Ask the user if they would like to create a custom struct
   printf("Would you like to create custom member variables for the struct, or use ");
   printf("a default template?\nThe default will include an 'int', 'double', and 'char*'.");
   printf("\n(y = custom, n = default)\n-");
   custom = (char)getchar();
   clear_input_buffer();
   // Check for valid user input
   if (custom != 'y' && custom != 'n')
      return -1;

   // If the user wants a custom struct, ask them for the setup
   if (custom == 'y')
   {
      // First, ask how many variables they want
      printf("For custom structs, you can have up to three of each of the following data types:\n");
      printf("- int\n- double\n- char\n");

      // Ask about integers
      printf("How many integers would you like? (Type '0', '1', '2', or '3')\n-");
      if (fgets(input, sizeof(input), stdin) == NULL)
         return -1;
      // Convert to integer
      decision = (int)strtol(input, NULL, 10);
      // Check for valid user input
      if (decision > 3 || decision < 0)
         return -1;
      // Update 'nums'
      for (i = 0; i < decision; i++)
         nums[i] = 0;
      // Reset decision
      decision = 0;

      // Ask about doubles
      printf("How many doubles would you like? (Type '0', '1', '2', or '3')\n-");
      if (fgets(input, sizeof(input), stdin) == NULL)
         return -1;
      // Convert to integer
      decision = (int)strtol(input, NULL, 10);
      // Check for valid user input
      if (decision > 3 || decision < 0)
         return -1;
      // Update 'dubs'
      for (i = 0; i < decision; i++)
         dubs[i] = 0.0;
      // Reset decision
      decision = 0;

      // Ask about characters
      printf("How many characters would you like? (Type '0', '1', '2', or '3')\n-");
      if (fgets(input, sizeof(input), stdin) == NULL)
         return -1;
      // Convert to integer
      decision = (int)strtol(input, NULL, 10);
      // Check for valid user input
      if (decision > 3 || decision < 0)
         return -1;
      // Update 'chars'
      for (i = 0; i < decision; i++)
         chars[i] = 'a';
      // Reset decision  (Not currently needed since 'decision' isn't used again)
      decision = 0;

      // If manual, ask user to input values
      if (rngFill == 'm')
      {
         int maxVal = 1;  // the maximum value represented by 'decPlaces' digits
         int minVal = 1;  // the minimum value represented by 'decPlaces' digits
         long tempLong = 0L;
         char tempChar = 'a';
         double tempDouble = 0.0;

         // Calculate 'maxVal'
         for (i = 0; i < decPlaces; i++)
            maxVal *= 10;
         maxVal -= 1;
         // Calculate 'minVal'
         for (i = 0; i < decPlaces - 1; i++)
            minVal *= 10;
         minVal = 0 - (minVal - 1);

         // Initialize the name of the struct
         names[0] = (char *)malloc(sizeof(char) * MAX_CUSTOM_STRUCT_NAME_LEN + 1);
         if (names[0] == NULL)  // Check that malloc() worked
            return 1;

         // Ask the user to name the struct
         printf("Enter a name for the struct. (Max length of %d)\n-", MAX_CUSTOM_STRUCT_NAME_LEN);
         if (fgets(input, 11, stdin) == NULL)
         {
            free(names[0]);  // Don't forget to free!
            return -1;
         }
         // Remove the newline character from the string for comparison
         input[(int)strcspn(input, "\n")] = '\0';
         // Copy the input into the 'names' array
         strncpy(names[0], input, strlen(input));

         // Ints
         for (i = 0; i < 3; i++)
         {
            // Check to see if the user has any integers remaining
            if (nums[i] == INT_MIN)
               break;

            // Initialize the name
            names[i + 1] = (char *)malloc(sizeof(char) * MAX_CUSTOM_STRUCT_NAME_LEN + 1);
            if (names[i + 1] == NULL)  // Check that malloc() worked
            {
               for (j = 0; j < i + 1; j++)
                  free(names[j]);
               return -1;
            }

            // Ask the user to name the variable
            printf("Enter a name for the ");
            if (i == 0)
               printf("first ");
            else if (i == 1)
               printf("second ");
            else  // i == 2
               printf("third ");
            printf("integer variable. (Max length of %d)\n-", MAX_CUSTOM_STRUCT_NAME_LEN);
            if (fgets(input, 11, stdin) == NULL)
            {
               for (j = 0; j <= i + 1; j++)
                  free(names[j]);
               return -1;
            }
            // Remove the newline character from the string for comparison
            input[(int)strcspn(input, "\n")] = '\0';
            // Copy the input into the 'names' array
            strncpy(names[i + 1], input, strlen(input));

            // Ask the user to enter a valid integer
            printf("Enter an integer between %d and %d:\n-", minVal, maxVal);
            if (fgets(input, 11, stdin) == NULL)
            {
               for (j = 0; j <= i + 1; j++)
                  free(names[j]);
               return -1;
            }
            // Convert the string to a long
            tempLong = strtol(input, NULL, 10);
            // Check for valid user input
            if (tempLong < (long)minVal || tempLong > (long)maxVal)
            {
               for (j = 0; j <= i + 1; j++)
                  free(names[j]);
               return -1;
            }
            else  // If valid, add it to the array
               nums[i] = (int)tempLong;
         }

         // Doubles
         for (i = 0; i < 3; i++)
         {
            // Check to see if the user has any doubles remaining
            if (dubs[i] == DBL_MIN)
               break;

            // Initialize the name
            names[i + 4] = (char *)malloc(sizeof(char) * MAX_CUSTOM_STRUCT_NAME_LEN + 1);
            if (names[i + 4] == NULL)  // Check that malloc() worked
            {
               for (j = 0; j < i + 4; j++)
                  free(names[j]);
               return -1;
            }

            // Ask the user to name the variable
            printf("Enter a name for the ");
            if (i == 0)
               printf("first ");
            else if (i == 1)
               printf("second ");
            else // i == 2
               printf("third ");
            printf("double variable. (Max length of %d)\n-", MAX_CUSTOM_STRUCT_NAME_LEN);
            if (fgets(input, 11, stdin) == NULL)
            {
               // NOTE: May unnecessarily run on int names that weren't initialized
               for (j = 0; j <= i + 4; j++)
                  free(names[j]);
               return -1;
            }
            // Remove the newline character from the string for comparison
            input[(int)strcspn(input, "\n")] = '\0';
            // Copy the input into the 'names' array
            strncpy(names[i + 4], input, strlen(input));

            // Ask the user to enter a valid double
            // TODO: Update to give them 2 * decPlaces ???
            printf("NOTE: The '.' and, if applicable, the negative sign WILL count as decimal places.\n");
            printf("Enter a floating point number with at most %d digits:\n-", decPlaces);
            if (fgets(input, 11, stdin) == NULL)
            {
               for (j = 0; j <= i + 4; j++)
                  free(names[j]);
               return -1;
            }
            // Convert the string to a double
            tempDouble = strtod(input, NULL);
            // Check for valid user input
            if (find_double_len(decPlaces, tempDouble) > decPlaces)
            {
               for (j = 0; j <= i + 4; j++)
                  free(names[j]);
               return -1;
            }
            else  // If valid, add it to the array
               dubs[i] = tempDouble;
         }

         // Chars
         for (i = 0; i < 3; i++)
         {
            // Check to see if the user has any characters remaining
            if (chars[i] == CHAR_MIN)
               break;

            // Initialize the name
            names[i + 7] = (char *)malloc(sizeof(char) * MAX_CUSTOM_STRUCT_NAME_LEN + 1);
            if (names[i + 7] == NULL)  // Check that malloc() worked
            {
               for (j = 0; j < i + 7; j++)
                  free(names[j]);
               return -1;
            }

            // Ask the user to name the variable
            printf("Enter a name for the ");
            if (i == 0)
               printf("first ");
            else if (i == 1)
               printf("second ");
            else // i == 2
               printf("third ");
            printf("character variable. (Max length of %d)\n-", MAX_CUSTOM_STRUCT_NAME_LEN);
            if (fgets(input, 11, stdin) == NULL)
            {
               // NOTE: May unnecessarily run on int and double names that weren't initialized
               for (j = 0; j <= i + 7; j++)
                  free(names[j]);
               return -1;
            }
            // Remove the newline character from the string for comparison
            input[(int)strcspn(input, "\n")] = '\0';
            // Copy the input into the 'names' array
            strncpy(names[i + 7], input, strlen(input));

            // Ask the user to enter a valid character
            printf("Enter a printable character:\n-");
            tempChar = (char)getchar();
            clear_input_buffer();
            // Check for valid user input
            if (!isprint(tempChar))
            {
               for (j = 0; j <= i + 7; j++)
                  free(names[j]);
               return -1;
            }
            else  // If valid, add it to the array
               chars[i] = tempChar;
         }
      }
      else  // 'rngFill' == ', randomly generate them
      {
         names[0] = (char *)malloc(sizeof(char) * MAX_CUSTOM_STRUCT_NAME_LEN + 1);
         if (names[0] == NULL)  // Check that malloc() worked
            return -1;

         snprintf(names[0], sizeof(char) * 7, "struct");

         // For each index, generate values for each of the arrays, as needed
         for (i = 0; i < 3; i++)
         {
            // Check to see if the user has remaining variables for type
            // If yes, generate a random value, else, move on
            if (nums[i] != INT_MIN)
            {
               // Create the name for the int variable
               names[i + 1] = (char *)malloc(sizeof(char) * MAX_CUSTOM_STRUCT_NAME_LEN + 1);
               if (names[i + 1] == NULL)  // Check that malloc() worked
               {
                  for (j = 0; j < i + 1; j++)
                     free(names[j]);
                  return -1;
               }
               snprintf(names[i + 1], sizeof(char) * 5, "num%d", i + 1);

               // Generate the value for the int variable
               nums[i] = get_rand_int(largestVal);  // FIXME: Doesn't allow for negatives
            }
            if (dubs[i] != DBL_MIN)
            {
               // Create the name for the double variable
               names[i + 4] = (char *)malloc(sizeof(char) * MAX_CUSTOM_STRUCT_NAME_LEN + 1);
               if (names[i + 4] == NULL)  // Check that malloc() worked
               {
                  for (j = 0; j < i + 4; j++)
                     free(names[j]);
                  return -1;
               }
               snprintf(names[i + 4], sizeof(char) * 6, "data%d", i + 1);

               // Generate the value for the double variable
               dubs[i] = (double)get_rand_int(largestVal / 100);  // FIXME: Temp solution
            }
            if (chars[i] != CHAR_MIN)
            {
               // Create the name for the character variable
               names[i + 7] = (char *)malloc(sizeof(char) * MAX_CUSTOM_STRUCT_NAME_LEN + 1);
               if (names[i + 7] == NULL)  // Check that malloc() worked
               {
                  for (j = 0; j < i + 7; j++)
                     free(names[j]);
                  return -1;
               }
               snprintf(names[i + 7], sizeof(char) * 6, "char%d", i + 1);

               // Generate the value for the character variable
               chars[i] = get_rand_printable();
            }
         }
      }
   }

   // Calculate 'stop'
   for (i = 0; i < 3; i++)
   {
      if (nums[i] != INT_MIN)
         stop++;
      if (dubs[i] != DBL_MIN)
         stop++;
      if (chars[i] != CHAR_MIN)
         stop++;
   }

   // Calculate 'size'
   size = get_size(names, nums, dubs, chars, decPlaces);

   // Initialize 'inside'
   inside = (char *)malloc(sizeof(char) * size + 1);
   if (inside == NULL)  // Check that malloc() worked
   {
      for (i = 0; i < MAX_NUM_CUSTOM_STRUCT_NAMES; i++)
         free(names[i]);
      return 1;
   }
   // Create 'inside' (Could call create_topAndBot())
   if (material == '#')
   {
      // snprintf(inside, sizeof(inside), "# %*s #", size - 4, "#");
      inside[0] = '#';
      inside[1] = ' ';
      for (i = 2; i < size - 2; i++)
         inside[i] = '#';
      inside[size - 2] = ' ';
      inside[size - 1] = '#';
   }
   else  // material == '+'
   {
      // snprintf(inside, sizeof(inside), "| %*s |", size - 4, "-");
      inside[0] = '|';
      inside[1] = ' ';
      for (i = 2; i < size - 2; i++)
         inside[i] = '-';
      inside[size - 2] = ' ';
      inside[size - 1] = '|';
   }
   inside[size] = '\0';  // NOTE: Don't forget the null terminator!

   // Initialize 'topAndBot'
   topAndBot = (char *)malloc(sizeof(char) * size + 1);
   if (topAndBot == NULL)  // Check that malloc() worked
   {
      for (i = 0; i < MAX_NUM_CUSTOM_STRUCT_NAMES; i++)
         free(names[i]);
      free(inside);
      return 1;
   }
   // Create 'topAndBot'
   if (material == '#')
   {
      for (i = 0; i < size; i++)
         topAndBot[i] = '#';
   }
   else  // material == '+'
   {
      topAndBot[0] = '+';
      for (i = 1; i < size - 1; i++)
         topAndBot[i] = '-';
      topAndBot[size - 1] = '+';
   }
   topAndBot[size] = '\0';  // NOTE: Don't forget the null terminator!

   /* Step 2: Print the diagram */

   // Print the address (if necessary) (kinda useless with only one struct)
   // NOTE: If 'MAX_NUM_STRUCT_NODES' is increased, this logic needs to be changed
   if (showAddress == 'y')
      fprintf(*ofp, "0x000\n");

   // Print the name section of the struct
   fprintf(*ofp, "%s\n", topAndBot);
   fprintf(*ofp, "| name: '%s'%*s|\n", names[0], size - 11 - (int)strlen(names[0]), "");
   fprintf(*ofp, "%s\n", topAndBot);

   // Print the variables of the struct
   for (i = 1, j = 0; i < MAX_NUM_CUSTOM_STRUCT_NAMES; i++)
   {
      // If element is not NULL, then that var needs to be printed
      if (names[i] != NULL)
      {
         // Print the name of the variable
         fprintf(*ofp, "| name: '%s'%*s|\n", names[i], size - 11 - (int)strlen(names[i]), "");

         // Print the type of the variable
         if (i < 4)  // int
            fprintf(*ofp, "| -type: 'int'%*s|\n", size - 15, "");
         else if (i < 7)  // double
            fprintf(*ofp, "| -type: 'double'%*s|\n", size - 18, "");
         else  // char
            fprintf(*ofp, "| -type: 'char'%*s|\n", size - 16, "");

         // Print the value of the variable
         if (i < 4)  // int
            fprintf(*ofp, "| -value: %d%*s|\n", nums[i - 1], size - 11 - find_dec_places(nums[i - 1]), "");
         else if (i < 7)  // double
            fprintf(*ofp, "| -value: %.*f%*s|\n",
                    decPlaces - 1 - find_dec_places((int)dubs[i - 4]), dubs[i - 4],
                    size - 11 - find_double_len(decPlaces, dubs[i - 4]), "");
         else  // char
            fprintf(*ofp, "| -value: %c%*s|\n", chars[i - 7], size - 12, "");

         // Print the seperator between variables
         if (j < stop - 1)  // We don't want to print one if its the last variable
            fprintf(*ofp, "%s\n", inside);

         // Increment
         j++;
      }
      // Else the element is NULL, and that var wasn't requested, so we move on
   }

   // Print the bottom of the diagram
   fprintf(*ofp, "%s\n", topAndBot);

   /* Step 3: Clean up */

   // NOTE: ALWAYS remember to free any dynamically allocated memory
   free(inside);
   free(topAndBot);
   for (i = 0; i < MAX_NUM_CUSTOM_STRUCT_NAMES; i++)
      free(names[i]);  // free() does nothing if the argument is already null

   return 0;
}

/*
 █████  ██████  ██████       ██████  ███████     ███████ ████████ ██████  ██    ██  ██████ ████████ ███████
██   ██ ██   ██ ██   ██     ██    ██ ██          ██         ██    ██   ██ ██    ██ ██         ██    ██
███████ ██████  ██████      ██    ██ █████       ███████    ██    ██████  ██    ██ ██         ██    ███████
██   ██ ██   ██ ██   ██     ██    ██ ██               ██    ██    ██   ██ ██    ██ ██         ██         ██
██   ██ ██   ██ ██   ██      ██████  ██          ███████    ██    ██   ██  ██████   ██████    ██    ███████
*/
// Used for making an array of struct nodes
int arr_of_structs(int quantity, char material, char rngFill, int largestVal, FILE **ofp)
{
   // TODO

   return 0;
}
