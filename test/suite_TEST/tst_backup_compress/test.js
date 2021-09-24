import * as names from 'names.js';

function main() {
    clickButton(waitForObject(names.mainWindowPushButtonQPushButton));
    clickButton(waitForObject(names.dialogBackupPushButtonQPushButton));
    mouseClick(waitForObjectItem(names.splitterSidebarQSidebar, "c"), 32, 14, Qt.NoModifier, Qt.LeftButton);
    doubleClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Documents"), 54, 17, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "source"), 50, 18, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
    clickButton(waitForObject(names.dialogBackupPushButton2QPushButton));
    mouseClick(waitForObjectItem(names.splitterSidebarQSidebar, "c"), 25, 8, Qt.NoModifier, Qt.LeftButton);
    mouseClick(waitForObjectItem(names.stackedWidgetTreeViewQTreeView, "Music"), 54, 15, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.qFileDialogChooseQPushButton));
    mouseClick(waitForObject(names.dialogBackupDialogBackup), 285, 319, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.dialogBackupCheckBox2QCheckBox));
    clickButton(waitForObject(names.dialogBackupPushButton5QPushButton));
}
