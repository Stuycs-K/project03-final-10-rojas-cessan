[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# Cessenger

### Nelli and the Nellies

Nelli Rojas-Cessa
       
### Project Description:

This is a chat program that allows you to communicate with multiple others users on different computers! It's similar to Messenger or WhatsApp. The maximum amount of users in one group chat is one host and eight other users. You must ask the host for their IP Address in real life to join their chatroom, which can be found using {ifconfig} on Terminal of the host computer. Every user has a username so they know who is sending certain messanges. The program also creates a chat log in a separate file which displays all the messsenges sent by all the users. The program color coded as well.
  
### Instructions:
Note: {} is used to show what is meant to be typed for clarification. Please type what is inside the brackets.

How does the user install/compile/run the program?
- To start server as a host, type the following in Terminal:
  - {make compile}
  - {./host}
  - Type in your username when prompted
  - The host must initiate the server (do this by following steps above) before others connect.
- To join as another user on a different computer, type the following in Terminal:
  - {make compile}
  - {./client ENTER_IP_ADDRESS_OF_HOST_HERE}
  - Type in your username when prompted
- To join on the same computer the IP Address is not necessary, so this would work:
  - {./client}
  
How does the user interact with this program?
- To send texts: type in Terminal and press enter to send
- To leave chat:
  - {.d} OR Ctrl-C
  - Host must use Ctrl-C to disconnect if not connected to any client.
- To view chat log:
  - {cat chat_log.txt}
  - Use a graphical file manager (like Finder on Mac) 
  
Known Bugs/Specifications:
- When using different computers, Marge and Lisa are not reliable as the host, and often fail to connect. As clients, they significantly lag, which can cause missing information. (Homer is generally good.)
- If you spam messages or send in rapid succession, the chat log will include unwanted junk data.
- May encounter issues when usernames or messages are exceeding large (around 1024 characters and more).
