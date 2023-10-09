import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class Server {
    private ServerSocket serverSocket;

    public Server(ServerSocket serverSocket) {
        this.serverSocket = serverSocket;
    }
    public void startServer() {
        try {
            while (!serverSocket.isClosed()) {
                Socket socket = serverSocket.accept();
                System.out.println("A new client has connected!");
                ClientHandler clientHandler = new ClientHandler(socket);

                Thread thread = new Thread(clientHandler);
                thread.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void clsoeServerSocket() {
        try {
            if (serverSocket != null) {
                serverSocket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
//    public static Server loadFromJsonFile() {
//        try (Reader reader = new BufferedReader(new InputStreamReader(
//                new FileInputStream("users.json"), StandardCharsets.UTF_8))) {
//            Gson gson = new Gson();
//            return gson.fromJson(reader, Server.class);
//        } catch (IOException e) {
//            e.printStackTrace(); // Handle the exception according to your needs
//            return null;
//        }
//    }

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(1234);
//        loadFromJsonFile();
        Server server = new Server(serverSocket);
        server.startServer();
    }
}
