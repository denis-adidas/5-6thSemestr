package com.denis_adidas.cloudstorage.model;

import lombok.Data;

@Data
public class Note {
    private Integer noteId;
    private String noteTitle;
    private String noteDescription;
    private int userId;

    public Note(Integer noteId, String noteTitle, String noteDescription, int userId) {
        this.noteId = noteId;
        this.noteTitle = noteTitle;
        this.noteDescription = noteDescription;
        this.userId = userId;
    }

    public Note() {
    }


}
