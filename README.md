Operating System Project

Problem Statement:
Consider a scheduling approach which is non pre-emptive similar to shortest job next in 
nature. The priority of each job is dependent on its estimated run time, and also the amount of 
time it has spent waiting. Jobs gain higher priority the longer they wait, which prevents 
indefinite postponement. The jobs that have spent a long time waiting compete against those 
estimated to have short run times. The priority can be computed as :
Priority = 1+ Waiting time / Estimated run time
Write a program to implement such an algorithm. Ensure
1. The input is given dynamically at run time by the user
2. The priority of each process is visible after each unit of time
3. The gantt chart is shown as an output
4. Calculate individual waiting time and average waiting time

Explanation:
Explaining the scheduling algorithm and the solution I provided.

The scheduling algorithm described in the question is a non-preemptive approach that is similar to the shortest job next algorithm. The priority of each job is determined by its estimated run time and the amount of time it has spent waiting. Jobs that have waited for a long time are given higher priority than jobs that have waited for a short time. The priority of each job is calculated using the formula:

Priority = 1 + Waiting time / Estimated run time

The program I provided implements this algorithm by defining a Job class that represents a single job. Each job has a name, an estimated run time, a waiting time (initialized to 0), and a priority (initialized to 1). The Job class also has a method called update_priority that updates the job's priority based on its waiting time and estimated run time.

The schedule function takes a list of Job objects as input and schedules them using the priority algorithm described above. The function uses a while loop to iterate over the waiting jobs until there are no more jobs left to schedule. At each iteration, the function sorts the waiting jobs by their priority and selects the job with the highest priority (i.e., the job that has been waiting the longest relative to its estimated run time). The function then runs the selected job for its estimated run time and updates the waiting times and priorities of all the other jobs based on the time spent waiting and their estimated run times. The function also keeps track of the completed jobs and calculates the total waiting time and average waiting time.

The main part of the program prompts the user to enter the job name and estimated run time for each job, creates a Job object for each job, and adds it to a list of waiting jobs. The program then calls the schedule function with the list of waiting jobs and outputs the results, including the Gantt chart, individual waiting times, and average waiting time.

I hope that helps explain the algorithm and solution! Let me know if you have any further questions.
