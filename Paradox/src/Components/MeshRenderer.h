#pragma once
#include"Renderer.h"
#include"../graphics/Mesh.h"
namespace Paradox {namespace graphics{
#define MAX_VERTEX_COUNT 3
#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX  1
#define SHADER_NORMAL_INDEX 2
class MeshRenderer : public Renderer
{
	protected :
		bool m_IsBatchRendering; 
	struct MeshData {
		maths::vec3 m_Position; 
		maths::vec2 m_TexCoords; 
		maths::vec3 m_Normals; 
	} *m_BufferMap;

	Mesh* m_Mesh; 
//	Material* m_Material; 
public:
	
	MeshRenderer(Mesh* mesh, bool isBatchRendering);//,Material* material = nullptr);
	MeshRenderer(Mesh* mesh, Shader* shader, bool isBatchRendering);// ,Material* material = nullptr);
	void render(const RenderingEngine& renderingEngine) override; 
	void setBatchRendering(bool isBatchRendering); 
	void SetMesh(Mesh* mesh); 
	auto getMesh() const -> const Mesh&; 
	~MeshRenderer();
protected: 
	void renderMesh(const MeshResource& meshResource);
	void begin() ;
	void submit(const MeshResource& meshResource) ;
	void flush(const MeshResource& meshResource) ;
	void end(); 
	void init(); 
	
};
} }

