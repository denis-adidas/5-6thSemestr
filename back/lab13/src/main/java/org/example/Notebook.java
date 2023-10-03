package org.example;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class Notebook {
    public class Person {
        @SerializedName("numbers")
        @Expose
        private ArrayList<String> numbers;
        @SerializedName("name")
        @Expose
        private final String name;

        public Person(String name, ArrayList<String> numbers) {
            this.name = name;
            this.numbers = numbers;
        }
        public Person(String name) {
            this.name = name;
            this.numbers = new ArrayList<String>();
        }
        public void addNumber(String number) {
            if (!number.isEmpty())
                numbers.add(number);
        }
        public void removeNumber(String number) {
            numbers.remove(number);
        }

        public ArrayList<String> getNumbers() {
            return numbers;
        }

        public String getName() {
            return name;
        }

    }
    private ArrayList<Person> persons = new ArrayList<Person>();

    public Notebook() {
        persons.add(new Person("Vasya"));
        persons.add(new Person("Kolya"));
    }

    public synchronized void addPerson(String name) {
        persons.add(new Person(name));
    }
    public synchronized void addPersonNumber(String name, String number) {
        persons.get(persons.indexOf(name)).addNumber(number);
    }
    public synchronized void removePersonNumber(String name, String number) {
        persons.get(persons.indexOf(name)).removeNumber(number);
    }

    public synchronized String[] getNamesStrings() {
        String[] array = new String [persons.size()];
        array = persons.toArray(array);
        return array;
    }

    public synchronized void reset() {
        persons.clear();
    }
    public void saveToJsonFile(String filePath) {
        try (Writer writer = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream(filePath), StandardCharsets.UTF_8))) {
            Gson gson = new GsonBuilder().setPrettyPrinting().create();
            gson.toJson(this, writer);
        } catch (IOException e) {
            e.printStackTrace(); // Handle the exception according to your needs
        }
    }

    public static Notebook loadFromJsonFile(String filePath) {
        try (Reader reader = new BufferedReader(new InputStreamReader(
                new FileInputStream(filePath), StandardCharsets.UTF_8))) {
            Gson gson = new Gson();
            return gson.fromJson(reader, Notebook.class);
        } catch (IOException e) {
            e.printStackTrace(); // Handle the exception according to your needs
            return null;
        }
    }
}
