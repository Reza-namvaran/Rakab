#include "Storage.hpp"

Storage::Storage() {
    if (!std::filesystem::exists(SAVE_FOLDER))
    {
        std::filesystem::create_directory(SAVE_FOLDER);
    }
}

std::string Storage::generateFileName() const {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::ostringstream out;
    out <<  SAVE_FOLDER << SAVE_FILE_PREFIX << std::put_time(std::localtime(&time_t), "%Y%m%d%H%M%S") << SAVE_FILE_EXTENSION;
    return out.str();
}

void Storage::savePlayerInfo(const Player& p_player,const std::string& path) const {}

void Storage::saveNewGame() {
    if (save_files.size() == MAX_SAVES)
    {
        std::filesystem::remove(save_files.front());
        save_files.pop_front();
    }

    std::string new_file_name = this->generateFileName();
    
    /// TODO: Implement this method
}