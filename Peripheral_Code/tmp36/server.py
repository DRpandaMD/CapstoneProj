#echo server program
#Michael Zarate
#April 16th 2016
#Sourced from raspberrypi.stackexchange.com

import socket

HOST = '10.143.7.215'  #our host IP found by /terminal./ifconfig
PORT = 5555          #arbritrary port number most likely not to be used


#create a socket using these paramters
pi_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#then we bind the HOST IP and PORT number to the socket
pi_socket.bind((HOST, PORT))

#we tell the socket to only try to listen to one other device
pi_socket.listen(1)

#.accept() returns a connection and the IP address
connection, address = pi_socket.accept()

#print to the screen who is connected
print 'Connected by: ', address

while 1:    #forever
    data = connection.recv(4096)  #we are going to recv 4096 a 'small' value from phython.org library page
    if not data: break              #if we don't get any data from other device break out
    write_string = str(data)
    #print data                      #we print the data
    #connection.sendall(data)        #we are echoing back to origin device
    writing_file = open('test.txt', 'w')
    
    writing_file.write(write_string)
    writing_file.close()

connection.close()                  # close the connection
print 'Connection Closed'
