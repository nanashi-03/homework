import java.io.*;
import java.net.*;
import java.util.*;

class Response implements Serializable {
    private static final long serialVersionUID = 1L;

    private int length;
    private int vowels;
    private int consonants;
    private int digits;

    public Response(int length, int vowels, int consonants, int digits) {
        this.length = length;
        this.vowels = vowels;
        this.consonants = consonants;
        this.digits = digits;
    }

    @Override
    public String toString() {
        return "Response {\n" +
          "length = " + length + ",\n" +
          "vowels = " + vowels + ",\n" +
          "consonants = " + consonants + ",\n" +
          "digits = " + digits + ",\n" +
        "}";
    }
}

class Server extends Thread {
    public static final int PORT = 5000;

    private boolean isVowel(char ch) {
        ch = Character.toLowerCase(ch);

        return ch == 'a' ||
            ch == 'e' ||
            ch == 'i' ||
            ch == 'o' ||
            ch == 'u';
    }

    @Override
    public void run() {
        try(ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("[Server] Started at port " + PORT );
            System.out.println("[Server] Waiting for client...");

            Socket socket = serverSocket.accept();

            System.out.println("[Server] Client connected");

            ObjectInputStream input = new ObjectInputStream(socket.getInputStream());

            String req = (String) input.readObject();

            System.out.println("[Server] Received: " + req);

            int length = req.length();
            int vowels = 0, consonants = 0, digits = 0;

            for(char ch : req.toCharArray()) {
                if(Character.isDigit(ch)) digits++;
                if(Character.isLetter(ch)) {
                    if(isVowel(ch)) vowels++;
                    else consonants++;
                }
            }

            Response res = new Response(length, vowels, consonants, digits);

            ObjectOutputStream output = new ObjectOutputStream(socket.getOutputStream());
            output.writeObject(res);
            output.flush();

            System.out.println("[Server] Response sent to client");

            socket.close();
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("[Server] Error");
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

            System.out.println("[Client] Enter a String: ");
            String str = sc.nextLine();

            output.writeObject(str);
            output.flush();

            System.out.println("[Client] Sent: " + str);

            ObjectInputStream input = new ObjectInputStream(socket.getInputStream());

            Response res = (Response) input.readObject();

            System.out.println("[Client] Response received: ");
            System.out.println(res.toString());

            socket.close();
            sc.close();
        } catch (IOException | ClassNotFoundException | InterruptedException e) {
            System.err.println("[Client] Error");
            e.printStackTrace();
        }
    }
}

public class tcp_string {
    public static void main(String args[]) throws InterruptedException {
        Server server = new Server();
        Client client = new Client();

        server.start();
        client.start();

        server.join();
        client.join();

        System.out.println("Program finished");
    }
}
