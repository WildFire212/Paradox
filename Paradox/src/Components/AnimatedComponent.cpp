#include "AnimatedComponent.h"
#include"../core/GameObject.h"
#include"glm.hpp"
namespace Paradox {
	namespace graphics {

AnimatedComponent::AnimatedComponent(AnimatedModel* animatedModel,Shader* shader): Renderer(shader)
{
	m_Root = animatedModel->getScene()->mRootNode;
	m_Bones = animatedModel->getBones(); 
	//adding vertices and indices
	m_Animation = animatedModel->getScene()->mAnimations[0];
	m_AnimatedModel = animatedModel;
	 m_GlobalInverseTransform = animatedModel->getGlobalInverseTransform();
	
	m_BoneTransforms = std::vector<mat4> (m_Bones.size());
	//timer = Time::getTime() /(double) Time::SECONDS; 
	timer = 0; 
	init(); 

}

void AnimatedComponent::init() {
	m_VAO->bind();
	m_VBO->bind();
	m_VBO->bufferData(NULL, 6000000, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glEnableVertexAttribArray(SHADER_NORMAL_INDEX);
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);
	glEnableVertexAttribArray(SHADER_BONEID1_INDEX);
	glEnableVertexAttribArray(SHADER_BONEID2_INDEX);
	glEnableVertexAttribArray(SHADER_BONEID3_INDEX);
	glEnableVertexAttribArray(SHADER_BONEID4_INDEX);



	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, 16 *sizeof(GLfloat), (const GLvoid*)0);
	glVertexAttribPointer(SHADER_COLOR_INDEX, 2,  GL_FLOAT, GL_FALSE, 16* sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, 16 *sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));
	glVertexAttribPointer(SHADER_BONEID1_INDEX,2, GL_FLOAT, GL_FALSE, 16 *sizeof(GLfloat), (const GLvoid*)(8 * sizeof(GLfloat)));
	glVertexAttribPointer(SHADER_BONEID2_INDEX,2, GL_FLOAT, GL_FALSE, 16* sizeof(GLfloat), (const GLvoid*)( 10* sizeof(GLfloat)));
	glVertexAttribPointer(SHADER_BONEID3_INDEX,2, GL_FLOAT, GL_FALSE, 16* sizeof(GLfloat), (const GLvoid*)( 12* sizeof(GLfloat)));
	glVertexAttribPointer(SHADER_BONEID4_INDEX,2, GL_FLOAT, GL_FALSE, 16* sizeof(GLfloat), (const GLvoid*)( 14* sizeof(GLfloat)));
	


	m_VBO->unbind();


	m_VAO->unbind();
}

void Paradox::graphics::AnimatedComponent::renderAnimatedModel(const MeshResource & animatedModel)
{

	begin();
	submit(animatedModel);
	end();

	flush(animatedModel);
}

