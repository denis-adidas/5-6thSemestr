package org.example.test;

import org.example.NotebookModel;
import org.junit.Before;
import org.junit.Test;

import java.util.List;

import static org.junit.Assert.*;

public class NotebookModelTest {
    private NotebookModel notebook;

    @Before
    public void setUp() {
        notebook = new NotebookModel();
    }

    @Test
    public void testAddPerson() {
        notebook.addPerson("Alice");
        assertEquals(3, notebook.getPersons().size());
        assertEquals("Alice", notebook.getPersons().get(2).getName());
    }

    @Test
    public void testAddPersonNumber() {
        notebook.addPersonNumber("Vasya", "123");
        List<String> numbers = notebook.getPersons().get(0).getNumbers();
        assertTrue(numbers.contains("123"));
    }

    // Add more tests for other methods...

    @Test
    public void testSerializationDeserialization() {
        // Create a Notebook object
        NotebookModel originalNotebook = new NotebookModel();
        originalNotebook.addPerson("Alice");
        originalNotebook.addPersonNumber("Alice", "123");

        // Serialize to JSON
        originalNotebook.saveToJsonFile("autosave.json");

        // Deserialize from JSON
        NotebookModel deserializedNotebook = NotebookModel.loadFromJsonFile("autosave.json");

        // Check if the deserialized object is equal to the original
        assertEquals(originalNotebook.getNamesStrings().length, deserializedNotebook.getNamesStrings().length);
        assertEquals(originalNotebook.getNamesStrings()[0], deserializedNotebook.getNamesStrings()[0]);
        assertEquals(originalNotebook.getPersons().get(0).getNumbers(), deserializedNotebook.getPersons().get(0).getNumbers());
    }

    // Add more tests as needed...

}
