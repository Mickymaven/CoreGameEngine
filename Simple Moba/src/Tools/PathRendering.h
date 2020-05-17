#if !defined(PATHRENDERING_H)
#define PATHRENDERING_H

#include <vector>
using std::vector;

#include "../../../EngineGameModuleDirectX9/src/Application/GlobalsDX9.h"//todo bad?

#include "../../../EngineGameModuleDirectX9/src/Graphics/LMMesh.h"
#include "../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../EngineGameModel/src/Base/Sprite.h"
#include "../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"

enum PathRenderOption
{ 
	pathRenderOptionAll,
	pathRenderOptionPath,
	pathRenderOptionPathOptimised,
	pathRenderOptionCount
};

class PathRendering
{

protected:
	static Sprite * nodeSprite;
	static SpriteView * nodeSpriteView;
	static LMVector3 * nodeSpritePosition;

	static Sprite * nodePath;
	static SpriteView * nodePathView;
	static LMVector3 * nodePathPosition;
	static LMVector3 * nodePathRotation;

	static Sprite * nodePathOptimised;
	static SpriteView * nodePathOptimisedView;
	static LMVector3 * nodePathOptimisedPosition;
	static LMVector3 * nodePathOptimisedRotation;

	PhysicsObject * nodePhysics;


	LMMesh m_pathMesh;
	LMMesh m_pathMeshOptimised;

	LMMesh m_nodeMesh;


public:
	PathRendering();
	~PathRendering();

	void RenderNodes(vector<LMVector3 *> * nodes);
	void RenderPaths(vector<vector<LMVector3 *>*> * paths, PathRenderOption option);
	void RenderPathWithPositions(LMVector3 * origin, LMVector3 * target, PathRenderOption option);
	

};

#endif