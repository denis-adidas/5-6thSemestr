package com.denis_adidas.cloudstorage.mapper;

import com.denis_adidas.cloudstorage.model.File;
import org.apache.ibatis.annotations.*;

import java.util.List;

@Mapper
public interface FileMapper {

    @Select("SELECT * FROM FILES WHERE fileId = #{fileId}")
    File getFileById(int fileId);

    @Insert("INSERT INTO FILES (filename, contentType, fileSize, fileData, userId, isDirectory, parentId) VALUES (#{filename}, #{contentType}, #{fileSize}, #{fileData}, #{userId}, #{isDirectory}, #{parentId})")
    @Options(useGeneratedKeys = true, keyProperty = "fileId")
    int insertFile(File file);

    @Delete("DELETE FROM FILES WHERE fileId = #{fileId}")
    int deleteFile(int fileId);

    @Select("SELECT * FROM FILES")
    List<File> getAllFiles();

    @Select("SELECT * FROM FILES WHERE parentId = #{parentId}")
    List<File> getFileByParentId(int parentId);

    @Select("SELECT * FROM FILES WHERE userId = #{userId} AND parentId = 0")
    List<File> getFilesByUser(int userId);

    @Select("SELECT * FROM FILES WHERE userId = #{userId} ORDER BY filename ASC")
    List<File> getFilesByUserSortedByNameAsc(int userId);

    @Select("SELECT * FROM FILES WHERE userId = #{userId} ORDER BY filename DESC")
    List<File> getFilesByUserSortedByNameDesc(int userId);


}
