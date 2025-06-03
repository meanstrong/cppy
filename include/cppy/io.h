#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "cppy/exception.h"
#include "cppy/internal/declare.h"

// 基础流类
class CPPY_API CPPY_IO_IOBase {
protected:
  bool _closed;

public:
    CPPY_IO_IOBase();
  virtual ~CPPY_IO_IOBase() = default;

  bool closed() const;
  virtual void close();

  // 检查流是否已关闭
  void _check_closed() const;
};

// 文本流基类
class CPPY_API CPPY_IO_TextIOBase : public CPPY_IO_IOBase {
public:
  virtual CPPY_ERROR_t read(std::string* const result, size_t size = -1) = 0;
  virtual CPPY_ERROR_t readline(std::string* const result, size_t size = -1) = 0;
  virtual CPPY_ERROR_t readlines(std::vector<std::string>* const result) = 0;
  virtual void write(const std::string &s) = 0;
  virtual void writelines(const std::vector<std::string> &lines) = 0;
};

// 内存文本流
class CPPY_API CPPY_IO_StringIO : public CPPY_IO_TextIOBase {
private:
  std::stringstream _stream;
  bool _readable;
  bool _writable;

public:
    CPPY_IO_StringIO(const std::string& initial_value = "", bool readable = true,
        bool writable = true);

    CPPY_ERROR_t read(std::string* const result, size_t size = -1) override;

    CPPY_ERROR_t readline(std::string* const result, size_t size = -1) override;

    CPPY_ERROR_t readlines(std::vector<std::string>* const result) override;

    void write(const std::string& s) override;

    void writelines(const std::vector<std::string>& lines) override;

    std::string getvalue() const;
};

// 文件流
class CPPY_API CPPY_IO_FileIO : public CPPY_IO_TextIOBase {
private:
  std::fstream _file;
  std::string _mode;

public:
    CPPY_IO_FileIO(const std::string& filename, const std::string& mode = "r");

    ~CPPY_IO_FileIO() override;

    void close() override;

    CPPY_ERROR_t read(std::string* const result, size_t size = -1) override;

    CPPY_ERROR_t readline(std::string* const result, size_t size = -1) override;

    CPPY_ERROR_t readlines(std::vector<std::string>* const result) override;

    void write(const std::string& s) override;

    void writelines(const std::vector<std::string>& lines) override;
};

// 二进制流基类
class CPPY_API CPPY_IO_BufferedIOBase : public CPPY_IO_IOBase {
public:
  virtual CPPY_ERROR_t read(std::vector<char>* const result, size_t size = -1) = 0;
  virtual void write(const std::vector<char> &data) = 0;
};

// 内存二进制流
class CPPY_API CPPY_IO_BytesIO : public CPPY_IO_BufferedIOBase {
private:
  std::vector<char> _buffer;
  size_t _position;
  bool _readable;
  bool _writable;

public:
    CPPY_IO_BytesIO(const std::vector<char>& initial_bytes = {}, bool readable = true,
        bool writable = true);

    CPPY_ERROR_t read(std::vector<char>* const result, size_t size = -1) override;

    void write(const std::vector<char>& data) override;

    std::vector<char> getvalue() const;
};
