#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 FragColor;
layout(location = 1) in vec2 FragUVcoord;

layout(location = 0) out vec4 OutColor;

layout(binding = 1) uniform sampler2D tex;
layout(binding = 2) uniform bool Color = false; 

void main()
{
	if(Color == true)OutColor = vec4(FragColor);	
	if(Color == false)OutColor = texture(tex, FragUVcoord);
}
