import socket
import threading

HOST = "127.0.0.1"


def reply_server():
    """Port 5053: receive a datagram and send a reply."""
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind((HOST, 5053))
        print(f"[5053] Reply server listening on {HOST}:5053")

        while True:
            data, addr = s.recvfrom(4096)
            print(f"[5053] Received {data!r} from {addr}")
            s.sendto(b"UDP reply from port 5053", addr)


def silent_server():
    """Port 5055: receive datagrams but never reply."""
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind((HOST, 5055))
        print(f"[5055] Silent server listening on {HOST}:5055")

        while True:
            data, addr = s.recvfrom(4096)
            print(f"[5055] Received {data!r} from {addr}; not replying")


if __name__ == "__main__":
    threading.Thread(target=reply_server, daemon=True).start()
    threading.Thread(target=silent_server, daemon=True).start()

    print("UDP test servers running. Press Ctrl+C to stop.")

    try:
        threading.Event().wait()
    except KeyboardInterrupt:
        print("\nStopping test servers.")
