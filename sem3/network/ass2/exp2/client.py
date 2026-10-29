import socket
import sys

SERVER_HOST = "127.0.0.1"
SERVER_PORT = 5000

if len(sys.argv) != 2:
    print("Usage: python3 udp_client.py <1|2|3>")
    print("  1 - Small message  (5 bytes)")
    print("  2 - Medium message (100 bytes)")
    print("  3 - Large message  (1000 bytes)")
    sys.exit(1)

choice = sys.argv[1]

if choice == "1":
    message = "HELLO"
elif choice == "2":
    message = "A" * 1000
elif choice == "3":
    message = "A" * 10000
else:
    message = choice

data = message.encode()

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print(f"Message type: {choice}")
print(f"Application data size: {len(data)} bytes")

client.sendto(data, (SERVER_HOST, SERVER_PORT))

print(f"Sent {len(data)} bytes to {SERVER_HOST}:{SERVER_PORT}")

try:
    response, server_address = client.recvfrom(65535)

    print(f"Response from {server_address}:")
    print(response.decode(errors="replace"))

except TimeoutError:
    print("No response received.")

client.close()
