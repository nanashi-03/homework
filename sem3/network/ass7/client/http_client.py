import os
import socket
import sys

BUFFER_SIZE = 4096

if len(sys.argv) < 5:
    print(f"Usage: python {sys.argv[0]} <server_ip_or_host> <port> <method> <path>")
    sys.exit(1)

host = sys.argv[1]
port = int(sys.argv[2])
method = sys.argv[3].upper()
path = sys.argv[4]

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    client_socket.connect((host, port))
except ConnectionError as e:
    print(f"Error connecting to server {host}:{port} -> {e}")
    sys.exit(1)

if method == "GET":
    request = (
        f"GET {path} HTTP/1.0\r\n"
        f"Host: {host}\r\n"
        f"User-Agent: CustomPythonClient/1.0\r\n"
        f"Connection: close\r\n\r\n"
    )
    client_socket.sendall(request.encode("utf-8"))

elif method == "PUT":
    filename = path.lstrip("/")
    body = b""
    if os.path.exists(filename):
        with open(filename, "rb") as f:
            body = f.read()
    else:
        print(
            f"Warning: Local file '{filename}' not found. Transmitting empty body."
        )

    header = (
        f"PUT {path} HTTP/1.0\r\n"
        f"Host: {host}\r\n"
        f"Content-Length: {len(body)}\r\n"
        f"Connection: close\r\n\r\n"
    )
    client_socket.sendall(header.encode("utf-8") + body)

else:
    print(f"Unsupported HTTP Method: {method}")
    client_socket.close()
    sys.exit(1)

response = b""
while True:
    data = client_socket.recv(BUFFER_SIZE)
    if not data:
        break
    response += data

client_socket.close()
print(response.decode("utf-8", errors="replace"))
