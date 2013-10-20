#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QList>
#include "widgetfile.h"

class FileManager : public QObject
{
    Q_OBJECT
public:
    static FileManager Instance;
    WidgetFile * currentWidgetFile() { if(_currentWidgetFileId < 0) return 0; return _widgetFiles.at(_currentWidgetFileId); }

    void initTheme();

    bool open(QString filename);
    void close(WidgetFile *widget);
    int count() { return _widgetFiles.count(); }
    int reverseAssociatedFileIndex(QString filename);

    File * file(int index);
    WidgetFile * widgetFile(QString filename);
    WidgetFile * widgetFile(int index) { return _widgetFiles.at(index); }

signals:
    void cursorPositionChanged(int,int);
    void requestOpenFile(QString);
    void filenameChanged(QString);
    void filenameChanged(WidgetFile*, QString);
    /**
     * @brief verticalSplitterChanged signal is send if the console or the errortable (simpleoutput)
     *        is open or close but not every time the splitter is moved
     */
    void verticalSplitterChanged();
    void messageFromCurrentFile(QString);

public slots:
    bool newFile();
    void openAssociatedFile();

    void sendFilenameChanged(WidgetFile* w, QString name) { emit filenameChanged(w,name); emit filenameChanged(name); }

    /**
     * The main parts of the slots are just used to call the same slots on the current file
     */
    void save() { this->currentWidgetFile()->save(); }
    void saveAs() { this->currentWidgetFile()->saveAs(); }
    void pdflatex(void){ this->currentWidgetFile()->pdflatex(); }
    void bibtex(void) { this->currentWidgetFile()->bibtex(); }
    void openFindReplaceWidget() { this->currentWidgetFile()->openFindReplaceWidget(); }
    void undo();
    void redo();
    void copy();
    void cut();
    void paste();
    void wrapEnvironment();
    void setPdfSynchronized(bool pdfSynchronized);
    void jumpToPdfFromSource();
    void rehighlight();
    void toggleConsole();
    void toggleErrorTable();

    void setCurrent(WidgetFile * widget);
    void setCurrent(int index);


private slots:
    void sendCursorPositionChanged(int x, int y) { emit cursorPositionChanged(x, y); }
    void sendVerticalSplitterChanged() { emit verticalSplitterChanged(); }
    void sendMessageFromCurrentFile(QString message) { emit messageFromCurrentFile(message); }

private:

    void createMasterConnexions(WidgetFile * widget, WidgetFile * master);
    void deleteMasterConnexions(WidgetFile * widget);
    void changeConnexions(WidgetFile *oldFile);

    explicit FileManager(QObject *parent = 0);
    QList<WidgetFile *> _widgetFiles;
    int _currentWidgetFileId;
    bool _pdfSynchronized;
};

#endif // FILEMANAGER_H
