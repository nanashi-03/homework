import java.io.*;
import java.net.*;
import java.time.*;
import java.util.*;

class Server extends Thread {

    public static final int PORT = 5000;

    private volatile boolean running = true;
    private ServerSocket serverSocket;

    @Override
    public void run() {
        try {
            serverSocket = new ServerSocket(PORT);

            System.out.println("[Server] Started on port " + PORT + " (Listening for clients...)");

            while (running) {
                try {
                    Socket socket = serverSocket.accept();

                    String clientAddr = socket.getInetAddress().getHostAddress() + ":" + socket.getPort();

                    System.out.println("[Server] Connected to " + clientAddr);

                    handleClient(socket, clientAddr);

                    System.out.println("[Server] Ready for next client...");
                } catch (SocketException e) {
                    if (!running) {
                        System.out.println("[Server] Server socket closed.");
                        break;
                    }
                }
            }
        } catch (IOException e) {
            if (running) {
                System.err.println("[Server] Error: " + e.getMessage());
            }
        } finally {
            System.out.println("[Server] Server stopped.");
        }
    }

    private void handleClient(Socket socket, String clientAddress) {
        try (
            ObjectOutputStream output = new ObjectOutputStream(socket.getOutputStream());
            ObjectInputStream input = new ObjectInputStream(socket.getInputStream())
        ) {
            output.flush();

            while (true) {
                String req = (String) input.readObject();

                System.out.println("[Server -> " + clientAddress + "] Received: " + req);

                String res;

                String upperReq = req.toUpperCase().trim();

                if (upperReq.equals("TIME")) {
                    res = LocalTime.now().toString();
                } else if (upperReq.equals("DATE")) {
                    res = LocalDate.now().toString();
                } else if (upperReq.equals("HOSTNAME")) {
                    res = InetAddress.getLocalHost().getHostName();
                } else if (upperReq.equals("QUIT")) {
                    res = "QUIT_ACK";
                } else if (upperReq.startsWith("ECHO ")) {
                    res = req.substring(5);
                } else {
                    res = "ERROR: Invalid command";
                }

                output.writeObject(res);
                output.flush();

                if (upperReq.equals("QUIT")) {
                    break;
                }
            }
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("[Server] Client " + clientAddress + " disconnected.");
        } finally {
            try {
                socket.close();
            } catch (IOException ignored) {}
        }
    }

    public void stopServer() {
        running = false;

        try {
            if (serverSocket != null && !serverSocket.isClosed()) {
                serverSocket.close();
            }
        } catch (IOException e) {
            System.err.println("[Server] Error closing server: " + e.getMessage());
        }
    }
}

class Client extends Thread {

    private final int clientId;
    private final List<String> commandsToExecute;

    public Client(int clientId, List<String> commandsToExecute) {
        this.clientId = clientId;
        this.commandsToExecute = commandsToExecute;
    }

    @Override
    public void run() {
        try (Socket socket = new Socket("127.0.0.1", Server.PORT)) {
            System.out.println("[Client-" + clientId + "] Connected to server.");

            ObjectOutputStream output = new ObjectOutputStream(socket.getOutputStream());

            output.flush();

            ObjectInputStream input = new ObjectInputStream(socket.getInputStream());

            for (String cmd : commandsToExecute) {
                Thread.sleep(300);
                System.out.println("[Client-" + clientId + "] Sending: " + cmd);

                output.writeObject(cmd);
                output.flush();

                String res = (String) input.readObject();

                System.out.println("[Client-" + clientId + "] Received: " + res);

                if (cmd.trim().equalsIgnoreCase("QUIT")) {
                    break;
                }
            }

            System.out.println("[Client-" + clientId + "] Session finished.");
        } catch (Exception e) {
            System.err.println(
                "[Client-" + clientId + "] Error: " + e.getMessage()
            );
        }
    }
}

public class tcp_sequential {

    public static void main(String[] args) throws InterruptedException {
        Server server = new Server();
        server.start();
        Thread.sleep(500);

        List<String> client1Cmds = Arrays.asList(
            "TIME",
            "ECHO Hello from Client 1",
            "DATE",
            "QUIT"
        );

        List<String> client2Cmds = Arrays.asList(
            "HOSTNAME",
            "ECHO Heavy Load Test",
            "TIME",
            "QUIT"
        );

        List<String> client3Cmds = Arrays.asList(
            "DATE",
            "INVALID_CMD",
            "ECHO Quick ping",
            "QUIT"
        );

        Client client1 = new Client(1, client1Cmds);
        Client client2 = new Client(2, client2Cmds);
        Client client3 = new Client(3, client3Cmds);

        System.out.println("\nRunning clients sequentially\n");

        System.out.println("Starting Client 1...");
        client1.start();
        client1.join();

        System.out.println("\nStarting Client 2...");
        client2.start();
        client2.join();

        System.out.println("\nStarting Client 3...");
        client3.start();
        client3.join();
        System.out.println("\nAll clients finished.");

        server.stopServer();
        server.join();

        System.out.println("Program finished cleanly.");
    }
}
