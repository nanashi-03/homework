import csv
import threading
import time
from collections import defaultdict
from datetime import datetime

from scapy.layers.inet import ICMP, IP, TCP, UDP
from scapy.sendrecv import sniff

CAPTURE_SECONDS = 15 * 60
BPF_FILTER = "ip and (tcp or udp or icmp)"

flows = defaultdict(lambda: {"packets": 0, "bytes": 0, "first": None, "last": None})

ip_stats = defaultdict(lambda: {"packets": 0, "bytes": 0})


def packet_analysis(pkt):
    if not pkt.haslayer(IP):
        return

    ip = pkt[IP]
    src_ip = ip.src
    dst_ip = ip.dst

    if pkt.haslayer(TCP):
        sport = pkt[TCP].sport
        dport = pkt[TCP].dport
        protocol = "TCP"

    elif pkt.haslayer(UDP):
        sport = pkt[UDP].sport
        dport = pkt[UDP].dport
        protocol = "UDP"

    elif pkt.haslayer(ICMP):
        sport = "-"
        dport = "-"
        protocol = "ICMP"

    else:
        return

    flow_key = (src_ip, sport, dst_ip, dport, protocol)

    packet_bytes = len(ip)
    timestamp = float(pkt.time)

    flow = flows[flow_key]
    flow["packets"] += 1
    flow["bytes"] += packet_bytes

    if flow["first"] is None:
        flow["first"] = timestamp

    flow["last"] = timestamp

    ip_stats[src_ip]["packets"] += 1
    ip_stats[src_ip]["bytes"] += packet_bytes


def print_flow(flow_key, stats):
    src, sport, dst, dport, protocol = flow_key
    duration = stats["last"] - stats["first"]

    print(
        f"{src}:{sport} -> {dst}:{dport} | "
        f"{protocol:4} | "
        f"Packets={stats['packets']:6} | "
        f"Bytes={stats['bytes']:10} | "
        f"Duration={duration:.6f} s"
    )


def show_top_flows(title, sort_key):
    print("\n" + "=" * 100)
    print(title)
    print("=" * 100)

    ranked = sorted(flows.items(), key=lambda item: item[1][sort_key], reverse=True)

    for rank, (key, stats) in enumerate(ranked[:10], start=1):
        print(f"{rank:2}. ", end="")
        print_flow(key, stats)


def show_ip_ranking(title, sort_key):
    print("\n" + "=" * 75)
    print(title)
    print("=" * 75)
    print(f"{'Rank':<6}{'Source IP':<20}{'Packets':>12}{'Bytes':>15}")

    ranked = sorted(ip_stats.items(), key=lambda item: item[1][sort_key], reverse=True)

    for rank, (ip, stats) in enumerate(ranked[:10], start=1):
        print(f"{rank:<6}{ip:<20}{stats['packets']:>12}{stats['bytes']:>15}")


def save_flows_csv():
    with open("network_flows.csv", "w", newline="") as file:
        writer = csv.writer(file)

        writer.writerow(
            [
                "Source IP",
                "Source Port",
                "Destination IP",
                "Destination Port",
                "Protocol",
                "Packets",
                "Bytes",
                "First Packet Time",
                "Last Packet Time",
                "Duration (seconds)",
            ]
        )

        for key, stats in flows.items():
            src, sport, dst, dport, protocol = key

            writer.writerow(
                [
                    src,
                    sport,
                    dst,
                    dport,
                    protocol,
                    stats["packets"],
                    stats["bytes"],
                    datetime.fromtimestamp(stats["first"]).isoformat(),
                    datetime.fromtimestamp(stats["last"]).isoformat(),
                    stats["last"] - stats["first"],
                ]
            )


def main():
    print("Network Flow Analysis")
    print("Capturing TCP, UDP and ICMP traffic for 15 minutes.\n")

    stop_event = threading.Event()
    capture_seconds = CAPTURE_SECONDS

    def countdown():
        for remaining in range(capture_seconds, 0, -1):
            if stop_event.is_set():
                break

            minutes, seconds = divmod(remaining, 60)
            print(
                f"\rTime remaining: {minutes:02d}:{seconds:02d}",
                end="",
                flush=True
            )
            stop_event.wait(1)

        if not stop_event.is_set():
            print("\rTime remaining: 00:00")
            print("Capture time completed.")

    timer_thread = threading.Thread(target=countdown, daemon=True)
    start = time.monotonic()

    timer_thread.start()

    try:
        sniff(
            filter=BPF_FILTER,
            prn=packet_analysis,
            store=False,
            timeout=capture_seconds
        )
    except KeyboardInterrupt:
        print("\nCapture stopped by user.")
    except (PermissionError, OSError) as exc:
        print(f"\nCapture error: {exc}")
    finally:
        stop_event.set()
        timer_thread.join()
        elapsed = time.monotonic() - start

    total_packets = sum(s["packets"] for s in flows.values())
    total_bytes = sum(s["bytes"] for s in flows.values())

    print(f"\nActual elapsed time: {elapsed:.2f} seconds")
    print(f"Unique directional flows: {len(flows)}")
    print(f"Total captured packets: {total_packets}")
    print(f"Total IP bytes: {total_bytes}")

    show_top_flows("TOP 10 FLOWS BY BYTES", "bytes")
    show_top_flows("TOP 10 FLOWS BY PACKETS", "packets")
    show_ip_ranking("TOP TALKERS: IPs BY PACKETS SENT", "packets")
    show_ip_ranking("TOP TALKERS: IPs BY BYTES SENT", "bytes")

    save_flows_csv()
    print("\nFull flow statistics saved to network_flows.csv")


if __name__ == "__main__":
    main()
