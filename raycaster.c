#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265359
#define DR 0.0174533

float px, py, pdx, pdy, pa;
int wallX = 8, wallY = 8, tileS = 64;
int map[] = 
{
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,1,0,0,0,1,
	1,0,0,0,0,0,1,1,
	1,1,1,1,1,1,1,1,
};

float dist(float ax, float ay, float bx, float by, float ang) {
	return ( sqrt ((bx - ax) * (bx - ax) + (by-ay) * (by - ay)));
}

void drawRays3D() {
	int r,mx,my,mp,dof;
	float rx,ry,ra,xo,yo, disT;
	ra = pa - DR * 30;
	if (ra < 0) {
		ra += 2*PI;
	} 
	if (ra > 2*PI) {
		ra 	-= 2*PI;
	}
	
	for (r = 0; r < 60; r++) {
		dof = 0;
		float disH= 1000000, hx = px, hy = py;
		float aTan = -1/tan(ra);
		if (ra > PI) {
			ry = (((int)py >> 6)<<6)-0.0001;
			rx = (py - ry) * aTan + px;
			yo = -64;
			xo = -yo*aTan;
		}
		if (ra < PI) {
			ry = (((int)py >> 6)<<6)+64;
			rx = (py - ry) * aTan + px;
			yo = 64;
			xo = -yo*aTan;
		}
		if (ra ==0 || ra == PI) {
			rx = px;
			ry = py; 
			dof = 8;
		}
		while(dof<8) {
			mx = (int) (rx) >>6;
			my = (int) (ry)>>6;
			mp = my*wallX+mx;
			if (mp > 0 && mp<wallX*wallY && map[mp] == 1) {
				dof = 8;
				hx = rx;
				hy = ry;
				disH = dist(px, py, hx, hy, ra);
			} else {
				rx+=xo;
				ry+=yo;
				dof += 1;
			}
		}
		
		dof =0;
		float disV = 100000, vx = px, vy = py;
		float nTan = -tan(ra);
		if (ra > PI/2 && ra < 3*PI/2) {
			rx = (((int)px >> 6)<<6)-0.0001;
			ry = (px - rx) * nTan + py;
			xo = -64;
			yo = -xo*nTan;
		}
		if (ra > 3*PI/2 || ra < PI/2) {
			rx = (((int)px >> 6)<<6)+64;
			ry = (px - rx) * nTan + py;
			xo = 64;
			yo = -xo*nTan;
		}
		if (ra ==0 || ra == PI) {
			rx = px;
			ry = py; 
			dof = 8;
		}
		while(dof<8) {
			mx = (int) (rx) >>6;
			my = (int) (ry)>>6;
			mp = my*wallX+mx;
			if (mp > 0 && mp<wallX*wallY && map[mp] == 1) {
				dof = 8;
				vx = rx;
				vy = ry;
				disV = dist(px, py, vx, vy, ra);
			} else {
				rx+=xo;
				ry+=yo;
				dof += 1;
			}
		}
		if (disV<disH) {
			rx = vx;
			ry = vy;
			disT = disV;
			glColor3f(0.7,0,0);
		}
		if (disH < disV){
			rx = hx;
			ry = hy;
			disT =disH;
			glColor3f(0.9,0,0);
		}
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex2i(px,py);
		glVertex2i(rx,ry);
		glEnd();
		
		float ca = pa - ra;
		if (ca < 0) {
			ca += 2*PI;
		}
		if (ca > 2*PI) {
			ca -= 2*PI;
		}
		disT=disT*cos(ca);
		float lineH=(tileS*320)/disT; 
		if (lineH > 320) {
			lineH = 320;
		}
		float lineO = 160 - lineH/2;
		glLineWidth(8);
		glBegin(GL_LINES);
		glVertex2i(r*8+530,lineO);
		glVertex2i(r*8+530,lineH+lineO);
		glEnd();
		
		glColor3f(0.5, 0.8, 1.0); 
		glBegin(GL_LINES);
		glVertex2i(r * 8 + 530, 0);
		glVertex2i(r * 8 + 530, lineO);
		glEnd();

		glColor3f(0.3, 0.3, 0);
		glBegin(GL_LINES);
		glVertex2i(r * 8 + 530, lineO + lineH);
		glVertex2i(r * 8 + 530, 320);  
		glEnd();

		ra+=DR;
		if (ra < 0) ra += 2 * PI;
		if (ra > 2 * PI) ra -= 2 * PI;
	}
}

void drawPlayer() {
	glColor3f(0,0,1);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(px,py);
	glEnd();
	
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(px, py);
	glVertex2i(px + pdx * 5, py + pdy*5);
	glEnd();
}

void controls(unsigned char key, int x, int y) {
	if (key == 'a') {
		pa-= 0.1;
		if (pa < 0) {
			pa+= 2*PI;
		}
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (key == 'd') {
		pa+= 0.1;
		if (pa > 2*PI) {
			pa-= 2*PI;
		}
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (key == 's') {
		float nx = px - cos(pa) * 20;
		float ny = py - sin(pa) * 20;
		int mx = (int)nx >> 6;
		int my = (int)ny >> 6;
		if (map[my*wallX + mx] == 0) {
			px-=pdx;
			py-=pdy;
		}
	}
	if (key == 'w') {
		float nx = px + cos(pa) * 20;
		float ny = py + sin(pa) * 20;
		int mx = (int)nx >> 6;
		int my = (int)ny >> 6;
		if (map[my*wallX + mx] == 0) {
			px+=pdx;
			py+=pdy;
		}
	}
	float spa = pa + PI / 2;  
	if (spa > 2 * PI) spa -= 2 * PI;
	
	float sdx = cos(spa) * 2;
	float sdy = sin(spa) * 2;
	
	if (key == 'q') {
	    float nx = px - sdx;
	    float ny = py - sdy;
	    int mx = (int)nx >> 6;
	    int my = (int)ny >> 6;
	    if (map[my * wallX + mx] == 0) {
	        px = nx;
	        py = ny;
	    }
	}
	
	if (key == 'e') {
	    float nx = px + sdx;
	    float ny = py + sdy;
	    int mx = (int)nx >> 6;
	    int my = (int)ny >> 6;
	    if (map[my * wallX + mx] == 0) {
	        px = nx;
	        py = ny;
	    }
	}
	glutPostRedisplay();
}

void drawMap2D() {
	int x, y, xv, yv;
	for (y = 0; y < wallY; y++){
		for (x = 0; x < wallX; x++){
			yv = y * tileS;
			xv = x * tileS;
			if (map[y*wallX + x]==1){
				glColor3f(1,1,1);
			} else {
				glColor3f(0,0,0);
			}
			glBegin(GL_QUADS);
			glVertex2i(xv + 1, yv + 1);
			glVertex2i(xv + 1, yv + tileS - 1);
			glVertex2i(xv + tileS - 1, yv + tileS - 1);
			glVertex2i(xv + tileS - 1, yv + 1);
			glEnd();
		}
	}
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap2D();
    drawRays3D();
    drawPlayer();
    glutSwapBuffers();
}

void resize(int W, int H) {
	glutReshapeWindow(1024, 512);
}

void init() {
    glClearColor(0.3f, 0.3f, 0.3f, 0.0f); 
    gluOrtho2D(0, 1024, 512, 0);          
    px = 300; py = 300;
    pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 512);
    glutInitWindowPosition(200,200);
    glutCreateWindow("Raycaster");
    init();                    
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
	glutKeyboardFunc(controls);
    glutMainLoop();          
    return 0;
}

