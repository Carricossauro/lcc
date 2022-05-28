
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <math.h>
#include <vector>


enum Model {plane, box, sphere, cone, cylinder, torus, bezier};

struct Point{
    float x,y,z;
    Point() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    Point(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
};


void normalize(float *a) {
    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}

void cross(float *a, float *b, float *res) {

    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}

std::string generatePlane(float length, int divisions ){


    std::stringstream buffer;
    
    float unit = length / divisions;
    float offset = length / 2;
    float x1, x2, z1, z2;
    float n[3] = {0, 1, 0};

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            x1 = i * unit - offset;
            z1 = j * unit - offset;
            x2 = (i+1) * unit - offset;
            z2 = (j+1) * unit - offset;

            buffer << x1 << ' ' << 0 << ' ' << z1 << '\n';
            buffer << n[0] << ' ' << n[1] << ' ' << n[2] << '\n';

            buffer << x2 << ' ' << 0 << ' ' << z2 << '\n';
            buffer << n[0] << ' ' << n[1] << ' ' << n[2] << '\n';
            
            buffer << x2 << ' ' << 0 << ' ' << z1 << '\n';
            buffer << n[0] << ' ' << n[1] << ' ' << n[2] << '\n';

            
            buffer << x1 << ' ' << 0 << ' ' << z1 << '\n';
            buffer << n[0] << ' ' << n[1] << ' ' << n[2] << '\n';
            
            buffer << x1 << ' ' << 0 << ' ' << z2 << '\n';
            buffer << n[0] << ' ' << n[1] << ' ' << n[2] << '\n';
            
            buffer << x2 << ' ' << 0 << ' ' <<z2 << '\n';
            buffer << n[0] << ' ' << n[1] << ' ' << n[2] << '\n';
        }
    }

    return buffer.str();

}


