/*
 * Cppcheck - A tool for static C/C++ code analysis
 * Copyright (C) 2007-2016 Cppcheck team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QFileDialog>
#include <QActionGroup>
#include <QTimer>
#include <QStringList>

#include "settings.h"
#include "platforms.h"
#include "ui_mainwindow.h"

class ThreadHandler;
class TranslationHandler;
class ScratchPad;
class LogView;
class Project;
class ErrorItem;
class QAction;

/// @addtogroup GUI
/// @{

/**
 * @brief Main window for cppcheck-gui
 *
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:

    /**
     * @brief Maximum number of MRU project items in File-menu.
     */
    enum { MaxRecentProjects = 5 };

    MainWindow(TranslationHandler* th, QSettings* settings);
    virtual ~MainWindow();

    /**
      * List of checked platforms.
      */
    Platforms mPlatforms;

    /**
     * @brief Checks given code
     *
     * @param code Content of the (virtual) file to be checked
     * @param filename Name of the (virtual) file to be checked - determines language.
     */
    void checkCode(const QString& code, const QString& filename);

public slots:

    /** @brief Slot for check files menu item */
    void checkFiles();

    /** @brief Slot to recheck all files */
    void reCheckAll();

    /**
     * @brief Slot to recheck selected files
     * @param selectedFilesList list of selected files
     */
    void performSelectedFilesCheck(QStringList selectedFilesList);

    /** @brief Slot to recheck modified files */
    void reCheckModified();

    /** @brief Slot to clear all search results */
    void clearResults();

    /** @brief Slot to open XML report file */
    void openResults();

    /**
     * @brief Show errors with type "style"
     * @param checked Should errors be shown (true) or hidden (false)
     */
    void showStyle(bool checked);

    /**
     * @brief Show errors with type "error"
     * @param checked Should errors be shown (true) or hidden (false)
     */
    void showErrors(bool checked);

    /**
     * @brief Show errors with type "warning"
     * @param checked Should errors be shown (true) or hidden (false)
     */
    void showWarnings(bool checked);

    /**
     * @brief Show errors with type "portability"
     * @param checked Should errors be shown (true) or hidden (false)
     */
    void showPortability(bool checked);

    /**
     * @brief Show errors with type "performance"
     * @param checked Should errors be shown (true) or hidden (false)
     */
    void showPerformance(bool checked);

    /**
     * @brief Show errors with type "information"
     * @param checked Should errors be shown (true) or hidden (false)
     */
    void showInformation(bool checked);

    /** @brief Slot to check all "Show errors" menu items */
    void checkAll();

    /** @brief Slot to uncheck all "Show errors" menu items */
    void uncheckAll();

    /** @brief Slot for check directory menu item */
    void checkDirectory();

    /** @brief Slot to open program's settings dialog */
    void programSettings();

    /** @brief Slot to open program's about dialog */
    void about();

    /** @brief Slot to to show license text */
    void showLicense();

    /** @brief Slot to to show authors list */
    void showAuthors();

    /** @brief Slot to save results */
    void save();

    /** @brief Slot to create new project file */
    void newProjectFile();

    /** @brief Slot to open project file and start checking contained paths. */
    void openProjectFile();

    /** @brief Slot to show scratchpad. */
    void showScratchpad();

    /** @brief Slot to close open project file. */
    void closeProjectFile();

    /** @brief Slot to edit project file. */
    void editProjectFile();

    /** @brief Slot for showing the log view. */
    void showLogView();

    /** @brief Slot for showing the scan and project statistics. */
    void showStatistics();

    /** @brief Slot for showing the library editor */
    void showLibraryEditor();

protected slots:

    /** @brief Slot for checkthread's done signal */
    void checkDone();

    /** @brief Lock down UI while checking */
    void checkLockDownUI();

    /** @brief Slot for enabling save and clear button */
    void resultsAdded();

    /** @brief Slot for showing/hiding standard toolbar */
    void toggleMainToolBar();

    /** @brief Slot for showing/hiding Categories toolbar */
    void toggleViewToolBar();

    /** @brief Slot for showing/hiding Filter toolbar */
    void toggleFilterToolBar();

    /** @brief Slot for updating View-menu before it is shown. */
    void aboutToShowViewMenu();

    /** @brief Slot when stop checking button is pressed */
    void stopChecking();

    /** @brief Open help file contents */
    void openHelpContents();

    /** @brief Add new line to log. */
    void log(const QString &logline);

    /** @brief Handle new debug error. */
    void debugError(const ErrorItem &item);

    /** @brief Filters the results in the result list. */
    void filterResults();

    /** @brief Opens recently opened project file. */
    void openRecentProject();

    /** @brief Selects the platform as checked platform. */
    void selectPlatform();

