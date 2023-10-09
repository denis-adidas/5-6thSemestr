import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;
import com.google.gson.reflect.TypeToken;

import java.io.*;
import java.lang.ref.Cleaner;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ClientHandler implements Runnable {
    public static ArrayList<ClientHandler> clientHandlers = new ArrayList<>();
    private Socket socket;
    private BufferedReader bufferedReader;
    private BufferedWriter bufferedWriter;
    private String clientUsername;
    private String clientPassword;

    public ClientHandler(Socket socket) {
        try {
            this.socket = socket;
            this.bufferedWriter = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            this.bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));


            this.clientUsername = bufferedReader.readLine();
            this.clientPassword = bufferedReader.readLine();

            List<User> users = loadUsersFromJson("users.json");
            if (users != null) {
                boolean isValidUser = false;
                for (User user : users) {
                    if (user.getUsername().equals(clientUsername) && user.getPassword().equals(clientPassword)) {
                        clientHandlers.add(this);
                        broadcastMessageToAll("SERVER: " + clientUsername + " has entered the chat!");
                        break;
                    }
                }

                if (!isValidUser) {
                    broadcastMessageToAll("Invalid username or password. Closing connection.");
                    closeEverything(socket, bufferedReader, bufferedWriter);
                    return;
                }
            } else {
                broadcastMessageToAll("Failed to load user data. Closing connection.");
                closeEverything(socket, bufferedReader, bufferedWriter);
                return;
            }



        } catch (IOException e) {
            closeEverything(socket, bufferedReader, bufferedWriter);
        }
    }

    @Override
    public void run() {
        String messageFromClient;

        while (socket.isConnected()) {
            try {
                messageFromClient = bufferedReader.readLine();
                if (messageFromClient.contains("@senduser")) {
                    String[] words = messageFromClient.split(" ");
                    if (words.length >= 4) {
                        String username = words[2];
                        String message = words[0] + " " + String.join(" ", Arrays.copyOfRange(words, 3, words.length));
                        broadcastMessageToUser(message , username);
                    } else {
                        broadcastMessageToAll("fail(");
                    }
                } else {
                    broadcastMessageToAll(messageFromClient);
                }
            } catch (IOException e) {
                closeEverything(socket, bufferedReader, bufferedWriter);
                break;
            }
        }
    }
    public void broadcastMessageToAll(String messageToSend) {
        for (ClientHandler clientHandler : clientHandlers) {
            try {
                if (!clientHandler.clientUsername.equals(clientUsername)) {
                    clientHandler.bufferedWriter.write(messageToSend);
                    clientHandler.bufferedWriter.newLine();
                    clientHandler.bufferedWriter.flush();
                }
            } catch (IOException e) {
                closeEverything(socket, bufferedReader, bufferedWriter);
            }
        }
    }
    public void broadcastMessageToUser(String messageToSend, String username) {
        for (ClientHandler clientHandler : clientHandlers) {
            try {
                if (clientHandler.clientUsername.equals(username)) {
                    clientHandler.bufferedWriter.write(messageToSend);
                    clientHandler.bufferedWriter.newLine();
                    clientHandler.bufferedWriter.flush();
                }
            } catch (IOException e) {
                closeEverything(socket, bufferedReader, bufferedWriter);
            }
        }
    }
    public void removeClienthandler(){
        clientHandlers.remove(this);
        broadcastMessageToAll("SERVER: " + clientUsername + " has left the chat");
    }
    public void closeEverything(Socket socket, BufferedReader bufferedReader, BufferedWriter bufferedWriter) {
        removeClienthandler();
        try {
            if (bufferedReader != null) {
                bufferedReader.close();
            }
            if (bufferedWriter != null) {
                bufferedWriter.close();
            }
            if (socket != null) {
                socket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    private static List<User> loadUsersFromJson(String filePath) {
        try (Reader reader = new BufferedReader(new InputStreamReader(
                new FileInputStream(filePath), StandardCharsets.UTF_8))) {
            Gson gson = new Gson();
            return gson.fromJson(reader, new TypeToken<List<User>>() {}.getType());
        } catch (IOException | JsonSyntaxException e) {
            e.printStackTrace();
            return null;
        }
    }
}
