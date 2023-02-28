class Job:
    def __init__(self, name, estimated_time):
        # Initialize a new job with a name, estimated run time, waiting time, and priority
        self.name = name
        self.estimated_time = estimated_time
        self.waiting_time = 0
        self.priority = 1

    def update_priority(self):
        # Update the priority of the job based on its waiting time and estimated run time
        self.priority = 1 + self.waiting_time / self.estimated_time

    def __str__(self):
        # Define a string representation of the job for debugging purposes
        return f"{self.name}(priority={self.priority}, estimated_time={self.estimated_time}, waiting_time={self.waiting_time})"


def schedule(jobs):
    # Schedule the given list of jobs using the priority algorithm described in the question
    time = 0
    waiting_jobs = jobs.copy()  # Create a copy of the list of waiting jobs
    completed_jobs = []  # Initialize an empty list of completed jobs

    while waiting_jobs:
        # Iterate over the waiting jobs until there are no more jobs left to schedule
        waiting_jobs.sort(key=lambda j: j.priority)  # Sort the waiting jobs by priority
        job = waiting_jobs.pop(0)  # Select the job with the highest priority
        print(f"Time {time}: Running job {job.name}")

        # Run the selected job for its estimated run time and update waiting times and priorities
        for t in range(job.estimated_time):
            time += 1
            job.waiting_time = time - job.estimated_time
            for other_job in waiting_jobs:
                other_job.waiting_time += 1
                other_job.update_priority()
            job.update_priority()
            print(f"Time {time}: {job.name}({job.priority})")

        completed_jobs.append(job)  # Add the completed job to the list of completed jobs

    # Calculate the total waiting time and average waiting time for all completed jobs
    total_waiting_time = sum(j.waiting_time for j in completed_jobs)
    average_waiting_time = total_waiting_time / len(completed_jobs)

    # Return the list of completed jobs and the average waiting time
    return completed_jobs, average_waiting_time


if __name__ == '__main__':
    # Prompt the user to enter job names and estimated run times, and create a list of waiting jobs
    jobs = []
    while True:
        name = input("Enter job name (or 'done' to finish): ")
        if name == "done":
            break
        estimated_time = int(input("Enter estimated run time: "))
        jobs.append(Job(name, estimated_time))

    # Schedule the waiting jobs using the priority algorithm and output the results
    completed_jobs, avg_waiting_time = schedule(jobs)
    print("Gantt chart:")
    for job in completed_jobs:
        print(f"{job.name} ", end="")
    print()
    print("Individual waiting times:")
    for job in completed_jobs:
        print(f"{job.name}: {job.waiting_time}")
    print(f"Average waiting time: {avg_waiting_time}")
