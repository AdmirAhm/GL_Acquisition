#pragma once
#include <gui/View.h>
#include <gui/ViewSwitcher.h>
#include <gui/Layout.h>
#include <gui/Label.h>
#include <gui/LineEdit.h>
#include <gui/NumericEdit.h>
#include <gui/TextEdit.h>
#include <gui/Button.h>
#include <gui/HorizontalLayout.h>
#include <gui/VerticalLayout.h>
#include <gui/GridLayout.h>
#include <cnt/StringBuilder.h>
#include <gui/GridComposer.h>
#include <gui/TableEdit.h>
#include "global.h"
#include "DialogGL.h"
#include "Cube.h"
#include <gui/ViewScroller.h>
#include "ViewSingle.h"


class ViewSwitch : public gui::ViewSwitcher
{
private:

protected:
    std::vector<ViewSingle*>_views;
    int _nInstances;
public:
    ViewSwitch(std::vector<Cube>& instances, int nInstances)
        :ViewSwitcher(nInstances)
    {
        for (auto &x : instances) {
            ViewSingle* vs = new ViewSingle(x);
            addView(vs);
        }

    }
    ~ViewSwitch() {
        for (auto& x : _views) delete x;
    }

    bool onFinishEdit(gui::LineEdit* pCtrl) override {
        return true;
    }
};
