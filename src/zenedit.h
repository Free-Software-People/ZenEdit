#ifndef ZENEDIT_H
#define ZENEDIT_H

#include <QMainWindow>
#include <QTextEdit>
#include <QString>

class ZenEdit : public QMainWindow {
    Q_OBJECT

public:
    ZenEdit(QWidget *parent = nullptr);
    ~ZenEdit() = default;

private slots:
    void openFile();
    void saveFile();
    void saveAsFile();
    void undo();
    void redo();
    void revertFile();

private:
    QTextEdit *editor;
    QString currentFile;
    void applyStyle();
    void createMenus();
    void createEditMenu();
};

#endif // ZENEDIT_H
