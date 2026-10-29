import socket

HOST = "127.0.0.1"
PORT = 5000

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

server.bind((HOST, PORT))
server.listen(1)

print(f"Server listening on {HOST}:{PORT}")

conn, addr = server.accept()
print(f"Connection established with {addr}")

total_bytes = 0

while True:
    data = conn.recv(4096)

    if not data:
        break

    total_bytes += len(data)

    print(f"Received {len(data)} bytes | Total: {total_bytes} bytes")

conn.close()
server.close()

print("Connection closed.")
print(f"Total data received: {total_bytes} bytes")
