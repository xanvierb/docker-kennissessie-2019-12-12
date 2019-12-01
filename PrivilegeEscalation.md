# Preventing privilege escalation
So you did the work and your Docker containers run with the least amount of privileges they can have. Or so you think... But do you know how `sudo` really works?

## Understanding the example
The following few exercises can be run safely from either your own host, a shell in the VM or inside a container

### suid, sgid:
Files can be marked `suid` or `sgid` and this is how a normal user can run them with elevated privileges

 - Either use your own host, a shell in the VM or spin up a `debian:sid-slim` container using `docker run -it debian:sid-slim`
 - Try the following commands:
   * `ls -l --color /bin/su`
   * `find / -perm /u=s,g=s`
 - Did you know about `wall`? Use the console of your VM or your host and execute `wall "Hello, world!"`

So the upside is you do not need to be root before changing your own password using `passwd`. The downside is that the security of this system is built entirely around trusting the blessed programs not to misbehave. Yet, sometimes programs have bugs...

### capabilities
Blanket `root` permissions for anything marked `suid` is a risk. In general the Unix concept of `root` is quite tricky: there are a *lot* of ordinary operations which require at least *some* level of elevated privileges.

On Linux you can use `capabilities` instead of `suid`. In brief, capabilities are a way to break up the "anything goes" level of privilege of `root` so you can run a normal user thread with only 'slightly' elevated privileges or you can run a programs as `root` without grantintg 'full' `root`. The [manual page on `capabilities`](http://man7.org/linux/man-pages/man7/capabilities.7.html) is well worth a read.

Similar to `setuid`, files can also be marked with `capabilities`. To find out what `capabilities` are associated with a file you can use the `getcap` command.

 - Either use your own host, a shell in the VM or spin up a `debian:sid-slim` container using `docker run -it debian:sid-slim`
 - Install the `ping` command if you don't have it yet  (check using `which ping`): `apt-get install iputils-ping`
 - Try the following command:
   * `/sbin/getcap $(which ping)`
 - Why does `ping` need elevated privileges?

### Preventing the normal ways of privilege elevation
On Linux a process/thread can opt-in into an additional security feature which prevents a process/thread from gaining new privileges ([the NO_NEW_PRIVS flag](https://www.kernel.org/doc/Documentation/prctl/no_new_privs.txt)). This feature works both against `suid` binaries and `capabilities`. Docker can use it to help guard against accidental escalation of privileges inside the container.

## Prepare the VM for the experiment

 - Copy `Dockerfile` and `.dockerignore` over to your VM
 - Build the container in the VM: `docker build . -t ping:latest`

## Experiment

### A: unprivileged users may still do privileged things by default

 - Run the `ping:latest` container as an unprivileged user: `docker run -it -u "$(id -u):$(id -g)" ping:latest`
 - Experiment with `ping`, trying pinging Google: `ping 8.8.8.8`

### B: prevent it!

 - Much the same as the previous experiment, except this time pass `--security-opt=no-new-privileges:true` when running the container.