std::string generateBox(float length, int divisions){

    std::stringstream buffer;

    float unit = length / divisions;
    float offset = length / 2;
    float x1, x2, y1, y2, z1, z2;

    float up[3]     = {0,1,0};
    float down[3]   = {0,-1,0};
    float left[3]   = {-1,0,0};
    float right[3]  = {1,0,0};
    float front[3]  = {0,0,1};
    float back[3]   = {0,0,-1};

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            x1 = i * unit - offset;
            z1 = j * unit - offset;
            x2 = (i+1) * unit - offset;
            z2 = (j+1) * unit - offset;



            buffer << x1 << ' ' << offset << ' ' << z1 << '\n';
            buffer << up[0] << ' ' << up[1] << ' ' << up[2] << '\n';
            
            buffer << x2 << ' ' << offset << ' ' << z2 << '\n';
            buffer << up[0] << ' ' << up[1] << ' ' << up[2] << '\n';
            
            buffer << x2 << ' ' << offset << ' ' << z1 << '\n';
            buffer << up[0] << ' ' << up[1] << ' ' << up[2] << '\n';

            
            buffer << x1 << ' ' << offset << ' ' << z1 << '\n';
            buffer << up[0] << ' ' << up[1] << ' ' << up[2] << '\n';
            
            buffer << x1 << ' ' << offset << ' ' << z2 << '\n';
            buffer << up[0] << ' ' << up[1] << ' ' << up[2] << '\n';
            
            buffer << x2 << ' ' << offset << ' ' << z2 << '\n';
            buffer << up[0] << ' ' << up[1] << ' ' << up[2] << '\n';

            
            buffer << x2 << ' ' << -offset << ' ' << z2 << '\n';
            buffer << down[0] << ' ' << down[1] << ' ' << down[2] << '\n';
            
            buffer << x1 << ' ' << -offset << ' ' << z1 << '\n';
            buffer << down[0] << ' ' << down[1] << ' ' << down[2] << '\n';
            
            buffer << x2 << ' ' << -offset << ' ' << z1 << '\n';
            buffer << down[0] << ' ' << down[1] << ' ' << down[2] << '\n';

            
            buffer << x1 << ' ' << -offset << ' ' << z2 << '\n';
            buffer << down[0] << ' ' << down[1] << ' ' << down[2] << '\n';
            
            buffer << x1 << ' ' << -offset << ' ' << z1 << '\n';
            buffer << down[0] << ' ' << down[1] << ' ' << down[2] << '\n';
            
            buffer << x2 << ' ' << -offset << ' ' << z2 << '\n';
            buffer << down[0] << ' ' << down[1] << ' ' << down[2] << '\n';
        }
    }

    for (int i = 0; i< divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            x1 = i * unit - offset;
            y1 = j * unit - offset;
            x2 = (i+1) * unit - offset;
            y2 = (j+1) * unit - offset;

            
            buffer << x2 << ' ' << y2 << ' ' << offset << '\n';
            buffer << front[0] << ' ' << front[1] << ' ' << front[2] << '\n';
            
            buffer << x1 << ' ' << y1 << ' ' << offset << '\n';
            buffer << front[0] << ' ' << front[1] << ' ' << front[2] << '\n';
            
            buffer << x2 << ' ' << y1 << ' ' << offset << '\n';
            buffer << front[0] << ' ' << front[1] << ' ' << front[2] << '\n';

            
            buffer << x1 << ' ' << y2 << ' ' << offset << '\n';
            buffer << front[0] << ' ' << front[1] << ' ' << front[2] << '\n';
            
            buffer << x1 << ' ' << y1 << ' ' << offset << '\n';
            buffer << front[0] << ' ' << front[1] << ' ' << front[2] << '\n';
            
            buffer << x2 << ' ' << y2 << ' ' << offset << '\n';
            buffer << front[0] << ' ' << front[1] << ' ' << front[2] << '\n';

            
            buffer << x1 << ' ' << y1 << ' ' << -offset << '\n';
            buffer << back[0] << ' ' << back[1] << ' ' << back[2] << '\n';
            
            buffer << x2 << ' ' << y2 << ' ' << -offset << '\n';
            buffer << back[0] << ' ' << back[1] << ' ' << back[2] << '\n';
            
            buffer << x2 << ' ' << y1 << ' ' << -offset << '\n';
            buffer << back[0] << ' ' << back[1] << ' ' << back[2] << '\n';

            
            buffer << x1 << ' ' << y1 << ' ' << -offset << '\n';
            buffer << back[0] << ' ' << back[1] << ' ' << back[2] << '\n';
            
            buffer << x1 << ' ' << y2 << ' ' << -offset << '\n';
            buffer << back[0] << ' ' << back[1] << ' ' << back[2] << '\n';
            
            buffer << x2 << ' ' << y2 << ' ' << -offset << '\n';
            buffer << back[0] << ' ' << back[1] << ' ' << back[2] << '\n';
        }
    }

    for (int i = 0; i< divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            z1 = i * unit - offset;
            y1 = j * unit - offset;
            z2 = (i+1) * unit - offset;
            y2 = (j+1) * unit - offset;

            
            buffer << offset << ' ' << y1 << ' ' << z1 << '\n';
            buffer << right[0] << ' ' << right[1] << ' ' << right[2] << '\n';
            
            buffer << offset << ' ' << y2 << ' ' << z2 << '\n';
            buffer << right[0] << ' ' << right[1] << ' ' << right[2] << '\n';
            
            buffer << offset << ' ' << y1 << ' ' << z2 << '\n';
            buffer << right[0] << ' ' << right[1] << ' ' << right[2] << '\n';

            
            buffer << offset << ' ' << y1 << ' ' << z1 << '\n';
            buffer << right[0] << ' ' << right[1] << ' ' << right[2] << '\n';
            
            buffer << offset << ' ' << y2 << ' ' << z1 << '\n';
            buffer << right[0] << ' ' << right[1] << ' ' << right[2] << '\n';
            
            buffer << offset << ' ' << y2 << ' ' << z2 << '\n';
            buffer << right[0] << ' ' << right[1] << ' ' << right[2] << '\n';

            
            buffer << -offset << ' ' << y2 << ' ' << z2 << '\n';
            buffer << left[0] << ' ' << left[1] << ' ' << left[2] << '\n';
            
            buffer << -offset << ' ' << y1 << ' ' << z1 << '\n';
            buffer << left[0] << ' ' << left[1] << ' ' << left[2] << '\n';
            
            buffer << -offset << ' ' << y1 << ' ' << z2 << '\n';
            buffer << left[0] << ' ' << left[1] << ' ' << left[2] << '\n';

            
            buffer << -offset << ' ' << y2 << ' ' << z1 << '\n';
            buffer << left[0] << ' ' << left[1] << ' ' << left[2] << '\n';
            
            buffer << -offset << ' ' << y1 << ' ' << z1 << '\n';
            buffer << left[0] << ' ' << left[1] << ' ' << left[2] << '\n';
            
            buffer << -offset << ' ' << y2 << ' ' << z2 << '\n';
            buffer << left[0] << ' ' << left[1] << ' ' << left[2] << '\n';
        }
    }


    return buffer.str();

}

