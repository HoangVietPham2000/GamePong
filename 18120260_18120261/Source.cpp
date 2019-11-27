#include "Ball.h"
// screen
int width = 640; // width of screen
int height = 480; // height of screen
int FPS = 640 / 60; // Frame per second

// score
int score_left = 0; // 
int score_right = 0;

// Paddle
Paddle Pleft;
Paddle Pright(width - Pleft.width - 10, 150);
// ball
Ball ball;

void keyboard() {
	// left paddle
	if (GetAsyncKeyState(VK_W)) {  // Get keyboard 
		if (Pleft.y < height - 12 - Pleft.height) {
			Pleft.y += Pleft.speed;
		}
	}
	if (GetAsyncKeyState(VK_S)) {
		if (Pleft.y > 11 )
		{
			Pleft.y -= Pleft.speed;
		}
	}

	// right paddle
	if (GetAsyncKeyState(VK_UP)) {
		if (Pright.y < height - 12 - Pright.height) {
			Pright.y += Pright.speed;
		}
		
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		if (Pright.y > 11) {
			Pright.y -= Pright.speed;
		}
		
	}
}

string inttostr(int x) {
	// converts int to string
	stringstream ss;
	ss << x;
	return ss.str();
}

void drawText(float x, float y, string text) { // Viết chữ ra màn hình
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text.c_str());
}

void updateBall2players() {
	// fly a bit
	ball.pos_x += ball.dir_x * ball.speed;
	ball.pos_y += ball.dir_y * ball.speed;

	// hit by left paddle?
	if (ball.pos_x < Pleft.x + Pleft.width &&
		ball.pos_x > Pleft.x &&
		ball.pos_y < Pleft.y + Pleft.height &&
		ball.pos_y > Pleft.y) {
		if (ball.dir_y > 0)
		{
			ball.dir_x = abs(ball.dir_x);
			ball.dir_y = abs(ball.dir_y);

		}
		else {
			ball.dir_x = abs(ball.dir_x);
			ball.dir_y = -abs(ball.dir_y);
		}
		ball.speed = ball.speed * 1.01;
	}

	// hit by right paddle?
	if (ball.pos_x > Pright.x &&
		ball.pos_x < Pright.x + Pright.width &&
		ball.pos_y < Pright.y + Pright.height &&
		ball.pos_y > Pright.y) {
		if (ball.dir_y > 0)
		{
			ball.dir_x = -abs(ball.dir_x);
			ball.dir_y = abs(ball.dir_y);

		}
		else {
			ball.dir_x = -abs(ball.dir_x);
			ball.dir_y = -abs(ball.dir_y);
		}
		ball.speed = ball.speed * 1.01;
	}

	// hit left wall?
	if (ball.pos_x < 0) {
		++score_right;
		ball.pos_x = width / 2;
		ball.pos_y = height / 2;
		ball.dir_x = -1.0f; // abs
		ball.dir_y = 0.3f;
		ball.speed = 2;
	}

	// hit right wall?
	if (ball.pos_x > width) {
		++score_left;
		ball.pos_x = width / 2;
		ball.pos_y = height / 2;
		ball.dir_x = -1.0f; // abs
		ball.dir_y = 0.3f;
		ball.speed = 2;
	}

	// hit top wall?
	if (ball.pos_y > height - 8) {
		ball.dir_y = -fabs(ball.dir_y); // abs
	}

	// hit bottom wall?
	if (ball.pos_y < 8) {
		ball.dir_y = abs(ball.dir_y); // abs
	}	
}

