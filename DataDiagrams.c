// ====================================
// DataDiagrams.c
// By Austin T. (Github: Knights879)
// ====================================

#include "DataDiagrams.h"

// Pre-defined list of names
const char *NAMES[NUM_NAMES] = {
   "Arya", "Bran", "Jon", "Rickon", "Robb", "Sansa", "Eddard",
   "Catelyn", "Dany", "Tyrion", "Bronn", "Jaime", "Cersei",
   "Petyr", "Varys", "Sandor", "Robert", "Tormund", "Samwell",
   "Brienne", "Melisandre", "Missandei", "Davos", "Gendry"
};

void printMenu()
{
   printf("===========================================\n");
   printf("Accepted diagram types:\n");
   printf("\t-array (arr), 2D array (2da), array of lists (aol), array of structures (aos)\n");
   printf("\t-stack (stk), queue (que)\n");
   printf("\t-linked list (ll), struct node (sn), tree (tre), trie (tri)\n");
   printf("\t-note that for node types, \"--->\" will be used to connect nodes to look like a list\n");

   printf("Accepted quantity range: [1, 100)\n");
   printf("\t-note that the results will be printed to a text document\n");
   printf("\t so side scrolling will be possible\n");

   printf("Accepted material:\n");
   printf("\t- '+' for corners, '-' for top and bottom, '|' for the walls\n");
   printf("\t  (USE '+' for this style)\n");
   printf("\t- '#' for everything, NOTE: if specifying in command line, use '\\#'\n");
   printf("\t- '/' for tree structures\n");

   printf("\nNOTE: For future runs you can use the following format to skip some of the questions.\n");
   printf("Proper format: ./[program name] -[diagram type] -[quantity] -[material] ");
   printf("-[rng fill] -[largest value]\n");
   printf("===========================================\n");
}

// Clears 'stdin'
void clear_input_buffer()
{
   int c;
   // Keep getting a char until the input buffer is empty
   do {
      c = getchar();
   } while (c != '\n' && c != EOF);
   // while ((c = getchar()) != '\n' && c != EOF);  // also works
}

// Returns a random int in the range: [0, 'largestVal']
int get_rand_int(int largestVal)
{
   return rand() % (largestVal + 1);
}

// Returns a random lowercase letter
char get_rand_alpha()
{
   // This will get an int from 97 to 122, which corresponds to 'a' to 'z' in ASCII
   return (char)((rand() % 26) + 97);
}

// Returns a random printable character
char get_rand_printable()
{
   // This will get an int from 32 to 126, which corresponds to the printable chars in ASCII
   // NOTE: This includes a space (which has a value of 32)
   return (char)((rand() % 94) + 32);
}

// Returns a random string from "NAMES" (see top of file)
const char * get_rand_string()
{
   return NAMES[rand() % NUM_NAMES];
}

// Returns a random double
double get_rand_dub(int decPlaces)
{
   int i;   // index in for loops
   int sign;   // determines whether the random double will be positive or negative
   int whole;  // represents the digits to the left of the decimal/period
   int wholeSize;  // represents the number of digits to the left of the decimal/period
   int decimal;    // represents the digits to the right of the decimal/period
   int decimalSize;  // represents the number of digits to the right of the decimal/period
   int maxVal = 1;   // stores the largest value allowed for 'whole' and then 'decimal'
   int tempDecP = decPlaces;  // stores the amount of 'decPlaces' currently available for use
   char tempStr[decPlaces + 1];  // used to convert the parts of the random double into 'randDub'
   double randDub;   // the randomly generated double to be returned

   // STEP 1: determine if the number will be positive or negative.
   // Let's make positive more likely (1 in 4), just because
   // If sign == 0, it's negative
   // If sign == 1, 2, or 3, it's positive
   sign = get_rand_int(3);

   // Now we need to update 'tempDecP'
   if (sign == 0)
      tempDecP -= 3;  // If sign is negative, we have one less space to use
   else  // sign == 1, 3, or 3
      tempDecP -= 2;

   // And now we can update 'maxVal'
   for (i = 0; i < tempDecP; i++)
      maxVal *= 10;
   maxVal--;

   // STEP 2: Generate the whole number part.
   whole = get_rand_int(maxVal);
   wholeSize = find_dec_places(whole);

   // Now we need to update 'tempDecP' again
   if (sign == 0)
      tempDecP = decPlaces - wholeSize - 2;
   else  // sign == 1, 2, or 3
      tempDecP = decPlaces - wholeSize - 1;

   // And now we can update 'maxVal' again
   maxVal = 1;  // Reset 'maxVal' so it can be updated correctly
   for (i = 0; i < tempDecP; i++)
      maxVal *= 10;
   maxVal--;

   // STEP 3: Generate the decimal/fraction part.
   decimal = get_rand_int(maxVal);
   decimalSize = find_dec_places(decimal);

   // STEP 4: Create the string from the sign, 'whole', decimal/period, and 'decimal' parts
   if (sign == 0)
   {
      if (wholeSize + decimalSize + 2 > decPlaces)
         return 1.1;

      snprintf(tempStr, sizeof(tempStr), "-%d.%d", whole, decimal);
   }
   else  // sign == 1, 2, or 3
   {
      if (wholeSize + decimalSize + 1 > decPlaces)
         return 1.1;

      snprintf(tempStr, sizeof(tempStr), "%d.%d", whole, decimal);
   }

   // STEP 5: Convert the string to a double
   randDub = strtod(tempStr, NULL);

   // Check just to make sure
   if (find_dec_places(randDub) > decPlaces)
      return 1.1;

   /* Collapsable comment so you can clear up this space on your screen
   // A simpler way to do it, but doesn't control the "size" of the number
   // NOTE: To use this method, you would need to pass 'largestVal' to the function

   // int i;
   // double lower = 1;
   // double upper = largestVal;
   // double randDub;

   // for (i = 0; i < decPlaces - 1; i++)
   //    lower *= 10;
   // lower = 0 - (lower - 1);

   // // l + (u - l) * (rand() % largestVal) / largestVal
   // randDub = lower + (upper - lower) * get_rand_int(largestVal) / largestVal; */

   return randDub;
}

