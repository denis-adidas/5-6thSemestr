import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class UDPServer {
    private static DatagramSocket serverSocket;
    private static InetAddress serverAddress;
    private static InetAddress clientAddress;
    private static boolean isConnected;
    private static int clientPort;


    public static void main(String args[]) throws Exception {
        startServer();

        ReadMessage readMessage = new ReadMessage(clientPort, clientAddress, serverSocket);
        WriteMessage writeMessage = new WriteMessage(clientAddress, clientPort, serverSocket);
        readMessage.start();
        writeMessage.start();
        writeMessage.join();
        System.out.println("Server is off");
    }
    private static void startServer() throws IOException {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter port for listening: ");
        int port = scanner.nextInt();
        System.out.println("The port is: " + port);
        serverSocket = new DatagramSocket(port);

        serverAddress = InetAddress.getByName("localhost");

        byte[] buffer = new byte[1024];
        DatagramPacket inputPacket = new DatagramPacket(buffer, buffer.length);
        System.out.println("Waiting for user...");
        getServerSocket().receive(inputPacket);
        clientPort = inputPacket.getPort();
        clientAddress = inputPacket.getAddress();
        DatagramPacket outputPacket = new DatagramPacket(buffer, buffer.length, getClientAddress(), getClientPort());
        System.out.println("New client: \n" + "Address: " + getClientAddress() + "\nPort" + getClientPort());
        isConnected = true;
    }

    public static DatagramSocket getServerSocket() {
        return serverSocket;
    }

    public static InetAddress getServerAddress() {
        return serverAddress;
    }

    public static InetAddress getClientAddress() {
        return clientAddress;
    }

    public static boolean isIsConnected() {
        return isConnected;
    }

    public static int getClientPort() {
        return clientPort;
    }
}
