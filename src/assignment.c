#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h> 

int disp_menu_2(int nos,int n,int arr[nos][nos],int war[nos][nos],char* webs[100]);
int disp_menu_3(int nos,int arr[nos][nos],int war[nos][nos],char* webs[100]);
int disp_menu_4(int nos,int arr[nos][nos],int war[nos][nos],char* webs[100]);
int disp_menu_5(int nos,int arr[nos][nos],int war[nos][nos],char* webs[100]);


//*************printer********************

void filePrint(int nos, int arr[nos][nos], char *webs[100])
{
    FILE *ptr = fopen("fileOutput.csv", "w");
    for (int i = 0; i < nos; i++)
        fprintf(ptr, ",%s", webs[i]);
    fprintf(ptr, "\n");
    for (int i = 0; i < nos; i++)
    {
        fprintf(ptr, "%s", webs[i]);
        for (int j = 0; j < nos; j++)
            fprintf(ptr, ",%d", arr[i][j]);
        fprintf(ptr, "\n");
    }
}

//*************plot function******************
void plot(char * fname){
    int pid;
    if((pid = fork())==0){
        if(execlp("python", "python","visualise.py",fname,(char*)NULL)==-1){
        	execlp("python3", "python3","visualise.py",fname,(char*)NULL);
        };
    }
    exit(0);
}



//*************main menu***********************
int max(int a,int b)
{                                                       
    if(a>b)
        return(a);
    else
        return(b);
}

//**************************menu 1 question 1 reflexive***************************
bool m1q1(int n,int arr[n][n])
{
    bool res=true;
    for(int i=0;i<n;i++)
    {
        if(arr[i][i]==0)
        res=false;
    }
    return res;
}


//*************************menu 1 qustion 2 symetric**************************

bool m1q2(int n,int arr[n][n])
{
    bool res=true;
    for(int i=0;i<n;i++)
    {
        for(int j=i;j<n;j++)
        {
            if(arr[i][j]!=arr[j][i])
            res=false;
        }
    }
    return res;
}
//*******************menu 1 question 8 check transitive*********

bool transitive(int n,int arr[n][n],int war[n][n])
{
    bool res=true;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(war[i][j]!=arr[i][j])
            res=false;
        }
    }

    return res;
}

//**********************menu 1 question 3*********************
bool m1q3(int n,int arr[n][n],int war[n][n])
{
    int res=true;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]!=war[i][j])
            res=false;
        }
    }

    return res;
}

//**************************menu 1 question 4*********************

bool m1q4(int n,int arr[n][n])
{
    bool res=false;
    for(int i=0;i<n;i++)
    {
        if(arr[i][i]==1)
        {
            res=true;
            break;
        }
    }
    return res;
}

//*********************menu 1 question 5***************************

bool m1q5(int n,int arr[n][n])
{
    bool res=true;
    for(int i=0;i<n;i++)
    {
        for(int j=i;j<n;j++)
        {
            if(arr[i][j]==1)
            {
                if(arr[i][j]==arr[j][i])
                res=false;
            }
        }
    }
}


//*******************menu 1 question 6****************************

bool m1q6(int n,int arr[n][n])
{
    bool res=true;
    for(int i=0;i<n;i++)
    {
        for(int j=i;j<n;j++)
        {
            if(i!=j)
            {
                if(arr[i][j]==1)
                {
                    if(arr[i][j]==arr[j][i])
                    res=false;
                }
            }
        }
    }
}

//*********************menu 1 question 7************************

bool m1q7(int n,int arr[n][n],int war[n][n])
{
    bool res;
    res=m1q1(n,arr) & m1q2(n,arr) & transitive(n,arr,war);
    return res;
}

//*******************menu 1 question 8 check antisymetric*********

bool antiSym(int n,int arr[n][n])
{
    bool res=true;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i!=j)
            {
                if(arr[i][j]==arr[j][i] && arr[i][j]==1)
                res=false;
            }
        }
    }
    return res;
}



//****************to check lattice//////////////////////////////////


int lub(int a, int b, int nos, int arr[nos][nos])
{
    if (arr[a][b])
        return b;
    else if (arr[b][a])
        return a;
    
    int flag = 0;
    int upper_bounds[nos];
    for (int i = 0; i < nos; i++)
    {
        if (arr[a][i] && arr[b][i])
        {
            upper_bounds[flag] = i;
            flag++;
        }
    }

    if (flag == 0)
        return -1;
    if (flag == 1)
        return upper_bounds[0];
    int min = upper_bounds[0];
    for (int i = 1; i < flag; i++)
    {
        if (arr[upper_bounds[i]][min])
            min = upper_bounds[i];
        else if (arr[min][upper_bounds[i]] == 0)
            return -1;
    }
    return min;
}

