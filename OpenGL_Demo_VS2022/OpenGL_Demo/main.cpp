#include <iostream>
#include <fstream>
#include <string>

#include <glew.h>
#include <freeglut.h>

#include <Vector_Matrix.h>


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

int CurrentWidth = 700,
CurrentHeight = 700;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4  model_mat_cpp;
int model_mat_location;


enum { Base = 0, LowerArm = 1, UpperArm = 2, NumAngles = 3 };
int Axis = Base;
float Theta[NumAngles] = { 0.0 };

float
znear = 0.1f,
zfar = 100.0f,
fov = 67.0f,
aspect = (float)CurrentWidth / CurrentHeight;

float
cam_speed = 0.05f,
cam_rot_speed = 1.0f,
cam_pos[] = { 0.0f, 0.0f, 3.0f },
cam_x = 0.0f,
cam_y = 0.0f,
cam_z = 0.0f;

mat4
view_mat_cpp,
projection_mat_cpp;

int
view_mat_location,
projection_mat_location;


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

void table0()
{
	mat4 instance = identity_mat4();
	instance = scale(vec3(0.5, 0.1, 0.5));
	mat4 model_table0 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table0.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void table1()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3((-0.5 / 2 + 0.05 / 2), (-0.3 / 2), (0.25 - 0.05 / 2))) * scale(vec3(0.05, 0.3, 0.05));
	mat4 model_table0 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table0.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void table2()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(-(-0.5 / 2 + 0.05 / 2), (-0.3 / 2), (0.25 - 0.05 / 2))) * scale(vec3(0.05, 0.3, 0.05));
	mat4 model_table0 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table0.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void table3()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3((-0.5 / 2 + 0.05 / 2), (-0.3 / 2), -(0.25 - 0.05 / 2))) * scale(vec3(0.05, 0.3, 0.05));
	mat4 model_table0 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table0.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void table4()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(-(-0.5 / 2 + 0.05 / 2), (-0.3 / 2), -(0.25 - 0.05 / 2))) * scale(vec3(0.05, 0.3, 0.05));
	mat4 model_table0 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table0.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chair0(float offset_x,float offset_y)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(offset_x + 0.5,offset_y + 0,0)) * scale(vec3(0.25, 0.05, 0.25));
	mat4 model_table0 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table0.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chair1(float offset_x,float offset_y)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(offset_x + 0.5 + 0.25 / 2 - 0.05 / 2, offset_y + -(0.2 / 2 + 0.05 / 2), 0.25 / 2 - 0.05 / 2)) * scale(vec3(0.05, 0.2, 0.05));
	mat4 model_table0 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table0.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chair2(float offset_x,float offset_y)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(offset_x + 0.5 - (0.25 / 2 - 0.05 / 2), offset_y + -(0.2 / 2 + 0.05 / 2), 0.25 / 2 - 0.05 / 2)) * scale(vec3(0.05, 0.2, 0.05));
	mat4 model_table0 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table0.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chair3(float offset_x,float offset_y)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(offset_x + 0.5 + 0.25 / 2 - 0.05 / 2, offset_y + -(0.2 / 2 + 0.05 / 2), -(0.25 / 2 - 0.05 / 2))) * scale(vec3(0.05, 0.2, 0.05));
	mat4 model_table0 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table0.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chair4(float offset_x, float offset_y)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(offset_x + 0.5 - (0.25 / 2 - 0.05 / 2), offset_y + -(0.2 / 2 + 0.05 / 2), -(0.25 / 2 - 0.05 / 2))) * scale(vec3(0.05, 0.2, 0.05));
	mat4 model_table0 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table0.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//
