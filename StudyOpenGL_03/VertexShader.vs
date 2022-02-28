#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
out vec3 ourColor; // ��Ƭ����ɫ�����һ����ɫ

void main()
{ 
	//�޸Ķ�����ɫ�������������µߵ�
	//gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);

	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	ourColor = aColor;
}