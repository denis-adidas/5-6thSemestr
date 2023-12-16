package com.denis_adidas.cloudstorage.mapper;

import com.denis_adidas.cloudstorage.model.File;
import org.apache.ibatis.annotations.*;

import java.util.List;

@Mapper
public interface FileMapper {

    @Select("SELECT * FROM FILES WHERE fileId = #{fileId}")
    File getFileById(int fileId);

    @Update("UPDATE files SET filename = #{filename}, contentType = #{contentType}, fileSize = #{fileSize}, fileData = #{fileData}, userId = #{userId}, parentId = #{parentId} WHERE fileId = #{fileId}")
    int updateFile(File file);

    @Insert("INSERT INTO FILES (filename, contentType, fileSize, fileData, userId, isDirectory, parentId) VALUES (#{filename}, #{contentType}, #{fileSize}, #{fileData}, #{userId}, #{isDirectory}, #{parentId})")
    @Options(useGeneratedKeys = true, keyProperty = "fileId")
    int insertFile(File file);

    @Delete("DELETE FROM FILES WHERE fileId = #{fileId}")
    int deleteFile(int fileId);

    @Select("SELECT * FROM FILES")
    List<File> getAllFiles();

    @Select("SELECT * FROM FILES WHERE parentId = #{parentId}")
    List<File> getFileByParentId(int parentId);

//    @Select("SELECT filename FROM FILES WHERE parentId = #{parentId}")
//    Integer getFilenameB
    @Select("SELECT * FROM FILES WHERE userId = #{userId} AND parentId = 0")
    List<File> getFilesByUser(int userId);

    @Select("SELECT * FROM FILES WHERE userId = #{userId} ORDER BY filename ASC")
    List<File> getFilesByUserSortedByNameAsc(int userId);

    @Select("SELECT * FROM FILES WHERE userId = #{userId} ORDER BY filename DESC")
    List<File> getFilesByUserSortedByNameDesc(int userId);

    @Delete("DELETE FROM FILES WHERE parentId != 0 AND parentId NOT IN (SELECT fileId FROM FILES)")
    void deleteFilesWithParentIdNotInFileId();
    @Select("SELECT fileId FROM FILES WHERE filename = #{filename}")
    int getFileIdByName(String filename);
    @Select("SELECT filename FROM FILES WHERE isDirectory = true AND userId = #{userId}")
    List<String> getDirectories(int userId);

    @Select("SELECT userId FROM FILES WHERE fileId = #{fileid}")
    int getUserIdByFileId(int fileId);

}