int glb(int a, int b, int nos, int arr[nos][nos])
{
    if (arr[a][b])
        return a;
    else if (arr[b][a])
        return b;
    int flag = 0;
    int lower_bounds[nos];
    for (int i = 0; i < nos; i++)
    {
        if (arr[i][a] && arr[i][b])
        {
            lower_bounds[flag] = i;
            flag++;
        }
    }
    if (flag == 0)
        return -1;
    if (flag == 1)
        return lower_bounds[0];
    int maxi = lower_bounds[0];
    for (int i = 1; i < flag; i++)
    {
        if (arr[maxi][lower_bounds[i]])
            maxi = lower_bounds[i];
        else if (arr[lower_bounds[i]][maxi] == 0)
            return -1;
    }
    return maxi;
}

//********************************************************************************

void printerr(int nos,int arr[][nos])
{
    for(int i=0;i<nos;i++)
    {
        for(int j=0;j<nos;j++)
        printf("%d ",arr[i][j]);
        printf("\n");
    }
}

int disp_menu_1(int nos,int arr[nos][nos],int war[nos][nos],char* webs[100])
{
    int ans=0;
    printf("\n\nChoose your question :-\n");
    printf("1. Does every website has a link to itself? \n");
    printf("2. Is it possible to return back to previous website from the current website in one step? \n");
    printf("3. Does every website have a link to a website which is reachable from it? \n");
    printf("4. Does there exists a website that contains a link to itself ?\n");
    printf("5. Is it possible to return to previous website from the current website in one step ? \n");
    printf("6. Is it possible to return to previous website from the current website in one step ? ( excluding the cases where the current and prvious websites are same ) \n");
    printf("7. Is it possible to divide the network into multiple pieces such that every website in a piece is reachable from every other website from that piece?\n");
    printf("8. Is this relation an example of poset?\n");
    printf("9. Exit\n");
    scan_menu_1:
    scanf("%d", &ans);

    if(ans==1)
    {
        bool ans1=m1q1(nos,arr);
        if(ans1)
        {
            printf("Yes it has link for itself\n");
            return 1;
        }
        else
        {
            printf("No \n");
            return disp_menu_2(nos, ans,arr,war,webs);
            
        }
    }

    else if(ans==2)
    {
        bool ans2=m1q2(nos,arr);
        if(ans2)
        {
            printf(" Yes is it possible to always return back to previous website from the current website in one step");
            return 1;
        }
        else 
        {
            printf("No\n");
            return disp_menu_2(nos, ans,arr,war,webs);
        }
    }

    else if(ans==3)
    {
        bool ans3=m1q3(nos,arr,war);
        if(ans3)
        {
            printf(" Yes\n");
            return 1;
        }
        else
        {
            printf("No\n");
            return disp_menu_2(nos, ans,arr,war,webs);
        }
    }

    else if(ans==4)
    {
        bool ans4=m1q4(nos,arr);
        if(ans4)
        {
            printf("Yes \n");
            return 1;
        }
        else
        {
            printf("No \n");
            return 1;
        }
    }

    else if(ans==5)
    {
        bool ans5=m1q5(nos,arr);
        if(ans5)
        {
            printf("Yes \n");
            return 1;
        }
        else
        {
            printf("No \n");
            return 1;
        }
    }
    else if(ans==6)
    {
        bool ans6=m1q6(nos,arr);
        if(ans6)
        {
            printf("Yes \n");
            return 1;
        }
        else
        {
            printf("No \n");
            return 1;
        }

    }

    else if(ans==7)
    {
        bool ans7=m1q7(nos,arr,war);
        if(ans7)
        {
            printf("Yes\n");
            return disp_menu_3(nos,arr,war,webs);
        }
        else
        {
            printf("No\n");
            return disp_menu_2(nos,ans,arr,war,webs);
        }
    }
    else if(ans==8)
    {
        bool reflexive=m1q1(nos,arr);
        bool antisymetric=antiSym(nos,arr);
        bool trans=transitive(nos,arr,war);

        if(reflexive && antisymetric && trans)
        {   
            printf("Yes it is a poset!\n");
            return disp_menu_4(nos,arr,war,webs);
        }
        else
        {
            printf("Not a poset \n");
            return 1;

        }

    }
    else if(ans==9)
    {
        return 0;
    }
    else
    {
        printf("Invalid Input Please re-enter\n\n");
        goto scan_menu_1;
    }

    
    
    
}



