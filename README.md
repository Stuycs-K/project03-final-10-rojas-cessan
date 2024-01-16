[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# Cessenger

### Nelli and the Nellies

Nelli Rojas-Cessa
       
### Project Description:

This is a chat program that allows you to communicate with multiple others users on different computers! It's similar to Messenger or WhatsApp. The maximum amount of users in one group chat is one host and eight other users. You must ask the host for their IP Address in real life to join their chatroom.
  
### Instructions:
How does the user install/compile/run the program.
- To start server as a host, type the following in Terminal:
  - make compile
  - ./host
- To join as another user, type the following in Terminal:
  - make compile
  - ./client ENTER_IP_ADDRESS_OF_HOST_HERE
  
How does the user interact with this program?
- To send texts, type in Terminal
- To leave chat:
  - .d OR Ctrl-C
  
Known Bugs/Specifications:
- Host must use Ctrl-C to disconnect if not connected to any client.
