#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct node
{
    char name[20];
    int seat,ticket,date;
    struct node* next;
};

struct qnode
{
    char name[20];
    int seat,ticket,date;
    struct qnode* qnext;
};


void enqueue(struct qnode **first,int d,char name[20],int date)
{
    struct qnode* n;
    n=*first;
    if(n!=NULL)
    {
        struct qnode* newnode = (struct qnode*)malloc(sizeof(struct qnode));
        newnode->ticket=d;
        newnode->date=date;
        strcpy(newnode->name,name);

        while((n->qnext)!=NULL)
        {
            n=n->qnext;
        }
        n->qnext=newnode;
        newnode->qnext=NULL;
    }
    else if(n==NULL)
    {
        struct qnode* head = (struct qnode*)malloc(sizeof(struct qnode)) ;

        head->ticket=d;
        head->date=date;
        strcpy(head->name,name);

        head->qnext=*first;
        *first=head;
    }
}

struct qnode* dequeue(struct qnode** first)
{
    struct qnode* m;
    m = *first;

    if(m==NULL)
    {
        return NULL;
    }
    else if(m->qnext==NULL)
    {
        *first=NULL;
        return m;
    }
    else
    {
        *first=m->qnext;
        return m;
    }
}


void display(struct qnode **first)
{
    struct qnode *n;
    n=*first;

    if(n!=NULL)
        printf("\nWaiting List\n");
    else
        printf("\nNo tickets in Waiting List\n");

    while(n!=NULL)
    {
        printf("Name : %s  ||  Date : %s  ||  Ticket No. : %d \n",n->name,n->date,n->ticket);
        n=n->qnext;
    }
    printf("\n\n");
}



int check(struct node **first,int d,char name[20],int date)
{
    struct node* m = (struct node*)malloc(sizeof(struct node)) ;
    m=*first;

    int n10=d%10;
    int dn100=d%100;
    int n100=dn100/10;
    int dn1000=d%1000;
    int n1000=dn1000/100;

    while(m!=NULL)
    {
        int mt = m->ticket;
        int m10=mt%10;
        int md100=mt%100;
        int m100=md100/10;
        int md1000=mt%1000;
        int m1000=md1000/100;

        if(m10==n10)
        {
            if(m1000 < n100&&m->date==date)
            {
                printf("Sorry ! This seat is Unavailable. So your ticket is added to waiting list.\n\n");
                struct qnode* qfirst = NULL;
                int tic=730000+d;
                return -1;
            }
        }
        m=m->next;
    }
    return 1;
}


int insertion(struct node **first,int d,char name[20],int date)
{
    struct node* head = (struct node*)malloc(sizeof(struct node)) ;

    head->next=*first;
    *first=head;
    struct node* m = (struct node*)malloc(sizeof(struct node)) ;
    m=head->next;
    int tic=730000+d;

    strcpy(head->name,name);
    head->seat=d%10;
    head->ticket=tic;
    head->date=date;
    int ret=0;

    return ret;

}


int set(struct node **first,int tn)
{
    struct node* head;
    struct node* n;
    head=*first;
    n=*first;
    struct node* m;
    m=n;
    int cou=1;
    int ret=0;

    while(n!=NULL)
    {
        if(tn==n->ticket && cou>1)
        {
            m->next=n->next;
            n->next=head;
            *first=n;
            head=*first;

            ret=1;
        }
        else if(tn==n->ticket && cou==1)
        {
            ret=1;
        }
        cou++;
        m=n;
        n=n->next;
    }
    return ret;
}

void traversal(struct node *n)
{
    FILE *ftr;
    ftr=fopen("FileTraverse","w");
    struct node *m;
    struct node *nn;
    nn=n;
    int t;
    char temp[20];
    while(n!=NULL)
    {
        m=n->next;
        while(m!=NULL)
        {
            if(n->seat>m->seat)
            {
                t=n->seat;
                n->seat=m->seat;
                m->seat=t;

                t=n->date;
                n->date=m->date;
                m->date=t;

                t=n->ticket;
                n->ticket=m->ticket;
                m->ticket=t;

                strcpy(temp,n->name);
                strcpy(n->name,m->name);
                strcpy(m->name,temp);
            }
            m=m->next;
        }
        n=n->next;
    }
    n=nn;
    while(n!=NULL)
    {
        fprintf(ftr,"%s - %s - %d - %d  \n",n->date,n->name,n->seat,n->ticket);
        n=n->next;
    }
    printf("\n\n");
    fclose(ftr);
}



void deletion(struct node** first)
{
    struct node* m;
    m = *first;
    if(m->next!=NULL)
    {
        *first=m->next;
        printf("\nTICKET CANCELED  -  %d \n\n",m->ticket);

    }
    else if(m->next==NULL)
    {
        printf("\nTICKET CANCELED  -  %d \n\n",m->ticket);
        *first=NULL;
    }
    else
    {
        printf("\nEMPTY !! deletion \n\n");
    }
}