//************************************menu 2**********************************************************************************


int disp_menu_2(int nos,int n,int arr[nos][nos],int war[nos][nos],char* webs[100])
{
    printf("\n\nDo you want to visualize how the network will look if we add minimum links to satisfy the property ( Enter 1 for yes and 0 for no )?\n");
    int ans;
    scanf_menu2:
    scanf("%d",&ans);
    
    
    if(ans==0)
    {
        return 1;

        
    }
    else if(ans==1)
    {
        int disp[nos][nos];
        if(n==1)
        {
            for(int i=0;i<nos;i++)
            {
                for(int j=0;j<nos;j++)
                {
                    if(i==j)
                    disp[i][j]=1;
                    else
                    disp[i][j]=arr[i][j];
                }
            }
            
        }
        else if(n==2)
        {
            for(int i=0;i<nos;i++)
            {
                for(int j=0;j<nos;j++)
                {
                    if(arr[i][j]==0&&arr[j][i]==0)
                    disp[i][j]=0;
                    else
                    {
                        disp[i][j]=1;
                        disp[j][i]=1;
                    }
                }
            }
        }
        else if(n==3)
        {
            for(int i=0;i<nos;i++)
            {
                for(int j=0;j<nos;j++)
                {
                    disp[i][j]=war[i][j];
                }
            }
        }
        else if(n==7)
        {
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    if(i==j)
                    disp[i][j]=1;
                    else
                    disp[i][j]=arr[i][j];
                }
            }

            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    if(arr[i][j]==1)
                    {
                        disp[i][j]=1;
                        disp[j][i]=1;

                    }
                    else
                    disp[i][j]=0;
                }
            }
            for(int k=0;k<nos;k++)
            {
                for(int i=0;i<nos;i++)
                {
                    for(int j=0;j<nos;j++)
                    disp[i][j]=max(disp[i][j],disp[i][k]&&disp[k][j]);
                }
            }
        }
        
        filePrint(nos,disp,webs);
        plot("fileOutput.csv");

        return 1;

        

    }
    else
    {
        printf("invalid input please re-enter \n");
        goto scanf_menu2;
    }


}

