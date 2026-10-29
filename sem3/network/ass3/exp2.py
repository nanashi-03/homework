import random
import sys

from scapy.layers.inet import ICMP, IP, TCP
from scapy.sendrecv import send, sr1


def main():
    dst_ip = input("Enter destination IP address: ").strip()

    try:
        dst_port = int(input("Enter destination TCP port: "))
        if not 1 <= dst_port <= 65535:
            raise ValueError
    except ValueError:
        print("Invalid TCP port.")
        sys.exit(1)

    src_port = random.randint(49152, 65535)
    client_isn = random.randint(0, 2**32 - 1)
    timeout = 3

    print("\n--- Sending SYN ---")
    print(f"Client ISN = {client_isn}")

    syn = IP(dst=dst_ip) / TCP(
        sport=src_port, dport=dst_port, flags="S", seq=client_isn
    )

    response = sr1(syn, timeout=timeout, verbose=0)

    if response is None:
        print("No response received.")
        return

    if response.haslayer(TCP):
        tcp = response[TCP]
        print(f"Response TCP flags = {tcp.flags}")

        if int(tcp.flags) & 0x04:  # RST flag
            print("Connection refused/reset; no SYN+ACK.")
            return

        if not (int(tcp.flags) & 0x02 and int(tcp.flags) & 0x10):
            print("Response is not SYN+ACK.")
            return

        server_isn = tcp.seq
        received_ack = tcp.ack

        expected_client_ack = (client_isn + 1) % (2**32)
        expected_server_ack = (server_isn + 1) % (2**32)

        print("\n--- Results ---")
        print(f"Client ISN = {client_isn}")
        print(f"Server ISN = {server_isn}")
        print(f"SYN+ACK acknowledgment = {received_ack}")
        print(f"Expected client acknowledgment = {expected_client_ack}")

        if received_ack != expected_client_ack:
            print("Unexpected SYN+ACK acknowledgment number.")
            return

        ack = IP(dst=dst_ip) / TCP(
            sport=src_port,
            dport=dst_port,
            flags="A",
            seq=expected_client_ack,
            ack=expected_server_ack,
        )

        print("\n--- Sending final ACK ---")
        ack.show()
        send(ack, verbose=0)

        print("Final ACK sent.")
        print(f"ACK segment SEQ = {expected_client_ack}")
        print(f"ACK segment ACK = {expected_server_ack}")

    elif response.haslayer(ICMP):
        icmp = response[ICMP]
        print(f"ICMP Type = {icmp.type}, Code = {icmp.code}")

    else:
        print("Unexpected response:", response.summary())


if __name__ == "__main__":
    main()