std::string generateSphere(float radius, int slices, int stacks){
    
    std::stringstream buffer;
    
    float x1, x2, x3, x4, y1, y2, z1, z2, z3, z4, arch_alfa = 2*M_PI / slices, arch_beta = M_PI / stacks;
    float n[3];
    
    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < stacks; j++) {
            x1 = radius * cos(M_PI_2 - arch_beta * j) * sin(arch_alfa*i);
            x2 = radius * cos(M_PI_2 - arch_beta * (j+1)) * sin(arch_alfa*i);
            x3 = radius * cos(M_PI_2 - arch_beta * (j+1)) * sin(arch_alfa*(i+1));
            x4 = radius * cos(M_PI_2 - arch_beta * j) * sin(arch_alfa*(i+1));

            y1 = radius * sin(M_PI_2 - arch_beta*j);
            y2 = radius * sin(M_PI_2 - arch_beta * (j+1));

            z1 = radius * cos(M_PI_2 - arch_beta * j) * cos(arch_alfa*i);
            z2 = radius * cos(M_PI_2 - arch_beta * (j+1)) * cos(arch_alfa*i);
            z3 = radius * cos(M_PI_2 - arch_beta * (j+1)) * cos(arch_alfa*(i+1));
            z4 = radius * cos(M_PI_2 - arch_beta * j) * cos(arch_alfa*(i+1));


            if (j != stacks-1) {
                
                buffer << x1 << ' ' << y1 << ' ' << z1 << "\n";
                n[0] = x1;
                n[1] = y1;
                n[2] = z1;
                normalize(n);
                buffer << n[0] << ' ' << n[1] << ' ' << n[2] << '\n';
                
                buffer << x2 << ' ' << y2 << ' ' << z2 << '\n';
                n[0] = x2;
                n[1] = y2;
                n[2] = z2;
                normalize(n);
                buffer << n[0] << ' ' << n[1] << ' ' << n[2] << '\n';
                
                buffer << x3 << ' ' << y2 << ' ' << z3 << '\n';
                n[0] = x3;
                n[1] = y2;
                n[2] = z3;
                normalize(n);
                buffer << n[0] << ' ' << n[1] << ' ' << n[2] << '\n';
            }
        
            if (j != 0) {
                
                buffer << x1 << ' ' << y1 << ' ' << z1 << '\n';
                n[0] = x1;
                n[1] = y1;
                n[2] = z1;
                normalize(n);
                buffer << n[0] << ' ' << n[1] << ' ' << n[2] << '\n';
                
                buffer << x3 << ' ' << y2 << ' ' << z3 << '\n';
                n[0] = x3;
                n[1] = y2;
                n[2] = z3;
                normalize(n);
                buffer << n[0] << ' ' << n[1] << ' ' << n[2] << '\n';
                
                buffer << x4 << ' ' << y1 << ' ' << z4 << '\n';
                n[0] = x4;
                n[1] = y1;
                n[2] = z4;
                normalize(n);
                buffer << n[0] << ' ' << n[1] << ' ' << n[2] << '\n';
            }


        }
    }
    
    return buffer.str();

}




