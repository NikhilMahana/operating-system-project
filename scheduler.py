class Job:
    def __init__(self, name, estimated_time):
        self.name = name
        self.estimated_time = estimated_time
        self.waiting_time = 0
        self.priority = 1

    def update_priority(self):
        self.priority = 1 + self.waiting_time / self.estimated_time

    def __str__(self):
        return f"{self.name}(priority={self.priority}, estimated_time={self.estimated_time}, waiting_time={self.waiting_time})"


def schedule(jobs):
    time = 0
    waiting_jobs = jobs.copy()
    completed_jobs = []

    while waiting_jobs:
        waiting_jobs.sort(key=lambda j: j.priority)
        job = waiting_jobs.pop(0)
        print(f"Time {time}: Running job {job.name}")
        for t in range(job.estimated_time):
            time += 1
            job.waiting_time = time - job.estimated_time
            for other_job in waiting_jobs:
                other_job.waiting_time += 1
                other_job.update_priority()
            job.update_priority()
            print(f"Time {time}: {job.name}({job.priority})")
        completed_jobs.append(job)

    total_waiting_time = sum(j.waiting_time for j in completed_jobs)
    average_waiting_time = total_waiting_time / len(completed_jobs)
    return completed_jobs, average_waiting_time


if __name__ == '__main__':
    jobs = []
    while True:
        name = input("Enter job name (or 'done' to finish): ")
        if name == "done":
            break
        estimated_time = int(input("Enter estimated run time: "))
        jobs.append(Job(name, estimated_time))

    completed_jobs, avg_waiting_time = schedule(jobs)

    print("Gantt chart:")
    for job in completed_jobs:
        print(f"{job.name} ", end="")
    print()

    print("Individual waiting times:")
    for job in completed_jobs:
        print(f"{job.name}: {job.waiting_time}")

    print(f"Average waiting time: {avg_waiting_time}")
