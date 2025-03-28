float cube[9][3] = {
    {1, 1, 1},
    {1, -1, 1},
    {-1, -1, 1},
    {-1, 1, 1},
    {-1, 1, -1},
    {-1, -1, -1},
    {1, -1, -1},
    {1, 1, -1}};

float *cube_quads[6][4] = {
    {cube[0], cube[1], cube[2], cube[3]},
    {cube[0], cube[7], cube[6], cube[1]},
    {cube[0], cube[3], cube[4], cube[7]},

    {cube[5], cube[4], cube[3], cube[2]},
    {cube[5], cube[2], cube[1], cube[6]},
    {cube[5], cube[6], cube[7], cube[4]},
};