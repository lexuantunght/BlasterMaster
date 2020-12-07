#include "Scene.h"
#include <fstream>
#include <string>
#include <vector>

Scene::Scene()
{
    mBackColor = 0x4866ff;

    LoadContent();
}

Scene::~Scene()
{
    
}

void Scene::Update(float dt)
{

}

void Scene::LoadContent()
{

}

void Scene::SaveData(int missile, int thunder, int rocket, int sel, int gun)
{
    std::ofstream myfile("Assets/modalBullet.txt");
    if (myfile.is_open())
    {
        myfile << missile << " " << thunder << " " << rocket << " " << sel << " " << gun;
        myfile.close();
    }
}

const std::vector<std::string> explodeCut(const std::string& s, const char& c)
{
    std::string buff{ "" };
    std::vector<std::string> v;

    for (auto n : s)
    {
        if (n != c) buff += n; else
            if (n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if (buff != "") v.push_back(buff);

    return v;
}

int* Scene::LoadData()
{
    std::fstream f;
    f.open("Assets/modalBullet.txt", std::ios::in);
    int* a = new int[5];
    while (!f.eof())
    {
        std::string line;
        std::getline(f, line);
        std::vector<std::string> info = { explodeCut(line, ' ') };
        a[0] = stoi(info[0]);
        a[1] = stoi(info[1]);
        a[2] = stoi(info[2]);
        a[3] = stoi(info[3]);
        a[4] = stoi(info[4]);
    }
    f.close();
    return a;
}

void Scene::Draw()
{

}

void Scene::OnKeyDown(int keyCode)
{

}

void Scene::OnKeyUp(int keyCode)
{

}

void Scene::OnMouseDown(float x, float y)
{

}

D3DCOLOR Scene::GetBackcolor()
{
    return mBackColor;
}