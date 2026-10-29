import sys

from scapy.layers.inet import ICMP, IP
from scapy.sendrecv import sr1


def main():
    dst_ip = input("Enter destination IP address: ").strip()

    try:
        max_ttl_input = input("Enter maximum TTL (1-64, default 30): ").strip()

        max_ttl = int(max_ttl_input or "30")

        if not 1 <= max_ttl <= 64:
            raise ValueError

    except ValueError:
        print("Invalid maximum TTL. Enter a value from 1 to 64.")
        sys.exit(1)

    timeout = 3

    print("\nTTL\tResponding IP\t\tICMP Type\tICMP Code")
    print("-" * 65)

    for ttl in range(1, max_ttl + 1):
        packet = IP(dst=dst_ip, ttl=ttl) / ICMP(type=8, code=0)

        try:
            response = sr1(packet, timeout=timeout, verbose=0)

        except PermissionError:
            print("Permission denied. Run with sudo/root.")
            sys.exit(1)

        except OSError as exc:
            print(f"Could not send packet at TTL {ttl}: {exc}")
            continue

        if response is None:
            print(f"{ttl}\t*\t\t\t-\t\t- (timeout)")
            continue

        responder = response[IP].src if response.haslayer(IP) else "Unknown"

        if response.haslayer(ICMP):
            icmp_type = int(response[ICMP].type)
            icmp_code = int(response[ICMP].code)

            print(f"{ttl}\t{responder}\t\t{icmp_type}\t\t{icmp_code}")

            if icmp_type == 0 and icmp_code == 0:
                print("\nDestination reached.")
                break

            if icmp_type == 3:
                print("Destination Unreachable received.")
                break

        else:
            print(f"{ttl}\t{responder}\tOther response")

    print("\nExperiment completed.")


if __name__ == "__main__":
    main()
