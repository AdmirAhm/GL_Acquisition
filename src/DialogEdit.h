//
//  Created by Izudin Dzafic on 28/07/2020.
//  Copyright © 2020 IDz. All rights reserved.
//
#pragma once
#include <gui/Dialog.h>
#include "ViewEdit.h"
#include "Cube.h"


class DialogEdit : public gui::Dialog
{
protected:
    ViewEdit _view;

    bool onClick(Dialog::Button::ID btnID, gui::Button* pButton) override
    {

        return true;
    }
public:
    DialogEdit(std::vector<Cube>&insts, int nInstances, gui::Control* pView, td::UINT4 wndID = 0)
        : gui::Dialog(pView, { 
                                {gui::Dialog::Button::ID::Cancel, tr("Cancel")} }, gui::Size(400, 800), wndID)
        , _view(insts, nInstances)
    {
        setCentralView(&_view);
        
        //        composeContent();
    }
};