std::string generateCone(float radius, float height, int slices, int stacks ){
    
    std::stringstream buffer;

    float arch_alfa = 2*M_PI / slices,ratio = height/radius, stack_size = height/stacks;
    float x1, x2, x3, x4, y1, y2, z1, z2, z3, z4, h1, h2, r1, r2;


    for (int i = 0; i < slices; i++) {
        x1 = radius * sin(arch_alfa * i);
        x2 = radius * sin(arch_alfa * (i+1));
        z1 = radius * cos(arch_alfa * i);
        z2 = radius * cos(arch_alfa * (i+1));

        
        buffer << x1 << ' ' << 0 << ' ' << z1 << '\n';
        
        buffer << 0 << ' ' << 0 << ' ' << 0 << '\n';
        
        buffer << x2 << ' ' << 0 << ' ' << z2 << '\n';
    }

    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            h1 = height - (i * stack_size);
            h2 = height - ((i+1) * stack_size);
            r1 = h1 / ratio;
            r2 = h2 / ratio;

            x1 = r1 * sin(arch_alfa * j);
            x2 = r1 * sin(arch_alfa * (j+1));
            x3 = r2 * sin(arch_alfa * (j+1));
            x4 = r2 * sin(arch_alfa * j);
            y1 = (i * stack_size);
            y2 = (i+1) * stack_size;
            z1 = r1 * cos(arch_alfa * j);
            z2 = r1 * cos(arch_alfa * (j+1));
            z3 = r2 * cos(arch_alfa * (j+1));
            z4 = r2 * cos(arch_alfa * j);

            buffer << x1 << ' ' << y1 << ' ' << z1 << '\n';

            buffer << x2 << ' ' << y1 << ' ' << z2 << '\n';

            buffer << x4 << ' ' << y2 << ' ' << z4 << '\n';

            if (i != stacks - 1) {
                
                buffer << x4 << ' ' << y2 << ' ' << z4 << '\n';
                
                buffer << x2 << ' ' << y1 << ' ' << z2 << '\n';
                
                buffer << x3 << ' ' << y2 << ' ' << z3 << '\n';
            }            

        }
    }


    return buffer.str();
}

std::string generateCylinder(float radius, float height, int slices, int stacks){

    std::stringstream buffer;

    float arch_alfa = 2*M_PI / slices, stack_size = height/stacks;
    float x1, x2, y1, y2, z1, z2;


    for (int i = 0; i < slices; i++) {
        x1 = radius * sin(arch_alfa * i);
        x2 = radius * sin(arch_alfa * (i+1));
        z1 = radius * cos(arch_alfa * i);
        z2 = radius * cos(arch_alfa * (i+1));

        buffer << x1 << ' ' << 0 << ' ' << z1 << '\n';
        
        buffer << 0 << ' ' << 0 << ' ' << 0 << '\n';
        
        buffer << x2 << ' ' << 0 << ' ' << z2 << '\n';

        
        buffer << 0 << ' ' << height << ' ' << 0 << '\n';
    
        buffer << x1 << ' ' << height << ' ' << z1 << '\n';
        
        buffer << x2 << ' ' << height << ' ' << z2 << '\n';

        for (int j = 0; j < stacks; j++){
            y1 = (j * stack_size);
            y2 = (j+1) * stack_size;

            
            buffer << x1 << ' ' << y1 << ' ' << z1 << '\n';
            
            buffer << x2 << ' ' << y1 << ' ' << z2 << '\n';
            
            buffer << x1 << ' ' << y2 << ' ' << z1 << '\n';

            
            buffer << x2 << ' ' << y2 << ' ' << z2 << '\n';
            
            buffer << x1 << ' ' << y2 << ' ' << z1 << '\n';
            
            buffer << x2 << ' ' << y1 << ' ' << z2 << '\n';
        }

    }

    return buffer.str();
}

std::string generateTorus(float R, float r, int slices, int stacks) {
    std::stringstream buffer;

    float arch_alpha = (2 * M_PI) / stacks, arch_beta = (2 * M_PI) / slices;
    float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;

    R = (R + r) / 2;
    r = R - r;

    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            x1 = (R + r * cos(arch_alpha * i)) * cos(arch_beta * j);
            x2 = (R + r * cos(arch_alpha * (i+1))) * cos(arch_beta * j);
            x3 = (R + r * cos(arch_alpha * (i+1))) * cos(arch_beta * (j+1));
            x4 = (R + r * cos(arch_alpha * i)) * cos(arch_beta * (j+1));

            y1 = r * sin(arch_alpha * i);
            y2 = r * sin(arch_alpha * (i+1));
            y3 = r * sin(arch_alpha * (i+1));
            y4 = r * sin(arch_alpha * i);

            z1 = (R + r * cos(arch_alpha * i)) * sin(arch_beta * j);
            z2 = (R + r * cos(arch_alpha * (i+1))) * sin(arch_beta * j);
            z3 = (R + r * cos(arch_alpha * (i+1))) * sin(arch_beta * (j+1));
            z4 = (R + r * cos(arch_alpha * i)) * sin(arch_beta * (j+1));

            buffer << x1 << ' ' << y1 << ' ' << z1 << '\n';
            
            buffer << x2 << ' ' << y2 << ' ' << z2 << '\n';
        
            buffer << x4 << ' ' << y4 << ' ' << z4 << '\n';

            
            buffer << x2 << ' ' << y2 << ' ' << z2 << '\n';
        
            buffer << x3 << ' ' << y3 << ' ' << z3 << '\n';
            
            buffer << x4 << ' ' << y4 << ' ' << z4 << '\n';

        }
    }
    
    return buffer.str();
}

