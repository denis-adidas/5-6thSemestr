package com.denis_adidas.cloudstorage.controller;

import com.denis_adidas.cloudstorage.model.Credential;
import com.denis_adidas.cloudstorage.model.File;
import com.denis_adidas.cloudstorage.model.Note;
import com.denis_adidas.cloudstorage.services.CredentialService;
import com.denis_adidas.cloudstorage.services.FileService;
import com.denis_adidas.cloudstorage.services.NoteService;
import com.denis_adidas.cloudstorage.services.UserService;
import org.springframework.security.core.Authentication;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;

import java.util.List;

@Controller
public class HomeController {

    private final CredentialService credentialService;
    private final FileService fileService;
    private final NoteService noteService;
    private final UserService userService;
    private String username;


    public HomeController(CredentialService credentialService, FileService fileService, NoteService noteService, UserService userService) {
        this.credentialService = credentialService;
        this.fileService = fileService;
        this.noteService = noteService;
        this.userService = userService;
    }

    @RequestMapping("/home")
    public String getHomeView(Authentication authentication, Credential credential, Note note, File file, Model model) {
        int userId = userService.getUser(authentication.getName()).getUserId();
        username = authentication.getName();
        List<String> directories = fileService.getDirectories(userId);
        directories.remove("home");

        model.addAttribute("files", fileService.getFilesByUser(userId));
        model.addAttribute("notes", noteService.getNoteByUser(userId));
        model.addAttribute("credentials", credentialService.getCredentialsByUser(userId));
        model.addAttribute("directories", directories);
        model.addAttribute("currentUser", authentication.getName());
        model.addAttribute("usageSpace", fileService.diskUsage(userId));

        return "home";
    }
    @GetMapping("/fileDetails/{fileId}")
    public String getFileDetails(@PathVariable int fileId, Model model) {
        int userId = fileService.getUserIdByFileId(fileId);

        String currentPath = fileService.getCurrentPath(fileId);
        String shareLink = fileService.shareLinkFile(fileId);

        List<String> directories = fileService.getDirectories(userId);
        directories.remove(fileService.getFileById(fileId).getFilename());

        File file = fileService.getFileById(fileId);


        if (file != null && file.isDirectory()) {
            model.addAttribute("files", fileService.getFileByParentId(fileId));
            model.addAttribute("parentId", fileId);
            model.addAttribute("currentPath", currentPath);
            model.addAttribute("directories", directories);
            model.addAttribute("currentUser", username);
            model.addAttribute("shareLink", shareLink);
            return "fileDetails";
        } else {
            return "home";
        }
    }

    @GetMapping("/share/fileDetails/{fileId}")
    public String getSharedFileDetails(@PathVariable int fileId, Model model) {
        int userId = fileService.getUserIdByFileId(fileId);

        List<String> directories = fileService.getDirectories(userId);
        directories.remove(fileService.getFileById(fileId).getFilename());

        File file = fileService.getFileById(fileId);


        if (file != null && file.isDirectory()) {
            model.addAttribute("files", fileService.getFileByParentId(fileId));
            model.addAttribute("directories", directories);
            return "share";
        } else {
            return "home";
        }
    }
}