// Finds the number of decimal places of a value
int find_dec_places(int largestVal)
{
   int decPlaces = 1;

   while(largestVal /= 10)
      decPlaces++;

   return decPlaces;
}

// Finds the length of a double
int find_double_len(int decPlaces, double d)
{
   char tempStr[decPlaces + 1];

   snprintf(tempStr, sizeof(tempStr), "%f", d);

   return (int)strlen(tempStr);
}

// Tests if the user entered a valid dType, returns the index if valid, else -1
int is_valid_d_type(char *dType)
{
   int i, numDCodes;
   char dTypeCodes[10][4] = {"arr", "2da", "aol", "aos", "stk", "que", "ll", "sn", "tre", "tri"};

   // This will store the number of dTypeCodes so more can be added later
   // without messing up the for loop below
   numDCodes = sizeof(dTypeCodes) / sizeof(dTypeCodes[0]);

   // Gross runtime TODO: Use hashmap for better performance
   for (i = 0; i < numDCodes; i++)
   {
      if (strcmp(dTypeCodes[i], dType) == 0)
         return i;
   }

   return -1;
}

/*
███████ ███████ ████████ ██    ██ ██████
██      ██         ██    ██    ██ ██   ██
███████ █████      ██    ██    ██ ██████
     ██ ██         ██    ██    ██ ██
███████ ███████    ██     ██████  ██
*/
// Sets up all the settings and returns 0 upon success
int setup(char *dType, int *quantity, char *material, char *rngFill, int *largestVal)
{
   long li;  // used to temp store the user input to a long (because strtol() returns a long)
   char input[11];  // stores the user's inputs
   // char *endP;

   // Set diagram type, if not already set
   if (is_valid_d_type(dType) == -1)
   {
      printf("You either did not enter a diagram type at the command line, ");
      printf("or the diagram type you entered was invalid.\n");
      printf("\nEnter the desired diagram type. -");
      if (fgets(input, sizeof(input), stdin) == NULL)
         return -1;

      // Remove the newline character from the string for comparison
      input[(int)strcspn(input, "\n")] = '\0';

      if (is_valid_d_type(input) == -1)
      {
         printf("\nYou entered an invalid diagram type code. Please see the menu above.\n");
         printf("If there is no menu above, re-run the program with no additional arguments.\n");
         return -1;
      }
      strncpy(dType, input, 3);
      dType[3] = '\0';
   }

   // Set quantity
   // If the user wants a struct node, make sure 'quantity' <= 'MAX_NUM_STRUCT_NODES'
   if (strcmp(dType, "sn") == 0)
   {
      printf("NOTE: For struct node, 'quantity' is limited to %d.\n", MAX_NUM_STRUCT_NODES);
      *quantity = 1;
      // NOTE: If 'MAX_NUM_STRUCT_NODES' is ever changed, this logic needs to be changed
   }
   if (*quantity == INT_MIN)
   {
      printf("Enter the desired number of diagrams. -");
      if (fgets(input, 11, stdin) == NULL)
         return -1;

      // Convert to integer
      li = strtol(input, NULL, 10);

      if (li < 1L || li > 99L)
      {
         printf("\nInvalid range. Valid range is [1, 100).\n");
         return -1;
      }
      *quantity = (int)li;
   }

   // Set material
   if (*material == ' ')
   {
      printf("Enter the desired material. -");
      *material = (char)getchar();
      clear_input_buffer();

      switch (*material)
      {
         case '+': case '#': case '/':
            break;

         case '-': case '|':
            *material = '+';
            printf("Assuming you want to use the +, -, | format. ");
            printf("In future runs please use '+' to indicate this format, not '-' or '|'.\n");
            break;

         default:
            printf("\nInvalid input.\n");
            return -1;
      }
   }

   // Set rngFill
   if (*rngFill == ' ')
   {
      // Ask the user if they want it to be like a template and left empty
      // or if they want rng fill. If rng fill they will have to specify the structure
      // of the diagrams they want printed (so that program knows what data types to generate).
      printf("Would you like randomly generated values to be inserted in the diagrams. (y or n) -");
      *rngFill = (char)getchar();
      clear_input_buffer();

      if (*rngFill != 'y' && *rngFill != 'n')
      {
         printf("\nInvalid input.\n");
         return -1;
      }
   }

   // Set largestVal
   if (*largestVal == INT_MIN)
   {
      printf("For spacing purposes, what will be the LARGEST integer used? -");
      if (fgets(input, 11, stdin) == NULL)
         return -1;

      // Convert to integer
      li = strtol(input, NULL, 10);

      if (li <= 0L)
      {
         printf("\nInvalid input. Please enter a positive whole number.\n");
         return -1;
      }
      if (li > 1000000L)
      {
         printf("\nFor spacing purposes, please select a number < 1,000,000.\n");
         return -1;
      }
      *largestVal = (int)li;
   }

   return 0;
}