void multMatrixVector(float m[4][4], float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j][k];
        }
    }

}

void multMatrixMatrix(float a[4][4], float b[4][4], float res[4][4]){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++){
            res[i][j] = 0;
            for(int k = 0; k < 4; k++)
                res[i][j] += a[i][k] * b[k][j];
        }
}

float B(float U, float V, float m[4][4]){

    float aux[4];
    float v[4];
    float r;

    v[0] = powf(V,3);
    v[1] = powf(V,2);
    v[2] = V;
    v[3] = 1;

    multMatrixVector(m,v,aux);

    r = powf(U,3)*aux[0] + powf(U,2)*aux[1] + U*aux[2] + aux[3];



    return r;

}

float Du(float U, float V, float m[4][4]){

    float aux[4];
    float v[4];
    float r;

    v[0] = powf(V,3);
    v[1] = powf(V,2);
    v[2] = V;
    v[3] = 1;

    multMatrixVector(m,v,aux);

    r = 3*powf(U,2)*aux[0] + 2*U*aux[1] + aux[2];



    return r;

}

float Dv(float U, float V, float m[4][4]){

    float aux[4];
    float v[4];
    float r;

    v[0] = 3*powf(V,2);
    v[1] = V*2;
    v[2] = 1;
    v[3] = 0;

    multMatrixVector(m,v,aux);

    r = powf(U,3)*aux[0] + powf(U,2)*aux[1] + U*aux[2] + aux[3];



    return r;

}

