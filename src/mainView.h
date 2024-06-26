#pragma once
#include <gui/View.h>
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
#include <dp/IDatabase.h>
#include "DialogEdit.h"




class mainView : public gui::View
{
protected:
    gui::Label _lblip;
    gui::LineEdit _ip;
    gui::Label _lblport;
    gui::LineEdit _port;
    gui::Label _lblinstances;
    gui::NumericEdit _instances;
    gui::Label _lblmeasures;
    gui::NumericEdit _measures;
    gui::Label _notcon;
    gui::Label _con;
    gui::TableEdit _tab;
    int _nInstances;

    gui::GridLayout _socket;
    gui::VerticalLayout _mainlt;
    gui::HorizontalLayout _hl;
    gui::HorizontalLayout _hl2;
    gui::HorizontalLayout _hl3;

    gui::Button _refresh;
    gui::Button _edit;
    gui::Button _run;

    std::vector<Cube>_insts;
public:
    mainView()
        : _lblip("IP address")
        , _lblport("PORT")
        , _notcon("Not connected")
        , _con("Connected")
        , _socket(2, 3)
        , _mainlt(5)
        , _refresh("Refresh")
        , _edit("Edit")
        , _run("Run")
        , _hl(4)
        , _hl2(3)
        , _hl3(5)
        , _lblinstances("Instances")
        , _instances(td::DataType::int4, gui::LineEdit::Messages::Send)
        , _lblmeasures("Measures")
        , _measures(td::DataType::int4, gui::LineEdit::Messages::Send)
    {
        _measures.setMaxValue(15);
        _instances.setMinValue(1);
        _measures.setMinValue(0);
        _instances.setValue(1);

        _socket.insert(0, 0, _lblip);
        _socket.insert(0, 1, _ip);
        _socket.insert(1, 0, _lblport);
        _socket.insert(1, 1, _port);

        _hl.append(_con);
        _hl.append(_notcon);
        _hl.appendSpacer();
        _hl.append(_refresh, td::HAlignment::Right);

        _hl2.appendSpacer();
        _hl2.append(_edit);
        _hl2.append(_run);

        _hl3.append(_lblinstances);
        _hl3.append(_instances);
        _hl3.appendSpacer();
        _hl3.append(_lblmeasures);
        _hl3.append(_measures);
        

        _mainlt.append(_socket);
        _mainlt.append(_hl);
        _mainlt.append(_hl3);
        _mainlt.append(_tab);
        _mainlt.append(_hl2);

        _con.setBold();
        _notcon.setBold();
        _con.setBackgroundColor(td::ColorID::Green);
        _notcon.setBackgroundColor(td::ColorID::Red);
        _con.hide(true, false);

        _ip.setText(ip);
        _port.setText(port);

        _ip.setAsReadOnly(true);
        _port.setAsReadOnly(true);

        setLayout(&_mainlt);

        _insts.emplace_back(Cube());
        _insts[0].params={0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 1.0f,
            0, 0, 0, 0.0f, 0.0f, 0, 1.0f, 2.0f, 0,
            1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.2f, 0.2f, 1.0f};
        _nInstances = 1;
    }

    ~mainView() {
        close_server = true;
    }


    bool onClick(gui::Button* pBtn) override
    {
        if (pBtn == &_refresh) {
            if (!isconnected) {
                _notcon.hide(false, false);
                _con.hide(true, false);
            }
            else {
                _con.hide(false, false);
                _notcon.hide(true, false);
            }
            return true;
        }
        if (pBtn == &_run) {
            DialogGL* dlg = new DialogGL(_insts, _nInstances, pBtn); 
            dlg->openModal([](gui::Dialog* pDlg) {});
        }

        if (pBtn == &_edit) {
            DialogEdit* dlg = new DialogEdit(_insts, _nInstances, pBtn);
            dlg->openModal([](gui::Dialog* pDlg) {});
        }
        return false;
    }
    
    bool onFinishEdit(gui::LineEdit* pCtrl) override {
        if (pCtrl == &_instances) {
            td::Variant val=_instances.getValue();
            _nInstances = val.i4Val();
            _insts.resize(_nInstances);
            return true;
        }
        if (pCtrl == &_measures) {
            td::Variant val = _measures.getValue();
            nMeasures = val.i4Val();
            return true;
        }
        return false;
    }
};