//*********************************menu 3*********************************************
int disp_menu_3(int nos,int arr[nos][nos],int war[nos][nos],char* webs[100])
{   
    printf("\n\nDo you want to print nodes of all pieces (enter 0 for no and 1 for yes) \n");
    int ans;
    scanf_menu3:
    
    scanf("%d",&ans);

    if(ans==0)
    {
        return 1;
    }
    else if(ans==1)
    {   
        int eq=1;
        for(int i=0;i<nos;i++)
        {   
            
            for(int j=0;j<nos;j++)
            {
                if(i>j)
                {
                    if(war[i][j]==1)
                    break;
                    
                }
                if(war[i][j]==1)
                printf(" %s ",webs[j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Invalid input \n");
        goto scanf_menu3;
    }
    return 1;
}

//********************************menu 4**************************************************


int disp_menu_4(int nos,int arr[nos][nos],int war[nos][nos],char* webs[100])
{

    int ans=0;
    printf("\n\n1. Display the Hasse diagram\n");
    printf("2. Display the website whose link is available in every website\n");
    printf("3. Display the website which has links of every website\n");
    printf("4. Display the websites that do not have links to any other website except itself\n");
    printf("5. Display the websites which can't be reached from any other website except itself\n");
    printf("6. Given some websites, display the websites which are reachable from all of them\n");
    printf("7. Given some websites, display the websites from which you can reach all the websites.\n");
    printf("8. Is this relation an example of lattice?\n");
    printf("9. Return to Main Menu\n");
    scanf_menu4:
    scanf("%d",&ans);
    
    
    if(ans==1)
    {
        int hasse[nos][nos];
        for(int i=0;i<nos;i++)
       {
           for(int j=0;j<nos;j++)
           {
               hasse[i][j]=arr[i][j];
           }
       }

        for(int i=0;i<nos;i++)
       {
           for(int j=0;j<nos;j++)
           {
               if(i==j)
               {
                   hasse[i][j]=0;
               }
           }
       }

       for(int i=0;i<nos;i++)
       {
           for(int j=0;j<nos;j++)
           {
               
               if(hasse[i][j]==1)
               {
                   for(int k=0;k<nos;k++)
                   {
                       if(hasse[j][k]==1 )
                       hasse[i][k]=0;
                   }
               }
            }
       }
        
       filePrint(nos,hasse,webs);
       plot("fileOutput.csv");


    }
    else if(ans==2)
    {   
        int ans2[nos];
        for(int i=0;i<nos;i++)
        {   
            bool isLinked=true;
            for(int j=0;j<nos;j++)
            {
                if(arr[j][i]==0)
                isLinked=false;
            }
            if(isLinked)
            ans2[i]=1;
            else
            ans2[i]=0;
        }
        printf("Websites that have there links in all websites are :-\n");
        for(int i=0;i<nos;i++)
        {
            if(ans2[i]==1)
            printf(" %s \n",webs[i]);
        }
    }
    else if(ans==3)
    {
        int ans3[nos];
        for(int i=0;i<nos;i++)
        {
            bool hasLinks=true;
            for(int j=0;j<nos;j++)
            {
                if(arr[i][j]==0)
                hasLinks=false;
            }
            if(hasLinks)
            ans3[i]=1;
            else
            ans3[i]=0;
        }
        printf("Websites that have there links to all websites are :-\n");
        for(int i=0;i<nos;i++)
        {
            if(ans3[i]==1)
            printf(" %s \n",webs[i]);
        }
    }
    else if(ans==4)
    {
        int ans4[nos];
        for(int i=0;i<nos;i++)
        {
            bool lonely=true;
            for(int j=0;j<nos;j++)
            {
                if(i!=j)
                {
                    if(arr[i][j]==1)
                    lonely=false;
                }
                else
                {
                    if(arr[i][j]==0)
                    lonely=false;
                }
            }
            if(lonely)
            ans4[i]=1;
            else
            ans4[i]=0;
        }
        printf("Websites that have links to only themselves :-\n");
        for(int i=0;i<nos;i++)
        {
            if(ans4[i]==1)
            printf(" %s \n",webs[i]);
        }
    }
    else if(ans==5)
    {   
        int ans5[nos];
        for(int i=0;i<nos;i++)
        {
            bool notReachable=true;
            for(int j=0;j<nos;j++)
            {
                if(i!=j)
                {
                    if(arr[j][i]==1)
                    notReachable=false;
                }
                else
                {
                    if(arr[i][j]==0)
                    notReachable=false;
                }
            }
            if(notReachable)
            ans5[i]=1;
            else
            ans5[i]=0;
        }
        printf("Websites that can't be reached from any other website except themselves :-\n");
        for(int i=0;i<nos;i++)
        {
            if(ans5[i]==1)
            printf(" %s \n",webs[i]);
        }

    }
    else if(ans==6)
    {
        printf("Enter no of websites you wish to enter: \n");
        int webno;
        scanf("%d",&webno);
        for(int i=1;i<=nos;i++)
        {
            printf("%d for website %s \n",i,webs[i-1]);
        }
        int input[webno];
        for(int i=0;i<webno;i++)
        {
            while((getchar()) != '\n');

            scanf("%d",&input[i]);
        }

        int ans6[nos];
        for(int i=0;i<nos;i++)
        {
            int boolc=1;
            for(int j=0;j<webno;j++)
            {
                boolc=boolc & arr[input[j]-1][i];
            }
            if(boolc==1)
            ans6[i]=1;
            else
            ans6[i]=0;
        }

        printf("Websites that can be reached from all of these websites are :-\n");
        for(int i=0;i<nos;i++)
        {
            if(ans6[i]==1)
            printf(" %s \n",webs[i]);
        }

    }
    else if(ans==7)
    {
        printf("Enter no of websites you wish to enter: \n");
        int webno;
        scanf("%d",&webno);
        for(int i=1;i<=nos;i++)
        {
            printf("%d for website %s \n",i,webs[i-1]);
        }
        int input[webno];
        for(int i=0;i<webno;i++)
        {
            while((getchar()) != '\n');

            scanf("%d",&input[i]);
        }
        
        int ans7[nos];
        for(int i=0;i<nos;i++)
        {
            int boolc=1;
            for(int j=0;j<webno;j++)
            {
                boolc=boolc & arr[i][input[j]-1];
            }
            if(boolc==1)
            ans7[i]=1;
            else
            ans7[i]=0;
        }

        printf("Websites that can be reached from all of these websites are :-\n");
        for(int i=0;i<nos;i++)
        {
            if(ans7[i]==1)
            printf(" %s \n",webs[i]);
        }
    }
    else if(ans==8)
    {
        bool isLattice=true;
        for(int i=0;i<nos-1;i++)
        {
            for(int j=i+1;j<nos;j++)
            {
                if((glb(i,j,nos,arr)==-1)||(lub(i,j,nos,arr)==-1))
                {
                    isLattice=false;
                    
                }
            }
        }

        if(isLattice)
        {
            printf("\n\n Yes it is a lattice\n");
            return disp_menu_5(nos,arr,war,webs);
        }
        else
        {
            printf("\n\nNo it is not a lattice \n");
            return 1;

        }
    }
    else if(ans=9)
    {
        return 1;
    }
    else
    {
        printf("Invalid Input please re-enter \n");
        goto scanf_menu4;
    }
    return 1;
}

//********************************menu 5*************************************************************************

int disp_menu_5(int nos,int arr[nos][nos],int war[nos][nos],char* webs[100])
{
    printf("\n\n 1. Given two websites A and B , display the websites which is reachable by both A and B and can also reach to all such sites that both A and B can reach \n");
    printf(" 2. Given two websites A and B , display the websites which can reach both A and B and is also reachable from all such sites which can reach both A and B \n");
    printf(" 3. is the lattice distributive \n");
    printf(" 4. go back to menu 4 \n");

    int ans;

    scanf_menu5:
    scanf("%d",&ans);

    if(ans==1)
    {   
        printf("\n\n Enter numeral for website A and B :-");
        int i,j;
        scanf("%d",&i);
        while((getchar()) != '\n');
        scanf("%d",&j);

        printf("\n %s \n",webs[lub(i,j,nos,arr)]);

    }
    else if(ans==2)
    {   
        printf("\n\nEnter numeral for website A and B :-");
        int i,j;
        scanf("%d",&i);
        while((getchar()) != '\n');
        scanf("%d",&j);

        printf("\n %s \n",webs[glb(i,j,nos,arr)]);
        
    }
    else if(ans==3)
    {
        bool checkDis=true;
        for(int i=0;i<nos;i++)
        {
            for(int j=0;j<nos;j++)
            {
                for(int k=0;k<nos;k++)
                {
                    //x ∧ (y ∨ z) = (x ∧ y) ∨ (x ∧ z).
                    if(glb(i,lub(j,k,nos,arr),nos,arr)!=lub(glb(i,j,nos,arr),glb(i,k,nos,arr),nos,arr))
                    checkDis=false;
                }
            }
        }

        if(checkDis)
        {
            printf("\nYes it is distributive\n");
            return 1;
        }
        else
        {
            printf("\nNo it is not distributive \n");
            return 1;
        }
    }
    else if(ans==4)
    {
        disp_menu_4(nos,arr,war,webs);
    }
    else
    {   
        printf("Invalid Input: ");
        goto scanf_menu5;
    }

    return 1;
}



//**************************************************************************************************************

int main()
{
    //reading the csv file and storing the matrix.***********************************************************************
    
    FILE *ptr = fopen("SampleInput.csv", "r");
    char tmp[1000];
    char *webs[100];
    fgets(tmp, 1000, ptr);
    int nos = 1;
    char *val = strtok(tmp, ",");
    int i = 0;
    while (val)
    {
        webs[i] = strdup(val);
        i++;
        val = strtok(NULL, ",\r\n");
    }
    nos = i;
    
    
    int arr[nos][nos];
    int r = 0;
    while (fgets(tmp, 1000, ptr))
    {
        char *val = strtok(tmp, ",");

        for (int c = 0; c < nos; c++)
        {
            val = strtok(NULL, ",\r\n");
            arr[r][c] = atoi(val);
        }

        r++;
    }
    int war[nos][nos];
    for (int i = 0; i < nos; i++)
    {
        for (int j = 0; j < nos; j++)
        {
            war[i][j] = arr[i][j];
        }
    }
    //*************************************************************************************************************
    
    //warshals algo**********************
    for(int k=0;k<nos;k++)
        {
            for(int i=0;i<nos;i++)
            {
                for(int j=0;j<nos;j++)
                war[i][j]=max(war[i][j],war[i][k]&&war[k][j]);
            }
        }
     //******************************************************************************

    while(disp_menu_1(nos,arr,war,webs));
    return 0;
}