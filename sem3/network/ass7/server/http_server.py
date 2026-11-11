import os
import socket
import sys

BUFFER_SIZE = 8192


def handle_client(client_socket):
    try:
        request_data = b""
        while b"\r\n\r\n" not in request_data:
            chunk = client_socket.recv(1024)
            if not chunk:
                break
            request_data += chunk

        if not request_data:
            return

        parts = request_data.split(b"\r\n\r\n", 1)
        header_text = parts[0].decode("utf-8", errors="replace")
        body_initial = parts[1] if len(parts) > 1 else b""

        lines = header_text.split("\r\n")
        if not lines or not lines[0]:
            return

        request_tokens = lines[0].split()
        if len(request_tokens) < 3:
            return

        method, path, _ = request_tokens[0], request_tokens[1], request_tokens[2]

        filename = "index.html" if path == "/" else path.lstrip("/")

        if method.upper() == "GET":
            if os.path.isfile(filename):
                with open(filename, "rb") as f:
                    file_content = f.read()

                header = (
                    "HTTP/1.0 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    f"Content-Length: {len(file_content)}\r\n"
                    "Connection: close\r\n\r\n"
                )
                client_socket.sendall(header.encode("utf-8") + file_content)
            else:
                error_body = b"<html><body><h1>404 Not Found</h1><p>The requested file does not exist.</p></body></html>\r\n"
                header = (
                    "HTTP/1.0 404 Not Found\r\n"
                    "Content-Type: text/html\r\n"
                    f"Content-Length: {len(error_body)}\r\n"
                    "Connection: close\r\n\r\n"
                )
                client_socket.sendall(header.encode("utf-8") + error_body)

        elif method.upper() == "PUT":
            content_length = 0
            for line in lines[1:]:
                if line.lower().startswith("content-length:"):
                    content_length = int(line.split(":")[1].strip())
                    break

            body_data = body_initial
            remaining = content_length - len(body_data)

            while remaining > 0:
                chunk = client_socket.recv(min(4096, remaining))
                if not chunk:
                    break
                body_data += chunk
                remaining -= len(chunk)

            with open(filename, "wb") as f:
                f.write(body_data)

            res_body = b"File created successfully.\n"
            header = (
                "HTTP/1.0 200 OK File Created\r\n"
                "Content-Type: text/plain\r\n"
                f"Content-Length: {len(res_body)}\r\n"
                "Connection: close\r\n\r\n"
            )
            client_socket.sendall(header.encode("utf-8") + res_body)

    finally:
        client_socket.close()


if len(sys.argv) < 2:
    print(f"Usage: python {sys.argv[0]} <port>")
    sys.exit(1)

port = int(sys.argv[1])
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

server_socket.bind(("0.0.0.0", port))
server_socket.listen(10)

print(f"[SERVER ACTIVE] Listening on port {port}...")

while True:
    try:
        client_socket, _ = server_socket.accept()
        handle_client(client_socket)
    except KeyboardInterrupt:
        print("\n[SERVER SHUTDOWN] Stopping server.")
        break
    except ConnectionError as e:
        print(f"Error accepting connection: {e}")

server_socket.close()