std::string generateSurface(float mx[4][4], float my[4][4], float mz[4][4], int tesselation){
    std::stringstream buffer;
    float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;
    float p1u[3], p1v[3], p1n[3], p2u[3], p2v[3], p2n[3], p3u[3], p3v[3], p3n[3], p4u[3], p4v[3], p4n[3];
    float tesselation_level = 1.0/tesselation;

    for(float i=0; i<1; i+=tesselation_level){
        for(float j=0; j<1; j+=tesselation_level){
            x1 = B(i,j,mx);
            p1u[0] = Du(i,j,mx);
            p1v[0] = Dv(i,j,mx);

            x2 = B(i+tesselation_level,j,mx);
            p2u[0] = Du(i+tesselation_level,j,mx);
            p2v[0] = Dv(i+tesselation_level,j,mx);

            x3 = B(i+tesselation_level,j+tesselation_level,mx);
            p3u[0] = Du(i+tesselation_level,j+tesselation_level,mx);
            p3v[0] = Dv(i+tesselation_level,j+tesselation_level,mx);

            x4 = B(i,j+tesselation_level,mx);
            p4u[0] = Du(i,j+tesselation_level,mx);
            p4v[0] = Dv(i,j+tesselation_level,mx);

            y1 = B(i,j,my);
            p1u[1] = Du(i,j,my);
            p1v[1] = Dv(i,j,my);

            y2 = B(i+tesselation_level,j,my);
            p2u[1] = Du(i+tesselation_level,j,my);
            p2v[1] = Dv(i+tesselation_level,j,my);


            y3 = B(i+tesselation_level,j+tesselation_level,my);
            p3u[1] = Du(i+tesselation_level,j+tesselation_level,my);
            p3v[1] = Dv(i+tesselation_level,j+tesselation_level,my);
            
            y4 = B(i,j+tesselation_level,my);
            p4u[1] = Du(i,j+tesselation_level,my);
            p4v[1] = Dv(i,j+tesselation_level,my);

            z1 = B(i,j,mz);
            p1u[2] = Du(i,j,mz);
            p1v[2] = Dv(i,j,mz);

            z2 = B(i+tesselation_level,j,mz);
            p2u[2] = Du(i+tesselation_level,j,mz);
            p2v[2] = Dv(i+tesselation_level,j,mz);

            z3 = B(i+tesselation_level,j+tesselation_level,mz);
            p3u[2] = Du(i+tesselation_level,j+tesselation_level,mz);
            p3v[2] = Dv(i+tesselation_level,j+tesselation_level,mz);

            z4 = B(i,j+tesselation_level,mz);
            p4u[2] = Du(i,j+tesselation_level,mz);
            p4v[2] = Dv(i,j+tesselation_level,mz);


            cross(p1u,p1v,p1n);
            cross(p2u,p2v,p2n);
            cross(p3u,p3v,p3n);
            cross(p4u,p4v,p4n);

            normalize(p1n);
            normalize(p2n);
            normalize(p3n);
            normalize(p4n);

            //p1n[0] = 1;
            //p1n[1] = 1;
            //p1n[2] = 1;
            //p2n[0] = 1;
            //p2n[1] = 1;
            //p2n[2] = 1;
            //p3n[0] = 1;
            //p3n[1] = 1;
            //p3n[2] = 1;
            //p4n[0] = 1;
            //p4n[1] = 1;
            //p4n[2] = 1;


            buffer << x1 << ' ' << y1 << ' ' << z1 << '\n';

            buffer << p1n[0] << ' ' << p1n[1] << ' ' << p1n[2] << '\n';


            buffer << x2 << ' ' << y2 << ' ' << z2 << '\n';

            buffer << p2n[0] << ' ' << p2n[1] << ' ' << p2n[2] << '\n';


            buffer << x3 << ' ' << y3 << ' ' << z3 << '\n';

            buffer << p3n[0] << ' ' << p3n[1] << ' ' << p3n[2] << '\n';

            
            
            buffer << x3 << ' ' << y3 << ' ' << z3 << '\n';

            buffer << p3n[0] << ' ' << p3n[1] << ' ' << p3n[2] << '\n';

            buffer << x4 << ' ' << y4 << ' ' << z4 << '\n';

            buffer << p4n[0] << ' ' << p4n[1] << ' ' << p4n[2] << '\n';

            
            buffer << x1 << ' ' << y1 << ' ' << z1 << '\n';

            buffer << p1n[0] << ' ' << p1n[1] << ' ' << p1n[2] << '\n';

            
            

            


            

            
            
            


            

            

            
            
                        

        }
    }

    return buffer.str();

}

std::string generateBezier(const char input[], int tesselation){
    std::stringstream buffer;
    std::ifstream fp(std::string("patch/") + input);
    std::vector<std::vector<int>> indices;
    std::vector<Point> points;
    float mx[4][4];
    float my[4][4];
    float mz[4][4];
    int num_patches, num_points;
    float bezierMat[4][4] = {{-1.0f,  3.0f, -3.0f, 1.0f},
                             { 3.0f, -6.0f,  3.0f, 0.0f},
                             {-3.0f,  3.0f,  0.0f, 0.0f},
                             { 1.0f,  0.0f,  0.0f, 0.0f}};
    


    fp >> num_patches;

    for(int i=0; i<num_patches; i++){
        std::vector<int> v;
        int p;
        std::string comma;
        for (int j=0; j<16; j++){
            fp >> p;
            if(j!=15)
                fp>>comma;
            v.push_back(p);
        }
        indices.push_back(v);
    }

    fp >> num_points;

    for(int i=0; i<num_points; i++){
        float x,y,z;
        std::string comma;
        fp >> x; 
        fp >> comma; 
        fp >> y;
        fp >> comma; 
        fp >> z;

        points.push_back(Point(x,y,z));
    }

    float aux[4][4];

    

    for(std::vector<int> indice: indices){
        for(int i=0; i<4; i++){
            for(int j = 0; j<4; j++){
                mx[j][i] = points[indice[i*4+j]].x;
                my[j][i] = points[indice[i*4+j]].y;
                mz[j][i] = points[indice[i*4+j]].z;
            }
        }
        multMatrixMatrix(bezierMat,mx,aux);
        multMatrixMatrix(aux,bezierMat,mx);

        multMatrixMatrix(bezierMat,my,aux);
        multMatrixMatrix(aux,bezierMat,my);

        multMatrixMatrix(bezierMat,mz,aux);
        multMatrixMatrix(aux,bezierMat,mz);

        buffer << generateSurface(mx,my,mz,tesselation);

    }
        

    return buffer.str();
}