void updateBall1players() {
	// fly a bit
	ball.pos_x += ball.dir_x * ball.speed;
	ball.pos_y += ball.dir_y * ball.speed;

	// hit by left paddle?
	if (ball.pos_x < Pleft.x + Pleft.width &&
		ball.pos_x > Pleft.x &&
		ball.pos_y < Pleft.y + Pleft.height &&
		ball.pos_y > Pleft.y) {
		if (ball.dir_y > 0)
		{
			ball.dir_x = abs(ball.dir_x);
			ball.dir_y = abs(ball.dir_y);
			
		}
		else {
			ball.dir_x = abs(ball.dir_x);
			ball.dir_y = -abs(ball.dir_y);
		}
		ball.speed = ball.speed * 1.01;
	}

	// hit by right paddle?
	if (ball.pos_x > Pright.x &&
		ball.pos_x < Pright.x + Pright.width &&
		ball.pos_y < Pright.y + Pright.height &&
		ball.pos_y > Pright.y) {
		if (ball.dir_y > 0)
		{
			ball.dir_x = -abs(ball.dir_x);
			ball.dir_y = abs(ball.dir_y);

		}
		else {
			ball.dir_x = -abs(ball.dir_x);
			ball.dir_y = -abs(ball.dir_y);
		}
		ball.speed = ball.speed * 1.01;
	}

	// hit left wall?
	if (ball.pos_x < 0) {
		++score_right;
		ball.pos_x = width / 2;
		ball.pos_y = height / 2;
		ball.dir_x = -1.0f; // abs
		ball.dir_y = 0.3f;
		ball.speed = 2;
	}

	// hit right wall?
	if (ball.pos_x > width) {
		++score_left;
		ball.pos_x = width / 2;
		ball.pos_y = height / 2;
		ball.dir_x = -1.0f; // abs
		ball.dir_y = 0.3f;
		ball.speed = 2;
	}

	// hit top wall?
	if (ball.pos_y > height - 8) {
		ball.dir_y = -fabs(ball.dir_y); // abs
	}

	// hit bottom wall?
	if (ball.pos_y < 8) {
		ball.dir_y = abs(ball.dir_y); // abs
	}
}

void updatePaddle1player() {
	Pright.y = ball.pos_y - Pright.height / 2;
	
}

void update2player(int value) {
	// input handling
	keyboard();

	// update ball
	updateBall2players();

	// Call update() again in 'FPS' milliseconds
	glutTimerFunc(FPS, update2player, 0);

	// Redisplay frame
	glutPostRedisplay();
}

void update1player(int value) {
	// input handling
	keyboard();

	// update ball
	updateBall1players();

	// update Paddle

	updatePaddle1player();

	if ((score_left - 3 > score_right && score_left > 3) ||
		(score_right - 3 > score_left && score_right > 3)) {
		glClearColor(0.355, 0.2, 0.5, 1.0); // tô nền màu xanh lá
		// draw score
		glColor3f(0.4, 0.0, 1.0); // màu xanh dương
		drawText(width / 2 - 10, height - 25, 
			inttostr(score_left) + "   :   " + inttostr(score_right));
	}
	else {
		// Call update() again in 'FPS' milliseconds
		glutTimerFunc(FPS, update1player, 0);

		// Redisplay frame
		glutPostRedisplay();
	}
}



void drawInf() { // hàm này định viết nhưng mà lỗi rồi
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 0.0); //màu vàng
	drawText(width / 2 - 30, height - 105, "18120260: Nguyen Gia Vi");
	drawText(width / 2 - 30, height - 135, "18120261: Pham Hoang Viet");
	while (GetAsyncKeyState(VK_W))
	{
		return;
	}
	glutSwapBuffers();
}