/*
███    ███  █████  ██ ███    ██
████  ████ ██   ██ ██ ████   ██
██ ████ ██ ███████ ██ ██ ██  ██
██  ██  ██ ██   ██ ██ ██  ██ ██
██      ██ ██   ██ ██ ██   ████
*/
int main(int argc, char **argv)
{
   int retval = 0;           // used to test return values from the diagram functions
   int quantity = INT_MIN;   // stores the number of diagrams the user requests
   int largestVal = INT_MIN; // represents the largest value to be used (for spacing purposes)
   char userInput = ' ';     // stores user options
   char rngFill = ' ';       // determines if the user wants rng values to fill the diagram
   char material = ' ';      // stores the type of material the user requests
   char dType[] = "!!!";     // stores the diagram type that the user requests
   FILE *ofp;                // the file pointer for the output file

   // Seeds rand() for any future call to rand() in this program
   srand(time(NULL));

   // Check for help call
   // NOTE: 'argv[0]' is the name of the executable
   if (argc > 1)
   {
      if (strcmp(argv[1], "help") == 0)
      {
         printMenu();
         return 2;
      }
   }

   /* Step 1: Determine the settings for the program */

   // Used to determine any settings given at the command line
   switch (argc)
   {
      // No additional arguments provided
      case 1:
         printMenu();
         break;
      // Diagram type provided
      case 2:
         printMenu();
         strcpy(dType, argv[1]);
         break;
      // Diagram type and quantity provided
      case 3:
         printMenu();
         strcpy(dType, argv[1]);
         quantity = atoi(argv[2]);
         break;
      // Diagram type, quantity, and material provided
      case 4:
         strcpy(dType, argv[1]);
         quantity = atoi(argv[2]);
         material = *argv[3];
         break;
      // Diagram type, quantity, material, and rng fill provided
      case 5:
         strcpy(dType, argv[1]);
         quantity = atoi(argv[2]);
         material = *argv[3];
         rngFill = *argv[4];
         break;
      // Everything provided
      case 6:
         strcpy(dType, argv[1]);
         quantity = atoi(argv[2]);
         material = *argv[3];
         rngFill = *argv[4];
         largestVal = atoi(argv[5]);
         break;
      default:
         printf("Invalid number of arguments.\n\n");
         printMenu();
         return 0;
   }

   // Now that the command line args have been assigned, call the setup function
   // NOTE: By moving this outside of the switch, it will now be called unnecessarily
   //       if everything was already provided at the command line and 'dType != "sn"'
   if (setup(dType, &quantity, &material, &rngFill, &largestVal))
   {
      printf("setup() failed.\n");
      return -1;
   }

   /* Step 2: Show the user what they have set so far and ask if they want to proceed */

   // Show user the settings they have selected
   printf("\nYou have chosen the following settings:\n");
   printf("dType = %s, quantity = %d, material = %c, rngFill = %c, largestVal = %d\n",
           dType, quantity, material, rngFill, largestVal);

   // Ask user if they would like to continue with those settings
   printf("\nPlease confirm the settings that you have entered.\n");
   printf("Press 'r' to re-enter settings, 'q' to quit, or any other letter to continue.\n-");
   userInput = (char)getchar();
   clear_input_buffer();

   // Quit
   if (userInput == 'q')
   {
      printf("User has decided to exit the program.\n");
      return 0;
   }
   // Re-enter settings
   else if (userInput == 'r')
   {
      strcpy(dType, "!!!");
      quantity = largestVal = INT_MIN;  // Kinda gross but saves space
      material = rngFill = ' ';         // Considered bad style by some

      if (setup(dType, &quantity, &material, &rngFill, &largestVal))
      {
         printf("setup() failed.\n");
         return -1;
      }
   }
   // Somehow, the user entered a none-printable character
   else if (!isprint(userInput))
   {
      printf("Invalid input.\n");
      return -1;
   }
   // The user entered a printable char that is not 'q' or 'r', so continue

   // Tells the user what they will be getting
   printf("Continuing with the following settings:\n");
   printf("\tdType = %s\n", dType);
   printf("\tquantity = %d\n", quantity);
   printf("\tmaterial = %c\n", material);
   printf("\trngFill = %c\n", rngFill);
   printf("\tlargestVal = %d\n", largestVal);

   /* Step 3: Create, or open, the output file and display the settings that will be used*/

   // Create the file that the diagram(s) will be printed to.
   // NOTE: "a" stands for "append" so it will always set the buffer to the end-of-file
   //       So if the file already exists, it will not overwrite anything
   ofp = fopen("output.txt", "a");
   if (ofp == NULL)
   {
      printf("Failed to open \"output.txt\".");
      return 2;
   }

   // This will make it so the diagram isn't squeezed up at the top of the file, or if the
   // file already exists, then this will make sure there is space between each diagram
   fprintf(ofp, "\n\n");

   // Before we create the diagram, print the settings that will be used in the file
   fprintf(ofp, "dType = %s, quantity = %d, material = %c, rngFill = %c, largestVal = %d\n",
           dType, quantity, material, rngFill, largestVal);
   fprintf(ofp, "\n");

   /* Step 4: Create the diagram by making the appropriate function call */

   // This will call the appropriate function to make the specified dType
   switch (is_valid_d_type(dType))
   {
      // arr
      case 0:
         retval = arr(quantity, material, rngFill, largestVal, &ofp);
         break;
      // 2da
      case 1:
         retval = two_d_arr(quantity, material, rngFill, largestVal, &ofp);
         break;
      // aol
      case 2:
         retval = arr_of_linked_lists(quantity, material, rngFill, largestVal, &ofp);
         break;
      // aos
      case 3:
         retval = arr_of_structs(quantity, material, rngFill, largestVal, &ofp);
         break;
      // stk
      case 4:
         retval = stack_queue(quantity, material, rngFill, largestVal, 's', &ofp);
         break;
      // que
      case 5:
         retval = stack_queue(quantity, material, rngFill, largestVal, 'q', &ofp);
         break;
      // ll
      case 6:
         retval = linked_list(quantity, material, rngFill, largestVal, &ofp);
         break;
      // sn
      case 7:
         retval = struct_node(quantity, material, rngFill, largestVal, &ofp);
         break;
      // tre
      case 8:
         retval = tree(quantity, rngFill, largestVal, &ofp);
         break;
      // tri
      case 9:
         retval = trie(quantity, rngFill, largestVal, &ofp);
         break;
      // Just in case
      default:
         printf("In default in \"is valid dType\" switch. Somehow invalid dType ");
         printf("made it this far.\n");
         fclose(ofp);  // NOTE: ALWAYS remember to clean up
         return -1;
   }

   // If the user specified dType was successfully printed, print success message
   if (retval == 0)
      printf("Successfully printed to file \"output.txt\" in the same location as this program.\n");
   else
   {
      printf("Error occured in printing to the output file.\n");
      printf("Error code: '%d'\n", retval);
      printf("To learn about this error code please refer to \"README.txt\"\n");
   }

   /* Step 5: Cleanup */

   // NOTE: ALWAYS close any files that you opened
   fclose(ofp);

   return 0;
}
