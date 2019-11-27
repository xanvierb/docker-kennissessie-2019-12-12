# Limiting the amount of memory you can use
Sometimes, software misbehaves. And sometimes, that misbehaviour can have... consequences.

## Understanding the contrived example
Before proceeding make sure that you understand what this program (snippet) is doing and why that would be dangerous:

```
size_t pageSize = 4096; // sysconf(_SC_PAGESIZE)
do
{
    void * mem = malloc(pageSize);
}
while (mem && !mlock(mem, pageSize));
```

## Prepare the VM for the experiment

 - Create a snapshot of your VM first, so you can revert safely back if you accidentally break your VM.
 - Copy `oom.c` over to your VM
 - Compile it on your VM with GCC: `gcc -o oom oom.c` should work

## Experiment

### A: limit the number of tasks a container can run at any given time
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
