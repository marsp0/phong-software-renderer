namespace Math {

// TODO (Martin): vector3 should have 3 components instead of 4. when dealing with 
// transformations we can extract required info from input vector and create
// a local 4d vector

	class Vector3 {

		public:
			
			Vector3(float x, float y, float z, float w);
			Vector3();

			float x;
			float y;
			float z;
			float w;
	};
};