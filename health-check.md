# An apple a day

One of the findings of the Docker Security Bench is that there are no configured health checks in your container. In this assignment you are going to do so. 

## lets go

1. retrieve the [xanvier/healthtest](https://hub.docker.com/repository/docker/xanvier/healthtest) container from docker hub.
2. There is a health endpoint configured in this container on [http://localhost/health.html]
3. use the `--health-cmd='<HEALTH CHECK COMMAND>'` flag in the `run` command
4. come up with a health check command that makes sense. 
5. When executing `docker ps` you'll notice that something changes.
