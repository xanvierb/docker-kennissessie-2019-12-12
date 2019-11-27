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

## Experiment

### A: limit the number of tasks a container can run at any given time
 - Spin up a `debian:sid-slim` container which does nothing much, but make sure to enforce a limit on the number of tasks that can live concurrently inside the container. You can use the following template as a starting point for your commands:
 
```sh
docker pull debian:sid-slim
docker run -d --entrypoint /usr/bin/tail debian:sid-slim -f /dev/null
```
 - Set up two parallel sessions in the container using `docker exec -it <container> /bin/sh`
 - In one `exec` session, set up a `watch ps aux`
 - In another kick off the fork-bomb
 - Does your limit work?

### B: what if you did not apply a limit:

 - Much the same as the previous one, except leave out the limit. You may have done this one already inadvertently if you skipped over the previous instructions a bit...
