import java.io.*;
import java.net.*;
import java.util.*;

public class udp_dns {
    private static final int PORT = 9876;
    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) {
        Thread serverThread = new Thread(new Server());
        Thread clientThread = new Thread(new Client());

        serverThread.start();
        clientThread.start();
    }

    static class Server implements Runnable {
        private final Map<String, String> dnsTable;

        public Server() {
            dnsTable = new HashMap<>();
            dnsTable.put("server1", "192.168.1.10");
            dnsTable.put("server2", "192.168.1.20");
            dnsTable.put("db-primary", "10.0.0.5");
            dnsTable.put("cache-node", "10.0.0.12");
            dnsTable.put("gateway", "192.168.1.1");
        }

        @Override
        public void run() {
            try (DatagramSocket socket = new DatagramSocket(PORT)) {
                System.out.println("[SERVER] DNS Resolver running and listening on port " + PORT + "...\n");
                byte[] receiveBuffer = new byte[BUFFER_SIZE];

                while (true) {
                    DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
                    socket.receive(receivePacket);

                    String requestedHost = new String(receivePacket.getData(), 0, receivePacket.getLength()).trim();
                    InetAddress clientAddress = receivePacket.getAddress();
                    int clientPort = receivePacket.getPort();

                    String response = dnsTable.getOrDefault(requestedHost.toLowerCase(), "NOT FOUND");

                    byte[] sendData = response.getBytes();
                    DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, clientAddress, clientPort);
                    socket.send(sendPacket);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    static class Client implements Runnable {
        @Override
        public void run() {
            try {
                Thread.sleep(500);

                InetAddress serverAddress = InetAddress.getByName("localhost");
                Scanner scanner = new Scanner(System.in);

                try (DatagramSocket socket = new DatagramSocket()) {
                    while (true) {
                        System.out.print("[CLIENT] Enter hostname to resolve (or 'EXIT' to quit): ");
                        String hostname = scanner.nextLine().trim();

                        if (hostname.isEmpty()) continue;

                        if (hostname.equalsIgnoreCase("EXIT")) {
                            System.out.println("[CLIENT] Exiting...");
                            scanner.close();
                            System.exit(0);
                        }

                        byte[] sendData = hostname.getBytes();
                        DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, serverAddress, PORT);
                        socket.send(sendPacket);

                        byte[] receiveBuffer = new byte[BUFFER_SIZE];
                        DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
                        socket.receive(receivePacket);

                        String ipAddress = new String(receivePacket.getData(), 0, receivePacket.getLength());
                        System.out.println("[CLIENT] Result: " + ipAddress + "\n");
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
