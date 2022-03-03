
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <math.h>

std::ofstream file;

enum Model {plane, box, sphere, cone};


void generatePlane(float length, int divisions ){


    std::stringstream output;
    
    float unit = length / divisions;
    float offset = length / 2;
    float x1, x2, z1, z2;

    //glBegin(GL_TRIANGLES);
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            x1 = i * unit - offset;
            z1 = j * unit - offset;
            x2 = (i+1) * unit - offset;
            z2 = (j+1) * unit - offset;

            //glVertex3f(x1, 0, z1);
            output << x1 << ' ' << 0 << ' ' << z1 << '\n';
            //glVertex3f(x2, 0, z2);
            output << x2 << ' ' << 0 << ' ' << z2 << '\n';
            //glVertex3f(x2, 0, z1);
            output << x2 << ' ' << 0 << ' ' << z1 << '\n';

            //glVertex3f(x1, 0, z1);
            output << x1 << ' ' << 0 << ' ' << z1 << '\n';
            //glVertex3f(x1, 0, z2);
            output << x1 << ' ' << 0 << ' ' << z2 << '\n';
            //glVertex3f(x2, 0, z2);
            output << x2 << ' ' << 0 << ' ' <<z2 << '\n';
        }
    }
    //glEnd();

    file << output.str();

}



