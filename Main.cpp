#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <Vector_Matrix.h>
#include<ctime>//Lấy thời gian hiện tại

using namespace std;
//Thêm tam giác màu
static const float coloredTriangle[] = {
	//position			//colors
	 1.0, -1.0,  0.0,	1.0, 0.5, 0.0,//bottom right
	-1.0, -1.0,  0.0,	0.0, 1.0, 0.0,//bottom left
	 0.0,  1.0,  0.0,	0.0, 0.3, 1.0//top
};
typedef struct
{
	float xyzw[4];

	float normal[4];
} Vertex;

Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ { -0.5f,	 0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 0.5, 0 } },
	{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 0.5, 0 } },
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0, 0, 0.5, 0 } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 1, 0, 0.2, 0 } },
	{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1, 0, 0.2, 0 } },
	{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 1, 0, 0.2, 0 } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,   0.5f, 1.0 },{ 1, 0, 0, 0 } },

	// v0-v5-v6 (top)
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	// v6-v1-v0
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ -1, 0, 0.7, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ -1, 0, 0.7, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ -1, 0, 0.7, 0 } },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	// v3-v2-v7
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0.1, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0.1, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0,-1, 0.1, 0 } },

	// v4-v7-v6 (back)
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } }
};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t NormalOffset = sizeof(Vertices[0].xyzw);

// Định nghĩa stack cho ma trận
class MatrixStack {
	int    index;
	int    size;
	mat4* matrices;

	public:
		MatrixStack(int numMatrices = 32) :index(0), size(numMatrices)
		{
			matrices = new mat4[numMatrices];
		}

		~MatrixStack()
		{
			delete[]matrices;
		}

		mat4& push(const mat4& m) {
			assert(index + 1 < size);
			matrices[index++] = m;
			return matrices[index];
		}

		mat4& pop(void) {
			assert(index - 1 >= 0);
			index--;
			return matrices[index];
		}
};

MatrixStack  mvstack;

int CurrentWidth = 700,
CurrentHeight = 700;

GLuint
VaoId[2],
VboId[2],
VertexShaderId,
FragmentShaderId,
ProgramId;

GLfloat yf = 0, xf = 0;

mat4
model_mat_cpp,
view_mat_cpp,
projection_mat_cpp;

int
model_mat_location,
view_mat_location,
projection_mat_location;

// Ma trận Xoay, Tỉ lệ, Tịnh tiến
float
R[] = { 0.0f, 0.0f, 0.0f },
S[] = { 1.0f, 1.0f, 1.0f },
T[] = { 0.0f, 0.0f, 0.0f };
//=============Sử dụng cho Camera============
int midWindowX;
int midWindowY;


bool keys[256]; // 256 kí tự trong bảng chữ cái
bool mouseLocked = true;
float beta = 0.0f;
float pitch = 0.0f;
float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 5.0f;
float moveSpeed = 0.5f;
float jumpSpeed = 0.4f;
float gravity = 0.010f;
bool isJumping = false;
bool isGrounded = true;

//--------------------------------------------------Dùng kiểm tra tịnh tiến, quay, co giãn--------------------------------------------------
bool is_translated = false,
is_rotated = false,
is_scaled = false;

float Alpha = 0.0f;


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
// ------------------------------------------
void CreatVaoVbo()
{
	glGenVertexArrays(2, &VaoId[0]);
	glGenBuffers(2, &VboId[0]);
	glBindVertexArray(VaoId[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coloredTriangle), coloredTriangle, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0); // Bật vertex_position
	glEnableVertexAttribArray(1); // Bật vertex_color
	glBindVertexArray(VaoId[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, (void*)0);
	// Layout location 2 cho vertex_normal
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset);

	// Bật thuộc tính đỉnh
	glEnableVertexAttribArray(0); // Bật vertex_position
	glEnableVertexAttribArray(2); // Bật vertex_normal

	// Bật kiểm tra độ sâu và ẩn con trỏ chuột
	glEnable(GL_DEPTH_TEST);
	glutSetCursor(GLUT_CURSOR_NONE);
}
// ------------------------------------------
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
// ------------------------------------------
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId[0]);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId[0]);
}
//--------------------------------------------------Ánh sáng--------------------------------------------------
#pragma region light
bool light1 = true, light2 = true;

