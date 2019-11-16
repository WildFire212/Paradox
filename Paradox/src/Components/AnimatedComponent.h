#pragma once
#include"../graphics/MeshLoaders/AnimatedModelLoader/Bone.h"
#include"../maths/maths.h"
#include<vector>
#include<assimp/scene.h>
#include<assimp/anim.h>
#include<string>
#include"../graphics/MeshLoaders/AnimatedModelLoader/AnimatedModel.h"
#include"Renderer.h"
#include"../core/Time.h"
using namespace Paradox::maths;

namespace Paradox {
	namespace graphics {
#define MAX_VERTEX_COUNT 5000
#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX  1
#define SHADER_NORMAL_INDEX 2
#define SHADER_BONEID1_INDEX 3
#define SHADER_BONEID2_INDEX 4
#define SHADER_BONEID3_INDEX 5
#define SHADER_BONEID4_INDEX 6

class AnimatedComponent :public  Renderer
{
private: 
	struct MeshData {
		vec3 m_Position;
		vec2 m_TexCoords;
		vec3 m_Normals;
		vec2 m_BoneData1; 
		vec2 m_BoneData2; 
		vec2 m_BoneData3; 
		vec2 m_BoneData4; 

	} *m_BufferMap;



	mat4 m_GlobalInverseTransform; 
	std::vector<Bone*> m_Bones; 
	std::vector<mat4> m_BoneTransforms; 
	aiNode*  m_Root; 
	aiAnimation* m_Animation; 
	AnimatedModel* m_AnimatedModel;
	 double timer; 
public:
	AnimatedComponent(AnimatedModel* animatedModel,Shader* shader);
	
	~AnimatedComponent();

	void init(); 
	void renderAnimatedModel(const MeshResource& meshResource);
	void begin();
	void submit(const MeshResource& meshResource);
	void flush(const MeshResource& meshResource);
	void end();
	

	void update(float delta) override; 
	void render(const RenderingEngine& engine) override;
	

	void readNodeHeirarchy(float animationTime, const aiNode* node, mat4 parentTransform);
	void boneTransforms(double timeInSeconds); 

	
	auto findNodeAnim(const aiAnimation* animation, std::string nodeName) -> const aiNodeAnim*;
	 auto findBone(std::string name) -> Bone*; 

	 auto calcInterpolatedScaling(float animationTime, const aiNodeAnim * nodeAnim) -> vec3;
	 auto calcInterpolatedPosition (float animationTime , const aiNodeAnim* nodeAnim) -> vec3;
	 auto calcInterpolatedRotation( float animationTime, const aiNodeAnim * nodeAnim) -> quaternion;


	 auto findScaling(float animationTime , const aiNodeAnim * nodeAnim ) -> int;
	 auto findRotation(float animationTime , const aiNodeAnim * nodeAnim ) -> int;
	 auto findPosition(float animationTime , const aiNodeAnim * nodeAnim ) -> int;

	 void setAnimatedModel(AnimatedModel* animatedModel); 
	 auto getAnimatedModel() const -> const AnimatedModel&; 

};

}}
