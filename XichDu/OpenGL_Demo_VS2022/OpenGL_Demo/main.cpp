#include <iostream>
#include <fstream>
#include <string>

#include <glew.h>
#include <freeglut.h>
#include<assert.h>
#include <vector_matrix.h>

using namespace std;

typedef struct
{
	float XYZW[4];
	float RGBA[4];
} Vertex;

//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { -0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,   0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,  -0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,   0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },

	// v0-v5-v6 (top)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v6-v1-v0
	{ { -0.5f,	 0.5f,	 -0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v7-v2-v1
	{ { -0.5f,	 -0.5f,	 -0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	 -0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	// v3-v2-v7
	{ { 0.5f,	 -0.5f,	 0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },

	// v4-v7-v6 (back)
	{ { 0.5f,	 -0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	-0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } }
};


const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);

float z = 0;

int CurrentWidth = 700,
CurrentHeight = 700;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4
model_mat_cpp,
null,
view_mat_cpp,
projection_mat_cpp;

int
model_mat_location,
view_mat_location,
projection_mat_location;

float alpha = 0;
float beta = 0;
float t = 0;
float c = 0;
void pillar()
{
	mat4 instance = identity_mat4();
	instance = scale(vec3(0.2, 5, 0.2));
	mat4 model_base = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void floor()
{
	mat4 instance = identity_mat4();
	instance = scale(vec3(2, 0.1, 2));
	mat4 model_base = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void floor1()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, -0.1, 0)) * scale(vec3(1.5, 0.1, 1.5));
	mat4 model_base = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void floor2()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, -0.2, 0)) * scale(vec3(1, 0.1, 1));
	mat4 model_base = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void celling()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0,0.5 + 0.05,0)) * scale(vec3(2, 0.1, 2));
	mat4 model_base = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void celling1()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0.5 + 0.05 + 0.1, 0)) * scale(vec3(1.5, 0.1, 1.5));
	mat4 model_base = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void celling2()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0.5 + 0.05 + 0.1 *2, 0)) * scale(vec3(1, 0.1, 1));
	mat4 model_base = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void cube(vec3 t, vec3 s)
{
	mat4 instance = identity_mat4();
	instance = translate(t) * scale(s);
	mat4 model_base = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void box(vec3 t)
{
	//cube(vec3(0.5/2 - 0.1/2, 0, 0.5 / 2 - 0.1/2), vec3(0.5, 0.2, 0.1));

	cube(vec3(0 + t.x , t.y + 0, t.z), vec3(0.5, 0.5, 0.1));


	cube(vec3(t.x + 0.5/2 - 0.1 / 2 , t.y + 0 , t.z + 0.5/2 ),vec3(0.1, 0.5, 0.5));
	cube(vec3(t.x + -(0.5 / 2 - 0.1 / 2) , t.y + 0 , t.z + 0.5 / 2 ), vec3(0.1, 0.5, 0.5));
	cube(vec3(t.x + (0.5 / 2 - 0.1 / 2) - 0.1 , t.y + -0.5/2 + 0.2/2 , t.z + 0.5 / 2), vec3(0.2, 0.2, 0.5));



	//model_mat_cpp = model_mat_cpp * translate(c);

	
}
void cua(vec3 t)
{
	cube(vec3(t.x + -(0.5 / 2 - 0.1 / 2), t.y + 0, t.z + 0.5 / 2 + 0.1 * 2), vec3(0.1, 0.5, 0.1));
	cube(vec3(t.x  + 0.5/2 + 0.1/2, t.y + 0, t.z + 0.5 / 2 + 0.1 * 2), vec3(0.1, 0.5, 0.1));

	cube(vec3(t.x + 0, t.y + 0, t.z + 0.5 - 0.1 / 2), vec3(0.5, 0.1, 0.1));
	cube(vec3(t.x + 0, t.y + 0.5 / 2 - 0.1 / 2, t.z + 0.5 - 0.1 / 2), vec3(0.5, 0.1, 0.1));
	cube(vec3(t.x + 0, t.y + -(0.5 / 2 - 0.1 / 2), t.z + 0.5 - 0.1 / 2), vec3(0.5, 0.1, 0.1));
}
void cua1(vec3 t)
{
	cube(vec3(t.x + -(0.5 / 2 - 0.1 / 2), t.y + 0, t.z + 0.5 / 2 + 0.1 / 2 - 0.5 / 2), vec3(0.1, 0.5, 0.1));
	cube(vec3(t.x + (0.5 / 2 - 0.1 / 2), t.y + 0, t.z + 0.5 / 2 + 0.1 / 2 - 0.5 / 2), vec3(0.1, 0.5, 0.1));

	cube(vec3(t.x + 0, t.y + 0, t.z + 0 + 0.1 / 2), vec3(0.5, 0.1, 0.1));
	cube(vec3(t.x + 0, t.y + 0.5 / 2 - 0.1 / 2, t.z + 0 + 0.1 / 2), vec3(0.5, 0.1, 0.1));
	cube(vec3(t.x + 0, t.y + -(0.5 / 2 - 0.1 / 2), t.z + 0 + 0.1 / 2), vec3(0.5, 0.1, 0.1));
}
void cua2(vec3 t)
{
	cube(vec3(t.x + -(0.5 / 2 - 0.1 / 2), t.y + 0, t.z + 0.5 / 2 + 0.5 / 2 - 0.05), vec3(0.1, 0.5, 0.1));
	cube(vec3(t.x + -(0.5 / 2 - 0.1 / 2), t.y + 0, t.z ), vec3(0.1, 0.5, 0.1));

	cube(vec3(t.x + -(0.5 / 2 - 0.1 / 2), t.y + 0, t.z + 0.5 / 2), vec3(0.1, 0.1, 0.5));
	cube(vec3(t.x + -(0.5 / 2 - 0.1 / 2), t.y + 0.5 / 2 - 0.1 / 2, t.z + 0.5 / 2), vec3(0.1, 0.1, 0.5));
	cube(vec3(t.x + -(0.5 / 2 - 0.1 / 2), t.y + -(0.5 / 2 - 0.1 / 2), t.z + 0.5 / 2), vec3(0.1, 0.1, 0.5));
}
void cua3(vec3 t)
{
	cube(vec3(t.x + (0.5 / 2 - 0.1 / 2), t.y + 0, t.z + 0.5 / 2 + 0.5 / 2 - 0.05), vec3(0.1, 0.5, 0.1));
	cube(vec3(t.x + (0.5 / 2 - 0.1 / 2), t.y + 0, t.z), vec3(0.1, 0.5, 0.1));

	cube(vec3(t.x + 0.5 / 2 - 0.1 / 2, t.y + 0, t.z + 0.5 / 2), vec3(0.1, 0.1, 0.5));
	cube(vec3(t.x + 0.5 / 2 - 0.1 / 2, t.y + 0.5 / 2 - 0.1 / 2, t.z + 0.5 / 2), vec3(0.1, 0.1, 0.5));
	cube(vec3(t.x + 0.5 / 2 - 0.1 / 2, t.y + -(0.5 / 2 - 0.1 / 2), t.z + 0.5 / 2), vec3(0.1, 0.1, 0.5));
}
void box1(vec3 t)
{
	//vec3(t.x + 0, t.y + 0, t.z + 0.5 - 0.1 / 2)
	//cube(vec3(0.5/2 - 0.1/2, 0, 0.5 / 2 - 0.1/2), vec3(0.5, 0.2, 0.1));

	cube(vec3(t.x + 0, t.y + 0, t.z + 0.5 - 0.1 / 2), vec3(0.5, 0.5, 0.1));


	cube(vec3(t.x + 0.5 / 2 - 0.1 / 2, t.y + 0, t.z + 0.5 / 2), vec3(0.1, 0.5, 0.5));
	cube(vec3(t.x + -(0.5 / 2 - 0.1 / 2), t.y + 0, t.z + 0.5 / 2), vec3(0.1, 0.5, 0.5));

	cube(vec3(t.x + -((0.5 / 2 - 0.1 / 2) - 0.1), t.y + -0.5 / 2 + 0.2 / 2, t.z + 0.5 / 2), vec3(0.2, 0.2, 0.5));



	//model_mat_cpp = model_mat_cpp * translate(c);

	
}
void box2(vec3 t)
{
	//vec3(t.x + 0, t.y + 0, t.z + 0.5 - 0.1 / 2)
	//cube(vec3(0.5/2 - 0.1/2, 0, 0.5 / 2 - 0.1/2), vec3(0.5, 0.2, 0.1));

	cube(vec3(t.x + 0, t.y + 0, t.z + 0.5 - 0.1 / 2), vec3(0.5, 0.5, 0.1));


	cube(vec3(t.x + 0.5 / 2 - 0.1 / 2, t.y + 0, t.z + 0.5 / 2), vec3(0.1, 0.5, 0.5));
	//--------------------------------matphai
	//cube(vec3(t.x + -(0.5 / 2 - 0.1 / 2), t.y + 0, t.z + 0.5 / 2), vec3(0.1, 0.5, 0.5));

	//------------------ghe
	cube(vec3(t.x + 0 , t.y + -0.5 / 2 + 0.2 / 2, t.z + ((0.5 / 2 - 0.1 / 2) + 0.1)), vec3(0.5, 0.2, 0.2));



	//model_mat_cpp = model_mat_cpp * translate(c);
	//------------------------------------------------------------------------------------------------------- mat sau
	cube(vec3(t.x + 0, t.y + 0, t.z + 0), vec3(0.5, 0.5, 0.1));
	//-------------------------------------------------------------cua
	
	//-------------------------------------------------------------------------------------------------------
}
void box3(vec3 t)
{


	cube(vec3(t.x + 0, t.y + 0, t.z + 0.5 - 0.1 / 2), vec3(0.5, 0.5, 0.1));

	//-----------trai
	//cube(vec3(t.x + -(0.5 / 2 - 0.1 / 2), t.y + 0, t.z + 0.5 / 2), vec3(0.1, 0.5, 0.5));
	//--------------------------------matphai
	cube(vec3(t.x + -(0.5 / 2 - 0.1 / 2), t.y + 0, t.z + 0.5 / 2), vec3(0.1, 0.5, 0.5));

	//------------------ghe
	cube(vec3(t.x + 0, t.y + -0.5 / 2 + 0.2 / 2, t.z + 0.2/2 + 0.1/2), vec3(0.5, 0.2, 0.2));



	//model_mat_cpp = model_mat_cpp * translate(c);
	//------------------------------------------------------------------------------------------------------- mat sau
	cube(vec3(t.x + 0, t.y + 0, t.z + 0), vec3(0.5, 0.5, 0.1));
	//-------------------------------------------------------------cua
	
	//-------------------------------------------------------------------------------------------------------
	//vec3(t.x + -(0.5 / 2 - 0.1 / 2), t.y + 0.5 / 2 - 0.1 / 2, t.z + 0.5 / 2)
}



// ---------------------------------------------------------------------------	
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}
// ---------------------------------------------------------------------------	
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
// ---------------------------------------------------------------------------	
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ---------------------------------------------------------------------------	
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
// ------------------------------------------


