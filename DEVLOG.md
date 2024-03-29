# Dev Log:

## Nelli
Notes: 
- The number of minutes in brackets refers to at-home work and doesn't include class time. They are approximations.
- When I sometimes refer to "multi," I mean it as in something related to using multiple sockets with select.

### 2024-01-03 - proposal
I wrote the proposal. [30 mins]

### 2024-01-04 - sockets and multithreading
I started by using sockets to first establish a connection (3-way handshake). Then I used fork to create one thread to perpetually send messages and the another thread to perpetually read messages. I ran into an issue when either side disconnects, it prints unwanted messages. [60 mins]

### 2024-01-05 - finishing disconnect
I'm still having the disconnect issue, but now it doesn't infinite loop on both host and client, it infinite loops on only client. I did this with getppid and an algorithm I wrote in my notebook. I also started username in class. At home, I finally got disconnect to work through learning to use WNOHANG and switching around the order of the threads. [40 mins]

### 2024-01-06 - select WEEKEND
Mainly tried to integrate "select" code to have multiple people in a chat. Didn't get it to work yet, still trying to understand the code. [30 mins]


### 2024-01-07 - structs for username WEEKEND + LATE NIGHT COMMIT
I tried to incorporate sending structs, so that the username could be shared with the others in a more organized way. It currently doesn't work. I'm getting the bad address error. [30 mins]

### 2024-01-08 - debugging structs 
On linux, I don't recieve an error for printing a string that cannot be printed. I suspect there's an issue with memory allocation. Still, trying to debug in class. For homework, I continued debugging. I've achieved the name working when it disconnects. However, I think I will resort tomorrow to help to fix this bug. [40 mins]

### 2024-01-09 - multiple clients, perhaps
Finally debugged structs! Also organized files for readability and messed around with the multi code in class. At home, I created a new branch because I'm unsure on if I'll manage to get multiple users to work. I came up with a possible way for the multi aspect to work. It compiles but doesn't work in the slightest. [70 mins]

### 2024-01-10 - multiple clients: connected
In class, I mainly planned how I was going to restructure basically me entire code. I originally used multi-threading to get a chat program between the host and client, but I'm switching to using select to be able to use multiple clients. At home, I debugged and got the client and host able to connect. However, I'm not sure why messages are not appearing. [35 mins]

### 2024-01-11 - multiple clients: debugging select
In class and at home, I spent all my time debugging. The sending messages part works well with the structs but disconnect is an issue. More glaringly, the host can only communicate with the latest client. [120 mins]

### 2024-01-12 - multi works WEEKEND + LATE NIGHT COMMIT
Both in class and at home: Debugged code so that you can now send and recieve between all clients and the host! Added errors for when a socket disconnects with SIGINT. Added freeing to when I malloc package structs. [40 mins]

### 2024-01-13 - disconnect works WEEKEND + LATE NIGHT COMMIT
I made disconnect work in the way I want it to work so it server doesn't stop even if someone disconnects using ".d" or SIGINT. It's also my birthday today. :) [30 mins]

### 2024-01-14 - disconnect messaging WEEKEND + LATE NIGHT COMMIT
Disconnect now sends messages to other clients still running when someone disconnects, and host will shut down server if host disconnects. Spent most time trying to debug why communication stops after one person disconnects. [60 mins]

### 2024-01-15 - chat log and finishing touches WEEKEND + LATE NIGHT COMMIT
I created a chat log that functions most of the time. It does repeat messages because the host sends multiple times, and writing to the chat log is done every time a message is sent. I tried to fix it with a boolean. Other last minute debugging and making the interface a little nicer. The Read Me file was also written. I added colors. A lot of time spent testing and preparing the demo. In retrospect, my proposal was very optimistic! If I had a few more days I think I could have gotten most of it done. [200 mins]

