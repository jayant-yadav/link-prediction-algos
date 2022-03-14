#include <bits/stdc++.h>
using namespace std;
struct node
{
  int i;
  int j;
  double score;
  struct node*next;
};
	int a[100][100];//adjacency matrix
	int b[100][100];
	int c[100][100];
	int n;//dimensions of adjacency matrix
	int steps;
	int included[100];
	int who;
	int posofnext=0;
	int pgraphdistance[100][100];
    int padamicadar[100][100];
    int pjaccard[100][100];
    int pprefattach[100][100];
	int cmn_vertices[100][100];
	int total_friends[100][100];
	double sadamicadar[100][100];
    double sjaccard[100][100];
    int sprefattach[100][100]={0};
    int sgraphdistance[100][100];
    struct node*start=NULL;
    struct node*next;
    struct node*temp;
    struct node *end;
void create(int i,int j,double score)
{
	temp=(struct node*)malloc(sizeof(struct node));
	temp->next=NULL;
	temp->i=i;
	temp->j=j;
	temp->score=score;
	if(start==NULL)
	{
		start=temp;
		end=temp;
	}
	else
	{
		end->next=temp;
		end=temp;
	}
}
template<class T>void refine(double t,T s[100][100],int temp[100][100])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
            if(s[i][j]>=t&&a[i][j]==0)
            {
            temp[i][j]=1;
            }
		}
	}
}
void refine2(double t,int s[100][100],int temp[100][100])
{
    for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
            if(s[i][j]>=t&&a[i][j]==0&&s[i][j]!=0)
            {
            temp[i][j]=1;
            }
		}
	}
}
template<class t>double meanscore(t s[100][100])
{     
      double total=0,count=0;;
      for(int i=0;i<n;i++)
      {
      	  for(int j=0;j<n;j++)
      	  {
      	  		if(s[i][j]!=0&&a[i][j]==1)
      	  		{
      	  		total+=s[i][j];
      	  		count++;
      	  		}
      	  }
      }
return total/count;
}
template<class t>double maxscore(t s[100][100])
{
	double max=-1;
	  for(int i=0;i<n;i++)
      {
      	  for(int j=0;j<n;j++)
      	  {
      	  	if(s[i][j]>max&&a[i][j]==1)
      	  	{
      	  	max=s[i][j];
      	    }
      	  }
      }
return max;     
}
template<class t>double minscore(t s[100][100])
{
	double min=100000000;
	  for(int i=0;i<n;i++)
      {
      	  for(int j=0;j<n;j++)
      	  {
      	  	  if(s[i][j]<min&&a[i][j]==1)
      	  	  {
      	   	    min=s[i][j];
              }
		  }
      }
return min;     
}
int commonvertices(int i,int j)
   {
      int k,score=0;
      for(k=0;k<n;k++)
        {
            if(a[i][k]==1 && a[j][k]==1 && i!=j)
            {
                score++;
            }
        }
     return score;
   }
int totalfriends(int i,int j)
   {
       int friends=0;
       for(int k=0;k<n;k++)
       {
           if(a[i][k]==1)
           {
              friends++;
           }
           if(a[j][k]==1 )
           {
           	  friends++;
           }
	   }
      if(i==j)
      {
         return 0;
      }
	  else if(a[i][j]==1)
      { 
	    return friends-2;//2 is subtracted for not considering a nad b if there is a edge b/w a and b;
      }
	  else
      {
      return friends;
      }
   }
