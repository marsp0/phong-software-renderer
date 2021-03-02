#include <SDL2/SDL.h>

class DisplayManager {
	public:
		
		DisplayManager(int width, int height);
		void Initialize();
		void SwapBuffers();
		void ShutDown();

		int width;
		int height;

	private:

		SDL_Window *window;
};