int isInt(const char number[]){
    int r = 1;
    for(int i=0; number[i] && r; i++){
        if(! std::isdigit(number[i]))
            r=0;
    }

    return r;
}



int isFloat(const char number[]){
    int r = 1;
    int comma = 0;
    for(int i=0; number[i] && r; i++){
        if ((number[i] == '.' || number[i] == ',') && i == 0)
            r = 0;
        else if(number[i] == '.' || number[i] == ',')
            comma++;
        else if(! std::isdigit(number[i]))
            r=0;
        if (comma >1)
            r = 0;
    }

    return r;

}


// seleciona qual o modelo a criar
int selectModel(int argc, char const *argv[]){
    int r;
    if(argc <=1)
        r = -1;
    else if( strcmp((argv[1]),"plane") == 0  && argc == 5 && isFloat(argv[2]) && isInt(argv[3]))
        r = plane;
    else if(strcmp((argv[1]),"box") == 0 && argc == 5 && isFloat(argv[2]) && isInt(argv[3]))
        r = box;
    else if(strcmp((argv[1]),"sphere") == 0 && argc == 6 && isFloat(argv[2]) && isInt(argv[3]) && isInt(argv[4]))
        r =  sphere;
    else if(strcmp((argv[1]),"cone") == 0 && argc == 7 && isFloat(argv[2]) && isFloat(argv[3]) && isInt(argv[4]) && isInt(argv[5]))
        r = cone;
    else if(strcmp((argv[1]),"cylinder") == 0 && argc == 7 && isFloat(argv[2]) && isFloat(argv[3]) && isInt(argv[4]) && isInt(argv[5]))
        r = cylinder;
    else if(strcmp((argv[1]),"torus") == 0 && argc == 7 && isFloat(argv[2]) && isFloat(argv[3]) && isInt(argv[4]) && isInt(argv[5]))
        r = torus;
    else if(strcmp((argv[1]),"bezier") == 0 && argc == 5 && isInt(argv[3]))
    {
        std::ifstream fp(std::string("patch/") + argv[2]);
        if(!fp)
            r = -1;
        else{
            r = bezier;
            fp.close();
        }
    }
    else
        r = -1;

    return r;
    
}






int main(int argc, char const *argv[])
{
    
    int option = selectModel(argc, argv);
    
    if(option==-1){
        std::cout <<"error: Invalid arguments! Supported syntax:\n";
        std::cout <<"* plane [length] [divisions] [output file]\n";
        std::cout <<"* box [length] [divisions] [output file]\n";
        std::cout <<"* sphere [radius] [slices] [stacks] [output file]\n";
        std::cout <<"* cone [radius] [height] [slices] [stacks] [output file]\n";
        std::cout <<"* cylinder [radius] [height] [slices] [stacks] [output file]\n";
        std::cout <<"* torus [Radius] [thickness] [slices] [stacks] [output file]\n";
        std::cout <<"* bezier [patch file] [tesselations] [output file]\n";

        return 0;
    }


    std::ofstream fp(std::string("3d/") + argv[argc-1]);

    if(!fp){
        std::cout <<"error: Opening file " << argv[argc-1] <<"\n";
        return 0;
    }

    std::cout <<"Processing...";

    switch(option){
        case plane:
            fp << generatePlane(std::stof(argv[2]),std::stoi(argv[3]));
            break;
        case box:
            fp << generateBox(std::stof(argv[2]),std::stoi(argv[3]));
            break;
        case sphere:
            fp << generateSphere(std::stof(argv[2]),std::stoi(argv[3]),std::stoi(argv[4]));
            break;
        case cone:
            fp << generateCone(std::stof(argv[2]),std::stof(argv[3]),std::stoi(argv[4]),std::stoi(argv[5]));
            break;
        case cylinder:
            fp << generateCylinder(std::stof(argv[2]),std::stof(argv[3]),std::stoi(argv[4]), std::stoi(argv[5]));
            break;
        case torus:
            fp << generateTorus(std::stof(argv[2]),std::stof(argv[3]),std::stoi(argv[4]), std::stoi(argv[5]));
            break;
        case bezier:
            fp << generateBezier(argv[2],std::stoi(argv[3]));
        default:
            break;
    }

    std::cout <<"Done\n";
    

    fp.close();
    
    

    return 0;
}