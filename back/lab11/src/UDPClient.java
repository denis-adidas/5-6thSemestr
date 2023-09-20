import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;
import java.util.Scanner;

public class UDPClient {
    private static InetAddress inetAddress;
    private static int port;
    private static DatagramSocket clientSocket;

    public static void main(String[] args) throws Exception{
        doConnection();

        ReadMessage readMessage = new ReadMessage(port, inetAddress, clientSocket);
        WriteMessage writeMessage = new WriteMessage(inetAddress, port, clientSocket);
        readMessage.start();
        writeMessage.start();
        writeMessage.join();
    }
    public static void doConnection() throws SocketException, UnknownHostException {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter hostname: ");
        inetAddress = InetAddress.getByName(scanner.nextLine());
        System.out.println("Enter port: ");
        port = scanner.nextInt();
        clientSocket = new DatagramSocket();
        byte[] buffer = new byte[1024];
        String firstPacket = "Connected";
        buffer = firstPacket.getBytes();
        DatagramPacket outputPacket = new DatagramPacket(buffer, firstPacket.length(), inetAddress, port);
        try {
            clientSocket.send(outputPacket);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}