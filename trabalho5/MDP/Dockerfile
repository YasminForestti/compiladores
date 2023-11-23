FROM ubuntu:18.04

RUN apt update && \
    apt -y install flex bison g++ make

WORKDIR /trabalho4/MDP

ENTRYPOINT [ "make" ]