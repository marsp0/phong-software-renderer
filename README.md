[![Build](https://github.com/marsp0/software-renderer/actions/workflows/build.yml/badge.svg)](https://github.com/marsp0/software-renderer/actions/workflows/build.yml)

# Software Renderer

Software renderer written from scratch. The goal of the project is for me to be able to better understand the graphics pipeline and what goes under the hood.

## Currently supported features
- Single Threaded Forward Renderer
- Perspective correct attribute interpolation
- Frustum culling
- Backface culling
- Z-Buffer
- Shading models
	- Gouraud Interpolation 
		- Phong reflection
		- BlinnPhong reflection
	- Phong Interpolation 
		- Phong reflection
		- BlinnPhong reflection
	- Metallic workflow (PBR)
	    - Lambertian Diffuse BRDF
	    - Cook-Torrance Specular BRDF
	    - Normal Mapping
- Directional lights

Would like to do
- Different types of texture filtering
- Anti aliasing
- Point lights
- Ambient Occlusion
- Image based lighting
- Gamma Correction

## Build and Run
See the relevant [wiki page](https://github.com/marsp0/software-renderer/wiki/Build).

## References
See the relevant [wiki page](https://github.com/marsp0/software-renderer/wiki/References).
