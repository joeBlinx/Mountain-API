//
// Created by stiven_perso on 1/19/21.
//

#ifndef SANDBOX_SHADER_FOLDER_H
#define SANDBOX_SHADER_FOLDER_H
#include <filesystem>
#cmakedefine SHADER_FOLDER std::filesystem::path{"@SHADER_FOLDER@"}
#cmakedefine ASSETS_FOLDER std::filesystem::path{"@ASSETS_FOLDER@"}
#endif //SANDBOX_SHADER_FOLDER_H
