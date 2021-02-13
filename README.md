# Server Stuffer

Server Stuffer is a testing utility which allows you to use [American Fuzzy Lop](https://lcamtuf.coredump.cx/afl/) on C programs which use sockets.

It works by using function re-definition to substitute socket system calls (`send`, `recv`, etc.) for regular file I/O, specifically, for a file with data generated by AFL.

In this way, you can use the bug-discovery power of AFL on a socket-based application without changing any of the code.

## Getting Started

Start by building a local copy of AFL. You can do this by running `make` in the AFL folder. See the AFL documentation for further instructions or troubleshooting information.

If you don't have a copy of AFL yet, you can download and build the latest version from the website:

```sh
wget 'https://lcamtuf.coredump.cx/afl/releases/afl-latest.tgz'
tar -xzvf afl-latest.tar.gz
cd afl-latest
make
```

Then, prepare an input and output folder. The input folder should contain a file with an example of some valid input, the output folder can be empty and will be populated by AFL.

Now, you can compile the code using AFL's version of GCC. Make sure to add `re-definition.c` and the `-ldl` flag. For example:

```sh
./afl-latest/afl-gcc (your files...) re-definition.c -ldl
```

Finally, you can run `build.sh` to build and run a Docker image containing AFL and your compiled program.

```sh
./build.sh (executable) (input directory) (output directory) (AFL directory)
```

Note that `build.sh` will request root access via. `sudo` to change some kernel settings (as required by AFL) and in order to run Docker.

Here, 'AFL directory' refers to the directory containing the executables for AFL. This may be a different directory if AFL is already installed on your system.

## Example Usage

There're some buggy programs in the example folder. To debug them, first compile them with AFL GCC:
```
./afl-latest/afl-gcc upd_server.c re-definition.c -ldl 
```
Then, create input and output folders, with one test case in the input folder, for example:
```
mkdir input
mkdir output
echo "a" > input/sample
```
Finally, run the build shell:
```
./build.sh a.out input output afl-latest
```

See what you get!