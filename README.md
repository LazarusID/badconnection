# badconnection

Light weight emulator for bad network connections

## Building

### Requirements

 1. Unix-like system which supports POSIX network functions

 2. C development toolchain, especially a C compiler and Make.

### Steps

 1. Clone this repo

 2. From the command line in the cloned repo, run `make`

## Running badconnection

 1. From the command line in the cloned repo, run `src/badconnection`

To use badconnection, point the client you are testing to localhost, port
7777


## Behavior

badconnction will listen for connections on its listening port.  When a new
connection is made, it will immediately close the connection.
