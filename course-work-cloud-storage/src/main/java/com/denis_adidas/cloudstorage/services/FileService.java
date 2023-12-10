package com.denis_adidas.cloudstorage.services;

import com.denis_adidas.cloudstorage.mapper.FileMapper;
import com.denis_adidas.cloudstorage.model.File;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.util.List;

@Service
public class FileService {

    private final FileMapper fileMapper;
    private final UserService userService;

    public FileService(FileMapper fileMapper, UserService userService) {
        this.fileMapper = fileMapper;
        this.userService = userService;
    }

    public List<File> getFilesByUser(int userId) {
        return fileMapper.getFilesByUser(userId);
    }

    public File getFileById(int fileId) {
        return fileMapper.getFileById(fileId);
    }

    public boolean addFile(MultipartFile multipartFile, String username) throws IOException {
        int userId = userService.getUser(username).getUserId();

        File file = new File(
                null,
                multipartFile.getOriginalFilename(),
                multipartFile.getContentType(),
                Long.toString(multipartFile.getSize()),
                multipartFile.getBytes(),
                userId
            );
        return fileMapper.insertFile(file) > 0;
    }

    public List<File> getAllFiles() {
        return fileMapper.getAllFiles();
    }

//    public List<File> getSortFiles(String type) {
//
//    }

    public boolean deleteFile(int fileId) {
        File file = fileMapper.getFileById(fileId);
        if (file != null) {
            return fileMapper.deleteFile(fileId) > 0;
        }
        return false;
    }


}
