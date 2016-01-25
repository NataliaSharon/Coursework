#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/wait.h> 
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>

#define NUMBER_OF_PROCESSES 5
#define MAX_EXPERIMENT_DURATION 1000

char req3[] = "OUTPUT1.csv";
char req4[] = "OUTPUT2.csv";	
char req5[] = "OUTPUT3.csv";	
char req7[] = "CPUTimings.html";
char req81[] = "TIMINGS1.html"; //without CPU aff, equal priorities
char req82[] = "TIMINGS2.html"; //with CPU aff, equal priorities
char req83[] = "TIMINGS3.html"; //with CPU aff, non-equal priorities
char req84[] = "TIMINGS4.html"; //without CPU aff, equal priorities, 15 processes
char req85[] = "TIMINGS5.html"; //with CPU aff, equal priorities, 15 processes
char req86[] = "TIMINGS6.html"; //with CPU aff, non-equal priorities 15 processes

struct timeval startTime, currentTime;
//time in milliseconds
long int getDifferenceInMilliSeconds(struct timeval start, struct timeval end);
//array which holds run times of child processes
static long int *pRunTimes;

//CPU core affinity
cpu_set_t cpuset;

void childProcess(struct timeval startTime, struct timeval currentTime, int index)
{
	
	pRunTimes[getDifferenceInMilliSeconds(startTime,currentTime)] = index;

}

long int getDifferenceInMilliSeconds(struct timeval start, struct timeval end)
{
	int seconds = end.tv_sec - start.tv_sec;
	int useconds = end.tv_usec - start.tv_usec;
	int mtime = (seconds * 1000 + useconds / 1000.0);
	return mtime;
}

int main() 
{
	//CPU core affinity (REQ4)
	CPU_ZERO(&cpuset);
	CPU_SET(rand() % 7, &cpuset); // which core to run on
	sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpuset);
	
	//share array between processes
	pRunTimes = mmap(NULL, MAX_EXPERIMENT_DURATION*sizeof(pRunTimes), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	pid_t pid[NUMBER_OF_PROCESSES];
	int status;
	gettimeofday(&startTime, NULL); //start time

	//create as many child processes as defined
	for (int index = 1; index <= NUMBER_OF_PROCESSES; index++)
	{

		pid[index] = fork(); //last index will be the child process running ps - 1
		
		//set process priority (REQ5)
		switch (index)
		{
			case 1:
				setpriority(PRIO_PROCESS, getpid(), 0);
				break;
				
			case 2:
				setpriority(PRIO_PROCESS, getpid(), 5);
				break;

			case 3:
				setpriority(PRIO_PROCESS, getpid(), 10);
				break;

			case 4:
				setpriority(PRIO_PROCESS, getpid(), 15);
				break;		
			
			case 5:
				system("ps -l > PROCESSLIST1.txt");
				break;
		}
		
		if(pid[index] < 0) 
		{
			printf("Could not create process\n");
			exit(1);
		} else if(pid[index] == 0) 
		{
			printf("Hello from the child process with index %d\n", index);
			gettimeofday(&currentTime,NULL); //current time
			
			while (getDifferenceInMilliSeconds(startTime, currentTime) < MAX_EXPERIMENT_DURATION)
				{
					gettimeofday(&currentTime,NULL); //current time
					childProcess(startTime, currentTime, index);	
				}
				
			exit(1);
		} else if(pid[index] > 0) 
		{
			printf("Hello from the parent process\n");
		}
	}
	
	for (int wait = 0; wait <= NUMBER_OF_PROCESSES; wait++)
		waitpid(pid[wait], &status, WCONTINUED); //wait for child processes 
		
	//writing to file
	FILE *file = fopen(req83, "w");
	int constantHeight = 65;
	int constantWdith = 1;
	
	if (!file)
	{
		printf("File could not open\n");
	} else
	{	
		fprintf(file, "<svg width='%d' height='%d'>\n", MAX_EXPERIMENT_DURATION*constantWdith, (NUMBER_OF_PROCESSES-1)*constantHeight);	

		for (int i = 0; i < MAX_EXPERIMENT_DURATION; i++)
				fprintf(file, "<rect x='%d' y='%d' width='1' height='%d' style='fill:pink'/>\n", i*constantWdith, (pRunTimes[i] - 1) * constantHeight, constantHeight);
			
		//	fprintf(file, "%d, %d\n", i, pRunTimes[i]);
	
		fprintf(file, "<svg/>");	
	}
	fclose (file);
	
	printf("This code will be executed by both the child and parent\n");
	


}