int detail(int tn,int bp,int dp,struct node *n,char from[20],char to[20])
{

    printf("\n\nTICKET DETAILS : \n\n");
    while(n!=NULL)
    {
        if(n->ticket==tn)
        {
            printf("%s to %s :Name      : %s \n",from,to,n->name);
            printf("               Date       : %s \n",n->date);
            printf("               Seat       : %d \n",n->seat);
            printf("               Ticket No. : %d \n\n",n->ticket);
            return 73;
        }
        n=n->next;
    }
    printf("\n\n");


}


int main()
{

    int ch1=0,bp,dp,seat,s,i;
    char name[20],from[20],to[20],date[20];
    int itr=0,tn,rep;
    int re=0;
    struct node* first = NULL;
    struct qnode* qfirst = NULL;
    system("COLOR  2");


    do
    {
        printf("\t----------------------------BUS TICKET BOOK----------------------\n");
        printf("\t\t\t\t1.Book Now!\n\t\t\t\t2.Cancel Ticket\n\t\t\t\t3.Ticket Details\n\t\t\t\t4.Waiting List\n\t\t\t\t5.Exit\n");
        printf("Enter your choice : ");
        scanf("%d",&ch1);
        printf("\n");
        int c=0,q=0;
        switch(ch1)
        {

        case 1:
            printf("Enter the start point  :  ");
            scanf("%s",&from);
            printf("\n");
            printf("Enter the end point  :  ");
            scanf("%s",&to);
            printf("\n");
            printf("Enter the date:");
            scanf("%s",&date);
            printf("\nEnter your name : ");
           scanf("%s",&name);

            printf("How many seat you want :");
            scanf("%d",&s);
            printf("\t----------------------------\n");
            printf("\t|1\t2\t3\t4  |\n");
            printf("\t|\t\t\t   |\n");
            printf("\t|\t\t\t   |  \n");
            printf("\t|5\t6\t7\t8  |\n");
            printf("\t|\t\t\t   |\n");
            printf("\t|\t\t\t   |\n");
            printf("\t|9\t10\t11\t12 |\n");
            printf("\t|\t\t\t   |\n");
            printf("\t----------------------------\n");
            printf("\nwhich seat you want :  ");
            for(i=0; i<s; i++)
            {
                scanf("%d",&seat);
                if(check(&first,(seat+120),name,date)==-1)
                {
                    int tic=730000+seat+120;
                    enqueue(&qfirst,tic,name,date);
                }
                else
                {
                    re=insertion(&first,(seat+120),name,date);
                    printf("\nTICKET CONFIRMED == %s   To  %s | %s | %s | %d | %d \n\n",from,to,date,name,seat,(730120+seat));
                    traversal(first);
                }


            }


            break;


        case 2 :
            tn=0;
            printf("Enter your ticket no. : ");
            scanf("%d",&tn);
            rep=0;
            int n10=tn%10;

            int dn100=tn%100;
            int n100=dn100/10;

            int dn1000=tn%1000;
            int n1000=dn1000/100;

            if(((tn-((tn)%1000))==730000) && n10<6 && n10>0 && n100<5 && n100>1
                    && n1000<4 && n1000>0 )
            {
                if(set(&first,tn)==1)
                {
                    deletion(&first);
                    traversal(first);
                    rep=1;
                    struct qnode *m;
                    m = dequeue(&qfirst);

                    if(m!=NULL)
                    {
                        strcpy(name,m->name);

                        tn=m->ticket;

                        n10=tn%10;

                        dn100=tn%100;
                        n100=dn100/10;
                        dp=n100;

                        dn1000=tn%1000;
                        n1000=dn1000/100;
                        bp=n1000;
                        int tt;

                        re=insertion(&first,(tn%1000),name,date);
                        traversal(first);
                        printf("\nTICKET CONFIRMED == %s to %s | %s | %s | %d | %d \n\n",from,to,date,name,seat,(730120+seat));



                    }
                }

                if(rep==0)
                    printf("Please enter valid Ticket Number.\n\n");
            }

            else
            {
                printf("Please enter valid Ticket Number \n\n");
            }




            break;

        case 3:

            traversal(first);

            tn=0;
            printf("Enter your ticket no. : ");
            scanf("%d",&tn);
            rep=0;
            n10=tn%10;
            dn100=tn%100;
            n100=dn100/10;
            dn1000=tn%1000;
            n1000=dn1000/100;

            if(((tn-((tn)%1000))==730000) && n10<6 && n10>0 && n100<5 && n100>1
                    && n1000<4 && n1000>0 )
            {
                if(detail(tn,n1000,n100,first,from,to)!=73)
                {
                    printf("Please enter valid Ticket Number \n\n");
                }
            }
            else
            {
                printf("Please enter valid Ticket Number \n\n");
            }
            break;

        case 4:
            display(&qfirst);
            break;

        }
    }
    while(ch1!=5);

}