double calsadamicadar(int *c ,int *b)
{   
    double score=0.0;
	for(int i=0;i<n;i++)
	{   //score=0.0;
		if(c[i]==1 && b[i]==1)
		{   
		    double count=0;
			for(int j=0;j<n;j++)
			{
			  if(a[i][j]==1)
			  count++;
			}
			score=score  +  1/log10(count);
		}
	}
return score;
}
void jaccard()
{    
        int i,j;
		for(i=0;i<n;i++)
        {
            for(j=i;j<n;j++)
            {
               cmn_vertices[i][j]=commonvertices(i,j);
               cmn_vertices[j][i]=cmn_vertices[i][j];
            }
        }
       for(i=0;i<n;i++)
       {
            for(j=i;j<n;j++)
            {
               total_friends[i][j]=totalfriends(i,j)-cmn_vertices[i][j];
               total_friends[j][i]=total_friends[i][j];
            }
       }
       for(i=0;i<n;i++)
       {
            for(j=i;j<n;j++)
            {
                if(total_friends[i][j]!=0)
                {
                    sjaccard[i][j]=(cmn_vertices[i][j])/double(total_friends[i][j]);
                    sjaccard[j][i]=sjaccard[i][j];
                }
                else
                 {
                    sjaccard[i][j]=0;
                 }
            }
       }
}
void adamicadar()
{
	int i,j;
    for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)
			{
			sadamicadar[i][j]=0;
		    }
			else
			{
			sadamicadar[i][j]=calsadamicadar(a[i],a[j]);
	        }
		}
	}
}
int calsprefattach(int *c,int *d)
{
	int c1=0,c2=0;
	for(int i=0;i<n;i++)
	{
		if(c[i]==1)
		{
		c1++;
	    }
		if(d[i]==1)
		{
		c2++;
	    }
	}
	return c1*c2;
}
void prefattach()
{
	int i,j;
    for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)
			{
			sprefattach[i][j]=0;
		    }
			else if(sprefattach[i][j]==0)
			{
			sprefattach[j][i]=sprefattach[i][j]=calsprefattach(a[i],a[j]);
		    }
		}
	}
}
int notincluded(int i)
{
    int flag=1;
    for(int k=0;k<posofnext;k++)
    {
        if(included[k]==i)
        {
        flag=0;
        }
    }
return flag;
}
int includeneighbours(int i,int j)
{
    int temp=posofnext;;
    steps++;
    for(int z=0;z<temp;z++)
    {
        for(int k=0;k<n;k++)
        {
            if(a[included[z]][k]==1)
            {
               if(notincluded(k))
               {
               included[posofnext++]=k;
               }
            }
        }
    }
if(notincluded(j))
{
    includeneighbours(included[++who],j);
}
else
{
return steps;
}
}
void graphdistance()
{
	int i,j;
    for(i=0;i<n;i++)
    {
        for(j=i;j<n;j++)
        {
           if(i==j)
           {
           sgraphdistance[i][j]=0;
           }
		   else
           {
           included[0]=i;
           sgraphdistance[i][j]=includeneighbours(i,j);
           }
           sgraphdistance[i][j]=-1*sgraphdistance[i][j];
           sgraphdistance[j][i]=sgraphdistance[i][j];
           posofnext=1;
           who=0;
           steps=0;
        }
    }
}
double performance(int s[100][100])
{
    double c1=0,c2=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(b[i][j]==1&&s[i][j]==1)
            {
                c1++;
            }
            if(s[i][j]==1)
            {
                c2++;
            }
        }
    }
