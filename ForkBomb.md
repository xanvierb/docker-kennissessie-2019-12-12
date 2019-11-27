# Limiting the number of tasks
Sometimes, software misbehaves. And sometimes, that misbehaviour can have... consequences.

## Understanding the contrived examples
Before proceeding make sure that you understand what these are doing and why that would be dangerous:

### The classic 'lots of shell syntax one' (bash):

```sh
:(){:|:&};:
```

Bonus question: did you notice that `:` was redefined here?

### Which is more readable in perl:

```sh
perl -e 'fork while fork' &
```

## Prepare the VM for the experiment

 - Create a snapshot of your VM first, so you can revert safely back if you accidentally break your VM.
 - Copy `fork.c` over to your VM
 - Compile it on your VM with GCC: `gcc -o fork fork.c` should work

## Experiment

### A: limit the number of tasks a container can run at any given time
 - Spin up a `debian:sid-slim` container which does nothing much, but make sure to enforce a limit on the number of tasks that can live concurrently inside the container. You can use the following template as a starting point for your commands:
 
```sh
docker pull debian:sid-slim
docker run -d --entrypoint /usr/bin/tail debian:sid-slim -f /dev/null
```
 - Copy `fork` into the container using `docker cp fork <container>:/usr/local/bin/fork`
 - Set up two parallel sessions in the container using `docker exec -it <container> /bin/sh`
 - In one `exec` session, set up a `watch ps aux`
 - In another experiment with `fork`. You can pass it a memory limit or just let it attempt to create 200 subprocesses by default.
 - Does your limit work?

### B: what if you did not apply a limit:

 - Much the same as the previous one, except leave out the limit. Then, crank up the number of processes for `fork` to 4294967297 (2^32 + 1) or use one of the 'real' fork-bomb examples instead of the `fork` program. What happens?
