
#include <iostream>
#include <iomanip>
#include <vector>
#include<GLFW/glfw3.h> 
#include<Windows.h> 
#include <math.h> 

#pragma comment(lib,"glfw3.lib") 
#pragma comment(lib,"opengl32.lib") 

using namespace std; 
double sc = 1;
float alpha, beta;
float iterat = 1;
bool curent = true;


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    sc += yoffset/100;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == 'W')
        alpha += 4.0;
    if (key == 'S')
        alpha -= 4.0;
    if (key == 'A')
        beta -= 2.0;
    if (key == 'D')
        beta += 2.0;
    //_______________STEPS_________________//
    if (key == '-') 
        iterat -= 0.8;
    if (key == '=')
        iterat += 0.8;
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action != GLFW_PRESS) {
        curent = true;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        curent = false;
    }
}



struct Point
{
    double x_coor;
    double y_coor;
    double z_coor;
};
vector < Point > v;

struct Shere_st
{
    double x_sh;
    double y_sh;
    double z_sh;
};

vector <Shere_st> sh;

const double PI = 3.141592653589793;


void lorenz(double x, double y, double z, double r, double a, double c) {
    double t = 0.01;

    cout << string(100, '\n') << "iterat: " << iterat << endl;
    cout << "x , y , z : {" << x << "; " << y << "; " << z << "}" <<endl;
    cout << "r : " << r << endl;
    cout << "a : " << a << endl;
    cout << "c : " << c << endl;
 
    for (float i = 0; i < iterat; i += 0.1) {

       double xt = x + t * a * (y - x);                // x = a * (y - x)
       double yt = y + t * (x * (r - z) - y);          // y = x * (r - z) - y)
       double zt = z + t * (x * y - c * z);            // z = x * y - c * z)

        x = xt;
        y = yt;
        z = zt;

        v.push_back({ x, y, z });
    }

    cout << "x , y , z : {" << x << "; " << y << "; " << z << "}" << endl;
}

void shere(double x0, double y0, double z0) {
    sh.clear();
    double r = 1.5;
    for (double i = 0; i < 2 * PI; i += PI / 5) {
        for (double j = 0; j < PI; j += PI / 5) {
            double x = x0 + r * sin(j) * cos(i);
            double y = y0 + r * sin(j) * sin(i);
            double z = z0 + r * cos(j);

            sh.push_back({ x, y, z });

            x = x0 + r * sin(j + PI / 5) * cos(i + PI / 5);
            y = y0 + r * sin(j + PI / 5) * sin(i + PI / 5);
            z = z0 + r * cos(j + PI / 5);

            sh.push_back({ x, y, z });
        }
    }
}


void draw_shere() {
    for (int i = 0; i < sh.size(); i++) {
        glBegin(GL_TRIANGLE_STRIP);
        glNormal3f(1.f, 1.f, 1.0f);
        glVertex3d(sh[i].x_sh, sh[i].y_sh, sh[i].z_sh);
    }
    glEnd();
}

//--------------------------------//
void move_shere1() {
    for (int i = 0; i < v.size()/2; i++) {
        shere(v[i].x_coor, v[i].y_coor, v[i].z_coor);
    }
}

void move_shere2() {
    for (int i = v.size() / 2; i < v.size(); i++) {
        shere(v[i].x_coor, v[i].y_coor, v[i].z_coor);
    }
}
//--------------------------------//

//--------------------------------//
void visual_lorenz1() {
  
    for (int i = 0; i < v.size()/2; i++) {
        glBegin(GL_TRIANGLE_STRIP);
        glNormal3f(0.f, 0.f, 1.0f);
        glColor3f(0.05f, 0.05f, 0.15f);
        glVertex3d(v[i].x_coor + 0.5f, v[i].y_coor + 0.5f, v[i].z_coor + 0.5f);
        glColor3f(0.25f, 0.25f, 0.35f);
        glVertex3d(v[i].x_coor - 0.5f, v[i].y_coor - 0.5f, v[i].z_coor - 0.5f);
    }
    glEnd();
}

