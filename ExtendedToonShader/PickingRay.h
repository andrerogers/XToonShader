#include <glm\glm.hpp>

#include "Obj Loader\objLoader.h"

class PickingRay
{
public:
	// Constructor
	PickingRay();

	// Destructor
	~PickingRay();

	// Methods
	bool isRayIntersect(objLoader *model, glm::vec3 *hit);

	inline void setRayStart(glm::vec3 startPos) { rayStart = startPos; }
	inline glm::vec3 getRayStart() { return rayStart; }
	inline void setRayStop(glm::vec3 stopPos) { rayStop = stopPos; }
	inline glm::vec3 getRayStop() { return rayStop; }

private:
	glm::vec3 rayStart;
	glm::vec3 rayStop;
};

