#include "Storage.hpp"

Storage::Storage() {
    if (!std::filesystem::exists(SAVE_FOLDER))
    {
        /// NOTE: if file save folder isn't available this will create it
        std::filesystem::create_directory(SAVE_FOLDER);
    }
}

/// DESCRIPTION: this method is used for generating name for save files using the time of the save action
std::string Storage::generateFileName() const {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::ostringstream out;
    out <<  SAVE_FOLDER << SAVE_FILE_PREFIX << std::put_time(std::localtime(&time_t), "%Y%m%d%H%M%S") << SAVE_FILE_EXTENSION;
    return out.str();
}

/// DESCRIPTION: this method writes player related data in the save file
void Storage::savePlayerInfo(const Player& p_player,const std::string& path) const {}

/// DESCRIPTION: this method saves constructs a complete save file
void Storage::saveNewGame() {
    if (save_files.size() == MAX_SAVES)
    {
        std::filesystem::remove(save_files.front());
        save_files.pop_front();
    }

    std::string new_file_name = this->generateFileName();
    
    /// TODO: Implement this method
}