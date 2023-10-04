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
    public void PersonToString() {
        notebook.addPerson("Denis");
        notebook.addPersonNumber("Denis", "+79876436110");
        notebook.addPersonNumber("Denis", "+79173305836");
        assertEquals("Name: Denis; Numbers: [+79876436110, +79173305836]", notebook.getPersons().get(2).toString());
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
        assertEquals(originalNotebook.getPersons().size(), deserializedNotebook.getPersons().size());
        assertEquals(originalNotebook.getPersons().get(0).getName(), deserializedNotebook.getPersons().get(0).getName());
        assertEquals(originalNotebook.getPersons().get(0).getNumbers(), deserializedNotebook.getPersons().get(0).getNumbers());
    }

    // Add more tests as needed...

}