void visual_lorenz2() {

    for (int i = v.size() / 2; i < v.size(); i++) {
        glBegin(GL_TRIANGLE_STRIP);
        glNormal3f(0.f, 0.f, 1.0f);
        glColor3f(0.05f, 0.15f, 0.05f);
        glVertex3d(v[i].x_coor + 0.5f, v[i].y_coor + 0.5f, v[i].z_coor + 0.5f);
        glColor3f(0.25f, 0.35f, 0.25f);
        glVertex3d(v[i].x_coor - 0.5f, v[i].y_coor - 0.5f, v[i].z_coor - 0.5f);
    }
    glEnd();
}
//--------------------------------//

void axis() {

    glBegin(GL_LINE_STRIP);// x
    glColor3f(0.8f, 0.0f, 0.0f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(50.f, 0.f, 0.f);
    glEnd();

    glBegin(GL_LINE_STRIP);// y
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, 50.f, 0.f);
    glEnd();

    glBegin(GL_LINE_STRIP);// z
    glColor3f(0.0f, 0.0f, 0.8f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, 0.f, 50.f);
    glEnd();

    for (int i = 1; i < 50; i++) {
        glBegin(GL_LINE_STRIP);
        glColor3f(0.8f, 0.0f, 0.0f);
        glVertex3f(i, 0.5f, 0.5f);
        glVertex3f(i, -0.5f, -0.5f);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.8f, 0.0f);
        glVertex3f(0.5f, i, 0.5f);
        glVertex3f(-0.5f, i, -0.5f);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.0f, 0.8f);
        glVertex3f(0.5f, 0.5f, i);
        glVertex3f(-0.5f, 0.5f, i);
        glEnd();

    }

}

void light() {
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float lpos[4] = { 10, 10.5, 100.5, 1 };
    float dir[4] = { -10, -10.5, -100.5, 1 };

    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);


    float ambient[] = { 0.85f, 0.85f, 0.85f, 0.f };
    float diffuse[] = { 1.f, 1.f, 1.f, 2.f };
    float spec[] = { 0.6f, 0.6f, 0.6f, 0.5f };
    float specref[] = { 0.4f, 0.4f, 0.4f, 0.5f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient); // фон
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse); // диффузное 
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec); // отражение

    glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
    glMateriali(GL_FRONT, GL_SHININESS, 32);
  
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 80);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glColorMaterial(GL_FRONT, GL_SHININESS);

}


void display(GLFWwindow * window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
    glDepthRange(0, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.f, 1.f, 1.f, 0.0f);
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                                                                  
    glOrtho(-5, 5, -5.0 * height / width, 5.0 * height / width, -5, 5);

    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();

    glScaled(sc/20, sc/20, sc/20);
    glTranslatef(-5.f, -10.0f, 0.f);

    glRotatef(alpha, 1, 0, 0);
    glRotatef(beta, 0, 1, 0);

    light();
    axis();

    move_shere1();
    glColor3f(0.f, 0.f, 0.5f);
    draw_shere();
    visual_lorenz1();



    move_shere2();
    glColor3f(0.f, 0.5f, 0.f);
    draw_shere();
    visual_lorenz2();

    glLoadIdentity();

    v.clear();  
    sh.clear();
}


void main() {

    if (!glfwInit())exit(EXIT_FAILURE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    double xn, yn, zn, rn, an, cn;
    cout << "Enter start coordinates" << endl;
    cin >> xn;
    cin >> yn;
    cin >> zn;

    cout << "Enter r" << endl;
    cin >> rn;
    cout << "Enter a" << endl;
    cin >> an;
    cout << "Enter c" << endl;
    cin >> cn;

    double xnn, ynn, znn, rnn, ann, cnn;
    cout << "Enter start coordinates" << endl;
    cin >> xnn;
    cin >> ynn;
    cin >> znn;

    cout << "Enter r" << endl;
    cin >> rnn;
    cout << "Enter a" << endl;
    cin >> ann;
    cout << "Enter c" << endl;
    cin >> cnn;
  
    glfwMakeContextCurrent(window);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    while (!glfwWindowShouldClose(window))
    {
        display(window);
        lorenz(xn, yn, zn, rn, an, cn);

        lorenz(xnn, ynn, znn, rnn, ann, cnn);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

}