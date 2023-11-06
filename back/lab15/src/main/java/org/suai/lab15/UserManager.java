package org.suai.lab15;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileSystems;
import java.util.ArrayList;

public class UserManager {
    private ArrayList<User> users = new ArrayList<User>();

    public void addUser(User user) {
        getUsers().add(user);
        saveToJsonFile("autosave.json");
    }

    public User getUserByName(String name) {
        for (User user : users) {
            if (user.getName().equals(name)) {
                return user;
            }
        }
        return null;
    }
    public synchronized void saveToJsonFile(String filePath) {
        try (Writer writer = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream(filePath), StandardCharsets.UTF_8))) {
            Gson gson = new GsonBuilder().setPrettyPrinting().create();
            gson.toJson(this, writer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public synchronized static UserManager loadFromJsonFile(String filePath) {
        try (Reader reader = new BufferedReader(new InputStreamReader(
                new FileInputStream(filePath), StandardCharsets.UTF_8))) {
            Gson gson = new Gson();
            return gson.fromJson(reader, UserManager.class);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public ArrayList<User> getUsers() {
        return users;
    }

}
