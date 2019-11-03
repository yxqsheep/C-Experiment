#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTUDENT 30
#define MAXNAME 10
#define MAXCOURSE 6

typedef struct
{
    long ID;
    char name[MAXNAME];
    int score[MAXCOURSE];
    int total;
    int average;
} STUDENT;

void menu(void);
void Input(int n,int m,STUDENT stu[]);
void Calculate(int n,int m,STUDENT stu[]);
void CalculateStu(int n,STUDENT stu[]);
void SelectionSort(STUDENT stu[],int n,int m,int (*compare)(int a,int b));
int Descending(int a,int b);
int Ascending(int a,int b);
void Sort(STUDENT stu[],int n,int m);
void Sortbyname(STUDENT stu[],int n,int m);
void Output(STUDENT stu[],int n,int m,int type);
void Search(STUDENT stu[],int n,int m);
void Searchbyname(STUDENT stu[],int n,int m);
void Analysis(STUDENT stu[],int n,int m);
void OutputAll(STUDENT stu[],int n,int m);
void WritetoFile(STUDENT stu[],int n,int m);
void ReadfromFile(STUDENT stu[],STUDENT _stu[],int *n,int *m);

int main(void)
{
    int choice;
    int i;
    int n=0,m;
    STUDENT stu[MAXSTUDENT],_stu[MAXSTUDENT];
    menu();
    scanf("%d",&choice);
    while (choice != 0)
    {
        if (choice != 1 && choice != 13 && n==0)
        {
            printf("Input data first!\n");
            choice =1;
        }
        switch (choice)
        {
        case 1:
            while (n<1 || n>30)
            {
                while (getchar() != '\n');
                printf("Input the number of students :");
                scanf("%d",&n);
            }
            while (m<=0 || m>6)
            {
                while (getchar() != '\n');
                printf("Input the number of courses : ");
                scanf("%d",&m);
            }
            Input(n,m,stu);
            for (i=0; i<n; i++)
            {
                _stu[i]=stu[i];
            }
            break;
        case 2:
            Calculate(n,m,stu);
            break;
        case 3:
            CalculateStu(n,stu);
            break;
        case 4:
            SelectionSort(_stu,n,m,Descending);
            break;
        case 5:
            SelectionSort(_stu,n,m,Ascending);
            break;
        case 6:
            Sort(_stu,n,m);
            Output(_stu,n,m,0);
            break;
        case 7:
            Sortbyname(_stu,n,m);
            Output(_stu,n,m,1);
            break;
        case 8:
            Search(_stu,n,m);
            break;
        case 9:
            Searchbyname(_stu,n,m);
            break;
        case 10:
            Analysis(_stu,n,m);
            break;
        case 11:
            OutputAll(stu,n,m);
            break;
        case 12:
            WritetoFile(stu,n,m);
            break;
        case 13:
            ReadfromFile(stu,_stu,&n,&m);
            break;
        default:
            printf("Illegal input!\n");
        }
        printf("Please enter your choice: ");
        scanf("%d",&choice);
    }
    return 0;
}

void menu(void)
{
    printf(" 1. Input record \n");
    printf(" 2. Calculate total and average score of every course \n");
    printf(" 3. Calculate total and average score of every student \n");
    printf(" 4. Sort in descending order by total score of every student \n");
    printf(" 5. Sort in ascending order by total score of every student \n");
    printf(" 6. Sort in ascending order by number \n");
    printf(" 7. Sort in dictionary order by name \n");
    printf(" 8. Search by number \n");
    printf(" 9. Search by name \n");
    printf(" 10.Statistic analysis for every student \n");
    printf(" 11.List record \n");
    printf(" 12.Write to a file \n");
    printf(" 13.Read from a file \n");
    printf(" 0. Exit \n");
    printf("Please enter your choice: ");
}

