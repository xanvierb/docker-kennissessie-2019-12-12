FROM debian:sid-slim

RUN apt-get update -qq && apt-get install -y -qq --no-install-recommends iputils-ping
