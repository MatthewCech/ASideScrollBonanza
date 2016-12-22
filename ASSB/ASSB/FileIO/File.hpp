/*!***************************************************************************
@file    File.hpp
@author  Reverie Wisp
@par     Email: contact@rw0.pw
@date    11/19/2016

@brief
Lifted from my ASCIIPlayer project, modified for this project.
*****************************************************************************/
#pragma once
#include <string>  // Filepath
#include <vector>  // Storage
#include <fstream> // std FileIO



namespace FileUtil
{
  // Proxy class for subscript operator shenanagins.
  class File;
  class FileProxy
  {
  public:
    FileProxy(unsigned int line, File &f);
		FileProxy(const FileProxy &rhs);
    FileProxy &operator =(std::string str);
    operator std::string() const;
    friend std::ostream& operator<<(std::ostream &os, const FileProxy &f);

  private:
    File &f_;
    const unsigned int line_;

		FileProxy &operator=(const FileProxy &rhs) = delete;
  };


  // The actual file class.
  class File
  {
  public:
    // Read, write, and modify modes.
    enum ModifyMode { Replace = 1, Join = 2 };
    enum FileType { Text = 4, Binary = 8 };

    // Default modes for the flags being passed.
    // Note that the defaults are all the first of two options in enums.
    // This is important for parsing reasons.
    static const int Defaults = Text | Replace;

    // Constructor and Destructor
    File(std::string filepath, int mode = Defaults);
    ~File();

    // Member Functions
    std::string GetLine(unsigned int line) const;
    std::string operator[](unsigned int line) const;
    FileProxy operator[](unsigned int line);
    void Write(const void *data, size_t dataSizeBytes, int line = -1);
    void Write(std::string toWrite, int line = -1, const std::string newlineDelimiter = "\n");
    bool ReRead();
    void Clear();
    bool Save();
    bool SaveAs(std::string newPath, bool override = true);
    void Append(const File &rhs);
    void operator+=(const File &rhs);

    // Friend functions
    friend std::ostream& operator<<(std::ostream &os, File &f);

    // General info functions
    bool         FileFound() const;
    unsigned int GetLineCount() const;
    std::string  GetFileLocation() const;
    std::string  GetFileName() const;
    std::string  GetExtension() const;
    std::vector<std::string> GetContents() const;

  private:
    // Private member functions
    bool readCurrent();
    bool writeChangesToFile(bool writeOver);
    std::string parseFileLocation();
    std::string parseFileName();
    std::string parseExtension();

    // Variables
    std::string              filepath_;          // Constructor provide full filepath.
    FileType                 currentFileType_;   // Text or binary?
    ModifyMode               currentModifyMode_; // Write over or append to lines?
    std::string              fileName_;          // File name as we know it?
    std::string              fileExtension_;     // File extension as we know it?
    std::string              fileLocation_;      // File location as we know it?
    unsigned int             lastModifiedLine_;  // Last line modified when writing to file.
    std::vector<std::string> fileLines_;         // Vector of current lines in file. (1 if bin)
    bool                     foundFile_;         // Was a file found at all when passed?
  };
}