void updateLightUniforms() {
	//light1 = 1; light2 = 1;
	glUniform1i(glGetUniformLocation(ProgramId, "enable_light_1"), light1 ? 0 : 1);
	glUniform1i(glGetUniformLocation(ProgramId, "enable_light_2"), light2 ? 1 : 0);
}

void onl1() {
	light1 = true;
	updateLightUniforms();
}

void offl1() {
	light1 = false;
	updateLightUniforms();
}


// ************************************Gọi màu trong vs.shader************************************
void setInt(const string& name, int value) {
	glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), value);
}
//-----------Tạo khối hộp cube đơn vị--------
void cube()
{
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();
	mat4 model_cube = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_cube.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
}
//-------------------------------

void ground() {
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, -1.05, -3.5)) * scale(vec3(60.0, 0.01, 40.0));
	setInt("color", 5);
	cube();
	model_mat_cpp = mvstack.pop();
}

void sky()
{
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, 50.0, -25.0)) * scale(vec3(200.0, 0.01, 200.0));
	setInt("color", 16);
	cube();
	model_mat_cpp = mvstack.pop();
}

// Hàng rào 
namespace hangrao {
	void veCot(float x, float y, float z, float width, float height, float depth) {
		mvstack.push(model_mat_cpp);
		// Màu sắc cột hàng rào (màu gỗ)
		setInt("color", 10);  // Giả sử màu số 10 là màu gỗ

		mat4 instance = identity_mat4();
		// Dịch chuyển tới vị trí cần vẽ
		instance = translate(vec3(x, y, z)) *
			scale(vec3(width, height, depth)); // Kích thước cột

		mat4 model_column = model_mat_cpp * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_column.m);

		// Vẽ cột (giả sử sử dụng một hình hộp)
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}
	void veThanhNgang(float x, float y, float z, float width, float height, float depth) {
		mvstack.push(model_mat_cpp);

		// Màu sắc thanh ngang (màu gỗ)
		setInt("color", 10);

		mat4 instance = identity_mat4();
		// Dịch chuyển tới vị trí cần vẽ
		instance = translate(vec3(x, y/2, z)) *
			scale(vec3(width, height, depth)); // Kích thước thanh ngang

		mat4 model_bar = model_mat_cpp * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bar.m);

		// Vẽ thanh ngang (giả sử sử dụng hình hộp)
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}
	void veHangRao(float startX, float startY, float startZ, float spacing, int numColumns,
		float columnWidth, float columnHeight, float columnDepth,
		float barWidth, float barHeight, float barDepth) {
		
		// Vẽ các cột	
		for (int i = 0; i < numColumns; ++i) {
			float x = startX + i * spacing;
			veCot(x, startY, startZ, columnWidth, columnHeight, columnDepth);
		}
		// Vẽ thanh ngang nối các cột
		for (int i = 1; i < numColumns - 2; ++i) {

			float x = startX + i * spacing + spacing / 2.0f;
			float z = startZ;  
			veThanhNgang(x, -0.8+startY + columnHeight / 2.0f, z, barWidth, barHeight, barDepth);
			veThanhNgang(x, -0.8+startY - columnHeight / 2.0f, z, barWidth, barHeight, barDepth);
		}
	}
}