void chair5(float offset_x ,float offset_y)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(offset_x + 0.5 + 0.25 / 2 - 0.05 / 2, offset_y + (0.2 / 2 + 0.05 / 2), 0.25 / 2 - 0.05 / 2)) * scale(vec3(0.05, 0.2, 0.05));
	mat4 model_table0 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table0.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chair6(float offset_x,float offset_y)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(offset_x + 0.5 + 0.25 / 2 - 0.05 / 2, offset_y + (0.2 / 2 + 0.05 / 2), -(0.25 / 2 - 0.05 / 2))) * scale(vec3(0.05, 0.2, 0.05));
	mat4 model_table0 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table0.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chair7(float offset_x,float offset_y)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(offset_x + 0.5 + 0.25 / 2 - 0.05 / 2, offset_y + (0.2 / 2 + 0.05 / 2),0)) * scale(vec3(0.05, 0.2, 0.05));
	mat4 model_table0 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table0.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chair8(float offset_x, float offset_y)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(offset_x + 0.5 + 0.25 / 2 - 0.05 / 2, offset_y + 0.075 + (0.2 / 2 + 0.05 / 2), 0)) * scale(vec3(0.05, 0.25/2, 0.35));
	mat4 model_table0 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table0.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void a_chair1(float offset_x, float offset_y)
{
	//
	chair0(offset_x, offset_y);
	chair1(offset_x, offset_y);
	chair2(offset_x, offset_y);
	chair3(offset_x, offset_y);
	chair4(offset_x, offset_y);

	//
	chair5(offset_x, offset_y);
	chair6(offset_x, offset_y);
	chair7(offset_x, offset_y);
	//
	chair8(offset_x, offset_y);
	////////////////////////////////
}
void a_chair2(float offset_x, float offset_y)
{
	//
	chair0(offset_x, offset_y);
	chair1(offset_x, offset_y);
	chair2(offset_x, offset_y);
	chair3(offset_x, offset_y);
	chair4(offset_x, offset_y);

	//
	chair5(offset_x - 0.2, offset_y);
	chair6(offset_x - 0.2, offset_y);
	chair7(offset_x - 0.2, offset_y);
	//
	chair8(offset_x - 0.2, offset_y);
	////////////////////////////////
}
// --------------------------------------------------------------------------
void chongchong0()
{
	mat4 instance = identity_mat4();
	instance = scale(vec3(0.05,0.4,0.05));
	mat4 model_chongchong = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chongchong.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chongchong1()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0.4/2 - 0.05/2, 0.2/2 + 0.05/2)) *  scale(vec3(0.05, 0.05, 0.2));
	mat4 model_chongchong = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chongchong.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chongchong2()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0.4 / 2 - 0.05 / 2, 2 * (0.2 / 2 + 0.05 / 2))) * rotate_z(120) * translate(vec3(0,0.25/2,0))* scale(vec3(0.05, 0.25, 0.05));
	mat4 model_chongchong = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chongchong.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void chongchong3()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0.4 / 2 - 0.05 / 2, 2 * (0.2 / 2 + 0.05 / 2))) * rotate_z(-120) * translate(vec3(0, 0.25 / 2, 0)) * scale(vec3(0.05, 0.25, 0.05));
	mat4 model_chongchong = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chongchong.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chongchong4()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0.4 / 2 - 0.05 / 2 , 2 * (0.2 / 2 + 0.05 / 2))) * rotate_z(0) * translate(vec3(0, 0.25 / 2, 0)) * scale(vec3(0.05, 0.25, 0.05));
	mat4 model_chongchong = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chongchong.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void chongchong_full()
{
	chongchong0();
	chongchong1();
	chongchong2();
	chongchong3();
	chongchong4();
}

void DisplayFunc(void)
{
	mat4 T = translate(vec3(-cam_pos[0], -cam_pos[1], -cam_pos[2]));

	/*mat4 R = rotate_x(-cam_x);*/
	mat4 R = rotate_y(-cam_y);

	//mat4 R = rotate_z(-cam_z);

	view_mat_cpp = R * T;
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);

	//
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");

	model_mat_cpp = rotate_y(Theta[Base]);

	table0();
	table1();
	table2();
	table3();
	table4();

	
	a_chair1(0.1,-0.075);
	a_chair2(-1.1, -0.075);



	model_mat_cpp = model_mat_cpp * translate(vec3( - 1.0, 0, 0));

	chongchong_full();
	glutSwapBuffers();
}
// ---------------------------------------------------------------------------	
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
}
// ---------------------------------------------------------------------------	
void IdleFunc(void)
{
	glutPostRedisplay();
}
// ---------------------------------------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		break;
		// dịch theo trục x
	case 'a':
		cam_pos[0] -= cam_speed;
		break;
	case 'A':
		cam_pos[0] -= cam_speed;
		break;

	case 'd':
		cam_pos[0] += cam_speed;
		break;
	case 'D':
		cam_pos[0] += cam_speed;
		break;

		// dịch theo trục z
	case 'w':
		cam_pos[2] -= cam_speed;
		break;
	case 'W':
		cam_pos[2] -= cam_speed;
		break;

	case 's':
		cam_pos[2] += cam_speed;
		break;
	case 'S':
		cam_pos[2] += cam_speed;
		break;

		// quay theo trục x
	case 'x':
		cam_x += cam_rot_speed;
		break;
	case 'X':
		cam_x -= cam_rot_speed;
		break;

		// quay theo trục y
	case 'y':
		cam_y += cam_rot_speed;
		break;
	case 'Y':
		cam_y -= cam_rot_speed;
		break;

		// quay theo trục z
	case 'z':
		cam_z += cam_rot_speed;
		break;
	case 'Z':
		cam_z -= cam_rot_speed;
		break;
	}
}
// ------------------------------------------
void MouseFunc(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Theta[Axis] += 5.0;
		if (Theta[Axis] > 360.0) { Theta[Axis] -= 360.0; }
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		Theta[Axis] -= 5.0;
		if (Theta[Axis] < 0.0) { Theta[Axis] += 360.0; }
	}

	glutPostRedisplay();
}

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
	glutCreateWindow("Robot Arm");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutMouseFunc(MouseFunc);
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