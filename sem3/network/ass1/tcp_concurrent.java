import java.io.*;
import java.net.*;
import java.time.*;
import java.util.*;
import java.util.concurrent.*;

class Server extends Thread {
    public static final int PORT = 5000;
    private final ExecutorService threadPool = Executors.newCachedThreadPool();
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
                    System.out.println("[Server] New connection accepted from " + clientAddr);

                    threadPool.submit(new ClientHandler(socket, clientAddr));
                }
                catch (SocketException e) {
                    if (!running) {
                        System.out.println("[Server] Server socket closed cleanly.");
                        break;
                    }
                }
            }
        }
        catch (IOException e) {
            if (running) System.err.println("[Server] Socket error: " + e.getMessage());
        }
        finally {
            threadPool.shutdownNow();
            System.out.println("[Server] Server stopped.");
        }
    }

    public void stopServer() {
        this.running = false;
        try {
            if (serverSocket != null && !serverSocket.isClosed()) serverSocket.close();
        }
        catch (IOException e) {
            System.err.println("[Server] Error closing server socket: " + e.getMessage());
        }
    }
}

class ClientHandler implements Runnable {
    private final Socket socket;
    private final String clientAddress;

    public ClientHandler(Socket socket, String clientAddress) {
        this.socket = socket;
        this.clientAddress = clientAddress;
    }

    @Override
    public void run() {
        try (
            ObjectOutputStream output = new ObjectOutputStream(socket.getOutputStream());
            ObjectInputStream input = new ObjectInputStream(socket.getInputStream())
        ) {
            output.flush();

            while (!Thread.currentThread().isInterrupted()) {
                String req = (String) input.readObject();
                if (req == null) break;

                System.out.println("[Server -> " + clientAddress + "] Received: " + req);
                String res;

                String upperReq = req.toUpperCase().trim();
                if (upperReq.equals("TIME")) {
                    res = LocalTime.now().toString();
                }
                else if (upperReq.equals("DATE")) {
                    res = LocalDate.now().toString();
                }
                else if (upperReq.equals("HOSTNAME")) {
                    res = InetAddress.getLocalHost().getHostName();
                }
                else if (upperReq.equals("QUIT")) {
                    res = "QUIT_ACK";
                }
                else if (upperReq.startsWith("ECHO ")) {
                    res = req.substring(5);
                }
                else {
                    res = "ERROR: Invalid command";
                }

                output.writeObject(res);
                output.flush();

                if (upperReq.equals("QUIT")) {
                    break;
                }
            }
        }
        catch (IOException | ClassNotFoundException e) {
            System.out.println("[Server] Client " + clientAddress + " disconnected.");
        }
        finally {
            try {
                socket.close();
            }
            catch (IOException ignored) {}
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
        try {
            Thread.sleep(100 * clientId);

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
            }
            System.out.println("[Client-" + clientId + "] Session finished.");
        }
        catch (Exception e) {
            System.err.println("[Client-" + clientId + "] Error: " + e.getMessage());
        }
    }
}

public class tcp_concurrent {
    public static void main(String[] args) throws InterruptedException {
        Server server = new Server();
        server.start();

        Thread.sleep(500);

        List<String> client1Cmds = Arrays.asList("TIME", "ECHO Hello from Client 1", "DATE", "QUIT");
        List<String> client2Cmds = Arrays.asList("HOSTNAME", "ECHO Heavy Load Test", "TIME", "QUIT");
        List<String> client3Cmds = Arrays.asList("DATE", "INVALID_CMD", "ECHO Quick ping", "QUIT");

        Client client1 = new Client(1, client1Cmds);
        Client client2 = new Client(2, client2Cmds);
        Client client3 = new Client(3, client3Cmds);

        System.out.println("Launching 3 Concurrent Clients");
        client1.start();
        client2.start();
        client3.start();

        client1.join();
        client2.join();
        client3.join();

        System.out.println("All clients finished. Shutting down server...");
        server.stopServer();
        server.join();

        System.out.println("Program finished cleanly.");
    }
}
