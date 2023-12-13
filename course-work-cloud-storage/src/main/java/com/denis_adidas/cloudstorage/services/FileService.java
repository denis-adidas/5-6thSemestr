package com.denis_adidas.cloudstorage.services;

import com.denis_adidas.cloudstorage.mapper.FileMapper;
import com.denis_adidas.cloudstorage.model.File;
import jdk.jfr.Description;
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

    public List<File> getFileByParentId(int parentId) {
        return fileMapper.getFileByParentId(parentId);
    }

    public List<String> getDirectories(int userId) {return fileMapper.getDirectories();}
    public boolean moveFileToDirectory(int fileId, String nameDirectory) {
        File file = fileMapper.getFileById(fileId);
        int newParentId = fileMapper.getFileIdByName(nameDirectory);
        if (file != null) {
            file.setParentId(newParentId);
            return fileMapper.updateFile(file) > 0;
        }
        return false;
    }

    public boolean addFile(MultipartFile multipartFile, Integer parentId, String username) throws IOException {
        int userId = userService.getUser(username).getUserId();

        File file = new File(
                null,
                multipartFile.getOriginalFilename(),
                multipartFile.getContentType(),
                Long.toString(multipartFile.getSize()),
                multipartFile.getBytes(),
                userId,
                parentId
            );
        return fileMapper.insertFile(file) > 0;
    }

    @Description("добавить fileSize = storageUsage")
    public boolean addFileAsDirectory(String username, String directoryName, Integer parentId) throws IOException {
        int userId = userService.getUser(username).getUserId();

        File file = new File(
                null,
                directoryName,
                userId,
                parentId,
                true
        );
        return fileMapper.insertFile(file) > 0;
    }


    public List<File> getAllFiles() {
        return fileMapper.getAllFiles();
    }

    public boolean deleteFile(int fileId) {
        File file = fileMapper.getFileById(fileId);
        if (file != null) {
            fileMapper.deleteFilesWithParentIdNotInFileId();
            return fileMapper.deleteFile(fileId) > 0;
        }
        return false;
    }


}