void drawRectrangle(float x, float y, float width, float height) {  // vẽ hình chữ nhật, như tên của hàm
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void draw_map() {
	glColor3f(0.0, 1.0, 1.0);
	//drawRect(0,0,8,height);
	//drawRect(width - 8, 0, width, height);
	drawRectrangle(width / 2 - 10, height - 25, width / 2, 0);
	drawRectrangle(0, height - 8, width, height); // in dòng trên cùng làm tường
	drawRectrangle(0, 0, width, 8); // in dòng dưới cùng làm tường
}

void draw() {
	// clear (has to be done at the beginning)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// draw Information
	//drawInf();
	// draw map
	draw_map();
	// draw paddle
	glColor3f(1.0, 1.0, 1.0); //màu trắng
	Pleft.drawRect(Pleft.x, Pleft.y, Pleft.width, Pleft.height);
	Pright.drawRect(Pright.x, Pright.y, Pright.width, Pright.height);

	// draw score
	glColor3f(0.4, 0.0, 1.0); // màu xanh dương
	drawText(width / 2 - 10, height - 25, inttostr(score_left) + " : " + inttostr(score_right));
	
	// draw ball
	glColor3f(1.9, 0.6, 0.6); //màu hồng
	drawRectrangle(ball.pos_x - ball.size / 2, ball.pos_y - ball.size / 2, ball.size, ball.size);
	glutSwapBuffers();
}

void enable2D_Winner(int width, int height) {
	glClearColor(0, 0, 0, 1.0); // tô nền màu xanh lá
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void enable2D(int width, int height) {
	glClearColor(0.355, 0.7382, 0.1679, 1.0); // tô nền màu xanh lá
	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//======================================
void menu(int argc, char** argv) {
here:TextColor(12);
	system("cls");
	gotoXY(45, 9);  cout << ".... VV STUDIO ...." << endl;
	TextColor(9);
	gotoXY(40, 11);  cout << "1-> New Game: 2 players" << endl;
	gotoXY(40, 12);  cout << "2-> New Game: 1 player and 1 computer" << endl;
	gotoXY(40, 13);  cout << "3-> About Us: " << endl;
	gotoXY(40, 14);  cout << "4-> Quit: " << endl;
	int n;
	TextColor(11);
	gotoXY(40, 15); cout << "Your Choice:   ->  ";
	cin >> n;
	switch ( n )
	{
	case 1:
	{
		system("cls");
		TextColor(12);
		gotoXY(45, 9);  cout << ".... VV STUDIO ...." << endl;
		TextColor(9);
		gotoXY(40, 12);  cout << "Player 1: " << endl;
		gotoXY(50, 13);  cout << "Use W and S to move up and down." << endl;
		gotoXY(40, 14);  cout << "Player 2:" << endl;
		gotoXY(50, 15);  cout << "Use navigation key to move up and down." << endl;
		TextColor(11);
		gotoXY(40, 17);  cout << "Let's try it . . .";
		_getch();
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(width, height);
		glutCreateWindow("Ping Pong");
		// Register callback functions  

		glutTimerFunc(FPS, update2player, 0);
		glutDisplayFunc(draw);
		// setup scene to 2d mode and set draw color to white
		enable2D(width, height);
		glColor3f(1.0f, 1.0f, 1.0f);


		// start the whole thing
		glutMainLoop();
		break;
	}
	case 2:
	{
		system("cls");
		TextColor(12);
		gotoXY(45, 9);  cout << ".... VV STUDIO ...." << endl;
		TextColor(9);
		gotoXY(40, 12);  cout << "Player: " << endl;
		gotoXY(50, 13);  cout << "Use W and S to move up and down." << endl;
		TextColor(12);
		gotoXY(40, 11);  cout << "Let's try it . . .";
		_getch();
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(width, height);
		glutCreateWindow("Ping Pong");
		//
		glutDisplayFunc(drawInf);
		// Register callback functions  

		glutTimerFunc(FPS, update1player, 0);
		glutDisplayFunc(draw);
		// setup scene to 2d mode and set draw color to white
		enable2D(width, height);
		glColor3f(1.0f, 1.0f, 1.0f);


		// start the whole thing
		glutMainLoop();
		break;
	}
	case 3:
	{
		system("cls");
		TextColor(12);
		gotoXY(45, 9);  cout << ".... VV STUDIO ...." << endl;
		TextColor(9);
		gotoXY(40, 12); cout << "Author: ";
		gotoXY(40, 14); cout << "        18120260 -> NGUYEN GIA VI" << endl;
		gotoXY(40, 16); cout << "        18120261 -> PHAM HOANG VIET" << endl;
		TextColor(11);
		gotoXY(40, 18); cout << "Game:   PING PONG ";
		_getch();
		goto here;
		break;
	}
	case 4:
	{
		system("cls");
		TextColor(12);
		gotoXY(40, 9);  cout << ".... VV STUDIO ...." << endl;
		TextColor(9);
		gotoXY(40, 11); cout << "Goodbye ~~~   ";
		Sleep(2000);
		break;
	}
	default:
		break;
	}

}

int main(int argc, char** argv) {
	PlaySound("EpicLegend.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	menu(argc, argv);
	return 0;
}
