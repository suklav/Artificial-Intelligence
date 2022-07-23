#include<stdio.h>
#include<conio.h>
#include<iostream>
#include <alloc.h>
#include<graphics.h>

//The 3x3 matrix
struct board
{
    int a[3][3],zero_i,zero_j;
    struct board *next;
    struct board *parent;
}initial,OPEN,CLOSE,SOLUTION;

int count = 1, tcnt=1;

void insertdfs(struct board *,struct board *);
void copy(struct board *,struct board *);
void display(struct board *);


//after the solution is found this function will show all the steps
void show_steps(struct board *s)
{
    struct board *temp = s,*temp1;
    //count = 0;
    SOLUTION.next = NULL;

    while(temp->parent!=NULL)
    {
        temp1 = (struct board*) malloc(sizeof(struct board));
        copy(temp,temp1);
        insertdfs(temp1,&SOLUTION);
        count++;
        temp = temp->parent;
    }

    //getch();
    system("cls");
    //clrscr();

    printf("\nSteps required: %d",count);
    temp = SOLUTION.next;

    while(temp!=NULL)
    {
        display(temp);
        getch();
        temp = temp->next;
    }
    printf("\nGOAL REACHED...!!");
    getch();
}

//Find the zero in the board, so can swap
void find(struct board *s)
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(s->a[i][j]==0)
            {
                   s->zero_i = i;
                   s->zero_j = j;
                   return;
            }
}

// Function will show the matrix while execution
void display(struct board *s)
{
    printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            printf("%d",s->a[i][j]);
        printf("\n");
    }
}


// check if this is the solution
int check(struct board *s)
{
    if(s->a[0][0]==1 && s->a[0][1]==2 && s->a[0][2]==3 &&
        s->a[1][0]==4 && s->a[1][1]==5 && s->a[1][2]==6 &&
            s->a[2][0]==7 && s->a[2][1]==8 && s->a[2][2]==0 )
    {
        display(s);
        printf("Found Solution:- \n");
        show_steps(s);
        getch();
        while(1)
        {
                continue;
        }
        return 0;
    }
    else
    {
        //count++;
        return 1;
    }
}

//function to go back to the parent node, means by copying
void copy(struct board *s, struct board *b)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            b->a[i][j] = s->a[i][j];
        }
    }
    b->zero_i = s->zero_i;
    b->zero_j = s->zero_j;
    b->next = NULL;
    b->parent = s->parent;
}


int istraversed(struct board *s)
{
    struct board *temp = &CLOSE;
    while(temp->next!=NULL)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                   if(s->a[i][j] != temp->a[i][j])
                   {
                    goto skip;
                   }
            }
        }
        goto found;
        skip:
        temp = temp->next;
    }
    goto ret;
    found: return 1;
    ret: return 0;
}

int isvalid(struct board *s,int c)
{

    {
        if(c==5)
        {
                if(s->zero_i==2)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
        }
        if(c==2)
        {

                if(s->zero_i==0)
                {
                       return 0;
                }
                else
                {
                       return 1;
                }
        }
        if(c==1)
        {
                if(s->zero_j==2)
                {
                       return 0;
                }
                else
                {
                       return 1;
                }
        }
        if(c==3)
        {

                if(s->zero_j==0)
                {
                    return 0;
                }
                else
                {
                       return 1;
                }
        }
    }
    return 0;
}

void insertdfs(struct board *s, struct board *b)
{
    if(b->next == NULL)
    {
        b->next = s;
    }
    else
    {
        struct board *tmp = b->next;
        b->next = s;
        s->next = tmp;
    }
}


void remove(struct board *s)
{
    struct board *tmp = s->next;
    OPEN.next = tmp;
    s->next = NULL;
    insertdfs(s,&CLOSE);
}


// the main function
main()
{
     char ip[10];
    //clrscr();
    printf("\nEnter initial array:\n");
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            again:
            scanf("%d",&initial.a[i][j]);
            if(initial.a[i][j] >8 || initial.a[i][j] <0)
            {       printf("enter a valid input 0 - 8 \n");
                   goto again;    
            }
        }

    int c;
    //clrscr();
    find(&initial);
    struct board *temp,*temp1,t,*tt;
    temp = (struct board*) malloc(sizeof(struct board));
    //printf("\nGame starts now:-");
    initial.next = NULL;
    initial.parent = NULL;
    copy(&initial,temp);
    temp->parent = &OPEN;
    OPEN.next = NULL;
    OPEN.parent = NULL;
    CLOSE.next = NULL;
    insertdfs(temp,&OPEN);
    while(OPEN.next!=NULL && check(OPEN.next))
    {
           copy(OPEN.next,&t);
           int flag=1,k;
           tt=OPEN.next;
           remove(OPEN.next);
           display(&t);
           //getch();
        if(isvalid(&t,5))    //UP
        {
            temp1 = (struct board*) malloc(sizeof(struct board));
            copy(&t,temp1);
            temp1->a[temp1->zero_i][temp1->zero_j] = temp1->a[temp1->zero_i+1][temp1->zero_j];
            temp1->a[temp1->zero_i+1][temp1->zero_j] = 0;
            temp1->zero_i++;
            temp1->parent = tt;
            k=istraversed(temp1);
            if(k==0)
            {
                insertdfs(temp1,&OPEN);
                flag=0;
            }
        }
        if(isvalid(&t,1))   //LEFT
        {
            temp1 = (struct board*) malloc(sizeof(struct board));
            copy(&t,temp1);
            temp1->a[temp1->zero_i][temp1->zero_j] = temp1->a[temp1->zero_i][temp1->zero_j+1];
            temp1->a[temp1->zero_i][temp1->zero_j+1] = 0;
            temp1->zero_j++;
            temp1->parent = tt;
            k=istraversed(temp1);
            if(k==0)
            {
                insertdfs(temp1,&OPEN);
                flag=0;
            }

        }
        if(isvalid(&t,2))    //DOWN
        {
            temp1 = (struct board*) malloc(sizeof(struct board));
            copy(&t,temp1);
            temp1->a[temp1->zero_i][temp1->zero_j] = temp1->a[temp1->zero_i-1][temp1->zero_j];
            temp1->a[temp1->zero_i-1][temp1->zero_j] = 0;
            temp1->zero_i--;
            temp1->parent = tt;
            k=istraversed(temp1);
            if(k==0)
            {
                insertdfs(temp1,&OPEN);
                flag=0;
            }

        }
        if(isvalid(&t,3))     //RIGHT
        {
            temp1 = (struct board*) malloc(sizeof(struct board));
            copy(&t,temp1);
            temp1->a[temp1->zero_i][temp1->zero_j] = temp1->a[temp1->zero_i][temp1->zero_j-1];
            temp1->a[temp1->zero_i][temp1->zero_j-1] = 0;
            temp1->zero_j--;
            k=istraversed(temp1);
            temp1->parent = tt;
            if(k==0)
            {
                insertdfs(temp1,&OPEN);
                flag=0;
            }

        }
        if(flag==1)
        {
            printf("\nNo successor generated...!");
        }
    }
}
