#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>
#include <dos.h>
#include "functions.h"
#define SIZE 100
int row,col;
int main()
{
    int defgen=0;//Default generation.
    char table[SIZE][SIZE];
    struct node * list;
    int generation=0;
    int phase1_a,phase1_a_1;
    bool rule_1,rule_2,rule_3,rule_4;
    memset(table,0,sizeof(table));
    print_phase1_a();
    scanf("%d",&phase1_a);
    char filename[100];
    int man_type;//Manually entering table living cells.
    int load=0;//Types of loading file in phase 1.
    switch(phase1_a)
    {
    case 1:
        print_phase1_a_1();
        scanf("%d",&phase1_a_1);
        switch(phase1_a_1)
        {
            int cell_num;
        case 1:
            printf("Enter number of cells you want to create:");
            scanf("%d",&cell_num);
            int i=0;
            for(; i<cell_num; i++)
            {
                int random_col,random_row;
A:
                ;
                random_col=rand()%col,random_row=rand()%row;
                if(!isDead(random_row,random_col,table))
                {
                    goto A;
                }
                else
                {
                    table[random_row][random_col]='*';
                }
            }
            rule_manage(&rule_1,&rule_2,&rule_3,&rule_4);
            break;
        case 2:
            system("cls");
            system("dir");
            file_load_table(table);
            rule_manage(&rule_1,&rule_2,&rule_3,&rule_4);
            break;
        case 3:
            system("cls");
            printf("[1] Manual by entering dots\n");
            printf("[2] Manual by choosing dots on the board using arrow keys!\n");
            scanf("%d",&man_type);
            if(man_type==1)
                phase1_a_3(table);
            else if(man_type==2)
            {
                system("cls");
                print_table(table,generation);
                manual_new(table,0,0);
            }
            rule_manage(&rule_1,&rule_2,&rule_3,&rule_4);
            break;
        }
        break;
    case 2:
        system("cls");
        printf("[1] Load from text files\n");
        printf("[2] Load from binary file\n");
        scanf("%d",&load);
        if(load==1)
        {
            system("dir");
            printf("Choose one of the name of above files:");
            getchar();
            gets(filename);
            file_load(filename,&rule_1,&rule_2,&rule_3,&rule_4,table,&defgen);
            generation=defgen;
        }
        else if(load==2)
        {
            print_files_binary();
            printf("Choose one of the name of above files:");
            getchar();
            gets(filename);
            binary_load(table,filename,&rule_1,&rule_2,&rule_3,&rule_4,&defgen);
            generation=defgen;
        }
        break;
    case 3:
        exit(0);
        break;
    }
    int phase2;
    system("cls");
    print_table(table,generation);
    list=create_node(table);
    struct node * new_node;
    char d[200]="del ";//For deleting text files.
    int save;
    d[4]='\0';
    char **good;
    while(true)
    {
        char c[1000];
        print_phase2();
        scanf("%d",&phase2);
        int dupli=0;//Checking duplicate file.
        switch(phase2)
        {
            int k;
        case 1:
            system("cls");
            rule(table,rule_1,rule_2,rule_3,rule_4);
            generation++;
            new_node=create_node(table);
            add_front(&list,new_node);
            print_table(list->info,generation);
            break;
        case 2:
            printf("Processing...\n");
            for(k=0; k<10; k++)
            {
                if(generation==3)
                    phase1_a++;
                Sleep(3000);
                rule(table,rule_1,rule_2,rule_3,rule_4);
                generation++;
                system("cls");
                new_node=create_node(table);
                add_front(&list,new_node);
                print_table(list->info,generation);
            }
            break;
        case 3:
            printf("[1] Binary Save\n");
            printf("[2] Save in Text file\n");
            scanf("%d",&save);
            printf("Enter name of file:");
            getchar();
            gets(c);
            if(save==1)
            {
                dupli=binary_save(list->info,generation,rule_1,rule_2,rule_3,rule_4,c);
            }
            if(save==2)
            {
                strcat(c,".save");
                file_save(c,table,rule_1,rule_2,rule_3,rule_4,generation);
            }
            if(dupli==1)
            {
                delete_file_binary(c);
                binary_save(table,generation,rule_1,rule_2,rule_3,rule_4,c);
                delete_file_binary("===");
            }
            exit(0);
            break;
        case 4:
            if(load==1)
            {
                strcat(d,filename);
                system(d);
            }
            else if(load==2)
            {
                delete_file_binary(filename);
            }
            exit(0);
            break;
        case 5:
            if(generation==defgen)
            {
                system("cls");
                printf("Cannot go previous more!!!\n");
                printf("You're in the first generation or you're in the loaded generation.\n");
            }
            else
            {
                struct node * temp=list;
                list=list->next;
                generation--;
                free(temp);
                system("cls");
                print_table(list->info,generation);
            }
            break;
        case 6:
            rule_manage(&rule_1,&rule_2,&rule_3,&rule_4);
            break;
        }
    }
    return 0;
}
