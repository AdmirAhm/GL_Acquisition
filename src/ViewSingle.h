#pragma once
#include <gui/View.h>
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



class ViewSingle : public gui::View
{
private:
    int getEditNumber(gui::LineEdit* ptr) {
        for (int i = 0; i < _edits.size(); i++) {
            if (ptr == _edits[i]) return i;
        }
        return -1;
    }
protected:
    gui::GridLayout _gl;
    std::vector<gui::Label*>_lbls;
    std::vector<gui::NumericEdit*>_edits;
    Cube& _instance;
    int _nInstances;
public:
    ViewSingle(Cube &instance)
        :_gl(19, 3)
        ,_instance(instance)
    {

        _lbls.resize(10 , nullptr);
        _edits.resize(27 , nullptr);
        gui::GridComposer gc(_gl);
        int i = 0;
        td::Decimal4 pom;
            _lbls[i * 10] = new gui::Label("Cube");
            gc.appendRow(*_lbls[i * 10], 1);

            _lbls[i * 10+1] = new gui::Label("Initial Rotation");
            gc.appendRow(*_lbls[i * 10+1], 1);
            _edits[i * 27] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27+1] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27+2] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            gc.appendRow(*_edits[i * 27+0], 1);
            gc.appendCol(*_edits[i * 27+1], 1);
            gc.appendCol(*_edits[i * 27+2], 1);
            pom = _instance.params[0];
            _edits[i * 27]->setValue(pom, false);
            pom = _instance.params[1];
            _edits[i * 27 + 1]->setValue(pom, false);
            pom = _instance.params[2];
            _edits[i * 27 + 2]->setValue(pom, false);

            _lbls[i * 10+2] = new gui::Label("Initial Translation");
            gc.appendRow(*_lbls[i * 10+2], 1);
            _edits[i * 27 + 3] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 4] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 5] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            pom = _instance.params[3];
            _edits[i * 27 + 3]->setValue(pom, false);
            pom = _instance.params[4];
            _edits[i * 27 + 4]->setValue(pom, false);
            pom = _instance.params[5];
            _edits[i * 27 + 5]->setValue(pom, false);
            gc.appendRow(*_edits[i * 27 + 3], 1);
            gc.appendCol(*_edits[i * 27 + 4], 1);
            gc.appendCol(*_edits[i * 27 + 5], 1);

            _lbls[i * 10+3] = new gui::Label("Initial Color");
            gc.appendRow(*_lbls[i * 10+3], 1);
            _edits[i * 27 + 6] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 7] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 8] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            pom = _instance.params[6];
            _edits[i * 27 + 6]->setValue(pom, false);
            pom = _instance.params[7];
            _edits[i * 27 + 7]->setValue(pom, false);
            pom = _instance.params[8];
            _edits[i * 27 + 8]->setValue(pom, false);
            gc.appendRow(*_edits[i * 27 + 6], 1);
            gc.appendCol(*_edits[i * 27 + 7], 1);
            gc.appendCol(*_edits[i * 27 + 8], 1);

            _lbls[i * 10+4] = new gui::Label("Rotation Measure");
            gc.appendRow(*_lbls[i * 10+4], 1);
            _edits[i * 27 + 9] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 10] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 11] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            pom = _instance.params[9];
            _edits[i * 27 + 9]->setValue(pom, false);
            pom = _instance.params[10];
            _edits[i * 27 + 10]->setValue(pom, false);
            pom = _instance.params[11];
            _edits[i * 27 + 11]->setValue(pom, false);
            gc.appendRow(*_edits[i * 27 + 9], 1);
            gc.appendCol(*_edits[i * 27 + 10], 1);
            gc.appendCol(*_edits[i * 27 + 11], 1);

            _lbls[i * 10+5] = new gui::Label("Translation Measure");
            gc.appendRow(*_lbls[i * 10+5], 1);
            _edits[i * 27 + 12] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 13] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 14] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            pom = _instance.params[12];
            _edits[i * 27 + 12]->setValue(pom, false);
            pom = _instance.params[13];
            _edits[i * 27 + 13]->setValue(pom, false);
            pom = _instance.params[14];
            _edits[i * 27 + 14]->setValue(pom, false);
            gc.appendRow(*_edits[i * 27 + 12], 1);
            gc.appendCol(*_edits[i * 27 + 13], 1);
            gc.appendCol(*_edits[i * 27 + 14], 1);

            _lbls[i * 10+6] = new gui::Label("Color Measure");
            gc.appendRow(*_lbls[i * 10+6], 1);
            _edits[i * 27 + 15] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 16] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 17] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            pom = _instance.params[15];
            _edits[i * 27 + 15]->setValue(pom, false);
            pom = _instance.params[16];
            _edits[i * 27 + 16]->setValue(pom, false);
            pom = _instance.params[17];
            _edits[i * 27 + 17]->setValue(pom, false);
            gc.appendRow(*_edits[i * 27 + 15], 1);
            gc.appendCol(*_edits[i * 27 + 16], 1);
            gc.appendCol(*_edits[i * 27 + 17], 1);

            _lbls[i * 10+7] = new gui::Label("Rotation Factor");
            gc.appendRow(*_lbls[i * 10+7], 1);
            _edits[i * 27 + 18] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 19] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 20] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            pom = _instance.params[18];
            _edits[i * 27 + 18]->setValue(pom, false);
            pom = _instance.params[19];
            _edits[i * 27 + 19]->setValue(pom, false);
            pom = _instance.params[20];
            _edits[i * 27 + 20]->setValue(pom, false);
            gc.appendRow(*_edits[i * 27 + 18], 1);
            gc.appendCol(*_edits[i * 27 + 19], 1);
            gc.appendCol(*_edits[i * 27 + 20], 1);

            _lbls[i * 10+8] = new gui::Label("Translation Factor");
            gc.appendRow(*_lbls[i * 10+8], 1);
            _edits[i * 27 + 21] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 22] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 23] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            pom = _instance.params[21];
            _edits[i * 27 + 21]->setValue(pom, false);
            pom = _instance.params[22];
            _edits[i * 27 + 22]->setValue(pom, false);
            pom = _instance.params[23];
            _edits[i * 27 + 23]->setValue(pom, false);
            gc.appendRow(*_edits[i * 27 + 21], 1);
            gc.appendCol(*_edits[i * 27 + 22], 1);
            gc.appendCol(*_edits[i * 27 + 23], 1);

            _lbls[i * 10+9] = new gui::Label("Color Factor");
            gc.appendRow(*_lbls[i * 10+9], 1);
            _edits[i * 27 + 24] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 25] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            _edits[i * 27 + 26] = new gui::NumericEdit(td::DataType::decimal4, gui::LineEdit::Messages::Send);
            pom = _instance.params[24];
            _edits[i * 27 + 24]->setValue(pom, false);
            pom = _instance.params[25];
            _edits[i * 27 + 25]->setValue(pom, false);
            pom = _instance.params[26];
            _edits[i * 27 + 26]->setValue(pom, false);
            gc.appendRow(*_edits[i * 27 + 24], 1);
            gc.appendCol(*_edits[i * 27 + 25], 1);
            gc.appendCol(*_edits[i * 27 + 26], 1);
        
        setLayout(&_gl);
    }
    ~ViewSingle() {
        for (int i = 0; i < _lbls.size(); i++) delete _lbls[i];
        for (int i = 0; i < _edits.size(); i++) delete _edits[i];
    }

    bool onFinishEdit(gui::LineEdit* pCtrl) override {
        int br=getEditNumber(pCtrl);
        if (br == -1) return false;
        td::Variant pom;
        pCtrl->getValue(pom);
        _instance.params[br % 27] = pom.dec4Val().getAsFloat();
        return true;
    }
};
