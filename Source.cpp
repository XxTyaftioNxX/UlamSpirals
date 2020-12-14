#include<iostream>
#include<GLFW/glfw3.h>

int ix = 1, iy = 0;

bool isPrime(int num) {
	bool flag = true;
	for (int i = 2; i <= num / 2; i++) {
		if (num % i == 0) {
			flag = false;
			break;
		}
	}
	return flag;
}

void draw_square(int x, int y, float size)
{
	float s = size / 2;
	glBegin(GL_TRIANGLES);

	glVertex3f(x - s, y + s, 0);
	glVertex3f(x + s, y + s, 0);
	glVertex3f(x - s, y - s, 0);

	glVertex3f(x + s, y + s, 0);
	glVertex3f(x - s, y - s, 0);
	glVertex3f(x + s, y - s, 0);

	glEnd();
}

void switcher()
{
	if (ix == 1 && iy == 0)
	{
		ix = 0;
		iy = 1;
		return;
	}
	if (ix == 0 && iy == 1)
	{
		ix = -1;
		iy = 0;
		return;
	}
	if (ix == -1 && iy == 0)
	{
		ix = 0;
		iy = -1;
		return;
	}
	if (ix == 0 && iy == -1)
	{
		ix = 1;
		iy = 0;
		return;
	}
}

int main() {

	int wheight = 300, wbreath = 300, size = 1;
	GLFWwindow* window;

	int xl = 0, yl = 0;
	int xpos = 0;
	int ypos = 0;
	int current = 1;

	int todraw[100000][2];
	int drawables = 0;

	while (true)
	{
		if (ix != 0)
		{
			xl++;
			if (xpos >= (wbreath / (2 * size)))
				break;
			int i = 1;
			if (xpos == 0)
				i = 0;
			else
				xpos += ix;
			for (i; i <= xl; i++)
			{
				if (isPrime(current))
				{
					todraw[drawables][0] = xpos;
					todraw[drawables][1] = ypos;
					drawables++;
				}
				if (i < xl)
					xpos += ix;
				current++;
			}
			switcher();
		}
		else {
			yl++;
			if (ypos >= (wheight / (2 * size)))
				break;
			ypos += iy;
			for (int i = 1; i <= yl; i++)
			{
				if (isPrime(current))
				{
					todraw[drawables][0] = xpos;
					todraw[drawables][1] = ypos;
					drawables++;
				}
				if (i < yl)
					ypos += iy;
				current++;
			}
			switcher();
		}
	}
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(wheight * 2, wbreath * 2, "Ulam Spirals", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glOrtho(-wbreath / 2, wbreath / 2, -wheight / 2, wheight / 2, 0, 1);
	for (int d = 0; d < drawables; d++)
	{
		std::cout << todraw[d][0] << "," << todraw[d][1] << std::endl;
		std::cout << d;
	}

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0, 1.0, 1.0);

		for (int d = 0; d < drawables; d++)
		{
			draw_square(todraw[d][0] * size, todraw[d][1] * size, size);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}