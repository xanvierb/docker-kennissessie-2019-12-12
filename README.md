# Docker security kennissessie.

Welcome to the excersises of the Docker security knowledge sharing session. You can find the presentation given earlier at http://dockersecurity.staq.info/#/. 

If you not yet have an VM setup, you can follow the guide over [here](./blob/master/VM.md). If you are using the VM provided by the course you can login using the credentials: 

```
un: experiments
pw: experiments
```

the experiments user is a member of the sudo group, but you can also `su` into the root account, the root user has the same password as the experiments user. 

## Excersises

You can do these excersises in this order. Be aware, read the excersises carefuly a lot of the course is about the information in the excersises itself. 

1. [Privilege Escelation](./blob/master/PrivilegeEscalation.md) 
2. [Out of memmory ](./blob/master/OOM.md) 
3. [Forking ](./blob/master/ForkBomb.md) 
4. [Docker in Docker](./blob/master/docker-in-docker.md) 
5. [Health Check](./blob/master/health-check.md) 
