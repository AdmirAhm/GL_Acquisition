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
#include "ViewSwitch.h"
#include <gui/ComboBox.h>


class ViewEdit : public gui::View
{
private:

    td::String int2str(int a) {
        char pom[100];
        int i = 0;
        bool neg = false;
        if (a < 0) neg = true;
        a = abs(a);
        while (a != 0) {
            pom[i] = '0' + a % 10;
            a /= 10;
            i++;
        }
        if (neg) {
            pom[i] = '-';
            i++;
        }
        for (int j = i - 1; j > (i - 1) / 2; j--) {
            char temp = pom[j];
            pom[j] = pom[i - 1 - j];
            pom[i - 1 - j] = temp;
        }
        pom[i] = '\0';
        return td::String(pom);
    }

protected:
    ViewSwitch _vs;
    gui::VerticalLayout _vl;
    gui::ComboBox _cb;
    int _nInstances;
public:
    ViewEdit(std::vector<Cube>& instances, int nInstances)
        :_vl(2)
        ,_vs(instances, nInstances)
    {
        for (int i = 0; i < nInstances; i++) {
            cnt::StringBuilder sb;
            sb.appendCString("Cube");
            sb.appendString(int2str(i+1));
            td::String pom;
            sb.getString(pom);
            _cb.addItem(pom);
        }
        _cb.setValue(0);
        _vl.append(_cb);
        _vl.append(_vs);
        setLayout(&_vl);
        _vs.showView(0);
    }
    ~ViewEdit() {

    }
    bool onChangedSelection(gui::ComboBox* pCmb) {
        td::Variant var;
        _cb.getValue(var);
        td::INT4 ind = var.i4Val();
        _vs.showView(ind);
        return true;
    }
    bool onFinishEdit(gui::LineEdit* pCtrl) override {
        return true;
    }
};
