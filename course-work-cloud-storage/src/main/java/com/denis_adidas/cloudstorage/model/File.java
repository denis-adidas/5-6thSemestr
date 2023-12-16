package com.denis_adidas.cloudstorage.model;

import lombok.Data;

@Data
public class File {
    private Integer fileId;
    private String filename;
    private String contentType;
    private String fileSize;
    private byte[] fileData;
    private int userId;
    private boolean isDirectory;
    private int parentId;

    public File() {
    }

    public File(Integer fileId, String filename, String contentType, String fileSize, byte[] fileData, Integer userId, Integer parentId) {
        this.fileId = fileId;
        this.filename = filename;
        this.contentType = contentType;
        this.fileSize = fileSize;
        this.fileData = fileData;
        this.userId = userId;
        this.parentId = parentId;
    }
    public File(Integer fileId, String filename, Integer userId, Integer parentId, Boolean isDirectory) {
        this.fileId = fileId;
        this.filename = filename;
        this.userId = userId;
        this.parentId = parentId;
        this.isDirectory = isDirectory;
    }


}