void Input(int n,int m,STUDENT stu[])
{
    int i,j,ret;
    for (i=0; i<n; i++)
    {
        printf("Input the ID of student%d:",i+1);
        ret=scanf("%ld",&stu[i].ID);
        while (ret!=1)
        {
            while (getchar() != '\n');
            printf("Input the ID of student%d:",i+1);
            ret=scanf("%ld",&stu[i].ID);
        }
        printf("Input the name of student%d:",i+1);
        ret=scanf("%s",stu[i].name);
        while (ret!=1)
        {
            while (getchar() != '\n');
            printf("Input the name of student%d:",i+1);
            ret=scanf("%s",stu[i].name);
        }
        for (j=0; j<m; j++)
        {
            printf("Input the score of course%d:",j+1);
            ret=scanf("%d",&stu[i].score[j]);
            while (ret!=1 || stu[i].score[j]<0 || stu[i].score[j]>100)
            {
                while (getchar() != '\n');
                printf("Input the score of course%d:",j+1);
                ret=scanf("%d",&stu[i].score[j]);
            }
        }
    }
    for (i=0; i<n; i++)
    {
        stu[i].total = 0;
        for (j=0; j<m; j++)
        {
            stu[i].total += stu[i].score[j];
        }
        stu[i].average = stu[i].total / m;
    }
}

void Calculate(int n,int m,STUDENT stu[])
{
    int i,j,total;
    for (i=0; i<m; i++)
    {
        total =0;
        for (j=0; j<n; j++)
        {
            total += stu[j].score[i];
        }
        printf("Course%d total: %d average: %d\n",i+1,total,total/n);
    }
}

void CalculateStu(int n,STUDENT stu[])
{
    int i;
    for (i=0; i<n; i++)
    {
        printf("%ld %s total:%d average:%d\n",stu[i].ID,stu[i].name,stu[i].total,stu[i].average);
    }
}

void SelectionSort(STUDENT stu[],int n,int m,int (*compare)(int a,int b))
{
    int i,j,k;
    STUDENT _stu;
    for (i=0; i<n-1; i++)
    {
        k=i;
        for (j=i+1; j<n; j++)
        {
            if (compare(stu[k].total,stu[j].total))
                k=j;
        }
        if (k != i)
        {
            _stu = stu[i];
            stu[i] = stu [k];
            stu[k] = _stu;
        }
    }
    for (i=0; i<n; i++)
    {
        printf("No.%d %ld %s total:%d\n",i+1,stu[i].ID,stu[i].name,stu[i].total);
    }
}

int Descending(int a,int b)
{
    return a<b;
}

int Ascending(int a,int b)
{
    return a>b;
}

void Sort(STUDENT stu[],int n,int m)
{
    int i,j,k;
    STUDENT _stu;
    for (i=0; i<n-1; i++)
    {
        k=i;
        for (j=i+1; j<n; j++)
        {
            if (stu[k].ID > stu[j].ID)
                k=j;
        }
        if (k != i)
        {
            _stu = stu[i];
            stu[i] = stu [k];
            stu[k] = _stu;
        }
    }
}

void Sortbyname(STUDENT stu[],int n,int m)
{
    int i,j,k;
    STUDENT _stu;
    for (i=0; i<n-1; i++)
    {
        k=i;
        for (j=i+1; j<n; j++)
        {
            if (strcmp(stu[k].name,stu[j].name) > 0)
                k=j;
        }
        if (k != i)
        {
            _stu = stu[i];
            stu[i] = stu [k];
            stu[k] = _stu;
        }
    }
}

void Output(STUDENT stu[],int n,int m,int type)
{
    int i,j;
    for (i=0; i<n; i++)
    {
        if (type == 0)
        {
            printf("%ld %s ",stu[i].ID,stu[i].name);
        }
        else
        {
            printf("%s %ld ",stu[i].name,stu[i].ID);
        }
        for (j=0; j<m; j++)
        {
            printf("%d ",stu[i].score[j]);
        }
        putchar('\n');
    }
}


