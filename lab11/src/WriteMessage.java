import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class WriteMessage extends Thread {
    private static String userName;
    private InetAddress address;
    private int port;
    private DatagramSocket socket;

    public WriteMessage(InetAddress address, int port, DatagramSocket socket) {
        this.setAddress(address);
        this.setPort(port);
        this.setSocket(socket);
        this.setUserName("Unknown");
    }

    @Override
    public void run() {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            String message = scanner.nextLine();
            if (message.charAt(0) == '@')
                commandMenu(message);
            else
                sendMessage(message);
        }
    }

    public void sendMessage(String message) {
        message = getUserName() + ": " + message;
        byte[] buffer;
        buffer = message.getBytes();
        DatagramPacket outputPacket = new DatagramPacket(buffer, message.length(), address, port);
        try {
            socket.send(outputPacket);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
    public void commandMenu(String message) {
        String[] options;
        options = message.split(" ");
        while (true) {
            if (options[0].equals("@name")) {
                System.out.println("Your new user name: ");
                WriteMessage.setUserName(options[1]);
                System.out.println(options[1]);
                break;
            }
            else if (options[0].equals("@quit")) {
                System.exit(1);
            }
            else {
                sendMessage(message);
                break;
            }
        }
    }
    public static String getUserName() {
        return userName;
    }

    public static void setUserName(String userName) {
        WriteMessage.userName = userName;
    }

    public InetAddress getAddress() {
        return address;
    }

    public void setAddress(InetAddress address) {
        this.address = address;
    }

    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public DatagramSocket getSocket() {
        return socket;
    }

    public void setSocket(DatagramSocket socket) {
        this.socket = socket;
    }
}
