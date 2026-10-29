import java.io.*;
import java.net.*;
import java.util.*;

class FileDataObject implements Serializable {
    private static final long serialVersionUID = 1L;
    private final String fileName;
    private final String fileExtension;
    private final byte[] fileContent;

    public FileDataObject(String fileName, byte[] fileContent) {
        this.fileExtension = fileName.contains(".") ? fileName.substring(fileName.lastIndexOf(".")) : "";
        this.fileName =  fileName.contains(".") ? fileName.substring(0, fileName.lastIndexOf('.')) : fileName;
        this.fileContent = fileContent;
    }

    public String getFileName() { return fileName; }
    public byte[] getFileContent() { return fileContent; }
    public String getFileExtension() { return fileExtension; }

    @Override
    public String toString() {
        return "FileDataObject {name='" + fileName + "', extension='" + fileExtension + "', size=" + fileContent.length + " bytes}";
    }
}

class Server extends Thread {
    public static final int PORT = 5000;

    @Override
    public void run() {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("[Server] Started at port " + PORT);
            System.out.println("[Server] Waiting for client connection...");

            Socket socket = serverSocket.accept();
            System.out.println("[Server] Client connected");

            ObjectInputStream input = new ObjectInputStream(socket.getInputStream());
            ObjectOutputStream output = new ObjectOutputStream(socket.getOutputStream());

            String requestedFilename = (String) input.readObject();
            System.out.println("[Server] Client requested file: " + requestedFilename);

            File fileToRead = new File(requestedFilename);

            if (fileToRead.exists() && fileToRead.isFile()) {
                System.out.println("[Server] File found. Reading content...");

                StringBuilder contentBuilder = new StringBuilder();
                Scanner fileScanner = new Scanner(fileToRead);
                while (fileScanner.hasNextLine()) {
                    contentBuilder.append(fileScanner.nextLine());
                    if (fileScanner.hasNextLine()) {
                        contentBuilder.append("\n");
                    }
                }
                fileScanner.close();

                byte[] fileBytes = contentBuilder.toString().getBytes();
                FileDataObject payload = new FileDataObject(fileToRead.getName(), fileBytes);

                output.writeObject(payload);
                System.out.println("[Server] Sent file object to client");
            } else {
                System.out.println("[Server] File not found. Sending error response.");
                output.writeObject("ERROR: Requested file '" + requestedFilename + "' does not exist on the server.");
            }

            output.flush();
            socket.close();
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("[Server] Error occurred");
            e.printStackTrace();
        }
    }
}

class Client extends Thread {
    private static final int PORT = 5000;

    @Override
    public void run() {
        try {
            Thread.sleep(500);
            Socket socket = new Socket("127.0.0.1", PORT);
            Scanner sc = new Scanner(System.in);
            System.out.println("[Client] Connected to Server");

            ObjectOutputStream output = new ObjectOutputStream(socket.getOutputStream());
            ObjectInputStream input = new ObjectInputStream(socket.getInputStream());

            System.out.print("[Client] Enter the filename to request from server: ");
            String filenameRequest = sc.nextLine();

            output.writeObject(filenameRequest);
            output.flush();
            System.out.println("[Client] Sent request for: " + filenameRequest);

            Object serverResponse = input.readObject();

            if (serverResponse instanceof FileDataObject) {
                FileDataObject receivedFile = (FileDataObject) serverResponse;
                System.out.println("[Client] Success! Received Object: " + receivedFile);

                String saveFileName = receivedFile.getFileName() + "_dl" + receivedFile.getFileExtension();
                File newFile = new File(saveFileName);

                try (FileOutputStream fos = new FileOutputStream(newFile)) {
                    fos.write(receivedFile.getFileContent());
                    fos.flush();
                }

                System.out.println("[Client] File saved locally as: " + newFile.getAbsolutePath());
                System.out.println("[Client] Content Preview:\n" + new String(receivedFile.getFileContent()));

            }
            else if (serverResponse instanceof String) {
                String errorMessage = (String) serverResponse;
                System.out.println("[Client] Server Message: " + errorMessage);
            }

            socket.close();
            sc.close();
        } catch (IOException | ClassNotFoundException | InterruptedException e) {
            System.err.println("[Client] Error occurred");
            e.printStackTrace();
        }
    }
}

public class tcp_file {
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
