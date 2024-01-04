# Final Project Proposal

## Group Members:

Nelli Rojas-Cessa
       
# Intentions:

The main objective of this project is to create a chat program that allows users on different computers to send messages and files back and forth, like the well-known application, Messenger. Two or multiple users can join a chatroom at a time using a randomly generated password to get access. Each user has a username. There is also a chat log that records the entire chat history. Users are also able to send files or images through the chat.

    
# Intended usage:

The chat program will operate on Terminal and display previous messages both sent and received by the user. To join a chatroom, the program will ask for a password and their username to ensure that they are a verified user. Each user will have their username displayed above their own messages. Messages will be color coded, and the background will also be customizable. Once a chat ends because someone disconnected, the chat log file can be used to read the entire chat history. To send images or files, the user would have to use a special command, which will be specified on the interface. 

  
# Technical Details:

The chat program will mainly utilize the following concepts from class: working with files, when transferring files and to see the chat log; sockets and networking to send messages back and forth; and semaphores to ensure users can send information at the same time without complications. The TCP handshake will be used initially to ensure a connection. Then sockets will be used in a client-server connection so that users can chat from different IP addresses. Semaphores will then be used to make sure there isn’t odd behavior when multiple users send messages at the same time and possible as an add-on to set permissions settings for certain users. A file is also created and written to as someone sends a message, which would be the chat log. For file transfer, sockets will also be used. 
    
# Intended pacing:

January 8: Basic chat function between two/multiple users
January 9: User interface 
January 10: Chat log
January 12: Add-ons like sending files/images
January 15: Finishing touches like colors and backgrounds