//Các thông số để mở cửa nhà VS
float door_angle = 0.0f, toilet_angle = -90.0f, water_angle = 0.0f;
bool is_rotating = true;
namespace toilet {
	void tuong(float x, float y, float z, float width, float height, float depth) {
		mvstack.push(model_mat_cpp);
		setInt("color", 01); 

		mat4 instance = identity_mat4();
		instance = translate(vec3(x, y, z)) *scale(vec3(width, height, depth)); 

		mat4 model_column = model_mat_cpp * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_column.m);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		model_mat_cpp = mvstack.pop();
	}
	void canhcua() {
		mvstack.push(model_mat_cpp);
		setInt("color", 98);
		model_mat_cpp = model_mat_cpp
			* translate(vec3(4, -0.2, 4.4))
			* rotate_y(door_angle)
			* translate(vec3(-0.5, 0, 0)) // Đưa cửa về vị trí ban đầu
			* scale(vec3(1, 2, 0.05));        // Thay đổi kích thước cửa

		cube();  // Vẽ cánh cửa
		model_mat_cpp = mvstack.pop();
	}
	void vetuong() {
		tuong(5, -0.2, 5, 0.05, 2, 1.2); //Trai
		tuong(4, -0.2, 5, 0.05, 2, 1.2); //Phai
		tuong(4 + 0.5, -0.2, 5 + 0.6, 1, 2, 0.05); //Sau
		tuong(4 + 0.5, 0.8, 5, 1, 0.05, 1.2); //Tren
		canhcua();
		
	}
	void toilet(float x, float y, float z, float width, float height, float depth, int id_color) {
		mvstack.push(model_mat_cpp);
		setInt("color", id_color);

		mat4 instance = identity_mat4();
		instance = translate(vec3(x, y, z)) * scale(vec3(width, height, depth));

		mat4 model_column = model_mat_cpp * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_column.m);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		model_mat_cpp = mvstack.pop();
	}
	void naptoilet() {
		mvstack.push(model_mat_cpp);
		setInt("color", 10);
		model_mat_cpp = model_mat_cpp
			* translate(vec3(4+0.5, -0.8, 4.9))
			* rotate_x(toilet_angle)
			* translate(vec3(0, 0, 0.2)) // Đưa cửa về vị trí ban đầu (0,0,0) cx dc ma nhi :)))
			* scale(vec3(0.5, 0.05, 0.25));        // Thay đổi kích thước cửa

		cube();
		model_mat_cpp = mvstack.pop();
	}
	void xanuoc() {
		mvstack.push(model_mat_cpp);
		setInt("color", 16);
		model_mat_cpp = model_mat_cpp
			* translate(vec3(4.5, -0.9, 4.9))            // Đặt vị trí ban đầu
			* rotate_y(water_angle)                      // Xoay nước theo góc hiện tại
			* translate(vec3(0, 0, 0))                 // Đưa nước ra xa tâm xoay
			* scale(vec3(0.1, 0.03, 0.1));              // Thay đổi kích thước nước
		cube(); 
		model_mat_cpp = mvstack.pop();
	}

	//Hàm điểu chỉnh tốc độ quay của nước
	void updateWaterAngle(float deltaTime) {
		if (is_rotating) { 
			water_angle += 360.0f * deltaTime; // Xoay nước, tốc độ xoay là 360 độ mỗi giây
			if (water_angle >= 360.0f) {
				water_angle -= 360.0f; // Giữ góc quay trong khoảng [0, 360]
			}
		}
	}
	void vetoilet() {
		toilet(4 + 0.5, -0.75, 5, 0.5, 0.5, 0.1, 98); //Cái sau
		toilet(4.76, -1, 4.95, 0.03, 0.3, 0.25, 04); //Cái dưới phải
		toilet(4.24, -1, 4.95, 0.03, 0.3, 0.25, 04); //Cái dưới Trái
		toilet(4.5, -1, 4.84, 0.5, 0.3, 0.03, 04); //Thanh chắn trước
		naptoilet();
		xanuoc();
	}
	
}

