#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>
#include <dos.h>
#define SIZE 100
struct node{
    char  info[SIZE][SIZE];
    struct node * next;
};
int row=100,col=100;
void table_cpy(char dst[][SIZE],char table[][SIZE])
{
    int i=0;
    for(i=0;i<row;i++)
    {
        int j=0;
        for(j=0;j<col;j++)
        {
            dst[i][j]=table[i][j];
        }
    }
}
void add_front(struct node **list,struct node * new_node)
{
    new_node->next=*list;
    *list=new_node;
}
struct node * create_node(char table[][SIZE])
{
    struct node * newnode;
    newnode=(struct node *)malloc(sizeof(struct node));
    if(newnode==NULL)
    {
        printf("Cannot allocate memory!\n");
        exit(0);
    }
    newnode->next=NULL;
    table_cpy(newnode->info,table);
    return newnode;
}

bool isDead(int i,int j,char table[][SIZE])
{
    if(table[i][j]!='*')
        return true;
    else
        return false;
}
void print_line()
{
    int i;
    for(i=0;i<col-1;i++)
    {
        printf("+---");
    }
    printf("+---+\n");
}

void print_row(int j,char table[][SIZE])
{
    int i;
    HANDLE hConsole;
    hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,7);
    for(i=0;i<col-1;i++)
    {
        if(table[j][i]=='*')
        {

            printf("|");
            SetConsoleTextAttribute(hConsole,68);
            printf(" * ");
            SetConsoleTextAttribute(hConsole,7);

        }
        else
            printf("|   ");
    }
    if(table[j][col-1]=='*')
    {
        printf("|");
        SetConsoleTextAttribute(hConsole,68);
        printf(" * ");
        SetConsoleTextAttribute(hConsole,7);
        printf("|");
    }
    else
        printf("|   |");
    printf("\n");
}
void print_table(char table[][SIZE],int gen)
{
    int i=0;
    printf("Generation %d: \n",gen);
    for(;i<row;i++)
    {
        print_line();
        print_row(i,table);
    }
    print_line();
}
void blink_cell(char table[][SIZE],int* i,int* j)
{
    COORD p= { 1+4*(*j), 2*(*i)+2 };
   HANDLE hConsole;
   while(true)
   {
       char c;
       p.X= 1+4*(*j);
       p.Y= 2*(*i)+2;
       hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
       SetConsoleCursorPosition(hConsole, p);
       while(!kbhit())
       {
           SetConsoleCursorPosition(hConsole, p);
           SetConsoleTextAttribute(hConsole,68);
           printf("   ");
           SetConsoleCursorPosition(hConsole, p);
           Sleep(300);
           SetConsoleTextAttribute(hConsole,7);
           printf("   ");
           Sleep(300);
       }
       if(table[*i][*j]=='*')
       {
           SetConsoleCursorPosition(hConsole, p);
           SetConsoleTextAttribute(hConsole,68);
           printf("   ");
       }
       else
       {
           SetConsoleCursorPosition(hConsole, p);
           SetConsoleTextAttribute(hConsole,7);
           printf("   ");
       }
        c=getch();
        if(c==-32)
        {
            c=getch();
            switch(c)
            {
                case 72:
                    (*i)--;
                    if(*i==-1)
                        *i=row-1;
                    break;
                case 80:
                    (*i)++;
                    if(*i==row)
                        *i=0;
                    break;
                case 75:
                    (*j)--;
                    if(*j==-1)
                        *j=col-1;
                    break;
                case 77:
                    (*j)++;
                    if(*j==col)
                        *j=0;
                    break;
            }
        }
        else if(c=='\r')
        {
            table[*i][*j]='*';
            system("cls");
            print_table(table,0);
            break;
        }
   }
}
int adj_check(int i,int j,char table[][SIZE])//Number of adjacent alive cells
{
    int num=0;
    if(i+1>row-1)
    {
        if(j+1>col-1)
        {
            if(table[i-1][j]=='*')
                num++;
            if(table[i-1][j-1]=='*')
                num++;
            if(table[i][j-1]=='*')
                num++;
            return num;
        }
        if(j-1<0)
        {
            if(table[i-1][j]=='*')
                num++;
            if(table[i-1][j+1]=='*')
                num++;
            if(table[i][j+1]=='*')
                num++;
            return num;
        }
        else{
            if(table[i-1][j]=='*')
                num++;
            if(table[i-1][j+1]=='*')
                num++;
            if(table[i][j+1]=='*')
                num++;
            if(table[i-1][j-1]=='*')
                num++;
            if(table[i][j-1]=='*')
                num++;
            return num;
        }
    }
    else if(i-1<0)
    {
        if(j+1>col-1)
        {
            if(table[i+1][j-1]=='*')
                num++;
            if(table[i][j-1]=='*')
                num++;
            if(table[i+1][j]=='*')
                num++;
            return num;
        }
        else if(j-1<0)
        {
            if(table[i+1][j+1]=='*')
                num++;
            if(table[i][j+1]=='*')
                num++;
            if(table[i+1][j]=='*')
                num++;
            return num;
        }
        else{
            if(table[i+1][j-1]=='*')
                num++;
            if(table[i][j-1]=='*')
                num++;
            if(table[i+1][j]=='*')
                num++;
            if(table[i+1][j+1]=='*')
                num++;
            if(table[i][j+1]=='*')
                num++;
            return num;
        }
    }
    else if(j+1>col-1)
    {
        if(table[i-1][j]=='*')
                num++;
        if(table[i][j-1]=='*')
                num++;
        if(table[i+1][j]=='*')
                num++;
        if(table[i-1][j-1]=='*')
                num++;
        if(table[i+1][j-1]=='*')
                num++;
        return num;
    }
    else if(j-1<0)
    {
        if(table[i-1][j]=='*')
                num++;
        if(table[i][j+1]=='*')
                num++;
        if(table[i+1][j]=='*')
                num++;
        if(table[i][j-1]=='*')
                num++;
        if(table[i-1][j+1]=='*')
                num++;
        return num;
    }
    else
    {
        if(table[i][j+1]=='*')
            num++;
        if(table[i+1][j]=='*')
            num++;
        if(table[i+1][j+1]=='*')
            num++;
        if(table[i-1][j]=='*')
            num++;
        if(table[i-1][j-1]=='*')
            num++;
        if(table[i][j-1]=='*')
            num++;
        if(table[i+1][j-1]=='*')
            num++;
        if(table[i-1][j+1]=='*')
            num++;
        return num;
    }
}
void rule1(int i,int j,char tablecpy[][SIZE],char table[][SIZE])//Checks rule 1 for i , j
{
    if((!isDead(i,j,table))&&adj_check(i,j,table)<2)
        tablecpy[i][j]=0;
}
void rule2(int i,int j,char tablecpy[][SIZE],char table[][SIZE])
{
    if((!isDead(i,j,table))&&adj_check(i,j,table)>3)
        tablecpy[i][j]=0;
}
void rule3(int i,int j,char tablecpy[][SIZE],char table[][SIZE])
{
    if((!isDead(i,j,table))&&(adj_check(i,j,table)==2||adj_check(i,j,table)==3))
        tablecpy[i][j]='*';
}
void rule4(int i,int j,char tablecpy[][SIZE],char table[][SIZE])
{
    if(adj_check(i,j,table)==3&&(isDead(i,j,table)))
        tablecpy[i][j]='*';
}

