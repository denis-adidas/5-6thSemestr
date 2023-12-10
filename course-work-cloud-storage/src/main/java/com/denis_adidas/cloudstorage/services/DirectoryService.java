package com.denis_adidas.cloudstorage.services;

import com.denis_adidas.cloudstorage.mapper.DirectoryMapper;
import com.denis_adidas.cloudstorage.model.Directory;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class DirectoryService {
    private final DirectoryMapper directoryMapper;
    private final UserService userService;

    public DirectoryService(DirectoryMapper directoryMapper, UserService userService) {
        this.directoryMapper = directoryMapper;
        this.userService = userService;
    }


    public List<Directory> getDirectoriesByUser(int userId) {
        return directoryMapper.getDirectoriesByUser(userId);
    }

    public Directory getDirectoryById(int directoryId) {
        return directoryMapper.getDirectoryById(directoryId);
    }

    public boolean addDirectory(String directoryName, String username, int parentDirectoryId) {
        int userId = userService.getUser(username).getUserId();

        Directory directory = new Directory(
                null,
                directoryName,
                userId,
                null,
                null
        );

        if (parentDirectoryId != 0) {
            directory.setParentId(parentDirectoryId);
        }

        return directoryMapper.insertDirectory(directory) > 0;
    }

    public List<Directory> getAllDirectories() {
        return directoryMapper.getAllDirectories();
    }


    public boolean deleteDirectory(int directoryId) {
        Directory directory = directoryMapper.getDirectoryById(directoryId);
        if (directory != null) {
            return directoryMapper.deleteDirectory(directoryId) > 0;
        }
        return false;
    }


}


