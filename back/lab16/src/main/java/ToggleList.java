import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.annotations.Expose;
import com.google.gson.reflect.TypeToken;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileSystems;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ToggleList {
    @Expose
    private Map<String, List<String>> lists;
    private final String filepath;

    public ToggleList(String filepath) {
        this.lists = new HashMap<>();
        this.filepath = filepath;
        loadFromJson();
    }

    public void saveToJson() {
        try (Writer writer = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream(filepath), StandardCharsets.UTF_8))) {
            Gson gson = new GsonBuilder().setPrettyPrinting().create();
            gson.toJson(lists, writer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void loadFromJson() {
        String userDir = FileSystems.getDefault()
                .getPath("")
                .toAbsolutePath()
                .getParent()
                .toString();
        File file = new File(userDir + "/webapps/lab16/autosave.json");
        try (Reader reader = new BufferedReader(new InputStreamReader(
                new FileInputStream(file), StandardCharsets.UTF_8))) {
            Gson gson = new Gson();
            lists = gson.fromJson(reader, new TypeToken<Map<String, List<String>>>() {}.getType());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public Map<String, List<String>> getLists() {
        return lists;
    }
    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();

        for (Map.Entry<String, List<String>> entry : lists.entrySet()) {
            String sectionName = entry.getKey();
            List<String> items = entry.getValue();

            result.append(sectionName).append(":\n");
            for (String item : items) {
                result.append("    ").append(item).append("\n");
            }
        }

        return result.toString();
    }

    public static void main(String[] args) {
        ToggleList tg = new ToggleList("autosave.json");
        for (Map.Entry<String, List<String>> entry : tg.getLists().entrySet()) {
            String sectionName = entry.getKey();
            List<String> items = entry.getValue();

            System.out.println(sectionName + ":");
            for (String item : items) {
                System.out.println("    " + item);
            }
        }
    }
}