void AnimatedComponent::begin() {
	m_VBO->bind();
	m_BufferMap = (MeshData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void Paradox::graphics::AnimatedComponent::submit(const MeshResource & meshResource)
{
	m_VAO->bind();
	//FileUtils::convertToArray(meshResource.getIndices())
	m_IBO->bufferData(meshResource.getIndices().data(), meshResource.getIndexCount(), GL_DYNAMIC_DRAW); //new ElementBuffer(&meshResource.getIndices()[0], meshResource.getIndexCount());//cannot create object every time 	

	m_VAO->unbind();
	std::vector<GLfloat> vertices = meshResource.getVertices();		//main Problem file utils 
	std::vector<GLfloat> normals = meshResource.getNormals();
	std::vector<GLfloat> texCoords = meshResource.getTexCoords();
	std::vector<glm::vec<4, BoneData>> boneData= m_AnimatedModel->getBoneData(); 

	for (int i = 0; i < meshResource.getVertexCount() / 3; i++)
	{
		m_BufferMap->m_Position = maths::vec3(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
		m_BufferMap->m_TexCoords = maths::vec2(texCoords[i * 2], texCoords[i * 2 + 1]);
		m_BufferMap->m_Normals = maths::vec3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]);
		m_BufferMap->m_BoneData1 = maths::vec2(boneData[i].x.boneID , boneData[i].x.weight);
		m_BufferMap->m_BoneData2 = maths::vec2(boneData[i].y.boneID,  boneData[i].y.weight);
		m_BufferMap->m_BoneData3 = maths::vec2(boneData[i].z.boneID,  boneData[i].z.weight);
		m_BufferMap->m_BoneData4 = maths::vec2(boneData[i].w.boneID,  boneData[i].w.weight);
		m_BufferMap++;
		
	}
}

void Paradox::graphics::AnimatedComponent::flush(const MeshResource& meshResource)
{
	m_VAO->bind();
	m_IBO->bind();
	glDrawElements(GL_TRIANGLES, meshResource.getIndexCount(), GL_UNSIGNED_SHORT, 0);
	m_IBO->unbind();
	m_VAO->unbind();
}

void Paradox::graphics::AnimatedComponent::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void AnimatedComponent::update(float delta)
{
		//boneTransforms((float)((double))
	//double timer2 = Time::getTime() / (double)Time::SECONDS; 
	//double de = timer2 - timer; 
	timer += delta; 
	boneTransforms((timer ));

}



void AnimatedComponent::render(const RenderingEngine & engine)
{
	m_Shader->bind(); 
	this->m_Parent->getTransform()->setRotation(quaternion(-0.7f, 0.0f, 0.0f, 1.0f));
	for (size_t i = 0; i < m_BoneTransforms.size(); i++)
	{
		m_Shader->SetUniformMat4(std::string("gBones[" + std::to_string(i) + "]").c_str(), m_BoneTransforms[i]);
	}

	m_Shader->updateAllUniforms(this->m_Parent->getTransform(), &engine, &m_AnimatedModel->getMeshResource().getMaterial()); //mesh->getMaterial; 
	renderAnimatedModel(m_AnimatedModel->getMeshResource());
	m_Shader->unbind(); 
}

void AnimatedComponent::readNodeHeirarchy(float animationTime,const aiNode * node, const mat4 parentTransform)
{
	std::string nodeName = node->mName.data; 
	const aiAnimation* animation = m_AnimatedModel->getScene()->mAnimations[0];

	mat4 nodeTransformation= maths::mat4::aIMatrix4x4ToMat4(node->mTransformation); 
	const aiNodeAnim* nodeAnim = findNodeAnim(m_Animation, nodeName);

	if (nodeAnim != nullptr)
	{
		// Interpolate scaling and generate scaling transformation matrix
		
		vec3 Scaling =  calcInterpolatedScaling( animationTime, nodeAnim); 
		mat4 scaleMatrix =mat4::Scale(Scaling);

		// Interpolate rotation and generate rotation transformation matrix
		quaternion rotation =	calcInterpolatedRotation(animationTime, nodeAnim); 
		mat4 rotationMatrix = mat4::Rotate(rotation); 
		
		// Interpolate translation and generate translation transformation matrix
		
		vec3 Translate = 	calcInterpolatedPosition( animationTime, nodeAnim);
		mat4 translateMatrix = mat4::Translate(Translate);

		//combine transformations....
		nodeTransformation = translateMatrix * rotationMatrix * scaleMatrix ;
	}

	mat4 GlobalTransformation = parentTransform * nodeTransformation; 

	Bone* bone =  findBone(nodeName);

	if ( bone != nullptr)
	{
		bone->m_FinalTransformation = m_GlobalInverseTransform * GlobalTransformation * bone->m_OffsetMatrix;	
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		readNodeHeirarchy(animationTime, node->mChildren[i], GlobalTransformation);
	}
}

void AnimatedComponent::boneTransforms(double timeInSeconds)
{
	mat4 Identity = mat4::Identity(); 

	float TickPerSecond = (float)(m_Animation->mTicksPerSecond != 0.0f ? m_Animation->mTicksPerSecond : 25.0f);
	//float TickPerSecond = 0.0f;
	double TimeInTicks = timeInSeconds * TickPerSecond;
	float AnimationTime = fmod(TimeInTicks, m_AnimatedModel->getScene()->mAnimations[0]->mDuration);

	readNodeHeirarchy(AnimationTime, m_Root, Identity);
	
	
	for (size_t i = 0; i < m_Bones.size(); i++)
	{
		m_BoneTransforms[i] = m_Bones[i]->m_FinalTransformation ; 
	}

}

const aiNodeAnim* AnimatedComponent::findNodeAnim(const aiAnimation * animation, std::string nodeName)
{
	for (size_t i = 0; i < animation->mNumChannels; i++)
	{
		const aiNodeAnim* nodeAnim = animation->mChannels[i]; 
		if (nodeAnim->mNodeName.data == nodeName)
		{
			return nodeAnim; 
		}		
	}		
			return nullptr; 
}

 Bone* AnimatedComponent::findBone(std::string name)
{
	for (std::vector<Bone*>::iterator it = m_Bones.begin(); it!= m_Bones.end(); ++it)
	{
		if ((*it)->m_Name == name)
		{
			return *it; 
		}

	}
	return nullptr; 
}

 vec3 AnimatedComponent::calcInterpolatedScaling( float animationTime, const aiNodeAnim * nodeAnim)
 {
	 
	 if (nodeAnim->mNumScalingKeys == 1)
	 {
		 aiVector3D value = nodeAnim->mScalingKeys[0].mValue;
		 return vec3(value.x, value.y, value.z);
		 
	 }

	 int scalingIndex = findScaling(animationTime, nodeAnim);
	 int nextScalingIndex = (scalingIndex + 1);
	 assert(nextScalingIndex < nodeAnim->mNumScalingKeys);

	 float deltaTime = (float)(nodeAnim->mScalingKeys[nextScalingIndex].mTime - nodeAnim->mScalingKeys[scalingIndex].mTime);
	 float factor = (animationTime - (float)nodeAnim->mScalingKeys[scalingIndex].mTime) / deltaTime;
	 assert(factor >= 0.0f && factor <= 1.0f);

	 //end and start scaling 
	 aiVector3D temp = nodeAnim->mScalingKeys[scalingIndex].mValue;
	 vec3 start = vec3(temp.x, temp.y, temp.z);
	 temp = nodeAnim->mScalingKeys[nextScalingIndex].mValue;
	 vec3 end = vec3(temp.x, temp.y, temp.z);
	 vec3 delta = end - start;

	 return start + factor * delta;

 }

 vec3 AnimatedComponent::calcInterpolatedPosition(float animationTime, const aiNodeAnim * nodeAnim)
 {	
	 if (nodeAnim->mNumPositionKeys == 1)
	 {
        aiVector3D value= nodeAnim->mPositionKeys[0].mValue; 
		return vec3(value.x, value.y, value.z); 

	}
	 int positionIndex = findPosition(animationTime, nodeAnim); 
	 int nextPositionIndex = positionIndex + 1; 
	 assert(nextPositionIndex < nodeAnim->mNumPositionKeys); 
	 float deltaTime = (float)(nodeAnim->mPositionKeys[nextPositionIndex].mTime - nodeAnim->mPositionKeys[positionIndex].mTime);
	 float factor = (animationTime - (float)nodeAnim->mPositionKeys[positionIndex].mTime) / deltaTime;

	 assert(factor >= 0.0f && factor <= 1.0f); 

	 //start and end 
	 aiVector3D temp = nodeAnim->mPositionKeys[positionIndex].mValue;
	 vec3 start =vec3(temp.x , temp.y , temp.z); 
	 temp = nodeAnim->mPositionKeys[nextPositionIndex].mValue; 
	 vec3 end = vec3(temp.x, temp.y , temp.z); 
	 vec3 delta = end - start;
	 return start + factor * delta; 


 }

 quaternion AnimatedComponent::calcInterpolatedRotation(float animationTime, const aiNodeAnim * nodeAnim)
 {
	 //atleast two values to interpolate
	 if (nodeAnim->mNumRotationKeys == 1) {
		 aiQuaternion value= nodeAnim->mRotationKeys[0].mValue; 
		return quaternion(value.x, value.y, value.z, value.w); 

	 }
	 
	 int rotationIndex = findRotation(animationTime, nodeAnim); 
	 int nextRotationIndex = (rotationIndex + 1); 
	 assert(nextRotationIndex < nodeAnim->mNumRotationKeys); 
	 float deltaTime = (float)(nodeAnim->mRotationKeys[nextRotationIndex].mTime - nodeAnim->mRotationKeys[rotationIndex].mTime);
	 float factor = (animationTime - ((float)nodeAnim->mRotationKeys[rotationIndex].mTime ))/ deltaTime; 
	 assert(factor >= 0.0f && factor <= 1.0f); 


	 //start and end 
	 aiQuaternion temp = nodeAnim->mRotationKeys[rotationIndex].mValue;
	 quaternion start = quaternion(temp.x, temp.y, temp.z,temp.w);
	 temp = nodeAnim->mRotationKeys[nextRotationIndex].mValue;
	 quaternion end = quaternion(temp.x, temp.y, temp.z,temp.w);
	
	// return start.Nlerp(end, factor, false); 
	//return start.Slerp(end, factor, false); 
	 return quaternion::nlerp(start, end, factor);
 }

 int AnimatedComponent::findScaling(float animationTime, const aiNodeAnim * nodeAnim)
 {
	 assert(nodeAnim->mNumScalingKeys > 0);
	 for (size_t i = 0; i < nodeAnim->mNumScalingKeys - 1; i++)
	 {
		 if (animationTime < (float)nodeAnim->mScalingKeys[i + 1].mTime)
			 return i; 
	 }
	 assert(0);
	 return 0;
 }

 int AnimatedComponent::findRotation(float animationTime, const aiNodeAnim * nodeAnim)
 {
	 assert(nodeAnim->mNumRotationKeys > 0);
		 for (size_t i = 0; i < nodeAnim->mNumRotationKeys  - 1; i++)
		 {
			 if (animationTime < (float)nodeAnim->mRotationKeys[i + 1].mTime)
				 return  i; 
		 }
		 assert(0);
		 return 0;
 }

 int AnimatedComponent::findPosition(float animationTime, const aiNodeAnim * nodeAnim)
 {
	 assert(nodeAnim->mNumPositionKeys > 0);
	 for (size_t i = 0; i < nodeAnim->mNumPositionKeys - 1; i++)
	 {
		 if (animationTime < (float)nodeAnim->mPositionKeys[i + 1].mTime)
			 return i; 
	 }
	 assert(0);
	 return 0; 
 }

 void AnimatedComponent::setAnimatedModel(AnimatedModel * animatedModel)
 {
	 m_AnimatedModel = animatedModel; 
 }

 const AnimatedModel & AnimatedComponent::getAnimatedModel() const
 {
	 return *m_AnimatedModel; 
 }

 AnimatedComponent::~AnimatedComponent()
{
}

} }
