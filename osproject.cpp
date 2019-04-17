#include<queue>
#include<iostream>
#include<stdio.h>
using namespace std;
#define MAX 1000
#define QUANTUM 4

int flag[MAX],arrival_time[MAX],burst_time[MAX],priority[MAX],rt[MAX],ft[MAX],fe[MAX],fe_flag[MAX],pid[MAX],tms,qt[MAX];

queue<int>round_r; 
void Round_R() 
{
      if(!round_r.empty())
      {
      	if(rt[round_r.front()]>0 && qt[round_r.front()]<4)
      	{
          		qt[round_r.front()]++;
          		rt[round_r.front()]--;
          		if(rt[round_r.front()]==0)
          		{
            	ft[round_r.front()]=tms+1;
            	round_r.pop();
          		}
          		if(rt[round_r.front()]!=0 && qt[round_r.front()]==4)
          		{
				qt[round_r.front()]=0;
				round_r.push(round_r.front());
				round_r.pop();
          		}
        	}
      }
}

int main()
{
int n=0,smallest=0,last_smallest=-1,min,sum=0,large=0;
    printf("\n\nEnter Number Of Processes : ");
	scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
    	printf("\n\n********** Process : %d **********\n\n",i+1);
		printf("Enter Process Id : ");
		scanf("%d",&pid[i]);
		printf("Arrival Time : ");
		scanf("%d",&arrival_time[i]);
		printf("Burst Time : ");
		scanf("%d",&burst_time[i]);
		printf("Priority : ");
		scanf("%d",&priority[i]);
    		if(arrival_time[i]>large)
    		  	large=arrival_time[i];
    		  sum+=burst_time[i];
    		  rt[i]=burst_time[i];
    }
    min=MAX;
    for(tms=0;!round_r.empty() || tms<=sum+large;tms++)
    {
      min=MAX;
      smallest=-1;
      for(int i=0;i<n;i++)
      {
      	if(arrival_time[i]<=tms && priority[i]<min && rt[i]>0 && !flag[i])
      	{
      		min=priority[i];
          		smallest=i;
        	}
      }
      if(smallest==-1 && !round_r.empty())
      {
      	if(last_smallest !=-1 && rt[last_smallest]==0)
      	{
      		    ft[last_smallest]=tms;
          		flag[last_smallest]=1;
        	}
        	last_smallest=-1;
        	Round_R();
        	continue;
      }
      else if(smallest!=-1 && !round_r.empty() && last_smallest==-1)
      {
      	if(qt[round_r.front()]<=4 && qt[round_r.front()]>0)
      	{
      		round_r.push(round_r.front());
      		round_r.pop();
        	}
      }
      if(smallest!=-1 && !fe_flag[smallest])
      {
      	fe[smallest]=tms-arrival_time[smallest];
      	fe_flag[smallest]=1;
      }
      if( smallest!=last_smallest && last_smallest!=-1 && !flag[last_smallest])
      {
      	round_r.push(last_smallest);
      	flag[last_smallest]=1;
      }
      if(smallest !=-1)
      	rt[smallest]--;
      
      if((smallest !=-1) && ((rt[smallest]==0) ||(burst_time[smallest]-rt[smallest])==QUANTUM))
      {
      	if((burst_time[smallest]-rt[smallest])==QUANTUM && rt[smallest]!=0)
      	{
      		flag[smallest]=1;
      		round_r.push(smallest);
        	}
       	else if(smallest!=-1)
       	{
          		ft[smallest]=tms+1;
          		flag[smallest]=1;
        	}
      }
      last_smallest=smallest;
    }
   	printf("\n***************************************************************");
	printf("\nProcess Id | Arrival_Time| Burst_Time | Completion_Time |Turn_around_Time|Waiting_Time \n");
	float average_waiting=0;
    for(int i=0;i<n;i++)
    {
    	printf("%d		%d		%d	   %d                %d                   %d\n",pid[i],arrival_time[i],burst_time[i],ft[i],ft[i]-arrival_time[i],ft[i]-burst_time[i]-arrival_time[i]);
    	average_waiting=average_waiting+(ft[i]-burst_time[i]-arrival_time[i]);
    	
	}
	printf("\nAverage Waiting Time : %f ms",average_waiting/(n*1.0));
	
    return 0;
}









