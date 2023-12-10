package com.denis_adidas.cloudstorage.services;

import com.denis_adidas.cloudstorage.mapper.DirectoryMapper;
import com.denis_adidas.cloudstorage.model.Directory;
import  com.denis_adidas.cloudstorage.model.User;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.Arrays;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

@SpringBootTest
public class DirectoryServiceTest {

    @Mock
    private DirectoryMapper directoryMapper;

    @Mock
    private UserService userService;

    @InjectMocks
    private DirectoryService directoryService;

    @Test
    public void testGetDirectoriesByUser() {
        // Arrange
        int userId = 1;
        List<Directory> expectedDirectories = Arrays.asList(new Directory(), new Directory());
        Mockito.when(directoryMapper.getDirectoriesByUser(userId)).thenReturn(expectedDirectories);

        // Act
        List<Directory> actualDirectories = directoryService.getDirectoriesByUser(userId);

        // Assert
        assertEquals(expectedDirectories, actualDirectories);
    }

    @Test
    public void testGetDirectoryById() {
        // Arrange
        int directoryId = 1;
        Directory expectedDirectory = new Directory();
        Mockito.when(directoryMapper.getDirectoryById(directoryId)).thenReturn(expectedDirectory);

        // Act
        Directory actualDirectory = directoryService.getDirectoryById(directoryId);

        // Assert
        assertEquals(expectedDirectory, actualDirectory);
    }

    @Test
    public void testAddDirectory() {
        // Arrange
        String directoryName = "TestDirectory";
        String username = "testUser";
        int parentDirectoryId = 2;

        // Mocking userService
        Mockito.when(userService.getUser(username)).thenReturn(new User(1, username, "coWhV4GeOO31xy27tCXx4Q==","password", "John", "Doe"));

        // Act
        boolean result = directoryService.addDirectory(directoryName, username, parentDirectoryId);

        System.out.println(directoryService.getDirectoriesByUser(5).toString());

        // Assert
        assertTrue(result);
    }

    @Test
    public void testGetAllDirectories() {
        // Arrange
        List<Directory> expectedDirectories = Arrays.asList(new Directory(), new Directory());
        Mockito.when(directoryMapper.getAllDirectories()).thenReturn(expectedDirectories);

        // Act
        List<Directory> actualDirectories = directoryService.getAllDirectories();

        // Assert
        assertEquals(expectedDirectories, actualDirectories);
    }

    @Test
    public void testDeleteDirectory() {
        // Arrange
        int directoryId = 1;
        Directory directoryToDelete = new Directory();
        Mockito.when(directoryMapper.getDirectoryById(directoryId)).thenReturn(directoryToDelete);
        Mockito.when(directoryMapper.deleteDirectory(directoryId)).thenReturn(1);

        // Act
        boolean result = directoryService.deleteDirectory(directoryId);

        // Assert
        assertTrue(result);
    }
}
