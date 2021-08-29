#include "Parser.hpp"

#include <fstream>
#include <iostream>


std::vector<std::unique_ptr<Model>> Parser::parseScene(const char* fileName)
{
    std::vector<std::unique_ptr<Model>> result;
    std::stringstream buffer = Parser::getBuffer(fileName);
    std::string line;
    std::string materialFile;
    // iterates over every model
    while (std::getline(buffer, line))
    {
        std::string             name;
        std::string             material;
        std::string             entry;
        std::vector<int>        vertexIndices;
        std::vector<int>        normalIndices;
        std::vector<int>        textureIndices;
        std::vector<Vector4f>   vertices;
        std::vector<Vector4f>   normals;
        std::vector<Vector4f>   textureCoords;

        std::stringstream lineBuffer;
        lineBuffer << line;
        
        std::getline(lineBuffer, entry, ' ');
        if (entry == "o")
        {
            std::getline(lineBuffer, name, ' ');
            // iterate over every attribute of the model
            while (std::getline(buffer, line))
            {
                std::stringstream attributeBuffer;
                attributeBuffer << line;

                std::string element;
                std::string attributeName;
                std::getline(attributeBuffer, attributeName, ' ');
                if (attributeName == "v" || attributeName == "vn")
                {
                    std::getline(attributeBuffer, element, ' ');
                    float x = std::stof(element);
                    
                    std::getline(attributeBuffer, element, ' ');
                    float y = std::stof(element);

                    std::getline(attributeBuffer, element, ' ');
                    float z = std::stof(element);
                    
                    if (attributeName == "v")
                    {
                        vertices.push_back(Vector4f(x, y, z, 1.f));
                    }
                    else
                    {
                        normals.push_back(Vector4f(x, y, z, 1.f));
                    }
                }
                else if (attributeName == "vt")
                {
                    std::getline(attributeBuffer, element, ' ');
                    float x = std::stof(element);
                    
                    std::getline(attributeBuffer, element, ' ');
                    float y = std::stof(element);
                    
                    textureCoords.push_back(Vector4f(x, y, 0.f, 1.f));
                }
                else if (attributeName == "usemtl")
                {
                    std::getline(attributeBuffer, material, ' ');
                }
                else if (attributeName == "f")
                {
                    std::string index;
                    while (std::getline(attributeBuffer, element, ' '))
                    {
                        std::stringstream indicesBuffer;
                        indicesBuffer << element;
                        std::getline(indicesBuffer, index, '/');
                        int v = std::stoi(index);
                        std::getline(indicesBuffer, index, '/');
                        int t = std::stoi(index);
                        std::getline(indicesBuffer, index, '/');
                        int n = std::stoi(index);
                        vertexIndices.push_back(v - 1);
                        textureIndices.push_back(t - 1);
                        normalIndices.push_back(n - 1);
                    }
                }

                // peek to see if the next row is a new object
                if (buffer.peek() == 'o')
                {
                    break;
                }
            }
            result.push_back(std::make_unique<Model>(vertices, normals, textureCoords, vertexIndices,
                                                     normalIndices, textureIndices));
        }
        else if (entry == "mtllib")
        {
            std::getline(lineBuffer, materialFile, ' ');
        }
    }
    return std::move(result);
}

std::stringstream Parser::getBuffer(const char* fileName)
{
    std::ifstream sceneFile(fileName, std::ifstream::in);
    std::stringstream buffer;
    buffer << sceneFile.rdbuf();
    sceneFile.close();
    return buffer;
}