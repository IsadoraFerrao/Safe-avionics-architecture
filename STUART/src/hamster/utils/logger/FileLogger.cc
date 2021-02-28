#include "FileLogger.h"
#include "Logger.h"

namespace hamster {
namespace utils {
namespace logger{

FileLogger::FileLogger() : file_stream(new std::ofstream) {
}

FileLogger::~FileLogger() {
    if (this->file_stream) {
        this->closeOStream();
    }
}

void FileLogger::openOStream(const std::string& name) {
    this->file_stream->open(name.c_str(), std::ios_base::binary | std::ios_base::out);
    if (!this->file_stream->is_open()) {
        throw (std::runtime_error("LOGGER: Unable to open an output stream"));
    }
}

void FileLogger::closeOStream() {
    if (this->file_stream) {
        this->file_stream->close();
    }
}

void FileLogger::write(const std::string& msg) {
    (* this->file_stream) << msg << std::endl;
    this->file_stream->flush();
}

} /* namespace logger */
} /* namespace utils */
} /* namespace hamster */

