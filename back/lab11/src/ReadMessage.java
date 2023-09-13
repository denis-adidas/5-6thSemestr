import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class ReadMessage extends Thread {
    boolean isConnected;
    int port;
    InetAddress address;
    DatagramSocket socket;
    public ReadMessage(int port, InetAddress address, DatagramSocket socket) {
        this.port = port;
        this.address = address;
        this.socket = socket;
        this.isConnected = true;
    }

    @Override
    public void run() {
        System.out.println("What do you want to do?");
        System.out.println("""
                1. Set username - @name;
                2. Send message - just write a message;
                3. Exit - @quit""");
        while (isConnected) {
            try {
                byte[] buffer = new byte[1024];
                DatagramPacket inputPacket = new DatagramPacket(buffer, buffer.length);
                socket.receive(inputPacket);
                String message = new String(inputPacket.getData(), 0, inputPacket.getLength());
                System.out.println(message);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
