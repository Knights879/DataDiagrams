// ====================================
// DataDiagrams.h
// By Austin T. (Github: Knights879)
// ====================================

#ifndef __DATADIAGRAM_H
#define __DATADIAGRAM_H

#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_NAMES 24
#define MAX_LEN_PER_STR 15
#define MAX_NUM_STRUCT_NODES 1
#define MAX_CUSTOM_STRUCT_NAME_LEN 10
#define MAX_NUM_CUSTOM_STRUCT_NAMES 10

/*
████████ ██    ██ ██████  ███████ ██████  ███████ ███████ ███████
   ██     ██  ██  ██   ██ ██      ██   ██ ██      ██      ██
   ██      ████   ██████  █████   ██   ██ █████   █████   ███████
   ██       ██    ██      ██      ██   ██ ██      ██           ██
   ██       ██    ██      ███████ ██████  ███████ ██      ███████
*/

/* Typedefs that will be used in the program */

// The settings for the program. Contains all the user defined options/necessary vars to run the program
typedef struct settings {
   int quantity;
   int largestVal;
   char rngFill;
   char material;
   FILE *ofp;
} Settings;

// 'Node' can play the role of "node", "linked list node", and struct for "array of structures"
typedef struct node {
   int num;
   double data;
   char c;
   char *str;
   struct node *next;
} Node;

// 'Listy' can be used with "linked list" (Credit to Dr. S for the name "Listy")
typedef struct list {
   struct node *head;
   struct node *tail;
} Listy;

// 'Tree' is a binary tree
typedef struct tree {
   int data;
   struct node *left;
   struct node *right;
} Tree;

// 'Trie' is a trie
typedef struct trie {
   char letter;
   struct trie *children[26];
} Trie;

// 'Stack' can be used to stack numbers or characters (array implementation)
typedef struct stack {
   int size;
   int capacity;
   int *iArray;
   char *cArray;
} Stack;

// 'Queue' is a queue (linked list implementation)
typedef struct queue {
   int size;
   Listy *list;
} Queue;

/*
███████ ██    ██ ███    ██  ██████ ████████     ██████  ██████   ██████  ████████ ███████
██      ██    ██ ████   ██ ██         ██        ██   ██ ██   ██ ██    ██    ██    ██
█████   ██    ██ ██ ██  ██ ██         ██        ██████  ██████  ██    ██    ██    ███████
██      ██    ██ ██  ██ ██ ██         ██        ██      ██   ██ ██    ██    ██         ██
██       ██████  ██   ████  ██████    ██        ██      ██   ██  ██████     ██    ███████
*/

/* Functions defined in "DataDiagrams.c" */

// Prints a menu that displays possible options
void printMenu(void);
// Clears 'stdin'
void clear_input_buffer(void);
// Returns a random int from 0 to (largestVal - 1)
int get_rand_int(int);
// Returns a random lowercase letter
char get_rand_alpha(void);
// Returns a random printable character
char get_rand_printable(void);
// Returns a random string from "NAMES" (see declaration above)
const char * get_rand_string(void);
// Returns a random double
double get_rand_dub(int);
// Find the number of decimal places of a given value
int find_dec_places(int);
// Finds the length of a double
int find_double_len(int, double);
// Tests if the users diagram type is valid
int is_valid_d_type(char *);
// Sets the settings for the program
int setup(char *, int *, char *, char *, int *);

/* Functions defined in "arrays.c" */

// Creates the top and bottom of the array diagram
void create_topAndBot(int, int, char, char *);
// Creates the "arr" 'dType'
int arr(int, char, char, int, FILE **);
// Creates the "2da" 'dType'
int two_d_arr(int, char, char, int, FILE **);

/* Functions defined in "linkedlists.c" */

// Creates the "ln" 'dType'
int linked_list(int, char, char, int, FILE **);
// Creates the "aol" 'dType'
int arr_of_linked_lists(int, char, char, int, FILE **);

/* Functions defined in "stacknqueue.c" */

// Prints the array implementation of a "stk" or "que"
int print_sq_arr(int, int, int, char, char, int, char, FILE **);
// Prints a "stk" or "que" node (linked list implementation)
void print_sq_ll_node(int, int, int, char, char, int, char, int, FILE **);
// Prints the linked list implementation of a "stk" or "que"
void print_sq_ll(int, int, int, char, char, int, char, char, FILE **);
// Creates the "stk" and "que" 'dType'
int stack_queue(int, char, char, int, char, FILE **);

/* Functions defined in "structs.c" */

// Used for making struct nodes
int struct_node(int, char, char, int, FILE **);
// Creates the "aos" 'dType'
int arr_of_structs(int, char, char, int, FILE **);

/* Functions defined in "trees.c" */

// Creates the "tre" 'dType'
int tree(int, char, int, FILE **);
// Creates the "tri" 'dType'
int trie(int, char, int, FILE **);


#endif
