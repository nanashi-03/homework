import socket
import time

HOST = "127.0.0.1"
PORT = 5000

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect((HOST, PORT))

print(f"Connected to {HOST}:{PORT}")

# Create 100 KB of data
data = b"A" * 20480

total_sent = 0

# Send data in chunks
chunk_size = 4096

for i in range(0, len(data), chunk_size):
    chunk = data[i:i + chunk_size]

    sent = client.send(chunk)
    total_sent += sent

    print(f"Sent {sent} bytes | Total: {total_sent} bytes")

    # Small delay to make packet behaviour easier to observe
    time.sleep(0.01)

client.shutdown(socket.SHUT_WR)

print("Finished sending data.")

# Wait briefly before closing
time.sleep(2)

client.close()

print("Connection closed.")
