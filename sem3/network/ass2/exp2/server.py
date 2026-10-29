import socket

HOST = "127.0.0.1"
PORT = 5000

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server.bind((HOST, PORT))

print(f"UDP Server listening on {HOST}:{PORT}")

while True:
    data, client_address = server.recvfrom(65535)

    print(
        f"Received {len(data)} bytes "
        f"from {client_address}: {data[:50]!r}"
    )

    response = (
        f"Server received {len(data)} bytes "
        f"from {client_address[1]}"
    ).encode()

    server.sendto(response, client_address)
