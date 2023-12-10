package com.denis_adidas.cloudstorage.controller;

import com.denis_adidas.cloudstorage.model.Credential;
import com.denis_adidas.cloudstorage.model.File;
import com.denis_adidas.cloudstorage.model.Note;
import com.denis_adidas.cloudstorage.services.CredentialService;
import com.denis_adidas.cloudstorage.services.FileService;
import com.denis_adidas.cloudstorage.services.NoteService;
import com.denis_adidas.cloudstorage.services.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletResponse;
import javax.validation.Valid;
import java.io.IOException;
import java.util.List;

@Controller
@RequestMapping("/files")
public class FileController {

    private final FileService fileService;
    private final NoteService noteService;
    private final CredentialService credentialService;
    private final UserService userService;

    @Autowired
    public FileController(
            FileService fileService,
            NoteService noteService,
            CredentialService credentialService,
            UserService userService
    ) {
        this.fileService = fileService;
        this.noteService = noteService;
        this.credentialService = credentialService;
        this.userService = userService;
    }

    @GetMapping()
    public String index(Model model, Authentication authentication) {
        int userId = userService.getUser(authentication.getName()).getUserId();

        List<File> files = fileService.getFilesByUser(userId);
        List<Note> notes = noteService.getNoteByUser(userId);
        List<Credential> credentials = credentialService.getCredentialsByUser(userId);

        model.addAttribute("files", files);
        model.addAttribute("notes", notes);
        model.addAttribute("credentials", credentials);

        return "files/index";
    }

    @PostMapping
    public ModelAndView fileUpload(@RequestParam("fileUpload") MultipartFile file, Authentication auth) {
        ModelAndView result = new ModelAndView();
        String status = null;

        try {
            if(fileService.addFile(file, auth.getName())) {
                result.addObject("success", true);
                status = "File uploaded successfully.";
            }
        } catch (IOException ex) {
            result.addObject("errorMsg", true);
            status = "Unable to upload file.";
        }
        result.setViewName("result");
        result.addObject("message", status);
        return result;
    }


    @GetMapping("/delete/{fileId}")
    public ModelAndView deleteFile(@PathVariable int fileId) {
        ModelAndView result = new ModelAndView();
        String status = "";

        if (fileService.deleteFile(fileId)) {
            result.addObject("success", true);
            status = "File deleted";
        } else {
            result.addObject("errorMsg", true);
            status = "Unable to delete file";
        }

        result.setViewName("result");
        result.addObject("message", status);
        return result;
    }

    @GetMapping("/download/{fileId}")
    public void downloadFile(@PathVariable int fileId, HttpServletResponse response) throws IOException {
        File file = fileService.getFileById(fileId);

        response.setContentType(file.getContentType());
        response.setContentLength(Integer.parseInt(file.getFileSize()));
        String headerValue = "file:" + file.getFilename();
        response.setHeader("Content-Disposition", headerValue);
        response.getOutputStream().write(file.getFileData());
        response.flushBuffer();
    }
}