private:

    /** @brief Rechecks files */
    void reCheck(bool all);

    /**
     * @brief Recheck selected files
     * @param files list of selected files
     * @param all true if all files of list, false if modified files of list
     */
    void reCheckSelected(QStringList files, bool all);

    /**
      * @brief Check the project.
      * @param project Pointer to the project to check.
      */
    void checkProject(Project *project);

    /**
     * @brief Set current language
     * @param code Language code of the language to set (e.g. "en").
     */
    void setLanguage(const QString &code);

    /** @brief Event coming when application is about to close. */
    virtual void closeEvent(QCloseEvent *event);

    /**
     * @brief Helper function to toggle all show error menu items
     * @param checked Should all errors be shown (true) or hidden (false)
     */
    void toggleAllChecked(bool checked);

    /** @brief Helper function to enable/disable all check,recheck buttons */
    void enableCheckButtons(bool enable);

    /**
     * @brief Select files/or directory to check.
     * Helper function to open a dialog to ask user to select files or
     * directory to check. Use native dialogs instead of Qt:s own dialogs.
     *
     * @param mode Dialog open mode (files or directories)
     * @return QStringList of files or directories that were selected to check
     */
    QStringList selectFilesToCheck(QFileDialog::FileMode mode);

    /**
     * @brief Check project
     * @param p imported project
     */
    void doCheckProject(ImportProject p);

    /**
     * @brief Check all files specified in parameter files
     *
     * @param files List of files and/or directories to check
     */
    void doCheckFiles(const QStringList &files);

    /**
     * @brief Get our default cppcheck settings and read project file.
     *
     * @return Default cppcheck settings
     */
    Settings getCppcheckSettings();

    /** @brief Load program settings */
    void loadSettings();

    /** @brief Save program settings */
    void saveSettings() const;

    /**
     * @brief Format main window title.
     * @param text Text added to end of the title.
     */
    void formatAndSetTitle(const QString &text = QString());

    /** @brief Show help contents */
    void openOnlineHelp();

    /**
     * @brief Enable or disable project file actions.
     * Project editing and closing actions should be only enabled when project is
     * open and we are not checking files.
     * @param enable If true then actions are enabled.
     */
    void enableProjectActions(bool enable);

    /**
     * @brief Enable or disable project file actions.
     * Project opening and creating actions should be disabled when checking.
     * @param enable If true then actions are enabled.
     */
    void enableProjectOpenActions(bool enable);

    /**
     * @brief Add include directories.
     * @param includeDirs List of include directories to add.
     * @param result Settings class where include directories are added.
     */
    void addIncludeDirs(const QStringList &includeDirs, Settings &result);

    /**
     * @brief Handle command line parameters given to GUI.
     * @param params List of string given to command line.
     */
    void handleCLIParams(const QStringList &params);

    /**
     * @brief Load XML file to the GUI.
     * @param selectedFile Filename (inc. path) of XML file to load.
     */
    void loadResults(const QString selectedFile);

    /**
     * @brief Load XML file to the GUI.
     * @param selectedFile Filename (inc. path) of XML file to load.
     * @param sourceDirectory Path to the directory that the results were generated for.
     */
    void loadResults(const QString selectedFile, const QString sourceDirectory);

    /**
     * @brief Load project file to the GUI.
     * @param filePath Filename (inc. path) of project file to load.
     */
    void loadProjectFile(const QString &filePath);

    /**
     * @brief Load library file
     * @param library  library to use
     * @param filename filename (no path)
     * @return error code
     */
    Library::Error loadLibrary(Library *library, QString filename);

    /**
     * @brief Tries to load library file, prints message on error
     * @param library  library to use
     * @param filename filename (no path)
     * @return True if no error
     */
    bool tryLoadLibrary(Library *library, QString filename);

    /**
     * @brief Update project MRU items in File-menu.
     */
    void updateMRUMenuItems();

    /**
     * @brief Add project file (path) to the MRU list.
     * @param project Full path to the project file to add.
     */
    void addProjectMRU(const QString &project);

    /**
     * @brief Remove project file (path) from the MRU list.
     * @param project Full path of the project file to remove.
     */
    void removeProjectMRU(const QString &project);

    /** @brief Program settings */
    QSettings *mSettings;

    /** @brief Thread to check files */
    ThreadHandler *mThread;

    /** @brief List of user defined applications to open errors with */
    ApplicationList *mApplications;

    /** @brief Class to handle translation changes */
    TranslationHandler *mTranslation;

    /** @brief Class holding all UI components */
    Ui::MainWindow mUI;

    /** @brief Current checked directory. */
    QString mCurrentDirectory;

    /** @brief Log view. */
    LogView *mLogView;

    /** @brief Scratchpad. */
    ScratchPad* mScratchPad;

    /** @brief Project (file). */
    Project *mProject;

    /** @brief Filter field in the Filter toolbar. */
    QLineEdit* mLineEditFilter;

    /** @brief Timer to delay filtering while typing. */
    QTimer* mFilterTimer;

    /** @brief GUI actions for selecting the checked platform. */
    QActionGroup *mPlatformActions;

    /** @brief GUI actions for selecting the coding standard. */
    QActionGroup *mCStandardActions, *mCppStandardActions;

    /** @brief GUI actions for selecting language. */
    QActionGroup *mSelectLanguageActions;

    /**
     * @brief Are we exiting the cppcheck?
     * If this is true then the cppcheck is waiting for check threads to exit
     * so that the application can be closed.
     */
    bool mExiting;

    /** @brief Set to true in case of loading log file. */
    bool mIsLogfileLoaded;

    /**
     * @brief Project MRU menu actions.
     * List of MRU menu actions. Needs also to store the separator.
     */
    QAction *mRecentProjectActs[MaxRecentProjects + 1];
};
/// @}
#endif // MAINWINDOW_H
