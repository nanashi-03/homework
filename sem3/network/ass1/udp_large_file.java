import java.io.*;
import java.net.*;
import java.nio.file.Files;
import java.util.*;

class Server extends Thread {
    public static final int PORT = 5000;
    private static final int CHUNK_SIZE = 4096;

    @Override
    public void run() {
        try (DatagramSocket socket = new DatagramSocket(PORT)) {
            System.out.println("[Server] Started at port " + PORT + " (UDP Large File Mode)");
            System.out.println("[Server] Waiting for client request...");

            byte[] receiveBuffer = new byte[1024];
            DatagramPacket requestPacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);

            socket.receive(requestPacket);
            String requestedFilename = new String(requestPacket.getData(), 0, requestPacket.getLength()).trim();
            System.out.println("[Server] Client requested file: " + requestedFilename);

            File fileToRead = new File(requestedFilename);

            if (fileToRead.exists() && fileToRead.isFile()) {
                System.out.println("[Server] File found. Dividing into chunks...");
                byte[] fileBytes = Files.readAllBytes(fileToRead.toPath());

                int totalChunks = (int) Math.ceil((double) fileBytes.length / CHUNK_SIZE);
                System.out.println("[Server] Total chunks to send: " + totalChunks);

                for (int seqNumber = 0; seqNumber < totalChunks; seqNumber++) {
                    int offset = seqNumber * CHUNK_SIZE;
                    int length = Math.min(CHUNK_SIZE, fileBytes.length - offset);

                    ByteArrayOutputStream baos = new ByteArrayOutputStream();
                    DataOutputStream dos = new DataOutputStream(baos);
                    dos.writeInt(totalChunks);
                    dos.writeInt(seqNumber);
                    dos.writeInt(length);
                    dos.write(fileBytes, offset, length);

                    byte[] sendData = baos.toByteArray();
                    DatagramPacket sendPacket = new DatagramPacket(
                            sendData, sendData.length, requestPacket.getAddress(), requestPacket.getPort());

                    socket.send(sendPacket);

                    Thread.sleep(1);
                }
                System.out.println("[Server] All chunks sent successfully.");
            } else {
                System.out.println("[Server] File not found. Sending error response.");
                sendError(socket, requestPacket, "ERROR: Requested file '" + requestedFilename + "' does not exist.");
            }
        } catch (IOException | InterruptedException e) {
            System.err.println("[Server] Error occurred");
            e.printStackTrace();
        }
    }

    private void sendError(DatagramSocket socket, DatagramPacket requestPacket, String errorMsg) throws IOException {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(baos);

        byte[] errorBytes = errorMsg.getBytes();
        dos.writeInt(-1);
        dos.writeInt(0);
        dos.writeInt(errorBytes.length);
        dos.write(errorBytes);

        byte[] sendData = baos.toByteArray();
        DatagramPacket sendPacket = new DatagramPacket(
                sendData, sendData.length, requestPacket.getAddress(), requestPacket.getPort());
        socket.send(sendPacket);
    }
}

class Client extends Thread {
    private static final int PORT = 5000;

    @Override
    public void run() {
        try {
            Thread.sleep(500);
            Scanner sc = new Scanner(System.in);

            try (DatagramSocket socket = new DatagramSocket()) {
                socket.setSoTimeout(5000);
                InetAddress serverAddress = InetAddress.getByName("127.0.0.1");

                System.out.print("[Client] Enter the filename to request from server: ");
                String filenameRequest = sc.nextLine().trim();

                byte[] requestData = filenameRequest.getBytes();
                DatagramPacket requestPacket = new DatagramPacket(requestData, requestData.length, serverAddress, PORT);
                socket.send(requestPacket);
                System.out.println("[Client] Sent request for: " + filenameRequest);

                int totalChunks = -1;
                int chunksReceived = 0;
                byte[][] fileDataArray = null;

                while (true) {
                    byte[] receiveBuffer = new byte[5000];
                    DatagramPacket responsePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);

                    try {
                        socket.receive(responsePacket);
                    } catch (SocketTimeoutException e) {
                        System.out.println("[Client] Timeout! Packets were lost in transit. File corrupted.");
                        break;
                    }

                    ByteArrayInputStream bais = new ByteArrayInputStream(responsePacket.getData(), 0, responsePacket.getLength());
                    DataInputStream dis = new DataInputStream(bais);

                    int headerTotalChunks = dis.readInt();

                    if (headerTotalChunks == -1) {
                        dis.readInt();
                        int len = dis.readInt();
                        byte[] errBytes = new byte[len];
                        dis.read(errBytes);
                        System.out.println("[Client] Server Message: " + new String(errBytes));
                        return;
                    }

                    if (totalChunks == -1) {
                        totalChunks = headerTotalChunks;
                        fileDataArray = new byte[totalChunks][];
                        System.out.println("[Client] Expecting " + totalChunks + " chunks. Receiving...");
                    }

                    int seqNumber = dis.readInt();
                    int dataLength = dis.readInt();

                    if (fileDataArray[seqNumber] == null) {
                        byte[] payload = new byte[dataLength];
                        dis.read(payload);
                        fileDataArray[seqNumber] = payload;
                        chunksReceived++;
                    }

                    if (chunksReceived == totalChunks) {
                        System.out.println("[Client] Success! All " + totalChunks + " chunks received.");
                        break;
                    }
                }

                if (chunksReceived == totalChunks && fileDataArray != null) {
                    String saveFileName = "dl_" + filenameRequest;
                    File newFile = new File(saveFileName);

                    try (FileOutputStream fos = new FileOutputStream(newFile)) {
                        for (int i = 0; i < totalChunks; i++) {
                            fos.write(fileDataArray[i]);
                        }
                    }
                    System.out.println("[Client] File perfectly reconstructed and saved locally as: " + newFile.getAbsolutePath());
                }

            }
            sc.close();
        } catch (IOException | InterruptedException e) {
            System.err.println("[Client] Error occurred");
            e.printStackTrace();
        }
    }
}

public class udp_large_file {
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
