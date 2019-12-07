# An apple a day

One of the findings of the Docker Security Bench is that there are no configured health checks in your container. In this assignment you are going to do so. 

## lets go

1. install some webserver at your own discretion to the container. 

TODO > gebruik nginx container

2. create an `/health` endpoint which returns a 200 response
3. configure Docker to use this endpoint
4. check `docker ps` and notice that this is changed

## What will this button do?

1. configure your endpoint to go down after a specified time
2. see how docker response to this with `docker ps`