import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 8080))
server.listen(1)
print("Server is waiting for connection...")

conn, adr = server.accept()
print("Connected to ", adr)
conn.send(b"Hello from server")
conn.close()