//Quầy kem
float alpha3 = 180.0f;
namespace quaykem {
	void wall_left_right() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.1, 2.5, 4.0));
		setInt("color", 1);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void wall_back() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(3.05, 2.5, 0.1));
		setInt("color", 1);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void wall_top() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(3.05, 0.1, 4));
		setInt("color", 1);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void tam_chan() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp *scale(vec3(1.5, 0.9, 0.02));
		setInt("color", 14);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void bien_hieu() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(3.05, 0.6, 0.02));
		setInt("color", 4);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void canh_cua() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(1.5, 2.1, 0.02));
		setInt("color", 7);
		cube();
		model_mat_cpp = mvstack.pop();
	}


	void thanh_ngan_cach() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.05, 2, 0.02));
		setInt("color", 03);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	// Hàm LED ánh sáng với chuyển động lên xuống
	void led_light(float time) {
		mvstack.push(model_mat_cpp);

		// Tạo hiệu ứng chuyển động LED lên xuống
		float offset = sin(time * 10.0f) * 0.15f; // Chuyển động theo trục Y (biên độ 1.0)
		model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, offset, 0.0f)) * scale(vec3(0.05, 0.05, 0.05));
		setInt("color", 16); // Màu đèn LED
		cube();

		mvstack.pop();
	}

	// Hàm chuỗi đèn LED quanh biển hiệu
	void led_chain(float time) {
		for (float x = -1.75; x <= 0.2; x += 0.3) {
			mvstack.push(model_mat_cpp);
			model_mat_cpp = model_mat_cpp * translate(vec3(-1.5, x, -0.03)); // Đặt LED ngay trước biển hiệu
			led_light(time); // Hiển thị đèn LED với hiệu ứng
			model_mat_cpp = mvstack.pop();
		}
	}

	void quay_kem(float time) {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(1.5, 0, 0));
		wall_left_right(); //Tuong trai
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-1.5, 0, 0));
		wall_left_right(); //Tuong phai
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, 0, 2.0));
		wall_back(); //Tuong sau
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, 2.5/2, 0));
		wall_top(); //Tuong tren
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, 0.95, -2));
		bien_hieu(); //Bien hieu
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0.75, -0.6, -2));
		tam_chan(); //Tam chan
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-1.52, 0, -2)) * rotate_y(alpha3) * translate(vec3(-1.5/2, 0, 0));
		canh_cua(); //Canh cua
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, 0, -2));
		thanh_ngan_cach(); //Thanh ngăn cách giữa cửa và chỗ bán
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, 0.95, -2));
		led_chain(time);
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(3.0, 0.95, -2));
		led_chain(time);
		model_mat_cpp = mvstack.pop();

	}
}

