package com.denis_adidas.cloudstorage.storageUsage;

import com.denis_adidas.cloudstorage.model.File;
import com.denis_adidas.cloudstorage.services.FileService;
import com.denis_adidas.cloudstorage.services.UserService;

import java.util.List;

public class StorageUsage {
    private String userName;
    private long usageSpace;
    private final FileService fileService;
    private final UserService userService;

    public StorageUsage(int userName, FileService fileService, UserService userService) {
        this.fileService = fileService;
        this.userService = userService;
    }

    public String diskUsage() {
        int userId = userService.getUser(userName).getUserId();
        List<File> files = fileService.getFilesByUser(userId);
        for (var x : files) {
            usageSpace += Long.parseLong(x.getFileSize());
        }
        return Long.toString(usageSpace);
    }
}
