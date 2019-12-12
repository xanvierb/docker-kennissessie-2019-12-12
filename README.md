# Docker security kennissessie.

Welcome to the excersises of the Docker security knowledge sharing session. You can find the presentation given earlier at http://dockersecurity.staq.info/#/. 

If you not yet have an VM setup, you can follow the guide over [here](./VM.md). If you are using the VM provided by the course you can login using the credentials: 

```
un: experiments
pw: experiments
```

the experiments user is a member of the sudo group, but you can also `su` into the root account, the root user has the same password as the experiments user. 

If you would like to access the VM using SSH you can log in to the machine and resolve the IP address of the host-only network using the `ip addr` command. 

## Excersises

### Excersise 1
Run `docker-bench-security` and look at some of the the outputs.If you are familiar with the output you can continue. 

### the Rest of the excersises
You can do these excersises in this order. Be aware, read the excersises carefuly a lot of the course is about the information in the excersises itself. 

1. [Privilege Escelation](./PrivilegeEscalation.md) 
2. [Limiting memory ](./OOM.md) 
3. [Limiting number of tasks ](./ForkBomb.md) 
4. [Docker in Docker](./docker-in-docker.md) 
5. [Health Check](./health-check.md) 
