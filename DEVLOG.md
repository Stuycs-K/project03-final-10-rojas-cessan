# Dev Log:

## Nelli
Note: The number of minutes in brackets refers to at-home work and doesn't include class time. 
### 2024-01-03 - proposal
I wrote the proposal. [30 mins]

### 2024-01-04 - sockets and multithreading
I started by using sockets to first establish a connection (3-way handshake). Then I used fork to create one thread to perpetually send messages and the another thread to perpetually read messages. I ran into an issue when either side disconnects, it prints unwanted messages. [60 mins]

### 2024-01-05 - Brief description
I'm still having the disconnect issue, but now it doesn't infinite loop on both host and client, it infinite loops on only client. I did this with getppid and an algorithm I wrote in my notebook. I also started username in class. At home, I finally got disconnect to work through learning to use WNOHANG and switching around the order of the threads. [40 mins]

### 2024-01-06 - Brief description
Detailed [xx mins]

### 2024-01-07 - Brief description
Detailed [xx mins]

