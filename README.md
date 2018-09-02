# Description

This is a miniature http proxy server implementation, written in c language, with a core codebase of less than 500 lines, and does not rely on any third-party libraries (can only work on unixlike systems).
Its main functions are:

* Http proxy
* Supports https tunneling
* Supports simple encrypted tunnels

Note: This code implementation is simple and hastily completed, and is currently only at the prototype stage.Pull requests are welcome. :)


There are usually two working modes: normal proxy mode and encrypted tunnel mode.


## normal proxy mode

This working mode is the same as a regular http proxy, and currently mproxy only performs simple http forwarding and does not cache any web pages.

## encrypted tunnel mode

 <pre>   
   +----------+        +-----------+       +----------+      +----------+
   |          |        |           |       |          |      |          |
   |          |        |           |       |          |      |          |
   |  APP     +------->| mproxy    |+------> mproxy   +------> Web      |
   |          |        |           |       |          |      |          |
   |          |        | client    |       | server   |      |          |
   +----------+        +-----------+       +----------+      +----------+
</pre>

## Build

```
./build.sh
```


## Instructions

### Used as a regular proxy server.

```bash
./mproxy -l 8000 -d
```

This working mode is not very meaningful for us, and is only used for demonstration purposes. The focus is on the next mode.

Note: the "-d" parameter indicates that the program is run as a daemon service to avoid the program ending when the terminal is closed.

### Used as a deployment method for encrypted tunnels
#### step1 : Start proxy as a remote proxy on the remote server

You need to compile the proxy source code on the remote server (you can also copy the binary directly) and then run the following command:

```bash
./mproxy  -l 8081 -D -d
```

The "-D" parameter specifies that the data received is decrypted, and its corresponding parameter "-E" is applied to the local proxy. The "-d" parameter specifies that the program is run as a background service to avoid the program ending when the terminal is closed.

#### step2 : Start proxy as a local proxy and specify the transmission method as encryption

Start a mporxy locally and specify the server address and port number of the server deployed remotely in the previous step.

```bash
./proxy  -l 8080 -h xxx.xxx.xxx.xxx:8081 -E
```

The "-l" parameter specifies the local listening port, the "-h" parameter specifies the server address and port number of the remote next hop server, which must be a foreign server for circumventing Internet censorship. The "-E" parameter specifies that the data is encrypted when sent, and its corresponding parameter "-D" is applied to the remote proxy.