//Đồng hồ BigBag
namespace dongho {
	void thanhdoc() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.02, 2.0, 0.02));
		setInt("color", 16);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void thanhdoctren() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.02, 0.9, 0.02));
		setInt("color", 16);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void thanhdoctrencung() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.02, 0.29, 0.02));
		setInt("color", 16);
		cube();
		model_mat_cpp = mvstack.pop();
	}
	void thancot() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(1.5, 5.0, 1));
		setInt("color", 5);
		cube();
		model_mat_cpp = mvstack.pop();
	}
	void matdongho() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(1.6, 1.5, 0.05));
		setInt("color", 16);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void vongtron(float radius) {
		int numSegments = 150;  // Số lượng đoạn thẳng để tạo thành vòng tròn
		float angleStep = 2.0f * M_PI / numSegments;  // Góc mỗi đoạn

		mvstack.push(model_mat_cpp);
		for (int i = 0; i < numSegments; i++) {
			float angle = i * angleStep;
			float x = radius * cos(angle);
			float y = radius * sin(angle);

			// Vẽ đoạn thẳng nhỏ tạo vòng tròn
			mvstack.push(model_mat_cpp);
			model_mat_cpp = model_mat_cpp * translate(vec3(x, y, 0.0f)) * scale(vec3(0.02, 0.02, 0.02));  // Đặt mỗi đoạn thẳng nhỏ
			setInt("color", 15);  // Màu vòng tròn
			cube();  // Vẽ đoạn thẳng nhỏ
			model_mat_cpp = mvstack.pop();
		}
		model_mat_cpp = mvstack.pop();
	}

	void kimdongho() {
		time_t now = time(0);  
		struct tm localTime; 

		// Thay thế localtime() bằng localtime_s
		localtime_s(&localTime, &now);  // Cập nhật localTime với thời gian hiện tại

		int gio = localTime.tm_hour % 12;  // Lấy giờ từ 0-11
		int phut = localTime.tm_min;       // Lấy phút
		int giay = localTime.tm_sec;       // Lấy giây

		// Tính góc quay
		float goc_phut = 6.0f * phut + 6.0f / 60.0f * giay; // Góc kim phút
		float goc_gio = 30.0f * gio + 30.0f / 60.0f * phut;  // Góc kim giờ

		// Vẽ kim phút
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * rotate_z(-goc_phut) * scale(vec3(0.02, 1.2, 0.02));  // Quay kim phút
		setInt("color", 10);  // Màu kim phút
		cube();
		mvstack.pop();

		// Vẽ kim giờ
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * rotate_z(-goc_gio) * scale(vec3(0.04, 0.4, 0.04));  // Quay kim giờ
		setInt("color", 1);  // Màu kim giờ
		cube();
		mvstack.pop();

	}

	void tuongcheo() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.05, 0.5, 1.4));

		setInt("color", 8);  // Chọn màu cho tường
		cube();  // Vẽ bức tường
		model_mat_cpp = mvstack.pop();
	}

	void thanhngang() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.752, 0.05, 1.15));
		setInt("color", 8);  // Chọn màu cho tường
		cube();  // Vẽ bức tường
		model_mat_cpp = mvstack.pop();
	}
	void thanhcheoleft() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * rotate_z(45)*scale(vec3(0.02, 0.5, 1.4));
		setInt("color", 8);  // Chọn màu cho tường
		cube();  // Vẽ bức tường
		model_mat_cpp = mvstack.pop();
	}
	void thanhcheoright() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * rotate_z(-45) * scale(vec3(0.02, 0.5, 1.4));
		setInt("color", 8);  // Chọn màu cho tường
		cube();  // Vẽ bức tường
		model_mat_cpp = mvstack.pop();
	}
	void bigbag() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(5.0, 1.3, 0));
		thancot();
		model_mat_cpp = mvstack.pop();

		for (float x = 4.3; x <= 5.7; x += 0.15) { 
			mvstack.push(model_mat_cpp); 
			model_mat_cpp = model_mat_cpp * translate(vec3(x, 0.1, -0.55)); 
			thanhdoc(); 
			model_mat_cpp = mvstack.pop(); 
		}

		for (float x = 4.3; x <= 5.7; x += 0.15) {
			mvstack.push(model_mat_cpp);
			model_mat_cpp = model_mat_cpp * translate(vec3(x, 3.1, -0.54));
			thanhdoctren();
			model_mat_cpp = mvstack.pop();
		}
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(5.0, 2.0, -0.52));
		matdongho();
		model_mat_cpp = mvstack.pop();
		
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(5.0, 2.0, -0.55));
		kimdongho();
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(5.0, 2.0, -0.55)); 
		vongtron(0.7f);
		model_mat_cpp = mvstack.pop();
		 
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * rotate_z(45.0f) *translate(vec3(6.7, -1.15, 0));
		tuongcheo();
		model_mat_cpp = mvstack.pop();
		
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * rotate_z(-45.0f) * translate(vec3(0.4, 5.95, 0));
		tuongcheo();
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(5.0, 4.12, 0));
		thanhngang();
		model_mat_cpp = mvstack.pop();

		for (float x = 4.55; x <= 5.5; x += 0.1) {
			mvstack.push(model_mat_cpp);
			model_mat_cpp = model_mat_cpp * translate(vec3(x, 3.935, -0.54));
			thanhdoctrencung();
			model_mat_cpp = mvstack.pop();
		}

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(4.82, 4.32, 0));
		thanhcheoright();
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(5.18, 4.32, 0));
		thanhcheoleft();
		model_mat_cpp = mvstack.pop();
	}
}