void rule(char table[][SIZE],bool rule_1,bool rule_2,bool rule_3,bool rule_4)//Rules the table!!!!!!
{
    int i;
    char tablecpy[SIZE][SIZE];
    memset(tablecpy,0,sizeof(tablecpy));
    table_cpy(tablecpy,table);
    int j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if(rule_1)
                rule1(i,j,tablecpy,table);
            if(rule_2)
                rule2(i,j,tablecpy,table);
            if(rule_3)
                rule3(i,j,tablecpy,table);
            if(rule_4)
                rule4(i,j,tablecpy,table);
        }
    }
    table_cpy(table,tablecpy);
}
void print_phase1_a()//Prints first menu in project
{
    printf("[1] New Game\n");
    printf("[2] Load A Saved Game\n");
    printf("[3] Exit\n");
}
void print_phase1_a_1()
{
    printf("Enter the dimensions (x and y) of the world: ");
    scanf("%d %d",&row,&col);
    printf("Initial live cell pattern:\n");
    printf("[1] Random\n");
    printf("[2] Load from file\n");
    printf("[3] Enter manually\n");
}
void print_phase2()
{
    printf("[1] Next Generation\n");
    printf("[2] Play the game\n");
    printf("[3] Save\n");
    printf("[4] Exit\n");
    printf("[5] Previous Generation\n");
    printf("[6] Change the rules\n");
}
bool file_save_found(char filename[100])
{
    FILE * fp=fopen(filename,"r");
    char c[100];
    while(1)
    {
        if(feof(fp))
        {
            fclose(fp);
            break;
        }
        fscanf(fp,"%s",c);
        if(strncmp(c,filename,strlen(filename))==0)
        {

        }
    }
    return false;
}
void file_save(char c[],char table[][SIZE],bool  rule_1,bool  rule_2,bool  rule_3,bool  rule_4,int gen)
{
    int i;
    FILE * fp=fopen(c,"w");


    fprintf(fp,"%d ",(int)rule_1);
    fprintf(fp,"%d ",(int)rule_2);
    fprintf(fp,"%d ",(int)rule_3);
    fprintf(fp,"%d\n",(int)rule_4);
    fprintf(fp,"%d ",row);
    fprintf(fp,"%d\n",col);
    fprintf(fp,"%d\n",gen);
    for(i=0;i<row;i++)
    {
        int j;
        for(j=0;j<col;j++)
        {
            if(table[i][j]==0)
                fprintf(fp,"0");
            else
                fprintf(fp,"%c",table[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}
void rule_manage(bool * rule_1,bool * rule_2,bool * rule_3,bool * rule_4)
{
    char RULE;
    printf("RULE1: A Living cell with less than 2 adjacent living cell will die.\n");
    printf("Do you want to enable this rule (y / n):\n");
    scanf("\n%c",&RULE);
    if(RULE=='y')
        *rule_1=true;
    else if(RULE=='n')
        *rule_1=false;
    printf("\n");
    printf("RULE2: A Living cell with more than 3 adjacent living cell will die.\n");
    printf("Do you want to enable this rule (y / n):\n");
    getchar();
    scanf("%c",&RULE);
    if(RULE=='y')
        *rule_2=true;
    else if(RULE=='n')
        *rule_2=false;
    printf("\n");
    printf("RULE3: A Living cell with 2 or 3 adjacent living cell will remain alive.\n");
    printf("Do you want to enable this rule (y / n):\n");
    getchar();
    scanf("%c",&RULE);
    if(RULE=='y')
        *rule_3=true;
    else if(RULE=='n')
        *rule_3=false;
    printf("\n");
    printf("RULE4: A Death cell with 3 adjacent living cell will become alive!!!\n");
    printf("Do you want to enable this rule (y / n):\n");
    getchar();
    scanf("%c",&RULE);
    if(RULE=='y')
        *rule_4=true;
    else if(RULE=='n')
        *rule_4=false;
    printf("\n");
}
void print_files_binary()//Prints Available files in Main.gof.
{
    FILE * fp=fopen("Main.gof","r+b");
    if(fp==NULL)
    {
        printf("Cannot open file\n");
        exit(-1);
    }
    fseek(fp,0,SEEK_SET);
    char filename[100];
    int n;
    while(!feof(fp))
    {
        fread(&n,sizeof(int),1,fp);
        fread(filename,sizeof(char),n,fp);
        if(feof(fp))
            break;
        filename[n]='\0';
        printf("%s\n",filename);
        fread(&n,sizeof(int),1,fp);
        fread(&n,sizeof(int),1,fp);//Skipping row
        fread(&n,sizeof(int),1,fp);//Skipping column
        fseek(fp,sizeof(bool)*4,SEEK_CUR);
        fread(&n,sizeof(int),1,fp);
        fseek(fp,sizeof(int)*n*2,SEEK_CUR);
    }
    fclose(fp);
}
void file_load_table(char table[][SIZE])
{
    char filename[1000];
    printf("Enter name of file you want to read from table:");
    getchar();
    gets(filename);
    FILE * fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("Cannot open file\n");
        exit(-1);
    }
    while(!feof(fp))
    {
        int i,j;
        fscanf(fp,"%d ",&i);
        fscanf(fp,"%d\n",&j);
        if(i<row&&j<col)
        {
            table[i][j]='*';
        }
    }
    fclose(fp);
}
void file_load(char filename[1000],bool * rule_1,bool * rule_2,bool * rule_3,bool * rule_4,char table[][SIZE],int * gen)//Load from text files.
{
    FILE * fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("Cannot open file\n");
        exit(-1);
    }
    char c;
    fscanf(fp,"%c ",&c);
    if(c=='1')
        *rule_1=true;
    else
        *rule_1=false;
    fscanf(fp,"%c ",&c);
    if(c=='1')
        *rule_2=true;
    else
        *rule_2=false;
    fscanf(fp,"%c ",&c);
    if(c=='1')
        *rule_3=true;
    else
        *rule_3=false;
    fscanf(fp,"%c\n",&c);
    if(c=='1')
        *rule_4=true;
    else
        *rule_4=false;
    fscanf(fp,"%d ",&row);
    fscanf(fp,"%d\n",&col);
    fscanf(fp,"%d\n",gen);
    int i=0,j=0;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            fscanf(fp,"%c",&table[i][j]);
        }
        fscanf(fp,"\n");
    }
    fclose(fp);
}
void phase1_a_3(char table[][SIZE])//Manually entering points by its x and y.
{
    int num;
    printf("Enter number of cells you want to enter:");
    scanf("%d",&num);
    int i;
    for(i=0;i<num;i++)
    {
        int j,k;
        while(true)
        {
            printf("Enter row of cell:");
            scanf("%d",&j);
            printf("Enter column of cell:");
            scanf("%d",&k);
            if(j<row&&k<col)
            {
                table[j][k]='*';
                break;
            }
            else{
                printf("Enter a Valid ROW & COLUMN!!!!\n");
                printf("Getting %d cell another time...\n",i+1);
                Sleep(1000);
            }
        }
    }
}
void manual_new(char table[][SIZE],int i,int j)//Graphic Entering dots.
{
    char c;
    int num;
    printf("Enter number of points you want to enter:");
    scanf("%d",&num);
    int n;
    for(n=0;n<num;n++)
    {
        blink_cell(table,&j,&i);
    }
}
int list_point(char table[][SIZE],int dst[][2])
{
    int num=0;
    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if(table[i][j]=='*')
            {
                dst[num][0]=i;
                dst[num][1]=j;
                num++;
            }
        }
    }
    return num;
}
bool found_binary(char file[100])//Prints Available files in Main.gof.
{
    FILE * fp=fopen("Main.gof","r+b");
    if(fp==NULL)
    {
        printf("Cannot open file\n");
        exit(-1);
    }
    fseek(fp,0,SEEK_SET);
    char filename[100];
    int n;
    while(!feof(fp))
    {
        fread(&n,sizeof(int),1,fp);
        fread(filename,sizeof(char),n,fp);
        if(feof(fp))
            break;
        filename[n]='\0';
        if(strncmp(file,filename,n)==0)
        {
            fclose(fp);
            return true;
        }
        fread(&n,sizeof(int),1,fp);
        fread(&n,sizeof(int),1,fp);//Skipping row
        fread(&n,sizeof(int),1,fp);//Skipping column
        fseek(fp,sizeof(bool)*4,SEEK_CUR);
        fread(&n,sizeof(int),1,fp);
        fseek(fp,sizeof(int)*n*2,SEEK_CUR);
    }
    fclose(fp);
    return false;

}

