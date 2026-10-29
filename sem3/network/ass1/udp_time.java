import java.io.*;
import java.util.*;
import java.net.*;
import java.time.LocalDate;
import java.time.LocalTime;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class udp_time {
    private static final int SERVER_PORT = 9876;
    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) {
        Thread serverThread = new Thread(new Server());
        Thread clientThread = new Thread(new Client());

        serverThread.start();
        clientThread.start();
    }

    static class Server implements Runnable {
        @Override
        public void run() {
            try (DatagramSocket socket = new DatagramSocket(SERVER_PORT)) {
                System.out.println("[SERVER] Running and listening on port " + SERVER_PORT + "...\n");
                byte[] receiveBuffer = new byte[BUFFER_SIZE];

                while (true) {
                    DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
                    socket.receive(receivePacket);

                    String request = new String(receivePacket.getData(), 0, receivePacket.getLength()).trim();
                    InetAddress clientAddress = receivePacket.getAddress();
                    int clientPort = receivePacket.getPort();

                    String response = processRequest(request);

                    byte[] sendData = response.getBytes();
                    DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, clientAddress, clientPort);
                    socket.send(sendPacket);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        private String processRequest(String request) {
            switch (request.toUpperCase()) {
                case "DATE":
                    return LocalDate.now().toString();
                case "TIME":
                    return LocalTime.now().format(DateTimeFormatter.ofPattern("HH:mm:ss"));
                case "DATETIME":
                    return LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
                default:
                    return "ERROR: Invalid command. Use DATE, TIME, or DATETIME.";
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
                        System.out.println("[CLIENT] Enter command (DATE, TIME, DATETIME) or 'EXIT' to quit:");
                        String command = scanner.nextLine().trim();

                        if (command.isEmpty()) continue;

                        if (command.equalsIgnoreCase("EXIT")) {
                            System.out.println("[CLIENT] Exiting...");
                            scanner.close();
                            System.exit(0);
                        }

                        System.out.println("[CLIENT] Sending request: " + command);

                        byte[] sendData = command.getBytes();
                        DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, serverAddress, SERVER_PORT);
                        socket.send(sendPacket);

                        byte[] receiveBuffer = new byte[BUFFER_SIZE];
                        DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
                        socket.receive(receivePacket);

                        String response = new String(receivePacket.getData(), 0, receivePacket.getLength());
                        System.out.println("[CLIENT] Received response: " + response + "\n");
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
