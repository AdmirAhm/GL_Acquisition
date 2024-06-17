#pragma once
#include <gui/gl/View.h>
#include <gui/Key.h>
#include <gui/Texture.h>
#include <gui/FileDialog.h>
#include "Program.h"
#include <gui/gl/CommandList.h>
#include <gui/gl/Buffer.h>
#include <gui/gl/Textures.h>
#include "global.h";
#include <queue>
#include "Cube.h"



class GLView : public gui::gl::View
{
    using Base = gui::gl::View;
    glm::mat4 _perspectiveMatrix;
    glm::mat4 _viewMatrix;
    glm::mat4 _mvpMatrix;
    glm::mat4 _measure;
    std::vector<std::queue<float> >filter;
    std::vector<float> sumfilter;

    std::vector<Cube>_insts;
    int _nInstances = 0;
    
    gui::gl::Buffer _gpuBuffer;
    
    Program _program;
    gui::gl::Command* pMtxSetterCmd = nullptr;
    gui::gl::Command* pCubeTextureCmd = nullptr;
    
    float _angleX = 0;
    float _angleY = 0;
    float _dAngle = 0.01f;
    
    td::BYTE _usedTexture = 0; //0 or 1
private:
    bool setupShaders()
    {
        if (!_program.link(":shVert", ":shFrag"))
            return false;
        return true;
    }
    
    void setup()
    {
        pMtxSetterCmd = _gpuBuffer.createCommand();
        pMtxSetterCmd->createMVPSetter(&_mvpMatrix);
        _gpuBuffer.encode(pMtxSetterCmd);

        /*float instanceData[] =
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         1.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0, 0.0f, 0.0f, 0,
         3.1415 / 20.0, 1.0f, 3.1415 / 20.0, 1.0f, 1.0f, 1.0f, 0.2f, 0.2f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 1.0f,
         0, 0, 0, 0.0f, 0.0f, 0, 1.0f, 2.0f, 0,
         1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.2f, 0.2f, 1.0f };*/
        float *instanceData = new float[_nInstances * 27];
        int i = 0;
        for (auto cube : _insts) {
            while (cube.params.size() < 27) cube.params.emplace_back(0.0f);
            for (int j = 0; j < 27; j++) {
                instanceData[i * 27 + j] = cube.params[j];
            }
            i++;
        }

        float vertices[] = {
            0.5f,   0.5f,  0.5f,  
           -0.5f,   0.5f,  0.5f,     
           -0.5f,  -0.5f,  0.5f,     
            0.5f,  -0.5f,  0.5f,    

            0.5f, -0.5f,  0.5f, 
            0.5f, -0.5f, -0.5f, 
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, 0.5f, 
            
            0.5f, -0.5f, -0.5f, 
           -0.5f, -0.5f, -0.5f,   
           -0.5f,  0.5f, -0.5f,  
            0.5f,  0.5f, -0.5f,  

           -0.5f, -0.5f, -0.5f, 
           -0.5f,  -0.5f, 0.5f, 
           -0.5f,  0.5f,  0.5f,  
           -0.5f,  0.5f, -0.5f,  

           -0.5f,  0.5f,  0.5f,  
            0.5f,  0.5f,  0.5f, 
            0.5f,  0.5f, -0.5f, 
           -0.5f,  0.5f, -0.5f,  

           -0.5f, -0.5f, -0.5f,  
            0.5f, -0.5f, -0.5f,    
            0.5f, -0.5f,  0.5f,  
           -0.5f, -0.5f,  0.5f
        };
        
        td::UINT4 indices[] =
        {
            0, 1, 2, 
            2, 3, 0,

            4, 5, 6, 
            4, 6, 7, 

            8, 9, 11, 
            9, 10, 11, 

            12, 13, 14, 
            12, 14, 15, 

            16, 17, 18, 
            16, 18, 19, 

            20, 21, 22, 
            20, 22, 23  
        };

        td::UINT4 nVertices = 4*6;
        
        _gpuBuffer.appendVertices(vertices, nVertices);
        
        td::UINT4 nIndices = 3*2*6;
        _gpuBuffer.appendIndices(indices, nIndices);
        _gpuBuffer.appendInstances(instanceData, _nInstances);
        
        pCubeTextureCmd = _gpuBuffer.createCommand();
        pCubeTextureCmd->createDrawElements(gui::gl::Primitive::Triangles, 0, nIndices);
        pCubeTextureCmd->setNumberOfInstances(_nInstances);
        _gpuBuffer.encode(pCubeTextureCmd);
        
        if (!_gpuBuffer.commit())
        {
            mu::dbgLog("ERROR! Cannot commit buffer to GPU");
            return;
        }

        _program.setBuffer(&_gpuBuffer);
        delete[] instanceData;
    }
protected:
    
