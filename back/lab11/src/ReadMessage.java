import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class ReadMessage extends Thread {
    private boolean isConnected;
    private int port;
    private InetAddress address;
    private DatagramSocket socket;
    private static StringBuilder chatHistory;
    public ReadMessage(int port, InetAddress address, DatagramSocket socket, StringBuilder chatHistory) {
        this.port = port;
        this.address = address;
        this.socket = socket;
        this.isConnected = true;
        this.chatHistory = chatHistory;
    }

    @Override
    public void run() {
        System.out.println("What do you want to do?");
        System.out.println("""
                1. Set username - @name;
                2. Save chat history - @dumpfile;
                3. Send message - just write a message;
                4. Exit - @quit""");
        while (isConnected) {
            try {
                byte[] buffer = new byte[1024];
                DatagramPacket inputPacket = new DatagramPacket(buffer, buffer.length);
                socket.receive(inputPacket);
                String message = new String(inputPacket.getData(), 0, inputPacket.getLength());
                if (message.equals("@dumpfile")) {
                    saveInFile();
                }
                else {
                    chatHistory.append(message).append("\n");
                    System.out.println(message);
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }
    public void saveInFile() {
        try {
            File file = new File("dumpFile.txt");
            file.createNewFile();
            FileWriter fileWriter = new FileWriter(file, false);

            try (BufferedWriter writer = new BufferedWriter(fileWriter)) {
                writer.write(chatHistory.toString());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
