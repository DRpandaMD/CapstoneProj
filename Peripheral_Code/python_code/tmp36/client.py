#echo client program
#Michael Zarate
#April 16th 2016
#Sourced from raspberrypi.stackexchange.com

import socket

#NOTE:  these IP's need to be edited for ever reconect to the router
HOST = '10.143.5.152'  #our host IP found by /ifconfig 
PORT = 5555             #abritrary port number most like not to be used

#create a socket using these paramters
pi_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print "Tying to connect to socket"

#we connect to the sock
pi_socket.connect((HOST,PORT))

print "Pi Socket has connected"

#we create a file object to read and send that file 
writing_file = open("tmp_output.txt", "r")
sending_obj = writing_file.read()
print sending_obj
writing_file.close()

send_string = str(sending_obj)

print 'Sending a file!!'

print 'this is our sending string: ',  send_string
pi_socket.sendall(send_string)

#data = pi_socket.recv(4096)

#print data

pi_socket.close()