import java.io.*;
import java.net.*;
import java.nio.file.Files;
import java.util.*;

class Server extends Thread {
    public static final int PORT = 5000;
    private static final int BUFFER_SIZE = 65507;

    @Override
    public void run() {
        try (DatagramSocket socket = new DatagramSocket(PORT)) {
            System.out.println("[Server] Started at port " + PORT + " (UDP)");
            System.out.println("[Server] Waiting for client request...");

            byte[] receiveBuffer = new byte[BUFFER_SIZE];
            DatagramPacket requestPacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);

            socket.receive(requestPacket);

            String requestedFilename = new String(requestPacket.getData(), 0, requestPacket.getLength()).trim();
            System.out.println("[Server] Client requested file: " + requestedFilename);

            File fileToRead = new File(requestedFilename);
            byte[] responseData;

            if (fileToRead.exists() && fileToRead.isFile()) {
                System.out.println("[Server] File found. Reading and sending content...");
                responseData = Files.readAllBytes(fileToRead.toPath());
            } else {
                System.out.println("[Server] File not found. Sending error response.");
                responseData = ("ERROR: Requested file '" + requestedFilename + "' does not exist.").getBytes();
            }

            DatagramPacket responsePacket = new DatagramPacket(
                    responseData,
                    responseData.length,
                    requestPacket.getAddress(),
                    requestPacket.getPort()
            );
            socket.send(responsePacket);
            System.out.println("[Server] Response sent.");

        } catch (IOException e) {
            System.err.print("[Server] Error occurred \n[Server] ");
            e.printStackTrace();
        }
    }
}

class Client extends Thread {
    private static final int PORT = 5000;
    private static final int BUFFER_SIZE = 65507;

    @Override
    public void run() {
        try {
            Thread.sleep(500);
            Scanner sc = new Scanner(System.in);

            try (DatagramSocket socket = new DatagramSocket()) {
                InetAddress serverAddress = InetAddress.getByName("127.0.0.1");

                System.out.print("[Client] Enter the filename to request from server: ");
                String filenameRequest = sc.nextLine().trim();

                byte[] requestData = filenameRequest.getBytes();
                DatagramPacket requestPacket = new DatagramPacket(requestData, requestData.length, serverAddress, PORT);
                socket.send(requestPacket);
                System.out.println("[Client] Sent request for: " + filenameRequest);

                byte[] receiveBuffer = new byte[BUFFER_SIZE];
                DatagramPacket responsePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
                socket.receive(responsePacket);

                String responseStr = new String(responsePacket.getData(), 0, responsePacket.getLength());

                if (responseStr.startsWith("ERROR:")) {
                    System.out.println("[Client] Server Message: " + responseStr);
                } else {
                    System.out.println("[Client] Success! Received file contents.");

                    String saveFileName = "dl_" + filenameRequest;
                    File newFile = new File(saveFileName);

                    try (FileOutputStream fos = new FileOutputStream(newFile)) {
                        fos.write(responsePacket.getData(), 0, responsePacket.getLength());
                    }

                    System.out.println("[Client] File saved locally as: " + newFile.getAbsolutePath());
                    System.out.println("[Client] Content Preview:\n" + responseStr);
                }
            }
            sc.close();
        } catch (IOException | InterruptedException e) {
            System.err.println("[Client] Error occurred");
            e.printStackTrace();
        }
    }
}

public class udp_file {
    public static void main(String[] args) throws InterruptedException {
        Server server = new Server();
        Client client = new Client();

        server.start();
        client.start();

        server.join();
        client.join();

        System.out.println("Program finished");
    }
}
