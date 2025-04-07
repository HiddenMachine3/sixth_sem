#include <GL/glut.h>
#include <GL/gl.h>

#include <stdlib.h>
#include <stdio.h>

const int WIDTH = 500, HEIGHT = 500;
int counter = 0, steps = 1;

float tetrahedron_points[4][3] = {
    {0, 1, 1},
    {1, 1, 0},
    {0, 0, 0},
    {1, 0, 1},
};
float colors[4][3];

void copy_array(float src[], float dest[], int n)
{
    for (int i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }
}

void draw_gasket(float points[4][3], int n, float colors[4][3])
{
    static int face_idx[4][3] = {{0, 1, 2}, {0, 3, 1}, {1, 3, 2}, {0, 2, 3}};
    if (n <= 0)
    {
        for (int f = 0; f < 4; f++)
        {
            glBegin(GL_TRIANGLES);
            glColor3f(colors[f][0], colors[f][1], colors[f][2]);
            for (int p = 0; p < 3; p++)
                glVertex3f(points[face_idx[f][p]][0], points[face_idx[f][p]][1], points[face_idx[f][p]][2]);
            glEnd();
        }
    }
    else
    {
        float mid[6][3];

        float new_points[4][4][3];

        for (int j = 0; j < 3; j++)
        {
            mid[0][j] = (points[0][j] + points[1][j]) / 2;
            mid[1][j] = (points[1][j] + points[2][j]) / 2;
            mid[2][j] = (points[0][j] + points[2][j]) / 2;
            mid[3][j] = (points[0][j] + points[3][j]) / 2;
            mid[4][j] = (points[1][j] + points[3][j]) / 2;
            mid[5][j] = (points[2][j] + points[3][j]) / 2;
        }

        copy_array(points[0], new_points[0][0], 3);
        copy_array(mid[0], new_points[0][1], 3);
        copy_array(mid[2], new_points[0][2], 3);
        copy_array(mid[3], new_points[0][3], 3);

        copy_array(mid[0], new_points[1][0], 3);
        copy_array(points[1], new_points[1][1], 3);
        copy_array(mid[1], new_points[1][2], 3);
        copy_array(mid[4], new_points[1][3], 3);

        copy_array(mid[2], new_points[2][0], 3);
        copy_array(mid[1], new_points[2][1], 3);
        copy_array(points[2], new_points[2][2], 3);
        copy_array(mid[5], new_points[2][3], 3);

        copy_array(mid[3], new_points[3][0], 3);
        copy_array(mid[4], new_points[3][1], 3);
        copy_array(mid[5], new_points[3][2], 3);
        copy_array(points[3], new_points[3][3], 3);

        for (int i = 0; i < 4; i++)
            draw_gasket(new_points[i], n - 1, colors);
    }
}

void draw_tetrahedron()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float rot_speed = counter++ * 0.0001;
    glRotatef(rot_speed * 360, 1, 0, 0);
    glRotatef(rot_speed * 360 * 0.5, 0, 0, 1);
    glRotatef(rot_speed * 360 * 0.3, 0, 1, 0);

    draw_gasket(tetrahedron_points, steps, colors);
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_tetrahedron();

    glFlush();
    glutPostRedisplay();
}

void setup(int *argc, char **argv)
{
    glutInit(argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Rotating Triangle");
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glutDisplayFunc(draw);

    glClearColor(0, 0, 0, 0);
    glutInitDisplayMode(GL_RGB);
    glEnable(GL_DEPTH_TEST);

    // getting the center of the tetrahedron to the origin
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
            tetrahedron_points[i][j] -= 0.5;
    }

    // init the face colors
    for (int i = 0; i < 4; i++)
        colors[i][0] = colors[i][1] = colors[i][2] = (i + 1) % 5 / 4.0;
}

int main(int argc, char **argv)
{
    printf("Enter the number of steps n : ");
    scanf("%d", &steps);
    setup(&argc, argv);
    glutMainLoop();
}