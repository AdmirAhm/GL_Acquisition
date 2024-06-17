//
//  Created by Izudin Dzafic on 28/07/2020.
//  Copyright © 2020 IDz. All rights reserved.
//
#pragma once
#include <gui/Dialog.h>
#include "GLView.h"
#include "Cube.h"


class DialogGL : public gui::Dialog
{
protected:
    GLView _view;

    bool onClick(Dialog::Button::ID btnID, gui::Button* pButton) override
    {

        return true;
    }
public:
    DialogGL(std::vector<Cube>insts, int nInstances, gui::Control* pView, td::UINT4 wndID = 0)
        : gui::Dialog(pView, { 
                                {gui::Dialog::Button::ID::Cancel, tr("Cancel")} }, gui::Size(1200, 600), wndID)
        , _view(insts, nInstances)
    {
        setCentralView(&_view);
        
        //        composeContent();
    }
};
