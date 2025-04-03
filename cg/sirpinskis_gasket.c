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

void copy_array(float src[], float dest[], int n)
{
    for (int i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }
}

void draw_gasket_face(float** points, int n)
{
    if (n <= 0)
    {
        for (int i = 0; i < 3; i++)
        {
            glVertex3f(points[i][0], points[i][1], points[i][2]);
        }
    }
    else
    {
        float **mid = (float **)malloc(3 * sizeof(float *));
        float ***new_triangles = (float ***)malloc(3 * sizeof(float **));
        for (int i = 0; i < 3; i++)
        {
            mid[i] = (float *)malloc(3 * sizeof(float));
            new_triangles[i] = (float **)malloc(3 * sizeof(float *));
            for (int j = 0; j < 3; j++)
            {
                new_triangles[i][j] = (float *)malloc(3 * sizeof(float));
            }
        }


        for (int i = 0; i < 3; i++)
        {
            mid[i][0] = (points[i][0] + points[(i + 1) % 3][0]) / 2;
            mid[i][1] = (points[i][1] + points[(i + 1) % 3][1]) / 2;
            mid[i][2] = (points[i][2] + points[(i + 1) % 3][2]) / 2;
        }

        copy_array(points[0], new_triangles[0][0], 3);
        copy_array(mid[0], new_triangles[0][1], 3);
        copy_array(mid[2], new_triangles[0][2], 3);

        copy_array(mid[0], new_triangles[1][0], 3);
        copy_array(points[1], new_triangles[1][1], 3);
        copy_array(mid[1], new_triangles[1][2], 3);

        copy_array(mid[1], new_triangles[2][0], 3);
        copy_array(points[2], new_triangles[2][1], 3);
        copy_array(mid[2], new_triangles[2][2], 3);

        draw_gasket_face(new_triangles[0], n - 1);
        draw_gasket_face(new_triangles[1], n - 1);
        draw_gasket_face(new_triangles[2], n - 1);
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

    float ** points = (float **)malloc(3 * sizeof(float *));
    for (int i = 0; i < 3; i++)
    {
        points[i] = (float *)malloc(3 * sizeof(float));
    }

    for (int i = 0; i < 4; i++)
    {
        int next_i = (i + 1) % 4, next_next_i = (i + 2) % 4;

        glColor3f((i + 1) % 5 / 4.0, (i + 1) % 5 / 4.0, (i + 1) % 5 / 4.0);
        glBegin(GL_TRIANGLES);

        copy_array(tetrahedron_points[i], points[0], 3);
        copy_array(tetrahedron_points[next_i], points[1], 3);
        copy_array(tetrahedron_points[next_next_i], points[2], 3);

        draw_gasket_face(points, steps);

        glEnd();
    }
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
}

int main(int argc, char **argv)
{
    printf("Enter the number of steps n : ");
    scanf("%d", &steps);
    setup(&argc, argv);
    glutMainLoop();
}