void Search(STUDENT stu[],int n,int m)
{
    int i,j,mid,ret;
    int find=0;
    long key;
    Sort(stu,n,m);
    printf("Input a ID :");
    ret=scanf("%ld",&key);
    while (ret !=1)
    {
        while (getchar()!= '\n');
        printf("Input a ID :");
        ret=scanf("%ld",&key);
    }
    i=0;
    j=n-1;
    while (find == 0 && i<=j)
    {
        mid = i+(j-i)/2;
        if (stu[mid].ID == key)
        {
            find = 1;
        }
        else if (stu[mid].ID > key)
        {
            j=mid-1;
        }
        else
        {
            i=mid+1;
        }
    }
    if (find == 0)
    {
        printf("Not found!\n");
    }
    else
    {
        printf("%ld %s ",stu[mid].ID,stu[mid].name);
        for (j=0; j<m; j++)
        {
            printf("%d ",stu[mid].score[j]);
        }
        putchar('\n');
    }
}

void Searchbyname(STUDENT stu[],int n,int m)
{
    int i,j,mid;
    int find=0;
    char key[MAXNAME];
    Sortbyname(stu,n,m);
    printf("Input a name :");
    scanf("%s",key);
    i=0;
    j=n-1;
    while (find == 0 && i<=j)
    {
        mid = i+(j-i)/2;
        if (! strcmp(stu[mid].name,key))
        {
            find = 1;
        }
        else if (strcmp(stu[mid].name,key) > 0)
        {
            j=mid-1;
        }
        else
        {
            i=mid+1;
        }
    }
    if (find == 0)
    {
        printf("Not found!\n");
    }
    else
    {
        printf("%s %ld ",stu[mid].name,stu[mid].ID);
        for (j=0; j<m; j++)
        {
            printf("%d ",stu[mid].score[j]);
        }
        putchar('\n');
    }
}

void Analysis(STUDENT stu[],int n,int m)
{
    int i,j,r;
    int a,b,c,d,e;
    printf("Course\tBest\tGood\tMiddle\tPass\tFail\n");
    for (j=0; j<m; j++)
    {
        a=b=c=d=e=0;
        for (i=0; i<n; i++)
        {
            r=stu[i].score[j]/10;
            switch (r)
            {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                e++;
                break;
            case 6:
                d++;
                break;
            case 7:
                c++;
                break;
            case 8:
                b++;
                break;
            case 9:
            case 10:
                a++;
                break;
            }
        }
        printf("%d\t%d %.0f%%\t%d %.0f%%\t%d %.0f%%\t%d %.0f%%\t%d %.0f%%\n",j+1,a,(float)a/(n+1)*100,
               b,(float)b/(n+1)*100,c,(float)c/(n+1)*100,d,(float)d/(n+1)*100,e,(float)e/(n+1)*100);
    }
}

void OutputAll(STUDENT stu[],int n,int m)
{
    int i,j;
    for (i=0; i<n; i++)
    {
        printf("%ld %s ",stu[i].ID,stu[i].name);
        for (j=0; j<m; j++)
        {
            printf("%d ",stu[i].score[j]);
        }
        printf("total:%d average:%d\n",stu[i].total,stu[i].average);
    }
}

void WritetoFile(STUDENT stu[],int n,int m)
{
    int i;
    FILE *fp;
    if ((fp=fopen("student.txt","w")) == NULL)
    {
        printf("Failure to open student.txt!\n");
        exit(0);
    }
    fprintf(fp,"%d\t%d",n,m);
    i=fwrite(stu,sizeof(STUDENT),n,fp);
    fclose(fp);
    if (i==n)
    {
        printf("All is Done!\n");
    }
    else
    {
        printf("Data lost!\n");
    }
}

void ReadfromFile(STUDENT stu[],STUDENT _stu[],int *n,int *m)
{
    FILE *fp;
    int i;
    if ((fp=fopen("student.txt","r")) == NULL)
    {
        printf("Failure to open student.txt!\n");
        exit(0);
    }
    fscanf(fp,"%d\t%d",n,m);
    for (i=0; !feof(fp); i++)
    {
        fread(&stu[i],sizeof(STUDENT),1,fp);
    }

    if (fclose(fp) == 0)
    {
        printf("All is Done!\n");
    }
    else
    {
        printf("Something goes wrong!\n");
    }
    for (i=0; i<*n; i++)
    {
        _stu[i]=stu[i];
    }
}
