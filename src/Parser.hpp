#pragma once

#include <sstream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdint.h>
#include <filesystem>

#include "Model.hpp"
#include "Vector.hpp"
#include "Material.hpp"

namespace parser
{
    std::vector<std::unique_ptr<Model>> parseScene(const std::string& fileName);
    std::unique_ptr<TextureBuffer>      parseTexture(const std::filesystem::path& textureFile);
};