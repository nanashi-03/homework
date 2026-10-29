import sys

from scapy.layers.inet import ICMP, IP, TCP
from scapy.sendrecv import sr1
from scapy.volatile import RandShort


def analyze_tcp_flags(dst_ip, dst_port):
    test_flags = {"SYN": "S", "ACK": "A", "FIN+ACK": "FA", "RST": "R", "SYN+FIN": "SF"}

    src_port = RandShort()
    timeout_val = 2

    print(f"\nTarget: {dst_ip}:{dst_port}")
    print("-" * 50)

    for flag_name, flag_val in test_flags.items():
        print(f"[*] Sending {flag_name} (Flags: {flag_val}) segment...")

        packet = IP(dst=dst_ip) / TCP(sport=src_port, dport=dst_port, flags=flag_val)

        reply = sr1(packet, timeout=timeout_val, verbose=0)

        if reply is None:
            print("    -> No response received within the timeout period (Dropped/Filtered).\n")
        elif (tcp_layer := reply.getlayer(TCP)) is not None:
            print(f"    -> Received TCP response. Flags: {tcp_layer.flags}\n")
        elif (icmp_layer := reply.getlayer(ICMP)) is not None:
            print(f"    -> Received ICMP response. Type: {icmp_layer.type}, Code: {icmp_layer.code}\n")
        else:
            print(f"    -> Received other type of response: {reply.summary()}\n")


if __name__ == "__main__":
    try:
        target_ip = input("Enter destination IP address: ")
        target_port = int(input("Enter destination TCP port number: "))
        analyze_tcp_flags(target_ip, target_port)
    except ValueError:
        print("Invalid port number. Please enter an integer.")
    except KeyboardInterrupt:
        print("\nExperiment aborted.")
        sys.exit(0)
