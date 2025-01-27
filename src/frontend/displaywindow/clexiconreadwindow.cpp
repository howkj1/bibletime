/*********
*
* In the name of the Father, and of the Son, and of the Holy Spirit.
*
* This file is part of BibleTime's source code, https://bibletime.info/
*
* Copyright 1999-2021 by the BibleTime developers.
* The BibleTime source code is licensed under the GNU General Public License
* version 2.0.
*
**********/

#include "clexiconreadwindow.h"

#include <QAction>
#include <QString>
#include "../../backend/keys/cswordkey.h"
#include "../../backend/keys/cswordldkey.h"
#include "../../backend/managers/cswordbackend.h"
#include "../../util/cresmgr.h"
#include "../keychooser/ckeychooser.h"
#include "btactioncollection.h"


CLexiconReadWindow::CLexiconReadWindow(
        QList<CSwordModuleInfo *> const & modules,
        CMDIArea * parent)
    : CDisplayWindow(modules, parent)
{}

void CLexiconReadWindow::insertKeyboardActions(BtActionCollection * a) {
    auto * actn = new QAction(tr("Next entry"), a);
    actn->setShortcut(CResMgr::displaywindows::lexiconWindow::nextEntry::accel);
    a->addAction("nextEntry", actn);

    actn = new QAction(tr("Previous entry"), a);
    actn->setShortcut(CResMgr::displaywindows::lexiconWindow::previousEntry::accel);
    a->addAction("previousEntry", actn);
}

void CLexiconReadWindow::initActions() {
    CDisplayWindow::initActions();
    insertKeyboardActions(actionCollection());
    initAddAction("nextEntry", this, &CLexiconReadWindow::nextEntry);
    initAddAction("previousEntry", this, &CLexiconReadWindow::previousEntry);
    m_actionCollection->readShortcuts("Lexicon shortcuts");
}

void CLexiconReadWindow::reload(CSwordBackend::SetupChangedReason reason) {
    CDisplayWindow::reload(reason);
    actionCollection()->readShortcuts("Lexicon shortcuts");
}

void CLexiconReadWindow::nextEntry()
{ keyChooser()->setKey(ldKey()->NextEntry()); }

void CLexiconReadWindow::previousEntry()
{ keyChooser()->setKey(ldKey()->PreviousEntry()); }

CSwordLDKey * CLexiconReadWindow::ldKey()
{ return dynamic_cast<CSwordLDKey*>(m_swordKey); }
