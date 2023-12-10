package com.denis_adidas.cloudstorage.model;

import lombok.Data;

@Data
public class Credential {
    private Integer credentialId;
    private String url;
    private String username;
    private String key;
    private String password;
    private int userId;

    public Credential(Integer credentialId, String url, String username, String password) {
        this.credentialId = credentialId;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    public Credential() {
    }

    public Credential(Integer credentialId, String url, String username, String key, String password, int userId) {
        this.credentialId = credentialId;
        this.url = url;
        this.username = username;
        this.key = key;
        this.password = password;
        this.userId = userId;
    }

}
