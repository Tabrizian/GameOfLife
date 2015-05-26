#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>
#include <dos.h>
#define SIZE 100
struct node{
    char info[SIZE][SIZE];
    struct node * next;
};
int list_point(char table[][SIZE],int dst[][2]);//Lists point in a table.
bool binary_save(char table[][SIZE],int gen,bool rule_1,bool rule_2,bool rule_3,bool rule_4,char filename[100]);//Saves Binary
struct node * create_node(char table[][SIZE] );//Creates New node.
void add_front(struct node **list,struct node * new_node);//Adds to the front of the Linked List
bool isDead(int i,int j,char table[][SIZE]);//Checks whether a cell is alive or dead.
void print_table(char table[][SIZE],int gen);//Prints one line
void print_line();//Prints one line
void print_row(int j,char table[][SIZE]);//Prints one row
void rule1(int i,int j,char tablecpy[][SIZE],char table[][SIZE]);//checks rule 1 for i,  j
void rule2(int i,int j,char tablecpy[][SIZE],char table[][SIZE]);//Checks rule 2 for i,  j
void rule3(int i,int j,char tablecpy[][SIZE],char table[][SIZE]);//Checks rule 3 for i,  j
void rule4(int i,int j,char tablecpy[][SIZE],char table[][SIZE]);//Checks rule 4 for i,  j
void table_cpy(char dst[][SIZE],char table[][SIZE]);
void rule(char table[][SIZE],bool rule_1,bool rule_2,bool rule_3,bool rule_4);//rules the table!!!!!!
void print_phase1_a();//prints first menu in project
void print_phase1_a_1();
void print_phase2();
void file_save(char c[],char table[][SIZE],bool  rule_1,bool  rule_2,bool  rule_3,bool  rule_4,int gen);//Saves in text file.
void rule_manage(bool * rule_1,bool * rule_2,bool * rule_3,bool * rule_4);//Gets rule
void print_files_binary();//Prints available files in Main.gof
void file_load_table(char table[][SIZE]);//Read points from files.
void file_load(char filename[1000],bool * rule_1,bool * rule_2,bool * rule_3,bool * rule_4,char table[][SIZE],int * gen);//Loads from file using text files.
void manual_new(char table[][SIZE],int i,int j);//Selects point in screen using arrow keys.
void blink_cell(char table[][SIZE],int* i,int* j);//Blinks table.
void binary_load(char table[][SIZE],char filename[100],bool * rule_1,bool * rule_2,bool * rule_3,bool * rule_4,int * gen);//Load binary
void delete_file_binary(char filename[100]);//Deleting binary file
#endif // FUNCTIONS_H_INCLUDED
