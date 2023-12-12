package com.denis_adidas.cloudstorage.mapper;

import com.denis_adidas.cloudstorage.model.File;
import com.denis_adidas.cloudstorage.model.User;
import com.denis_adidas.cloudstorage.services.FileService;
import com.denis_adidas.cloudstorage.services.UserService;
import com.denis_adidas.cloudstorage.storageUsage.StorageUsage;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mybatis.spring.boot.test.autoconfigure.MybatisTest;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.jdbc.AutoConfigureTestDatabase;

import java.util.ArrayList;
import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;
import static org.mockito.Mockito.*;

@MybatisTest
@AutoConfigureTestDatabase(replace = AutoConfigureTestDatabase.Replace.NONE)
class FileMapperTest {

    @Autowired
    private FileMapper fileMapper;
    @Autowired
    private UserMapper userMapper;

    @Mock
    private FileService fileService;

    @Mock
    private UserService userService;

    private StorageUsage storageUsage;

    private static User testUser;

    private File testFile;

    @BeforeAll
    static void beforeAll() {
        testUser = new User(null, "johnnydoe", "someSalt", "password", "John", "Doe");
    }

    @BeforeEach
    void setUp() {
        userMapper.createUser(testUser);
        testUser = userMapper.getUser(testUser.getUsername());
        byte[] fileData = new byte[20];
        testFile = new File(null, "somefile.png", "image/png", "32", fileData, testUser.getUserId());
        fileMapper.insertFile(testFile);
    }

    @Test
    void getFileById() {
        File fileById = fileMapper.getFileById(1);
        assertThat(fileById.getFilename()).isEqualTo(testFile.getFilename());
        assertThat(fileById.getFileData()).isEqualTo(testFile.getFileData());
    }


    @Test
    void insertFile() {
        byte[] fileData = new byte[20];
        int created = fileMapper.insertFile(new File(null, "somefile.png", "image/png", "32", fileData, testUser.getUserId()));
        assertThat(created).isGreaterThan(0);
    }

    @Test
    void deleteFile() {
        int deleted = fileMapper.deleteFile(1);
        assertThat(deleted).isGreaterThan(0);
    }

    @Test
    void getAllFiles() {
        List<File> allFiles = fileMapper.getAllFiles();
        assertThat(allFiles).isNotEmpty();

        File file = allFiles.get(0);
        assertThat(file.getContentType()).isEqualTo(testFile.getContentType());
        assertThat(file.getFileSize()).isEqualTo(testFile.getFileSize());
    }

    @Test
    void getFilesByUser() {
        fileMapper.insertFile(testFile);
        List<File> filesByUser = fileMapper.getFilesByUser(1);
        assertThat(filesByUser).isNotEmpty();
        assertThat(filesByUser.size()).isGreaterThan(1);

        File file = filesByUser.get(0);
        assertThat(file).isNotNull();
        assertThat(file.getFilename()).isEqualTo(testFile.getFilename());
        assertThat(file.getFileData()).isEqualTo(testFile.getFileData());
    }
    @Test
    void diskUsage() {
        // Arrange
        int userId = 1;
        String userName = "johnnydoe";
        List<File> files = new ArrayList<>();
        File file1 = new File(null, "file1.txt", "text/plain", "10", new byte[10], userId);
        File file2 = new File(null, "file2.txt", "text/plain", "20", new byte[20], userId);
        files.add(file1);
        files.add(file2);

        when(userService.getUser(userName)).thenReturn(new User(userId, userName, "someSalt", "password", "John", "Doe"));
        when(fileService.getFilesByUser(userId)).thenReturn(files);

        // Act
        String result = storageUsage.diskUsage();

        // Assert
        assertThat(result).isEqualTo("30"); // 10 + 20 = 30
        verify(userService, times(1)).getUser(userName);
        verify(fileService, times(1)).getFilesByUser(userId);
    }
}