// ---------------------------------------------------------------------------	
void DisplayFunc(void)
{
	// Các tham số của hàm lookat
	vec3	eye(-1.0f, 0.7f, 2.0f),
		at(0.0f, 0.0f, 0.0f),
		up(0.0f, 1.0f, 0.0f);

	view_mat_cpp = lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	//Bo sung 7 dong ben duoi
	float znear = 1.0f,
		zfar = 100.0f,
		fov = 67.0f,
		aspect = (float)CurrentWidth / CurrentHeight;
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model_mat_cpp = null;
	pillar();

	model_mat_cpp = translate(vec3(0,t,0)) * rotate_y(z);
	
	floor();
	floor1();
	floor2();
	celling();
	celling1();
	celling2();

	box(vec3(0, 0.5/2 + 0.05, 0.4));
	box1(vec3(0, 0.5 / 2 + 0.05, - 0.4 - 0.5));
	box2(vec3(-0.1 -0.5, 0.5 / 2 + 0.05, -0.2));
	box3(vec3(0.1 + 0.5, 0.5 / 2 + 0.05, -0.2));

	mat4 temp = model_mat_cpp;
	model_mat_cpp = temp * translate(vec3(c, 0, 0));
	cua(vec3(0, 0.5 / 2 + 0.05, 0.4));

	model_mat_cpp = temp * translate(vec3(-c, 0, 0));
	cua1(vec3(0, 0.5 / 2 + 0.05, -0.4 - 0.5));

	model_mat_cpp = temp * translate(vec3(0, 0, c));
	cua2(vec3(-0.1 - 0.5, 0.5 / 2 + 0.05, -0.2));

	model_mat_cpp = temp * translate(vec3(0, 0, -c));
	cua3(vec3(0.1 + 0.5, 0.5 / 2 + 0.05, -0.2));

	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	glutSwapBuffers();
}
// ---------------------------------------------------------------------------	
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight); //Bo sung day nua
}
// ---------------------------------------------------------------------------	
void IdleFunc(void)
{
	// thiết lập cờ gọi hiển thị lại
	glutPostRedisplay();
}
// ---------------------------------------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(EXIT_SUCCESS); break;
	case 'z':
		if (z >= 360 || z <= -360)
		{
			z = 0;
		}
		z += 5;
		break;
	case 'Z':
		if (z >= 360 || z <= -360)
		{
			z = 0;
		}
		z -= 5; break;

	case 't':
		t += 0.05; break;
	case 'T':
		t -= 0.05; break;
	case 'c':
		c += 0.05; break;
	case 'C':
		c -= 0.05; break;
	}
}
// ------------------------------------------

// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Wheel");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();
	return 0;
}
// --------------------------------------
bool CompileShader(GLuint shaderID) {
	cout << "Compiling shader" << shaderID << "..." << endl;
	glCompileShader(shaderID);
	int result = -1;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		cout << "Shader " << shaderID << " compile failed" << endl;
		int maxLength = 2048;
		int realLength = 0;
		char log[2048];
		glGetShaderInfoLog(shaderID, maxLength, &realLength, log);
		cout << log << endl;
		return false;
	}
	cout << "Shader " << shaderID << " compile successful" << endl;
	return true;
}