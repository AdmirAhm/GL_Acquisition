//
//  Created by Izudin Dzafic on 28/07/2020.
//  Copyright © 2020 IDz. All rights reserved.
//
#pragma once
#include <gui/gl/Program.h>

class Program : public gui::gl::Program
{
protected:
    
    //if linking is ok, this method is called
    void onLinked() override
    {
        reserveUniforms(1);
        _matrixLocation = getUniformLocation("mvp");
        _uniformLocations[0] = getUniformLocation("measurein");
        assert(_matrixLocation >= 0);
    }
    
    void onError() override
    {
        assert(false);
    }
    
public:
    Program()
    {
    }
    
    //set MVP matrix uniform
    void setMVP(const glm::mat4x4& mvp)
    {
        setUniformValue(_matrixLocation, mvp);
    }

    void setMeasure(const glm::mat4x4& measure)
    {
        setUniformValue(0, measure);
    }
    
};
