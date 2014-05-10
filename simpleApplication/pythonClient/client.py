import socket
import sys
TCP_IP = '192.168.149.129'
TCP_PORT = 5005
BUFFER_SIZE = 2000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
s.connect((TCP_IP, TCP_PORT))
while 1:
  print 'user data:'
  content = sys.stdin.readline();
  s.send(content)
  data = s.recv(BUFFER_SIZE)
  print "received data:", data
s.close()
