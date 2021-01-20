//
// Created by stiven_perso on 1/19/21.
//

#ifndef SANDBOX_RESSOURCE_PATHS_H
#define SANDBOX_RESSOURCE_PATHS_H
#include <filesystem>
#cmakedefine SHADER_FOLDER std::filesystem::path{"@SHADER_FOLDER@"}
#cmakedefine ASSETS_FOLDER std::filesystem::path{"@ASSETS_FOLDER@"}
#endif //SANDBOX_RESSOURCE_PATHS_H
