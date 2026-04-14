#include "zenedit.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QMenuBar>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

ZenEdit::ZenEdit(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("ZenEdit");
    resize(800, 600);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    editor = new QTextEdit(this);
    layout->addWidget(editor);

    setCentralWidget(centralWidget);
    createMenus();
    createEditMenu();
    applyStyle();
}

void ZenEdit::createMenus() {
    QMenuBar *mBar = menuBar();
    QMenu *fileMenu = mBar->addMenu("&File");
 
    QAction *openAction = fileMenu->addAction("&Open");
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &ZenEdit::openFile);
 
    QAction *saveAction = fileMenu->addAction("&Save");
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &ZenEdit::saveFile);
 
    QAction *saveAsAction = fileMenu->addAction("&Save As...");
    connect(saveAsAction, &QAction::triggered, this, &ZenEdit::saveAsFile);
 
    fileMenu->addSeparator();
 
    QAction *revertAction = fileMenu->addAction("&Revert");
    connect(revertAction, &QAction::triggered, this, &ZenEdit::revertFile);
 
    fileMenu->addSeparator();
 
    QAction *exitAction = fileMenu->addAction("&Exit");
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
}
 
void ZenEdit::createEditMenu() {
    QMenuBar *mBar = menuBar();
    QMenu *editMenu = mBar->addMenu("&Edit");
 
    QAction *undoAction = editMenu->addAction("&Undo");
    undoAction->setShortcut(QKeySequence::Undo);
    connect(undoAction, &QAction::triggered, this, &ZenEdit::undo);
 
    QAction *redoAction = editMenu->addAction("&Redo");
    redoAction->setShortcut(QKeySequence::Redo);
    connect(redoAction, &QAction::triggered, this, &ZenEdit::redo);
}

void ZenEdit::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt);;All Files (*)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        editor->setPlainText(in.readAll());
        currentFile = fileName;
        setWindowTitle("ZenEdit - " + fileName);
        file.close();
    } else {
        QMessageBox::critical(this, "Error", "Could not open file");
    }
}

void ZenEdit::saveFile() {
    if (currentFile.isEmpty()) {
        saveAsFile();
    } else {
        QFile file(currentFile);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << editor->toPlainText();
            file.close();
        } else {
            QMessageBox::critical(this, "Error", "Could not save file");
        }
    }
}

void ZenEdit::saveAsFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File As", "", "Text Files (*.txt);;All Files (*)");
    if (fileName.isEmpty()) return;
 
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << editor->toPlainText();
        currentFile = fileName;
        setWindowTitle("ZenEdit - " + fileName);
        file.close();
    } else {
        QMessageBox::critical(this, "Error", "Could not save file");
    }
}
 
void ZenEdit::undo() {
    editor->undo();
}
 
void ZenEdit::redo() {
    editor->redo();
}
 
void ZenEdit::revertFile() {
    if (currentFile.isEmpty()) return;
 
    QFile file(currentFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        editor->setPlainText(in.readAll());
        file.close();
    } else {
        QMessageBox::critical(this, "Error", "Could not revert file");
    }
}
 
void ZenEdit::applyStyle() {
    this->setStyleSheet(
        "QMainWindow { background-color: #f5f5f5; }"
        "QMenuBar { background-color: #f5f5f5; color: #333333; border-bottom: 1px solid #ddd; }"
        "QMenuBar::item:selected { background-color: #eee; }"
        "QMenu { background-color: #fdfdfd; color: #333333; border: 1px solid #ddd; }"
        "QMenu::item:selected { background-color: #eee; }"
        "QTextEdit { "
        "  background-color: #fdfdfd; "
        "  color: #333333; "
        "  border: none; "
        "  font-family: 'Courier New', monospace; "
        "  font-size: 14px; "
        "  padding: 20px; "
        "}"
    );
}