void delete_file_binary(char filename[100])
{
    FILE * fp=fopen("Main.gof","r+b");
    if(fp==NULL)
    {
        printf("Cannot open file\n");
        exit(-1);
    }
    fseek(fp,0,SEEK_SET);
    FILE * newfp=fopen("temp.gof","w+b");
    if(newfp==NULL)
    {
        printf("Cannot open file\n");
        exit(-1);
    }
    char filename_load[100];
    int  gen;
    int row1,col1;
    bool rule_1,rule_2, rule_3, rule_4;
    int n;
    while(!feof(fp))
    {
        fread(&n,sizeof(int),1,fp);
        fread(filename_load,sizeof(char),n,fp);
        filename_load[n]='\0';
        if(strncmp(filename_load,filename,n)==0)
        {
            if(feof(fp))
                break;
            fread(&row1,sizeof(int),1,fp);
            fread(&col1,sizeof(int),1,fp);
            fread(&gen,sizeof(int),1,fp);
            fread(&rule_1,sizeof(bool),1,fp);
            fread(&rule_2,sizeof(bool),1,fp);
            fread(&rule_3,sizeof(bool),1,fp);
            fread(&rule_4,sizeof(bool),1,fp);
            fread(&n,sizeof(int),1,fp);
            int i=0;
            int x,y;
            for(i=0;i<n;i++)
            {
                fread(&x,sizeof(int),1,fp);
                fread(&y,sizeof(int),1,fp);
            }
        }

        else
        {
            if(feof(fp))
                break;
            fwrite(&n,sizeof(int),1,newfp);
            fwrite(filename_load,sizeof(char),n,newfp);
            fread(&row1,sizeof(int),1,fp);
            fread(&col1,sizeof(int),1,fp);
            fread(&gen,sizeof(int),1,fp);
            fread(&rule_1,sizeof(bool),1,fp);
            fread(&rule_2,sizeof(bool),1,fp);
            fread(&rule_3,sizeof(bool),1,fp);
            fread(&rule_4,sizeof(bool),1,fp);
            fread(&n,sizeof(int),1,fp);
            fwrite(&row1,sizeof(int),1,newfp);
            fwrite(&col1,sizeof(int),1,newfp);
            fwrite(&gen,sizeof(int),1,newfp);
            fwrite(&rule_1,sizeof(bool),1,newfp);
            fwrite(&rule_2,sizeof(bool),1,newfp);
            fwrite(&rule_3,sizeof(bool),1,newfp);
            fwrite(&rule_4,sizeof(bool),1,newfp);
            fwrite(&n,sizeof(int),1,newfp);
            int i=0;
            int x,y;
            for(i=0;i<n;i++)
            {
                fread(&x,sizeof(int),1,fp);
                fread(&y,sizeof(int),1,fp);
                fwrite(&x,sizeof(int),1,newfp);
                fwrite(&y,sizeof(int),1,newfp);
            }
            if(feof(fp))
            break;
        }
    }
    fclose(fp);
    fflush(fp);
    fclose(newfp);
    fflush(newfp);
    system("del Main.gof");
    system("rename temp.gof Main.gof");
}
bool binary_save(char table[][SIZE],int gen,bool rule_1,bool rule_2,bool rule_3,bool rule_4,char filename[100])
{
    FILE * fp=fopen("Main.gof","r+b");
    if(fp==NULL)
    {
        printf("Cannot open file\n");
        exit(-1);
    }
    int n;
    char c='\0';
    if(!found_binary(filename))
    {
        fseek(fp,0,SEEK_END);
        n=strlen(filename);
        fwrite(&n,sizeof(int),1,fp);
        fwrite(filename,sizeof(char),n,fp);
        fwrite(&row,sizeof(int),1,fp);
        fwrite(&col,sizeof(int),1,fp);
        int i;
        int point[SIZE*SIZE][2];
        n=list_point(table,point);
        fwrite(&gen,sizeof(int),1,fp);
        fwrite(&rule_1,sizeof(bool),1,fp);
        fwrite(&rule_2,sizeof(bool),1,fp);
        fwrite(&rule_3,sizeof(bool),1,fp);
        fwrite(&rule_4,sizeof(bool),1,fp);
        fwrite(&n,sizeof(int),1,fp);
        for(i=0;i<n;i++)
        {
            fwrite(&point[i][0],sizeof(int),1,fp);
            fwrite(&point[i][1],sizeof(int),1,fp);
        }
    }
    else{

        printf("The file with the name %s exist.\n",filename);
        printf("Do you want to replace the file? (y / n)\n");
        scanf("%s",&c);
        if(c=='y')
        {
            fclose(fp);
            binary_save(table,gen,rule_1,rule_2,rule_3,rule_4,"===");
        }
        else if(c=='n')
        {
            printf("Enter new file name:");
            scanf("%s",filename);
            binary_save(table,gen,rule_1,rule_2,rule_3,rule_4,filename);
        }
    }
    fclose(fp);
    if(c=='y')
    return true;
}
void binary_load(char table[][SIZE],char filename[100],bool * rule_1,bool * rule_2,bool * rule_3,bool * rule_4,int * gen)
{
    FILE * fp=fopen("Main.gof","r+b");
    if(fp==NULL)
    {
        printf("Cannot open file\n");
        exit(-1);
    }
    fseek(fp,0,SEEK_SET);
    char filename_load[100];
    int n;
    if(found_binary(filename))
    {
    while(!feof(fp))
    {
        fread(&n,sizeof(int),1,fp);
        fread(filename_load,sizeof(char),n,fp);
        filename_load[n]='\0';
        if(strncmp(filename_load,filename,n)==0)
        {
            if(feof(fp))
                break;
            fread(&row,sizeof(int),1,fp);
            fread(&col,sizeof(int),1,fp);
            fread(gen,sizeof(int),1,fp);
            fread(rule_1,sizeof(bool),1,fp);
            fread(rule_2,sizeof(bool),1,fp);
            fread(rule_3,sizeof(bool),1,fp);
            fread(rule_4,sizeof(bool),1,fp);
            fread(&n,sizeof(int),1,fp);
            int i=0;
            int x,y;
            for(i=0;i<n;i++)
            {
                fread(&x,sizeof(int),1,fp);
                fread(&y,sizeof(int),1,fp);
                table[x][y]='*';
            }
            fclose(fp);
            return;
        }
        if(feof(fp))
            break;
        fread(&n,sizeof(int),1,fp);//Skipping row
        fread(&n,sizeof(int),1,fp);//Skipping column
        fread(&n,sizeof(int),1,fp);//Skipping generation
        fseek(fp,sizeof(bool)*4,SEEK_CUR);//Skipping rules
        fread(&n,sizeof(int),1,fp);
        fseek(fp,sizeof(int)*n*2,SEEK_CUR);
    }
    }
    else{
        printf("File with this name not found!\n");
        exit(0);
    }
    fclose(fp);
}
