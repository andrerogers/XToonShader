#include "Obj Loader\objLoader.h"

class ModelLoader
{
public:
	// Constructor
	ModelLoader(void);

	// Destructor
	~ModelLoader(void);

	void loadModel(const char *fileName);
	void renderModel();

	objLoader *model;
};