void generateBox(float length, int divisions){

    std::stringstream output;

    float unit = length / divisions;
    float offset = length / 2;
    float x1, x2, y1, y2, z1, z2;

    //glBegin(GL_TRIANGLES);
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            x1 = i * unit - offset;
            z1 = j * unit - offset;
            x2 = (i+1) * unit - offset;
            z2 = (j+1) * unit - offset;

            //glVertex3f(x1, offset, z1);
            output << x1 << ' ' << offset << ' ' << z1 << '\n';
            //glVertex3f(x2, offset, z2);
            output << x2 << ' ' << offset << ' ' << z2 << '\n';
            //glVertex3f(x2, offset, z1);
            output << x2 << ' ' << offset << ' ' << z1 << '\n';

            //glVertex3f(x1, offset, z1);
            output << x1 << ' ' << offset << ' ' << z1 << '\n';
            //glVertex3f(x1, offset, z2);
            output << x1 << ' ' << offset << ' ' << z2 << '\n';
            //glVertex3f(x2, offset, z2);
            output << x2 << ' ' << offset << ' ' << z2 << '\n';

            //glVertex3f(x2, -offset, z2);
            output << x2 << ' ' << -offset << ' ' << z2 << '\n';
            //glVertex3f(x1, -offset, z1);
            output << x1 << ' ' << -offset << ' ' << z1 << '\n';
            //glVertex3f(x2, -offset, z1);
            output << x2 << ' ' << -offset << ' ' << z1 << '\n';

            //glVertex3f(x1, -offset, z2);
            output << x1 << ' ' << -offset << ' ' << z2 << '\n';
            //glVertex3f(x1, -offset, z1);
            output << x1 << ' ' << -offset << ' ' << z1 << '\n';
            //glVertex3f(x2, -offset, z2);
            output << x2 << ' ' << -offset << ' ' << z2 << '\n';
        }
    }

    for (int i = 0; i< divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            x1 = i * unit - offset;
            y1 = j * unit - offset;
            x2 = (i+1) * unit - offset;
            y2 = (j+1) * unit - offset;

            //glVertex3f(x2, y2, offset);
            output << x2 << ' ' << y2 << ' ' << offset << '\n';
            //glVertex3f(x1, y1, offset);
            output << x1 << ' ' << y1 << ' ' << offset << '\n';
            //glVertex3f(x2, y1, offset);
            output << x2 << ' ' << y1 << ' ' << offset << '\n';

            //glVertex3f(x1, y2, offset);
            output << x1 << ' ' << y2 << ' ' << offset << '\n';
            //glVertex3f(x1, y1, offset);
            output << x1 << ' ' << y1 << ' ' << offset << '\n';
            //glVertex3f(x2, y2, offset);
            output << x2 << ' ' << y2 << ' ' << offset << '\n';

            //glVertex3f(x1, y1, -offset);
            output << x1 << ' ' << y1 << ' ' << -offset << '\n';
            //glVertex3f(x2, y2, -offset);
            output << x2 << ' ' << y2 << ' ' << -offset << '\n';
            //glVertex3f(x2, y1, -offset);
            output << x2 << ' ' << y1 << ' ' << -offset << '\n';

            //glVertex3f(x1, y1, -offset);
            output << x1 << ' ' << y1 << ' ' << -offset << '\n';
            //glVertex3f(x1, y2, -offset);
            output << x1 << ' ' << y2 << ' ' << -offset << '\n';
            //glVertex3f(x2, y2, -offset);
            output << x2 << ' ' << y2 << ' ' << -offset << '\n';
        }
    }

    for (int i = 0; i< divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            z1 = i * unit - offset;
            y1 = j * unit - offset;
            z2 = (i+1) * unit - offset;
            y2 = (j+1) * unit - offset;

            //glVertex3f(offset, y1, z1);
            output << offset << ' ' << y1 << ' ' << z1 << '\n';
            //glVertex3f(offset, y2, z2);
            output << offset << ' ' << y2 << ' ' << z2 << '\n';
            //glVertex3f(offset, y1, z2);
            output << offset << ' ' << y1 << ' ' << z2 << '\n';

            //glVertex3f(offset, y1, z1);
            output << offset << ' ' << y1 << ' ' << z1 << '\n';
            //glVertex3f(offset, y2, z1);
            output << offset << ' ' << y2 << ' ' << z1 << '\n';
            //glVertex3f(offset, y2, z2);
            output << offset << ' ' << y2 << ' ' << z2 << '\n';

            //glVertex3f(-offset, y2, z2);
            output << -offset << ' ' << y2 << ' ' << z2 << '\n';
            //glVertex3f(-offset, y1, z1);
            output << -offset << ' ' << y1 << ' ' << z1 << '\n';
            //glVertex3f(-offset, y1, z2);
            output << -offset << ' ' << y1 << ' ' << z2 << '\n';

            //glVertex3f(-offset, y2, z1);
            output << -offset << ' ' << y2 << ' ' << z1 << '\n';
            //glVertex3f(-offset, y1, z1);
            output << -offset << ' ' << y1 << ' ' << z1 << '\n';
            //glVertex3f(-offset, y2, z2);
            output << -offset << ' ' << y2 << ' ' << z2 << '\n';
        }
    }

    //glEnd();

    file << output.str();

}



void generateSphere(float radius, int slices, int stacks){
    std::stringstream output;
    float x1, x2, x3, x4, y1, y2, z1, z2, z3, z4, arch_alfa = 2*M_PI / slices, arch_beta = M_PI / stacks;

    //glBegin(GL_TRIANGLES);
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

            if(j!=stacks-1) {
                //glVertex3f(x1, y1, z1);
                output << x1 << ' ' << y1 << ' ' << z1 << '\n';
                //glVertex3f(x2, y2, z2);
                output << x2 << ' ' << y2 << ' ' << z2 << '\n';
                //glVertex3f(x3, y2, z3);
                output << x3 << ' ' << y2 << ' ' << z3 << '\n';
            }
            if(j!=0){
                //glVertex3f(x1, y1, z1);
                output << x1 << ' ' << y1 << ' ' << z1 << '\n';
                //glVertex3f(x3, y2, z3);
                output << x3 << ' ' << y2 << ' ' << z3 << '\n';
                //glVertex3f(x4, y1, z4);
                output << x4 << ' ' << y1 << ' ' << z4 << '\n';

            }

        }
    }
    //glEnd();
    
    file << output.str();

}


