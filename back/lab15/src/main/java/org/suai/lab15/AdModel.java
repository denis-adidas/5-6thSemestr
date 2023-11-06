package org.suai.lab15;

import java.time.LocalDate;
import java.util.Date;

public class AdModel {
    private String title;
    private String text;
    private final String username;
    private final Date date;

    public AdModel(String title, String text, String username) {
        this.title = title;
        this.text = text;
        this.username = username;
        date = new Date();
    }

    public String getTitle() {
        return title;
    }

    public String getText() {
        return text;
    }

    public String getUsername() {
        return username;
    }

    public Date getDate() {
        return date;
    }
}