    void onInit() override
    {
        auto [major, minor] = getOpenGLVersion();
        mu::dbgLog("Used opengl %d.%d", major, minor);
        
        if (!setupShaders())
        {
            mu::dbgLog("ERROR! OpenGL cannnot setup shaders!");
            assert(false);
            return;
        }
        setup();
        
        
        float fov = 45.0f; 
        float aspectRatio = 16.0f / 9.0f;
        float nearClip = 0.1f; 
        float farClip = 100.0f;

        _perspectiveMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);

        glm::vec3 cameraPosition = glm::vec3(8.0, 0.0, 0.0f); 
        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.5f);   
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);   

        _viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
        
        _mvpMatrix = _perspectiveMatrix * _viewMatrix; 
        _measure = glm::mat4(0);
        
        gui::gl::Context::enable(gui::gl::Context::Flag::DepthTest);
        gui::gl::Context::enable(gui::gl::Context::Flag::CullFace);

        _program.setMVP(_mvpMatrix);
        _program.setMeasure(_measure);
        
#ifdef DEBUG_GL
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            mu::dbgLog("OpenGL error: %x", error);
        }
#endif
    }
    
    bool prepareNextFrame() override
    {
        filter.resize(nMeasures);
        sumfilter.resize(nMeasures);
        std::string str = _message.c_str();
        std::stringstream ss(str);
        
        _measure = glm::mat4(0);
        float x;
        for (int i = 0; i < nMeasures; i++) {
            ss >> x;
            sumfilter[i] += x;
            filter[i].push(x);
            if (filter[i].size() > 10) {
                sumfilter[i] -= filter[i].front();
                filter[i].pop();
            }
            _measure[(i+1)/4][(i+1)%4]= 1.0 * sumfilter[i] / 10;
        }

        return true;
    }
    
    void onDraw(const gui::Rect& rect) override
    {
        gui::gl::Context::clear(td::ColorID::Black);
        gui::gl::Context::clear({gui::gl::Context::Clear::Color, gui::gl::Context::Clear::Depth});

        _program.activate();
        _program.setMeasure(_measure);
        _program.execute();

        _program.deActivate();
    }

public:
    GLView(std::vector<Cube>insts, int nInstances)
    {
        _nInstances = nInstances;
        for (auto x : insts) _insts.emplace_back(x);
        _gpuBuffer.init(64, 100, 100, 100, { gui::gl::DataType::vec3 }, { gui::gl::DataType::vec3 , gui::gl::DataType::vec3 , gui::gl::DataType::vec3 , gui::gl::DataType::vec3 , gui::gl::DataType::vec3 , gui::gl::DataType::vec3 , gui::gl::DataType::vec3 , gui::gl::DataType::vec3 , gui::gl::DataType::vec3 });
        
        gui::gl::Context reqContext(gui::gl::Context::Animation::Yes, gui::gl::DepthBuffer::Size::B2);
        createContext(reqContext, {gui::InputDevice::Event::Keyboard, gui::InputDevice::Event::PrimaryClicks, gui::InputDevice::Event::SecondaryClicks });
    }
    
    ~GLView()
    {
        //close_server = true;
        makeCurrentContext();
    }
    
    void updateSpeed(float val)
    {
        _dAngle = val;
    }
    
    
    void exportFrame()
    {

    }
};
