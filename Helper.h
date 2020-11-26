UniformBufferObject UBO;
glm::mat4 Model;
void* Data;

//Fps
int Frame = 0;
int Final_Time;
int Init_Time = 0;
int Final_Fps = 0;
char CharFPS[32];

void CalcFps(const char *title)
{
	Frame ++;
	Final_Time = time(NULL);
	if(Final_Time - Init_Time > 0)	
	{
		Final_Fps = Frame/(Final_Time - Init_Time);
		Frame = 0;
		Init_Time = Final_Time;
	}
	
	sprintf(CharFPS,"%s %d", title, Final_Fps);
	glfwSetWindowTitle(window, CharFPS);
}

void LoadIdentity()
{
	Model = glm::mat4(1.0f);
}

void Translate(float x, float y, float z)
{
	Model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	UBO.Model = Model;
}

void Rotate(float angle, float x, float y, float z)
{
	Model = glm::rotate(Model, angle, glm::vec3(x, y, z));
	UBO.Model = Model;
}

void Scale(float x, float y, float z)
{
	Model = glm::scale(Model, glm::vec3(x, y, z));
	UBO.Model = Model;
}

void PushMatrix()
{
	vkMapMemory(device, UniformBufferMemory, 0, sizeof(UBO.Model), 0, &Data);
	memcpy(Data, &UBO.Model, sizeof(UBO.Model));
	vkUnmapMemory(device, UniformBufferMemory);
}

glm::mat4 PerspectivMatrix( float aspect_ratio, float field_of_view, float near_plane, float far_plane ) 
{
    float f = 1.0f / tan(glm::radians(0.5f * field_of_view) );

    glm::mat4 perspective_projection_matrix = 
	{
      f / aspect_ratio,
      0.0f,
      0.0f,
      0.0f,

      0.0f,
      -f,
      0.0f,
      0.0f,

      0.0f,
      0.0f,
      far_plane / (near_plane - far_plane),
      -1.0f,
      
      0.0f,
      0.0f,
      (near_plane * far_plane) / (near_plane - far_plane),
      0.0f
    };
    return perspective_projection_matrix;
}
