import random
import sys

from scapy.layers.inet import ICMP, IP, TCP, UDP
from scapy.packet import Raw
from scapy.sendrecv import sr1


def main():
    dst_ip = input("Enter destination IP address: ").strip()

    try:
        start_port = int(input("Enter starting UDP port: "))
        end_port = int(input("Enter ending UDP port: "))

        if not (
            1 <= start_port <= 65535
            and 1 <= end_port <= 65535
            and start_port <= end_port
        ):
            raise ValueError

    except ValueError:
        print("Invalid port range.")
        sys.exit(1)

    src_port = random.randint(49152, 65535)
    timeout = 3
    payload = b"UDP Experiment 4"

    print(f"\nDestination: {dst_ip}")
    print(f"UDP port range: {start_port}-{end_port}")
    print("\nPort\tResult\t\t\tDetails")
    print("-" * 65)

    for dst_port in range(start_port, end_port + 1):
        packet = (
            IP(dst=dst_ip) / UDP(sport=src_port, dport=dst_port) / Raw(load=payload)
        )

        try:
            response = sr1(packet, timeout=timeout, verbose=0)

        except PermissionError:
            print("Permission denied. Run with sudo/root.")
            sys.exit(1)

        except OSError as exc:
            print(f"{dst_port}\tSend error: {exc}")
            continue

        if response is None:
            print(f"{dst_port}\tNo response\t\tTimeout")

        elif response.haslayer(ICMP):
            icmp = response[ICMP]
            icmp_type = int(icmp.type)
            icmp_code = int(icmp.code)

            if icmp_type == 3 and icmp_code == 3:
                result = "Port unreachable"
            elif icmp_type == 3:
                result = "Destination unreachable"
            else:
                result = "ICMP response"

            print(f"{dst_port}\t{result}\tType={icmp_type}, Code={icmp_code}")

        elif response.haslayer(UDP):
            udp = response[UDP]
            print(f"{dst_port}\tUDP response\t\tSource port={udp.sport}")

        elif response.haslayer(TCP):
            print(f"{dst_port}\tUnexpected TCP response")

        else:
            print(f"{dst_port}\tOther response\t\t{response.summary()}")

    print("\nExperiment completed.")


if __name__ == "__main__":
    main()