void generateCone(float radius, float height, int slices, int stacks ){
    
    std::stringstream output;

    float arch_alfa = 2*M_PI / slices,ratio = height/radius, stack_size = height/stacks;
    float x1, x2, x3, x4, y1, y2, z1, z2, z3, z4, h1, h2, r1, r2;

    //glBegin(GL_TRIANGLES);
    for (int i = 0; i < slices; i++) {
        x1 = radius * sin(arch_alfa * i);
        x2 = radius * sin(arch_alfa * (i+1));
        z1 = radius * cos(arch_alfa * i);
        z2 = radius * cos(arch_alfa * (i+1));

        //glVertex3f(x1, 0, z1);
        output << x1 << ' ' << 0 << ' ' << z1 << '\n';
        //glVertex3f(0, 0, 0);
        output << 0 << ' ' << 0 << ' ' << 0 << '\n';
        //glVertex3f(x2, 0, z2);
        output << x2 << ' ' << 0 << ' ' << z2 << '\n';
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
            y1 = height - h1;
            y2 = height - h2;
            z1 = r1 * cos(arch_alfa * j);
            z2 = r1 * cos(arch_alfa * (j+1));
            z3 = r2 * cos(arch_alfa * (j+1));
            z4 = r2 * cos(arch_alfa * j);

            //glVertex3f(x1, y1, z1);
            output << x1 << ' ' << y1 << ' ' << z1 << '\n';
            //glVertex3f(x2, y1, z2);
            output << x2 << ' ' << y1 << ' ' << z2 << '\n';
            //glVertex3f(x4, y2, z4);
            output << x4 << ' ' << y2 << ' ' << z4 << '\n';

            //if (i!=stacks-1){
                //glVertex3f(x4, y2, z4);
                output << x4 << ' ' << y2 << ' ' << z4 << '\n';
                //glVertex3f(x2, y1, z2);
                output << x2 << ' ' << y1 << ' ' << z2 << '\n';
                //glVertex3f(x3, y2, z3);
                output << x3 << ' ' << y2 << ' ' << z3 << '\n';

            //}
        }
    }

    //glEnd();

    file << output.str();
}


// seleciona qual o modelo a criar
int selectModel(int argc, char const *argv[]){
    int r;
    if(argc <=1)
        r = -1;
    else if( strcmp((argv[1]),"plane") == 0   && argc == 5)
        r = plane;
    else if(strcmp((argv[1]),"box") == 0 && argc == 5)
        r = box;
    else if(strcmp((argv[1]),"sphere") == 0 && argc == 6)
        r =  sphere;
    else if(strcmp((argv[1]),"cone") == 0 && argc == 7)
        r = cone;
    else
        r = -1;

    return r;
    
}



int main(int argc, char const *argv[])
{
    

    int choice = selectModel(argc, argv);
    
    if(choice==-1){
        std::cout <<"error: Invalid arguments! Supported syntax:\n";
        std::cout <<"* plane [length] [divisions] [output file]\n";
        std::cout <<"* box [length] [divisions] [output file]\n";
        std::cout <<"* sphere [radius] [slices] [stacks] [output file]\n";
        std::cout <<"* cone [radius] [height] [slices] [stacks] [output file]\n";

        return 0;
    }


    file.open( std::string("3d/") + argv[argc-1]);

    if(!file){
        std::cout <<"error: Opening file " << argv[argc-1] <<"\n";
        return 0;
    }

    std::cout <<"Processing...";

    switch(choice){
        case plane:
            generatePlane(std::stof(argv[2]),std::stof(argv[3]));
            break;
        case box:
            generateBox(std::stof(argv[2]),std::stof(argv[3]));
            break;
        case sphere:
            generateSphere(std::stof(argv[2]),std::stof(argv[3]),std::stof(argv[4]));
            break;
        case cone:
            generateCone(std::stof(argv[2]),std::stof(argv[3]),std::stof(argv[4]),std::stof(argv[5]));
            break;
        default:
            break;

    }

    std::cout <<"Done\n";
    

    file.close();
    
    

    return 0;
}