float alpha_khoanuoc = 0.0f;
bool dropWater = false;    // Trạng thái: giọt nước rơi hay không
float waterPosY = 0.1f;    // Vị trí ban đầu của giọt nước theo trục Y
float waterSpeed = -0.001f; // Tốc độ rơi xuống của giọt nước
namespace voinuoc{
	void thanvoi() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.2, 1.0, 0.5));
		setInt("color", 5); 
		cube();  
		model_mat_cpp = mvstack.pop();
	}

	void khoanuoc() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * rotate_z(alpha_khoanuoc) *scale(vec3(0.05, 0.02, 0.02));
		setInt("color", 16);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void truc1() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.02, 0.2, 0.02));
		setInt("color", 1);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void truc2() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.1, 0.02, 0.02));
		setInt("color", 1);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void truc3() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.02, 0.05, 0.02));
		setInt("color", 1);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	//Mảnh thứ bên trái, bên phải của bồn rửa tay
	void manh_left_right() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.22, 0.2, 0.01));
		setInt("color", 16);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	//Mảnh thứ bên dưới của bồn rửa tay
	void manh_bot() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.18, 0.01, 0.415));
		setInt("color", 05);
		cube();
		model_mat_cpp = mvstack.pop();
	}
	
	//Mảnh trước của bồn rửa tay
	void manh_front() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.01, 0.18, 0.5));
		setInt("color", 06);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void bonnuoc() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.02, 0.05, 0.02));
		setInt("color", 16);
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void water() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.02, 0.06, 0.01));
		setInt("color", 16);
		cube();
		model_mat_cpp = mvstack.pop();
}
	void updateWater() {
		if (dropWater) {
			waterPosY += waterSpeed; // Cập nhật vị trí Y
			if (waterPosY < -0.5f) { // Giới hạn rơi (dưới một điểm nhất định)
				dropWater = false;   // Dừng giọt nước khi chạm "đất"
			}
		}
	}
	void hoanchinh() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-3, -0.55, -1.0));
		thanvoi();
		model_mat_cpp = mvstack.pop();

		// Thân vòi 1.1
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-2.95, 0.04, -1.2)); 
		truc1();
		model_mat_cpp = mvstack.pop();

		// Khóa nước 1
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-2.95, 0.04, -1.21)); 
		khoanuoc();
		model_mat_cpp = mvstack.pop();

		// Thân vòi 1.2
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-2.895, 0.14, -1.2)); 
		truc2();
		model_mat_cpp = mvstack.pop();

		// Thân vòi 1.3
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-2.85, 0.12, -1.2)); 
		truc3();
		model_mat_cpp = mvstack.pop();

		//Giọt nước 1
		if (dropWater) {
			mvstack.push(model_mat_cpp);
			model_mat_cpp = model_mat_cpp * translate(vec3(-2.85, waterPosY, -1.2));
			water();
			model_mat_cpp = mvstack.pop();
		}
		

		// Thân vòi 2.1
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-2.95, 0.04, -0.81)); 
		truc1();
		model_mat_cpp = mvstack.pop();

		// Khóa nước 2
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-2.95, 0.04, -0.8));  
		khoanuoc();
		model_mat_cpp = mvstack.pop();

		// Thân vòi 2.2
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-2.895, 0.14, -0.8));  
		truc2();
		model_mat_cpp = mvstack.pop();

		// Thân vòi 2.3
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-2.85, 0.12, -0.8));  
		truc3();
		model_mat_cpp = mvstack.pop();

		//Giọt nước 2
		if (dropWater) {
			mvstack.push(model_mat_cpp);
			model_mat_cpp = model_mat_cpp * translate(vec3(-2.85, waterPosY, -0.8));
			water();
			model_mat_cpp = mvstack.pop();
		}
		
		//Bồn rửa tay
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-2.83, -0.4, -1.2));
		manh_left_right();
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-2.83, -0.4, -0.8));
		manh_left_right();
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-2.82, -0.485, -1.0));
		manh_bot();
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-2.72, -0.4, -1.0));
		manh_front();
		model_mat_cpp = mvstack.pop();
	}
}
void DisplayFunc(void)
{
	model_mat_cpp = identity_mat4();
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);

	if (is_translated) {
		model_mat_cpp = model_mat_cpp * translate(vec3(T[0], T[1], T[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (is_rotated) {
		model_mat_cpp = model_mat_cpp * rotate_x(R[0]) * rotate_y(R[1]) * rotate_z(R[2]);
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (is_scaled) {
		model_mat_cpp = model_mat_cpp * scale(vec3(S[0], S[1], S[2]));  // Áp dụng tỉ lệ
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}

	glMatrixMode(GL_MODELVIEW);  
	// Các tham số của hàm lookat
	vec3 eye(cameraX, cameraY, -cameraZ),
		at(cameraX + sin(beta), cameraY - pitch, cameraZ - cos(beta)),
		up(0.0f, 1.0f, 0.0f);

	view_mat_cpp = lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	// Phép chiếu phối cảnh
	float znear = 1.0f, 
		zfar = 100.0f, 
		fov = 67.0f, 
		aspect = (float)CurrentWidth / CurrentHeight;
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Mặt đất
	ground();

	// Bầu trời
	sky();

	mvstack.push(model_mat_cpp); //PUSH_0

	//Hang rao
	hangrao::veHangRao(-2, -0.75, -8, 1, 20, 0.1, 0.8, 0.1, 3, 0.1, 0.1); //float startX, float startY, float startZ, float spacing( khoảng cách giữa các cột)
	
	//Toilet
	toilet::vetuong();
	toilet::updateWaterAngle(0.0006); //Chinh toc do quay cua nuoc ở nhà VS
	toilet::vetoilet();

	//Quay kem
	int startTime = glutGet(GLUT_ELAPSED_TIME);  // Lấy thời gian trôi qua tính bằng mili giây
	float time = static_cast<float>(startTime) / 1000.0f;  // Chuyển sang giây
	quaykem::quay_kem(time); 

	//Dong ho
	dongho::bigbag();

	voinuoc::updateWater(); //Cập nhật vị trí giọt nước

	//Vòi nước
	voinuoc::hoanchinh();
	model_mat_cpp = mvstack.pop(); //POP_0
	glutSwapBuffers();
}

//--------------Các hàm cho camera--------------
void updateCamera() {

	if (isJumping) {
		cameraY += jumpSpeed;
		jumpSpeed -= gravity;
		if (cameraY <= 0.0f) {
			cameraY = 0.0f;
			isJumping = false;
			isGrounded = true;
			jumpSpeed = 0.2f;
		}
	}
	glutPostRedisplay();
}
// ------------------------------------------
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	midWindowX = Width / 2;
	midWindowY = Height / 2;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ------------------------------------------
bool phim1 = true, phim2 = true;
void IdleFunc(void)
{
	onl1();
	glutPostRedisplay();
}
//--------Con lăn chuột---------------
void mouseWheel(int button, int direction, int x, int y) {
	if (direction > 0) {  // Cuộn chuột lên (phóng to)
		S[0] *= 1.1f;  // Phóng to đối tượng
		S[1] *= 1.1f;
		S[2] *= 1.1f;
	}
	else {  // Cuộn chuột xuống (thu nhỏ)
		S[0] /= 1.1f;  // Thu nhỏ đối tượng
		S[1] /= 1.1f;
		S[2] /= 1.1f;
	}

	// Sau khi thay đổi tỉ lệ, yêu cầu vẽ lại
	glutPostRedisplay();
}

// ------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		glutLeaveMainLoop();
		break;
	//----------------camera----------------
	case 'w': //Camera gần
		cameraX += sin(beta) * moveSpeed;
		cameraZ -= cos(beta) * moveSpeed;
		break;
	case 's': //Camera xa
		cameraX -= sin(beta) * moveSpeed;
		cameraZ += cos(beta) * moveSpeed;
		break;
	case 'a': //Sang trái
		cameraX += sin(beta - 3.1415926535 / 2) * moveSpeed;
		cameraZ -= cos(beta - 3.1415926535 / 2) * moveSpeed;
		break;
	case 'd': //Sang phải
		cameraX += sin(beta + 3.1415926535 / 2) * moveSpeed;
		cameraZ -= cos(beta + 3.1415926535 / 2) * moveSpeed;
		break;
	case 'q': // Quay camera ra sau và nhìn ngược lại
		beta += 3.1415926535; // Quay 180 độ
		if (beta > 2 * 3.1415926535) 
			beta -= 2 * 3.1415926535; // Giữ giá trị beta trong khoảng [0, 2π]
		cameraZ = -cameraZ; // Vị trí mắt không đổi
		break;
	case 'x':
		R[0] -= 10.0f;
		is_rotated = true;
		break;
	case 'X':
		R[0] += 10.0f;
		is_rotated = true;
		break;

	case 'y':
		R[1] -= 10.0f;
		is_rotated = true;
		break;
	case 'Y':
		R[1] += 10.0f;
		is_rotated = true;
		break;

	case 'z':
		R[2] -= 10.0f;
		is_rotated = true;
		break;
	case 'Z':
		R[2] += 10.0f;
		is_rotated = true;
		break;

	case '+': //Phóng to
		S[0] *= 1.05f;
		S[1] *= 1.05f;
		S[2] *= 1.05f;
		is_scaled = true;
		break;

	case '-': //Thu nhỏ
		S[0] /= 1.05f;
		S[1] /= 1.05f;
		S[2] /= 1.05f;
		is_scaled = true;
		break;

	case 'r': //Tịnh tiến sang phải
		T[0] -= 0.15f;
		is_translated = true;
		break;
	case 'l': //Tịnh tiến sang trái
		T[0] += 0.15f;
		is_translated = true;
		break;
	case ',':  //Tịnh tiến Xuống dưới
		T[1] += 0.15f;
		is_translated = true;
		break;
	case '.': //Tịnh tiến lên trên
		T[1] -= 0.15f;
		is_translated = true;
		break;
	case 'g':
		T[2] -= 0.15f;
		is_translated = true;
		break;
	case 'h':
		T[2] += 0.15f;
		is_translated = true;
		break;
	case '/': // Mở cửa
		if (door_angle > -180.0f) // Giới hạn mở tối đa 180 độ
			door_angle -= 2.0f;
		if(toilet_angle > -180.0f)
			toilet_angle -= 2.0f;
		break;
	case '?': // Đóng cửa
		if (door_angle < 0.0f) // Giới hạn đóng hoàn toàn
			door_angle += 2.0f;
		if(toilet_angle < -90)
			toilet_angle += 2.0f;
		break;

	case 'f': //Mở cửa quầy kem
		if (alpha3 > 90)
			alpha3 -= 5.0f;
		break;
	case 'F': //Đóng cửa quầy kem
		if (alpha3 < 180)
			alpha3 += 5.0f;
		break;
	case '2':
		alpha_khoanuoc += 5.0f;
		dropWater = true;    // Kích hoạt trạng thái rơi
		waterPosY = 0.1f;    // Đặt lại vị trí ban đầu của giọt nước
		break;
	case '3':
		is_rotating = !is_rotating; // Bật/tắt trạng thái xả nước
		break;
	}
}
// ----------------------------------------

void SpecialFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		T[0] -= 0.05f;
		is_translated = true;
		break;
	case GLUT_KEY_RIGHT:
		T[0] += 0.05f;
		is_translated = true;
		break;
	case GLUT_KEY_UP:
		T[1] += 0.05f;
		is_translated = true;
		break;
	case GLUT_KEY_DOWN:
		T[1] -= 0.05f;
		is_translated = true;
		break;
	case GLUT_KEY_ALT_R:
		T[2] -= 0.05f;
		is_translated = true;
		break;
	case GLUT_KEY_CTRL_R:
		T[2] += 0.05f;
		is_translated = true;
		break;
	}
}
void danhsachlenh() {
	cout << "g/h : Tinh tien vat the ve gan/xa camera" << endl;
	cout << "w/s : Dieu khien camera tien/lui  " << endl;
	cout << "a/d : Dieu khien camera sang trai/phai" << endl;
	cout << "r/l : Dieu khien vat the sang trai/phai" << endl;
	cout << "q   : Nhin nguoc lai 180 do" << endl;
	cout << "+/- : Phong to/Thu nho (+ hoac cuon chuot) " << endl;
	cout << "./, : Dua camera len tren/xuong duoi" << endl;
	cout << "//? : Mo/Dong cua nha VS + Nap Toilet mo ra" << endl;
	cout << "x/X : Quay quanh truc Ox" << endl;
	cout << "y/Y : Quay quanh truc Oy" << endl;
	cout << "z/Z : Quay quanh truc Oz" << endl;
	cout << "f/F : Dong/Mo cua quay kem" << endl;
	cout << "2   : Bat/tat trang thai mo voi nuoc rua tay" << endl;
	cout << "3   : Bat/tat trang thai xa nuoc nha VS" << endl;
	
	cout << endl;
}
// ------------------------------------------
int main(int argc, char* argv[])
{
	danhsachlenh();
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Computer Graphic: City Park");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutCloseFunc(CloseFunc);
	glutMouseWheelFunc(mouseWheel);
	glutMainLoop();
	return 0;
}
