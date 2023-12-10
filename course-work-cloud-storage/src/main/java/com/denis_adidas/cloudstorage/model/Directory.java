package com.denis_adidas.cloudstorage.model;

import lombok.Data;

import java.util.List;

@Data
public class Directory {
    private Integer directoryId;
    private String directoryName;
    private int userId;
    private int parentId;
    private List<File> files;
    private List<Directory> directories;

    public Directory() {
    }

    public Directory(Integer directoryId, String directoryName, Integer userId, List<File> files, List<Directory> directories) {
        this.directoryId = directoryId;
        this.directoryName = directoryName;
        this.userId = userId;
        this.files = files;
        this.directories = directories;
    }
}

