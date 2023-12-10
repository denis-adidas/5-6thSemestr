package com.denis_adidas.cloudstorage.mapper;

import com.denis_adidas.cloudstorage.model.Directory;
import org.apache.ibatis.annotations.*;

import java.util.List;

@Mapper
public interface DirectoryMapper {

    @Select("SELECT * FROM DIRECTORIES WHERE directoryId = #{directoryId}")
    Directory getDirectoryById(int directoryId);

    @Insert("INSERT INTO DIRECTORIES (directoryName, userId, parentId) VALUES (#{directoryName}, #{userId}, #{parentId})")
    @Options(useGeneratedKeys = true, keyProperty = "directoryId")
    int insertDirectory(Directory directory);

    @Delete("DELETE FROM DIRECTORIES WHERE directoryId = #{directoryId}")
    int deleteDirectory(int directoryId);

    @Select("SELECT * FROM DIRECTORIES")
    List<Directory> getAllDirectories();

    @Select("SELECT * FROM DIRECTORIES WHERE userId = #{userId}")
    List<Directory> getDirectoriesByUser(int userId);

    @Select("SELECT * FROM DIRECTORIES WHERE parentId = #{parentId}")
    List<Directory> getDirectoriesByParent(int parentId);
}
