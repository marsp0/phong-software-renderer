#pragma once

// Note: this "system" will probably be rewritten at a later stage as i 
// do not know 100% how it will work with all the different shaders.
// If materials get too big we can use some form of manager that holds all instead 
// of having them in the model (this should also be done for textures as they are currently loaded multiple times)

struct Material
{
    #if !PBR_SHADER

        std::unique_ptr<TextureBuffer> diffuseTexture;
        float ambient;
        float diffuse;
        float specular;
        float shininess;

    #else

        std::unique_ptr<TextureBuffer> albedoTexture;
        std::unique_ptr<TextureBuffer> metallicTexture;
        std::unique_ptr<TextureBuffer> roughnessTexture;
        std::unique_ptr<TextureBuffer> normalTexture;

    #endif
};