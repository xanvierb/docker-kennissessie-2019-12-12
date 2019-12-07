# Docker in Docker

Running Docker in Docker is not something that realy happens that much but is a scenario that can occur. For example when you are using Docker in you Continious Integration tooling. There are some security risk accompanied by this solution which most users are not aware of. In this excersise we are going to take a closer look in the security implications of a set up like this.

![yo dawg](img/docker-meme.jpg)

## Start other containers!

Docker communicates with the Docker deamon using a socket. If we manage to mount the docker socket of the host in a container we can control the Docker deamon of the host from a container. I don't think we have to explain why this can be a dangerous thing to do. We are, however, going to show you why this is a dangerous thing to do!

1. First start an (interactive terminal) container with a volume mount to the container. hint: You can use the `-v`-flag to mount a volume `-v host-path:/container-path` (the usual location of the docker socket is: `/var/run/docker.sock`)
2. When the container is started use `apt` to install the `docker.io` package (don't forget to retrieve the package list)
3. Now, you want to give commands to Docker to access the docker deamon of the host, therefor you have to instruct Docker to use the socket that you mounted. `docker --host unix://<LOCATION OF SOCKET> <DOCKER COMMAND>`. Use this command to start an interactive terminal container of `ubuntu:bionic`
4. Check on the host machine with `docker ps` if this container is running on the host.

## Sudo with no audit logging


docker cp ->> informatie lekken, host configs berwerken of lezen

lsns 
but how?
chroot

## Mitigeren

Andere build tooling gebruiken: kaniko

