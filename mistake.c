docker build -f Dockerfile.build -t  kubsh_image .
[+] Building 30.9s (2/2) FINISHED                                                                                                                                                                                              docker:default
 => [internal] load build definition from Dockerfile.build                                                                                                                                                                               0.0s
 => => transferring dockerfile: 168B                                                                                                                                                                                                     0.0s
 => ERROR [internal] load metadata for docker.io/library/debian:bullseye                                                                                                                                                                30.8s
------
 > [internal] load metadata for docker.io/library/debian:bullseye:
------
Dockerfile.build:1
--------------------
   1 | >>> FROM debian:bullseye
   2 |     
   3 |     RUN apt-get update && \
--------------------
ERROR: failed to solve: DeadlineExceeded: DeadlineExceeded: DeadlineExceeded: debian:bullseye: failed to resolve source metadata for docker.io/library/debian:bullseye: failed to authorize: DeadlineExceeded: failed to fetch anonymous token: Get "https://auth.docker.io/token?scope=repository%3Alibrary%2Fdebian%3Apull&service=registry.docker.io": dial tcp 98.83.53.163:443: i/o timeout
user@user-VirtualBox:~/docker$ 