if(c2!=0)    
{
    return c1/c2;
    
}
else
{
    return 0.0;
}
}
template<class t> void print(t s[100][100])
{
		for(int i=0;i<n;i++)
	    {  
	    for(int j=0;j<n;j++)
    	cout<<s[i][j]<<"  ";
    	cout<<endl;
    	}	
}
/*void sortll(int num)
{
	struct node *i,*j,*tmp,*tmp2;
	i=start;
	while(i!=NULL)
	{
		j=i;
		while(j->next!=NULL)
		{
			if(j->score>j->next->score)
			{
				tmp=start;
				if(j!=start)
				{ 
				  while(tmp->next!=j)
				  tmp=tmp->next;
				}
				tmp2=j->next;
				tmp->next=tmp2;
				j->next=tmp2->next;
				tmp2->next=j;
			}
			j=j->next;
		}
		while(num&&start!=NULL)
		{
		c[start->i][start->j]=1;
		num--;
	    }
	}
}*/
void swap(struct node *a, struct node *b)
{
    double temp = a->score;
    a->score = b->score;
    b->score = temp;
    int t=a->i;
    a->i=b->i;
    b->i=t;
    t=a->j;
    a->j=b->j;
    b->j=t;
}
void bubbleSort()
{
    int swapped, i;
    struct node *ptr1;
    struct node *lptr = NULL;
 
    /* Checking for empty list */
    ptr1=start;
    if (ptr1 == NULL)
        return;
 
    do
    {
        swapped = 0;
        ptr1 = start;
 
        while (ptr1->next != lptr)
        {
            if (ptr1->score < ptr1->next->score)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
template<class t>void type2(int num,t s[100][100],int c[100][100])
{
    cout<<"SCORE MATRIX-\n";
    print(s);
    cout<<endl;
    cout<<endl;
 	for(int i=0;i<n;i++)
 	{
 		for(int j=0;j<n;j++)
 		{
 			if(a[i][j]==1)
 			{
 				s[i][j]=0;
 			}
 			else if(i!=j)
 			{
 				create(i,j,s[i][j]);
 			}
 		}
 	}
 	cout<<"score matrix for all possible future links-\n";
 	print(s);
 	cout<<endl;
    cout<<endl;
    bubbleSort();
    temp=start;
    int flag=0;
    num=num*2;
    struct node*temp2;
    while(flag==0)
    {
            if(num>0&&temp!=NULL)
            {
                temp2=temp;
                while(temp2!=NULL)
                {
                    if(temp2->score==temp->score)
                    {
                        c[temp2->i][temp2->j]=1;
                    }
                    temp2=temp2->next;
                }
                temp=temp->next;
                num--;
            }
            else
            {
                flag=1;
                break;
            }
    }
    cout<<"ADJACENCY MATRIX FOR PREDICTED LINKS\n";
 	print(c);
 	cout<<endl;
    cout<<endl;
}
template<class t>void edit(t s[100][100])
{
    for(int i=0;i<n;i++)
 	{
 		for(int j=0;j<n;j++)
 		{
 			if(a[i][j]==1)
 			{
 				s[i][j]=0;
 			}
 		}
 	}
}
int main() {
	int i,j,k,mode,type;
	double s;
	cout<<"************LINK PREDICTION AND ANALYSIS OF LINK PREDICTION ALGORITHMS************\n";
	try
	{
	cout<<"enter size\n";
	cin>>n;
	if(n>100)
	  {
    	throw n;
	  }
	}
	catch(int x)
	{
		cout<<"********************ERROR ENCOUNTERED***************************\n";
		cout<<"***************OUT OF BOUNDS************************\n";
		cout<<"**********ENTER A SMALLER VALUE*************\n";
		cin>>n;
		if(n>100)
		throw n;
	}
	catch(...)
	{
		cout<<"***********************INPUT VARIABLE CAN'T BE HANDLED*****************************\n";
		cout<<"************************PROGRAM TERMINATED************************";
		exit(0);
	}
	cout<<"enter adjacency matrix \n";
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			try
			{
			cin>>a[i][j];
			if(a[i][j]!=0&&a[i][j]!=1)
			{
			    throw a[i][j];
			}
			}
			catch(int x)
			{
			    cout<<"********EXCEPTION CAUGHT************\n";
			    cout<<"**********ENTER A VALID VALUE*************\n";
			    cin>>a[i][j];
			    if(a[i][j]!=0&&a[i][j]!=1)
			    {
			        throw a[i][j];
			    }
			}
			catch(...)
			{
			   	cout<<"***********************INPUT VALUE CAN'T BE HANDLED*****************************\n";
		        cout<<"************************PROGRAM TERMINATED************************";
		        exit(0); 
			}
		}
	}
   cout<<"enter adjacency matrix after time t\n";
   	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			try
			{
		    	cin>>a[i][j];
			    if(a[i][j]!=0&&a[i][j]!=1)
			    {
			    throw a[i][j];
			    }
			}
			catch(int x)
			{
			    cout<<"********EXCEPTION CAUGHT************\n";
			    cout<<"**********ENTER A VALID VALUE*************\n";
			    cin>>a[i][j];
			    if(a[i][j]!=0&&a[i][j]!=1)
			    {
			        throw a[i][j];
			    }
			}
			catch(...)
			{
			   	cout<<"***********************INPUT VALUE CAN'T BE HANDLED*****************************\n";
		        cout<<"************************PROGRAM TERMINATED************************";
		        exit(0); 
			}
			if(a[i][j]==b[i][j]==1)
			{
			b[i][j]=0;
			}
		}
	}
   adamicadar();
   jaccard();
   prefattach();
   graphdistance();
	cout<<"select type\n";
	try
	{
	cin>>type;
	   if(type!=2&&type!=1)
	   {
	   throw type;
	   }
	}
    catch(int x)
	{
	cout<<"********EXCEPTION CAUGHT************\n";
	cout<<"**********ENTER A VALID VALUE*************\n";
	cin>>type;
	   if(type!=1&&type!=2)
       {
	    throw type;
       }
    }
	catch(...)
	{
   	cout<<"***********************INPUT VALUE CAN'T BE HANDLED*****************************\n";
   	cout<<"************************PROGRAM TERMINATED************************";
	exit(0); 
	}
	if(type==1)
	{
	     cout<<"select mode"<<endl;
	     cout<<"1.compares on basis scores of mean score value of existing links useful to predict average number of links with average accuracy"<<endl;
	     cout<<"2.compares on basis scores of max score value of existing links useful to predict less number of links but accurate ones"<<endl;
	     cout<<"3.compares on basis scores of min value of existing links useful to predict more number of links but less accurate"<<endl;
	     try
	     {
	     cin>>mode;
	     if(mode!=2&&mode!=1&&mode!=3)
	     {
	         throw mode;
	     }
	     }    
	     catch(int x)
      	 {
	     cout<<"********EXCEPTION CAUGHT************\n";
	     cout<<"**********ENTER A VALID VALUE*************\n";
	     cin>>mode;
	     if(mode!=1&&mode!=2&&mode!=3)
         {
	        throw mode;
         }
         }
	     catch(...)
	     {
   	     cout<<"***********************INPUT VALUE CAN'T BE HANDLED*****************************\n";
   	     cout<<"************************PROGRAM TERMINATED************************";
	     exit(0); 
	     }
         if(mode==1)
         {
   	     refine(meanscore(sadamicadar),sadamicadar,padamicadar);
   	     cout<<"***************ADAMIC ADAR ALGORITHM FOR LINK PREDICTION***************";
         cout<<endl;
         cout<<"SCORE MATRIX-\n";
         print(sadamicadar);
         cout<<endl;
         cout<<endl;
         edit(sadamicadar);
         cout<<"score matrix for all possible future links-\n";
         print(sadamicadar);
         cout<<endl;
         cout<<endl;
         cout<<"ADJACENCY MATRIX FOR PREDICTED LINKS\n";
         print(padamicadar);
         cout<<endl;
         cout<<endl;
   	     refine(meanscore(sjaccard),sjaccard,pjaccard);
   	     cout<<"***************JACCARD ALGORITHM FOR LINK PREDICTION***************";
         cout<<endl;
         cout<<"SCORE MATRIX-\n";
         print(sjaccard);
         cout<<endl;
         cout<<endl;
         edit(sjaccard);
         cout<<"score matrix for all possible future links-\n";
         print(sjaccard);
         cout<<endl;
         cout<<endl;
         cout<<"ADJACENCY MATRIX FOR PREDICTED LINKS\n";
         print(pjaccard);
         cout<<endl;
         cout<<endl;
   	     refine(meanscore(sprefattach),sprefattach,pprefattach);
   	     cout<<"***************PREFERENTIAL ATTACHMENT ALGORITHM FOR LINK PREDICTION************";
         cout<<endl;
         cout<<"SCORE MATRIX-\n";
         print(sprefattach);
         cout<<endl;
         cout<<endl;
         edit(sprefattach);
         cout<<"score matrix for all possible future links-\n";
         print(sprefattach);
         cout<<endl;
         cout<<endl;
         cout<<"ADJACENCY MATRIX FOR PREDICTED LINKS\n";
         print(pprefattach);
         cout<<endl;
         cout<<endl;
   	     refine2(meanscore(sgraphdistance),sgraphdistance,pgraphdistance);
         cout<<"***************GRAPH DISTANCE ALGORITHM FOR LINK PREDICTION***************";
         cout<<endl;
         cout<<"SCORE MATRIX-\n";
         print(sgraphdistance);
         cout<<endl;
         cout<<endl;
         edit(sgraphdistance);
         cout<<"score matrix for all possible future links-\n";
         print(sgraphdistance);
         cout<<endl;
         cout<<endl;
         cout<<"ADJACENCY MATRIX FOR PREDICTED LINKS\n";
         print(pgraphdistance);
         cout<<endl;
         cout<<endl;
         }
         else if(mode==2)
         {
   	     refine(maxscore(sadamicadar),sadamicadar,padamicadar);
   	     cout<<"***************ADAMIC ADAR ALGORITHM FOR LINK PREDICTION***************";
         cout<<endl;
         cout<<"SCORE MATRIX-\n";
         print(sadamicadar);
         cout<<endl;
         cout<<endl;
         edit(sadamicadar);
         cout<<"score matrix for all possible future links-\n";
         print(sadamicadar);
         cout<<endl;
         cout<<endl;
         cout<<"ADJACENCY MATRIX FOR PREDICTED LINKS\n";
         print(padamicadar);
         cout<<endl;
         cout<<endl;
   	     refine(maxscore(sjaccard),sjaccard,pjaccard);
   	     cout<<"***************JACCARD ALGORITHM FOR LINK PREDICTION***************";
         cout<<endl;
         cout<<"SCORE MATRIX-\n";
         print(sjaccard);
         cout<<endl;
         cout<<endl;
         edit(sjaccard);
         cout<<"score matrix for all possible future links-\n";
         print(sjaccard);
         cout<<endl;
         cout<<endl;
         cout<<"ADJACENCY MATRIX FOR PREDICTED LINKS\n";
         print(pjaccard);
         cout<<endl;
         cout<<endl;
   	     refine(maxscore(sprefattach),sprefattach,pprefattach);
   	     cout<<"***************PREFERENTIAL ATTACHMENT ALGORITHM FOR LINK PREDICTION************";
         cout<<endl;
         cout<<"SCORE MATRIX-\n";
         print(sprefattach);
         cout<<endl;
         cout<<endl;
         edit(sprefattach);
         cout<<"score matrix for all possible future links-\n";
         print(sprefattach);
         cout<<endl;
         cout<<endl;
         cout<<"ADJACENCY MATRIX FOR PREDICTED LINKS\n";
         print(pprefattach);
         cout<<endl;
         cout<<endl;
   	     refine2(maxscore(sgraphdistance),sgraphdistance,pgraphdistance);
         cout<<"***************GRAPH DISTANCE ALGORITHM FOR LINK PREDICTION***************";
         cout<<endl;
         cout<<"SCORE MATRIX-\n";
         print(sgraphdistance);
         cout<<endl;
         cout<<endl;
         edit(sgraphdistance);
         cout<<"score matrix for all possible future links-\n";
         print(sgraphdistance);
         cout<<endl;
         cout<<endl;
         cout<<"ADJACENCY MATRIX FOR PREDICTED LINKS\n";
         print(pgraphdistance);
         cout<<endl;
         cout<<endl;
        }
        else if(mode==3)
         {
   	     refine(minscore(sadamicadar),sadamicadar,padamicadar);
   	     cout<<"***************ADAMIC ADAR ALGORITHM FOR LINK PREDICTION***************";
         cout<<endl;
         cout<<"SCORE MATRIX-\n";
         print(sadamicadar);
         cout<<endl;
         cout<<endl;
         edit(sadamicadar);
         cout<<"score matrix for all possible future links-\n";
         print(sadamicadar);
         cout<<endl;
         cout<<endl;
         cout<<"ADJACENCY MATRIX FOR PREDICTED LINKS\n";
         print(padamicadar);
         cout<<endl;
         cout<<endl;
   	     refine(minscore(sjaccard),sjaccard,pjaccard);
   	     cout<<"***************JACCARD ALGORITHM FOR LINK PREDICTION***************";
         cout<<endl;
         cout<<"SCORE MATRIX-\n";
         print(sjaccard);
         cout<<endl;
         cout<<endl;
         edit(sjaccard);
         cout<<"score matrix for all possible future links-\n";
         print(sjaccard);
         cout<<endl;
         cout<<endl;
         cout<<"ADJACENCY MATRIX FOR PREDICTED LINKS\n";
         print(pjaccard);
         cout<<endl;
         cout<<endl;
   	     refine(minscore(sprefattach),sprefattach,pprefattach);
   	     cout<<"***************PREFERENTIAL ATTACHMENT ALGORITHM FOR LINK PREDICTION************";
         cout<<endl;
         cout<<"SCORE MATRIX-\n";
         print(sprefattach);
         cout<<endl;
         cout<<endl;
         edit(sprefattach);
         cout<<"score matrix for all possible future links-\n";
         print(sprefattach);
         cout<<endl;
         cout<<endl;
         cout<<"ADJACENCY MATRIX FOR PREDICTED LINKS\n";
         print(pprefattach);
         cout<<endl;
         cout<<endl;
   	     refine2(minscore(sgraphdistance),sgraphdistance,pgraphdistance);
         cout<<"***************GRAPH DISTANCE ALGORITHM FOR LINK PREDICTION***************";
         cout<<endl;
         cout<<"SCORE MATRIX-\n";
         print(sgraphdistance);
         cout<<endl;
         cout<<endl;
         edit(sgraphdistance);
         cout<<"score matrix for all possible future links-\n";
         print(sgraphdistance);
         cout<<endl;
         cout<<endl;
         cout<<"ADJACENCY MATRIX FOR PREDICTED LINKS\n";
         print(pgraphdistance);
         cout<<endl;
         cout<<endl;
        }
    }
    if(type==2)
    {  
         int num;
	     cout<<"enter top number of links to be predicted\n";
 	     cin>>num;
         cout<<"***************ADAMIC ADAR ALGORITHM FOR LINK PREDICTION***************";
         cout<<endl;
         type2(num,sadamicadar,padamicadar);
         cout<<"***************JACCARD ALGORITHM FOR LINK PREDICTION***************";
         cout<<endl;
         type2(num,sjaccard,pjaccard);
         cout<<"***************PREFERENTIAL ATTACHMENT ALGORITHM FOR LINK PREDICTION************";
         cout<<endl;
         type2(num,sprefattach,pprefattach);
         cout<<"***************GRAPH DISTANCE ALGORITHM FOR LINK PREDICTION***************";
         cout<<endl;
         type2(num,sgraphdistance,pgraphdistance);
    }
    cout<<"**************************PERFORMANCE ANALYSIS**************************\n";
    cout<<endl;
    cout<<endl;
	cout<<"***************ADAMIC ADAR ALGORITHM FOR LINK PREDICTION***************\n";
	cout<<"SCORE MATRIX for all possible future links-\n";
	print(sadamicadar);
	cout<<endl;
	cout<<endl;
	cout<<"actual links that appeared after time t which were not present initially are:\n";
    print(b);
    cout<<endl;
    cout<<endl;
	cout<<"links predicted by ADAMIC ADAR algorithm for LINK PREDICTION are-\n";
	print(padamicadar);
	cout<<endl;
	cout<<"accuracy-"<<performance(padamicadar);
	cout<<endl;
	cout<<endl;
	cout<<"***************JACCARD ALGORITHM FOR LINK PREDICTION***************\n";
	cout<<"SCORE MATRIX-\n";
	print(sjaccard);
	cout<<endl;
	cout<<endl;
	cout<<"actual links that appeared after time t which were not present initially are:\n";
    print(b);
    cout<<endl;
    cout<<endl;
	cout<<"links predicted by JACCARD algorithm for LINK PREDICTION are-\n";
	print(pjaccard);
	cout<<endl;
	cout<<endl;
	cout<<"accuracy-"<<performance(pjaccard);
	cout<<endl;
	cout<<endl;
	cout<<"***************PREFERENTIAL ATTACHMENT ALGORITHM FOR LINK PREDICTION************\n";
	print(sprefattach);
	cout<<endl;
	cout<<endl;
	cout<<"actual links that appeared after time t which were not present initially are:\n";
    print(b);
    cout<<endl;
    cout<<endl;
	cout<<"links predicted by PREFERENTIAL ATTACHMENT algorithm for LINK PREDICTION are-\n";
	print(pprefattach);
	cout<<endl;
	cout<<endl;
	cout<<"accuracy-"<<performance(pprefattach);
	cout<<endl;
	cout<<endl;
	cout<<"***************GRAPH DISTANCE ALGORITHM FOR LINK PREDICTION***************\n";
	print(sgraphdistance);
	cout<<endl;
	cout<<endl;
	cout<<"actual links that appeared after time t which were not present initially are:\n";
    print(b);
    cout<<endl;
    cout<<endl;
	cout<<"links predicted by GRAPH DISTANCE algorithm for LINK PREDICTION are-\n";
	print(pgraphdistance);
	cout<<endl;
	cout<<endl;
	cout<<"accuracy-"<<performance(pgraphdistance);
	cout<<endl;
	return 0;
}
