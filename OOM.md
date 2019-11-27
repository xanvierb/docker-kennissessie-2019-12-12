# Limiting the amount of memory you can use
Sometimes, software misbehaves. And sometimes, that misbehaviour can have... consequences.

## Understanding the contrived example
Before proceeding make sure that you understand what this C program (snippet) is doing and why that would be dangerous:

```
#define PAGE_SIZE 4096

do
{
    void * mem = malloc(PAGE_SIZE);
}
while (mem && !mlock(mem, PAGE_SIZE));
```

For details on `malloc()` and `mlock()` you can refer to the `man` pages:

 - [`man 3 malloc`](http://man7.org/linux/man-pages/man3/malloc.3.html)
 - [`man 2 mlock`](http://man7.org/linux/man-pages/man2/mlock.2.html)

## Prepare the VM for the experiment

 - Create a snapshot of your VM first, so you can revert safely back if you accidentally break your VM.
 - Copy `oom.c` over to your VM
 - Compile it on your VM with GCC: `gcc -o oom oom.c` should work

## Experiment

### A: limit the amount of memory a container can use at any given time
 - Spin up a `debian:sid-slim` container which does nothing much, but make sure to enforce a limit on the number of tasks that can live concurrently inside the container. You can use the following template as a starting point for your commands:

```sh
docker pull debian:sid-slim
docker run -d --entrypoint /usr/bin/tail debian:sid-slim -f /dev/null
```
 - Copy `oom` into the container using `docker cp oom <container>:/usr/local/bin/oom`
 - Set up two parallel sessions in the container using `docker exec -it <container> /bin/sh`
 - In one `exec` session, set up a `watch ps aux`
 - In another experiment with `oom`. You can pass it a memory limit (should be a multiple of 4096) or just let it attempt to eat 2GiB by default.
 - Does your limit work?

### B: what if you did not apply a limit:

 - Much the same as the previous one, except leave out the limit. You may have done this one already inadvertently if you skipped over the previous instructions a bit...
