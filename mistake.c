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

463463673737

 
 user@user-VirtualBox:~/docker$ docker run -v $(pwd):/opt kubsh_image
/docker-entrypoint.sh: /docker-entrypoint.d/ is not empty, will attempt to perform configuration
/docker-entrypoint.sh: Looking for shell scripts in /docker-entrypoint.d/
/docker-entrypoint.sh: Launching /docker-entrypoint.d/10-listen-on-ipv6-by-default.sh
10-listen-on-ipv6-by-default.sh: info: Getting the checksum of /etc/nginx/conf.d/default.conf
10-listen-on-ipv6-by-default.sh: info: Enabled listen on IPv6 in /etc/nginx/conf.d/default.conf
/docker-entrypoint.sh: Sourcing /docker-entrypoint.d/15-local-resolvers.envsh
/docker-entrypoint.sh: Launching /docker-entrypoint.d/20-envsubst-on-templates.sh
/docker-entrypoint.sh: Launching /docker-entrypoint.d/30-tune-worker-processes.sh
/docker-entrypoint.sh: Configuration complete; ready for start up
2025/11/22 10:52:19 [notice] 1#1: using the "epoll" event method
2025/11/22 10:52:19 [notice] 1#1: nginx/1.29.3
2025/11/22 10:52:19 [notice] 1#1: built by gcc 14.2.0 (Debian 14.2.0-19) 
2025/11/22 10:52:19 [notice] 1#1: OS: Linux 6.8.0-45-generic
2025/11/22 10:52:19 [notice] 1#1: getrlimit(RLIMIT_NOFILE): 1048576:1048576
2025/11/22 10:52:19 [notice] 1#1: start worker processes
2025/11/22 10:52:19 [notice] 1#1: start worker process 29
2025/11/22 10:52:19 [notice] 1#1: start worker process 30
^C2025/11/22 10:52:54 [notice] 1#1: signal 2 (SIGINT) received, exiting
**************************
user@user-VirtualBox:~/docker$ docker build -f Dockerfile.build -t kubsh_image .
[+] Building 31.0s (2/2) FINISHED                                docker:default
 => [internal] load build definition from Dockerfile.build                 0.0s
 => => transferring dockerfile: 176B                                       0.0s
 => ERROR [internal] load metadata for docker.io/library/debian:latest    30.9s
------
 > [internal] load metadata for docker.io/library/debian:latest:
------
Dockerfile.build:1
--------------------
   1 | >>> FROM debian
   2 |     
   3 |     RUN apt-get update && apt-get install -y --no-install-recommends gcc make libfuse3-dev libreadline-dev
--------------------
ERROR: failed to solve: DeadlineExceeded: DeadlineExceeded: DeadlineExceeded: debian: failed to resolve source metadata for docker.io/library/debian:latest: failed to authorize: DeadlineExceeded: failed to fetch anonymous token: Get "https://auth.docker.io/token?scope=repository%3Alibrary%2Fdebian%3Apull&service=registry.docker.io": dial tcp 54.236.114.2:443: i/o timeout
************************
user@user-VirtualBox:~/docker$ docker images
REPOSITORY    TAG       IMAGE ID       CREATED       SIZE
kubsh_image   latest    a3561f55db7b   2 weeks ago   152MB
mynginx       latest    a3561f55db7b   2 weeks ago   152MB
nginx         latest    d261fd19cb63   3 weeks ago   152MB
hello-world   latest    d2c94e258dcb   2 years ago   13.3kB

user@user-VirtualBox:~/docker$ docker run kubsh_image
/docker-entrypoint.sh: /docker-entrypoint.d/ is not empty, will attempt to perform configuration
/docker-entrypoint.sh: Looking for shell scripts in /docker-entrypoint.d/
/docker-entrypoint.sh: Launching /docker-entrypoint.d/10-listen-on-ipv6-by-default.sh
10-listen-on-ipv6-by-default.sh: info: Getting the checksum of /etc/nginx/conf.d/default.conf
10-listen-on-ipv6-by-default.sh: info: Enabled listen on IPv6 in /etc/nginx/conf.d/default.conf
/docker-entrypoint.sh: Sourcing /docker-entrypoint.d/15-local-resolvers.envsh
/docker-entrypoint.sh: Launching /docker-entrypoint.d/20-envsubst-on-templates.sh
/docker-entrypoint.sh: Launching /docker-entrypoint.d/30-tune-worker-processes.sh
/docker-entrypoint.sh: Configuration complete; ready for start up
2025/11/29 10:07:01 [notice] 1#1: using the "epoll" event method
2025/11/29 10:07:01 [notice] 1#1: nginx/1.29.3
2025/11/29 10:07:01 [notice] 1#1: built by gcc 14.2.0 (Debian 14.2.0-19) 
2025/11/29 10:07:01 [notice] 1#1: OS: Linux 6.8.0-45-generic
2025/11/29 10:07:01 [notice] 1#1: getrlimit(RLIMIT_NOFILE): 1048576:1048576
2025/11/29 10:07:01 [notice] 1#1: start worker processes
2025/11/29 10:07:01 [notice] 1#1: start worker process 29
2025/11/29 10:07:01 [notice] 1#1: start worker process 30
2025/11/29 10:07:21 [notice] 1#1: signal 28 (SIGWINCH) received

user@user-VirtualBox:~/docker$ docker network ls
NETWORK ID     NAME      DRIVER    SCOPE
69eac7d728f0   bridge    bridge    local
880dad800780   host      host      local
a3decffe3f3d   none      null      local

user@user-VirtualBox:~/docker$ docker run --rm busybox ping -c 3 8.8.8.8
Unable to find image 'busybox:latest' locally
latest: Pulling from library/busybox
e59838ecfec5: Pull complete 
Digest: sha256:e3652a00a2fabd16ce889f0aa32c38eec347b997e73bd09e69c962ec7f8732ee
Status: Downloaded newer image for busybox:latest
PING 8.8.8.8 (8.8.8.8): 56 data bytes

--- 8.8.8.8 ping statistics ---
3 packets transmitted, 0 packets received, 100% packet loss



