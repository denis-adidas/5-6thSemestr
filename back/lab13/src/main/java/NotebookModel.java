
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;
import jdk.jfr.Description;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class NotebookModel {

    public class Person {

        @SerializedName("numbers")
        @Expose
        private ArrayList<String> numbers;
        @SerializedName("name")
        @Expose
        private final String name;
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
        @Override
        public String toString() {
            StringBuilder str = new StringBuilder();
            str.append("Name: ").append(name).append("; ");
            str.append("Numbers: ").append(numbers.toString());
            return str.toString();
        }
    }
    private ArrayList<Person> persons = new ArrayList<Person>();
    public NotebookModel() {
        getPersons().add(new Person("Vasya"));
        getPersons().add(new Person("Kolya"));
    }

    public ArrayList<Person> getPersons() {
        return persons;
    }

    public synchronized void addPerson(String name) {
        boolean personExists = false;
        for (Person x : getPersons()) {
            if (x.getName().equals(name)) {
                personExists = true;
                break;
            }
        }

        if (!personExists) {
            Person newPerson = new Person(name);
            getPersons().add(newPerson);
        }
    }

    public synchronized void addPersonNumber(String name, String number) {
        addPerson(name);
        for (Person x : getPersons())
            if (x.getName().equals(name))
                x.addNumber(number);
    }
    public synchronized void removePersonNumber(String name, String number) {
        getPersons().get(getPersons().indexOf(name)).removeNumber(number);
    }

    public synchronized void reset() {
        getPersons().clear();
    }
    public void saveToJsonFile(String filePath) {
        try (Writer writer = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream(filePath), StandardCharsets.UTF_8))) {
            Gson gson = new GsonBuilder().setPrettyPrinting().create();
            gson.toJson(this, writer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static NotebookModel loadFromJsonFile(String filePath) {
        try (Reader reader = new BufferedReader(new InputStreamReader(
                new FileInputStream(filePath), StandardCharsets.UTF_8))) {
            Gson gson = new Gson();
            return gson.fromJson(reader, NotebookModel.class);
        } catch (IOException e) {
            e.printStackTrace(); // Handle the exception according to your needs
            return null;
        }
    }
}
